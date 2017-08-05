/*
    File:  AVTimedMetadataGroup.h

	Framework:  AVFoundation
 
	Copyright 2010-2015 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMTimeRange.h>
#import <CoreMedia/CMFormatDescription.h>
#import <CoreMedia/CMSampleBuffer.h>

@class AVTimedMetadataGroupInternal;
@class AVDateRangeMetadataGroupInternal;
@class AVMetadataItem;

NS_ASSUME_NONNULL_BEGIN

/*!
	@class		AVMetadataGroup
 
	@abstract	AVMetadataGroup is the common superclass for AVTimedMetadataGroup and AVDateRangeMetadataGroup; each represents a collection of metadata items associated with a segment of a timeline. AVTimedMetadataGroup is typically used with content that defines an independent timeline, while AVDateRangeMetadataGroup is typically used with content that's associated with a specific range of dates.
*/

NS_CLASS_AVAILABLE(10_11, 9_0)
@interface AVMetadataGroup : NSObject

@property (nonatomic, readonly, copy) NSArray<AVMetadataItem *> *items;

@end

@interface AVMetadataGroup (AVMetadataGroupIdentification)

/* indicates the classifyingLabel of the group; nil if no classifyingLabel is indicated */
@property (nonatomic, readonly, nullable) NSString *classifyingLabel NS_AVAILABLE(10_11_3, 9_3);

/* indicates the unique identifier of the group; nil if no unique identifier is indicated */
@property (nonatomic, readonly, nullable) NSString *uniqueID NS_AVAILABLE(10_11_3, 9_3);

@end

/*!
	@class		AVTimedMetadataGroup
 
	@abstract	AVTimedMetadataGroup is used to represent a collection of metadata items that are valid for use during a specific range of time. For example, AVTimedMetadataGroups are used to represent chapters, optionally containing metadata items for chapter titles and chapter images.
*/

NS_CLASS_AVAILABLE(10_7, 4_3)
@interface AVTimedMetadataGroup : AVMetadataGroup <NSCopying, NSMutableCopying>
{
@private
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
- (instancetype)initWithItems:(NSArray<AVMetadataItem *> *)items timeRange:(CMTimeRange)timeRange;

/*!
	@method		initWithSampleBuffer:
	@abstract	Initializes an instance of AVTimedMetadataGroup with a sample buffer.
	@param		sampleBuffer
				A CMSampleBuffer with media type kCMMediaType_Metadata.
	@result		An instance of AVTimedMetadataGroup.
*/
- (nullable instancetype)initWithSampleBuffer:(CMSampleBufferRef)sampleBuffer NS_AVAILABLE(10_10, 8_0);

/* indicates the time range of the timed metadata */
@property (nonatomic, readonly) CMTimeRange timeRange;

/* an array of AVMetadataItems */
@property (nonatomic, readonly, copy) NSArray<AVMetadataItem *> *items;

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
- (nullable CMMetadataFormatDescriptionRef)copyFormatDescription NS_AVAILABLE(10_10, 8_0) CF_RETURNS_RETAINED;

@end

/*!
	@class		AVMutableTimedMetadataGroup
 
	@abstract	AVMutableTimedMetadataGroup is used to represent a mutable collection of metadata items that are valid for use during a specific range of time.
*/

NS_CLASS_AVAILABLE(10_7, 4_3)
@interface AVMutableTimedMetadataGroup : AVTimedMetadataGroup
{
@private
	AVTimedMetadataGroupInternal	*_mutablePriv;
}

/* indicates the time range of the timed metadata */
@property (nonatomic, readwrite) CMTimeRange timeRange;

/* an array of AVMetadataItems */
@property (nonatomic, readwrite, copy) NSArray<AVMetadataItem *> *items;

@end

/*!
	@class		AVDateRangeMetadataGroup
 
	@abstract	AVDateRangeMetadataGroup is used to represent a collection of metadata items that are valid for use within a specific range of dates.
*/

NS_CLASS_AVAILABLE(10_11, 9_0)
@interface AVDateRangeMetadataGroup : AVMetadataGroup <NSCopying, NSMutableCopying>
{
@private
	AVDateRangeMetadataGroupInternal *_priv;
}

/*!
	@method		initWithItems:startDate:endDate:
	@abstract	Initializes an instance of AVDateRangeMetadataGroup with a collection of metadata items.
	@param		items
				An NSArray of AVMetadataItems.
	@param		startDate
				The start date of the collection of AVMetadataItems.
	@param		endDate
				The end date of the collection of AVMetadataItems. If the receiver is intended to represent information about an instantaneous event, the value of endDate should be equal to the value of startDate. A value of nil for endDate indicates that the endDate is indefinite.
	@result		An instance of AVDateRangeMetadataGroup.
*/
- (instancetype)initWithItems:(NSArray<AVMetadataItem *> *)items startDate:(NSDate *)startDate endDate:(nullable NSDate *)endDate;

/* indicates the start date of the metadata */
@property (nonatomic, readonly, copy) NSDate *startDate;

/* indicates the end date of the metadata */
@property (nonatomic, readonly, copy, nullable) NSDate *endDate;

/* an array of AVMetadataItems */
@property (nonatomic, readonly, copy) NSArray<AVMetadataItem *> *items;

@end

/*!
	@class		AVMutableDateRangeMetadataGroup
 
	@abstract	AVMutableDateRangeMetadataGroup is used to represent a mutable collection of metadata items that are valid for use within a specific range of dates.
*/

NS_CLASS_AVAILABLE(10_11, 9_0)
@interface AVMutableDateRangeMetadataGroup : AVDateRangeMetadataGroup
{
@private
	AVDateRangeMetadataGroupInternal *_mutablePriv;
}

/* indicates the start date of the metadata */
@property (nonatomic, readwrite, copy) NSDate *startDate;

/* indicates the end date of the metadata */
@property (nonatomic, readwrite, copy, nullable) NSDate *endDate;

/* an array of AVMetadataItems */
@property (nonatomic, readwrite, copy) NSArray<AVMetadataItem *> *items;

@end

NS_ASSUME_NONNULL_END
