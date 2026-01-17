//
//  IOUSBHostCIEndpointStateMachine.h
//  IOUSBHostFramework
//
//  Copyright © 2020 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IOUSBHost/IOUSBHostControllerInterfaceDefinitions.h>

@class IOUSBHostControllerInterface;

NS_ASSUME_NONNULL_BEGIN

/*!
 * @class   IOUSBHostCIEndpointStateMachine
 * @brief   The object representing the state of a user-mode USB host controller endpoint
 * @details This class assists with tracking internal state transitions of a user-mode USB host controller endpoint, and parses IOUSBHostCIMessage command
 *          structures to update state and generate properly formatted command responses.  Clients should create an IOUSBHostCIEndpointStateMachine in
 *          response to an IOUSBHostCIMessageTypeEndpointCreate command, and then use the provided interfaces to identify and process commands,
 *          doorbells, and transfer structures for the endpoint.  The IOUSBHostCIEndpointStateMachine should be destroyed in response to an
 *          IOUSBHostCIMessageTypeEndpointDestroy command.
 *
 *          Endpoint state is controlled by IOUSBHostCIMessage structures representing commands and transfer completions, and IOUSBHostCIDoorbell messages.
 *          Only an endpoint in the IOUSBHostCIEndpointStateActive state may inspect transfer structures, read or modify IO buffers, and generate transfer completions.
 *
 *          IOUSBHostCIEndpointStateMachine does not provide any concurrency protection, the client is responsible for necessary serialization.
 */
@interface IOUSBHostCIEndpointStateMachine : NSObject

- (instancetype)init __attribute__((unavailable("Please use initWithInterface:command")));

/*!
 * @brief       Initializes an IOUSBHostCIEndpointStateMachine object
 * @discussion  The IOUSBHostCIEndpointStateMachine defaults to the IOUSBHostCIEndpointStatePaused state.
 * @param       interface IOUSBHostControllerInterface which will be used to send command responses.
 * @param       command IOUSBHostCIMessage with type IOUSBHostCIMessageTypeEndpointCreate
 * @return      IOUSBHostCIEndpointStateMachine instance, to be released by the caller.
 */
-(nullable instancetype)initWithInterface:(IOUSBHostControllerInterface*)interface
                                  command:(const IOUSBHostCIMessage*)command
                                    error:(NSError**)error NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

/*!
 * @brief       Inspect an IOUSBHostCIMessage command
 * @discussion  The IOUSBHostCIMessage command is inspected to determine if it is handled by this state machine and is appropriate for the current state.
 * @param       command IOUSBHostCIMessage command structure received from the kernel driver.
 * @return      BOOL YES if the command is targeting this endpoint, and can be handled in the current state
 *              BOOL NO if the command does not target this endpoint, or cannot be handled in the current state
*/
-(BOOL)inspectCommand:(const IOUSBHostCIMessage*)command
                error:(NSError**)error;

/*!
 * @brief       Advance the state machine and respond to an IOUSBHostCIMessage command
 * @discussion  If the command passes inspectCommand and the client indicates the command was processed successfully, endpointState is updated and
 *              a properly formatted command response message is sent to the kernel driver.  If the client indicates the command was not processed successfully,
 *              endpointState is not updated but a properly formatted command response message is sent to the kernel driver.
 * @param       command IOUSBHostCIMessage command structure received from the kernel driver.
 * @param       status IOUSBHostCIMessageStatus reported by the user-mode USB host controller implementation for the command response.
 * @return      BOOL YES if the command response was sent to the kernel driver
 *              BOOL NO if the command response was not sent to the kernel driver
*/
-(BOOL)respondToCommand:(const IOUSBHostCIMessage*)command
                 status:(const IOUSBHostCIMessageStatus)status
                  error:(NSError**)error;

/*!
 * @brief       Advance the state machine and process an IOUSBHostCIDoorbell message
 * @discussion  The IOUSBHostCIDoorbell is inspected to determine if it is handled by this state machine and is appropriate for the current state.  If successful,
 *              the client should check for an IOUSBHostCIEndpointStateActive endpointState and a currentTransferMessage with IOUSBHostCIMessageControlValid set to determine
 *              if more IOUSBHostCIMessages should be processed.
 * @param       doorbell IOUSBHostCIDoorbell message received from the kernel driver.
 * @return      BOOL YES if the doorbell is targeting this endpoint and can be handled in the current state.
 *              BOOL NO is the doorbell does not target this endpoint or cannot be handled in the current state.
 */
-(BOOL)processDoorbell:(const IOUSBHostCIDoorbell)doorbell
                 error:(NSError**)error;

/*!
 * @brief       Send an IOUSBHostCIMessage representing a transfer completion to the kernel, and advance the state machine
 * @discussion  When a client has processed an IOUSBHostCIMessage representing a transfer, the result is reported to the kernel by another IOUSBHostCIMessage.  If successful,
 *              this object will use controllerInterface's enqueueInterrupt interface to send a properly formatted IOUSBHostCIMessage to the kernel with
 *              IOUSBHostCITransferCompletionMessageData1TransferStructure populated with currentTransferMessage's virtual address, and endpointState and currentTransferMessage
 *              are updated.  After a successful call, the client should check for an IOUSBHostCIEndpointStateActive endpointState and a currentTransferMessage with IOUSBHostCIMessageControlValid
 *              set to determine if more IOUSBHostCIMessages should be processed.
 * @param       message pointer to the IOUSBHostCIMessage which generated this tranafer completion message.  This must match currentTransferMessage to be successful.
 * @param       status IOUSBHostCIMessageStatus
 * @param       transferLength The number of bytes transferred for the specified transfer structure.
 */
-(BOOL)enqueueTransferCompletionForMessage:(const IOUSBHostCIMessage*)message
                                    status:(IOUSBHostCIMessageStatus)status
                            transferLength:(NSUInteger)transferLength
                                     error:(NSError**)error;

@property(nonatomic, readonly)  IOUSBHostCIEndpointState        endpointState;

@property(nonatomic, readonly)  NSUInteger                      deviceAddress;

@property(nonatomic, readonly)  NSUInteger                      endpointAddress;

@property(nonatomic, readonly)  const IOUSBHostCIMessage*       currentTransferMessage;

@property(nonatomic, readonly)  IOUSBHostControllerInterface*   controllerInterface;

@end

NS_ASSUME_NONNULL_END
