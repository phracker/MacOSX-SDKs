//
//  VZMacGraphicsDevice.h
//  Virtualization
//
//  Copyright © 2022-2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZGraphicsDevice.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract A Mac graphics device.
 @discussion
    The VZMacGraphicsDevice is the runtime counterpart of VZMacGraphicsDeviceConfiguration.

    For example, if a `VZVirtualMachineConfiguration.graphicsDevices[0]` is an instance of `VZMacGraphicsDeviceConfiguration`, when creating the virtual Mac, the `VZVirtualMachine.graphicsDevices[0]` is the corresponding `VZMacGraphicsDevice`.

    An important property is the `displays` inherited from `VZGraphicsDevice`. It provides the list of displays on the graphics device,
    each corresponding to the display configuration set on `VZMacGraphicsDeviceConfiguration`.

 @see VZMacGraphicsDeviceConfiguration
 @see VZGraphicsDevice.displays
 */
VZ_EXPORT API_AVAILABLE(macos(14.0))
@interface VZMacGraphicsDevice : VZGraphicsDevice

@end

NS_ASSUME_NONNULL_END
