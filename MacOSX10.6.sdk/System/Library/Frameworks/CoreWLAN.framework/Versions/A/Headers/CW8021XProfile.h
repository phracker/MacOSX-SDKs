/*!
 * @header CW8021XProfile.h
 * @copyright 2009 Apple Inc. All rights reserved.
 * @updated 2009-05-20
 * @version 1.0.0
 */

#ifndef _CORE_WLAN_8021X_PROFILE_H_
#define _CORE_WLAN_8021X_PROFILE_H_

/*!
 * @class
 * @abstract CoreWLAN 802.1X profile.
 * @discussion Encapsulates an 802.1X profile providing accessors to various profile properties.
 */
@interface CW8021XProfile : NSObject <NSCopying, NSCoding> 

/*!
 * @property
 * @abstract User-defined name.
 */
@property(readwrite, copy) NSString *userDefinedName __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Wireless network name.
 */
@property(readwrite, copy) NSString *ssid __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract IEEE 802.1X username.
 */
@property(readwrite, copy) NSString *username __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract IEEE 802.1X password.
 */
@property(readwrite, copy) NSString *password __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract IEEE 802.1X client always prompts the user for the IEEE 802.1X password.
 */
@property BOOL alwaysPromptForPassword __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

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
- (CW8021XProfile*)init __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @method
 * @result An CW8021XProfile object with default parameters for the given network.
 * @abstract Convenience method for getting an CW8021XProfile object with default parameters.
 * @discussion The default EAP profile supports (in preferred order) TLS, PEAP, TTLS, and EAP-FAST.  The profile will conditionally 
 * support TLS only if their is a certificate available.  TTLS uses MSCHAPv2 inner authentication and EAP-FAST uses automatic 
 * PAC provisioning.  Support for more advanced EAP profile options may be added in a future implementation.
 */
+ (CW8021XProfile*)profile __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*! @methodgroup Comparing 802.1X profiles */
/*!
 * @method
 * @param profile The CW8021XProfile object for which to test equality.
 * @result <i>YES</i> if the objects are equal.
 * @abstract Method for determining CW8021XProfile object equality.
 * @discussion Two CW8021XProfile objects are considered equal if all their corresponding properties are equal. 
 */
- (BOOL)isEqualToProfile:(CW8021XProfile *)profile __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*! @methodgroup Getting all stored 802.1X user profiles */
/*!
 * @method
 * @result An NSArray object containing CW8021XProfile objects representing all stored 802.1X user profiles for the login user.
 * @abstract Retrieves the all the stored 802.1X profiles for the login user
 * @discussion If there are no 802.1X user profiles for the login user, then this method will return an empty NSArray object.    
 */
+ (NSArray*)allUser8021XProfiles __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );
@end

#endif /* _CORE_WLAN_8021X_PROFILE_H_ */
