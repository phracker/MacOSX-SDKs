/*
     File:       AudioToolbox/ExtendedAudioFile.h

     Contains:   API for reading/writing AudioFiles via an AudioConverter

     Copyright:  (c) 1985-2008 by Apple, Inc., all rights reserved.

     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:

                        http://developer.apple.com/bugreporter/

*/
#ifndef __ExtendedAudioFile_h__
#define __ExtendedAudioFile_h__

#include <Availability.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <CoreFoundation/CoreFoundation.h>
	#include <AudioToolbox/AudioFile.h>
#else
	#include <CoreFoundation.h>
	#include <AudioFile.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*!
	@header		ExtendedAudioFile.h
	
	@abstract	ExtendedAudioFile APIs.
	
	The ExtendedAudioFile provides high-level audio file access, building
	on top of the AudioFile and AudioConverter API sets. It provides a single
	unified interface to reading and writing both encoded and unencoded files.
*/

//==================================================================================================
//	Types

/*!
	@typedef	ExtAudioFileRef
	@abstract   An extended audio file object.
*/
typedef struct OpaqueExtAudioFile *	ExtAudioFileRef;


//==================================================================================================
//	Properties

/*!
    @enum           ExtAudioFilePropertyID
    @constant       kExtAudioFileProperty_FileDataFormat
                        An AudioStreamBasicDescription. Represents the file's actual
						data format. Read-only.
	@constant		kExtAudioFileProperty_FileChannelLayout
						An AudioChannelLayout.

						If writing: the channel layout is written to the file, if the format
						supports the layout. If the format does not support the layout, the channel
						layout is still interpreted as the destination layout when performing
						conversion from the client channel layout, if any.

						If reading: the specified layout overrides the one read from the file, if
						any.

						When setting this, it must be set before the client format or channel
						layout.
	@constant		kExtAudioFileProperty_ClientDataFormat
						An AudioStreamBasicDescription.

						The format must be linear PCM (kAudioFormatLinearPCM).

						You must set this in order to encode or decode a non-PCM file data format.
						You may set this on PCM files to specify the data format used in your calls
						to read/write.
	@constant		kExtAudioFileProperty_ClientChannelLayout
						An AudioChannelLayout. Specifies the channel layout of the
						AudioBufferList's passed to ExtAudioFileRead() and
						ExtAudioFileWrite(). The layout may be different from the file's
						channel layout, in which the ExtAudioFileRef's underlying AudioConverter
						performs the remapping. This must be set after ClientDataFormat, and the
						number of channels in the layout must match.
	@constant		kExtAudioFileProperty_CodecManufacturer
						A UInt32 specifying the manufacturer of the codec to be used. This must be 
						specified before setting kExtAudioFileProperty_ClientDataFormat, which
						triggers the creation of the codec. This can be used on iOS
						to choose between a hardware or software encoder, by specifying 
						kAppleHardwareAudioCodecManufacturer or kAppleSoftwareAudioCodecManufacturer.
						
						Available starting on Mac OS X version 10.7 and iOS version 4.0.
	@constant		kExtAudioFileProperty_AudioConverter
						AudioConverterRef. The underlying AudioConverterRef, if any. Read-only.
						
						N.B. If you alter any properties of the AudioConverterRef, for example,
						an encoder's bit rate, you must set the kExtAudioFileProperty_ConverterConfig
						property on the ExtAudioFileRef afterwards. A NULL configuration is 
						sufficient. This will ensure that the output file's data format is consistent
						with the format being produced by the converter.
						
						<pre>
							CFArrayRef config = NULL;
							err = ExtAudioFileSetProperty(myExtAF, kExtAudioFileProperty_ConverterConfig, 
							  sizeof(config), &config);
						</pre>
						
	@constant		kExtAudioFileProperty_AudioFile
						The underlying AudioFileID. Read-only.
	@constant		kExtAudioFileProperty_FileMaxPacketSize
						UInt32 representing the file data format's maximum packet size in bytes.
						Read-only.
	@constant		kExtAudioFileProperty_ClientMaxPacketSize
						UInt32 representing the client data format's maximum packet size in bytes.
						Read-only.
	@constant		kExtAudioFileProperty_FileLengthFrames
						SInt64 representing the file's length in sample frames. Read-only on 
						non-PCM formats; writable for files in PCM formats.
	@constant		kExtAudioFileProperty_ConverterConfig
						CFArrayRef representing the underlying AudioConverter's configuration, as
						specified by kAudioConverterPropertySettings.
						
						This may be NULL to force resynchronization of the converter's output format
						with the file's data format.
	@constant		kExtAudioFileProperty_IOBufferSizeBytes
						UInt32 representing the size of the buffer through which the converter
						reads/writes the audio file (when there is an AudioConverter).
	@constant		kExtAudioFileProperty_IOBuffer
						void *. This is the memory buffer which the ExtAudioFileRef will use for
						disk I/O when there is a conversion between the client and file data
						formats. A client may be able to share buffers between multiple
						ExtAudioFileRef instances, in which case, it can set this property to point
						to its own buffer. After setting this property, the client must
						subsequently set the kExtAudioFileProperty_IOBufferSizeBytes property. Note
						that a pointer to a pointer should be passed to ExtAudioFileSetProperty.
	@constant		kExtAudioFileProperty_PacketTable
						AudioFilePacketTableInfo
						This can be used to both override the priming and remainder information in an audio file and
						to retrieve the current priming and remainder frames information for a given ExtAudioFile object. 
						If the underlying file type does not provide packet table info, the Get call will return an error.
						
						If you set this, then you can override the setting for these values in the file to ones that you want to use.
						When setting this, you can use a value of -1 for either the priming or remainder frames to use the value that
						is currently stored in the file. If you set this to a non-negative number (or zero) then that value will override
						whatever value is stored in the file that you are reading.
						Retrieving the value of the property will always retrieve the value the ExtAudioFile object is using (whether this
						is derived from the file, or from your override).
						If you want to determine what the value is in the file, you should use the AudioFile property:
						kAudioFilePropertyPacketTableInfo
						
						When the property is set, only the remaining and priming values are used. You should set the mNumberValidFrames to zero.
						
						For example, a file encoded using AAC may have 2112 samples of priming at the start of the file
						and a remainder of 823 samples at the end. When ExtAudioFile returns decoded samples to you,
						it will trim out the <priming num samples> at the start of the file, and the <remainder num samples> at the end.
						It will get these numbers initially from the file. A common use case for overriding this would be to set the priming
						and remainder samples to 0, so in this example you would retrieve an additional 2112 samples of silence from the start of the file
						and 823 samples of silence at the end of the file (silence, because the encoders use silence to pad out these priming and remainder samples)
*/
enum { // ExtAudioFilePropertyID
	kExtAudioFileProperty_FileDataFormat		= 'ffmt',   // AudioStreamBasicDescription
	kExtAudioFileProperty_FileChannelLayout		= 'fclo',   // AudioChannelLayout
	kExtAudioFileProperty_ClientDataFormat		= 'cfmt',   // AudioStreamBasicDescription
	kExtAudioFileProperty_ClientChannelLayout	= 'cclo',   // AudioChannelLayout
	kExtAudioFileProperty_CodecManufacturer		= 'cman',	// UInt32
	
