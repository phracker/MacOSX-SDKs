//
//  VZVirtioConsoleDeviceConfiguration.h
//  Virtualization
//
//  Copyright © 2022-2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZConsoleDeviceConfiguration.h>
#import <Virtualization/VZVirtioConsolePortConfigurationArray.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Virtio Console Device
 @discussion
    This console device enables communication between the host and the guest using console ports through the Virtio interface.

    The device sets up one or more ports via VZVirtioConsolePortConfiguration on the Virtio console device.
 @see VZVirtioConsolePortConfiguration
 @see VZVirtualMachineConfiguration.consoleDevices
 */
VZ_EXPORT API_AVAILABLE(macos(13.0))
@interface VZVirtioConsoleDeviceConfiguration : VZConsoleDeviceConfiguration

- (instancetype)init NS_DESIGNATED_INITIALIZER;

/*!
 @abstract The console ports to be configured for this console device.
 */
@property (readonly, strong) VZVirtioConsolePortConfigurationArray *ports;

@end

NS_ASSUME_NONNULL_END
