/*!
 * @header CWNetwork.h
 * @copyright 2010 Apple Inc. All rights reserved.
 * @updated 2010-03-09
 * @version 2.0.0
 */

#ifndef _CORE_WLAN_NETWORK_H_
#define _CORE_WLAN_NETWORK_H_

#import <Foundation/Foundation.h>
#import <CoreWLAN/CoreWLANTypes.h>

#pragma mark -
@class CWChannel;

/*!
 * @class
 * @abstract Encapsulates an IEEE 802.11 network, providing read-only accessors to various properties of the network.
 */
@interface CWNetwork : NSObject <NSCopying, NSCoding> {
@private
	NSDictionary *_scanRecord;
}

/*!
 * @property
 * @abstract The service set identifier (SSID) for the network, encoded as a string.
 * @discussion If the SSID can not be encoded as a valid UTF-8 or WinLatin1 string, this method returns <i>nil</i>.
 */
@property(readonly) NSString *ssid NS_AVAILABLE_MAC(10_6);

/*!
 * @property
 * @abstract The service set identifier (SSID) for the network, returned as data.
 * @discussion The SSID is defined as 1-32 octets.
 */
@property(readonly) NSData *ssidData NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract The basic service set identifier (BSSID) for the network, returned as UTF-8 string. 
 * @discussion  Returns a UTF-8 string formatted as <00:00:00:00:00:00>.
 */
@property(readonly) NSString *bssid NS_AVAILABLE_MAC(10_6);

/*!
 * @property
 * @abstract The channel for the network.
 */
@property(readonly) CWChannel *wlanChannel NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract The aggregate received signal strength indication (RSSI) measurement (dBm) for the network.
 */
@property(readonly) NSInteger rssiValue NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract The aggregate noise measurement (dBm) for the network.
 */
@property(readonly) NSInteger noiseMeasurement NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract Information element data included in beacon or probe response frames.
 */
@property(readonly) NSData *informationElementData NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract The country code (ISO/IEC 3166-1:1997) for the network.
 */
@property(readonly) NSString *countryCode NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract The beacon interval (ms) for the network.
 */
@property(readonly) NSUInteger beaconInterval NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 * @abstract The network is an IBSS network.
 */
@property(readonly) BOOL ibss NS_AVAILABLE_MAC(10_7);

/*! @methodgroup Comparing wireless networks */
/*!
 * @method
 * @param network The CWNetwork object for which to test equality.
 * @result <i>YES</i> if the objects are equal.
 * @abstract Method for determining CWNetwork object equality.
 * @discussion Two CWNetwork objects are considered equal if their corresponding <i>ssidData</i>, <i>securityType</i>, and
 * <i>networkType</i> properties are equal. 
 */
- (BOOL)isEqualToNetwork:(CWNetwork*)network NS_AVAILABLE_MAC(10_6);

/*! @methodgroup Getting supported security types */
/*!
 * @method
 * @param security The security type.
 * @result <i>YES</i> if the network supports the specified security type.
 * @abstract Method for determining which security types a network supports.
 */
- (BOOL)supportsSecurity:(CWSecurity)security;

/*! @methodgroup Getting supported PHY modes */
/*!
 * @method
 * @param security The PHY mode.
 * @result <i>YES</i> if the network supports the specified PHY mode.
 * @abstract Method for determining which PHY modes a network supports.
 */
- (BOOL)supportsPHYMode:(CWPHYMode)phyMode;
@end

#pragma mark -
@class CWWirelessProfile;
@interface CWNetwork (Deprecated)

/*!
 * @property
 * @abstract Security mode for the given CWNetwork.
 * @see //apple_ref/occ/tdef/CWSecurityMode CWSecurityMode
 */

@property(readonly) NSNumber *securityMode NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @property
 * @abstract Physical layer mode for the given CWNetwork.
 * @see //apple_ref/occ/tdef/CWPHYMode CWPHYMode
 */
@property(readonly) NSNumber *phyMode NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @property
 * @abstract Channel number for the given CWNetwork.
 */
@property(readonly) NSNumber *channel NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @property
 * @abstract Aggregate RSSI value for the given CWNetwork.
 */
@property(readonly) NSNumber *rssi NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @property
 * @abstract Aggregate noise value for the given CWNetwork.
 */
@property(readonly) NSNumber *noise NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @property
 * @abstract Information element data included in beacon or probe response.
 */
@property(readonly) NSData *ieData NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @property
 * @abstract Whether or not the given CWNetwork is a computer-to-computer network.
 */
@property(readonly) BOOL isIBSS NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @property
 * @abstract Basic service set identifier for the given CWNetwork.
 */
@property(readonly) NSData *bssidData NS_DEPRECATED_MAC(10_6, 10_7);

/*!
 * @property
 * @abstract Stored CWWirelessProfile for the given CWNetwork.
 */
@property(readonly) CWWirelessProfile *wirelessProfile NS_DEPRECATED_MAC(10_6, 10_7);
@end

#endif /* _CORE_WLAN_NETWORK_H_ */
