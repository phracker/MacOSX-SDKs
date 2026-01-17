#if !__has_include(<AVFCore/AVCaptionGroup.h>)
/*
	File:  AVCaptionGroup.h

	Framework:  AVFoundation
 
	Copyright 2015-2023 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#if ( TARGET_OS_OSX || ( TARGET_OS_IOS && ! TARGET_OS_VISION ) )

#import <Foundation/Foundation.h>
#import <CoreMedia/CMTimeRange.h>

NS_ASSUME_NONNULL_BEGIN

@class AVCaptionGroupInternal;
@class AVCaption;

/*!
 @class AVCaptionGroup
 @abstract
	An instance of AVCaptionGroup represents zero or more captions that intersect in time.
 @discussion
 	The time range of each caption may overlap as there can be more than one active caption at a time. A sequence of AVCaptionGroup objects represents such overlapping caption timeline.

	An instance of AVCaptionGroup has a time range and a list of active captions for the time range. Two successive AVCaptionGroup objects have contiguous and non-overlapping time ranges. A new AVCaptionGroup time range commences whenever any of caption becomes active or inactive. When a caption spans over multiple AVCaptionGroup time ranges, these  AVCaptionGroup objects refer to an equal AVCaption object. 

	An empty AVCaptionGroup represents the time range without any active captions.

	The list of captions in the group is ordered according to the document order. For example, suppose a TTML document has two temporally overhapping captions:
	
    <div>
      <p begin="1s" end="3s">Hello<p>
      <p begin="0s" end="2s">World<p>
    </div>
	
	AVCaptionGroup for time range 1s to 2s has the list of captions: Hello and World in this order despite the fact that "World" is shown earlier than "Hello". 

	A client may use AVCaptionGroup to get the list of active captions for the time range. For example, presentation processing may find the AVCaptionGroup object for the current time, get the list of captions, and place them into the destination display region. 
 */
API_AVAILABLE(macos(12.0), ios(18.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos, watchos, visionos)
@interface AVCaptionGroup : NSObject
{
@private
	AVCaptionGroupInternal *_internal;
}

/*!
 @method initWithCaptions:timeRange:
 @abstract
	Initializes a caption group with the given set of captions and the time range.
 @discussion
	Every caption in the array must be equal or sub range of the time range, otherwise an exception is raised. 
 @param captions
	The captions that will be included in the group. The array is coped.
 @result
	A newly-initialized caption group.
 */
- (instancetype)initWithCaptions:(NSArray<AVCaption*> *)captions timeRange:(CMTimeRange)timeRange;

/*!
 @method initWithTimeRange:
 @abstract
	Initializes an empty caption group with the given time range.
 @discussion
	This is a convenient initializer to create an empty caption group time range.
 @param timeRange
	The time range for which there are no captions.
 @result
	A newly-initialized empty caption group.
 */
- (instancetype)initWithTimeRange:(CMTimeRange)timeRange;

/*!
 @property timeRange
 @abstract
	The time range represented by the caption group.
 @discussion
	If there are no captions in the group (i.e. the value of the captions property is an empty array), then the value of this property represents the time range of a sequence where no captions are present.
 */
@property (nonatomic, readonly) CMTimeRange timeRange;

/*!
 @property captions
 @abstract
	An array of AVCaption objects.
 @discussion
	If the value is an empty array, the caption group represents a region of the timeline in which there are no captions.
 */
@property (nonatomic, readonly) NSArray<AVCaption*> *captions;

@end

NS_ASSUME_NONNULL_END

#endif // ( TARGET_OS_OSX || ( TARGET_OS_IOS && ! TARGET_OS_VISION ) )

#else
#import <AVFCore/AVCaptionGroup.h>
#endif
