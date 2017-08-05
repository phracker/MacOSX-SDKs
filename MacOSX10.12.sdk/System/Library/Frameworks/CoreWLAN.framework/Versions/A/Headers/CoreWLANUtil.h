/*!
 * @header CoreWLANUtil.h
 * @copyright 2010-2014 Apple Inc. All rights reserved.
 */

#ifndef _CORE_WLAN_UTIL_H_
#define _CORE_WLAN_UTIL_H_

#import <Foundation/Foundation.h>

@class CWNetwork;

/*! @functiongroup Accessing Wi-Fi Keychain Items */
NS_ASSUME_NONNULL_BEGIN

/*!
 * @method
 *
 * @param domain 
 * The keychain domain, which determines which keychain will be used.
 *
 * @param ssid
 * The service set identifier (SSID) which is used to uniquely identify the keychain item.
 *
 * @param password 
 * An NSString passed by reference, which upon return will contain the Wi-Fi keychain password for the specified SSID.
 * This parameter is optional.
 *
 * @result
 * An OSStatus error code indicating whether or not a failure occurred.
 * <i>errSecSuccess</i> indicates no error occurred.
 *
 * @abstract 
 * Finds and returns (by reference) the password for the specified SSID and keychain domain.
 */
OSStatus CWKeychainFindWiFiPassword( CWKeychainDomain domain, NSData *ssid, NSString * __nullable * __nullable password ) NS_AVAILABLE_MAC(10_9);

/*!
 * @method
 *
 * @param domain 
 * The keychain domain, which determines which keychain will be used.
 *
 * @param ssid
 * The service set identifier (SSID) which is used to uniquely identify the keychain item.
 *
 * @param password 
 * The Wi-Fi network password.
 *
 * @result
 * An OSStatus error code indicating whether or not a failure occurred.
 * <i>errSecSuccess</i> indicates no error occurred.
 *
 * @abstract 
 * Sets the Wi-Fi network keychain password for the specified SSID and keychain domain.
 */
OSStatus CWKeychainSetWiFiPassword( CWKeychainDomain domain, NSData *ssid, NSString *password ) NS_AVAILABLE_MAC(10_9);

/*!
 * @method
 *
 * @param domain
 * The keychain domain, which determines which keychain will be used.
 *
 * @param ssid
 * The service set identifier (SSID) which is used to uniquely identify the keychain item.
 *
 * @result
 * An OSStatus error code indicating whether or not a failure occurred.
 * <i>errSecSuccess</i> indicates no error occurred.
 *
 * @abstract 
 * Deletes the password for the specified SSID and keychain domain.
 */
OSStatus CWKeychainDeleteWiFiPassword( CWKeychainDomain domain, NSData *ssid ) NS_AVAILABLE_MAC(10_9);

/*!
 * @method
 *
 * @param domain
 * The keychain domain, which determines which keychain will be used.
 *
 * @param ssid
 * The service set identifier (SSID) which is used to uniquely identify the keychain item.
 *
 * @param username 
 * An NSString passed by reference, which upon return will contain the 802.1X username for the specified SSID.
 * This parameter is optional.
 *
 * @param password
 * An NSString passed by reference, which upon return will contain the 802.1X password for the specified SSID.
 * This parameter is optional.
 *
 * @result
 * An OSStatus error code indicating whether or not a failure occurred.
 * <i>errSecSuccess</i> indicates no error occurred.
 *
 * @abstract 
 * Finds and returns the 802.1X username and password stored for the specified SSID and keychain domain.
 */
OSStatus CWKeychainFindWiFiEAPUsernameAndPassword( CWKeychainDomain domain, NSData *ssid, NSString * __nullable * __nullable username, NSString * __nullable * __nullable password ) NS_AVAILABLE_MAC(10_9);

/*!
 * @method
 *
 * @param domain
 * The keychain domain, which determines which keychain will be used.
 *
 * @param ssid
 * The service set identifier (SSID) which is used to uniquely identify the keychain item.
 *
 * @param username
 * The 802.1X username.
 *
 * @param password
 * The 802.1X password. This parameter is optional.
 *
 * @result
 * An OSStatus error code indicating whether or not a failure occurred.
 * <i>errSecSuccess</i> indicates no error occurred.
 *
 * @abstract 
 * Sets the 802.1X username and password for the specified SSID and keychain domain.
 */
OSStatus CWKeychainSetWiFiEAPUsernameAndPassword( CWKeychainDomain domain, NSData *ssid, NSString * __nullable username, NSString * __nullable password ) NS_AVAILABLE_MAC(10_9);

/*!
 * @method
 *
 * @param domain
 * The keychain domain, which determines which keychain will be used.
 *
 * @param ssid
 * The service set identifier (SSID) which is used to uniquely identify the keychain item.
 *
 * @result
 * An OSStatus error code indicating whether or not a failure occurred.
 * <i>errSecSuccess</i> indicates no error occurred.
 *
 * @abstract 
 * Deletes the 802.1X username and password for the specified SSID and keychain domain.
 */
