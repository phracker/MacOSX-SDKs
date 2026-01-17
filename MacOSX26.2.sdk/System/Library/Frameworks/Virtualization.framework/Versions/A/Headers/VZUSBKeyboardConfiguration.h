//
//  VZUSBKeyboardConfiguration.h
//  Virtualization
//
//  Copyright © 2019-2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZKeyboardConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Configuration for a USB keyboard.
 @discussion This device can be used by VZVirtualMachineView to send key events to the virtual machine.
 */
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZUSBKeyboardConfiguration : VZKeyboardConfiguration

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
