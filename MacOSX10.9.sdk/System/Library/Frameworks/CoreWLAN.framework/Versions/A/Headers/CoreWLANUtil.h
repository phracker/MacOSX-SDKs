/*!
 * @header CoreWLANUtil.h
 * @copyright 2010 Apple Inc. All rights reserved.
 * @updated 2010-03-09
 * @version 2.0.0
 */

#ifndef _CORE_WLAN_UTIL_H_
#define _CORE_WLAN_UTIL_H_

#import <Foundation/Foundation.h>

#pragma mark -
#pragma mark Keychain Methods
#pragma mark -

/*! @group Keychain Methods */

/*!
 * @method
 * @param domain The keychain domain, which determines which keychain will be used.
 * @param ssid The service set identifier.
 * @param password An NSString object passed by reference, which corresponds to the non-enterprise network password for the specified SSID.
 * @result An OSStatus error code which will indicate whether or not a failure occurred during execution.  <i>errSecSuccess</i> indicates no error occurred.
 * @abstract Finds and returns the password stored for the specified SSID and keychain domain.
 */
OSStatus CWKeychainFindWiFiPassword( CWKeychainDomain domain, NSData *ssid, NSString **password ) NS_AVAILABLE_MAC(10_9);

/*!
 * @method
 * @param domain The keychain domain, which determines which keychain will be used.
 * @param ssid The service set identifier.
 * @param password The network password.
 * @result An OSStatus error code which will indicate whether or not a failure occurred during execution.  <i>errSecSuccess</i> indicates no error occurred.
 * @abstract Sets the keychain password for the specified SSID and keychain domain.
 */
OSStatus CWKeychainSetWiFiPassword( CWKeychainDomain domain, NSData *ssid, NSString *password ) NS_AVAILABLE_MAC(10_9);

/*!
 * @method
 * @param domain The keychain domain, which determines which keychain will be used.
 * @param ssid The service set identifier.
 * @abstract Deletes the password for the specified SSID and keychain domain.
 */
OSStatus CWKeychainDeleteWiFiPassword( CWKeychainDomain domain, NSData *ssid ) NS_AVAILABLE_MAC(10_9);

/*!
 * @method
 * @param domain The keychain domain, which determines which keychain will be used.
 * @param ssid The service set identifier.
 * @param username An NSString object passed by reference, which corresponds to the 802.1X username for the specified SSID.
 * @param password An NSString object passed by reference, which corresponds to the 802.1X password for the specified SSID.
 * @result An OSStatus error code which will indicate whether or not a failure occurred during execution.  <i>errSecSuccess</i> indicates no error occurred.
 * @abstract Finds and returns the username and password stored for the specified SSID and keychain domain.
 */
OSStatus CWKeychainFindWiFiEAPUsernameAndPassword( CWKeychainDomain domain, NSData *ssid, NSString **username, NSString **password ) NS_AVAILABLE_MAC(10_9);

/*!
 * @method
 * @param domain The keychain domain, which determines which keychain will be used.
 * @param ssid The service set identifier.
 * @param username The 802.1X username.
 * @param password The 802.1X password.
 * @result An OSStatus error code which will indicate whether or not a failure occurred during execution.  <i>errSecSuccess</i> indicates no error occurred.
 * @abstract Sets the keychain item containing the 802.1X username and password for the specified SSID and keychain domain.
 */
OSStatus CWKeychainSetWiFiEAPUsernameAndPassword( CWKeychainDomain domain, NSData *ssid, NSString *username, NSString *password ) NS_AVAILABLE_MAC(10_9);

/*!
 * @method
 * @param domain The keychain domain, which determines which keychain will be used.
 * @param ssid The service set identifier.
 * @result An OSStatus error code which will indicate whether or not a failure occurred during execution.  <i>errSecSuccess</i> indicates no error occurred.
 * @abstract Deletes the keychain item containing the 802.1X username and password for the specified SSID and keychain domain.
 */
OSStatus CWKeychainDeleteWiFiEAPUsernameAndPassword( CWKeychainDomain domain, NSData *ssid ) NS_AVAILABLE_MAC(10_9);

/*!
 * @method
 * @param domain The keychain domain, which determines which keychain will be used.
 * @param ssid The service set identifier.
 * @param identity A SecIdentityRef object passed by reference, which contains the certificate to use for the specified SSID.
 * @result An OSStatus error code which will indicate whether or not a failure occurred during execution.  <i>errSecSuccess</i> indicates no error occurred.
 * @abstract Finds and returns the identity stored for the specified SSID and keychain domain.
 * @discussion If specified, the returned identity must be released by the caller.
 */
OSStatus CWKeychainCopyWiFiEAPIdentity( CWKeychainDomain domain, NSData *ssid, SecIdentityRef *identity ) NS_AVAILABLE_MAC(10_9);

/*!
 * @method
 * @param domain The keychain domain, which determines which keychain will be used.
 * @param ssid The service set identifier.
 * @param identity The identity containing the certificate to use for 802.1X authentication.
 * @result An OSStatus error code which will indicate whether or not a failure occurred during execution.  <i>errSecSuccess</i> indicates no error occurred.
 * @abstract Associates an exisiting identity item to the specified SSID for the specified keychain domain.
 * @discussion If the <i>identity</i> is <i>nil<i/> the method will disassociate the specified SSID from its current identity.
 */
OSStatus CWKeychainSetWiFiEAPIdentity( CWKeychainDomain domain, NSData *ssid, SecIdentityRef identity ) NS_AVAILABLE_MAC(10_9);

