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
 */
CORETELEPHONY_EXTERN NSString * const CTSubscriberTokenRefreshed  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);

CORETELEPHONY_CLASS_AVAILABLE(7_0)
@interface CTSubscriber : NSObject

/*
 * carrierToken
 *
 * Description:
 *     A data blob containing authorization information about the subscriber.
 *     This API has been deprecated but continues to work as it did in iOS 10.
 *     In a future release, this API will only return nil.
 *
 *     May return nil if no token is available.
 */
@property (nonatomic, readonly, retain, nullable) NSData* carrierToken
__API_UNAVAILABLE(macos, watchos, tvos)
__API_DEPRECATED("Deprecated and will always return nil in a future release.", ios(7.0, 11.0))
;

@end

NS_ASSUME_NONNULL_END
