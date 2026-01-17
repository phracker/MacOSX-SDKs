//
//  VZUSBMassStorageDevice.h
//  Virtualization
//
//  Copyright © 2023-2024 Apple Inc. All rights reserved.
//

#import <Virtualization/VZStorageDevice.h>
#import <Virtualization/VZUSBDevice.h>

NS_ASSUME_NONNULL_BEGIN

@class VZUSBMassStorageDeviceConfiguration;

/*!
 @abstract Class representing a hot-pluggable USB Mass Storage device.
 @discussion
    This device is created through either instantiating it directly and passing VZUSBMassStorageDeviceConfiguration to its initializer
    or instantiating a VZUSBMassStorageDeviceConfiguration in a VZVirtualMachineConfiguration. Direct instantiation will create
    an object that can be passed to -[VZUSBController attachDevice:completionHandler:] method. Instantiation via VZUSBMassStorageDeviceConfiguration
    will make the device available in VZUSBController.usbDevices property.
 @see VZUSBController
 */
VZ_EXPORT API_AVAILABLE(macos(15.0))
@interface VZUSBMassStorageDevice : VZStorageDevice <VZUSBDevice>

/*!
 @abstract Initialize the runtime USB Mass Storage device object.
 @param configuration The configuration of the USB Mass Storage device.
 @see VZUSBMassStorageDeviceConfiguration
 */
- (instancetype)initWithConfiguration:(VZUSBMassStorageDeviceConfiguration *)configuration NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
