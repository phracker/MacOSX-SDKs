//
//  VZVmnetNetworkDeviceAttachment.h
//  Virtualization
//
//  Copyright © 2024-2025 Apple Inc. All rights reserved.
//

#import <Virtualization/VZNetworkDeviceAttachment.h>
#import <vmnet/vmnet.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Network device attachment that allows custom network topology.
 @discussion
    This attachment is backed by a logical network which is created and customized through
    the vmnet framework APIs to allow custom network topology, which allows multiple virtual
    machines to appear on the same network and connect with each other.

 @see VZNetworkDeviceConfiguration
 @see VZVirtioNetworkDeviceConfiguration
 */
VZ_EXPORT API_AVAILABLE(macos(26.0))
@interface VZVmnetNetworkDeviceAttachment : VZNetworkDeviceAttachment

/*!
 @abstract Initialize a `VZVmnetNetworkDeviceAttachment` with a logical network.
 @param network The logical network object.
 @return An initialized `VZVmnetNetworkDeviceAttachment`.
 @discussion
    To ensure proper isolation between application processes, a VM can only use the `network` that is created by the
    same application process. If a VM created by one application tries to use a `network` created by another application,
    starting the interface with this attachment will fail.

    The vmnet framework requires an entitlement to create or configure a network. For more information, please
    refer to the vmnet framework API documentation.

    An example use of this API is:
    ```
    vmnet_return_t status;
    auto network_configuration = vmnet_network_configuration_create(VMNET_SHARED_MODE, &status);
    if (!network_configuration) {
        // Handle error return `status`.
    }

    auto network = vmnet_network_create(network_configuration, &status);
    if (!network) {
        // Handle error return `status`.
    }

    VZVmnetNetworkDeviceAttachment *attachment = [[VZVmnetNetworkDeviceAttachment alloc] initWithNetwork:network];

    VZVirtioNetworkDeviceConfiguration virtioNetworkDevice = [[VZVirtioNetworkDeviceConfiguration alloc] init];
    virtioNetworkDevice.attachment = attachment;
    ```
 */
- (instancetype)initWithNetwork:(vmnet_network_ref)network NS_DESIGNATED_INITIALIZER;

/*!
 @abstract The network object that the attachment will be initialized with.
 */
@property (readonly) vmnet_network_ref network;

@end

NS_ASSUME_NONNULL_END
