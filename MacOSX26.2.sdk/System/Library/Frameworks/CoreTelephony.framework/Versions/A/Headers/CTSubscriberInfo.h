/*
 *  CTSubscriberInfo.h
 *  CFTelephony
 *
 *  Copyright 2012 Apple, Inc. All rights reserved.
 *
 */

#ifdef __OBJC__

#import <Foundation/Foundation.h>
#import <CoreTelephony/CoreTelephonyDefines.h>

#import <CoreTelephony/CTSubscriber.h>

NS_ASSUME_NONNULL_BEGIN

CORETELEPHONY_CLASS_AVAILABLE(6_0) API_UNAVAILABLE(macCatalyst, watchos) API_UNAVAILABLE(macos, tvos)
@interface CTSubscriberInfo : NSObject

+ (NSArray<CTSubscriber *> *)subscribers
API_AVAILABLE(ios(12.1))
API_UNAVAILABLE(macCatalyst, watchos)
;

+ (CTSubscriber*) subscriber
API_DEPRECATED_WITH_REPLACEMENT("Use subscribers instead", ios(6.0, 12.1))
;

@end

NS_ASSUME_NONNULL_END

#endif // __OBJC__
