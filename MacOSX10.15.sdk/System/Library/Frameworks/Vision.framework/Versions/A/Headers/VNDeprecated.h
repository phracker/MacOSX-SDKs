//
//  VNDetectAnimalRectanglesRequest.h
//  Vision
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Vision/VNDefines.h>


NS_ASSUME_NONNULL_BEGIN


typedef NSString *VNAnimalDetector NS_STRING_ENUM;

VN_EXPORT VNAnimalDetector const VNAnimalDetectorDog API_DEPRECATED_WITH_REPLACEMENT("Use VNRecognizeAnimalsRequest with VNAnimalIdentifierDog instead", macos(10.15, 10.15), ios(13.0, 13.0), tvos(13.0, 13.0));
VN_EXPORT VNAnimalDetector const VNAnimalDetectorCat API_DEPRECATED_WITH_REPLACEMENT("Use VNRecognizeAnimalsRequest with VNAnimalIdentifierCat instead", macos(10.15, 10.15), ios(13.0, 13.0), tvos(13.0, 13.0));


NS_ASSUME_NONNULL_END
