/*
	File:	MTAudioProcessingTap.h

	Framework:	MediaToolbox

	Copyright 2011-2013 Apple Inc. All rights reserved.
*/

#ifndef MTAUDIOPROCESSINGTAP_H
#define MTAUDIOPROCESSINGTAP_H

#include <CoreFoundation/CoreFoundation.h>
#include <CoreMedia/CMBase.h>
#include <CoreMedia/CMTimeRange.h>
#include <AudioToolbox/AudioToolbox.h>

#if defined(__cplusplus)
extern "C"
{
#endif

#pragma pack(push, 4)

typedef const struct opaqueMTAudioProcessingTap *MTAudioProcessingTapRef; // CFType, retain/release please

MT_EXPORT CFTypeID MTAudioProcessingTapGetTypeID(void) __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_6_0);

/*!
	@enum		MTAudioProcessingTapCreationFlags
	@abstract	Flags used when creating audio processing taps.

	@discussion
		Either the PreEffects or PostEffects flag must be set, but not both.

	@constant	kMTAudioProcessingTapCreationFlag_PreEffects
		Signifies that the processing tap is inserted before any effects.
	@constant	kMTAudioProcessingTapCreationFlag_PostEffects
		Signifies that the processing tap is inserted after any effects.
*/
enum {
	kMTAudioProcessingTapCreationFlag_PreEffects	= (1 << 0),
	kMTAudioProcessingTapCreationFlag_PostEffects	= (1 << 1),
};
typedef uint32_t MTAudioProcessingTapCreationFlags;

/*!
	@enum		MTAudioProcessingTapFlags
	@abstract	Flags passed to the process callback and from GetSourceAudio.

	@constant	kMTAudioProcessingTapFlag_StartOfStream
		Signifies that the source audio is the beginning of a continuous stream,
		i.e., following the beginning or resumption of playback.
		Returned from GetSourceAudio.
	@constant	kMTAudioProcessingTapFlag_EndOfStream
		Signifies that the source audio is past the end of stream. This happens when
		the audio queue is being stopped asynchronously and has finished playing
		all of its data. Returned from GetSourceAudio and should be propagated
		on return from the process callback.
*/
enum {
	// these are flags that are passed to the process callback and from GetSourceAudio
	kMTAudioProcessingTapFlag_StartOfStream			= (1 << 8),
    kMTAudioProcessingTapFlag_EndOfStream			= (1 << 9),
};
typedef uint32_t MTAudioProcessingTapFlags;

/*!
	@typedef	MTAudioProcessingTapInitCallback
	@abstract	Init callback.

	@discussion
		An init callback that is invoked when MTAudioProcessingTapCreate() is called.
		The init callback is always balanced by a finalize callback when the MTAudioProcessingTap object
		is released.

	@param		tap
				The processing tap.
	@param		clientInfo
				The client data of the processing tap passed in callbacks struct in MTAudioProcessingTapCreate().
	@param		tapStorageOut
				Additional client data.  The intent is for clients to allocate a block of memory for use within their custom 
				MTAudioProcessingTap implementation that will be freed when the finalize callback is invoked.  This argument
				is optional.
*/
typedef void (*MTAudioProcessingTapInitCallback)(
		MTAudioProcessingTapRef tap,
		void *clientInfo,
		void **tapStorageOut);

/*!
	@typedef	MTAudioProcessingTapFinalizeCallback
	@abstract	Finalize callback.

	@discussion
		This callback is called when it is safe to free any buffers or other state associated with the tap.
		This callback will be called exactly once when the MTAudioProcessingTap object is finalized.
		If tapStorage was allocated in the init callback, it should be freed here.

	@param		tap
				The processing tap.
*/
typedef void (*MTAudioProcessingTapFinalizeCallback)(MTAudioProcessingTapRef tap);

/*!
	@typedef	MTAudioProcessingTapPrepareCallback
	@abstract	Audio processing preparation callback.

	@discussion
		A preparation callback that is invoked when the underlying audio machinery is initialized.

		The preparation callback should be where output buffers that will be returned by the
		ProcessingTapCallback are allocated (unless in-place processing is desired).

		Note that the preparation callback can potentially be called multiple times over the lifetime
		of the tap object, if the client performs an operation that requires the underlying audio machinery to
		be torn down and rebuilt.

	@param		tap
				The processing tap.
	@param		maxFrames
				The maximum number of sample frames that can be requested of a processing
				tap at any one time. Typically this will be approximately 50 msec of audio
				(2048 samples @ 44.1kHz).
	@param		processingFormat
				The format in which the client will receive the audio data to be processed.
				This will always be the same sample rate as the client format and usually
				the same number of channels as the client format of the audio queue. (NOTE:
				the number of channels may be different in some cases if the client format
				has some channel count restrictions; for example, if the client provides 5.1
				AAC, but the decoder can only produce stereo). The channel order, if the
				same as the client format, will be the same as the client channel order. If
				the channel count is changed, it will be to either 1 (mono) or 2 (stereo, in
				which case the first channel is left, the second right).

				If the data is not in a convenient format for the client to process in, then
				the client should convert the data to and from that format. This is the most
				efficient mechanism to use, as the audio system may choose a format that is
				most efficient from its playback requirement.
*/
typedef void (*MTAudioProcessingTapPrepareCallback)(
		MTAudioProcessingTapRef tap,
		CMItemCount maxFrames,
		const AudioStreamBasicDescription *processingFormat);

