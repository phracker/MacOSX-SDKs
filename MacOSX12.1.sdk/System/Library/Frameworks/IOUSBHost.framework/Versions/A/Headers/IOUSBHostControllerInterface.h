//
//  IOUSBHostControllerInterface.h
//  IOUSBHostControllerInterface
//
//  Copyright © 2020 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IOKit/IOKitLib.h>
#import <IOUSBHost/IOUSBHostControllerInterfaceDefinitions.h>
#import <IOUSBHost/IOUSBHostCIControllerStateMachine.h>
#import <IOUSBHost/IOUSBHostCIPortStateMachine.h>

NS_ASSUME_NONNULL_BEGIN
/*!
 * @class   IOUSBHostControllerInterface
 * @brief   The object representing a user-mode USB host controller
 * @details IOUSBHostControllerInterface enables a process to instantiate a USB host controller to provide access to remote USB devices or create synthetic USB devices.
 *          The entitlement com.apple.developer.usb.host-controller-interface is required to use this class.
 *          The com.apple.iokit.usb.framework.IOUSBHost subsystem is used for logging.
 */

/* Example instantiation
const IOUSBHostCIMessage _capabilities = {
    .control =   (IOUSBHostCIMessageTypeControllerCapabilities << IOUSBHostCIMessageControlTypePhase)
               | IOUSBHostCIMessageControlNoResponse
               | IOUSBHostCIMessageControlValid
               | (1 << IOUSBHostCICapabilitiesMessageControlPortCountPhase),                // Port count
    .data0   =   (1 << IOUSBHostCICapabilitiesMessageData0CommandTimeoutThresholdPhase)     // 2 seconds
               | (2 << IOUSBHostCICapabilitiesMessageData0ConnectionLatencyPhase),          // 4ms
    .data1   = 0
};

const IOUSBHostCIMessage _portCapabilities = {
    .control =   (IOUSBHostCIMessageTypePortCapabilities << IOUSBHostCIMessageControlTypePhase)
               | IOUSBHostCIMessageControlNoResponse
               | IOUSBHostCIMessageControlValid
               | (1 << IOUSBHostCIPortCapabilitiesMessageControlPortNumberPhase)
               | (0 << IOUSBHostCIPortCapabilitiesMessageControlConnectorTypePhase),        // ACPI TypeA
    .data0   = ((907 / 8) << IOUSBHostCIPortCapabilitiesMessageData0MaxPowerPhase),         // Max power for the power (8mA units)
    .data1   = 0
};

IOUSBHostControllerInterfaceCommandHandler commandHandler = ^(IOUSBHostControllerInterface * _Nonnull controller, IOUSBHostCIMessage command)
{
};

IOUSBHostControllerInterfaceDoorbellHandler doorbellHandler = ^(IOUSBHostControllerInterface* controller, IOUSBHostCIDoorbell* doorbellArray, uint32_t doorbellCount)
{
};

void interestHandler(void* refCon, io_service_t service, uint32_t messageType, void* messageArgument)
{
}

int main(int argc, const char * argv[])
{
    @autoreleasepool
    {
        NSMutableData* capabilitiesData = [[NSMutableData alloc] initWithBytes:&_capabilities length:sizeof(IOUSBHostCIMessage)];
        [capabilitiesData appendBytes:&_portCapabilities length:sizeof(IOUSBHostCIMessage)];
        
        NSError* error = [[NSError alloc] initWithDomain:IOUSBHostErrorDomain code:KERN_SUCCESS userInfo:nil];
        
        IOUSBHostControllerInterface* controller = [[IOUSBHostControllerInterface alloc] initWithCapabilities:capabilitiesData
                                                                                                        queue:nil
                                                                                              interruptRateHz:1000
                                                                                                        error:&error
                                                                                               commandHandler:commandHandler
                                                                                              doorbellHandler:doorbellHandler
                                                                                              interestHandler:interestHandler];

        if(error.code == KERN_SUCCESS)
        {
            dispatch_main();
        }
    }
    return 0;
}
 */

@interface IOUSBHostControllerInterface : NSObject

