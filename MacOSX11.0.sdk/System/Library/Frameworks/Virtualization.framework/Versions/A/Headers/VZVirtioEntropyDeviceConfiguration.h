//
//  VZVirtioEntropyDeviceConfiguration.h
//  Virtualization
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZEntropyDeviceConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Virtio Entropy Device
 @discussion The device exposes a source of entropy for the guest's random number generator.
 */
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZVirtioEntropyDeviceConfiguration : VZEntropyDeviceConfiguration

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
