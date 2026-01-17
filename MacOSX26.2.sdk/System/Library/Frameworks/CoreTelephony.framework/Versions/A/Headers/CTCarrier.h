/*
 *  CTCarrier.h
 *  CoreTelephony
 *
 *  Copyright 2009 Apple, Inc.. All rights reserved.
 *
 */

#ifdef __OBJC__

#import <Foundation/Foundation.h>
#import <CoreTelephony/CoreTelephonyDefines.h>

NS_ASSUME_NONNULL_BEGIN

CORETELEPHONY_CLASS_DEPRECATED(4_0, 16_0, "Deprecated with no replacement")
@interface CTCarrier : NSObject

/*
 * carrierName
 *
 * Discussion:
 *   An NSString containing the name of the subscriber's cellular service provider.
 */
@property (nonatomic, readonly, retain, nullable) NSString *carrierName
API_UNAVAILABLE(macos, tvos)
API_DEPRECATED("Deprecated; returns '--' at some point in the future", ios(4.0, 16.0), watchos(3.0, 9.0))
;

/*
 * mobileCountryCode
 *
 * Discussion:
 *   An NSString containing the mobile country code for the subscriber's 
 *   cellular service provider, in its numeric representation
 */
@property (nonatomic, readonly, retain, nullable) NSString *mobileCountryCode
API_UNAVAILABLE(macos, tvos)
API_DEPRECATED("Deprecated; returns '65535' at some point in the future", ios(4.0, 16.0), watchos(3.0, 9.0))
;


/*
 * mobileNetworkCode
 *
 * Discussion:
 *   An NSString containing the  mobile network code for the subscriber's 
 *   cellular service provider, in its numeric representation
 */
@property (nonatomic, readonly, retain, nullable) NSString *mobileNetworkCode
API_UNAVAILABLE(macos, tvos)
API_DEPRECATED("Deprecated; returns '65535' at some point in the future", ios(4.0, 16.0), watchos(3.0, 9.0))
;


/*
 * isoCountryCode
 *
 * Discussion:
 *   Returns an NSString object that contains country code for
 *   the subscriber's cellular service provider, represented as an ISO 3166-1
 *   country code string
 */

@property (nonatomic, readonly, retain, nullable) NSString* isoCountryCode
API_UNAVAILABLE(macos, tvos)
API_DEPRECATED("Deprecated; returns '--' at some point in the future", ios(4.0, 16.0), watchos(3.0, 9.0))
;

/*
 * allowsVOIP
 *
 * Discussion:
 *   A BOOL value that is YES if this carrier allows VOIP calls to be
 *   made on its network, NO otherwise.
 */

@property (nonatomic, readonly, assign) BOOL allowsVOIP
API_UNAVAILABLE(macos, tvos)
API_DEPRECATED("Deprecated; returns YES at some point in the future", ios(4.0, 16.0), watchos(3.0, 9.0))
;

@end

NS_ASSUME_NONNULL_END

#endif // __OBJC__
