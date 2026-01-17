/*!
 * @header CW8021XProfile.h
 * @copyright 2010 Apple Inc. All rights reserved.
 * @updated 2010-03-09
 * @version 1.0.0
 */

#ifndef _CORE_WLAN_8021X_PROFILE_H_
#define _CORE_WLAN_8021X_PROFILE_H_

#import <Foundation/Foundation.h>

/*!
 * @class
 * @abstract CoreWLAN 802.1X profile.
 * @discussion Encapsulates an 802.1X profile providing accessors to various profile properties.  The CW8021XProfile class is
 * deprecated, and will no longer function.
 */
@interface CW8021XProfile : NSObject <NSCopying, NSCoding> {
@private
    NSString *_userDefinedName;
    NSString *_ssid;
    NSString *_username;
    NSString *_password;
    BOOL _alwaysPromptForPassword;
}

/*!
 * @property
 * @abstract User-defined name.
 */
@property(readwrite, copy) NSString *userDefinedName NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @property
 * @abstract Wireless network name.
 */
@property(readwrite, copy) NSString *ssid NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @property
 * @abstract IEEE 802.1X username.
 */
@property(readwrite, copy) NSString *username NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @property
 * @abstract IEEE 802.1X password.
 */
@property(readwrite, copy) NSString *password NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @property
 * @abstract IEEE 802.1X client always prompts the user for the IEEE 802.1X password.
 */
@property BOOL alwaysPromptForPassword NS_DEPRECATED_MAC(10_6, 10_7);

/*! @methodgroup Getting an 802.1X profile */
/*!
 * @method
 * @result An CW8021XProfile object.
 * @abstract Creates and returns an CW8021XProfile object with default parameters.
 * @discussion The default EAP profile supports (in preferred order) TLS, PEAP, TTLS, and EAP-FAST.  The profile will conditionally 
 * support TLS only if their is a certificate available.  TTLS uses MSCHAPv2 inner authentication and EAP-FAST uses automatic 
 * PAC provisioning.  Support for more advanced EAP profile options may be added in a future implementation.  This method is the designated 
 * initializer for the CW8021XProfile class.
 */
- (CW8021XProfile*)init NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @method
 * @result An CW8021XProfile object with default parameters for the given network.
 * @abstract Convenience method for getting an CW8021XProfile object with default parameters.
 * @discussion The default EAP profile supports (in preferred order) TLS, PEAP, TTLS, and EAP-FAST.  The profile will conditionally 
 * support TLS only if their is a certificate available.  TTLS uses MSCHAPv2 inner authentication and EAP-FAST uses automatic 
 * PAC provisioning.  Support for more advanced EAP profile options may be added in a future implementation.
 */
+ (CW8021XProfile*)profile NS_DEPRECATED_MAC(10_6, 10_7);

/*! @methodgroup Comparing 802.1X profiles */
/*!
 * @method
 * @param profile The CW8021XProfile object for which to test equality.
 * @result <i>YES</i> if the objects are equal.
 * @abstract Method for determining CW8021XProfile object equality.
 * @discussion Two CW8021XProfile objects are considered equal if all their corresponding properties are equal. 
 */
- (BOOL)isEqualToProfile:(CW8021XProfile *)profile NS_DEPRECATED_MAC(10_6, 10_7);

/*! @methodgroup Getting all stored 802.1X user profiles */
/*!
 * @method
 * @result An NSArray object containing CW8021XProfile objects representing all stored 802.1X user profiles for the login user.
 * @abstract Retrieves the all the stored 802.1X profiles for the login user
 * @discussion If there are no 802.1X user profiles for the login user, then this method will return an empty NSArray object.    
 */
+ (NSArray*)allUser8021XProfiles NS_DEPRECATED_MAC(10_6, 10_7);
@end

#endif /* _CORE_WLAN_8021X_PROFILE_H_ */
