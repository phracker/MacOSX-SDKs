//
//  AVB17221ACMPMessage.h
//  AudioVideoBridging
//
//  Copyright (c) 2011-2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class AVBMACAddress;
@class AVBIPAddress;

/*!
	@class		AVB17221ACMPMessage
	@abstract	AVB17221ACMPMessage encapsulates an IEEE Std 1722.1™-2013 AVDECC Connection Management Protocol message.
	@discussion	AVB17221ACMPMessage encapsulates an IEEE Std 1722.1™-2013 AVDECC Connection Management Protocol (ACMP) message.
 */
API_AVAILABLE(macos(10.8)) API_UNAVAILABLE(ios, tvos)
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
@property (assign) uint64_t controllerEntityID API_AVAILABLE(macos(10.9)) API_UNAVAILABLE(ios, tvos);
/*!
	@property	talkerEntityID
	@abstract	The talker_entity_id field of the ACMP message.
 */
@property (assign) uint64_t talkerEntityID API_AVAILABLE(macos(10.9)) API_UNAVAILABLE(ios, tvos);
/*!
	@property	listenerEntityID
	@abstract	The listener_entity_id field of the ACMP message.
 */
@property (assign) uint64_t listenerEntityID API_AVAILABLE(macos(10.9)) API_UNAVAILABLE(ios, tvos);
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
 @property	connectedListenersEntries
 @abstract	The connected_listeners_entries field of the ACMP message.
 */
@property (assign) uint16_t connectedListenersEntries API_AVAILABLE(macos(12)) API_UNAVAILABLE(ios, tvos);
/*!
 @property	connectedListenersEntriesValid
 @abstract	The CL_ENTRIES_VALID flag in the flags field of the ACMP message.
 */
@property (assign) bool connectedListenersEntriesValid API_AVAILABLE(macos(12)) API_UNAVAILABLE(ios, tvos);

/*!
 @property	ipFlags
 @abstract	The ip_flags field of the ACMP message.
 */
@property (assign) AVB17221ACMPIPFlag ipFlags API_AVAILABLE(macos(12)) API_UNAVAILABLE(ios, tvos);
/*!
 @property	sourcePort
 @abstract	The source_port field of the ACMP message.
 */
@property (assign) uint16_t sourcePort API_AVAILABLE(macos(12)) API_UNAVAILABLE(ios, tvos);
/*!
 @property	destinationPort
 @abstract	The destination_port field of the ACMP message.
 */
@property (assign) uint16_t destinationPort API_AVAILABLE(macos(12)) API_UNAVAILABLE(ios, tvos);
/*!
 @property	sourceAddress
 @abstract	The source_ip_address field of the ACMP message.
 */
@property (copy) AVBIPAddress *sourceIPAddress API_AVAILABLE(macos(12)) API_UNAVAILABLE(ios, tvos);
/*!
 @property	destinationAddress
 @abstract	The destination_ip_address field of the ACMP message.
 */
@property (copy) AVBIPAddress *destinationIPAddress API_AVAILABLE(macos(12)) API_UNAVAILABLE(ios, tvos);

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

