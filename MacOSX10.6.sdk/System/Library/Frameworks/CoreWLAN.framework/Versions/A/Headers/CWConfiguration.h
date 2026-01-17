/*!
 * @header CWConfiguration.h
 * @copyright 2009 Apple Inc. All rights reserved.
 * @updated 2009-05-20
 * @version 1.0.0
 */

#ifndef _CORE_WLAN_CONFIGURATION_H_
#define _CORE_WLAN_CONFIGURATION_H_

/*!
 * @class
 * @abstract CoreWLAN configuration. 
 * @discussion Encapsulates a static configuration for a given IEEE 802.11 wireless interface.
 */
@interface CWConfiguration : NSObject <NSCopying, NSCoding>

/*!
 * @property
 * @abstract Array of stored CWWirelessProfile objects for the given CWConfiguration.
 */
@property(readwrite, copy) NSSet *rememberedNetworks __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Ordered array of CWWirelessProfile objects.
 * @discussion The preferred networks list is a subset of the remembered networks set.  It cannot contain duplicate entries
 * and cannot contain any entries that are not present in the remembered networks set.
 */
@property(readwrite, copy) NSArray *preferredNetworks __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Preference to always remember networks joined.
 */
@property BOOL alwaysRememberNetworks __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Preference to disconnect from the current network upon user logout.
 */
@property BOOL disconnectOnLogout __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Preference to require administrative privileges to change networks.
 */
@property BOOL requireAdminForNetworkChange __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Preference to require administrative privileges to change the CoreWLAN interface power state.
 */
@property BOOL requireAdminForPowerChange __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Preference to require administrative privileges to create computer-to-computer networks.
 */
@property BOOL requireAdminForIBSSCreation __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*! @methodgroup Getting a configuration */
/*!
 * @method
 * @result A CWConfiguration object.
 * @abstract Creates and returns an CWConfiguration.
 * @discussion This method is the designated initializer for the CWConfiguration class.
 */
- (CWConfiguration*)init __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @method
 * @result A CWConfiguration object.
 * @abstract Convenience method for getting an CWConfiguration object.
 */
+ (CWConfiguration*)configuration __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*! @methodgroup Comparing configurations */
/*!
 * @method
 * @param configuration The CWConfiguration object for which to test equality.
 * @result <i>YES</i> if the objects are equal.
 * @abstract Method for determining CWConfiguration object equality.
 * @discussion Two CWConfiguration objects are considered equal if all their corresponding properties are equal. 
 */
- (BOOL)isEqualToConfiguration:(CWConfiguration*)configuration __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );
@end

#endif /* _CORE_WLAN_CONFIGURATION_H_ */
