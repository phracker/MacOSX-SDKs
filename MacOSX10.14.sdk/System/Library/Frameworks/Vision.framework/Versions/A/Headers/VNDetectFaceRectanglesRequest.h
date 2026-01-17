//
//  VNDetectFaceRectanglesRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>


NS_ASSUME_NONNULL_BEGIN


/*!
	@brief A request that will detect faces in an image.

	@details This request will generate VNFaceObservation objects with defined a boundingBox.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNDetectFaceRectanglesRequest : VNImageBasedRequest
@end


API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
static const NSUInteger VNDetectFaceRectanglesRequestRevision1 = 1;

API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
static const NSUInteger VNDetectFaceRectanglesRequestRevision2 = 2;


NS_ASSUME_NONNULL_END
