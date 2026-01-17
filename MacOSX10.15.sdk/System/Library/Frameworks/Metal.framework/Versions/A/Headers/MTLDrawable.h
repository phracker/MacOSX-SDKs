//
//  MTLDrawable.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>

NS_ASSUME_NONNULL_BEGIN
@protocol MTLDrawable;

/*!
 @typedef MTLDrawablePresentedHandler
 @abstract The presented callback function protocol
 @disucssion Be careful when you use delta between this presentedTime and previous frame's presentedTime to animate next frame. If the frame was presented using presentAfterMinimumDuration or presentAtTime, the presentedTime might includes delays to meet your specified present time. If you want to measure how much frame you can achieve, use GPUStartTime in the first command buffer of your frame rendering and GPUEndTime of your last frame rendering to calculate the frame interval.
*/
typedef void (^MTLDrawablePresentedHandler)(id<MTLDrawable>);

/*!
 @protocol MTLDrawable
 @abstract All "drawable" objects (such as those coming from CAMetalLayer) are expected to conform to this protocol
 */
API_AVAILABLE(macos(10.11), ios(8.0))
@protocol MTLDrawable <NSObject>

/* Present this drawable as soon as possible */
- (void)present;

/* Present this drawable at the given host time */
- (void)presentAtTime:(CFTimeInterval)presentationTime;


@end
NS_ASSUME_NONNULL_END