	// read-only:
	kExtAudioFileProperty_AudioConverter		= 'acnv',	// AudioConverterRef
	kExtAudioFileProperty_AudioFile				= 'afil',	// AudioFileID
	kExtAudioFileProperty_FileMaxPacketSize		= 'fmps',	// UInt32
	kExtAudioFileProperty_ClientMaxPacketSize	= 'cmps',	// UInt32
	kExtAudioFileProperty_FileLengthFrames		= '#frm',	// SInt64
	
	// writable:
	kExtAudioFileProperty_ConverterConfig		= 'accf',   // CFPropertyListRef
	kExtAudioFileProperty_IOBufferSizeBytes		= 'iobs',	// UInt32
	kExtAudioFileProperty_IOBuffer				= 'iobf',	// void *
	kExtAudioFileProperty_PacketTable			= 'xpti'	// AudioFilePacketTableInfo
};
typedef UInt32						ExtAudioFilePropertyID;

/*!
    @enum           ExtAudioFile errors
    @constant       kExtAudioFileError_CodecUnavailableInputConsumed
						iOS only. Returned when ExtAudioFileWrite was interrupted. You must stop calling
						ExtAudioFileWrite. If the underlying audio converter can resume after an
						interruption (see kAudioConverterPropertyCanResumeFromInterruption), you must
						wait for an EndInterruption notification from AudioSession, and call AudioSessionSetActive(true)
						before resuming. In this situation, the buffer you provided to ExtAudioFileWrite was successfully
						consumed and you may proceed to the next buffer.
    @constant       kExtAudioFileError_CodecUnavailableInputNotConsumed
						iOS only. Returned when ExtAudioFileWrite was interrupted. You must stop calling
						ExtAudioFileWrite. If the underlying audio converter can resume after an
						interruption (see kAudioConverterPropertyCanResumeFromInterruption), you must
						wait for an EndInterruption notification from AudioSession, and call AudioSessionSetActive(true)
						before resuming. In this situation, the buffer you provided to ExtAudioFileWrite was not
						successfully consumed and you must try to write it again.
*/
enum {
#if TARGET_OS_IPHONE
	kExtAudioFileError_CodecUnavailableInputConsumed    = -66559,
	kExtAudioFileError_CodecUnavailableInputNotConsumed = -66560,
#endif
	kExtAudioFileError_InvalidProperty			= -66561,
	kExtAudioFileError_InvalidPropertySize		= -66562,
	kExtAudioFileError_NonPCMClientFormat		= -66563,
	kExtAudioFileError_InvalidChannelMap		= -66564,	// number of channels doesn't match format
	kExtAudioFileError_InvalidOperationOrder	= -66565,
	kExtAudioFileError_InvalidDataFormat		= -66566,
	kExtAudioFileError_MaxPacketSizeUnknown		= -66567,
	kExtAudioFileError_InvalidSeek				= -66568,	// writing, or offset out of bounds
	kExtAudioFileError_AsyncWriteTooLarge		= -66569,
	kExtAudioFileError_AsyncWriteBufferOverflow	= -66570	// an async write could not be completed in time
};


