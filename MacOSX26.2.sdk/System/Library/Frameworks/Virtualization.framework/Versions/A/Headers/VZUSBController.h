//
//  VZUSBController.h
//  Virtualization
//
//  Copyright © 2023-2025 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

@protocol VZUSBDevice;

/*!
 @abstract Class representing a USB controller in a virtual machine.
 @discussion
    VZUSBController should not be instantiated directly.
    USB controllers are first configured on the VZVirtualMachineConfiguration through a subclass of VZUSBControllerConfiguration.
    When a VZVirtualMachine is created from the configuration, the USB controllers are available through the VZVirtualMachine.usbControllers property.
    The real type of VZUSBController corresponds to the type used by the configuration.
    For example, a VZXHCIControllerConfiguration leads to a device of type VZXHCIController.
 @see VZUSBControllerConfiguration
 */
VZ_EXPORT API_AVAILABLE(macos(15.0))
@interface VZUSBController : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Attach a USB device.
 @discussion
    If the device is successfully attached to the controller, it will appear in the usbDevices property,
    its usbController property will be set to point to the USB controller that it is attached to
    and completion handler will return nil.
    If the device was previously attached to this or another USB controller, attach function will fail
    with the `VZErrorDeviceAlreadyAttached`. If the device cannot be initialized correctly, attach
    function will fail with `VZErrorDeviceInitializationFailure`.
    This method must be called on the virtual machine's queue.
 @param device USB device to attach.
 @param completionHandler Block called after the device has been attached or on error.
    The error parameter passed to the block is nil if the attach was successful.
    It will be also invoked on an virtual machine's queue.
 @see VZUSBDevice
 */
- (void)attachDevice:(id <VZUSBDevice>)device completionHandler:(void (^ NS_SWIFT_NONSENDABLE)(NSError * _Nullable errorOrNil))completionHandler NS_SWIFT_NAME(attach(device:completionHandler:));

/*!
 @abstract Detach a USB device.
 @discussion
    If the device is successfully detached from the controller, it will disappear from the usbDevices property,
    its usbController property will be set to nil and completion handler will return nil.
    If the device wasn't attached to the controller at the time of calling detach method, it will fail
    with the `VZErrorDeviceNotFound` error.
    This method must be called on the virtual machine's queue.
 @param device USB device to detach.
 @param completionHandler Block called after the device has been detached or on error.
    The error parameter passed to the block is nil if the detach was successful.
    It will be also invoked on an virtual machine's queue.
 @see VZUSBDevice
 */
- (void)detachDevice:(id <VZUSBDevice>)device completionHandler:(void (^ NS_SWIFT_NONSENDABLE)(NSError * _Nullable errorOrNil))completionHandler NS_SWIFT_NAME(detach(device:completionHandler:));

/*!
 @abstract Return a list of USB devices attached to controller.
 @discussion
    If corresponding USB controller configuration included in VZVirtualMachineConfiguration contained  any USB devices,
    those devices will appear here when virtual machine is started.
 @see VZUSBDevice
 @see VZUSBDeviceConfiguration
 @see VZUSBControllerConfiguration
 @see VZVirtualMachineConfiguration
 */
@property (readonly, copy) NSArray<id <VZUSBDevice>> *usbDevices;

@end

NS_ASSUME_NONNULL_END
