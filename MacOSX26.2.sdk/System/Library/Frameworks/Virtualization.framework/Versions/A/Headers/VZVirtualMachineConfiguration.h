//
//  VZVirtualMachineConfiguration.h
//  Virtualization
//
//  Copyright © 2019-2025 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class VZAudioDeviceConfiguration;
@class VZBootLoader;
@class VZConsoleDeviceConfiguration;
@class VZDirectorySharingDeviceConfiguration;
@class VZEntropyDeviceConfiguration;
@class VZGraphicsDeviceConfiguration;
@class VZKeyboardConfiguration;
@class VZMemoryBalloonDeviceConfiguration;
@class VZNetworkDeviceConfiguration;
@class VZPlatformConfiguration;
@class VZPointingDeviceConfiguration;
@class VZSerialPortConfiguration;
@class VZSocketDeviceConfiguration;
@class VZStorageDeviceConfiguration;
@class VZUSBControllerConfiguration;

/*!
 @abstract Virtual machine configuration.
 @discussion
    VZVirtualMachineConfiguration defines the configuration of a VZVirtualMachine.

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

    ## Configuring a virtual machine to run macOS

    To configure a virtual machine running macOS:
    - Set up a platform configuration of type VZMacPlatformConfiguration and set it on the `platform` property.
    - Set up a VZMacOSBootLoader on the `bootLoader` property.
    - Set the CPUCount and memorySize based on the guest's VZMacOSConfigurationRequirements.
    - Set up the main storage device as first device on `storageDevices`. Additional storage devices can be set up after the main storage.
    - Set up the `keyboards`, `pointingDevices` and `graphicsDevices` devices.
    - Set up any additional device as needed.

    ## Configuring a virtual machine to run Linux

    To configure a virtual machine running Linux:
    - Set up a VZLinuxBootLoader on the `bootLoader` property.
    - Set the CPUCount and memorySize.
    - Set up any additional device as needed.

 @see VZVirtualMachine
 */
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZVirtualMachineConfiguration : NSObject <NSCopying>

/*!
 @abstract Boot loader used when the virtual machine starts.
 @see VZLinuxBootLoader
 @see VZMacOSBootLoader
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
@property (readwrite) uint64_t memorySize;

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
 @abstract The hardware platform to use.
 @discussion
    Can be an instance of a VZGenericPlatformConfiguration or VZMacPlatformConfiguration. Defaults to VZGenericPlatformConfiguration.
    When restoring from saved state you must ensure your configuration matches that of the saved virtual machine.

 @see VZGenericPlatformConfiguration
 @see VZMacPlatformConfiguration
 */
@property (strong) VZPlatformConfiguration *platform API_AVAILABLE(macos(12.0));

/*!
 @abstract List of audio devices. Empty by default.
 @see VZVirtioSoundDeviceConfiguration
 */
@property (readwrite, copy) NSArray<VZAudioDeviceConfiguration *> *audioDevices API_AVAILABLE(macos(12.0));

/*!
 @abstract List of console devices. Empty by default.
 @see VZVirtioConsoleDeviceConfiguration
 */
@property (readwrite, copy) NSArray<VZConsoleDeviceConfiguration *> *consoleDevices API_AVAILABLE(macos(13.0));

/*!
 @abstract List of directory sharing devices. Empty by default.
 @see VZVirtioFileSystemDeviceConfiguration
 */
@property (readwrite, copy) NSArray<VZDirectorySharingDeviceConfiguration *> *directorySharingDevices API_AVAILABLE(macos(12.0));

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
 @see VZNVMExpressControllerDeviceConfiguration
 @see VZUSBMassStorageDeviceConfiguration
 @see VZVirtioBlockDeviceConfiguration
 */
@property (readwrite, copy) NSArray<VZStorageDeviceConfiguration *> *storageDevices;

/*!
 @abstract List of keyboards. Empty by default.
 @see VZUSBKeyboardConfiguration
 @see VZMacKeyboardConfiguration
 */
@property (copy) NSArray<VZKeyboardConfiguration *> *keyboards API_AVAILABLE(macos(12.0));

/*!
 @abstract List of pointing devices. Empty by default.
 @see VZUSBScreenCoordinatePointingDeviceConfiguration
 @see VZMacTrackpadConfiguration
 */
@property (copy) NSArray<VZPointingDeviceConfiguration *> *pointingDevices API_AVAILABLE(macos(12.0));

/*!
 @abstract List of graphics devices. Empty by default.
 @see VZMacGraphicsDeviceConfiguration
 */
@property (copy) NSArray<VZGraphicsDeviceConfiguration *> *graphicsDevices API_AVAILABLE(macos(12.0));

/*!
 @abstract List of USB Controllers. Empty by default.
 @discussion
    This list represents a set of USB controllers that the virtual machine will start with.
    For each entry in this list, there will be a corresponding runtime object created in VZVirtualMachine.usbControllers property.
 @see VZUSBControllerConfiguration
 */
@property (readwrite, copy) NSArray<VZUSBControllerConfiguration *> *usbControllers API_AVAILABLE(macos(15.0));

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
- (BOOL)validateWithError:(NSError **)error;

#if defined(__arm64__)
/*!
 @abstract Validate the configuration is savable.
 @discussion
    Verify that a virtual machine with this configuration is savable.
    Not all configuration options can be safely saved and restored from file.
    If this evaluates to NO, the caller should expect future calls to saveMachineStateToURL:completionHandler: to fail.
 @param error If not nil, assigned with an error describing the unsupported configuration option.
 @return YES if the configuration is savable.
 */
- (BOOL)validateSaveRestoreSupportWithError:(NSError **)error API_AVAILABLE(macos(14.0));
#endif

/*!
 @abstract Minimum amount of memory required by virtual machines.
 @see VZVirtualMachineConfiguration.memorySize
 */
@property (class, readonly) uint64_t minimumAllowedMemorySize;

/*!
 @abstract Maximum amount of memory allowed for a virtual machine.
 @see VZVirtualMachineConfiguration.memorySize
 */
@property (class, readonly) uint64_t maximumAllowedMemorySize;

/*!
 @abstract Minimum number of CPUs for a virtual machine.
 @see VZVirtualMachineConfiguration.CPUCount
 */
@property (class, readonly) NSUInteger minimumAllowedCPUCount;

/*!
 @abstract Maximum number of CPUs for a virtual machine.
 @see VZVirtualMachineConfiguration.CPUCount
 */
@property (class, readonly) NSUInteger maximumAllowedCPUCount;

@end

NS_ASSUME_NONNULL_END
