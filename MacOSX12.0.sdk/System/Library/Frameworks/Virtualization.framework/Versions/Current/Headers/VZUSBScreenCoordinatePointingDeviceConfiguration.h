//
//  VZUSBScreenCoordinatePointingDeviceConfiguration.h
//  Virtualization
//
//  Copyright © 2019-2021 Apple Inc. All rights reserved.
//

#import <Virtualization/VZPointingDeviceConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Configuration for a USB pointing device that reports absolute coordinates.
 @discussion This device can be used by VZVirtualMachineView to send pointer events to the virtual machine.
 */
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZUSBScreenCoordinatePointingDeviceConfiguration : VZPointingDeviceConfiguration

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
