//
//  VNDetectTextRectanglesRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>


NS_ASSUME_NONNULL_BEGIN


/*!
	@brief A request that will detect regions of text in an image.

	@details This request will generate VNTextObservation objects describing the locations of text detected in an image.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNDetectTextRectanglesRequest : VNImageBasedRequest

/*!
	@brief Determine whether or not the bounding boxes of individual characters should also be defined in the resultant VNTextObservations.
*/
@property (readwrite, nonatomic, assign) BOOL reportCharacterBoxes;

@end

NS_ASSUME_NONNULL_END
