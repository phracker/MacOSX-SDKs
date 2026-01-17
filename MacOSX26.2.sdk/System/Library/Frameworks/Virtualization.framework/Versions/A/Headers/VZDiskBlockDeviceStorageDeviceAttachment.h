//
//  VZDiskBlockDeviceStorageDeviceAttachment.h
//  Virtualization
//
//  Copyright © 2022-2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDiskSynchronizationMode.h>
#import <Virtualization/VZStorageDeviceAttachment.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Storage device attachment using a disk block device to store data.
 @discussion
    The disk block device implements a storage attachment by using an actual disk rather than a disk image on a file system.

    For example, a disk block device on the disk at `/dev/rdisk42` would execute the I/O operations directly on that disk
    rather than through a file system.

    Note that if the disk has a file system formatted on it, the guest is able to destroy data in a way that is not recoverable.
    The disk passed to this attachment needs to be handled with caution.

    An example use of this API is:
    ```
    NSFileHandle *fileHandle = [NSFileHandle fileHandleForReadingAtPath:@"/dev/rdisk42"];
    if (!fileHandle) {
        // Handle errors.
    }

    NSError *error;
    VZDiskBlockDeviceStorageDeviceAttachment *attachment =
        [[VZDiskBlockDeviceStorageDeviceAttachment alloc] initWithFileHandle:fileHandle
                                                                     readOnly:YES
                                                          synchronizationMode:VZDiskSynchronizationModeFull
                                                                        error:error];
    if (!attachment) {
        // Handle errors.
    }
    ```

    Disk file handles are typically only accessible by the `root` user unless permission is explicitly granted.
    Running virtual machines as root is not recommended. If `root` access is required to open the file descriptor, it is recommended to do that operation
    in a separate process then pass the file descriptor to a less privileged process running Virtualization framework.

 @see VZDiskImageStorageDeviceAttachment
 @see VZNVMExpressControllerDeviceConfiguration
 @see VZUSBMassStorageDeviceConfiguration
 @see VZVirtioBlockDeviceConfiguration
 */
VZ_EXPORT API_AVAILABLE(macos(14.0))
@interface VZDiskBlockDeviceStorageDeviceAttachment : VZStorageDeviceAttachment

/*!
 @abstract Initialize the disk attachment from a file handle.
 @param fileHandle File handle to a block device.
 @param readOnly If YES, the disk attachment is read only, otherwise, if the file handle allows writes, the device can write data into it.
 @param synchronizationMode Defines how the disk synchronizes with the underlying storage when the guest operating system flushes data.
 @param error If not nil, assigned with the error if the initialization failed.
 @return An initialized `VZDiskBlockDeviceStorageDeviceAttachment` or nil if there was an error.
 @discussion
    The file handle is retained by the disk attachment.
    The handle must be open when the virtual machine starts.

    The `readOnly` parameter affects how the disk is exposed to the guest operating system
    by the storage controller. If the disk is intended to be used read-only, it is also recommended
    to open the file handle as read-only.
 */
- (nullable instancetype)initWithFileHandle:(NSFileHandle *)fileHandle readOnly:(BOOL)readOnly synchronizationMode:(VZDiskSynchronizationMode)synchronizationMode error:(NSError **)error NS_DESIGNATED_INITIALIZER;

/*!
 @abstract File handle to the underlying disk used for storage by the attachment.
*/
@property (readonly, strong) NSFileHandle *fileHandle;

/*!
 @abstract Whether the underlying disk attachment is read-only.
*/
@property (readonly, getter=isReadOnly) BOOL readOnly;

/*!
 @abstract The mode in which the disk image synchronizes data with the underlying storage device.
*/
@property (readonly) VZDiskSynchronizationMode synchronizationMode;

@end

NS_ASSUME_NONNULL_END
