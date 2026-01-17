//
//  VZUSBDevice.h
//  Virtualization
//
//  Copyright © 2021-2024 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

@class VZUSBController;

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Protocol representing a USB Device in a virtual machine.
 @discussion
    Classes that conform to this protocol represent hot-pluggable USB devices.
    VZUSBDevice protocol should not be used with objects outside of Virtualization framework.
    This protocol only describes capabilities of Virtualization framework objects.
 @see VZUSBMassStorageDevice
 */
VZ_EXPORT API_AVAILABLE(macos(15.0))
@protocol VZUSBDevice <NSObject>

/*!
 @abstract USB controller that the device is attached to.
 @discussion
    If a USB device object that conforms to this protocol is currently attached to a USB controller, this
    property includes a pointer to the USB controller object that the device is attached to.
    Otherwise, it contains nil.
 */
@property (readonly, nullable, weak) VZUSBController *usbController;

/*!
 @abstract Device UUID.
 @discussion
    Device UUID from device configuration objects that conform to `VZUSBDeviceConfiguration`.
 @see VZUSBDeviceConfiguration
 */
@property (readonly, copy) NSUUID *uuid;

@end

NS_ASSUME_NONNULL_END
