/*!
 * @header CWNetwork.h
 * @copyright 2009-2014 Apple Inc. All rights reserved.
 */

#ifndef _CORE_WLAN_NETWORK_H_
#define _CORE_WLAN_NETWORK_H_

#import <Foundation/Foundation.h>
#import <CoreWLAN/CoreWLANTypes.h>

NS_ASSUME_NONNULL_BEGIN
@class CWChannel;

/*!
 * @class
 *
 * @abstract 
 * Represents a device participating in a Wi-Fi network, providing accessors to various network attributes.
 */
NS_CLASS_AVAILABLE_MAC(10_6)
@interface CWNetwork : NSObject <NSCopying, NSSecureCoding>
{
    @private
	
        NSDictionary *_scanRecord;
}

/*!
 * @property
 *
 * @abstract
 * Returns the service set identifier (SSID) for the Wi-Fi network device, encoded as a string.
 *
 * @discussion
 * Returns nil if the SSID can not be encoded as a valid UTF-8 or WinLatin1 string.
 */
@property(readonly, nullable) NSString *ssid NS_AVAILABLE_MAC(10_6);


/*!
 * @property
 *
 * @abstract 
 * Returns the service set identifier (SSID) for the Wi-Fi network device, encapsulated in an NSData object.
 *
 * @discussion
 * The SSID is defined as 1-32 octets.
 */
@property(readonly, nullable) NSData *ssidData NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 *
 * @abstract 
 * Returns the basic service set identifier (BSSID) for the Wi-Fi network device, returned as UTF-8 string.
 *
 * @discussion
 * Returns a UTF-8 string using hexadecimal characters formatted as XX:XX:XX:XX:XX:XX.
 */
@property(readonly, nullable) NSString *bssid NS_AVAILABLE_MAC(10_6);

/*!
 * @property
 *
 * @abstract 
 * The operating channel of the Wi-Fi device.
 */
@property(readonly) CWChannel *wlanChannel NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 *
 * @abstract 
 * Returns the received signal strength indication (RSSI) measurement (dBm) for the Wi-Fi device.
 */
@property(readonly) NSInteger rssiValue NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 *
 * @abstract 
 * Returns the noise measurement (dBm) for the Wi-Fi device.
 */
@property(readonly) NSInteger noiseMeasurement NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 *
 * @abstract 
 * Returns information element data included in beacon or probe response frames.
 */
@property(readonly, nullable) NSData *informationElementData NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 *
 * @abstract 
 * Returns the advertised country code (ISO/IEC 3166-1:1997) for the Wi-Fi device.
 */
@property(readonly, nullable) NSString *countryCode NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 *
 * @abstract
 * Returns the beacon interval (ms) for the Wi-Fi device.
 */
@property(readonly) NSInteger beaconInterval NS_AVAILABLE_MAC(10_7);

/*!
 * @property
 *
 * @result
 * YES if the Wi-Fi device is part of an IBSS network, NO otherwise.
 *
 * @abstract
 * Indicates whether or not the Wi-Fi device is participating in an independent basic service set (IBSS), or ad-hoc Wi-Fi network.
 */
@property(readonly) BOOL ibss NS_AVAILABLE_MAC(10_7);

/*! @functiongroup Comparing Networks */

/*!
 * @method
 *
 * @param network 
 * A CWNetwork object.
 *
 * @result
 * YES if the objects are equal, NO otherwise.
 *
 * @abstract 
 * Determine CWNetwork equality.
 *
 * @discussion
 * CWNetwork objects are considered equal if their corresponding <i>ssidData</i> and <i>bssid</i> properties are equal.
 */
- (BOOL)isEqualToNetwork:(CWNetwork *)network NS_AVAILABLE_MAC(10_6);

/*! @methodgroup Getting Supported Security Types */

/*!
 * @method
 *
 * @param security
 * A CWSecurity type value.
 *
 * @result
 * <i>YES</i> if the Wi-Fi device supports the specified security type, <i>NO</i> otherwise.
 *
 * @abstract 
 * Determine which security types a Wi-Fi device supports.
 */
- (BOOL)supportsSecurity:(CWSecurity)security NS_AVAILABLE_MAC(10_7);

/*! @methodgroup Getting Supported PHY Modes */

/*!
 * @method
 *
 * @param phyMode
 * A CWPHYMode type value.
 *
 * @result 
 * YES if the Wi-Fi device supports the specified PHY mode, NO otherwise.
 *
 * @abstract
 * Determine which PHY modes a Wi-Fi device supports.
 */
- (BOOL)supportsPHYMode:(CWPHYMode)phyMode NS_AVAILABLE_MAC(10_8);
@end
NS_ASSUME_NONNULL_END

#endif /* _CORE_WLAN_NETWORK_H_ */
