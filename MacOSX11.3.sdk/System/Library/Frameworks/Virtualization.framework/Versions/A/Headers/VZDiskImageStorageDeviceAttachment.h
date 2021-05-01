//
//  VZDiskImageStorageDeviceAttachment.h
//  Virtualization
//
//  Copyright © 2019-2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZStorageDeviceAttachment.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Storage device attachment using a disk image to implement the storage.
 @discussion
    This storage device attachment uses a disk image on the host file system as the drive of the storage device.

    Only raw data disk images are supported.
 @see VZVirtioBlockDeviceConfiguration
 */
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZDiskImageStorageDeviceAttachment : VZStorageDeviceAttachment

/*!
 @abstract Initialize the attachment from a local file url.
 @param url Local file URL to the disk image in RAW format.
 @param readOnly If YES, the device attachment is read-only, otherwise the device can write data to the disk image.
 @param error If not nil, assigned with the error if the initialization failed.
 @return A VZDiskImageStorageDeviceAttachment on success. Nil otherwise and the error parameter is populated if set.
 */
- (nullable instancetype)initWithURL:(NSURL *)url readOnly:(BOOL)readOnly error:(NSError * _Nullable *)error NS_DESIGNATED_INITIALIZER;

/*!
 @abstract URL of the underlying disk image.
*/
@property (readonly, copy) NSURL *URL;

/*!
 @abstract Whether the underlying disk image is read-only.
*/
@property (readonly, getter=isReadOnly) BOOL readOnly;

@end

NS_ASSUME_NONNULL_END
