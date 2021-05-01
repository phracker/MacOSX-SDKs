//
//  VZMACAddress.h
//  Virtualization
//
//  Copyright © 2019-2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>
#import <net/ethernet.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract VZMACAddress represents a media access control address (MAC address), the 48-bit ethernet address.
 @discussion
    The easiest way to obtain a MAC address is with +[VZMACAddress randomLocallyAdministeredAddress]. The method
    returns a valid local MAC address typically used with network interfaces.
 @see VZNetworkDeviceConfiguration
*/
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZMACAddress : NSObject<NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Initialize the VZMACAddress from a 48-bit ethernet address.
 @param ethernetAddress A 48-bit ethernet address.
 */
- (instancetype)initWithEthernetAddress:(ether_addr_t)ethernetAddress NS_DESIGNATED_INITIALIZER;

/*!
 @abstract Initialize the VZMACAddress from a string representation of a MAC address.
 @param string
    The string should be formatted representing the 6 bytes in hexadecimal separated by a colon character.
        e.g. "01:23:45:ab:cd:ef"

    The alphabetical characters can appear lowercase or uppercase.
 @return A VZMACAddress or nil if the string is not formatted correctly.
 */
- (nullable instancetype)initWithString:(NSString *)string;

/*!
 @abstract Create a valid, random, unicast, locally administered address.
 @discussion The generated address is not guaranteed to be unique.
 */
+ (instancetype)randomLocallyAdministeredAddress;

/*!
 @abstract The address represented as an ether_addr_t.
 */
@property (readonly) ether_addr_t ethernetAddress;

/*!
 @abstract The address represented as a string.
 @discussion
    The 6 bytes are represented in hexadecimal form, separated by a colon character.
    Alphabetical characters are lowercase.

    The address is compatible with the parameter of -[VZMACAddress initWithString:].
 */
@property (readonly, copy) NSString *string;

/*!
 @abstract True if the address is the broadcast address, false otherwise.
 */
@property (readonly, getter=isBroadcastAddress) BOOL isBroadcastAddress;

/*!
 @abstract True if the address is a multicast address, false otherwise.
*/
@property (readonly, getter=isMulticastAddress) BOOL isMulticastAddress;

/*!
 @abstract True if the address is a unicast address, false otherwise.
*/
@property (readonly, getter=isUnicastAddress) BOOL isUnicastAddress;

/*!
 @abstract True if the address is a locally administered addresses (LAA), false otherwise.
*/
@property (readonly, getter=isLocallyAdministeredAddress) BOOL isLocallyAdministeredAddress;

/*!
 @abstract True if the address is a universally administered addresses (UAA), false otherwise.
*/
@property (readonly, getter=isUniversallyAdministeredAddress) BOOL isUniversallyAdministeredAddress;

@end

NS_ASSUME_NONNULL_END
