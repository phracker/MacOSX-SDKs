//
//  AVBMACAddress.h
//  AudioVideoBridging
//
//  Copyright (c) 2011-2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
	@class		AVBMACAddress
	@abstract	AVBMACAddress is a class for holding and representing an Ethernet MAC Address.
 */
NS_CLASS_AVAILABLE(10_8, NA)
@interface AVBMACAddress : NSObject <NSCopying>
{
	@private
	uint8_t _bytes[AVBMACAddressSize];
}

/*!
	@method		initWithBytes:
	@abstract	This method initializes the receiver to contain the MAC address specified.
	@param		bytes A pointer to 6 octets of memory containing the MAC address.
	@result		The initialized receiver.
 */
- (instancetype)initWithBytes:(const uint8_t *)bytes;

/*!
	@property	bytes
	@abstract	The .
 */
@property (assign, readonly) const uint8_t *bytes NS_RETURNS_INNER_POINTER;

/*!
	@property	dataRepresentation
	@abstract	An NSData object containing the bytes of the MAC address.
 */
@property (copy) NSData *dataRepresentation;

/*!
	@property	stringRepresentation
	@abstract	The colon separated cannonical string representation of the MAC address e.g. 12:34:56:78:ab:cd
 */
@property (copy) NSString *stringRepresentation;

/*!
	@property	multicast
	@abstract	Returns if the multicast bit is set in the MAC address.
 */
@property (assign, getter=isMulticast) BOOL multicast;

@end

NS_ASSUME_NONNULL_END