/*!
 * @method
 * @param ssid The service set identifier.
 * @param identityList An NSArray object passed by reference, which will be populated with SecIdentityRef objects.
 * @result An OSStatus error code which will indicate whether or not a failure occurred during execution.  <i>errSecSuccess</i> indicates no error occurred.
 * @abstract Finds and returns the available identities stored in the keychain.
 * @discussion If there are no available identities, this method will return <i>nil</i>.
 */
OSStatus CWKeychainCopyEAPIdentityList( CFArrayRef *list ) NS_DEPRECATED_MAC(10_7, 10_9);

/*!
 * @method
 * @param ssid The service set identifier.
 * @param username An NSString object passed by reference, which corresponds to the 802.1X username for the specified SSID.
 * @param password An NSString object passed by reference, which corresponds to the 802.1X password for the specified SSID.
 * @result An OSStatus error code which will indicate whether or not a failure occurred during execution.  <i>errSecSuccess</i> indicates no error occurred.
 * @abstract Finds and returns the username and password stored for the specified SSID and keychain domain.
 * @discussion If specified, the returned username and password must be released by the caller.
 */
OSStatus CWKeychainCopyEAPUsernameAndPassword( CFDataRef ssidData, CFStringRef *username, CFStringRef *password ) NS_DEPRECATED_MAC(10_7, 10_9);

/*!
 * @method
 * @param ssid The service set identifier.
 * @param username The 802.1X username.
 * @param password The 802.1X password.
 * @result An OSStatus error code which will indicate whether or not a failure occurred during execution.  <i>errSecSuccess</i> indicates no error occurred.
 * @abstract Sets the keychain item containing the 802.1X username and password for the specified SSID and keychain domain.
 */
OSStatus CWKeychainSetEAPUsernameAndPassword( CFDataRef ssidData, CFStringRef username, CFStringRef password ) NS_DEPRECATED_MAC(10_7, 10_9);

/*!
 * @method
 * @param domain The keychain domain, which determines which keychain will be used.
 * @param ssid The service set identifier.
 * @result An OSStatus error code which will indicate whether or not a failure occurred during execution.  <i>errSecSuccess</i> indicates no error occurred.
 * @abstract Deletes the keychain item containing the 802.1X username and password for the specified SSID and keychain domain.
 */
OSStatus CWKeychainDeleteEAPUsernameAndPassword( CFDataRef ssidData ) NS_DEPRECATED_MAC(10_7, 10_9);

/*!
 * @method
 * @param ssid The service set identifier.
 * @param identity A SecIdentityRef object passed by reference, which contains the certificate to use for the specified SSID.
 * @result An OSStatus error code which will indicate whether or not a failure occurred during execution.  <i>errSecSuccess</i> indicates no error occurred.
 * @abstract Finds and returns the identity stored for the specified SSID and keychain domain.
 * @discussion If specified, the returned identity must be released by the caller.
 */
OSStatus CWKeychainCopyEAPIdentity( CFDataRef ssidData, SecIdentityRef *identity ) NS_DEPRECATED_MAC(10_7, 10_9);

/*!
 * @method
 * @param ssid The service set identifier.
 * @param identity The identity containing the certificate to use for 802.1X authentication.
 * @result An OSStatus error code which will indicate whether or not a failure occurred during execution.  <i>errSecSuccess</i> indicates no error occurred.
 * @abstract Associates an exisiting identity item to the specified SSID for the specified keychain domain.
 * @discussion If the <i>identity</i> is <i>nil<i/> the method will disassociate the specified SSID from its current identity.
 */
OSStatus CWKeychainSetEAPIdentity( CFDataRef ssidData, SecIdentityRef identity ) NS_DEPRECATED_MAC(10_7, 10_9);

/*!
 * @method
 * @param ssid The service set identifier.
 * @param password The network password.
 * @result An OSStatus error code which will indicate whether or not a failure occurred during execution.  <i>errSecSuccess</i> indicates no error occurred.
 * @abstract Sets the keychain password for the specified SSID and keychain domain.
 */
OSStatus CWKeychainSetPassword( CFDataRef ssidData, CFStringRef password ) NS_DEPRECATED_MAC(10_7, 10_9);

/*!
 * @method
 * @param ssid The service set identifier.
 * @param password An NSString object passed by reference, which corresponds to the non-enterprise network password for the specified SSID.
 * @result An OSStatus error code which will indicate whether or not a failure occurred during execution.  <i>errSecSuccess</i> indicates no error occurred.
 * @abstract Finds and returns the password stored for the specified SSID and keychain domain.
 * @discussion If specified, the returned password must be released by the caller.
 */
OSStatus CWKeychainCopyPassword( CFDataRef ssidData, CFStringRef *password ) NS_DEPRECATED_MAC(10_7, 10_9);

/*!
 * @method
 * @param ssid The service set identifier.
 * @abstract Deletes the password for the specified SSID and keychain domain.
 */
OSStatus CWKeychainDeletePassword( CFDataRef ssidData ) NS_DEPRECATED_MAC(10_7, 10_9);

#pragma mark -
#pragma mark Utility Methods
#pragma mark -

/*! @group Merging Scan Results */

/*!
 * @method
 * @param networks The set of networks to merge.
 * @abstract Merges the specified set of CWNetwork objects.
 * @discussion Duplicate networks are defined as networks with the same SSID, security type, and BSS type.  
 * When duplicates are found, the network with the best RSSI value will remain.
 */
NSSet* CWMergeNetworks( NSSet *networks ) NS_AVAILABLE_MAC(10_7);

#endif /* _CORE_WLAN_UTIL_H_ */
