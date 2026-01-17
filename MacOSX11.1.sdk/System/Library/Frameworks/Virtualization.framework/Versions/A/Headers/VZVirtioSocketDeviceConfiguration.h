//
//  VZVirtioSocketDeviceConfiguration.h
//  Virtualization
//
//  Copyright © 2019-2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZSocketDeviceConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Configuration of the Virtio socket device.
 @discussion
    This configuration creates a Virtio socket device for the guest which communicates with the host through the Virtio interface.

    Only one Virtio socket device can be used per virtual machine.
 @see VZVirtioSocketDevice
 */
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZVirtioSocketDeviceConfiguration : VZSocketDeviceConfiguration

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
