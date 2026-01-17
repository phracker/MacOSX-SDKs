//
//  VZVirtioGraphicsDeviceConfiguration.h
//  Virtualization
//
//  Copyright © 2019-2025 Apple Inc. All rights reserved.
//

#import <Virtualization/VZGraphicsDeviceConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

@class VZVirtioGraphicsScanoutConfiguration;

/*!
 @abstract Configuration for a Virtio graphics device.
 @discussion
    This device configuration creates a graphics device using paravirtualization.
    The emulated device follows the Virtio GPU Device specification.

    This device can be used to attach a display to be shown in a VZVirtualMachineView.
*/
VZ_EXPORT API_AVAILABLE(macos(13.0))
@interface VZVirtioGraphicsDeviceConfiguration : VZGraphicsDeviceConfiguration

- (instancetype)init;

/*!
 @abstract The scanouts to be attached to this graphics device.
 @discussion
    Maximum of one scanout is supported.
*/
@property (copy) NSArray<VZVirtioGraphicsScanoutConfiguration *> *scanouts;

@end

NS_ASSUME_NONNULL_END
