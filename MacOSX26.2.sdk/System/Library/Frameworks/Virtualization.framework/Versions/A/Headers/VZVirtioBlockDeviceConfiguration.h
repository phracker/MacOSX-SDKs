//
//  VZVirtioBlockDeviceConfiguration.h
//  Virtualization
//
//  Copyright © 2019-2023 Apple Inc. All rights reserved.
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

/*!
 @abstract Initialize a VZVirtioBlockDeviceConfiguration with a device attachment.
 @param attachment The storage device attachment. This defines how the virtualized device operates on the host side.
 @see VZDiskImageStorageDeviceAttachment
 */
- (instancetype)initWithAttachment:(VZStorageDeviceAttachment *)attachment NS_DESIGNATED_INITIALIZER;

/*!
 @abstract Check if blockDeviceIdentifier is a valid Virtio block device identifier.
 @param blockDeviceIdentifier The device identifier to validate.
 @param error If not nil, assigned with an error describing why the device identifier is not valid.
 @discussion The device identifier must be at most 20 bytes in length and ASCII-encodable.
*/
+ (BOOL)validateBlockDeviceIdentifier:(NSString *)blockDeviceIdentifier error:(NSError **)error API_AVAILABLE(macos(12.3));

/*!
 @abstract The device identifier is a string identifying the Virtio block device. Empty string by default.
 @discussion
    The identifier can be retrieved in the guest via a VIRTIO_BLK_T_GET_ID request.

    The identifier must be encodable as an ASCII string of length at most 20 bytes.
    This property can be checked with +[VZVirtioBlockDeviceConfiguration validateBlockDeviceIdentifier:error:].
 @see +[VZVirtioBlockDeviceConfiguration validateBlockDeviceIdentifier:error:]
 */
@property (copy) NSString *blockDeviceIdentifier API_AVAILABLE(macos(12.3));

@end

NS_ASSUME_NONNULL_END
