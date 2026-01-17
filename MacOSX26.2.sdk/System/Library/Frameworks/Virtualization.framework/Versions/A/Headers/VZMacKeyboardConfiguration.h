//
//  VZMacKeyboardConfiguration.h
//  Virtualization
//
//  Copyright © 2021-2023 Apple Inc. All rights reserved.
//

#ifdef __arm64__

#import <Virtualization/VZKeyboardConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Configuration for a Mac keyboard.
 @discussion
    This device can be used by VZVirtualMachineView to send keyboard events to the virtual machine.
    This keyboard supports Apple-specific features such as the globe key.
    Note: this device is only recognized by virtual machines running macOS 13.0 and later. In order to support both macOS 13.0 and earlier
    guests, VZVirtualMachineConfiguration.keyboards can be set to an array containing both a VZMacKeyboardConfiguration and
    a VZUSBKeyboardConfiguration object. macOS 13.0 and later guests will use the Mac keyboard device,
    while earlier versions of macOS will use the USB keyboard device.
 */
VZ_EXPORT API_AVAILABLE(macos(14.0))
@interface VZMacKeyboardConfiguration : VZKeyboardConfiguration

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END

#endif
