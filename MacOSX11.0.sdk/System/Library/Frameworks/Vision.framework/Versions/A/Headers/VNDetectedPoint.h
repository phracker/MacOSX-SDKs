//
//  VNDetectedPoint.h
//  Vision
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Vision/VNGeometry.h>
#import <Vision/VNTypes.h>


NS_ASSUME_NONNULL_BEGIN


typedef NSString * VNRecognizedPointKey NS_STRING_ENUM;

typedef NSString * VNRecognizedPointGroupKey NS_STRING_ENUM;



/*!
 @class VNDetectedPoint
 @brief VNDetectedPoint is a VNPoint with a confidence value.
 @discussion It should be noted that VNDetectedPoint is not intended as an overall replacement of CGPoint, NSPoint or vec2, but is used by observations that detect points of interest.
 */
API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
@interface VNDetectedPoint : VNPoint

+ (instancetype) new NS_UNAVAILABLE;
- (instancetype) init NS_UNAVAILABLE;
- (instancetype) initWithX:(double)x y:(double)y NS_UNAVAILABLE;
- (instancetype) initWithLocation:(CGPoint)location NS_UNAVAILABLE;


/*!
@brief The confidence in the accuracy of the location, in the range of [0.0, 1.0].
*/
@property (readonly) VNConfidence confidence;

@end



/*!
 @class VNRecognizedPoint
 @brief An extension of VNDetectedPoint that associates an identifier to the point.
 @discussion It should be noted that VNRecognizedPoint is not intended as an overall replacement of CGPoint, NSPoint or vec2, but is used by observations that recognize labeled points of interest.
 */
API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
@interface VNRecognizedPoint : VNDetectedPoint

/*!
 @brief The is the identifier that provides context as to the kind of point that was recognized.
 @discussion The string is defined by the model that recognized the point. Usually these are technical labels that are not localized and not meant to be used directly to be presented to an end user in the UI.
 */
@property (readonly, copy) VNRecognizedPointKey identifier;

@end


NS_ASSUME_NONNULL_END
