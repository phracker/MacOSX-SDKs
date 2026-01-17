/*
     File:       AudioToolbox/AudioConverter.h

     Contains:   API for translating between audio data formats.

     Version:    Technology: Mac OS X
                 Release:    Mac OS X

     Copyright:  (c) 1985-2001 by Apple Computer, Inc., all rights reserved.

     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:

                     http://developer.apple.com/bugreporter/

*/
#if !defined(__AudioConverter_h__)
#define __AudioConverter_h__

//==================================================================================================

/*!
	@header		AudioConverter.h
	
	@abstract	Functions for performing audio format conversions.
	
	@discussion
				AudioConverters convert between various linear PCM and compressed
				audio formats. Supported transformations include:
				
				<ul>
				<li>PCM float/integer/bit depth conversions</li>
				<li>PCM sample rate conversion</li>
				<li>PCM interleaving and deinterleaving</li>
				<li>encoding PCM to compressed formats</li>
				<li>decoding compressed formats to PCM</li>
				</ul>
				
				A single AudioConverter may perform more than one
				of the above transformations.
*/

//=============================================================================
//	Includes
//=============================================================================

#include <AvailabilityMacros.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <CoreAudio/CoreAudioTypes.h>
#else
	#include <CoreAudioTypes.h>
#endif

