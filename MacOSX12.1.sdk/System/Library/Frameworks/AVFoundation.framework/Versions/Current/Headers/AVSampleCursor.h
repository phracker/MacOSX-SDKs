#if !__has_include(<AVFCore/AVSampleCursor.h>)
/*
	File:  AVSampleCursor.h

	Framework:  AVFoundation
 
	Copyright 2014-2021 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMTime.h>
#import <CoreMedia/CMSampleBuffer.h>

NS_ASSUME_NONNULL_BEGIN

#pragma pack(push)
#pragma pack()

/*!
	@class		AVSampleCursor

	@abstract	An AVSampleCursor is always positioned at a specific media sample in a sequence of media samples as defined by a higher-level construct, such as an AVAssetTrack. It can be moved to a new position in that sequence either backwards or forwards, either in decode order or in presentation order. Movement can be requested according to a count of samples or according to a delta in time.
	@discussion
	  AVSampleCursors can be compared by position within the sample sequence.
	  AVSampleCursors can be used synchronously to perform I/O in order to load media data of one or more media samples into memory.
	  An AVSampleCursor can provide information about the media sample at its current position, such as its duration, its presentation and decode timestamps, whether it can be decoded independently of other media samples, its offset and length in its storage container, and whether the track signals that the sample is intended to be loaded with other contiguous media samples in a "chunk". 
*/

@class AVSampleCursorInternal;

API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, tvos, watchos)
@interface AVSampleCursor : NSObject <NSCopying> {
@private
	AVSampleCursorInternal	*_sampleCursor;
}
AV_INIT_UNAVAILABLE

/*!
	@method			stepInDecodeOrderByCount:
	@abstract		Moves the cursor a given number of samples in decode order.
	@param			stepCount
					The number of samples to move across. If positive, step forward this many samples. If negative, step backward (-stepCount) samples.
	@result			The number of samples the cursor traversed. If the beginning or the end of the sample sequence was reached before the requested number of samples was traversed, the absolute value of the result will be less than the absolute value of stepCount.
*/
- (int64_t)stepInDecodeOrderByCount:(int64_t)stepCount;

/*!
	@method			stepInPresentationOrderByCount:
	@abstract		Moves the cursor a given number of samples in presentation order.
	@param			stepCount
					The number of samples to move across. If positive, step forward this many samples. If negative, step backward (-stepCount) samples.
	@result			The number of samples the cursor traversed. If the beginning or the end of the sample sequence was reached before the requested number of samples was traversed, the absolute value of the result will be less than the absolute value of stepCount.
*/
- (int64_t)stepInPresentationOrderByCount:(int64_t)stepCount;

/*!
	@method			stepByDecodeTime:wasPinned:
	@abstract		Moves the cursor by a given deltaTime on the decode timeline.
	@param			deltaDecodeTime
					The amount of time to move in the decode timeline.
	@param			outWasPinned
					If the beginning or the end of the sample sequence was reached before the requested deltaDecodeTime was traversed, the BOOL value at the address specified by outWasPinned will be set to YES. May be NULL if this information isn't desired.
	@result			The amount of time the cursor was moved along the decode timeline. Because sample cursors snap to sample boundaries when stepped, this value may not be equal to deltaDecodeTime even if the cursor was not pinned.
*/
- (CMTime)stepByDecodeTime:(CMTime)deltaDecodeTime wasPinned:(nullable BOOL *)outWasPinned;

/*!
	@method			stepByPresentationTime:wasPinned:
	@abstract		Moves the cursor by a given deltaTime on the presentation timeline.
	@param			deltaPresentationTime
					The amount of time to move in the presentation timeline.
	@param			outWasPinned
					If the beginning or the end of the sample sequence was reached before the requested deltaPresentationTime was traversed, the BOOL value at the address specified by outWasPinned will be set to YES. May be NULL if this information isn't desired.
	@result			The amount of time the cursor was moved along the presentation timeline. Because sample cursors snap to sample boundaries when stepped, this value may not be equal to deltaPresentationTime even if the cursor was not pinned.
*/
- (CMTime)stepByPresentationTime:(CMTime)deltaPresentationTime wasPinned:(nullable BOOL *)outWasPinned;

@end


@interface AVSampleCursor (AVSampleCursorTemporalPosition)

