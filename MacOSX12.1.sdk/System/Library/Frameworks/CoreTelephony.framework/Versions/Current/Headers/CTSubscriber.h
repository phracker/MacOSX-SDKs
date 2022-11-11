/*
 *  CTSubscriber.h
 *  CoreTelephony
 *
 *  Copyright 2012 Apple, Inc.. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreTelephony/CoreTelephonyDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*
 * CTSubscriberTokenRefreshed
 *
 * Description:
 *     The name of the NSNotification sent when the carrier token is available.
 *     The `object' argument is set to the CTSubscriber instance for which the token was refreshed.
 */
CORETELEPHONY_EXTERN NSString * const CTSubscriberTokenRefreshed
API_UNAVAILABLE(macos)
API_DEPRECATED_WITH_REPLACEMENT("-[CTSubscriberDelegate subscriberTokenRefreshed:]", ios(7.0, 12.1))
;

@class CTSubscriber;

API_AVAILABLE(ios(12.1)) API_UNAVAILABLE(macCatalyst, watchos) API_UNAVAILABLE(macos, tvos)
@protocol CTSubscriberDelegate
- (void)subscriberTokenRefreshed:(CTSubscriber *)subscriber;
@end

CORETELEPHONY_CLASS_AVAILABLE(7_0) API_UNAVAILABLE(macCatalyst, watchos) API_UNAVAILABLE(macos, tvos)
@interface CTSubscriber : NSObject

/*
 * carrierToken
 *
 * Description:
 *     A data blob containing authorization information about the subscriber.
 *     This API is deprecated without replacement. Starting in iOS 11.3, this API returns nil.
 */
@property (nonatomic, readonly, retain, nullable) NSData* carrierToken
API_UNAVAILABLE(macos, watchos, tvos)
API_DEPRECATED("Deprecated; returns nil starting in iOS 11.3.", ios(7.0, 11.0))
;

/*
 * identifier
 *
 * Description:
 *     An implementation-defined identifier that can be used to correlate this CTSubscriber
 *     with information vended by other API's.
 *     The format of the identifier can change across software releases. Therefore, applications
 *     should not persist it.
 */

@property (nonatomic, readonly) NSString* identifier
API_UNAVAILABLE(macos, tvos)
API_AVAILABLE(ios(12.1))
API_UNAVAILABLE(macCatalyst, watchos)
;

@property (nonatomic, weak) id<CTSubscriberDelegate> delegate
API_UNAVAILABLE(macos, tvos)
API_AVAILABLE(ios(12.1))
API_UNAVAILABLE(macCatalyst, watchos)
;

@end

NS_ASSUME_NONNULL_END
