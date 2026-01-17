//
//  VNDetectRectanglesRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>
#import <Vision/VNTypes.h>


NS_ASSUME_NONNULL_BEGIN


/*!
	@brief A request that will detect rectangles in an image.

	@details This request will generate VNRectangleObservation objects describing the location of rectangles detected in an image.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNDetectRectanglesRequest : VNImageBasedRequest

/*!
 @brief Specifies the minimum aspect ratio of the rectangle(s) to look for, range [0.0, 1.0], default 0.5
 */
@property (readwrite, nonatomic, assign) VNAspectRatio minimumAspectRatio;

/*!
 @brief Specifies the maximum aspect ratio of the rectangle(s) to look for, range [0.0, 1.0], default 1.0
 */
@property (readwrite, nonatomic, assign) VNAspectRatio maximumAspectRatio;

/*!
 @brief Specifies the maximum number of degrees a rectangle corner angle can deviate from 90 degrees, range [0,45], default 30
 */
@property (readwrite, nonatomic, assign) VNDegrees quadratureTolerance;

/*!
 @brief Specifies the minimum size of the rectangle to be detected, as a proportion of the smallest dimension, range [0.0, 1.0], default .2. Any smaller rectangles that may have been detected will not be returned. 
 */
@property (readwrite, nonatomic, assign) float minimumSize;

/*!
 @brief Specifies a minimum confidence score, range [0.0, 1.0], default 0.0. Any rectangles with a lower confidence score will not be returned.
 */
@property (readwrite, nonatomic, assign) VNConfidence minimumConfidence;

/*!
 @brief Specifies the maximum number of rectangles to be returned.  The default is 1.  Setting this property to 0 will allow an unlimited number of observations to be returned.
 */
@property (readwrite, nonatomic, assign) NSUInteger maximumObservations;


@end


API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
static const NSUInteger VNDetectRectanglesRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