/*!
	@typedef	MTAudioProcessingTapUnprepareCallback
	@abstract	Audio processing unpreparation callback.

	@discussion
		The unpreparation callback is invoked when the underlying audio machinery stops calling the process callback.

		Preparation/Unpreparation callbacks are always paired.

		Process callbacks will only ever be called after the prepare callback returns, and before unprepare is called.

	@param		tap
				The processing tap.
*/
typedef void (*MTAudioProcessingTapUnprepareCallback)(MTAudioProcessingTapRef tap);

/*!
	@typedef	MTAudioProcessingTapProcessCallback
	@abstract	A function called when an audio track has data to be processed by its tap.

	@discussion
		A processing callback is invoked when the audio track has data that can be processed by a
		given tap.

		The processing callback will be called when there is sufficient input data to provide for
		processing. The callback should then go and request as much source data as it needs in order
		to produce the requested number of processed samples. When the callback requests source data,
		it may receive less data than it requests.

		The tap must provide the same number of samples that are being requested. Under normal circumstances,
		the source data it requests should be satisfied (as the client running the audio queue is also
		providing the queue with the audio source material). If there is insufficient source data available
		(this is indicated by the numberFramesOut from the GetSourceAudio call), then the processing tap
		should cope as best as it can; it can either return less data than was requested, insert silence,
		insert noise, etc.
		If less data is returned than requested, the remainder will be filled with silence.

		A processing tap is a real-time operation, so the general Core Audio limitations for real-time
		processing apply.  For example, care should be taken not to allocate memory or call into
		blocking system calls, as this will interfere with the real-time nature of audio playback.

		Under normal operation, the source data will be continuous from the last time the callback was
		called, and the processed samples should be continuous from the previous samples returned. If
		there is any discontinuity between the last samples provided for processing, the audio queue will
		set the kMTAudioProcessingTapFlag_StartOfStream bit in the flags. After a discontinuity, the
		first sample that the processing tap outputs should correspond to the first sample that was
		provided in the source samples (so a reset + consequent process serves to re-anchor a
		relationship between the processing tap's source and processed samples). In this case, the
		processing tap will typically discard any previous state (for example, if a processing tap was
		adding a reverb to a signal, then the discontinuity flag would act the same as AudioUnitReset;
		any previous source information in the processing tap should be discarded).

		The caller is responsible for absorbing any processing delays. For example, if the
		processing is to be done by an audio unit that reports a processing latency, then the caller
		should remove those latency samples from the audio unit's rendering and not return them to
		the tap.

		The processing tap may operate on the provided source data in place ("in-place processing")
		and return pointers to that buffer, rather than its own. This is similar to audio
		unit render operations. The processing tap will be provided with a bufferList on input
		where the mData pointers are NULL.

		When the output audio is stopped asynchronously, the processing tap will see the
		kMTAudioProcessingTapFlag_EndOfStream bit set on return from GetSourceAudio, and is responsible
		for propagating this bit from the callback when its processing has reached this point.

		A processing tap will NEVER see the same source data again, so, it should keep its own copy,
		if it needs to keep it for further reference past the duration of this call. It also cannot
		assume that the pointers to the source data that it retrieves will remain valid AFTER the
		processing tap has executed.

		Should the processing tap provide custom buffers in bufferListInOut, it should ensure that the
		data pointers remain valid until the tap is executed again.

	@param		tap
				The processing tap.
	@param		numberFrames
				The requested number of sample frames that should be rendered.
	@param		flags
				The flags passed at construction time are provided.
	@param		bufferListInOut
				The audio buffer list which will contain processed source data.
				On input, all fields except for the buffer pointers will be filled in,
				and can be passed directly to GetSourceAudio() if in-place processing is
				desired.
				On output, the bufferList should contain the processed audio buffers.
	@param		numberFramesOut
				The number of frames of audio data provided in the processed data. Can be 0.
	@param		bufferListOut
				The input bufferList filled in with the tap output.
	@param		flagsOut
				The start/end of stream flags should be set when appropriate (see Discussion, above).
*/
typedef void (*MTAudioProcessingTapProcessCallback)(
		MTAudioProcessingTapRef tap,
		CMItemCount numberFrames,
		MTAudioProcessingTapFlags flags,
		AudioBufferList *bufferListInOut,
		CMItemCount *numberFramesOut,
		MTAudioProcessingTapFlags *flagsOut);

