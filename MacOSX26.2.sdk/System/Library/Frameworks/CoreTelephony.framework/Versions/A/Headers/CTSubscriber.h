/*
 *  CTSubscriber.h
 *  CoreTelephony
 *
 *  Copyright 2012 Apple, Inc.. All rights reserved.
 *
 */

#ifdef __OBJC__

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
 *     This method is only available to carrier apps with suitable entitlements.
 *     A data blob containing authorization information about the subscriber.
 */
@property (nonatomic, readonly, retain, nullable) NSData* carrierToken
API_UNAVAILABLE(macos, tvos, visionos)
API_AVAILABLE(ios(7.0), watchos(26.0))
;

/*
 * refreshCarrierToken
 *
 * Description:
 *     This method is only available to carrier apps with suitable entitlements.
 *     If the carrier token does exist but is declined by the server, then the token
 *     may be updated using this method. As a general rule, retrieve the carrierToken first.
 *     A refresh should only be done when that information is known to be incorrect.
 *
 *     If the refresh will be performed, this function will return YES and the
 *     subscriberTokenRefreshed(_:) delegate method will be called.
 *     If the request to refresh fails due to invalid argument (bad carrier descriptors or invalid service descriptor)
 *     or subscriber does not support the authentication action, this function will return NO.
 */
- (BOOL)refreshCarrierToken
API_UNAVAILABLE(macos, tvos, visionos)
API_AVAILABLE(ios(6.0),watchos(26.0))
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

/*
 * SIMInserted
 *
 * Description
 *     Returns whether or not the SIM matching the Info.plist carrier information (MCC / MNC / GIDs) is currently inserted in the associated descriptor
*/
@property(readonly, getter=isSIMInserted) BOOL SIMInserted
API_UNAVAILABLE(macos, tvos, visionos)
API_AVAILABLE(ios(18.0), watchos(11.0))
API_UNAVAILABLE(macCatalyst)
;

@property (nonatomic, weak) id<CTSubscriberDelegate> delegate
API_UNAVAILABLE(macos, tvos)
API_AVAILABLE(ios(12.1))
API_UNAVAILABLE(macCatalyst, watchos)
;

@end

NS_ASSUME_NONNULL_END

#endif // __OBJC__
