//
//  VNDetectHorizonRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>
#import <Vision/VNObservation.h>


NS_ASSUME_NONNULL_BEGIN


/*!
	@brief Determine what the horizon tilt of an image is.
	
	@discussion If the horizon tilt is detected in an image, the request will provide a VNHorizonObservation in the results which describe how to transform the image so that the horizon line becomes level.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNDetectHorizonRequest : VNImageBasedRequest

/*!
	@discussion VNHorizonObservation results.
*/
@property (readonly, copy, nullable) NSArray<VNHorizonObservation*>* results;

@end


API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
static const NSUInteger VNDetectHorizonRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
