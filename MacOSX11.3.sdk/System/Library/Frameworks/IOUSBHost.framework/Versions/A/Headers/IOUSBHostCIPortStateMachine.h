//
//  IOUSBHostCIPortStateMachine.h
//  IOUSBHostFramework
//
//  Created by Dan Wilson on 4/27/20.
//

#import <Foundation/Foundation.h>
#import <IOUSBHost/IOUSBHostControllerInterfaceDefinitions.h>

@class IOUSBHostControllerInterface;

NS_ASSUME_NONNULL_BEGIN

/*!
 * @class   IOUSBHostCIPortStateMachine
 * @brief   The object representing the state of a user-mode USB host controller root port
 * @details This class assists with tracking internal state transitions of a user-mode USB host controller root port, and parses IOUSBHostCIMessage command
 *          structures to update state and generate properly formatted command responses.
 */
@interface IOUSBHostCIPortStateMachine : NSObject

- (instancetype)init __attribute__((unavailable("Please use initWithInterface")));

/*!
 * @brief       Initializes an IOUSBHostCIPortStateMachine object
 * @discussion  The IOUSBHostCIPortStateMachine defaults to the IOUSBHostCIPortStateOff state.
 * @param       interface IOUSBHostControllerInterface which will be used to send command responses.
 * @param       portNumber NSUInteger for the root port number tracked by this instance
 * @return      IOUSBHostCIPortStateMachine instance, to be released by the caller.
 */
-(nullable instancetype)initWithInterface:(IOUSBHostControllerInterface*)interface
                               portNumber:(NSUInteger)portNumber
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

@property(nonatomic, readonly)  NSUInteger                      portNumber;

@property(nonatomic, readonly)  IOUSBHostCIPortState            portState;

@property(nonatomic, readonly)  IOUSBHostCIPortStatus           portStatus;

@property(nonatomic, readonly)  IOUSBHostControllerInterface*   controllerInterface;

@property(nonatomic, readwrite) BOOL                            powered;

@property(nonatomic, readwrite) BOOL                            connected;

@property(nonatomic, readwrite) BOOL                            overcurrent;

-(BOOL)updateLinkState:(const IOUSBHostCILinkState)linkState
                 speed:(const IOUSBHostCIDeviceSpeed)speed
inhibitLinkStateChange:(const BOOL)inhibitLinkStateChange
                 error:(NSError**)error;

@property(nonatomic, readonly)  IOUSBHostCILinkState            linkState;

@property(nonatomic, readonly)  IOUSBHostCIDeviceSpeed          speed;

@end

NS_ASSUME_NONNULL_END
