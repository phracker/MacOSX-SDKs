//
//  VNDetectFaceRectanglesRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>
#import <Vision/VNObservation.h>


NS_ASSUME_NONNULL_BEGIN


/*!
	@brief A request that will detect faces in an image.

	@details This request will generate VNFaceObservation objects with a defined boundingBox.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNDetectFaceRectanglesRequest : VNImageBasedRequest

/*!
	@discussion VNFaceObservation results.
*/
@property (readonly, copy, nullable) NSArray<VNFaceObservation*>* results;

@end


API_DEPRECATED_WITH_REPLACEMENT("VNDetectFaceRectanglesRequestRevision2", macos(10.14, 13.0), ios(12.0, 16.0), tvos(12.0, 16.0))
static const NSUInteger VNDetectFaceRectanglesRequestRevision1 = 1;

/*!
    @brief    This request revision can calculate face roll and yaw properties. See [VNFaceObservation -roll] and [VNFaceObservation -yaw]  respectively.
*/
API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
static const NSUInteger VNDetectFaceRectanglesRequestRevision2 = 2;

/*!
    @brief    This request revision can calculate face pitch, in addition to roll and yaw, see [VNFaceObservation -pitch] property. In addition, all three properties - roll, yaw, and pitch are now reported in contiguous manner.
*/
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0))
static const NSUInteger VNDetectFaceRectanglesRequestRevision3 = 3;


NS_ASSUME_NONNULL_END
