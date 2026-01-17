/*
	File:		AVAudioFile.h
	Framework:	AVFoundation
	
	Copyright (c) 2014-2015 Apple Inc. All Rights Reserved.
*/

#import <AVFAudio/AVAudioTypes.h>
#import <AVFAudio/AVAudioFormat.h>

NS_ASSUME_NONNULL_BEGIN

@class NSURL;
@class AVAudioPCMBuffer;

/*!
	@class AVAudioFile
	@abstract
		AVAudioFile represents an audio file opened for reading or writing.
	@discussion
		Regardless of the file's actual format, reading and writing the file is done via 
		`AVAudioPCMBuffer` objects, containing samples in an `AVAudioCommonFormat`,
		referred to as the file's "processing format." Conversions are performed to and from
		the file's actual format.
		
		Reads and writes are always sequential, but random access is possible by setting the
		framePosition property.
*/
OS_EXPORT API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0))
@interface AVAudioFile : NSObject {
@private
	void *_impl;
}
/*! @method initForReading:error:
	@abstract Open a file for reading.
	@param fileURL
		the file to open
	@param outError
		on exit, if an error occurs, a description of the error
	@discussion
		This opens the file for reading using the standard format (deinterleaved floating point).
*/
- (nullable instancetype)initForReading:(NSURL *)fileURL error:(NSError **)outError;

/*!	@method initForReading:commonFormat:interleaved:error:
	@abstract Open a file for reading, using a specified processing format.
	@param fileURL
		the file to open
	@param format
		the processing format to use when reading from the file
	@param interleaved
		whether to use an interleaved processing format
	@param outError
		on exit, if an error occurs, a description of the error
*/
- (nullable instancetype)initForReading:(NSURL *)fileURL commonFormat:(AVAudioCommonFormat)format interleaved:(BOOL)interleaved error:(NSError **)outError;

/*! @method initForWriting:settings:error:
	@abstract Open a file for writing.
	@param fileURL
		the path at which to create the file
	@param settings
		the format of the file to create (See `AVAudioRecorder`.)
	@param outError
		on exit, if an error occurs, a description of the error
	@discussion
		The file type to create can be set through the corresponding settings key. If not set, it will be
		inferred from the file extension. Will overwrite a file at the specified URL if a file exists.

		This opens the file for writing using the standard format (deinterleaved floating point).
*/
- (nullable instancetype)initForWriting:(NSURL *)fileURL settings:(NSDictionary<NSString *, id> *)settings error:(NSError **)outError;

/*! @method initForWriting:settings:commonFormat:interleaved:error:
	@abstract Open a file for writing.
	@param fileURL
		the path at which to create the file
	@param settings
		the format of the file to create (See `AVAudioRecorder`.)
	@param format
		the processing format to use when writing to the file
	@param interleaved
		whether to use an interleaved processing format
	@param outError
		on exit, if an error occurs, a description of the error
	@discussion
		The file type to create can be set through the corresponding settings key. If not set, it will be
		inferred from the file extension. Will overwrite a file at the specified URL if a file exists.
*/
- (nullable instancetype)initForWriting:(NSURL *)fileURL settings:(NSDictionary<NSString *, id> *)settings commonFormat:(AVAudioCommonFormat)format interleaved:(BOOL)interleaved error:(NSError **)outError;

/*! @method readIntoBuffer:error:
	@abstract Read an entire buffer.
	@param buffer
		The buffer into which to read from the file. Its format must match the file's
		processing format.
	@param outError
		on exit, if an error occurs, a description of the error
	@return
		YES for success.
	@discussion
		Reading sequentially from framePosition, attempts to fill the buffer to its capacity. On
		return, the buffer's length indicates the number of sample frames successfully read.
*/
- (BOOL)readIntoBuffer:(AVAudioPCMBuffer *)buffer error:(NSError **)outError;

/*! @method readIntoBuffer:frameCount:error:
	@abstract Read a portion of a buffer.
	@param frames
		The number of frames to read.
	@param buffer
		The buffer into which to read from the file. Its format must match the file's
		processing format.
	@param outError
		on exit, if an error occurs, a description of the error
	@return
		YES for success.
	@discussion
		Like `readIntoBuffer:error:`, but can be used to read fewer frames than buffer.frameCapacity.
*/
- (BOOL)readIntoBuffer:(AVAudioPCMBuffer *)buffer frameCount:(AVAudioFrameCount)frames error:(NSError **)outError;

/*! @method writeFromBuffer:error:
	@abstract Write a buffer.
	@param buffer
		The buffer from which to write to the file. Its format must match the file's
		processing format.
	@param outError
		on exit, if an error occurs, a description of the error
	@return
		YES for success.
	@discussion
		Writes sequentially. The buffer's frameLength signifies how much of the buffer is to be written.
*/
- (BOOL)writeFromBuffer:(const AVAudioPCMBuffer *)buffer error:(NSError **)outError;

/*!	@property url
	@abstract The URL the file is reading or writing.
*/
@property (nonatomic, readonly) NSURL *url;

/*! @property fileFormat
	@abstract The on-disk format of the file.
*/
@property (nonatomic, readonly) AVAudioFormat *fileFormat;

/*! @property processingFormat
	@abstract The processing format of the file.
*/
@property (nonatomic, readonly) AVAudioFormat *processingFormat;

/*! @property length
	@abstract The number of sample frames in the file.
	@discussion
		 Note: this can be expensive to compute for the first time.
*/
@property (nonatomic, readonly) AVAudioFramePosition length;

/*! @property framePosition
	@abstract The position in the file at which the next read or write will occur.
	@discussion
		Set framePosition to perform a seek before a read or write. A read or write operation advances the frame position by the number of frames read or written.
*/
@property (nonatomic) AVAudioFramePosition framePosition;
@end

NS_ASSUME_NONNULL_END
