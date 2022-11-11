/*
 * Copyright (c) 2020-2021 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

NS_ASSUME_NONNULL_BEGIN

/*!
 * @typedef NEHotspotNetworkSecurityType
 * @abstract Wi-Fi network security type
 */
typedef NS_ENUM(NSInteger, NEHotspotNetworkSecurityType) {
	/*! @const NEHotspotNetworkSecurityTypeOpen Open security type */
	NEHotspotNetworkSecurityTypeOpen = 0,
	/*! @const NEHotspotNetworkSecurityTypeWEP WEP security type */
	NEHotspotNetworkSecurityTypeWEP = 1,
	/*! @const NEHotspotNetworkSecurityTypeWPA WPA/WPA2/WPA3 using pre-shared secret */
	NEHotspotNetworkSecurityTypePersonal = 2,
	/*! @const NEHotspotNetworkSecurityTypeEnterprise WPA/WPA2/WPA3 using enterprise level security */
	NEHotspotNetworkSecurityTypeEnterprise = 3,
	/*! @const NEHotspotNetworkSecurityTypeUnknown Unknown security type*/
	NEHotspotNetworkSecurityTypeUnknown = 4
} API_AVAILABLE(ios(15.0), watchos(8.0), macCatalyst(15.0)) API_UNAVAILABLE(macos, tvos);


/*!
 * @file NEHotspotNetwork.h
 * @discussion This file declares the NEHotspotNetwork API. The NEHotspotNetwork API is used to find SSID and BSSID of the current Wi-Fi network.
 */

/*!
 * @interface NEHotspotNetwork
 * @discussion
 *   The NEHotspotNetwork class provides a class method to get the SSID and BSSID of
 *   the current Wi-Fi network.
 *
 *   NEHotspotNetwork is part of NetworkExtension.framework
 */
API_AVAILABLE(ios(9.0), watchos(7.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos)
@interface NEHotspotNetwork : NSObject

/*!
 * @property SSID
 * @discussion The SSID of the Wi-Fi network.
 */
@property (readonly) NSString * SSID
API_AVAILABLE(ios(9.0), watchos(7.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 * @property BSSID
 * @discussion The BSSID of the Wi-Fi network.
 */
@property (readonly) NSString * BSSID
API_AVAILABLE(ios(9.0), watchos(7.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 * @property securityType
 * @discussion The security type of the Wi-Fi network.
 */
@property (readonly) NEHotspotNetworkSecurityType securityType
API_AVAILABLE(ios(15.0), watchos(8.0), macCatalyst(15.0)) API_UNAVAILABLE(macos, tvos);

/*!
 * @method fetchCurrentWithCompletionHandler:completionHandler:
 * @discussion This method returns SSID, BSSID and security type of the current Wi-Fi network when the
 *   requesting application meets one of following 4 requirements -.
 *   1. application is using CoreLocation API and has user's authorization to access precise location.
 *   2. application has used NEHotspotConfiguration API to configure the current Wi-Fi network.
 *   3. application has active VPN configurations installed.
 *   4. application has active NEDNSSettingsManager configuration installed.
 *   An application will receive nil if it fails to meet any of the above 4 requirements.
 *   An application will receive nil if does not have the "com.apple.developer.networking.wifi-info" entitlement.
 * @param completionHandler A block that will be executed when current Wi-Fi network details are
 *   obtained from the system. The NEHotspotNetwork object passed to this block will be nil if the requesting
 *   application fails to meet above requirements, non-nil otherwise. NEHotspotNetwork object contains only valid
 *   SSID, BSSID and security type values, when the block is passed non-nil object.This block is executed on application's
 *   main queue.
 */
+ (void)fetchCurrentWithCompletionHandler:(void (^)(NEHotspotNetwork * __nullable currentNetwork))completionHandler API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

@end

NS_ASSUME_NONNULL_END
