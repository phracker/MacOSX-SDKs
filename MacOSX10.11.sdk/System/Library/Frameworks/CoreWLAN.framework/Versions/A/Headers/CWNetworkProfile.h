/*!
 * @header CWNetworkProfile.h
 * @copyright 2010-2014 Apple Inc. All rights reserved.
 */

#ifndef _CORE_WLAN_NETWORK_PROFILE_H_
#define _CORE_WLAN_NETWORK_PROFILE_H_

#import <Foundation/Foundation.h>
#import <CoreWLAN/CoreWLANTypes.h>

/*!
 * @class
 *
 * @abstract 
 * Encapsulates a preferred network entry.
 */
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE_MAC(10_7)
@interface CWNetworkProfile : NSObject <NSCopying, NSMutableCopying, NSSecureCoding>
{
	NSData          *_ssidData;
    
    NSString        *_ssid;
	
    NSUInteger      _securityType;
	
    BOOL            _disabled;
	
    BOOL            _systemMode;
	
    BOOL            _hiddenNetwork;
	
    NSDate          *_lastConnected;
	
    BOOL            _captiveNetwork;
	
    BOOL            _temporarilyDisabled;
    
    BOOL            _autoLogin;
    
    BOOL            _isPasspoint;
    
    NSString        *_domainName;
    
    NSString        *_displayName;
    
    NSArray         *_roamingConsortiumList;
    
    NSArray         *_naiRealmList;
    
    BOOL            _isServiceProviderRoamingEnabled;
    
    BOOL            _possiblyHiddenNetwork;
    
    NSSet           *_collocatedGroup;
    
    NSSet           *_channelHistory;
        
    NSInteger       _roamingProfileType;
    
    BOOL            _isPersonalHotspot;
}

/*!
 * @property
 *
 * @abstract 
 * Returns the service set identifier (SSID) for the Wi-Fi network profile, encoded as a string.
 *
 * @discussion 
 * Returns nil if the SSID can not be encoded as a valid UTF-8 or WinLatin1 string.
 */
@property(readonly, copy, nullable) NSString *ssid NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 *
 * @abstract 
 * Returns the service set identifier (SSID) for the Wi-Fi network profile, encapsulated in an NSData object.
 *
 * @discussion
 * The SSID is 1-32 octets.
 */
@property(readonly, copy, nullable) NSData *ssidData NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 *
 * @abstract 
 * Returns the security type of the Wi-Fi network profile.
 */
@property(readonly) CWSecurity security NS_AVAILABLE_MAC(10_7);

/*! @functiongroup Creating a Network Profile */

/*!
 * @method
 *
 * @abstract 
 * Convenience method for getting a CWNetworkProfile object.
 */
+ (instancetype)networkProfile NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 *
 * @abstract 
 * Initializes a CWNetworkProfile object.
 */
- (instancetype)init NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 *
 * @param networkProfile 
 * A CWNetworkProfile object.
 *
 * @result 
 * A CWNetworkProfile object.
 *
 * @abstract 
 * Initializes a CWNetworkProfile object with the properties of an existing CWNetworkProfile object.
 */
- (instancetype)initWithNetworkProfile:(CWNetworkProfile *)networkProfile NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 *
 * @param networkProfile
 * A CWNetworkProfile object.
 *
 * @result
 * A CWNetworkProfile object.
 *
 * @abstract
 * Convenience method for getting a CWNetworkProfile object initialized with the properties of an existing CWNetworkProfile object.
 */
+ (instancetype)networkProfileWithNetworkProfile:(CWNetworkProfile *)networkProfile NS_AVAILABLE_MAC(10_7);

/*! @functiongroup Comparing Network Profiles */

/*!
 * @method
 *
 * @param network
 * A CWNetworkProfile object.
 *
 * @result
 * YES if the objects are equal, NO otherwise.
 *
 * @abstract
 * Determine CWNetworkProfile equality.
 *
 * @discussion
 * CWNetworkProfile objects are considered equal if their corresponding <i>ssidData</i> and <i>security</i> properties are equal.
 */
- (BOOL)isEqualToNetworkProfile:(CWNetworkProfile *)networkProfile NS_AVAILABLE_MAC(10_7);

@end

/*!
 * @class
 *
 * @abstract
 * Mutable subclass of CWNetworkProfile.  Use this class for changing profile properties.
 *
 * @discussion
 * To commit Wi-Fi network profile changes, use -[CWMutableConfiguration setNetworkProfiles:] and 
 * -[CWInterface commitConfiguration:authorization:error:].
 */
NS_CLASS_AVAILABLE_MAC(10_7)
@interface CWMutableNetworkProfile : CWNetworkProfile

/*!
 * @property
 *
 * @abstract
 * Set the service set identifier (SSID).
 */
@property(copy) NSData *ssidData NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 *
 * @abstract
 * Set the security type.
 */
@property CWSecurity security NS_AVAILABLE_MAC(10_7);

@end
NS_ASSUME_NONNULL_END

#endif /* _CORE_WLAN_NETWORK_PROFILE_H_ */
