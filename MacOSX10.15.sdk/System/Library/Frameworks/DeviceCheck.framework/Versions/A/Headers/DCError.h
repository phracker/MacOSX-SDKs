//
//  DCError.h
//  DeviceCheck
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <DeviceCheck/DeviceCheck.h>

NS_ASSUME_NONNULL_BEGIN

extern NSErrorDomain const DCErrorDomain API_AVAILABLE(ios(11.0), macos(10.15), tvos(11.0)) API_UNAVAILABLE(watchos);

typedef NS_ERROR_ENUM(DCErrorDomain, DCError) {
    DCErrorUnknownSystemFailure,
    DCErrorFeatureUnsupported
} API_AVAILABLE(ios(11.0), macos(10.15), tvos(11.0)) API_UNAVAILABLE(watchos);

NS_ASSUME_NONNULL_END

