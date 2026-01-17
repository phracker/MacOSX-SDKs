//
//  VZVirtioBlockDeviceConfiguration.h
//  Virtualization
//
//  Copyright © 2019-2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZStorageDeviceConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Configuration of a paravirtualized storage device of type Virtio Block Device.
 @discussion
    This device configuration creates a storage device using paravirtualization.
    The emulated device follows the Virtio Block Device specification.

    The host implementation of the device is done through an attachment subclassing VZStorageDeviceAttachment
    like VZDiskImageStorageDeviceAttachment.
 */
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZVirtioBlockDeviceConfiguration : VZStorageDeviceConfiguration

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Initialize a VZVirtioBlockDeviceConfiguration with a device attachment.
 @param attachment The storage device attachment. This defines how the virtualized device operates on the host side.
 @see VZDiskImageStorageDeviceAttachment
 */
- (instancetype)initWithAttachment:(VZStorageDeviceAttachment *)attachment NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
