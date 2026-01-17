//
//  MLModelError.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString * const MLModelErrorDomain API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

typedef enum MLModelError : NSInteger {
    MLModelErrorGeneric = 0,
    MLModelErrorFeatureType = 1,
    MLModelErrorIO = 3,
    MLModelErrorCustomLayer API_AVAILABLE(macos(10.13.2), ios(11.2), watchos(4.2), tvos(11.2)) = 4,
    MLModelErrorCustomModel API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) = 5,
    MLModelErrorUpdate API_AVAILABLE(macos(10.15), ios(13.0)) = 6,
    MLModelErrorParameters API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0), tvos(13.0)) = 7,
} MLModelError API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

NS_ASSUME_NONNULL_END