/*!
	@property		presentationTimeStamp
	@abstract		The presentation timestamp (PTS) of the sample at the current position of the cursor.
*/
@property (nonatomic, readonly) CMTime presentationTimeStamp;

/*!
	@property		decodeTimeStamp
	@abstract		The decode timestamp (DTS) of the sample at the current position of the cursor.
*/
@property (nonatomic, readonly) CMTime decodeTimeStamp;

/*!
	@method			comparePositionInDecodeOrderWithPositionOfCursor:
	@abstract		Compares the relative positions of two AVSampleCursors.
	@param			cursor
					An instance of AVSampleCursor with which to compare positions.
	@result			kCFCompareLessThan, kCFCompareEqualTo or kCFCompareGreaterThan, depending on whether the receiver points at a sample before, the same as, or after the sample pointed to by the specified AVSampleCursor.
	@discussion		If the receiver and cursor reference different sequences of samples, as when they're created by different instances of AVAssetTrack, results are undefined.
*/
- (NSComparisonResult)comparePositionInDecodeOrderWithPositionOfCursor:(AVSampleCursor *)cursor;

/*!
	@method			samplesWithEarlierDecodeTimeStampsMayHaveLaterPresentationTimeStampsThanCursor:
	@abstract		This method tests a boundary in the reordering from decode order to presentation order, determining whether it's possible for any sample earlier in decode order than the sample at the position of the receiver can have a presentation timestamp later than that of the specified sample cursor.
	@param			cursor
					An instance of AVSampleCursor with which to test the sample reordering boundary.
	@result			YES if it's possible for any sample earlier in decode order than the sample at the position of the receiver can have a presentation timestamp later than that of the specified sample cursor.
	@discussion		If the receiver and cursor reference different sequences of samples, as when they're created by different instances of AVAssetTrack, results are undefined.
*/
-(BOOL)samplesWithEarlierDecodeTimeStampsMayHaveLaterPresentationTimeStampsThanCursor:(AVSampleCursor *)cursor;

/*!
	@method			samplesWithLaterDecodeTimeStampsMayHaveEarlierPresentationTimeStampsThanCursor:
	@abstract		This method tests a boundary in the reordering from decode order to presentation order, determining whether it's possible for any sample later in decode order than the sample at the position of the receiver can have a presentation timestamp earlier than that of the specified sample cursor.
	@param			cursor
					An instance of AVSampleCursor with which to test the sample reordering boundary.
	@result			YES if it's possible for any sample later in decode order than the sample at the position of the receiver can have a presentation timestamp earlier than that of the specified sample cursor.
	@discussion		If the receiver and cursor reference different sequences of samples, as when they're created by different instances of AVAssetTrack, results are undefined.
*/
-(BOOL)samplesWithLaterDecodeTimeStampsMayHaveEarlierPresentationTimeStampsThanCursor:(AVSampleCursor *)cursor;

@end


@interface AVSampleCursor (AVSampleCursorCurrentSampleInfo)

/*!
	@property		currentSampleDuration
	@abstract		Indicates the decode duration of the sample at the receiver's current position.
	@discussion		If the receiver must be advanced past its current position in order to determine the decode duration of the current sample, the value of currentSampleDuration is equal to kCMTimeIndefinite. This can occur with streaming formats such as MPEG-2 transport streams.
*/
@property (nonatomic, readonly) CMTime currentSampleDuration;

/*!
	@method			copyCurrentSampleFormatDescription:
	@abstract		Provides the format description of the sample at the receiver's current position.
*/
- (CMFormatDescriptionRef)copyCurrentSampleFormatDescription CF_RETURNS_RETAINED;

/*!
    @struct		AVSampleCursorSyncInfo
    @abstract   A struct for describing attributes of a media sample for consideration when resynchronizing a decoder.
    @field      sampleIsFullSync
    			Indicates whether the sample is a full sync sample, also known as an Instantaneous Decoder Refresh sample, and is sufficient in itself to completely resynchronize a decoder.
    @field      sampleIsPartialSync
    			Indicates whether the sample is a partial sync sample.
    @field      sampleIsDroppable
    			Indicates whether the sample is droppable.
*/
typedef struct {
    BOOL      sampleIsFullSync;
    BOOL      sampleIsPartialSync;
    BOOL      sampleIsDroppable;
} AVSampleCursorSyncInfo;

