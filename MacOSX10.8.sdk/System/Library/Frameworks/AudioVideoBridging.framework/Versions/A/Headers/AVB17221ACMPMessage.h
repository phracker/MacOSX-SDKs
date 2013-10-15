//
//  AVB17221ACMPMessage.h
//  AudioVideoBridging
//
//  Copyright 2011-2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class AVBMACAddress;

/*!
	@class		AVB17221ACMPMessage
	@abstract	AVB17221ACMPMessage encapsulates an IEEE P1722.1 AVDECC Connection Management Protocol message.
	@discussion	AVB17221ACMPMessage encapsulates an IEEE P1722.1 AVDECC Connection Management Protocol (ACMP) message.
 */
NS_CLASS_AVAILABLE(10_8, NA)
@interface AVB17221ACMPMessage : NSObject <NSCopying>
#ifndef _LP64
{
	@private
	AVB17221ACMPMessageType messageType;
	AVB17221ACMPStatusCode status;
	uint64_t streamID;
	uint64_t controllerGUID;
	uint64_t talkerGUID;
	uint64_t listenerGUID;
	uint16_t talkerUniqueID;
	uint16_t listenerUniqueID;
	uint16_t connectionCount;
	uint16_t sequenceID;
	AVB17221ACMPFlags flags;
	
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
@property (assign) uint64_t controllerGUID;
/*!
	@property	talkerGUID
	@abstract	The talker_guid field of the ACMP message.
 */
@property (assign) uint64_t talkerGUID;
/*!
	@property	listenerGUID
	@abstract	The listener_guid field of the ACMP message.
 */
@property (assign) uint64_t listenerGUID;
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
@property (copy) AVBMACAddress *destinationMAC;
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
	@property	sourceMAC
	@abstract	The source_mac field of the ACMP message.
 */
@property (copy) AVBMACAddress *sourceMAC;

@end
