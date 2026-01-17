//
//  VZXHCIController.h
//  Virtualization
//
//  Copyright © 2023-2024 Apple Inc. All rights reserved.
//

#import <Virtualization/VZUSBController.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Class representing a USB XHCI controller in a virtual machine.
 @discussion
    VZXHCIController should not be instantiated directly.
    In order to create a runtime VZXHCIController object, the usbControllers property of
    VZVirtualMachineConfiguration object needs to be populated with VZXHCIControllerConfiguration object.
 @see VZUSBController
 @see VZXHCIControllerConfiguration
 */
VZ_EXPORT API_AVAILABLE(macos(15.0))
@interface VZXHCIController : VZUSBController

@end

NS_ASSUME_NONNULL_END
