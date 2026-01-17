//
//  VZConsoleDevice.h
//  Virtualization
//
//  Copyright © 2022-2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Class representing a console device in a virtual machine.
 @discussion
    VZConsoleDevice should not be instantiated directly.

    Console devices are first configured on the VZVirtualMachineConfiguration through a subclass of VZConsoleDeviceConfiguration.
    When a VZVirtualMachine is created from the configuration, the console devices are available through the VZVirtualMachine.consoleDevices property.

    The real type of VZConsoleDevice corresponds to the type used by the configuration.
    For example, a VZVirtioConsoleDeviceConfiguration leads to a device of type VZVirtioConsoleDevice.
 @see VZConsoleDeviceConfiguration
 */
VZ_EXPORT API_AVAILABLE(macos(13.0))
@interface VZConsoleDevice : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
