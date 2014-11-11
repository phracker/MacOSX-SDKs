/*
    File:  AVTimedMetadataGroup.h

	Framework:  AVFoundation
 
	Copyright 2010-2014 Apple Inc. All rights reserved.

*/

/*!
	@class		AVTimedMetadataGroup
 
	@abstract	AVTimedMetadataGroup is used to represent a collection of metadata items that are valid for use during a specific range of time. For example, AVTimedMetadataGroups are used to represent chapters, optionally containing metadata items for chapter titles and chapter images.
*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMTimeRange.h>
#import <CoreMedia/CMFormatDescription.h>
#import <CoreMedia/CMSampleBuffer.h>

@class AVTimedMetadataGroupInternal;

NS_CLASS_AVAILABLE(10_7, 4_3)
@interface AVTimedMetadataGroup : NSObject <NSCopying>
{
	AVTimedMetadataGroupInternal *_priv;
}

/*!
	@method		initWithItems:timeRange:
	@abstract	Initializes an instance of AVTimedMetadataGroup with a collection of metadata items.
	@param		items
				An NSArray of AVMetadataItems.
	@param		timeRange
				The timeRange of the collection of AVMetadataItems.
	@result		An instance of AVTimedMetadataGroup.
*/
- (instancetype)initWithItems:(NSArray *)items timeRange:(CMTimeRange)timeRange;

/*!
	@method		initWithSampleBuffer:
	@abstract	Initializes an instance of AVTimedMetadataGroup with a sample buffer.
	@param		sampleBuffer
				A CMSampleBuffer with media type kCMMediaType_Metadata.
	@result		An instance of AVTimedMetadataGroup.
*/
- (instancetype)initWithSampleBuffer:(CMSampleBufferRef)sampleBuffer NS_AVAILABLE(10_10, 8_0);

/* indicates the time range of the timed metadata */
@property (readonly) CMTimeRange timeRange;

/* array of AVMetadataItem */
@property (readonly, copy) NSArray *items;

@end


@interface AVTimedMetadataGroup (AVTimedMetadataGroupSerializationSupport)

/*!
	@method		copyFormatDescription
	@abstract	Creates a format description based on the receiver's items.
	@result		An instance of CMMetadataFormatDescription sufficient to describe the contents of all the items referenced by the receiver.
	@discussion
		The returned format description is suitable for use as the format hint parameter when creating an instance of AVAssetWriterInput.
 
		Each item referenced by the receiver must carry a non-nil value for its dataType property.  An exception will be thrown if any item does not have a data type.
*/
- (CMMetadataFormatDescriptionRef)copyFormatDescription NS_AVAILABLE(10_10, 8_0) CF_RETURNS_RETAINED;

@end

/*!
	@class		AVMutableTimedMetadataGroup
 
	@abstract	AVMutableTimedMetadataGroup is used to represent a mutable collection of metadata items that are valid for use during a specific range of time.
*/

@class AVMutableTimedMetadataGroupInternal;

NS_CLASS_AVAILABLE(10_7, 4_3)
@interface AVMutableTimedMetadataGroup : AVTimedMetadataGroup
{
	AVMutableTimedMetadataGroupInternal	*_mutablePriv;
}

/* indicates the time range of the timed metadata */
@property (readwrite) CMTimeRange timeRange;

/* array of AVMetadataItem */
@property (readwrite, copy) NSArray *items;

@end
