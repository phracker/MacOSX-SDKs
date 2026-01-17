//
//  VZVirtioNetworkDeviceConfiguration.h
//  Virtualization
//
//  Copyright © 2019-2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZNetworkDeviceConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Configuration of a paravirtualized network device of type Virtio Network Device.
 @discussion
    The communication channel used on the host is defined through the attachment. It is set with the VZNetworkDeviceConfiguration.attachment property.

    The configuration is only valid with valid MACAddress and attachment.

 @see VZVirtualMachineConfiguration.networkDevices
 */
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZVirtioNetworkDeviceConfiguration : VZNetworkDeviceConfiguration

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