/*!
	@property		currentSampleSyncInfo
	@abstract		Provides information about the current sample for consideration when resynchronizing a decoder, as when scrubbing.
*/
@property (nonatomic, readonly) AVSampleCursorSyncInfo currentSampleSyncInfo;

/*!
    @struct		AVSampleCursorDependencyInfo
    @abstract   A struct for describing dependencies between a media sample and other media samples in the same sample sequence.
    @field      sampleIndicatesWhetherItHasDependentSamples
    			Indicates whether the presence or absence of other samples that are dependent on the sample is known.
    @field      sampleHasDependentSamples
    			If sampleIndicatesWhetherItHasDependentSamples is YES, indicates whether the sample has dependent samples.
    @field      sampleIndicatesWhetherItDependsOnOthers
    			Indicates whether the sample's independency from other samples or dependency on other samples is known.
    @field      sampleDependsOnOthers
    			If sampleIndicatesWhetherItDependsOnOthers is YES, indicates whether the sample depends on other media samples.
    @field      sampleIndicatesWhetherItHasRedundantCoding
    			Indicates whether the presence of redundant coding of the sample is known.
    @field      sampleHasRedundantCoding
    			If sampleIndicatesWhetherItHasRedundantCoding is YES, indicates whether the sample has redundant coding.
*/
typedef struct {
	BOOL sampleIndicatesWhetherItHasDependentSamples;
    BOOL sampleHasDependentSamples;
	BOOL sampleIndicatesWhetherItDependsOnOthers;
    BOOL sampleDependsOnOthers;
	BOOL sampleIndicatesWhetherItHasRedundantCoding;
    BOOL sampleHasRedundantCoding;
} AVSampleCursorDependencyInfo;

/*!
	@property		currentSampleDependencyInfo
	@abstract		Provides information about dependencies between a media sample and other media samples in the same sample sequence, if known.
*/
@property (nonatomic, readonly) AVSampleCursorDependencyInfo currentSampleDependencyInfo;

/*!
       @property               currentSampleDependencyAttachments
       @abstract               Provides a dictionary containing dependency related sample buffer attachments, if known.  See kCMSampleAttachmentKey_... in CoreMedia/CMSampleBuffer.h.
*/
@property (nonatomic, readonly, nullable) NSDictionary *currentSampleDependencyAttachments API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, tvos, watchos);

/*!
	@struct		AVSampleCursorAudioDependencyInfo
	@abstract   A struct for describing the independent decodability of audio samples
	@field      audioSampleIsIndependentlyDecodable
				Indicates whether the sample is independently decodable.  Will be YES for Immediate Playout Frames (IPFs) and Independent Frames (IFs).
	@field      audioSamplePacketRefreshCount
				If audioSampleIsIndependentlyDecodable is YES, indicates how many samples, starting at this sample, must be fed to the decoder to achieve full decoder refresh.  Will be zero for Immediate Playout Frames (IPFs). 
*/
typedef struct {
	BOOL		audioSampleIsIndependentlyDecodable;
	NSInteger	audioSamplePacketRefreshCount;
} AVSampleCursorAudioDependencyInfo;

/*!
	@property	currentSampleAudioDependencyInfo
	@abstract	Provides information about the independent decodability of an audio sample.
	@discussion	In order to position a sample cursor at the first sample that the audio decoder requires for a full refresh, you will need to walk it back from
 				the current sample until you find a sample that is independently decodable, and whose audioSamplePacketRefreshCount is greater than or equal to
 				the number of steps back you have taken.  This implies that if the current sample (before this walk) is independently decodable, with an
 				audioSampleRefreshCount of zero, no walk is required.
*/
@property (nonatomic, readonly) AVSampleCursorAudioDependencyInfo currentSampleAudioDependencyInfo API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos, watchos);

