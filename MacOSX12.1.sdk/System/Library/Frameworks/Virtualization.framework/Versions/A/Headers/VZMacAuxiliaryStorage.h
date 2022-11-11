//
//  VZMacAuxiliaryStorage.h
//  Virtualization
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#ifdef __arm64__

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class VZMacHardwareModel;

/*!
 @abstract Options when creating a new auxiliary storage.
*/
typedef NS_OPTIONS(NSUInteger, VZMacAuxiliaryStorageInitializationOptions) {
    /*! Overwrite an existing auxiliary storage. */
    VZMacAuxiliaryStorageInitializationOptionAllowOverwrite = 1ULL << 0,
} NS_SWIFT_NAME(VZMacAuxiliaryStorage.InitializationOptions) API_AVAILABLE(macos(12.0));

/*!
 @abstract Mac auxiliary storage.
 @discussion
    The Mac auxiliary storage contains data used by the boot loader and the guest operating system. It is necessary to boot a macOS guest OS.

    When creating a new virtual machine from scratch, VZMacOSInstaller can use a default initialized auxiliary storage.
    Use -[VZMacAuxiliaryStorage initCreatingStorageAtURL:hardwareModel:options:error:] to create an empty auxiliary storage.

    The hardware model used when creating the new auxiliary storage depends on the restore image that will be used for installation.
    From the restore image, use VZMacOSRestoreImage.mostFeaturefulSupportedConfiguration to get a supported configuration.
    A configuration has a VZMacHardwareModel associated with it.

    After initializing the new auxiliary storage, set it on VZMacPlatformConfiguration.auxiliaryStorage to use it.
    The hardware model in VZMacPlatformConfiguration.hardwareModel must be identical to the one used to create the empty
    auxiliary storage. The behavior is undefined otherwise.

    When installing macOS, the VZMacOSInstaller lays out data on the auxiliary storage.
    After installation, the macOS guest uses the auxiliary storage for every subsequent boot.

    When moving or doing a backup of a virtual machine, the file containing the auxiliary storage must also be moved
    or copied along with the main disk image.

    To boot a virtual machine that has already been installed with VZMacOSInstaller, use -[VZMacAuxiliaryStorage initWithContentsOfURL:]
    to set up the auxiliary storage from the existing file used at installation.
    When using an existing file, the hardware model of the VZMacPlatformConfiguration must match the hardware model used when
    the file was created.
 @seealso VZMacPlatformConfiguration
 @seealso VZMacOSRestoreImage
 @seealso VZMacOSConfigurationRequirements
 @seealso VZMacOSInstaller
 */
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZMacAuxiliaryStorage : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Initialize the auxiliary storage from the URL of an existing file.
 @param URL The URL of the auxiliary storage on the local file system.
 @discussion To create a new auxiliary storage, use -[VZMacAuxiliaryStorage initCreatingStorageAtURL:hardwareModel:options:error].
 */
- (instancetype)initWithContentsOfURL:(NSURL *)URL;

/*!
 @abstract Write an initialized VZMacAuxiliaryStorage to a URL on a file system.
 @param URL The URL to write the auxiliary storage to on the local file system.
 @param hardwareModel The hardware model to use. The auxiliary storage can be laid out differently for different hardware models.
 @param options Initialization options.
 @param error If not nil, used to report errors if creation fails.
 @return A newly initialized VZMacAuxiliaryStorage on success. If an error was encountered returns @c nil, and @c error contains the error.
 */
- (nullable instancetype)initCreatingStorageAtURL:(NSURL *)URL hardwareModel:(VZMacHardwareModel *)hardwareModel options:(VZMacAuxiliaryStorageInitializationOptions)options error:(NSError **)error;

/*!
 @abstract The URL of the auxiliary storage on the local file system.
 */
@property (readonly, copy) NSURL *URL;

@end

NS_ASSUME_NONNULL_END

#endif
