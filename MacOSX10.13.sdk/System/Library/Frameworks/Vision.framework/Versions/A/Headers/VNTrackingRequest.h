//
//  VNTrackingRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>


NS_ASSUME_NONNULL_BEGIN


typedef NS_ENUM(NSUInteger, VNRequestTrackingLevel)
{
    VNRequestTrackingLevelAccurate = 0,
    VNRequestTrackingLevelFast
};


/*!
	@abstract	A base class for all tracking requests.
	@discussion	Since this class is not meant to be directly instantiated, no initializers are available.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNTrackingRequest : VNImageBasedRequest

/*!
 @property property inputObservation
 @abstract The starting object observation for initial tracker setup or returned from previous object tracking iteration. In general, unless documented in the request's documentation, the rectangle must be defined in normalized coordinates (size and origin between [0,1] with origin at LLC).
*/
@property (readwrite, nonatomic, strong) VNDetectedObjectObservation * inputObservation;

/*!
 @property property trackingLevel
 @abstract Tracking level allows tuning tracking algorithm to prefer speed (VNRequestOptionTrackingLevelFast) vs. tracking object location accuracy (VNRequestOptionTrackingLevelAccurate)
 */
@property (readwrite, nonatomic, assign) VNRequestTrackingLevel trackingLevel;

/*!
 @property property lastFrame
 @abstract This property allows marking the last frame for tracking using current tracker. If set to YES, the results for this frame will be processed and returned and the current tracker will be released to the pool of available trackers
 */
@property (readwrite, nonatomic, assign, getter=isLastFrame) BOOL lastFrame;

- (instancetype) init   NS_UNAVAILABLE;
- (instancetype) initWithCompletionHandler:(nullable VNRequestCompletionHandler)completionHandler   NS_UNAVAILABLE;

@end


NS_ASSUME_NONNULL_END
