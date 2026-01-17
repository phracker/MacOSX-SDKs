//
//  VZVirtioGraphicsDevice.h
//  Virtualization
//
//  Copyright © 2022-2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZGraphicsDevice.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract A Virtio graphics device.
 @discussion
    The VZVirtioGraphicsDevice is the runtime counterpart of VZVirtioGraphicsDeviceConfiguration.

    For example, if a `VZVirtualMachineConfiguration.graphicsDevices[0]` is an instance of `VZVirtioGraphicsDeviceConfiguration`, when creating the virtual machine, the `VZVirtualMachine.graphicsDevices[0]` is the corresponding `VZVirtioGraphicsDevice`.

    An important property is the `displays` inherited from `VZGraphicsDevice`. It provides the list of scanouts on the graphics device,
    each corresponding to the scanout configuration set on `VZVirtioGraphicsDeviceConfiguration`.

 @see VZVirtioGraphicsDeviceConfiguration
 @see VZGraphicsDevice.displays
 */
VZ_EXPORT API_AVAILABLE(macos(14.0))
@interface VZVirtioGraphicsDevice : VZGraphicsDevice

@end

NS_ASSUME_NONNULL_END
