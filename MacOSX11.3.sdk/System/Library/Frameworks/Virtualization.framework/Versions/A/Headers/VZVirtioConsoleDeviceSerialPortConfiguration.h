//
//  VZVirtioConsoleDeviceSerialPortConfiguration.h
//  Virtualization
//
//  Copyright © 2019-2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZSerialPortConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Virtio Console Serial Port Device
 @discussion
    The device creates a console which enables communication between the host and the guest through the Virtio interface.

    The device sets up a single port on the Virtio console device.
 */
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZVirtioConsoleDeviceSerialPortConfiguration : VZSerialPortConfiguration

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
