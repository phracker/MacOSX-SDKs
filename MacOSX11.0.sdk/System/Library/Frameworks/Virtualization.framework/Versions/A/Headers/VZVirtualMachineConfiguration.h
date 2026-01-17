//
//  VZVirtualMachineConfiguration.h
//  Virtualization
//
//  Copyright © 2019-2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class VZBootLoader;
@class VZEntropyDeviceConfiguration;
@class VZMemoryBalloonDeviceConfiguration;
@class VZNetworkDeviceConfiguration;
@class VZSerialPortConfiguration;
@class VZSocketDeviceConfiguration;
@class VZStorageDeviceConfiguration;

/*!
 @abstract Virtual machine configuration.
 @discussion
    VZVirtualMachineConfiguration defines the configuration of a VZVirtualMachine.

    The following properties must be configured before creating a virtual machine:
    - bootLoader

    The configuration of devices is often done in two parts:
    - Device configuration
    - Device attachment

    The device configuration defines the characteristics of the emulated hardware device.
    For example, for a network device, the device configuration defines the type of network adapter present
    in the virtual machine and its MAC address.

    The device attachment defines the host machine's resources that are exposed by the virtual device.
    For example, for a network device, the device attachment can be virtual network interface with a NAT
    to the real network.

    Creating a virtual machine using the Virtualization framework requires the app to have the "com.apple.security.virtualization" entitlement.
    A VZVirtualMachineConfiguration is considered invalid if the application does not have the entitlement.

 @see VZVirtualMachine
 */
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZVirtualMachineConfiguration : NSObject <NSCopying>

/*!
 @abstract Boot loader used when the virtual machine starts.
 @see VZLinuxBootLoader
 */
@property (nullable, strong) VZBootLoader *bootLoader;

/*!
 @abstract Virtual machine memory size in bytes.
 @discussion
    The memory size must be a multiple of a 1 megabyte (1024 * 1024 bytes) between VZVirtualMachineConfiguration.minimumAllowedMemorySize
    and VZVirtualMachineConfiguration.maximumAllowedMemorySize.

    The memorySize represents the total physical memory seen by a guest OS running in the virtual machine.
    Not all memory is allocated on start, the virtual machine allocates memory on demand.
 @see VZVirtualMachineConfiguration.minimumAllowedMemorySize
 @see VZVirtualMachineConfiguration.maximumAllowedMemorySize
 */
@property (readwrite) unsigned long long memorySize;

/*!
 @abstract Number of CPUs.
 @discussion
    The number of CPUs must be a value between VZVirtualMachineConfiguration.minimumAllowedCPUCount
    and VZVirtualMachineConfiguration.maximumAllowedCPUCount.

 @see VZVirtualMachineConfiguration.minimumAllowedCPUCount
 @see VZVirtualMachineConfiguration.maximumAllowedCPUCount
 */
@property (readwrite) NSUInteger CPUCount;

/*!
 @abstract List of entropy devices. Empty by default.
 @see VZVirtioEntropyDeviceConfiguration
*/
@property (readwrite, copy) NSArray<VZEntropyDeviceConfiguration *> *entropyDevices;

/*!
 @abstract List of memory balloon devices. Empty by default.
 @see VZVirtioTraditionalMemoryBalloonDeviceConfiguration
*/
@property (readwrite, copy) NSArray<VZMemoryBalloonDeviceConfiguration *> *memoryBalloonDevices;

/*!
 @abstract List of network adapters. Empty by default.
 @see VZVirtioNetworkDeviceConfiguration
 */
@property (readwrite, copy) NSArray<VZNetworkDeviceConfiguration *> *networkDevices;

/*!
 @abstract List of serial ports. Empty by default.
 @see VZVirtioConsoleDeviceSerialPortConfiguration
 */
@property (readwrite, copy) NSArray<VZSerialPortConfiguration *> *serialPorts;

/*!
 @abstract List of socket devices. Empty by default.
 @see VZVirtioSocketDeviceConfiguration
 */
@property (readwrite, copy) NSArray<VZSocketDeviceConfiguration *> *socketDevices;

/*!
 @abstract List of disk devices. Empty by default.
 @see VZVirtioBlockDeviceConfiguration
 */
@property (readwrite, copy) NSArray<VZStorageDeviceConfiguration *> *storageDevices;

@end

/*!
 @abstract Virtual machine configuration runtime validation.
 */
@interface VZVirtualMachineConfiguration (VZVirtualMachineConfigurationValidation)

/*!
 @abstract Validate the configuration.
 @param error If not nil, assigned with the validation error if the validation failed.
 @return YES if the configuration is valid.
 */
- (BOOL)validateWithError:(NSError * _Nullable *)error;

/*!
 @abstract: Minimum amount of memory required by virtual machines.
 @see VZVirtualMachineConfiguration.memorySize
 */
@property (class, readonly) unsigned long long minimumAllowedMemorySize;

/*!
 @abstract: Maximum amount of memory allowed for a virtual machine.
 @see VZVirtualMachineConfiguration.memorySize
 */
@property (class, readonly) unsigned long long maximumAllowedMemorySize;

/*!
 @abstract: Minimum number of CPUs for a virtual machine.
 @see VZVirtualMachineConfiguration.CPUCount
 */
@property (class, readonly) NSUInteger minimumAllowedCPUCount;

/*!
 @abstract: Maximum number of CPUs for a virtual machine.
 @see VZVirtualMachineConfiguration.CPUCount
 */
@property (class, readonly) NSUInteger maximumAllowedCPUCount;

@end

NS_ASSUME_NONNULL_END