//==================================================================================================
//	Creation/Destruction
/*!
    @functiongroup  Creation/Destruction
*/

/*!
	@function   ExtAudioFileOpenURL
	
	@abstract   Opens an audio file specified by a CFURLRef.
	@param		inURLRef
					The audio file to read.
	@param		outExtAudioFile
					On exit, a newly-allocated ExtAudioFileRef.
	@result		An OSStatus error code.

	@discussion
				Allocates a new ExtAudioFileRef, for reading an existing audio file.
*/
extern OSStatus
ExtAudioFileOpenURL(		CFURLRef					inURL,
							ExtAudioFileRef *			outExtAudioFile)	__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_1);

/*!
	@function   ExtAudioFileWrapAudioFileID
	
	@abstract   Wrap an AudioFileID in an ExtAudioFileRef.
	@param		inFileID
					The AudioFileID to wrap.
	@param		inForWriting
					True if the AudioFileID is a new file opened for writing.
	@param		outExtAudioFile
					On exit, a newly-allocated ExtAudioFileRef.
	@result		An OSStatus error code.

	@discussion
				Allocates a new ExtAudioFileRef which wraps an existing AudioFileID. The
				client is responsible for keeping the AudioFileID open until the
				ExtAudioFileRef is disposed. Disposing the ExtAudioFileRef will not close
				the AudioFileID when this Wrap API call is used, so the client is also
				responsible for closing the AudioFileID when finished with it.
*/
extern OSStatus
ExtAudioFileWrapAudioFileID(AudioFileID					inFileID,
							Boolean						inForWriting,
							ExtAudioFileRef *			outExtAudioFile)	
																			__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_2_1);

