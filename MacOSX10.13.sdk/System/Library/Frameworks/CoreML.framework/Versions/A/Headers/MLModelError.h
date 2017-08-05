//
//  MLModelError.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

extern NSString * const MLModelErrorDomain API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

typedef enum MLModelError : NSInteger {
    MLModelErrorGeneric = 0,
    MLModelErrorFeatureType = 1,
    MLModelErrorIO = 3,
} MLModelError API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

NS_ASSUME_NONNULL_END