#if defined(__cplusplus)
extern "C"
{
#endif

//=============================================================================
//	Theory of Operation
//=============================================================================

//=============================================================================
//	Types specific to the Audio Converter API
//=============================================================================

/*!
	@typedef	AudioConverterRef
	@abstract	A reference to an AudioConverter object.
*/
typedef struct OpaqueAudioConverter *	AudioConverterRef;

typedef UInt32							AudioConverterPropertyID;

//=============================================================================
//	Standard Properties
//=============================================================================

/*!
	@enum		AudioConverterPropertyID
	@abstract	The properties of an AudioConverter, accessible via AudioConverterGetProperty()
				and AudioConverterSetProperty().
	
	@constant	kAudioConverterPropertyMinimumInputBufferSize
					a UInt32 that indicates the size in bytes of the smallest buffer of input
					data that can be supplied via the AudioConverterInputProc or as the input to
					AudioConverterConvertBuffer
	@constant	kAudioConverterPropertyMinimumOutputBufferSize
					a UInt32 that indicates the size in bytes of the smallest buffer of output
					data that can be supplied to AudioConverterFillBuffer or as the output to
					AudioConverterConvertBuffer
	@constant	kAudioConverterPropertyMaximumInputBufferSize
					a UInt32 that indicates the size in bytes of the largest buffer of input
					data that will be requested from the AudioConverterInputProc. This is mostly
					useful for variable bit rate compressed data. This will be equal to
					0xFFFFFFFF if the maximum value depends on what is requested from the
					output, which is usually the case for constant bit rate formats.
	@constant	kAudioConverterPropertyMaximumInputPacketSize
					a UInt32 that indicates the size in bytes of the largest single packet of
					data in the input format. This is mostly useful for variable bit rate
					compressed data (decoders).
	@constant	kAudioConverterPropertyMaximumOutputPacketSize
					a UInt32 that indicates the size in bytes of the largest single packet of
					data in the output format. This is mostly useful for variable bit rate
					compressed data (encoders).
	@constant	kAudioConverterPropertyCalculateInputBufferSize
					a UInt32 that on input holds a size in bytes that is desired for the output
					data. On output, it will hold the size in bytes of the input buffer required
					to generate that much output data. Note that some converters cannot do this
					calculation.
	@constant	kAudioConverterPropertyCalculateOutputBufferSize
					a UInt32 that on input holds a size in bytes that is desired for the input
					data. On output, it will hold the size in bytes of the output buffer
					required to hold the output data that will be generated. Note that some
					converters cannot do this calculation.
	@constant	kAudioConverterPropertyInputCodecParameters
					The value of this property varies from format to format and is considered
					private to the format. It is treated as a buffer of untyped data.
	@constant	kAudioConverterPropertyOutputCodecParameters
					The value of this property varies from format to format and is considered
					private to the format. It is treated as a buffer of untyped data.
	@constant	kAudioConverterSampleRateConverterAlgorithm
					DEPRECATED: please use kAudioConverterSampleRateConverterQuality instead

					An OSType that specifies the sample rate converter to use (as defined in
					AudioUnit/AudioUnitProperties.h -- for now only Apple SRC's can be used)
	@constant	kAudioConverterSampleRateConverterQuality
					A UInt32 that specifies rendering quality of the sample rate converter (see
					enum constants below)
	@constant	kAudioConverterCodecQuality
					A UInt32 that specifies rendering quality of a codec (see enum constants
					below)
	@constant	kAudioConverterPrimeMethod
					a UInt32 specifying priming method (usually for sample-rate converter) see
					explanation for struct AudioConverterPrimeInfo below along with enum
					constants
	@constant	kAudioConverterPrimeInfo
					A pointer to AudioConverterPrimeInfo (see explanation for struct
					AudioConverterPrimeInfo below)
	@constant	kAudioConverterChannelMap
					An array of SInt32's.  The size of the array is the number of output
					channels, and each element specifies which input channel's data is routed to
					that output channel (using a 0-based index of the input channels), or -1 if
					no input channel is to be routed to that output channel.  The default
					behavior is as follows. I = number of input channels, O = number of output
					channels. When I > O, the first O inputs are routed to the first O outputs,
					and the remaining puts discarded.  When O > I, the first I inputs are routed
					to the first O outputs, and the remaining outputs are zeroed.
					
					A simple example for splitting mono input to stereo output (instead of routing
					the input to only the first output channel):
					
<pre>
   // this should be as large as the number of output channels:
  SInt32 channelMap[2] = { 0, 0 };
  AudioConverterSetProperty(theConverter, kAudioConverterChannelMap, 
    sizeof(channelMap), channelMap);
</pre>
	@constant	kAudioConverterDecompressionMagicCookie
					A void * pointing to memory set up by the caller. Required by some formats
					in order to decompress the input data.
	@constant	kAudioConverterCompressionMagicCookie
					A void * pointing to memory set up by the caller. Returned by the converter
					so that it may be stored along with the output data. It can then be passed
					back to the converter for decompression at a later time.
	@constant	kAudioConverterEncodeBitRate
					A UInt32 containing the number of bits per second to aim for when encoding
					data. This property is only relevant to encoders.
	@constant	kAudioConverterEncodeAdjustableSampleRate
					For encoders where the AudioConverter was created with an output sample rate
					of zero, and the codec can do rate conversion on its input, this provides a
					way to set the output sample rate. The property value is a Float64.
	@constant	kAudioConverterInputChannelLayout
					The property value is an AudioChannelLayout.
	@constant	kAudioConverterOutputChannelLayout
					The property value is an AudioChannelLayout.
	@constant	kAudioConverterApplicableEncodeBitRates
					The property value is an array of AudioValueRange describing applicable bit
					rates based on current settings.
	@constant	kAudioConverterAvailableEncodeBitRates
					The property value is an array of AudioValueRange describing available bit
					rates based on the input format. You can get all available bit rates from
					the AudioFormat API.
	@constant	kAudioConverterApplicableEncodeSampleRates
					The property value is an array of AudioValueRange describing applicable
					sample rates based on current settings.
	@constant	kAudioConverterAvailableEncodeSampleRates
					The property value is an array of AudioValueRange describing available
					sample rates based on the input format. You can get all available sample
					rates from the AudioFormat API.
	@constant	kAudioConverterAvailableEncodeChannelLayoutTags
					The property value is an array of AudioChannelLayoutTags for the format and
					number of channels specified in the input format going to the encoder.
	@constant	kAudioConverterCurrentOutputStreamDescription
					Returns the current completely specified output AudioStreamBasicDescription.
					For example when encoding to AAC, your original output stream description
					will not have been completely filled out.
	@constant	kAudioConverterCurrentInputStreamDescription
					Returns the current completely specified input AudioStreamBasicDescription.
	@constant	kAudioConverterPropertySettings
					Returns the a CFArray of property settings for converters.
	@constant	kAudioConverterPropertyBitDepthHint
					A UInt32 of the source bit depth to preserve. This is a hint to some
					encoders like lossless about how many bits to preserve in the input. The
					converter usually tries to preserve as many as possible, but a lossless
					encoder will do poorly if more bits are supplied than are desired in the
					output.
*/
enum // typedef UInt32 AudioConverterPropertyID
{
	kAudioConverterPropertyMinimumInputBufferSize		= 'mibs',
	kAudioConverterPropertyMinimumOutputBufferSize		= 'mobs',
	kAudioConverterPropertyMaximumInputBufferSize		= 'xibs',
	kAudioConverterPropertyMaximumInputPacketSize		= 'xips',
	kAudioConverterPropertyMaximumOutputPacketSize		= 'xops',
	kAudioConverterPropertyCalculateInputBufferSize		= 'cibs',
	kAudioConverterPropertyCalculateOutputBufferSize	= 'cobs',
	kAudioConverterPropertyInputCodecParameters			= 'icdp',
	kAudioConverterPropertyOutputCodecParameters		= 'ocdp',
	kAudioConverterSampleRateConverterAlgorithm			= 'srci',
	kAudioConverterSampleRateConverterQuality			= 'srcq',
	kAudioConverterCodecQuality							= 'cdqu',
	kAudioConverterPrimeMethod							= 'prmm',
	kAudioConverterPrimeInfo							= 'prim',
	kAudioConverterChannelMap							= 'chmp',
	kAudioConverterDecompressionMagicCookie				= 'dmgc',
	kAudioConverterCompressionMagicCookie				= 'cmgc',
	kAudioConverterEncodeBitRate						= 'brat',
	kAudioConverterEncodeAdjustableSampleRate			= 'ajsr',
	kAudioConverterInputChannelLayout					= 'icl ',
	kAudioConverterOutputChannelLayout					= 'ocl ',
	kAudioConverterApplicableEncodeBitRates				= 'aebr',
	kAudioConverterAvailableEncodeBitRates				= 'vebr',
	kAudioConverterApplicableEncodeSampleRates			= 'aesr',
	kAudioConverterAvailableEncodeSampleRates			= 'vesr',
	kAudioConverterAvailableEncodeChannelLayoutTags		= 'aecl',
	kAudioConverterCurrentOutputStreamDescription		= 'acod',
	kAudioConverterCurrentInputStreamDescription		= 'acid',
	kAudioConverterPropertySettings						= 'acps',
	kAudioConverterPropertyBitDepthHint					= 'acbd'
};

/*!
	@enum		Quality constants

	@abstract	Constants to be used with kAudioConverterSampleRateConverterQuality.

	@constant	kAudioConverterQuality_Max			maximum quality
	@constant	kAudioConverterQuality_High			high quality
	@constant	kAudioConverterQuality_Medium		medium quality
	@constant	kAudioConverterQuality_Low			low quality
	@constant	kAudioConverterQuality_Min			minimum quality
*/
enum
{
	kAudioConverterQuality_Max								= 0x7F,
	kAudioConverterQuality_High								= 0x60,
	kAudioConverterQuality_Medium							= 0x40,
	kAudioConverterQuality_Low								= 0x20,
	kAudioConverterQuality_Min								= 0
};


/*!
	@enum		Prime method constants

	@abstract	Constants to be used with kAudioConverterPrimeMethod.
	
	@constant	kConverterPrimeMethod_Pre
					Primes with leading + trailing input frames.
	@constant	kConverterPrimeMethod_Normal
					Only primes with trailing (zero latency). Leading frames are assumed to be
					silence.
	@constant	kConverterPrimeMethod_None
					Acts in "latency" mode. Both leading and trailing frames assumed to be
					silence.
*/
enum
{
	kConverterPrimeMethod_Pre 		= 0,
	kConverterPrimeMethod_Normal 	= 1,
	kConverterPrimeMethod_None 		= 2
};

/*!
	@struct		AudioConverterPrimeInfo
	@abstract	Specifies priming information.
	
	@field		leadingFrames
		Specifies the number of leading (previous) input frames, relative to the normal/desired
		start input frame, required by the converter to perform a high quality conversion. If
		using kConverterPrimeMethod_Pre, the client should "pre-seek" the input stream provided
		through the input proc by leadingFrames. If no frames are available previous to the
		desired input start frame (because, for example, the desired start frame is at the very
		beginning of available audio), then provide "leadingFrames" worth of initial zero frames
		in the input proc.  Do not "pre-seek" in the default case of
		kConverterPrimeMethod_Normal or when using kConverterPrimeMethod_None.

	@field		trailingFrames
		Specifies the number of trailing input frames (past the normal/expected end input frame)
		required by the converter to perform a high quality conversion.  The client should be
		prepared to provide this number of additional input frames except when using
		kConverterPrimeMethod_None. If no more frames of input are available in the input stream
		(because, for example, the desired end frame is at the end of an audio file), then zero
		(silent) trailing frames will be synthesized for the client.
			
	@discussion
		When using AudioConverterFillBuffer() (either a single call or a series of calls), some
		conversions, particularly involving sample-rate conversion, ideally require a certain
		number of input frames previous to the normal start input frame and beyond the end of
		the last expected input frame in order to yield high-quality results.
		
		These are expressed in the leadingFrames and trailingFrames members of the structure.
		
		The very first call to AudioConverterFillBuffer(), or first call after
		AudioConverterReset(), will request additional input frames beyond those normally
		expected in the input proc callback to fulfill this first AudioConverterFillBuffer()
		request. The number of additional frames requested, depending on the prime method, will
		be approximately:

		<pre>
            kConverterPrimeMethod_Pre       leadingFrames + trailingFrames
            kConverterPrimeMethod_Normal    trailingFrames
            kConverterPrimeMethod_None      0
		</pre>

		Thus, in effect, the first input proc callback(s) may provide not only the leading
		frames, but also may "read ahead" by an additional number of trailing frames depending
		on the prime method.

		kConverterPrimeMethod_None is useful in a real-time application processing live input,
		in which case trailingFrames (relative to input sample rate) of through latency will be
		seen at the beginning of the output of the AudioConverter.  In other real-time
		applications such as DAW systems, it may be possible to provide these initial extra
		audio frames since they are stored on disk or in memory somewhere and
		kConverterPrimeMethod_Pre may be preferable.  The default method is
		kConverterPrimeMethod_Normal, which requires no pre-seeking of the input stream and
		generates no latency at the output.
*/
struct AudioConverterPrimeInfo {
	UInt32		leadingFrames;
	UInt32		trailingFrames;
};
typedef struct AudioConverterPrimeInfo AudioConverterPrimeInfo;

//=============================================================================
//	Errors
//=============================================================================

enum
{
	kAudioConverterErr_FormatNotSupported		= 'fmt?',
	kAudioConverterErr_OperationNotSupported	= 0x6F703F3F, // 'op??', integer used because of trigraph
	kAudioConverterErr_PropertyNotSupported		= 'prop',
	kAudioConverterErr_InvalidInputSize			= 'insz',
	kAudioConverterErr_InvalidOutputSize		= 'otsz',
		// e.g. byte size is not a multiple of the frame size
	kAudioConverterErr_UnspecifiedError			= 'what',
	kAudioConverterErr_BadPropertySizeError		= '!siz',
	kAudioConverterErr_RequiresPacketDescriptionsError = '!pkd',
	kAudioConverterErr_InputSampleRateOutOfRange	= '!isr',
	kAudioConverterErr_OutputSampleRateOutOfRange	= '!osr'
};

//=============================================================================
//	Routines
//=============================================================================

//-----------------------------------------------------------------------------
/*!
	@function	AudioConverterNew
	@abstract	Create a new AudioConverter.

	@param		inSourceFormat
					The format of the source audio to be converted.
	@param		inDestinationFormat
					The destination format to which the audio is to be converter.
	@param		outAudioConverter
					On successful return, points to a new AudioConverter instance.
	@result		An OSStatus result code.
	
	@discussion
				For a pair of linear PCM formats, the following conversions
				are supported:
				
				<ul>
				<li>addition and removal of channels, when the stream descriptions'
				mChannelsPerFrame does not match. Channels may also be reordered and removed
				using the kAudioConverterChannelMap property.</li>
				<li>sample rate conversion</li>
				<li>interleaving/deinterleaving, when the stream descriptions' (mFormatFlags &
				kAudioFormatFlagIsNonInterleaved) does not match.</li>
				<li>conversion between any pair of the following formats:</li>
					<ul>
					<li>8 bit integer, signed or unsigned</li>
					<li>16, 24, or 32-bit integer, big- or little-endian. Other integral
					bit depths, if high-aligned and non-packed, are also supported</li>
					<li>32 and 64-bit float, big- or little-endian.</li>
					</ul>
				</ul>
				
				Also, encoding and decoding between linear PCM and compressed formats is
				supported. Functions in AudioToolbox/AudioFormat.h return information about the
				supported formats. When using a codec, you can use any supported PCM format (as
				above); the converter will perform any necessary additional conversion between
				your PCM format and the one created or consumed by the codec.
*/
extern OSStatus
AudioConverterNew(		const AudioStreamBasicDescription*	inSourceFormat,
						const AudioStreamBasicDescription*	inDestinationFormat,
						AudioConverterRef*					outAudioConverter)	AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


//-----------------------------------------------------------------------------
/*!
	@function	AudioConverterNewSpecific
	@abstract	Create a new AudioConverter using specific codecs.

	@param		inSourceFormat
					The format of the source audio to be converted.
	@param		inDestinationFormat
					The destination format to which the audio is to be converter.
	@param		inNumberClassDescriptions
					The number of class descriptions.
	@param		inClassDescriptions
					AudioClassDescriptions specifiying the codec to instantiate.
	@param		outAudioConverter
					On successful return, points to a new AudioConverter instance.
	@result		An OSStatus result code.
	
	@discussion
				This function is identical to AudioConverterNew(), except that the client may
				explicitly choose which codec to instantiate if there is more than one choice.
*/
extern OSStatus
AudioConverterNewSpecific(	const AudioStreamBasicDescription*	inSourceFormat,
							const AudioStreamBasicDescription*	inDestinationFormat,
							UInt32								inNumberClassDescriptions,
							AudioClassDescription*				inClassDescriptions,
							AudioConverterRef*					outAudioConverter)
																				AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

//-----------------------------------------------------------------------------
/*!
	@function	AudioConverterDispose
	@abstract	Destroy an AudioConverter.

	@param		inAudioConverter
					The AudioConverter to dispose.
	@result		An OSStatus result code.
*/
extern OSStatus
AudioConverterDispose(	AudioConverterRef	inAudioConverter)					AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

//-----------------------------------------------------------------------------
/*!
	@function	AudioConverterReset
	@abstract	Reset an AudioConverter

	@param		inAudioConverter
					The AudioConverter to reset.
	@result		An OSStatus result code.
	
	@discussion
				Should be called whenever there is a discontinuity in the source audio stream
				being provided to the converter. This will flush any internal buffers in the
				converter.
*/

extern OSStatus
AudioConverterReset(	AudioConverterRef	inAudioConverter)					AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

//-----------------------------------------------------------------------------
/*!
	@function	AudioConverterGetPropertyInfo
	@abstract	Returns information about an AudioConverter property.

	@param		inAudioConverter
					The AudioConverter to query.
	@param		inPropertyID
					The property to query.
	@param		outSize
					If non-null, on exit, the size of the property value in bytes.
	@param		outWritable
					If non-null, on exit, indicates whether the property value is writable.
	@result		An OSStatus result code.
*/
extern OSStatus
AudioConverterGetPropertyInfo(	AudioConverterRef			inAudioConverter,
								AudioConverterPropertyID	inPropertyID,
								UInt32*						outSize,
								Boolean*					outWritable)		AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

//-----------------------------------------------------------------------------
/*!
	@function	AudioConverterGetProperty
	@abstract	Returns an AudioConverter property value.

	@param		inAudioConverter
					The AudioConverter to query.
	@param		inPropertyID
					The property to fetch.
	@param		ioPropertyDataSize
					On entry, the size of the memory pointed to by outPropertyData. On 
					successful exit, the size of the property value.
	@param		outPropertyData
					On exit, the property value.
	@result		An OSStatus result code.
*/
extern OSStatus
AudioConverterGetProperty(	AudioConverterRef			inAudioConverter,
							AudioConverterPropertyID	inPropertyID,
							UInt32*						ioPropertyDataSize,
							void*						outPropertyData)		AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

//-----------------------------------------------------------------------------
/*!
	@function	AudioConverterSetProperty
	@abstract	Sets an AudioConverter property value.

	@param		inAudioConverter
					The AudioConverter to modify.
	@param		inPropertyID
					The property to set.
	@param		inPropertyDataSize
					The size in bytes of the property value.
	@param		inPropertyData
					Points to the new property value.
	@result		An OSStatus result code.
*/
extern OSStatus
AudioConverterSetProperty(	AudioConverterRef			inAudioConverter,
							AudioConverterPropertyID	inPropertyID,
							UInt32						inPropertyDataSize,
							const void*					inPropertyData)			AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


//-----------------------------------------------------------------------------
/*!
	@typedef	AudioConverterInputDataProc
	@abstract	Callback function for supplying input data to AudioConverterFillBuffer.

	@param		inAudioConverter
					The AudioConverter requesting input.
	@param		ioDataSize
					On entry, the minimum number of bytes of audio data the converter
					would like in order to fulfill its current FillBuffer request.
					On exit, the number of bytes of audio data actually being provided
					for input, or 0 if there is no more input.
	@param		outData
					On exit, *outData should point to the audio data being provided
					for input.
	@param		inUserData
					The inInputDataProcUserData parameter passed to AudioConverterFillBuffer().
	@result		An OSStatus result code.
	
	@discussion
				This callback function supplies input to AudioConverterFillBuffer.
				
				The AudioConverter requests a minimum amount of data (*ioDataSize). The callback
				may return any amount of data. If it is less than than the minimum, the callback
				will simply be called again in the near future.

				The callback supplies a pointer to a buffer of audio data. The callback is
				responsible for not freeing or altering this buffer until it is called again.
				
				If the callback returns an error, it must return zero bytes of data.
				AudioConverterFillBuffer will stop producing output and return whatever output
				has already been produced to its caller, along with the error code. This
				mechanism can be used when an input proc has temporarily run out of data, but
				has not yet reached end of stream.
*/
typedef OSStatus
(*AudioConverterInputDataProc)(	AudioConverterRef			inAudioConverter,
								UInt32*						ioDataSize,
								void**						outData,
								void*						inUserData);

//-----------------------------------------------------------------------------
/*!
	@function	AudioConverterFillBuffer
	@abstract	Converts data supplied by an input callback function.

	@param		inAudioConverter
					The AudioConverter to use.
	@param		inInputDataProc
					A callback function which supplies the input data.
	@param		inInputDataProcUserData
					A value for the use of the callback function.
	@param		ioOutputDataSize
					On entry, the size of the buffer pointed to by outOutputData.
					On exit, the number of bytes written to outOutputData
	@param		outOutputData
					The buffer into which the converted data is written.
	@result		An OSStatus result code.
	
	@discussion
				Produces a buffer of output data from an AudioConverter. The supplied input
				callback function is called whenever necessary.
				
				<b>NOTE:</b> AudioConverterFillBuffer is limited to simpler conversions
				that do not involve multiple deinterleaved buffers or packetized
				formats. Use AudioConverterFillComplexBuffer for those cases.
*/
extern OSStatus
AudioConverterFillBuffer(	AudioConverterRef				inAudioConverter,
							AudioConverterInputDataProc		inInputDataProc,
							void*							inInputDataProcUserData,
							UInt32*							ioOutputDataSize,
							void*							outOutputData)		AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

//-----------------------------------------------------------------------------
/*!
	@function	AudioConverterConvertBuffer
	@abstract	Converts data from an input buffer to an output buffer.

	@param		inAudioConverter
					The AudioConverter to use.
	@param		inInputDataSize
					The size of the buffer inInputData.
	@param		inInputData
					The input audio data buffer.
	@param		ioOutputDataSize
					On entry, the size of the buffer outOutputData. On exit, the number of bytes
					written to outOutputData.
	@param		outOutputData
					The output data buffer.
	@result
				Produces a buffer of output data from an AudioConverter, using the supplied
				input buffer. 
				
				<b>WARNING:</b> this function will fail for any conversion where there is a
				variable relationship between the input and output data buffer sizes. This
				includes sample rate conversions and most compressed formats. In these cases,
				use AudioConverterFillBuffer. Generally this function is only appropriate for
				PCM-to-PCM conversions where there is no sample rate conversion.
*/
extern OSStatus
AudioConverterConvertBuffer(	AudioConverterRef				inAudioConverter,
								UInt32							inInputDataSize,
								const void*						inInputData,
								UInt32*							ioOutputDataSize,
								void*							outOutputData)	AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

//-----------------------------------------------------------------------------
/*!
	@typedef	AudioConverterComplexInputDataProc
	@abstract	Callback function for supplying input data to AudioConverterFillComplexBuffer.

	@param		inAudioConverter
					The AudioConverter requesting input.
	@param		ioNumberDataPackets
					On entry, the minimum number of packets of input audio data the converter
					would like in order to fulfill its current FillBuffer request. On exit, the
					number of packets of audio data actually being provided for input, or 0 if
					there is no more input.
	@param		ioData
					On exit, the members of ioData should be set to point to the audio data
					being provided for input.
	@param		outDataPacketDescription
					If non-null, on exit, the callback is expected to fill this in with
					an AudioStreamPacketDescription for each packet of input data being provided.
	@param		inUserData
					The inInputDataProcUserData parameter passed to AudioConverterFillBuffer().
	@result		An OSStatus result code.
	
	@discussion
				This callback function supplies input to AudioConverterFillComplexBuffer.
				
				The AudioConverter requests a minimum number of packets (*ioNumberDataPackets).
				The callback may return one or more packets. If this is less than than the minimum,
				the callback will simply be called again in the near future.

				The callback manipulates the members of ioData to point to one or more buffers
				of audio data (multiple buffers are used with non-interleaved PCM data). The
				callback is responsible for not freeing or altering this buffer until it is
				called again.

				If the callback returns an error, it must return zero packets of data.
				AudioConverterFillComplexBuffer will stop producing output and return whatever
				output has already been produced to its caller, along with the error code. This
				mechanism can be used when an input proc has temporarily run out of data, but
				has not yet reached end of stream.
*/
typedef OSStatus
(*AudioConverterComplexInputDataProc)(	AudioConverterRef				inAudioConverter,
										UInt32*							ioNumberDataPackets,
										AudioBufferList*				ioData,
										AudioStreamPacketDescription**	outDataPacketDescription,
										void*							inUserData);

//-----------------------------------------------------------------------------
/*!
	@function	AudioConverterFillComplexBuffer
	@abstract	Converts data supplied by an input callback function, supporting non-interleaved
				and packetized formats.

	@param		inAudioConverter
					The AudioConverter to use.
	@param		inInputDataProc
					A callback function which supplies the input data.
	@param		inInputDataProcUserData
					A value for the use of the callback function.
	@param		ioOutputDataPacketSize
					On entry, the capacity of outOutputData expressed in packets in the
					converter's output format. On exit, the number of packets of converted
					data that were written to outOutputData.
	@param		outOutputData
					The converted output data is written to this buffer.
	@param		outPacketDescription
					If non-null, and the converter's output uses packet descriptions, then
					packet descriptions are written to this array. It must point to a memory
					block capable of holding *ioOutputDataPacketSize packet descriptions.
					(See AudioFormat.h for ways to determine whether an audio format
					uses packet descriptions).
	@result		An OSStatus result code.

	@discussion
				Produces a buffer list of output data from an AudioConverter. The supplied input
				callback function is called whenever necessary.
*/
extern OSStatus
AudioConverterFillComplexBuffer(	AudioConverterRef					inAudioConverter,
									AudioConverterComplexInputDataProc	inInputDataProc,
									void*								inInputDataProcUserData,
									UInt32*								ioOutputDataPacketSize,
									AudioBufferList*					outOutputData,
									AudioStreamPacketDescription*		outPacketDescription)
																				AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

#if defined(__cplusplus)
}
#endif

#endif
