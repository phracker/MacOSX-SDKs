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


static const NSUInteger VNTranslationalImageRegistrationRequestRevision1 = 1;



/*!
	@brief An image registration request that will calculate a homographic transformation for morphing a "floating" image onto an unchanging "reference" image.
	
	@discussion The request is created with the targeted image acting as the floating image. Processing the request will calculate the matrix warp transform that morph the floating image onto the reference image.
	            Note that the request will fail unless the pixel dimensions of the reference image do not exactly match the resolved region of interest of the floating image.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNHomographicImageRegistrationRequest : VNImageRegistrationRequest
@end


static const NSUInteger VNHomographicImageRegistrationRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
