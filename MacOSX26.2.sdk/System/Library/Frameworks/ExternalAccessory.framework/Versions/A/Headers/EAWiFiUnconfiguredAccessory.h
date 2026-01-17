//
//  EAWiFiUnconfiguredAccessory.h
//  ExternalAccessory
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 *  @options EAWiFiUnconfiguredAccessoryProperties
 *
 *  @discussion Represents the properties of an EAWiFiUnconfiguredAccessory.
 *
 *  @constant EAWiFiUnconfiguredAccessoryPropertySupportsAirPlay  Option set if the accessory is advertising that it supports AirPlay.
 *  @constant EAWiFiUnconfiguredAccessoryPropertySupportsAirPrint Option set if the accessory is advertising that it supports AirPrint.
 *  @constant EAWiFiUnconfiguredAccessoryPropertySupportsHomeKit  Option set if the accessory is advertising that it supports HomeKit.
 *
 */
typedef NS_OPTIONS(NSUInteger, EAWiFiUnconfiguredAccessoryProperties)
{
    EAWiFiUnconfiguredAccessoryPropertySupportsAirPlay  = (1 << 0),
    EAWiFiUnconfiguredAccessoryPropertySupportsAirPrint = (1 << 1),
    EAWiFiUnconfiguredAccessoryPropertySupportsHomeKit  = (1 << 2)
};

/*!
 * @brief Object representing an unconfigured MFi Wireless Accessory Configuration (WAC) accessory.
 *
 * @discussion This class models an unconfigured MFi Wireless Accessory Configuration accessory
 *             discovered via a EAWiFiUnconfiguredAccessoryBrowser search.
 *
 */
NS_CLASS_AVAILABLE(NA, 8_0)
@interface EAWiFiUnconfiguredAccessory : NSObject

/*!
 * @property name
 *
 * @discussion The name of the accessory.
 *
 */
@property(copy, nonatomic, readonly) NSString *name;

/*!
 * @property manufacturer
 *
 * @discussion The name of the accessory's manufacturer.
 *
 */
@property(copy, nonatomic, readonly) NSString *manufacturer;

/*!
 * @property model
 *
 * @discussion The model name of accessory.
 *
 */
@property(copy, nonatomic, readonly) NSString *model;

/*!
 * @property ssid
 *
 * @discussion The Wi-Fi SSID of the accessory.
 *
 */
@property(copy, nonatomic, readonly) NSString *ssid;

/*!
 * @property macAddress
 *
 * @discussion The primary MAC address of the accessory.
 *
 */
@property(copy, nonatomic, readonly) NSString *macAddress;

/*!
 * @property properties
 *
 * @discussion The properties the accessory supports.
 *
 */
@property(readonly, nonatomic, readonly) EAWiFiUnconfiguredAccessoryProperties properties;

@end

NS_ASSUME_NONNULL_END
