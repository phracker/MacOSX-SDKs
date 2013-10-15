/*!
 * @header CWWirelessProfile.h
 * @copyright 2010 Apple Inc. All rights reserved.
 * @updated 2010-03-09
 * @version 1.0.0
 */

#ifndef _CORE_WLAN_WIRELESS_PROFILE_H_
#define _CORE_WLAN_WIRELESS_PROFILE_H_

#import <Foundation/Foundation.h>

@class CW8021XProfile, CWMutableNetworkProfile;

/*!
 * @class
 * @abstract CoreWLAN wireless profile.
 * @discussion Encapsulates a stored wireless profile entry.
 */
@interface CWWirelessProfile : NSObject <NSCopying, NSCoding> {
@private
    CWMutableNetworkProfile *_networkProfile;
}


/*!
 * @property
 * @abstract Wireless network name for the given CWWirelessProfile.
 */
@property(readwrite, copy) NSString *ssid NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @property
 * @abstract Security mode for the given CWWirelessProfile.
 */
@property(readwrite, retain) NSNumber *securityMode NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @property
 * @abstract The passphrase from the default login keychain for the given CWWirelessProfile.
 * @discussion This method may prompt the user to allow access to their default login keychain.
 */
@property(readwrite, copy) NSString *passphrase NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @property
 * @abstract User CW8021XProfile for the given CWWirelessProfile.
 */
@property(readwrite, retain) CW8021XProfile *user8021XProfile NS_DEPRECATED_MAC(10_6, 10_7);

/*! @methodgroup Getting a wireless profile */
/*!
 * @method
 * @result An CWWirelessProfile object.
 * @abstract Creates and returns an CWWirelessProfile.
 * @discussion This method is the designated initializer for the CWWirelessProfile class.
 */
- (CWWirelessProfile*)init NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @method
 * @result An CWWirelessProfile object.
 * @abstract Convenience method for getting an CWWirelessProfile object.
 */
+ (CWWirelessProfile*)profile NS_DEPRECATED_MAC(10_6, 10_7);

/*! @methodgroup Comparing wireless profiles */
/*!
 * @method
 * @param profile The CWWirelessProfile object for which to test equality.
 * @result <i>YES</i> if the objects are equal.
 * @abstract Method for determining CWWirelessProfile object equality.
 * @discussion Two CWWirelessProfile objects are considered equal if all their corresponding properties are equal. 
 */
- (BOOL)isEqualToProfile:(CWWirelessProfile*)profile NS_DEPRECATED_MAC(10_6, 10_7);
@end

#endif /* _CORE_WLAN_WIRELESS_PROFILE_H_ */