/*!
	@function   ExtAudioFileCreateWithURL
	
	@abstract   Create a new audio file.
	@param		inURL
					The URL of the new audio file.
	@param		inFileType
					The type of file to create. This is a constant from AudioToolbox/AudioFile.h, e.g.
					kAudioFileAIFFType. Note that this is not an HFSTypeCode.
	@param		inStreamDesc
					The format of the audio data to be written to the file.
	@param		inChannelLayout
					The channel layout of the audio data. If non-null, this must be consistent
					with the number of channels specified by inStreamDesc.
	@param		inFlags
					The same flags as are used with AudioFileCreateWithURL
					Can use these to control whether an existing file is overwritten (or not).
	@param		outExtAudioFile
					On exit, a newly-allocated ExtAudioFileRef.
	@result		An OSStatus error code.

	@discussion
				Creates a new audio file.
				
				If the file to be created is in an encoded format, it is permissible for the
				sample rate in inStreamDesc to be 0, since in all cases, the file's encoding
				AudioConverter may produce audio at a different sample rate than the source. The
				file will be created with the audio format actually produced by the encoder.
*/
extern OSStatus
ExtAudioFileCreateWithURL(	CFURLRef							inURL,
							AudioFileTypeID						inFileType,
							const AudioStreamBasicDescription * inStreamDesc,
							const AudioChannelLayout *			inChannelLayout,
                    		UInt32								inFlags,
							ExtAudioFileRef *					outExtAudioFile)						
																			__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_1);
																			
#if !TARGET_OS_IPHONE && !CA_NO_CORE_SERVICES
/*!
	@function   ExtAudioFileOpen
	
	@abstract   Opens an audio file specified by an FSRef.
	@param		inFSRef
					The audio file to read.
	@param		outExtAudioFile
					On exit, a newly-allocated ExtAudioFileRef.
	@result		An OSStatus error code.

	@discussion
				Allocates a new ExtAudioFileRef, for reading an existing audio file.
				
				This function is deprecated as of Mac OS 10.6. ExtAudioFileOpenURL is preferred.
*/
extern OSStatus
ExtAudioFileOpen(			const struct FSRef *		inFSRef,
							ExtAudioFileRef *			outExtAudioFile)	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_4,__MAC_10_6,__IPHONE_NA,__IPHONE_NA);

/*!
	@function   ExtAudioFileCreateNew
	
	@abstract   Create a new audio file.
	@param		inParentDir
					The directory in which to create the new file.
	@param		inFileName
					The name of the new file.
	@param		inFileType
					The type of file to create. This is a constant from AudioToolbox/AudioFile.h, e.g.
					kAudioFileAIFFType. Note that this is not an HFSTypeCode.
	@param		inStreamDesc
					The format of the audio data to be written to the file.
	@param		inChannelLayout
					The channel layout of the audio data. If non-null, this must be consistent
					with the number of channels specified by inStreamDesc.
	@param		outExtAudioFile
					On exit, a newly-allocated ExtAudioFileRef.
	@result		An OSStatus error code.

	@discussion
				Creates a new audio file.
				
				If the file to be created is in an encoded format, it is permissible for the
				sample rate in inStreamDesc to be 0, since in all cases, the file's encoding
				AudioConverter may produce audio at a different sample rate than the source. The
				file will be created with the audio format actually produced by the encoder.

				This function is deprecated as of Mac OS 10.6. ExtAudioFileCreateWithURL is preferred.
*/
extern OSStatus
ExtAudioFileCreateNew(		const struct FSRef *				inParentDir,
							CFStringRef							inFileName,
							AudioFileTypeID						inFileType,
							const AudioStreamBasicDescription * inStreamDesc,
							const AudioChannelLayout *			inChannelLayout,
							ExtAudioFileRef *					outExtAudioFile)
																			__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_4,__MAC_10_6,__IPHONE_NA,__IPHONE_NA);
