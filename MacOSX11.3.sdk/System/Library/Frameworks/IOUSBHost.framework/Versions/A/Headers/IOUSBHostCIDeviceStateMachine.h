//
//  IOUSBHostCIDeviceStateMachine.h
//  IOUSBHostFramework
//
//  Created by Dan Wilson on 4/28/20.
//

#import <Foundation/Foundation.h>
#import <IOUSBHost/IOUSBHostControllerInterfaceDefinitions.h>

@class IOUSBHostControllerInterface;

NS_ASSUME_NONNULL_BEGIN

/*!
 * @class   IOUSBHostCIDeviceStateMachine
 * @brief   The object representing the state of a user-mode USB host controller device
 * @details This class assists with tracking internal state transitions of a user-mode USB host controller device, and parses IOUSBHostCIMessage command
 *          structures to update state and generate properly formatted command responses.
 */
@interface IOUSBHostCIDeviceStateMachine : NSObject

- (instancetype)init __attribute__((unavailable("Please use initWithInterface:command")));

/*!
 * @brief       Initializes an IOUSBHostCIDeviceStateMachine object
 * @discussion  The IOUSBHostCIDeviceStateMachine defaults to the IOUSBHostCIDeviceStateActive state.
 * @param       interface IOUSBHostControllerInterface which will be used to send command responses.
 * @param       command IOUSBHostCIMessage with type IOUSBHostCIMessageTypeDeviceCreate
 * @return      IOUSBHostCIDeviceStateMachine instance, to be released by the caller.
 */
-(nullable instancetype)initWithInterface:(IOUSBHostControllerInterface*)interface
                                  command:(const IOUSBHostCIMessage*)command
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
 * @brief       Advance the state machine and respond to an IOUSBHostCIMessageTypeDeviceCreate command
 * @discussion  If the command passes inspectCommand and the client indicates the command was processed successfully, the state machine is
 *              advanced, and a properly formatted command response message is sent to the kernel driver.  If the client indicates the command was
 *              not processed successfully, the state machine is not advanced but a properly formatted command response message is sent to the kernel
 *              driver.
 * @param       command IOUSBHostCIMessage command structure received from the kernel driver.  The Type field must be IOUSBHostCIMessageTypeDeviceCreate
 * @param       status IOUSBHostCIMessageStatus reported by the user-mode USB host controller implementation for the command response.
 * @param       deviceAddress NSUInteger used only when responding to the initial IOUSBHostCIMessageTypeDeviceCreate command, containing
 *              a valid USB device address successfully assigned to the device.
 * @return      BOOL YES if the command response was sent to the kernel driver
 *              BOOL NO if the command response was not sent to the kernel driver
*/-(BOOL)respondToCommand:(const IOUSBHostCIMessage*)command
                 status:(const IOUSBHostCIMessageStatus)status
          deviceAddress:(NSUInteger)deviceAddress
                  error:(NSError**)error;


@property(nonatomic, readonly)  IOUSBHostCIDeviceState          deviceState;

@property(nonatomic, readonly)  NSUInteger                      completeRoute;

@property(nonatomic, readonly)  NSUInteger                      deviceAddress;

@property(nonatomic, readonly)  IOUSBHostControllerInterface*   controllerInterface;

@end

NS_ASSUME_NONNULL_END
