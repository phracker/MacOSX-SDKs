//
//  AVB17221ACMPInterface.h
//  AudioVideoBridging
//
//  Copyright (c) 2011-2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class AVB17221ACMPMessage;
@class AVB17221ACMPInterface;

/*!
	@typedef	AVB17221ACMPInterfaceCompletion:
	@abstract	The prototype for the completion handler block for command messages.
 */
typedef void (^AVB17221ACMPInterfaceCompletion)(NSError * __nullable error, AVB17221ACMPMessage *message);

@class AVBInterface;
@class AVBMACAddress;

/*!
 @protocol	AVB17221ACMPClient
 @abstract	AVB17221ACMPClient is an objective-c protocol for classes intending to receive callbacks from AVB1722ACMPInterface.
 @discussion	AVB17221ACMPClient is an objective-c protocol for classes intending to receive callbacks from AVB1722ACMPInterface.
 There is a separate callback for each IEEE Std 1722.1™-2013 AVDECC Connection Managment Protocol (ACMP) command and response messages.
 */
@protocol AVB17221ACMPClient

@required

/*!
 @method		ACMPDidReceiveCommand:onInterface:
 @abstract	Handle a received AECP command.
 @param		message		An instance of a subclass of AVB17221ACMPMessage appropriate for the message type.
 @param		anInterface	The AVB17221ACMPInterface the message was received on.
 @result		YES if the message was processed, NO otherwise.
 */
- (BOOL)ACMPDidReceiveCommand:(AVB17221ACMPMessage *)message onInterface:(AVB17221ACMPInterface *)anInterface;

/*!
 @method		ACMPDidReceiveResponse:onInterface:
 @abstract	Handle a received AECP response.
 @param		message		An instance of a subclass of AVB17221ACMPMessage appropriate for the message type.
 @param		anInterface	The AVB17221ACMPInterface the message was received on.
 @result		YES if the message was processed, NO otherwise.
 */
- (BOOL)ACMPDidReceiveResponse:(AVB17221ACMPMessage *)message onInterface:(AVB17221ACMPInterface *)anInterface;

@end

/*!
	@class		AVB17221ACMPInterface
	@abstract	AVB17221ACMPInterface is a concrete subclass of AVB1722ControlInterface providing the access to the IEEE Std 1722.1™-2013 AVDECC Connection Management Protocol interface.
	@discussion	AVB17221ACMPInterface is a concrete subclass of AVB1722ControlInterface providing the access to the IEEE Std 1722.1™-2013 AVDECC Connection Management Protocol (ACMP) interface.
				It provides callbacks per entity EntityID via a handler object implementing the AVB17221ACMPClient protocol. AVB17221ACMPInterface objects
				are typically not created directly but are created indirectly and accessed via the acmp property of the AVBInterface object.
 */
NS_CLASS_AVAILABLE(10_8, NA)
@interface AVB17221ACMPInterface : AVB1722ControlInterface
{
#if AVB_LEGACY_OBJC_RUNTIME
@private
	void *_implACMPInterface;
#endif
}

/*!
	@property	multicastDestinationAddress
	@abstract	An AVBMACAddress of the multicast destination MAC address being used for all ACMP messages on the interface.
	@discussion	The MAC Address pointed to by the property is pre-initialized with the IEEE Std 1722.1™-2013 standard value, 91:e0:f0:01:00:00
 */
@property (readonly, copy) AVBMACAddress *multicastDestinationAddress;

/*!
	@method		AVB17221ACMPInterfaceWithInterface:
	@abstract	Creates an autoreleased instance of AVB17221ACMPInterface for the specified AVBInterface
	@param		anInterface	The interface on which to create the instance.
	@result		An autoreleased instance of the control service class.
 */
+ (AVB17221ACMPInterface *)ACMPInterfaceWithInterface:(AVBInterface *)anInterface;
/*!
	@method		AVB17221ACMPInterfaceWithInterfaceNamed:
	@abstract	Creates an autoreleased instance of AVB17221ACMPInterfaceWithInterfaceNamed for the specified network interface with the specified BSD name.
	@param		anInterfaceName	The BSD name of the interface.
	@result		An autoreleased instance of the control service class.
 */
+ (AVB17221ACMPInterface *)ACMPInterfaceWithInterfaceNamed:(NSString *)anInterfaceName;

/*!
	@method		setHandler:forGUID:
	@abstract	Add an object implementing the AVB17221ACMPClient protocol as a handler for messages to or from a specified GUID.
	@param		handler	The object which will handle all of the commands and responses.
	@param		targetGUID	The GUID of the entity the messages are to or from.
	@result		YES if the handler was added, NO if there is already a handler or if the routing ID couldn't be added.
 */
- (BOOL)setHandler:(id<AVB17221ACMPClient>)handler forGUID:(uint64_t)targetGUID  NS_DEPRECATED(10_8, 10_9, NA, NA);
/*!
	@method		setHandler:forEntityID:
	@abstract	Add an object implementing the AVB17221ACMPClient protocol as a handler for messages to or from a specified EntityID.
	@param		handler	The object which will handle all of the commands and responses.
	@param		targetEntityID	The EntityID of the entity the messages are to or from.
	@result		YES if the handler was added, NO if there is already a handler or if the routing ID couldn't be added.
 */
- (BOOL)setHandler:(id<AVB17221ACMPClient>)handler forEntityID:(uint64_t)targetEntityID NS_AVAILABLE(10_9, NA);
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
	@method		sendACMPResponseMessage:
	@abstract	Send an ACMP response message.
	@param		message	A pointer to an AVB17221ACMPMessage struct containing the ACMP message to send.
	@result		kIOReturnSuccess if the message was successfully sent, otherwise an error indicating failure reason.
	@discussion	This method synchronizes access to sending ACMP messages, and can safely be called from multiple threads and while handling a received command.
 */
- (BOOL)sendACMPResponseMessage:(AVB17221ACMPMessage *)message error:(NSError **)error;

/*!
	@method		sendACMPCommandMessage:completionHandler:
	@abstract	Send an ACMP command message.
	@param		message	A pointer to an AVB17221ACMPMessage struct containing the ACMP message.
	@param		completionHandler	A block containing code to execute when the command has been sent or timed out.
	@result		kIOReturnSuccess if the message was successfully sent, otherwise an error indicating failure reason.
	@discussion	This method synchronizes access to sending ACMP messages, and can safely be called from multiple threads. The completionHandler 
				is synchronized with the reception of messages from the kernel object providing the command transport. This method handles the retry
				and message timeout per the IEEE Std 1722.1™-2013 standard timeouts.
 */
- (BOOL)sendACMPCommandMessage:(AVB17221ACMPMessage *)message completionHandler:(AVB17221ACMPInterfaceCompletion)completionHandler;

@end

NS_ASSUME_NONNULL_END
