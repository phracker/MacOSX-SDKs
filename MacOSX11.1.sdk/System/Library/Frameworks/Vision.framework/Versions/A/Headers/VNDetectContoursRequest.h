//
//  VNDetectContoursRequest.h
//  Vision
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>


NS_ASSUME_NONNULL_BEGIN


/*!
 @brief A request that will detect the countours for the edges in an image.

 @discussion This request will produce a VNContoursObservation which describes the contours.
 */
API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
@interface VNDetectContoursRequest : VNImageBasedRequest

/*!
 @brief The amount to adjust the image's contrast by. Valid values are from [0.0 ... +3.0].
        A value of +1.0 means that the contrast is not adjusted. The default value is +2.0.
 @discussion Countour detection works best with high contrast images. The default value of 2 doubles the image's contrast to aid in detection. If the image already has a high contrast then this value should be set to 1.
*/
@property (readwrite, nonatomic) float contrastAdjustment;

/*!
 @brief Identifies to the request if detecting a dark object on a light background, or vice versa, to aid in detection. The default value is YES.
 */
@property (readwrite, nonatomic) BOOL detectsDarkOnLight;
@property (readwrite, nonatomic) BOOL detectDarkOnLight API_DEPRECATED_WITH_REPLACEMENT("use detectsDarkOnLight", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));

/*!
 @brief The limit on the maximum dimension of the image to be used for contour detection. Valid range of values is [64 ... NSUIntegerMax]. The default value is 512.
 @discussion As the contour request is compute intensive, the input image is scaled down maintaining aspect ratio (if needed), such that its maximum dimension is the value of this property. The image never gets scaled up, so specifying the maximum value ensures that the image gets processed in its original size and not downscaled.
 */
@property (readwrite, nonatomic) NSUInteger maximumImageDimension;

@end


API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
static const NSUInteger VNDetectContourRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