#endif

/*!
	@function   ExtAudioFileDispose
	
	@abstract   Close the file and dispose the object.
	@param		inExtAudioFile
					The extended audio file object.
	@result		An OSStatus error code.
	
	@discussion
				Closes the file and deletes the object.
*/
extern OSStatus
ExtAudioFileDispose(		ExtAudioFileRef				inExtAudioFile)		
																			__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_2_1);


//==================================================================================================
//	I/O
/*!
    @functiongroup  I/O
*/

/*!
	@function   ExtAudioFileRead
	
	@abstract   Perform a synchronous sequential read.
	
	@param		inExtAudioFile
					The extended audio file object.
	@param		ioNumberFrames
					On entry, ioNumberFrames is the number of frames to be read from the file.
					On exit, it is the number of frames actually read. A number of factors may
					cause a fewer number of frames to be read, including the supplied buffers
					not being large enough, and internal optimizations. If 0 frames are
					returned, however, this indicates that end-of-file was reached.
	@param		ioData
					Buffer(s) into which the audio data is read.
	@result		An OSStatus error code.

	@discussion
				If the file has a client data format, then the audio data from the file is
				translated from the file data format to the client format, via the
				ExtAudioFile's internal AudioConverter.
				
				(Note that the use of sequential reads/writes means that an ExtAudioFile must
				not be read on multiple threads; clients wishing to do this should use the
				lower-level AudioFile API set).
*/
extern OSStatus
ExtAudioFileRead(			ExtAudioFileRef			inExtAudioFile,
							UInt32 *				ioNumberFrames,
							AudioBufferList *		ioData)					
																			__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_2_1);

/*!
	@function   ExtAudioFileWrite
	
	@abstract   Perform a synchronous sequential write.

	@param		inExtAudioFile
					The extended audio file object.
	@param		inNumberFrames
					The number of frames to write.
	@param		ioData
					The buffer(s) from which audio data is written to the file.
	@result		An OSStatus error code.
	
	@discussion
				If the file has a client data format, then the audio data in ioData is
				translated from the client format to the file data format, via the
				ExtAudioFile's internal AudioConverter.
*/
extern OSStatus
ExtAudioFileWrite(			ExtAudioFileRef			inExtAudioFile,
							UInt32					inNumberFrames,
							const AudioBufferList * ioData)					
																			__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_2_1);

/*!
	@function   ExtAudioFileWriteAsync
	
	@abstract   Perform an asynchronous sequential write.
	
	@param		inExtAudioFile
					The extended audio file object.
	@param		inNumberFrames
					The number of frames to write.
	@param		ioData
					The buffer(s) from which audio data is written to the file.
	@result		An OSStatus error code.
		
	@discussion
				Writes the provided buffer list to an internal ring buffer and notifies an
				internal thread to perform the write at a later time. The first time this is
				called, allocations may be performed. You can call this with 0 frames and null
				buffer in a non-time-critical context to initialize the asynchronous mechanism.
				Once initialized, subsequent calls are very efficient and do not take locks;
				thus this may be used to write to a file from a realtime thread.

				The client must not mix synchronous and asynchronous writes to the same file.

				Pending writes are not guaranteed to be flushed to disk until
				ExtAudioFileDispose is called.

				N.B. Errors may occur after this call has returned. Such errors may be returned
				from subsequent calls to this function.
*/
extern OSStatus
ExtAudioFileWriteAsync(		ExtAudioFileRef			inExtAudioFile,
							UInt32					inNumberFrames,
							const AudioBufferList * ioData)					
																			__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_2_1);

