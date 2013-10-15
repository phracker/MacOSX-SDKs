/*!
 * @header CWConfiguration.h
 * @copyright 2010 Apple Inc. All rights reserved.
 * @updated 2010-03-09
 * @version 2.0.0
 */

#ifndef _CORE_WLAN_CONFIGURATION_H_
#define _CORE_WLAN_CONFIGURATION_H_

#import <Foundation/Foundation.h>

#pragma mark -
@class SFAuthorization, CWNetworkProfile;

/*!
 * @class
 * @abstract Encapsulates an immutable configuration for an AirPort WLAN interface. 
 */
@interface CWConfiguration : NSObject <NSCopying, NSMutableCopying, NSCoding> {	
@private
	NSDictionary *_info;
@protected
	NSOrderedSet *_networkProfiles;
	BOOL _rememberJoinedNetworks;
	BOOL _requireAdministratorForAssociation;
	BOOL _requireAdministratorForPower;
	BOOL _requireAdministratorForIBSSMode;
}

/*!
 * @property
 * @abstract An array of remembered CWNetworkProfile objects.
 * @discussion The order of this array corresponds to the order in which the the CWNetworkProfile 
 * objects participate in the auto-join process.
 */
@property(readonly, copy) NSOrderedSet *networkProfiles NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract Require an administrator password to change networks.
 */
@property(readonly, assign) BOOL requireAdministratorForAssociation NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract Require an administrator password to change the interface power state.
 */
@property(readonly, assign) BOOL requireAdministratorForPower NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract Require an administrator password to create a computer-to-computer network.
 */
@property(readonly, assign) BOOL requireAdministratorForIBSSMode NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract AirPort client will remember all joined networks.
 */
@property(readonly, assign) BOOL rememberJoinedNetworks NS_AVAILABLE_MAC(10_7);

/*! @methodgroup Creating a configuration */
/*!
 * @method
 * @abstract Convenience method for getting an empty CWConfiguration object.
 */
+ (id)configuration NS_AVAILABLE_MAC(10_6);

/*!
 * @method
 * @abstract Creates an empty CWConfiguration object.
 */
- (id)init NS_AVAILABLE_MAC(10_6);

/*!
 * @method
 * @param configuration The CWConfiguration object to use to initialize a new CWConfiguration object.
 * @result A CWConfiguration object.
 * @abstract Creates and returns a CWConfiguration object initialized with the given CWConfiguration object.
 */
- (id)initWithConfiguration:(CWConfiguration*)configuration NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 * @param configuration The CWConfiguration object to use to initialize a new CWConfiguration object.
 * @result A CWConfiguration object.
 * @abstract Convenience method for getting a CWConfiguration object initialized with the given CWConfiguration object.
 */
+ (id)configurationWithConfiguration:(CWConfiguration*)configuration NS_AVAILABLE_MAC(10_7);

/*! @methodgroup Comparing configurations */
/*!
 * @method
 * @param configuration The CWConfiguration object with which to compare the receiver.
 * @result <i>YES</i> if the objects are equal.
 * @abstract Determine CWConfiguration object equality.
 * @discussion CWConfiguration objects are considered equal if all their corresponding properties are equal. 
 */
- (BOOL)isEqualToConfiguration:(CWConfiguration*)configuration NS_AVAILABLE_MAC(10_6);
@end

#pragma mark -
/*!
 * @class
 * @abstract Encapsulates a mutable configuration for an AirPort WLAN interface. 
 */
@interface CWMutableConfiguration : CWConfiguration
@property(readwrite, copy) NSOrderedSet *networkProfiles NS_AVAILABLE_MAC(10_7);
@property(readwrite, assign) BOOL requireAdministratorForAssociation NS_AVAILABLE_MAC(10_7);
@property(readwrite, assign) BOOL requireAdministratorForPower NS_AVAILABLE_MAC(10_7);
@property(readwrite, assign) BOOL requireAdministratorForIBSSMode NS_AVAILABLE_MAC(10_7);
@property(readwrite, assign) BOOL rememberJoinedNetworks NS_AVAILABLE_MAC(10_7);
@end

#pragma mark -
@interface CWConfiguration (Deprecated)

/*!
 * @property
 * @abstract Array of stored CWWirelessProfile objects for the given CWConfiguration.
 */
@property(readwrite, copy) NSSet *rememberedNetworks NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @property
 * @abstract Ordered array of CWWirelessProfile objects.
 * @discussion The preferred networks list is a subset of the remembered networks set.  It cannot contain duplicate entries
 * and cannot contain any entries that are not present in the remembered networks set.
 */
@property(readwrite, copy) NSArray *preferredNetworks NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @property
 * @abstract Preference to always remember networks joined.
 */
@property(readwrite, assign) BOOL alwaysRememberNetworks NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @property
 * @abstract Preference to disconnect from the current network upon user logout.
 */
@property(readwrite, assign) BOOL disconnectOnLogout NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @property
 * @abstract Preference to require administrative privileges to change networks.
 */
@property(readwrite, assign) BOOL requireAdminForNetworkChange NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @property
 * @abstract Preference to require administrative privileges to change the CoreWLAN interface power state.
 */
@property(readwrite, assign) BOOL requireAdminForPowerChange NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @property
 * @abstract Preference to require administrative privileges to create computer-to-computer networks.
 */
@property(readwrite, assign) BOOL requireAdminForIBSSCreation NS_DEPRECATED_MAC(10_6, 10_7);
@end


#endif /* _CORE_WLAN_CONFIGURATION_H_ */
