//
//  VZDirectorySharingDevice.h
//  Virtualization
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Base class representing a directory sharing device in a virtual machine.
 @discussion
    VZDirectorySharingDevice should not be instantiated directly.

    Directory sharing devices are first configured on the VZVirtualMachineConfiguration through a subclass of VZDirectorySharingDeviceConfiguration.
    When a VZVirtualMachine is created from the configuration, the directory sharing devices are available through the VZVirtualMachine.directorySharingDevices property.

    The real type of VZDirectorySharingDevice corresponds to the type used by the configuration.
    For example, a VZVirtioFileSystemDeviceConfiguration leads to a device of type VZVirtioFileSystemDevice.
 @see VZVirtioFileSystemDevice
 @see VZVirtioFileSystemDeviceConfiguration
 */
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZDirectorySharingDevice : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
