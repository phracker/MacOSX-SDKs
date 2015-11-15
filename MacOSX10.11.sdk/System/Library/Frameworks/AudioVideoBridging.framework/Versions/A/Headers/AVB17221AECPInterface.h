//
//  AVB17221AECPInterface.h
//  AudioVideoBridging
//
//  Copyright (c) 2011-2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN

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
typedef void (^AVB17221AECPInterfaceCompletion)(NSError * __nullable e, AVB17221AECPMessage *m);

@class AVBInterface;
@class AVBMACAddress;

/*!
	@class		AVB17221AECPInterface
	@abstract	AVB17221AECPInterface is a concrete subclass of AVB1722ControlInterface providing the access to the IEEE Std 1722.1™-2013 AVDECC Enumeration and Control Protocol interface.
	@discussion	AVB17221AECPInterface is a concrete subclass of AVB1722ControlInterface providing the access to the IEEE Std 1722.1™-2013 AVDECC Enumeration and Control Protocol (AECP) interface.
				It provides callbacks per entity EntityID via a handler object implementing the AVB17221AECPClient protocol. AVB17221AECPInterface objects
				are typically not created directly but are created indirectly and accessed via the aecp property of the AVBInterface object.
 */
NS_CLASS_AVAILABLE(10_8, NA)
@interface AVB17221AECPInterface : AVB1722ControlInterface
{
#if AVB_LEGACY_OBJC_RUNTIME
@private
	void *_implAECPInterface;
#endif
}


/*!
	@method		AECPInterfaceWithInterface:
	@abstract	Creates an autoreleased instance of AVB17221AECPInterface for the specified AVBInterface
	@param		anInterface	The interface on which to create the instance.
	@result		An autoreleased instance of the control service class.
 */
+ (nullable AVB17221AECPInterface *)AECPInterfaceWithInterface:(AVBInterface *)anInterface;
/*!
	@method		AECPInterfaceWithInterfaceNamed:
	@abstract	Creates an autoreleased instance of AVB17221AECPInterfaceWithInterfaceNamed for the specified network interface with the specified BSD name.
	@param		anInterfaceName	The BSD name of the interface.
	@result		An autoreleased instance of the control service class.
 */
+ (nullable AVB17221AECPInterface *)AECPInterfaceWithInterfaceNamed:(NSString *)anInterfaceName;

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
	@abstract	Add an object implementing the AVB17221AECPClient protocol as a handler for messages to or from a specified Entity ID.
	@param		handler	The object which will handle all of the commands and responses.
	@param		targetEntityID	The EntityID of the entity the messages are to or from.
	@result		YES if the handler was added, NO if there is already a handler or if the routing ID couldn't be added.
 */
- (BOOL)setHandler:(id<AVB17221AECPClient>)handler forEntityID:(uint64_t)targetEntityID NS_DEPRECATED(10_9, 10_11, NA, NA, "Use -setCommandHandler:forEntityID: and -setResponseHandler:forControllerEntityID: instead.");
/*!
	@method		removeHandlerForGUID:
	@abstract	Removed a handler for messages to or from a specified GUID.
	@param		targetGUID	The GUID of the entity the messages are to or from.
 */
- (void)removeHandlerForGUID:(uint64_t)targetGUID NS_DEPRECATED(10_8, 10_9, NA, NA);
/*!
	@method		removeHandlerForEntityID:
	@abstract	Removed a handler  for messages to or from a specified EntityID.
	@param		targetEntityID	The EntityID of the entity the messages are to or from.
 */
- (void)removeHandlerForEntityID:(uint64_t)targetEntityID NS_DEPRECATED(10_9, 10_11, NA, NA, "Use -removeCommandHandlerForEntityID: or -removeResponseHandlerForControllerEntityID: instead.");

/*!
	@method		setCommandHandler:forEntityID:
	@abstract	Add an object implementing the AVB17221AECPClient protocol as a handler for command messages to a specified Entity ID.
	@param		handler	The object which will handle all of the commands.
	@param		targetEntityID	The Entity ID of the entity the messages are to.
	@result		YES if the handler was added, NO if there is already a handler or if the routing ID couldn't be added.
 */
- (BOOL)setCommandHandler:(id<AVB17221AECPClient>)handler forEntityID:(uint64_t)targetEntityID NS_AVAILABLE(10_11, NA);
/*!
	@method		removeCommandHandlerForEntityID:
	@abstract	Removed a handler for command messages to or from a specified EntityID.
	@param		targetEntityID	The EntityID of the entity the messages are to.
 */
- (void)removeCommandHandlerForEntityID:(uint64_t)targetEntityID NS_AVAILABLE(10_11, NA);

/*!
	@method		setResponseHandler:forControllerEntityID:
	@abstract	Add an object implementing the AVB17221AECPClient protocol as a handler for response messages for a specified controller EntityID.
	@param		handler	The object which will handle all of the responses for the Controller Entity ID.
	@param		controllerEntityID	The Entity ID of the controller the messages are for.
	@result		YES if the handler was added, NO if there is already a handler or if the routing ID couldn't be added.
 */
- (BOOL)setResponseHandler:(id<AVB17221AECPClient>)handler forControllerEntityID:(uint64_t)controllerEntityID NS_AVAILABLE(10_11, NA);
/*!
	@method		removeResponseHandlerForControllerEntityID:
	@abstract	Removed a handler for response messages to or from a specified EntityID.
	@param		controllerEntityID	The EntityID of the controller the messages are for.
 */
- (void)removeResponseHandlerForControllerEntityID:(uint64_t)controllerEntityID NS_AVAILABLE(10_11, NA);

/*!
	@method		sendCommand:toMACAddress:completionHandler:
	@abstract	Send an AECP command message.
	@param		message	An instance of a subclass of AVB17221AECPMessage which contains the command message.
	@param		destMAC	The MAC address of the end station to send the message to.
	@param		completionHandler	A block containing code to execute when the command has been sent or timed out.
	@result		A BOOL indicating success or failure
	@discussion	This method synchronizes access to the kernel service providing transport for the message. This method is safe to call from any thread.
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

NS_ASSUME_NONNULL_END
