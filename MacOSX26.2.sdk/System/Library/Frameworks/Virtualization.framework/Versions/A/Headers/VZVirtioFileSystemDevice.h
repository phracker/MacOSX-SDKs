//
//  VZVirtioFileSystemDevice.h
//  Virtualization
//
//  Copyright © 2021-2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDirectorySharingDevice.h>

NS_ASSUME_NONNULL_BEGIN

@class VZDirectoryShare;

/*!
 @abstract Virtio File System Device
 @discussion
    This is a device that exposes host resources to the guest as a file system mount.
    The directory share defines which host resources are exposed to the guest.

    This device is created through instantiating a VZVirtioFileSystemDeviceConfiguration in a VZVirtualMachineConfiguration and is available in the
    VZVirtualMachine.directorySharingDevices property.
 @see VZVirtioFileSystemDeviceConfiguration
 @see VZSingleDirectoryShare
 @see VZMultipleDirectoryShare
 */
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZVirtioFileSystemDevice : VZDirectorySharingDevice

/*!
 @abstract The tag is a string identifying the device.
 @discussion The tag is presented as a label in the guest identifying this device for mounting.
 */
@property (readonly, copy) NSString *tag;

/*!
 @abstract Directory share. Defines how host resources are exposed to the guest virtual machine.
 @discussion
    Setting this property to VZLinuxRosettaDirectoryShare is not supported and will cause an exception to be raised.
 @see VZSingleDirectoryShare
 @see VZMultipleDirectoryShare
 */
@property (nullable, strong) VZDirectoryShare *share;

@end

NS_ASSUME_NONNULL_END
