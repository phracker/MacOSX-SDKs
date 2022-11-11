//
//  VZVirtioFileSystemDeviceConfiguration.h
//  Virtualization
//
//  Copyright © 2020-2021 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDirectorySharingDeviceConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

@class VZDirectoryShare;

/*!
 @abstract Configuration of a Virtio file system device.
 @discussion
    This configuration creates a Virtio file system device which allows for exposing
    directories on the host to a guest via a tag label.
 */
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZVirtioFileSystemDeviceConfiguration : VZDirectorySharingDeviceConfiguration

/*!
 @abstract Configuration of the Virtio file system device.
 @param tag The label identifying this device in the guest.
 @discussion The tag is presented as a label in the guest identifying this device for mounting. The tag must be valid, which can be checked with +[VZVirtioFileSystemDeviceConfiguration validateTag:error:].
 @see +[VZVirtioFileSystemDeviceConfiguration validateTag:error:]
 */
- (instancetype)initWithTag:(NSString *)tag NS_DESIGNATED_INITIALIZER;

/*!
 @abstract Check if tag is a valid Virtio file system tag.
 @param tag The tag to validate.
 @param error If not nil, assigned with an error describing why the tag is not valid.
 @discussion The tag must be non-empty and less than 36 bytes when encoded in UTF-8.
*/
+ (BOOL)validateTag:(NSString *)tag error:(NSError **)error;

/*!
 @abstract The tag is a string identifying the device.
 @discussion The tag is presented as a label in the guest identifying this device for mounting. The tag must be valid, which can be checked with +[VZVirtioFileSystemDeviceConfiguration validateTag:error:].
 @see +[VZVirtioFileSystemDeviceConfiguration validateTag:error:]
 */
@property (copy) NSString *tag;

/*!
 @abstract Directory share. Defines how host resources are exposed to the guest virtual machine.
 @see VZSingleDirectoryShare
 @see VZMultipleDirectoryShare
 */
@property (nullable, strong) VZDirectoryShare *share;

@end

NS_ASSUME_NONNULL_END
