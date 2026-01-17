//
//  VZNVMExpressControllerDeviceConfiguration.h
//  Virtualization
//
//  Copyright © 2019-2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZStorageDeviceConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Configuration of an NVM Express Controller storage device.
 @discussion
    This device configuration creates a storage device that conforms to the NVM Express specification revision 1.1b.

    The device configuration is valid only if used with VZGenericPlatformConfiguration.
 @see VZGenericPlatformConfiguration
 */
VZ_EXPORT API_AVAILABLE(macos(14.0))
@interface VZNVMExpressControllerDeviceConfiguration : VZStorageDeviceConfiguration

/*!
 @abstract Initialize a VZNVMExpressControllerDeviceConfiguration with a device attachment.
 @param attachment The storage device attachment. This defines how the virtualized device operates on the host side.
 @see VZDiskImageStorageDeviceAttachment
 */
- (instancetype)initWithAttachment:(VZStorageDeviceAttachment *)attachment NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
