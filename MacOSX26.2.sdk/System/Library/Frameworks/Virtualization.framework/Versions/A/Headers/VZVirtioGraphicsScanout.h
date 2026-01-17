//
//  VZVirtioGraphicsScanout.h
//  Virtualization
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZGraphicsDisplay.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Class representing a Virtio graphics device scanout.
 @discussion
    The VZVirtioGraphicsScanout is the runtime counterpart of VZVirtioGraphicsScanoutConfiguration.

    When a graphics device is configured with class VZVirtioGraphicsScanoutConfiguration,
    the VZGraphicsDevice's displays are in the same order as their configuration objects and they have the type VZVirtioGraphicsScanout.

    For example, if when setting up a virtual machine, its `VZVirtioGraphicsDeviceConfiguration.scanouts[0]` is a `VZVirtioGraphicsScanoutConfiguration`,
    then after creating a virtual machine from the configuration, the `VZVirtualMachine.graphicsDevices` is a `VZVirtioGraphicsDevice`.
    The `VZVirtioGraphicsDevice.displays[0]` is a `VZVirtioGraphicsScanout` corresponding to the `VZVirtioGraphicsScanoutConfiguration` in the configuration.

 @see VZVirtioGraphicsScanoutConfiguration
 @see VZGraphicsDisplay
 @see VZGraphicsDevice
 */
VZ_EXPORT API_AVAILABLE(macos(14.0))
@interface VZVirtioGraphicsScanout : VZGraphicsDisplay

@end

NS_ASSUME_NONNULL_END
