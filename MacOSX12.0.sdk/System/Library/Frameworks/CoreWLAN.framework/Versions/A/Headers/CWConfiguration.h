/*!
 * @header CWConfiguration.h
 * @copyright 2009-2014 Apple Inc. All rights reserved.
 */

#ifndef _CORE_WLAN_CONFIGURATION_H_
#define _CORE_WLAN_CONFIGURATION_H_

#import <Foundation/Foundation.h>

@class CWNetworkProfile;

/*!
 * @class
 *
 * @abstract 
 * Encapsulates the system configuration for a given Wi-Fi interface.
 *
 * @discussion
 * The CWConfiguration class contains basic network configuration settings and also the list of preferred networks.
 * CWConfiguration is an immutable object. For changing configuration settings and/or the preferred networks list, see CWMutableConfiguration.
 */
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE_MAC(10_6)
@interface CWConfiguration : NSObject <NSCopying, NSMutableCopying, NSSecureCoding>
{
    @private
	
        NSDictionary    *_info;
	
        NSOrderedSet<CWNetworkProfile *>    *_networkProfiles;
    
        BOOL            _rememberJoinedNetworks;
    
        BOOL            _requireAdministratorForAssociation;
    
        BOOL            _requireAdministratorForPower;
    
        BOOL            _requireAdministratorForIBSSMode;
}

/*!
 * @property
 *
 * @result
 * An NSOrderedSet of CWNetworkProfile objects.
 *
 * @abstract
 * Returns the preferred networks list.
 *
 * @discussion 
 * The order of the ordered set corresponds to the order the preferred networks list.
 */
@property(readonly, copy) NSOrderedSet<CWNetworkProfile *> *networkProfiles NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 *
 * @result
 * YES if the preference is enabled, NO otherwise.
 *
 * @abstract 
 * Returns the preference to require an administrator password to change networks.
 *
 * @discussion
 * If YES, the user may be prompted to enter an administrator password upon attempting to join a Wi-Fi network.
 * This preference is enforced at the API layer.
 */
@property(readonly) BOOL requireAdministratorForAssociation NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 *
 * @result
 * YES if the preference is enabled, NO otherwise.
 *
 * @abstract 
 * Returns the preference to require an administrator password to change the interface power state.
 *
 * @discussion
 * If YES, the user may be prompted to enter an administrator password upon attempting to turn Wi-Fi on or off.
 * This preference is enforced at the API layer.
 */
@property(readonly) BOOL requireAdministratorForPower NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 *
 * @result
 * YES if the preference is enabled, NO otherwise.
 *
 * @abstract
 * Returns the preference to require an administrator password to create a computer-to-computer network.
 *
 * @discussion
 * If YES, the user may be prompted to enter an administrator password upon attempting to create an IBSS network.
 * This preference is enforced at the API layer.
 */
@property(readonly) BOOL requireAdministratorForIBSSMode NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 *
 * @result
 * YES if the preference is enabled, NO otherwise.
 *
 * @abstract
 * Returns the preference to remember all Wi-Fi networks joined unless otherwise specified by the user when joining a particular Wi-Fi network.
 */
@property(readonly) BOOL rememberJoinedNetworks NS_AVAILABLE_MAC(10_7);

/*! @functiongroup Creating a Wi-Fi Configuration */

/*!
 * @method
 *
 * @abstract 
 * Convenience method for getting a CWConfiguration object.
 */
+ (instancetype)configuration NS_AVAILABLE_MAC(10_6);

/*!
 * @method
 *
 * @abstract 
 * Initializes a CWConfiguration object.
 */
- (instancetype)init NS_AVAILABLE_MAC(10_6);

/*!
 * @method
 *
 * @param configuration 
 * A CWConfiguration object.
 *
 * @result 
 * A CWConfiguration object.
 *
 * @abstract 
 * Initializes a CWConfiguration object with the properties of an existing CWConfiguration object.
 */
- (instancetype)initWithConfiguration:(CWConfiguration *)configuration NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 *
 * @param configuration
 * A CWConfiguration object.
 *
 * @result
 * A CWConfiguration object.
 *
 * @abstract
 * Convenience method for getting a CWConfiguration object initialized with the properties of an existing CWConfiguration object.
 */
+ (instancetype)configurationWithConfiguration:(CWConfiguration *)configuration NS_AVAILABLE_MAC(10_7);

/*! @functiongroup Comparing Wi-Fi Configurations */

/*!
 * @method
 *
 * @param configuration 
 * The CWConfiguration with which to compare the receiver.
 *
 * @result 
 * YES if the objects are equal, NO otherwise.
 *
 * @abstract 
 * Determine CWConfiguration equality.
 *
 * @discussion 
 * CWConfiguration objects are considered equal if all their corresponding properties are equal.
 */
- (BOOL)isEqualToConfiguration:(CWConfiguration *)configuration NS_AVAILABLE_MAC(10_6);

@end

/*!
 * @class
 *
 * @abstract
 * Mutable subclass of CWConfiguration.  Use this class for changing configuration settings and/or the preferred networks list.
 *
 * @discussion
 * To commit configuration changes, use -[CWInterface commitConfiguration:authorization:error:].
 */
NS_CLASS_AVAILABLE_MAC(10_6)
@interface CWMutableConfiguration : CWConfiguration

/*!
 * @property
 *
 * @abstract
 * Add, remove, or update the preferred networks list.
 */
@property(copy) NSOrderedSet<CWNetworkProfile *> *networkProfiles NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 *
 * @abstract
 * Set the preference to require an administrator password to change networks.
 */
@property BOOL requireAdministratorForAssociation NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 *
 * @abstract
 * Set the preference to require an administrator password to change the interface power state.
 */
@property BOOL requireAdministratorForPower NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 *
 * @abstract
 * Set the preference to require an administrator password to change networks.
 */
@property BOOL requireAdministratorForIBSSMode NS_DEPRECATED_MAC(10_7, 11_0);


/*!
 * @property
 *
 * @abstract
 * Set the preference to require an administrator password to create a computer-to-computer network.
 */
@property BOOL rememberJoinedNetworks NS_AVAILABLE_MAC(10_7);

@end
NS_ASSUME_NONNULL_END

#endif /* _CORE_WLAN_CONFIGURATION_H_ */
