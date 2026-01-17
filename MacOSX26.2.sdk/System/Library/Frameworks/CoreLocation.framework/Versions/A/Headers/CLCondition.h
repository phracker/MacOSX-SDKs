//
//  CLCondition.h
//  CLCondition
//
//  Copyright (c) 2021 Apple Inc. All rights reserved.
//
#pragma once

#import <Foundation/Foundation.h>
#import <CoreLocation/CLAvailability.h>

#if ((defined(__MAC_OS_X_VERSION_MIN_REQUIRED) && \
			 __MAC_OS_X_VERSION_MIN_REQUIRED  >=    __MAC_14_0) || \
	(defined(__IPHONE_OS_VERSION_MIN_REQUIRED) && \
			 __IPHONE_OS_VERSION_MIN_REQUIRED >= __IPHONE_17_0) || \
	(defined(__TV_OS_VERSION_MIN_REQUIRED) && \
			 __TV_OS_VERSION_MIN_REQUIRED     >=   __TVOS_17_0) || \
	(defined(__WATCH_OS_VERSION_MIN_REQUIRED) && \
			 __WATCH_OS_VERSION_MIN_REQUIRED  >= __WATCHOS_10_0) || \
	(defined(__VISION_OS_VERSION_MIN_REQUIRED) && \
			 __VISION_OS_VERSION_MIN_REQUIRED  >= __VISIONOS_2_0)) //To prevent iPadOS apps from crashing in visionOS
#define CL_TARGET_SUPPORTS_CONDITIONS 1
#else
#define CL_TARGET_SUPPORTS_CONDITIONS 0
#endif

NS_ASSUME_NONNULL_BEGIN

CL_EXTERN

/*	Discussion:
 *		Abstract base class from which all other conditions are derived from.
 *
 *	Note:
 *		Do not derive from this class xor its subclasses. Passing instances
 *		custom conditions will result in unintended behavior.
 *
 */
NS_REFINED_FOR_SWIFT NS_SWIFT_SENDABLE
API_AVAILABLE(macos(14.0), ios(17.0)) API_UNAVAILABLE(watchos, tvos, visionos)
@interface CLCondition : NSObject<NSSecureCoding, NSCopying>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