/*!
	@property		samplesRequiredForDecoderRefresh
	@abstract		Count of samples prior to the current sample, in decode order, that the decoder requires in order to achieve fully coherent output at the current decode time, as after a seek. Zero will be returned if no samples are required for decoder refresh or if the track does not contain this information.
	@discussion		Some sample sequences that do not indicate sample dependencies may instead indicate that in order for a specific sample to be decoded with all available accuracy, samples prior to that sample in decode order must be decoded before the specific sample is decoded.

	In order to position a sample cursor at the first sample that the decoder requires for a full refresh, you can use code like the following:
	
	
			NSInteger samplesPriorToCurrentSampleToFeedToDecoder = [mySampleCursor samplesRequiredForDecoderRefresh];
			AVSampleCursor *cursorForObtainingRefreshSamples = [mySampleCursor copy];
			[cursorForObtainingRefreshSamples stepInDecodeOrderByCount: -samplesPriorToCurrentSampleToFeedToDecoder ];
			
			// cursorForObtainingRefreshSamples is now positioned at the first sample that must be provided to the decoder
			// in order to decode the sample at the position of mySampleCursor in full
			
*/
@property (nonatomic, readonly) NSInteger samplesRequiredForDecoderRefresh API_AVAILABLE(macos(10.11)) API_UNAVAILABLE(ios, tvos, watchos);

@end


@interface AVSampleCursor (AVSampleCursorSampleStorageInfo)

/*!
	@property		currentChunkStorageURL
	@abstract		The URL of the storage container of the current sample, as well as other samples that are intended to be loaded in the same operation as a "chunk".
	@discussion		May be nil; if nil, the storage location of the chunk is the URL of the sample cursor's track's asset, if it has one.
*/
@property (nonatomic, readonly, nullable) NSURL *currentChunkStorageURL;

/*!
    @struct		AVSampleCursorStorageRange
    @abstract   A struct for indicating the offset and length of storage occupied by a media sample or its chunk.
    @field      offset
    			The offset of the first byte of storage occupied by a media sample or its chunk.
    @field      length
    			The count of bytes of storage occupied by a media sample or its chunk.
    @discussion Like NSRange, but rangier.
*/
typedef struct {
    int64_t offset;
    int64_t length;
} AVSampleCursorStorageRange;

/*!
	@property		currentChunkStorageRange
	@abstract		The offset and length of samples in currentChunkStorageURL that are intended to be loaded together with the current sample as a "chunk".
	@discussion		If the current chunk isn't stored contiguously in its storage container, currentChunkStorageRange.offset will be -1. In such cases you can use AVSampleBufferGenerator to obtain the sample data.
*/
@property (nonatomic, readonly) AVSampleCursorStorageRange currentChunkStorageRange;

/*!
    @struct		AVSampleCursorChunkInfo
    @abstract   Provides information about a chunk of media samples.
    @field      chunkSampleCount
    			The count of media samples in the chunk.
    @field      chunkHasUniformSampleSizes
    			YES if all of the samples in the chunk occupy the same number of bytes in storage.
    @field      currentChunkHasUniformSampleDurations
    			YES if all of the samples in the chunk have the same duration.
    @field      currentChunkHasUniformFormatDescriptions
    			YES if all of the samples in the chunk have the same format description.
*/
typedef struct {
    int64_t chunkSampleCount;
    BOOL chunkHasUniformSampleSizes;
    BOOL chunkHasUniformSampleDurations;
    BOOL chunkHasUniformFormatDescriptions;
} AVSampleCursorChunkInfo;

/*!
	@property		currentChunkInfo
	@abstract		Provides information about the "chunk" of samples to which the current sample belongs. If the media format that defines the sequence of samples does not signal "chunking" of samples in any way, each sample will be considered by the receiver as belonging to a chunk of one sample only.
*/
@property (nonatomic, readonly) AVSampleCursorChunkInfo currentChunkInfo;

/*!
	@property		currentSampleIndexInChunk
	@abstract		The index of the current sample within the chunk to which it belongs.
*/
@property (nonatomic, readonly) int64_t currentSampleIndexInChunk;

/*!
	@property		currentSampleStorageRange
	@abstract		The offset and length of the current sample in currentChunkStorageURL.
	@discussion		If the current sample isn't stored contiguously in its storage container, currentSampleStorageRange.offset will be -1. In such cases you can use AVSampleBufferGenerator to obtain the sample data.
*/
@property (nonatomic, readonly) AVSampleCursorStorageRange currentSampleStorageRange;

@end

#pragma pack(pop)

NS_ASSUME_NONNULL_END


#else
#import <AVFCore/AVSampleCursor.h>
#endif
