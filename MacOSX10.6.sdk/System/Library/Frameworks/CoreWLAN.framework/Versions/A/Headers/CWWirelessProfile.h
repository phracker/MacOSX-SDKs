/*!
 * @header CWWirelessProfile.h
 * @copyright 2009 Apple Inc. All rights reserved.
 * @updated 2009-05-20
 * @version 1.0.0
 */

#ifndef _CORE_WLAN_WIRELESS_PROFILE_H_
#define _CORE_WLAN_WIRELESS_PROFILE_H_

@class CW8021XProfile;

/*!
 * @class
 * @abstract CoreWLAN wireless profile.
 * @discussion Encapsulates a stored wireless profile entry.
 */
@interface CWWirelessProfile : NSObject <NSCopying, NSCoding>

/*!
 * @property
 * @abstract Wireless network name for the given CWWirelessProfile.
 */
@property(readwrite, copy) NSString *ssid __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Security mode for the given CWWirelessProfile.
 * @see //apple_ref/occ/tdef/CWSecurityMode CWSecurityMode
 */
@property(readwrite, retain) NSNumber *securityMode __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract The passphrase from the default login keychain for the given CWWirelessProfile.
 * @discussion This method may prompt the user to allow access to their default login keychain.
 */
@property(readwrite, copy) NSString *passphrase __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract User CW8021XProfile for the given CWWirelessProfile.
 */
@property(readwrite, retain) CW8021XProfile *user8021XProfile __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*! @methodgroup Getting a wireless profile */
/*!
 * @method
 * @result An CWWirelessProfile object.
 * @abstract Creates and returns an CWWirelessProfile.
 * @discussion This method is the designated initializer for the CWWirelessProfile class.
 */
- (CWWirelessProfile*)init __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @method
 * @result An CWWirelessProfile object.
 * @abstract Convenience method for getting an CWWirelessProfile object.
 */
+ (CWWirelessProfile*)profile __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*! @methodgroup Comparing wireless profiles */
/*!
 * @method
 * @param profile The CWWirelessProfile object for which to test equality.
 * @result <i>YES</i> if the objects are equal.
 * @abstract Method for determining CWWirelessProfile object equality.
 * @discussion Two CWWirelessProfile objects are considered equal if all their corresponding properties are equal. 
 */
- (BOOL)isEqualToProfile:(CWWirelessProfile*)profile __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );
@end

#endif /* _CORE_WLAN_WIRELESS_PROFILE_H_ */
