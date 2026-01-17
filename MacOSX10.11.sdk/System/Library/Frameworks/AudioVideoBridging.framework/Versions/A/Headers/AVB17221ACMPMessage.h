//
//  AVB17221ACMPMessage.h
//  AudioVideoBridging
//
//  Copyright (c) 2011-2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class AVBMACAddress;

/*!
	@class		AVB17221ACMPMessage
	@abstract	AVB17221ACMPMessage encapsulates an IEEE Std 1722.1™-2013 AVDECC Connection Management Protocol message.
	@discussion	AVB17221ACMPMessage encapsulates an IEEE Std 1722.1™-2013 AVDECC Connection Management Protocol (ACMP) message.
 */
NS_CLASS_AVAILABLE(10_8, NA)
@interface AVB17221ACMPMessage : NSObject <NSCopying>
#if AVB_LEGACY_OBJC_RUNTIME
{
	@private
	AVB17221ACMPMessageType messageType;
	AVB17221ACMPStatusCode status;
	uint64_t streamID;
	uint64_t controllerEntityID;
	uint64_t talkerEntityID;
	uint64_t listenerEntityID;
	uint16_t talkerUniqueID;
	uint16_t listenerUniqueID;
	uint16_t connectionCount;
	uint16_t sequenceID;
	AVB17221ACMPFlags flags;
	uint16_t vlanID;
	
	AVBMACAddress *sourceMAC;
	AVBMACAddress *destinationMAC;
}
#endif

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
	@abstract	The controller_guid field of the ACMP message.
 */
@property (assign) uint64_t controllerGUID NS_DEPRECATED(10_8, 10_9, NA, NA);
/*!
	@property	controllerGUID
	@abstract	The controller_entity_id field of the ACMP message.
 */
@property (assign) uint64_t controllerEntityID NS_AVAILABLE(10_9, NA);
/*!
	@property	talkerGUID
	@abstract	The talker_guid field of the ACMP message.
 */
@property (assign) uint64_t talkerGUID NS_DEPRECATED(10_8, 10_9, NA, NA);
/*!
	@property	talkerEntityID
	@abstract	The talker_entity_id field of the ACMP message.
 */
@property (assign) uint64_t talkerEntityID NS_AVAILABLE(10_9, NA);
/*!
	@property	listenerGUID
	@abstract	The listener_guid field of the ACMP message.
 */
@property (assign) uint64_t listenerGUID NS_DEPRECATED(10_8, 10_9, NA, NA);
/*!
	@property	listenerEntityID
	@abstract	The listener_entity_id field of the ACMP message.
 */
@property (assign) uint64_t listenerEntityID NS_AVAILABLE(10_9, NA);
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

@end

NS_ASSUME_NONNULL_END

