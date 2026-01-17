//
//  VZBridgedNetworkDeviceAttachment.h
//  Virtualization
//
//  Copyright © 2019-2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZNetworkDeviceAttachment.h>

NS_ASSUME_NONNULL_BEGIN

@class VZBridgedNetworkInterface;

/*!
 @abstract Network device attachment bridging a host physical interface with a virtual network device.
 @discussion
    A bridged network allows the virtual machine to use the same physical interface as the host. Both host and virtual machine
    send and receive packets on the same physical interface but have distinct network layers.

    The bridge network device attachment is used with a VZNetworkDeviceConfiguration to define a virtual network device.

    Using a VZBridgedNetworkDeviceAttachment requires the app to have the "com.apple.vm.networking" entitlement.

 @see VZBridgedNetworkInterface
 @see VZNetworkDeviceConfiguration
 @see VZVirtioNetworkDeviceConfiguration
 */
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZBridgedNetworkDeviceAttachment : VZNetworkDeviceAttachment

/*!
 @abstract Initialize a VZBridgedNetworkDeviceAttachment with a host network interface.
 @param interface Host network interface controller.
 */
- (instancetype)initWithInterface:(VZBridgedNetworkInterface *)interface NS_DESIGNATED_INITIALIZER;

/*!
 @abstract Network interface of this device attachment.
 */
@property (readonly, strong) VZBridgedNetworkInterface *interface;

@end

NS_ASSUME_NONNULL_END
