//
//  VZMacHardwareModel.h
//  Virtualization
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#ifdef __arm64__

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Describes a specific virtual Mac hardware model.
 @discussion
    The Mac hardware model abstracts a set of virtualized hardware elements and configurations.
    A version of macOS may only run on certain hardware models. The host may also only provide certain hardware models
    based on the version of macOS and the underlying hardware.
    Use VZMacHardwareModel.supported to know if a hardware model is supported on the current host.

    Choosing the hardware model starts from a restore image with VZMacOSRestoreImage.
    A restore image describes its supported configuration requirements through VZMacOSRestoreImage.mostFeaturefulSupportedConfiguration.
    A configuration requirements object has a corresponding hardware model that can be used to configure a virtual machine
    that meets the requirements.

    Once the hardware model is obtained, use VZMacPlatformConfiguration.hardwareModel to configure the Mac platform,
    and -[VZMacAuxiliaryStorage initCreatingStorageAtURL:hardwareModel:options:error:] to create its auxiliary storage.
    Once the virtual machine is created, use VZMacOSInstaller to install macOS on it.

    If the virtual machine is preserved on disk, the hardware model used for installation should be preserved for subsequent boots.
    The VZMacHardwareModel.dataRepresentation property provides a unique binary representation that can be serialized.
    The hardware model then can be recreated from the binary representation with -[VZMacHardwareModel initWithDataRepresentation:].
 @seealso VZMacOSInstaller
 @seealso VZMacOSRestoreImage
*/
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZMacHardwareModel : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Get the hardware model described by the specified data representation.
 @param dataRepresentation The opaque data representation of the hardware model to be obtained.
 */
- (nullable instancetype)initWithDataRepresentation:(NSData *)dataRepresentation;

/*!
 @abstract Opaque data representation of the hardware model.
 @discussion This can be used to recreate the same hardware model with -[VZMacHardwareModel initWithDataRepresentation:].
 */
@property (readonly, copy) NSData *dataRepresentation;

/*!
 @abstract Indicate whether this hardware model is supported by the host.
 @discussion
    If this hardware model is not supported by the host, no VZVirtualMachineConfiguration using it will validate.
    The validation error of the VZVirtualMachineConfiguration provides more information about why the hardware model is unsupported.
 */
@property (readonly, getter=isSupported) BOOL supported;

@end

NS_ASSUME_NONNULL_END

#endif