enum {
	kMTAudioProcessingTapCallbacksVersion_0 = 0,
};

/*!
	@typedef	MTAudioProcessingTapCallbacks

	@field		version
				The version number of the structure passed in as a parameter to MTAudioProcessingTapCreate().
				Must be kMTAudioProcessingTapCallbacksVersion_0.
	@field		clientInfo
				Client data that will be passed to the init callback when it is invoked. Can be NULL.
	@field		init
				A callback to allow the client to initialize the tap processor. Can be NULL.
				This callback is called before MTAudioProcessingTapCreate() returns.
	@field		finalize
				A callback to allow the client to perform any necessary cleanup. Can be NULL.
				This callback will be called exactly once when the MTAudioProcessingTap object is finalized.
	@field		prepare
				A callback to allow the client to prepare the tap processor (allocate memory buffers, etc). Can be NULL.
				Note that the callback may be called multiple times.
	@field		unprepare
				A callback to allow the client to perform any necessary cleanup for which that is prepared. Can be NULL.
	@field		process
				A callback for processing the audio.
*/
typedef struct {
	int version;
	void *clientInfo;
	MTAudioProcessingTapInitCallback init;
	MTAudioProcessingTapFinalizeCallback finalize;
	MTAudioProcessingTapPrepareCallback prepare;
	MTAudioProcessingTapUnprepareCallback unprepare;
	MTAudioProcessingTapProcessCallback process;
} MTAudioProcessingTapCallbacks;

/*!
	@function	MTAudioProcessingTapCreate
	@abstract	Create a new processing tap.
	@discussion	This function creates a processing tap.
				The processing tap will then be used to process decoded data.
				The processing is performed on audio either before or after any effects or other
				processing (varispeed, etc) is applied by the audio queue.

	@param		allocator
				The allocator to use to allocate memory for the new tap. Pass NULL or kCFAllocatorDefault to use the current default allocator.
	@param		callbacks
				Callbacks struct.  MTAudioProcessingTap will make a copy of this struct.
	@param		flags
				Flags that are used to control aspects of the processing tap.
				Valid flags are:
				- kMTAudioProcessingTapCreationFlag_PreEffects:
					processing is done before any further effects are applied by the audio queue to the audio.
				- kMTAudioProcessingTapCreationFlag_PostEffects:
					processing is done after all processing is done, including that of other taps.
	@param		tapOut
				The processing tap object.

    @result     An OSStatus result code.
*/
MT_EXPORT OSStatus MTAudioProcessingTapCreate(
		CFAllocatorRef allocator,
		const MTAudioProcessingTapCallbacks *callbacks,
		MTAudioProcessingTapCreationFlags flags,
		MTAudioProcessingTapRef *tapOut) __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_6_0);

/*!
	@function	MTAudioProcessingTapGetStorage
	@abstract	Used by a processing tap to retrieve a custom storage pointer.

	@param		tap
				The processing tap.

	@result		The tapStorage returned by the init callback.
*/
MT_EXPORT void *MTAudioProcessingTapGetStorage(MTAudioProcessingTapRef tap) __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_6_0);

/*!
	@function	MTAudioProcessingTapGetSourceAudio
	@abstract	Used by a processing tap to retrieve source audio.
	@discussion	This function may only be called from the processing tap's callback.

	@param		tap
				The processing tap.
	@param		numberFrames
				The number of frames the processing tap requires for its processing.
	@param		bufferListInOut
				The audio buffer list which will contain the source data.
				On input, all fields except for the buffer pointers must be filled in.
				If the buffer pointers are NULL (recommended), non-NULL pointers will be
				returned and system owns the source buffers; these buffers are only applicable
				for the duration of the processing tap callback.
				If the buffer pointers are non-NULL, then they must be big enough to hold
				numberFrames, and the source data will be copied into these buffers.
	@param		flagsOut
				Flags to describe state about the input requested, e.g., discontinuity/complete. Can be NULL.
	@param		timeRangeOut
				The asset time range corresponding to the provided source audio frames. Can be NULL.
	@param		numberFramesOut
				The number of source frames that have been provided. Can be NULL.
				This can be less than the number of requested frames specified in numberFrames.

	@result		An OSStatus result code.
*/
MT_EXPORT OSStatus MTAudioProcessingTapGetSourceAudio(
		MTAudioProcessingTapRef tap,
		CMItemCount numberFrames,
		AudioBufferList *bufferListInOut,
		MTAudioProcessingTapFlags *flagsOut,
		CMTimeRange *timeRangeOut,
		CMItemCount *numberFramesOut) __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_6_0);

#pragma pack(pop)

#if defined(__cplusplus)
}
#endif

#endif // MTAUDIOPROCESSINGTAP_H

