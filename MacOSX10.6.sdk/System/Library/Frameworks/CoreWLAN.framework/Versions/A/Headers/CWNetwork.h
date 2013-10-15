/*!
 * @header CWNetwork.h
 * @copyright 2009 Apple Inc. All rights reserved.
 * @version 1.0.0
 */

#ifndef _CORE_WLAN_NETWORK_H_
#define _CORE_WLAN_NETWORK_H_

@class CWWirelessProfile;

/*!
 * @class
 * @abstract CoreWLAN wireless (IEEE 802.11) network 
 * @discussion Encapsulates a wireless network providing read-only accessors to various properties of the network.
 */
@interface CWNetwork : NSObject <NSCopying, NSCoding> 

/*!
 * @property
 * @abstract Service set identifier for the given CWNetwork.
 */
@property(readonly) NSString *ssid __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Basic service set identifier for the given CWNetwork.
 */
@property(readonly) NSString *bssid __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Basic service set identifier for the given CWNetwork.
 */
@property(readonly) NSData *bssidData __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Security mode for the given CWNetwork.
 * @see //apple_ref/occ/tdef/CWSecurityMode CWSecurityMode
 */
@property(readonly) NSNumber *securityMode __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Physical layer mode for the given CWNetwork.
 * @see //apple_ref/occ/tdef/CWPHYMode CWPHYMode
 */
@property(readonly) NSNumber *phyMode __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Channel number for the given CWNetwork.
 */
@property(readonly) NSNumber *channel __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Aggregate RSSI value for the given CWNetwork.
 */
@property(readonly) NSNumber *rssi __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Aggregate noise value for the given CWNetwork.
 */
@property(readonly) NSNumber *noise __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Information element data included in beacon or probe response.
 */
@property(readonly) NSData *ieData __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Whether or not the given CWNetwork is a computer-to-computer network.
 */
@property(readonly) BOOL isIBSS __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*!
 * @property
 * @abstract Stored CWWirelessProfile for the given CWNetwork.
 */
@property(readonly) CWWirelessProfile *wirelessProfile __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );

/*! @methodgroup Comparing wireless networks */
/*!
 * @method
 * @param network The CWNetwork object for which to test equality.
 * @result <i>YES</i> if the objects are equal.
 * @abstract Method for determining CWNetwork object equality.
 * @discussion Two CWNetwork objects are considered equal if their corresponding <i>ssid</i>, <i>securityMode</i>, and
 * <i>isIBSS</i> properties are equal. 
 */
- (BOOL)isEqualToNetwork:(CWNetwork*)network __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_NA );
@end

#endif /* _CORE_WLAN_NETWORK_H_ */
