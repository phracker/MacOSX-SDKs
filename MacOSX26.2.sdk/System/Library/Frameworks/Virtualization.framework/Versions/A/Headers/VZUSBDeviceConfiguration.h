//
//  VZUSBDeviceConfiguration.h
//  Virtualization
//
//  Copyright © 2023-2024 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Protocol for USB Device configuration.
 @discussion
    Classes that conform to this protocol represent hot-pluggable USB device configurations.
    VZUSBDeviceConfiguration protocol should not be used with objects outside of Virtualization framework.
    This protocol only describes capabilities of Virtualization framework objects.
 @see VZUSBMassStorageDeviceConfiguration
 */
VZ_EXPORT API_AVAILABLE(macos(15.0))
@protocol VZUSBDeviceConfiguration <NSObject>

/*!
 @abstract Device UUID.
 @discussion
    Device UUID is auto-generated.
    Before restoring the virtual machine, it should be replaced with the uuid of a previously attached device when the virtual machine was saved.
 */
@property (readwrite, copy) NSUUID *uuid;

@end

NS_ASSUME_NONNULL_END
