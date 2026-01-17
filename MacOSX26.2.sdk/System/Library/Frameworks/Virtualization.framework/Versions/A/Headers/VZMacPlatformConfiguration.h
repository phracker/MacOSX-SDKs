//
//  VZMacPlatformConfiguration.h
//  Virtualization
//
//  Copyright © 2021-2024 Apple Inc. All rights reserved.
//

#ifdef __arm64__

#import <Virtualization/VZPlatformConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

@class VZMacAuxiliaryStorage;
@class VZMacHardwareModel;
@class VZMacMachineIdentifier;

/*!
 @abstract The platform configuration for booting macOS on Apple Silicon.
 @discussion
    When creating a virtual machine from scratch, the `hardwareModel` and `auxiliaryStorage` depend on the restore image
    that will be used to install macOS.

    To choose the hardware model, start from VZMacOSRestoreImage.mostFeaturefulSupportedConfiguration to get a supported configuration, then
    use its VZMacOSConfigurationRequirements.hardwareModel property to get the hardware model.
    Use the hardware model to set up VZMacPlatformConfiguration and to initialize a new auxiliary storage with
    -[VZMacAuxiliaryStorage initCreatingStorageAtURL:hardwareModel:options:error:].

    When a virtual machine is saved to disk then loaded again, the `hardwareModel`, `machineIdentifier` and `auxiliaryStorage`
    must be restored to their original values.

    If multiple virtual machines are created from the same configuration, each should have a unique  `auxiliaryStorage` and `machineIdentifier`.
 @seealso VZMacOSRestoreImage
 @seealso VZMacOSConfigurationRequirements
*/
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZMacPlatformConfiguration : VZPlatformConfiguration

- (instancetype)init NS_DESIGNATED_INITIALIZER;

/*!
 @abstract The Mac hardware model.
 */
@property (copy) VZMacHardwareModel *hardwareModel;

/*!
 @abstract The unique Mac machine identifier.
 @discussion
    Running two virtual machines concurrently with the same identifier results in undefined behavior in the guest operating system.
 */
@property (copy) VZMacMachineIdentifier *machineIdentifier;

/*!
 @abstract The Mac auxiliary storage.
 @discussion
    When creating a virtual machine from scratch, the hardware model of the `auxiliaryStorage` must match the hardware model of
    the `hardwareModel` property.
 */
@property (nullable, strong) VZMacAuxiliaryStorage *auxiliaryStorage;

@end

NS_ASSUME_NONNULL_END

#endif
