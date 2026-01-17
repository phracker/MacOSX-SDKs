//
//  IOUSBHostCIControllerStateMachine.h
//  IOUSBHostFramework
//
//  Created by Dan Wilson on 4/23/20.
//

#import <Foundation/Foundation.h>
#import <IOUSBHost/IOUSBHostControllerInterfaceDefinitions.h>

@class IOUSBHostControllerInterface;

NS_ASSUME_NONNULL_BEGIN

/*!
 * @class   IOUSBHostCIControllerStateMachine
 * @brief   The object representing the state of a user-mode USB host controller
 * @details This class assists with tracking internal state transitions of a user-mode USB host controller, and parses IOUSBHostCIMessage command
 *          structures to update state and generate properly formatted command responses.
 */
@interface IOUSBHostCIControllerStateMachine : NSObject

- (instancetype)init __attribute__((unavailable("Please use initWithInterface")));

/*!
 * @brief       Initializes an IOUSBHostCIControllerStateMachine object
 * @discussion  The IOUSBHostCIControllerStateMachine defaults to the IOUSBHostCIControllerStateOff state.
 * @param       interface IOUSBHostControllerInterface which will be used to send command responses.
 * @return      IOUSBHostCIControllerStateMachine instance, to be released by the caller.
 */
-(nullable instancetype)initWithInterface:(IOUSBHostControllerInterface*)interface
                                    error:(NSError**)error NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

/*!
 * @brief       Inspect an IOUSBHostCIMessage command
 * @discussion  The IOUSBHostCIMessage command is inspected to determine if it is handled by the state machine, and
 *              is appropriate for the current state.
 * @param       command IOUSBHostCIMessage command structure received from the kernel driver.
 * @return      BOOL YES if the command is targeting a controller, and can be handled in the current state
 *              BOOL NO if the command does not target a controller, or cannot be handled in the current state
*/
-(BOOL)inspectCommand:(const IOUSBHostCIMessage*)command
                error:(NSError**)error;

/*!
 * @brief       Advance the state machine and respond to an IOUSBHostCIMessage command
 * @discussion  If the command passes inspectCommand and the client indicates the command was processed successfully, the state machine is
 *              advanced, and a properly formatted command response message is sent to the kernel driver.  If the client indicates the command was
 *              not processed successfully, the state machine is not advanced but a properly formatted command response message is sent to the kernel
 *              driver.
 * @param       command IOUSBHostCIMessage command structure received from the kernel driver.
 * @param       status IOUSBHostCIMessageStatus reported by the user-mode USB host controller implementation for the command response.
 * @return      BOOL YES if the command response was sent to the kernel driver
 *              BOOL NO if the command response was not sent to the kernel driver
*/
-(BOOL)respondToCommand:(const IOUSBHostCIMessage*)command
                 status:(const IOUSBHostCIMessageStatus)status
                  error:(NSError**)error;

/*!
 * @brief       Advance the state machine and respond to an IOUSBHostCIMessageTypeControllerFrameNumber command
 * @discussion  If the command passes inspectCommand and the client indicates the command was processed successfully, the state machine is
 *              advanced, and a properly formatted command response message is sent to the kernel driver.  If the client indicates the command was
 *              not processed successfully, the state machine is not advanced but a properly formatted command response message is sent to the kernel
 *              driver.
 * @param       command IOUSBHostCIMessage command structure received from the kernel driver.  The Type field must be IOUSBHostCIMessageTypeControllerFrameNumber
 * @param       status IOUSBHostCIMessageStatus reported by the user-mode USB host controller implementation for the command response.
 * @param       frame uint64_t containing the number of 1ms frames that have elapsed since the controller began counting frames
 * @param       timestamp uint64_t containing the mach_absolute_time() correlated to the beginning of the frameNumber
 * @return      BOOL YES if the command response was sent to the kernel driver
 *              BOOL NO if the command response was not sent to the kernel driver
*/
-(BOOL)respondToCommand:(const IOUSBHostCIMessage*)command
                 status:(const IOUSBHostCIMessageStatus)status
                  frame:(uint64_t)frame
              timestamp:(uint64_t)timestamp
                  error:(NSError**)error;

/*!
 * @brief       Enqueue frame and timestamp messages for delivery to the kernel driver
 * @discussion  If the controller interface is in the IOUSBHostCIControllerStateActive state, messages with the type IOUSBHostCIMessageTypeFrameNumberUpdate and
 *              IOUSBHostCIMessageTypeFrameTimestampUpdate will be generated using the provided inputs, and enqueued for delivery to the kernel driver.
 * @param       frame uint64_t containing the number of 1ms frames that have elapsed since the controller began counting frames
 * @param       timestamp uint64_t containing the mach_absolute_time() correlated to the beginning of the frameNumber
 * @return      BOOL YES if the messages were enqueued for delivery to the kernel.
 *              BOOL NO if the messages were not enqueued for delivery to the kernel.
*/
-(BOOL)enqueueUpdatedFrame:(uint64_t)frame
                 timestamp:(uint64_t)timestamp
                     error:(NSError**)error;

@property(nonatomic, readonly)  IOUSBHostCIControllerState      controllerState;

@property(nonatomic, readonly)  IOUSBHostControllerInterface*   controllerInterface;

@end

NS_ASSUME_NONNULL_END