/*!
	@function   ExtAudioFileSeek

	@abstract   Seek to a specific frame position.

	@param		inExtAudioFile
					The extended audio file object.
	@param		inFrameOffset
					The desired seek position, in sample frames, relative to the beginning of
					the file. This is specified in the sample rate and frame count of the file's format
					(not the client format)
	@result		An OSStatus error code.
	
	@discussion
				Sets the file's read position to the specified sample frame number. The next call
				to ExtAudioFileRead will return samples from precisely this location, even if it
				is located in the middle of a packet.
				
				This function's behavior with files open for writing is currently undefined.
*/
extern OSStatus
ExtAudioFileSeek(			ExtAudioFileRef			inExtAudioFile,
							SInt64					inFrameOffset)			
																			__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_2_1);

/*!
	@function   ExtAudioFileTell
	
	@abstract   Return the file's read/write position.

	@param		inExtAudioFile
					The extended audio file object.
	@param		outFrameOffset
					On exit, the file's current read/write position in sample frames. This is specified in the 
					sample rate and frame count of the file's format (not the client format)
	@result		An OSStatus error code.
	
	@discussion
*/
extern OSStatus
ExtAudioFileTell(			ExtAudioFileRef			inExtAudioFile,
							SInt64 *				outFrameOffset)			
																			__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_2_1);

//==================================================================================================
//	Property Access
/*!
    @functiongroup  Property Access
*/

/*!
	@function   ExtAudioFileGetPropertyInfo
	@abstract   Get information about a property

	@param		inExtAudioFile
					The extended audio file object.
	@param		inPropertyID
					The property being queried.
	@param		outSize
					If non-null, on exit, this is set to the size of the property's value.
	@param		outWritable
					If non-null, on exit, this indicates whether the property value is settable.
	@result		An OSStatus error code.

	@discussion
*/
extern OSStatus
ExtAudioFileGetPropertyInfo(ExtAudioFileRef			inExtAudioFile,
							ExtAudioFilePropertyID	inPropertyID,
							UInt32 *				outSize,
							Boolean *				outWritable)			
																			__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_2_1);

/*!
	@function   ExtAudioFileGetProperty
	@abstract   Get a property value.

	@param		inExtAudioFile
					The extended audio file object.
	@param		inPropertyID
					The property being fetched.
	@param		ioPropertyDataSize
					On entry, the size (in bytes) of the memory pointed to by outPropertyData.
					On exit, the actual size of the property data returned.	
	@param		outPropertyData
					The value of the property is copied to the memory this points to.
	@result		An OSStatus error code.

	@discussion
*/
extern OSStatus
ExtAudioFileGetProperty(	ExtAudioFileRef			inExtAudioFile,
							ExtAudioFilePropertyID	inPropertyID,
							UInt32 *				ioPropertyDataSize,
							void *					outPropertyData)		
																			__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_2_1);

/*!
	@function   ExtAudioFileSetProperty
	@abstract   Set a property value.

	@param		inExtAudioFile
					The extended audio file object.
	@param		inPropertyID
					The property being set.
	@param		inPropertyDataSize
					The size of the property data, in bytes.
	@param		inPropertyData
					Points to the property's new value.
	@result		An OSStatus error code.

	@discussion
*/
extern OSStatus
ExtAudioFileSetProperty(	ExtAudioFileRef			inExtAudioFile,
							ExtAudioFilePropertyID	inPropertyID,
							UInt32					inPropertyDataSize,
							const void *			inPropertyData)			
																			__OSX_AVAILABLE_STARTING(__MAC_10_4,__IPHONE_2_1);



#ifdef __cplusplus
}
#endif

#endif // __ExtendedAudioFile_h__
