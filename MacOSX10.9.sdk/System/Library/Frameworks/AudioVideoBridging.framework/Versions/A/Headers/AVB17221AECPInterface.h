//
//  AVB17221AECPInterface.h
//  AudioVideoBridging
//
//  Copyright 2011-2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


@class AVB17221AECPMessage;
@class AVB17221AECPInterface;

/*!
 @protocol	AVB17221AECPClient
 @abstract	AVB17221AECPClient is an objective-c protocol for classes intending to receive callbacks from an AVB1722AECPInterface instance.
 @discussion	AVB17221AECPClient is an objective-c protocol for classes intending to receive callbacks from an AVB1722AECPInterface instance.
 Commands and responses are provided with separate callbacks.
 */
@protocol AVB17221AECPClient

@required

/*!
 @method		AECPDidReceiveCommand:onInterface:
 @abstract	Handle a received AECP command.
 @param		message		An instance of a subclass of AVB17221AECPMessage appropriate for the message type.
 @param		anInterface	The AVB17221AECPInterface the message was received on.
 @result		YES if the message was processed, NO otherwise.
 */
- (BOOL)AECPDidReceiveCommand:(AVB17221AECPMessage *)message onInterface:(AVB17221AECPInterface *)anInterface;

/*!
 @method		AECPDidReceiveResponse:onInterface:
 @abstract	Handle a received AECP response.
 @param		message		An instance of a subclass of AVB17221AECPMessage appropriate for the message type.
 @param		anInterface	The AVB17221AECPInterface the message was received on.
 @result		YES if the message was processed, NO otherwise.
 */
- (BOOL)AECPDidReceiveResponse:(AVB17221AECPMessage *)message onInterface:(AVB17221AECPInterface *)anInterface;

@end

/*!
 @typedef	AVB17221AECPInterfaceCompletion:
 @abstract	The prototype for the completion handler block for AECP command messages.
 */
typedef void (^AVB17221AECPInterfaceCompletion)(NSError *, AVB17221AECPMessage *);

@class AVBInterface;
@class AVBMACAddress;

/*!
	@class		AVB17221AECPInterface
	@abstract	AVB17221AECPInterface is a concrete subclass of AVB1722ControlInterface providing the access to the IEEE P1722.1 AVDECC Enumeration and Control Protocol interface.
	@discussion	AVB17221AECPInterface is a concrete subclass of AVB1722ControlInterface providing the access to the IEEE P1722.1 AVDECC Enumeration and Control Protocol (AECP) interface.
				It provides callbacks per entity EntityID via a handler object implementing the AVB17221AECPClient protocol. AVB17221AECPInterface objects
				are typically not created directly but are created indirectly and accessed via the aecp property of the AVBInterface object.
 */
NS_CLASS_AVAILABLE(10_8, NA)
@interface AVB17221AECPInterface : AVB1722ControlInterface
{
	@private
	NSMutableDictionary *commandHandlers;
	
	uint16_t nextSequenceID;
	
	uint64_t inflightControllerEntityID;
	uint8_t inflightMessageType;
	uint16_t inflightSequenceID;
	
	uint16_t lastReceivedSequenceID;
	
	BOOL _monitorMode;
	id<AVB17221AECPClient> _monitorModeDelegate;
	
	NSMutableArray *pendingAEMResponses;
}


/*!
	@method		AECPInterfaceWithInterface:
	@abstract	Creates an autoreleased instance of AVB17221AECPInterface for the specified AVBInterface
	@param		anInterface	The interface on which to create the instance.
	@result		An autoreleased instance of the control service class.
 */
+ (AVB17221AECPInterface *)AECPInterfaceWithInterface:(AVBInterface *)anInterface;
/*!
	@method		AECPInterfaceWithInterfaceNamed:
	@abstract	Creates an autoreleased instance of AVB17221AECPInterfaceWithInterfaceNamed for the specified network interface with the specified BSD name.
	@param		anInterfaceName	The BSD name of the interface.
	@result		An autoreleased instance of the control service class.
 */
+ (AVB17221AECPInterface *)AECPInterfaceWithInterfaceNamed:(NSString *)anInterfaceName;

/*!
	@method		setHandler:forGUID:
	@abstract	Add an object implementing the AVB17221AECPClient protocol as a handler for messages to or from a specified GUID.
	@param		handler	The object which will handle all of the commands and responses.
	@param		targetGUID	The GUID of the entity the messages are to or from.
	@result		YES if the handler was added, NO if there is already a handler or if the routing ID couldn't be added.
 */
- (BOOL)setHandler:(id<AVB17221AECPClient>)handler forGUID:(uint64_t)targetGUID NS_DEPRECATED(10_8, 10_9, NA, NA);
/*!
	@method		setHandler:forEntityID:
	@abstract	Add an object implementing the AVB17221AECPClient protocol as a handler for messages to or from a specified EntityID.
	@param		handler	The object which will handle all of the commands and responses.
	@param		targetEntityID	The EntityID of the entity the messages are to or from.
	@result		YES if the handler was added, NO if there is already a handler or if the routing ID couldn't be added.
 */
- (BOOL)setHandler:(id<AVB17221AECPClient>)handler forEntityID:(uint64_t)targetEntityID NS_AVAILABLE(10_9, NA);
/*!
	@method		removeHandlerForGUID:
	@abstract	Removed a handler  for messages to or from a specified GUID.
	@param		targetGUID	The GUID of the entity the messages are to or from.
 */
- (void)removeHandlerForGUID:(uint64_t)targetGUID NS_DEPRECATED(10_8, 10_9, NA, NA);
/*!
	@method		removeHandlerForEntityID:
	@abstract	Removed a handler  for messages to or from a specified EntityID.
	@param		targetEntityID	The EntityID of the entity the messages are to or from.
 */
- (void)removeHandlerForEntityID:(uint64_t)targetEntityID NS_AVAILABLE(10_9, NA);

/*!
	@method		sendCommand:toMACAddress:completionHandler:
	@abstract	Send an AECP command message.
	@param		message	An instance of a subclass of AVB17221AECPMessage which contains the command message.
	@param		destMAC	The MAC address of the end station to send the message to.
	@param		completionHandler	A block containing code to execute when the command has been sent or timed out.
	@result		A BOOL indicating success or failure
	@discussion	This method synchronizes access to the kernel service providing transport for the message. This method is safe to call from any thread. 
				This method blocks until either the response is received or a the appropriate timeout expires. The sequence_id is automatically inserted and guaranteed
				to be monotonically increasing for all AECP messages sent from this interface object.
 */
- (BOOL)sendCommand:(AVB17221AECPMessage *)message toMACAddress:(AVBMACAddress *)destMAC completionHandler:(AVB17221AECPInterfaceCompletion)completionHandler;

/*!
	@method		sendResponse:toMACAddress:error:
	@abstract	Send an AECP response.
	@param		message	An instance of a subclass of AVB17221AECPMessage which contains the response message.
	@param		destMAC	The MAC address of the end station to send the message to. This argument needs to points to kIOEthernetAddressSize bytes of memory.
	@result		IOReturn indicating success or failure and reason for failure.
	@discussion	This method synchronizes access to the kernel service providing transport for the message. This method is safe to call from any thread. 
 */
- (BOOL)sendResponse:(AVB17221AECPMessage *)message toMACAddress:(AVBMACAddress *)destMAC error:(NSError **)error;

@end
