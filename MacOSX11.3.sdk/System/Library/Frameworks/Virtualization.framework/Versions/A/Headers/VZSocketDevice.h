//
//  VZSocketDevice.h
//  Virtualization
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Base class representing a socket device in a virtual machine.
 @discussion
    VZSocketDevice should not be instantiated directly.

    Socket devices are first configured on the VZVirtualMachineConfiguration through a subclass of VZSocketDeviceConfiguration.
    When a VZVirtualMachine is created from the configuration, the socket devices are available through the VZVirtualMachine.socketDevices property.

    The real type of VZSocketDevice corresponds to the type used by the configuration.
    For example, a VZVirtioSocketDeviceConfiguration leads to a device of type VZVirtioSocketDevice.
 @see VZVirtioSocketDevice
 @see VZVirtioSocketDeviceConfiguration
 */
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZSocketDevice : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