/*!
 * @typedef     IOUSBHostControllerInterfaceCommandHandler
 * @brief       Client-supplied block to handle IOUSBHostCIMessage structures representing controller, port, device, or endpoint commands
 * @discussion  The kernel driver controls the state of the client's USB services via commands that target the controller, port, device, or endpoint.  The command response
 *              must be received by the kernel driver before a new command will be sent.
 *
 *              Commands with a type targeting the controller (IOUSBHostCIMessageTypeController*) should be processed by the IOUSBHostCIControllerStateMachine
 *              available via the IOUSBHostControllerInterface's controllerStateMachine property.
 *
 *              Commands with a type targeting the root ports (IOUSBHostCIMessageTypePort*) should be processed by the IOUSBHostCIPortStateMachines
 *              available via the getPortStateMachineForCommand interface.
 *
 *              Commands with a type targeting a device (IOUSBHostCIMessageTypeDevice*) should be processed by a client-created IOUSBHostCIDeviceStateMachine.
 *
 *              Commands with a type targeting an endpoint (IOUSBHostCIMessageTypeEndpoint*) should be processed by a client-created IOUSBHostCIEndpointStateMachine.
 */
typedef void (^ IOUSBHostControllerInterfaceCommandHandler)(IOUSBHostControllerInterface* controller, IOUSBHostCIMessage command);

/*!
 * @typedef     IOUSBHostControllerInterfaceDoorbellHandler
 * @brief       Client-supplied block to handle IOUSBHostCIDoorbell messages
 * @discussion  The kernel driver sends IOUSBHostCIDoorbell messages to notify the client that transfer structures for specific endpoints have been updated.  Doorbell messages
 *              should be processed by a client-created IOUSBHostCIEndpointStateMachine.
 */
typedef void (^ IOUSBHostControllerInterfaceDoorbellHandler)(IOUSBHostControllerInterface* controller, IOUSBHostCIDoorbell* doorbellArray, uint32_t doorbellCount);

#pragma mark session management and creation

- (instancetype)init __attribute__((unavailable("Please use initWithCapabilities:queue:interruptRateHz:error:commandHandler:doorbellHandler:interestHandler.")));

/*!
 * @brief       Initializes IOUSBHostControllerInterface object along with a user client
 * @discussion  If the user client cannot be created, nil will be returned.
 *              When done using the object, destroy must be called on the object.
 * @param       capabilities NSData containing an array of IOUSBHostCIMessage structures.  The first must have an IOUSBHostCIMessageControlType of IOUSBHostCIMessageTypeControllerCapabilities,
 *              followed by at least one message with an IOUSBHostCIMessageControlType of IOUSBHostCIMessageTypePortCapabilities.
 * @param       queue A serial queue to service asynchronous operations. If nil, a serial queue will be created on behalf of the client.
 * @param       interruptRateHz NSUInteger representing the rate in Hz at which interrupts will be delivered to the kernel driver.
 *              A value ot 0 will send all interrupts to the kernel immediately.
 * @param       commandHandler IOUSBHostControllerInterfaceCommandHandler used to process IOUSBHostCIMessage messages sent by the kernel driver.
 * @param       doorbellHandler IOUSBHostControllerInterfaceDoorbellHandler used to process IOUSBHostCIDoorbell values sent by the kernel driver.
 * @param       interestHandler IOServiceInterestCallback used to process service state changes such as termination. See IOServiceAddInterestNotification
 *              in IOKitLib for more details. All notifications will be serviced on an internal serial queue separate from command and doorbell handlers.
 * @return      An IOUSBHostControllerInterface. The object is to be released by the caller.
 */
-(nullable instancetype)initWithCapabilities:(NSData*)capabilities
                                        queue:(nullable dispatch_queue_t)queue
                              interruptRateHz:(NSUInteger)interruptRateHz
                                        error:(NSError**)error
                               commandHandler:(IOUSBHostControllerInterfaceCommandHandler)commandHandler
                              doorbellHandler:(IOUSBHostControllerInterfaceDoorbellHandler)doorbellHandler
                              interestHandler:(nullable IOServiceInterestCallback)interestHandler NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

/*!
 * @brief       Removes underlying allocations of the IOUSBHostControllerInterface object along with user client
 * @discussion  When the IOUSBHostControllerInterface is no longer needed, destroy must be called. This will destroy
 *              the connection with the user client and de-register interest on the service. If the object
 *              is freed, destroy will be called automatically. Calling destroy multiple times has no effect.
 */
