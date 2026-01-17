//
//  AVB17221ACMPMessage.h
//  AudioVideoBridging
//
//  Copyright (c) 2011-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class AVBMACAddress;

/*!
	@class		AVB17221ACMPMessage
	@abstract	AVB17221ACMPMessage encapsulates an IEEE Std 1722.1™-2013 AVDECC Connection Management Protocol message.
	@discussion	AVB17221ACMPMessage encapsulates an IEEE Std 1722.1™-2013 AVDECC Connection Management Protocol (ACMP) message.
 */
API_AVAILABLE(macos(10.8))
@interface AVB17221ACMPMessage : NSObject <NSCopying>

/*!
	@property	messageType
	@abstract	The message_type field of the ACMP message.
 */
@property (assign) AVB17221ACMPMessageType messageType;
/*!
	@property	status
	@abstract	The status field of the ACMP message.
 */
@property (assign) AVB17221ACMPStatusCode status;
/*!
	@property	streamID
	@abstract	The stream_id field of the ACMP message.
 */
@property (assign) uint64_t streamID;
/*!
	@property	controllerGUID
	@abstract	The controller_entity_id field of the ACMP message.
 */
@property (assign) uint64_t controllerEntityID API_AVAILABLE(macos(10.9));
/*!
	@property	talkerEntityID
	@abstract	The talker_entity_id field of the ACMP message.
 */
@property (assign) uint64_t talkerEntityID API_AVAILABLE(macos(10.9));
/*!
	@property	listenerEntityID
	@abstract	The listener_entity_id field of the ACMP message.
 */
@property (assign) uint64_t listenerEntityID API_AVAILABLE(macos(10.9));
/*!
	@property	talkerUniqueID
	@abstract	The talker_unique_id field of the ACMP message.
 */
@property (assign) uint16_t talkerUniqueID;
/*!
	@property	listenerUniqueID
	@abstract	The listener_unique_id field of the ACMP message.
 */
@property (assign) uint16_t listenerUniqueID;
/*!
	@property	destinationMAC
	@abstract	The dest_mac field of the ACMP message.
 */
@property (copy, nullable) AVBMACAddress *destinationMAC;
/*!
	@property	connectionCount
	@abstract	The connection_count field of the ACMP message.
 */
@property (assign) uint16_t connectionCount;
/*!
	@property	sequenceID
	@abstract	The sequence_id field of the ACMP message.
 */
@property (assign) uint16_t sequenceID;
/*!
	@property	flags
	@abstract	The flags field of the ACMP message.
 */
@property (assign) AVB17221ACMPFlags flags;
/*!
	@property	vlanID
	@abstract	The stream_vlan_id field of the ACMP message.
 */
@property (assign) uint16_t vlanID;

/*!
	@property	sourceMAC
	@abstract	The source_mac field of the ACMP message.
 */
@property (copy, nullable) AVBMACAddress *sourceMAC;

/*!
	@method		errorForStatusCode:
	@abstract	This method returns an NSError filled out with an appropriate description for the passed in status code.
	@result		An NSError instance within the AVBErrorDomain with the status code and an appropriate description.
				Will return nil if status code is success or in progress.
 */
+ (nullable NSError *)errorForStatusCode:(AVB17221ACMPStatusCode)statusCode;

/*!
	@method		errorForStatusCode
	@abstract	This method returns an NSError filled out with an appropriate description for the message's status code.
	@result		An NSError instance within the AVBErrorDomain with the status code and an appropriate description.
				Will return nil if status code is success or in progress.
 */
- (nullable NSError *)errorForStatusCode;

@end

NS_ASSUME_NONNULL_END

