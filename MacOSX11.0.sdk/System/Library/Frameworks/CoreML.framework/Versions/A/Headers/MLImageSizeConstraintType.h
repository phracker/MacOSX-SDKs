//
//  MLImageSizeConstraintType.h
//  CoreML
//
//  Copyright © 2018 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>


typedef NS_ENUM(NSInteger, MLImageSizeConstraintType) {

    MLImageSizeConstraintTypeUnspecified = 0,  // Any image size is allowed

    MLImageSizeConstraintTypeEnumerated = 2, // Limited to an enumerated set of image sizes

    MLImageSizeConstraintTypeRange = 3,      // Allow full width and height ranges

} API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

