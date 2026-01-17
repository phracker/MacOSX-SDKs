//
//  VZMacGraphicsDisplay.h
//  Virtualization
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZGraphicsDisplay.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Class representing a virtual Mac graphics display.
 @discussion
    The VZMacGraphicsDisplay is the runtime counterpart of VZMacGraphicsDisplayConfiguration.

    When a graphics device is configured with class VZMacGraphicsDisplayConfiguration,
    the VZGraphicsDevice's displays are in the same order as their configuration objects and they have the type VZMacGraphicsDisplay.

    For example, if when setting up a virtual Mac, `VZMacGraphicsDeviceConfiguration.displays[0]` is a `VZMacGraphicsDisplayConfiguration`,
    then after creating a virtual machine from the configuration, the `VZVirtualMachine.graphicsDevices` is a `VZMacGraphicsDevice`.
    The `VZMacGraphicsDevice.displays[0]` is a `VZMacGraphicsDisplay` corresponding to the `VZMacGraphicsDeviceConfiguration` in the configuration.

 @see VZMacGraphicsDisplayConfiguration
 @see VZGraphicsDevice
 */
VZ_EXPORT API_AVAILABLE(macos(14.0))
@interface VZMacGraphicsDisplay : VZGraphicsDisplay

/*!
 @abstract The pixel density as a number of pixels per inch.
*/
@property (readonly) NSInteger pixelsPerInch;

@end

NS_ASSUME_NONNULL_END
