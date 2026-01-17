//
//  VNTrackHomographicImageRegistrationRequest.h
//  Vision
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Vision/VNStatefulRequest.h>


NS_ASSUME_NONNULL_BEGIN


/*!
	@brief An image registration request that will produce a homographic transformation that can morph one image to another.
	@discussion Because this is a stateful request, it must be performed on at least two images in order to produce an observation.
*/
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0))
@interface VNTrackHomographicImageRegistrationRequest : VNStatefulRequest

/*!
	@brief Create a new request that can statefully track the homographic registration of two images.
	@discussion This is a convenience initializer for a frame analysis spacing of kCMTimeZero and a nil completion handler.
*/
- (instancetype) init;

/*!
	@brief Create a new request that can statefully track the homographic registration of two images.
	@discussion This is a convenience initializer for a frame analysis spacing of kCMTimeZero.
*/
- (instancetype) initWithCompletionHandler:(nullable VNRequestCompletionHandler)completionHandler;

/*!
	@discussion VNImageHomographicAlignmentObservation results.
*/
@property (readonly, copy, nullable) NSArray<VNImageHomographicAlignmentObservation*>* results;

@end


API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0))
static const NSUInteger VNTrackHomographicImageRegistrationRequestRevision1 = 1;



NS_ASSUME_NONNULL_END
