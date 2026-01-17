//
//  AVBIPAddress.h
//  AudioVideoBridging
//
//  Created by Ashley Butterworth on 7/16/20.
//  Copyright © 2020-2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#include <sys/socket.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class		AVBIPAddress
 @abstract	AVBIPAddress is a class for holding and representing an IP Address, either IPv4 or IPv6.
 */
API_AVAILABLE(macos(12)) API_UNAVAILABLE(ios, tvos)
@interface AVBIPAddress : NSObject <NSCopying>

/*!
 @method	initWithIPv6Address:
 @abstract	This method initializes the receiver to contain the IPv6 address specified.
 @param		ipv6Address A pointer to 16 octets of memory containing the IPv6 address.
 @result	The initialized receiver.
 */
- (instancetype)initWithIPv6Address:(const uint8_t *)ipv6Address;

/*!
 @method	initWithIPv6AddressData:
 @abstract	This method initializes the receiver to contain the IPv6 address specified.
 @param		ipv6Address An NSData containing 16 octets with the IPv6 address.
 @result	The initialized receiver.
 */
- (instancetype)initWithIPv6AddressData:(NSData *)ipv6Address;

/*!
 @method	initWithIPv4Address:
 @abstract	This method initializes the receiver to contain the IPv4 address specified.
 @param		ipv4Address A uint32_t containing the IPv4 address in host byte order.
 @result	The initialized receiver.
 */
- (instancetype)initWithIPv4Address:(uint32_t)ipv4Address;

/*!
 @method	initWithSockAddr:
 @abstract	This method initializes the receiver to contain the address specified.
 @param		sockAddr A pointer to a sock_addr containing either an IPv4 or IPv6 address.
 @result	The initialized receiver.
 */
- (instancetype)initWithSockAddr:(const struct sockaddr *)sockAddr;


/*!
 @property	representsIPv4Address
 @abstract	A boolean indicating if the address is an IPv4 address.
 */
@property (assign, readonly) BOOL representsIPv4Address;

/*!
 @property	ipv6Address
 @abstract	An NSData object containing the bytes of the IPv6 representaion of the address. This value is always valid and uses the IPv4 to IPv6 address translation of 2.5.5.2 of RFC 4291 to encode the address
 */
@property (copy) NSData *ipv6Address;

/*!
 @property	ipv4Address
 @abstract	An unsigned32 bit integer containg the IPv4 representaion in host byte order. This value is only valid when representsIPv4Address returns YES.
 */
@property (assign) uint32_t ipv4Address;

/*!
 @property	stringRepresentation
 @abstract	A strign representation of the IP address in the appropriate representation for IPv4 or IPv6.
 */
@property (copy) NSString *stringRepresentation API_AVAILABLE(macos(14)) API_UNAVAILABLE(ios, tvos);

@end

NS_ASSUME_NONNULL_END
