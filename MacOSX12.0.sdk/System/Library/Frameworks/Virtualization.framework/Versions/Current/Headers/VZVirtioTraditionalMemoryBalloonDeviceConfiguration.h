//
//  VZVirtioTraditionalMemoryBalloonDeviceConfiguration.h
//  Virtualization
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZMemoryBalloonDeviceConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Configuration of the Virtio traditional memory balloon device.
 @discussion
    This configuration creates a Virtio traditional memory balloon device which allows for managing guest memory.
    Only one Virtio traditional memory balloon device can be used per virtual machine.
 @see VZVirtioTraditionalMemoryBalloonDevice
 */
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZVirtioTraditionalMemoryBalloonDeviceConfiguration : VZMemoryBalloonDeviceConfiguration

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
