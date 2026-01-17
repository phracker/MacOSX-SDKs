//
//  VZMemoryBalloonDevice.h
//  Virtualization
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Base class representing a memory balloon device in a virtual machine.
 @discussion
    VZMemoryBalloonDevice should not be instantiated directly.

    Memory balloon devices are first configured on the VZVirtualMachineConfiguration through a subclass of VZMemoryBalloonDeviceConfiguration.
    When a VZVirtualMachine is created from the configuration, the memory balloon devices are available through the VZVirtualMachine.memoryBalloonDevices property.

    The real type of VZMemoryBalloonDevice corresponds to the type used by the configuration.
    For example, a VZVirtioTraditionalMemoryBalloonDeviceConfiguration leads to a device of type VZVirtioTraditionalMemoryBalloonDevice.
 @see VZVirtioTraditionalMemoryBalloonDevice
 @see VZVirtioTraditionalMemoryBalloonDeviceConfiguration
 */
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZMemoryBalloonDevice : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
