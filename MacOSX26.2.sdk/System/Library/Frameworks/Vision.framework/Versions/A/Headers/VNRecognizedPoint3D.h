//
//  VNRecognizedPoint3D.h
//  Vision
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Vision/VNGeometry.h>
#import <Vision/VNTypes.h>

NS_ASSUME_NONNULL_BEGIN

/*!
    @class VNRecognizedPoint3D
    @brief An extension of VNPoint3D that associates an identifier to the point.
    @discussion It should be noted that VNRecognizedPoint3D is not intended as an overall replacement of simd float 4x4, but is used by observations that recognize labeled points of interest.
 */

API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0))
@interface VNRecognizedPoint3D : VNPoint3D

+ (instancetype) new NS_UNAVAILABLE;
- (instancetype) init NS_UNAVAILABLE;

/*!
    @brief The is the identifier that provides context as to the kind of point that was recognized.
    @discussion The string is defined by the model that recognized the point. Usually these are technical labels that are not localized and not meant to be used directly to be presented to an end user in the UI.
 */
@property (readonly, copy) VNRecognizedPointKey identifier;

@end

NS_ASSUME_NONNULL_END
