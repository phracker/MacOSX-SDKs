//
//  VZMacTrackpadConfiguration.h
//  Virtualization
//
//  Copyright © 2021-2023 Apple Inc. All rights reserved.
//

#ifdef __arm64__

#import <Virtualization/VZPointingDeviceConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Configuration for a Mac trackpad.
 @discussion
    This device can be used by VZVirtualMachineView to send pointer events and multi-touch trackpad gestures to the virtual machine.
    Note: this device is only recognized by virtual machines running macOS 13.0 and later. In order to support both macOS 13.0 and earlier
    guests, VZVirtualMachineConfiguration.pointingDevices can be set to an array containing both a VZMacTrackpadConfiguration and
    a VZUSBScreenCoordinatePointingDeviceConfiguration object. macOS 13.0 and later guests will use the multi-touch trackpad device,
    while earlier versions of macOS will use the USB pointing device.
 */
VZ_EXPORT API_AVAILABLE(macos(13.0))
@interface VZMacTrackpadConfiguration : VZPointingDeviceConfiguration

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END

#endif
