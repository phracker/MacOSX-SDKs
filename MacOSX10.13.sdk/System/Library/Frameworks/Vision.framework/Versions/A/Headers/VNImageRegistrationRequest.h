//
//  VNImageRegistrationRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Vision/VNTargetedImageRequest.h>
#import <Vision/VNObservation.h>


NS_ASSUME_NONNULL_BEGIN


/*!
	@brief A request that will calculate a transformation for morphing a "floating" image onto an unchanging "reference" image.
	
	@discussion The request is created with the targeted image acting as the floating image. Processing the request will calculate the transformations that morph the floating image onto the reference image.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNImageRegistrationRequest : VNTargetedImageRequest
@end


/*!
	@brief An image registration request that will calculate a translational transformation for morphing a "floating" image onto an unchanging "reference" image.
	
	@discussion The request is created with the targeted image acting as the floating image. Processing the request will calculate the affine transformations that morph the floating image onto the reference image.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNTranslationalImageRegistrationRequest : VNImageRegistrationRequest
@end



/*!
	@brief An image registration request that will calculate a homographic transformation for morphing a "floating" image onto an unchanging "reference" image.
	
	@discussion The request is created with the targeted image acting as the floating image. Processing the request will calculate the matrix warp transform that morph the floating image onto the reference image.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNHomographicImageRegistrationRequest : VNImageRegistrationRequest
@end


NS_ASSUME_NONNULL_END