OSStatus CWKeychainDeleteWiFiEAPUsernameAndPassword( CWKeychainDomain domain, NSData *ssid ) NS_AVAILABLE_MAC(10_9);

/*!
 * @method
 *
 * @param domain
 * The keychain domain, which determines which keychain will be used.
 *
 * @param ssid
 * The service set identifier (SSID) which is used to uniquely identify the keychain item.
 *
 * @param identity 
 * A SecIdentityRef passed by reference, which upon return will contain the SecIdentityRef associated with the specified SSID.
 * This parameter is optional.  The returned value must be released by the caller.
 *
 * @result
 * An OSStatus error code indicating whether or not a failure occurred.
 * <i>errSecSuccess</i> indicates no error occurred.
 *
 * @abstract 
 * Finds and returns the identity stored for the specified SSID and keychain domain.
 */
OSStatus CWKeychainCopyWiFiEAPIdentity( CWKeychainDomain domain, NSData *ssid, __nullable SecIdentityRef * __nullable identity ) NS_AVAILABLE_MAC(10_9);

/*!
 * @method
 *
 * @param domain
 * The keychain domain, which determines which keychain will be used.
 *
 * @param ssid
 * The service set identifier (SSID) which is used to uniquely identify the keychain item.
 *
 * @param identity 
 * The identity containing the certificate to use for 802.1X authentication.
 * Passing nil clears any identity association for the specified SSID.
 *
 * @result
 * An OSStatus error code indicating whether or not a failure occurred.
 * <i>errSecSuccess</i> indicates no error occurred.
 *
 * @abstract 
 * Associates an identity to the specified SSID and keychain domain.
 */
OSStatus CWKeychainSetWiFiEAPIdentity( CWKeychainDomain domain, NSData *ssid, __nullable SecIdentityRef identity ) NS_AVAILABLE_MAC(10_9);

/*!
 * @method
 *
 * @param identityList 
 * A CFArrayRef passed by reference, which upon return will be populated with a list of SecIdentityRef objects.
 * This parameter is optional.  The returned value must be released by the caller.
 *
 * @result
 * An OSStatus error code indicating whether or not a failure occurred.
 * <i>errSecSuccess</i> indicates no error occurred.
 *
 * @abstract 
 * Finds and returns all available identities.
 */
OSStatus CWKeychainCopyEAPIdentityList( __nullable CFArrayRef * __nullable list ) NS_AVAILABLE_MAC(10_7);

/*!
 * @method
 *
 * @param ssidData
 * The service set identifier (SSID) which is used to uniquely identify the keychain item.
 *
 * @param username
 * A CFStringRef passed by reference, which upon return will contain the 802.1X username for the specified SSID.
 * This parameter is optional.  The returned value must be released by the caller.
 *
 * @param password
 * A CFStringRef passed by reference, which upon return will contain the 802.1X password for the specified SSID.
 * This parameter is optional.  The returned value must be released by the caller.
 *
 * @result
 * An OSStatus error code indicating whether or not a failure occurred.
 * <i>errSecSuccess</i> indicates no error occurred.
 *
 * @abstract
 * Finds and returns the 802.1X username and password stored for the specified SSID.
 * The keychain used is determined by the SecPreferencesDomain of the caller as returned by SecKeychainGetPreferenceDomain().
 */
OSStatus CWKeychainCopyEAPUsernameAndPassword( CFDataRef ssidData, __nullable CFStringRef * __nullable username, __nullable CFStringRef * __nullable password ) NS_DEPRECATED_MAC(10_7, 10_9, "Use CWKeychainFindWiFiEAPUsernameAndPassword() instead");

/*!
 * @method
 *
 * @param ssidData
 * The service set identifier (SSID) which is used to uniquely identify the keychain item.
 *
 * @param username
 * The 802.1X username.
 *
 * @param password
 * The 802.1X password. This parameter is optional.
 *
 * @result
 * An OSStatus error code indicating whether or not a failure occurred.
 * <i>errSecSuccess</i> indicates no error occurred.
 *
 * @abstract
 * Sets the 802.1X username and password for the specified SSID.
 * The keychain used is determined by the SecPreferencesDomain of the caller as returned by SecKeychainGetPreferenceDomain().
 */
OSStatus CWKeychainSetEAPUsernameAndPassword( CFDataRef ssidData, __nullable CFStringRef username, __nullable CFStringRef password ) NS_DEPRECATED_MAC(10_7, 10_9, "Use CWKeychainSetWiFiEAPUsernameAndPassword() instead");

/*!
 * @method
 *
 * @param ssidData
 * The service set identifier (SSID) which is used to uniquely identify the keychain item.
 *
 * @result
 * An OSStatus error code indicating whether or not a failure occurred.
 * <i>errSecSuccess</i> indicates no error occurred.
 *
 * @abstract
 * Deletes the 802.1X username and password for the specified SSID.
 * The keychain used is determined by the SecPreferencesDomain of the caller as returned by SecKeychainGetPreferenceDomain().
 */