-(void)destroy;

/*!
 * @brief       The dispatch queue for asynchronous operations.
 */
@property(readonly) dispatch_queue_t queue;

#pragma mark interrupts to kernel driver

/*!
 * @brief       Enqueue an interrupt for delivery to the kernel service
 * @discussion  This method enqueues one interrupt message for delivery to the kernel service.  interruptRateHz is used to determine when the interrupt message is
 *              delivered to the kernel service.
 * @param       interrupt An IOUSBHostCIMessage structure representing an interrupt message
 */
-(BOOL)enqueueInterrupt:(const IOUSBHostCIMessage*)interrupt
                  error:(NSError**)error;

/*!
 * @brief       Enqueue an interrupt for delivery to the kernel service
 * @discussion  This method enqueues one interrupt message for delivery to the kernel service.
 * @param       interrupt An IOUSBHostCIMessage structure representing an interrupt message
 * @param       expedite Bool NO to use interruptRateHz to determine when the interrupt message is delivered to the kernel service. Bool YES if interruptRateHz
 *              should be ignored, sending the message to the kernel driver at the next opportunity while maintaining in-order delivery of all interrupt messages.
 */
-(BOOL)enqueueInterrupt:(const IOUSBHostCIMessage*)interrupt
               expedite:(BOOL)expedite
                  error:(NSError**)error;

/*!
 * @brief       Enqueue interrupts for delivery to the kernel service
 * @discussion  This method enqueues one or more interrupt messages for delivery to the kernel service.   interruptRateHz is used to determine when the interrupt message is
 *              delivered to the kernel service.
 * @param       interrupts An IOUSBHostCIMessage structure representing one or more interrupt messages
 * @param       count The number of interrupt messages represented by the interrupts parameter
*/
-(BOOL)enqueueInterrupts:(const IOUSBHostCIMessage*)interrupts
                   count:(NSUInteger)count
                   error:(NSError**)error;

/*!
 * @brief       Enqueue interrupts for delivery to the kernel service
 * @discussion  This method enqueues one or more interrupt messages for delivery to the kernel service.   interruptRateHz is used to determine when the interrupt message is
 *              delivered to the kernel service.
 * @param       interrupts An IOUSBHostCIMessage structure representing one or more interrupt messages
 * @param       count The number of interrupt messages represented by the interrupts parameter
 * @param       expedite Bool NO to use interruptRateHz to determine when the interrupt message is delivered to the kernel service. Bool YES if interruptRateHz
 *              should be ignored, sending the message to the kernel driver at the next opportunity while maintaining in-order delivery of all interrupt messages.
*/
-(BOOL)enqueueInterrupts:(const IOUSBHostCIMessage*)interrupts
                   count:(NSUInteger)count
                expedite:(BOOL)expedite
                   error:(NSError**)error;

/*!
 * @brief       The interrupt moderation rate for sending interrupt messages to the kernel driver
 * @discussion  interruptRateHz will cause submitted interrupt messages to be batched together and submitted to the kernel
 *              at the specified rate.  A value ot 0 will deliver all interrupts to the kernel driver as soon as possible.
 */
@property(nonatomic) NSUInteger interruptRateHz;

#pragma mark command state machines

@property(nonatomic, readonly) IOUSBHostCIControllerStateMachine* controllerStateMachine;

-(IOUSBHostCIPortStateMachine*) getPortStateMachineForCommand:(const IOUSBHostCIMessage*)command
                                                        error:(NSError**)error;

#pragma mark static properties

/*!
 * @brief       The capabilities structure passed in during initialization
 * @discussion  The capabilities passed into the initializer can be retrieved for reference.
 * */
@property(nonatomic, readonly) const IOUSBHostCIMessage* capabilities;

/*!
 * @brief       Retrieve a port capabilities structure passed in during initialization
 */
-(const IOUSBHostCIMessage*)capabilitiesForPort:(NSUInteger)port;

/*!
 * @brief       A UUID used to identify the host controller interface in this process and the kernel
 */
@property(nonatomic, readonly) NSUUID* uuid;

@end

NS_ASSUME_NONNULL_END
