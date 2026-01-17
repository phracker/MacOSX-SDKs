//
//  VZGraphicsDevice.h
//  Virtualization
//
//  Copyright © 2019-2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class VZGraphicsDisplay;

/*!
 @abstract Class representing a graphics device in a virtual machine.
 @discussion
    VZGraphicsDevice should not be instantiated directly.

    Graphics devices are first configured on the VZVirtualMachineConfiguration through a subclass of VZGraphicsDeviceConfiguration.
    When a VZVirtualMachine is created from the configuration, the graphics devices are available through the VZVirtualMachine.graphicsDevices property.

    The real type of VZGraphicsDevice corresponds to the type used by the configuration.
    For example, a VZVirtioGraphicsDeviceConfiguration leads to a device of type VZVirtioGraphicsDevice.
    And a VZMacGraphicsDeviceConfiguration leads to a device of type VZMacGraphicsDevice.
 @see VZGraphicsDeviceConfiguration
 */
VZ_EXPORT API_AVAILABLE(macos(14.0))
@interface VZGraphicsDevice : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Return the list of graphics displays configured for this graphics device.
 @discussion Graphics displays are configured on the graphics device configuration.
 @see VZMacGraphicsDisplayConfiguration
 @see VZVirtioGraphicsScanoutConfiguration
 */
@property (readonly, copy) NSArray<VZGraphicsDisplay *> *displays;

@end

NS_ASSUME_NONNULL_END
