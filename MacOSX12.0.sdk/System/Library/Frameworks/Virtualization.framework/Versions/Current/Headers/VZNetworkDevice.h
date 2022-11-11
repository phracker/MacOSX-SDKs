//
//  VZNetworkDevice.h
//  Virtualization
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Virtualization/VZNetworkDeviceAttachment.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Class representing a network device in a virtual machine.
 @discussion
    VZNetworkDevice should not be instantiated directly.

    Network devices are first configured on the VZVirtualMachineConfiguration through a subclass of VZNetworkDeviceConfiguration.
    When a VZVirtualMachine is created from the configuration, the network devices are available through the VZVirtualMachine.networkDevices property.

 @see VZNetworkDeviceConfiguration
 */

VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZNetworkDevice : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract The network attachment that's currently connected to this network device.
 @discussion
    Setting this property will result in an attempt to change the network device attachment which may fail, in which case
    the -[VZVirtualMachineDelegate virtualMachine:networkDevice:attachmentWasDisconnectedWithError:] will be invoked and this property
    will be set to nil.

    This property may change at any time while the VM is running based on the state of the host network.
 */
@property (nullable, strong) VZNetworkDeviceAttachment *attachment;

@end

NS_ASSUME_NONNULL_END