OSStatus CWKeychainDeleteEAPUsernameAndPassword( CFDataRef ssidData ) NS_DEPRECATED_MAC(10_7, 10_9, "Use CWKeychainDeleteWiFiEAPUsernameAndPassword() instead");

/*!
 * @method
 *
 * @param ssidData
 * The service set identifier (SSID) which is used to uniquely identify the keychain item.
 *
 * @param identity
 * A SecIdentityRef passed by reference, which upon return will contain the SecIdentityRef associated with the specified SSID.
 * This parameter is optional.  The returned value must be released by the caller.
 *
 * @result
 * An OSStatus error code indicating whether or not a failure occurred.
 * <i>errSecSuccess</i> indicates no error occurred.
 *
 * @abstract
 * Finds and returns the identity stored for the specified SSID and keychain domain.
 * The keychain used is determined by the SecPreferencesDomain of the caller as returned by SecKeychainGetPreferenceDomain().
 */
OSStatus CWKeychainCopyEAPIdentity( CFDataRef ssidData, __nullable SecIdentityRef * __nullable identity ) NS_DEPRECATED_MAC(10_7, 10_9, "Use CWKeychainCopyWiFiEAPIdentity() instead");

/*!
 * @method
 *
 * @param ssidData
 * The service set identifier (SSID) which is used to uniquely identify the keychain item.
 *
 * @param identity
 * The identity containing the certificate to use for 802.1X authentication.
 * Passing nil clears any identity association for the specified SSID.
 *
 * @result
 * An OSStatus error code indicating whether or not a failure occurred.
 * <i>errSecSuccess</i> indicates no error occurred.
 *
 * @abstract
 * Associates an identity to the specified SSID.
 * The keychain used is determined by the SecPreferencesDomain of the caller as returned by SecKeychainGetPreferenceDomain().
 */
OSStatus CWKeychainSetEAPIdentity( CFDataRef ssidData, __nullable SecIdentityRef identity ) NS_DEPRECATED_MAC(10_7, 10_9, "Use CWKeychainSetWiFiEAPIdentity() instead");

/*!
 * @method
 *
 * @param ssidData
 * The service set identifier (SSID) which is used to uniquely identify the keychain item.
 *
 * @param password
 * The Wi-Fi network password.
 *
 * @result
 * An OSStatus error code indicating whether or not a failure occurred.
 * <i>errSecSuccess</i> indicates no error occurred.
 *
 * @abstract
 * Sets the Wi-Fi network keychain password for the specified SSID.
 * The keychain used is determined by the SecPreferencesDomain of the caller as returned by SecKeychainGetPreferenceDomain().
 */
OSStatus CWKeychainSetPassword( CFDataRef ssidData, CFStringRef password ) NS_DEPRECATED_MAC(10_7, 10_9, "Use CWKeychainSetWiFiPassword() instead");

/*!
 * @method
 *
 * @param ssidData
 * The service set identifier (SSID) which is used to uniquely identify the keychain item.
 *
 * @param password
 * A CFStringRef passed by reference, which upon return will contain the Wi-Fi keychain password for the specified SSID.
 * This parameter is optional.  The returned value must be released by the caller.
 *
 * @result
 * An OSStatus error code indicating whether or not a failure occurred.
 * <i>errSecSuccess</i> indicates no error occurred.
 *
 * @abstract
 * Finds and returns (by reference) the password for the specified SSID.
 * The keychain used is determined by the SecPreferencesDomain of the caller as returned by SecKeychainGetPreferenceDomain().
 */
OSStatus CWKeychainCopyPassword( CFDataRef ssidData, __nullable CFStringRef * __nullable password ) NS_DEPRECATED_MAC(10_7, 10_9, "Use CWKeychainFindWiFiPassword() instead");

/*!
 * @method
 *
 * @param ssidData
 * The service set identifier (SSID) which is used to uniquely identify the keychain item.
 *
 * @result
 * An OSStatus error code indicating whether or not a failure occurred.
 * <i>errSecSuccess</i> indicates no error occurred.
 *
 * @abstract
 * Deletes the password for the specified SSID and keychain domain.
 * The keychain used is determined by the SecPreferencesDomain of the caller as returned by SecKeychainGetPreferenceDomain().
 */
OSStatus CWKeychainDeletePassword( CFDataRef ssidData ) NS_DEPRECATED_MAC(10_7, 10_9, "Use CWKeychainDeleteWiFiPassword() instead");

/*! @functiongroup Merging Scan Results */

/*!
 * @method
 *
 * @param networks 
 * The set of networks to merge.
 *
 * @abstract 
 * Merges the specified set of CWNetwork objects.
 *
 * @discussion 
 * Duplicate networks are defined as networks with the same SSID, security type, and BSS type (IBSS or Infrastructure).
 * When duplicate networks exist, the network with the best RSSI value will be chosen.
 */
NSSet<CWNetwork *> * CWMergeNetworks( NSSet<CWNetwork *> *networks ) NS_AVAILABLE_MAC(10_7);

NS_ASSUME_NONNULL_END

#endif /* _CORE_WLAN_UTIL_H_ */
