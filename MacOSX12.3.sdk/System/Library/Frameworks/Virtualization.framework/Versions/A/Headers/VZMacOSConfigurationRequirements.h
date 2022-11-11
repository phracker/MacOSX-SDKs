//
//  VZMacOSConfigurationRequirements.h
//  Virtualization
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#ifdef __arm64__

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class VZMacHardwareModel;

/*!
 @abstract VZMacOSConfigurationRequirements describes the parameter constraints required by a specific configuration of macOS.
 @discussion
    When a VZMacOSRestoreImage is loaded, it can be inspected to determine the configurations supported by that restore image.
 @seealso VZMacHardwareModel
 @seealso VZMacOSRestoreImage
*/
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZMacOSConfigurationRequirements : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract The hardware model for this configuration.
 @discussion
    The hardware model can be used to configure a new virtual machine that meets the requirements.
    Use VZMacPlatformConfiguration.hardwareModel to configure the Mac platform, and -[VZMacAuxiliaryStorage initCreatingStorageAtURL:hardwareModel:options:error:] to create its auxiliary storage.
 @seealso VZMacPlatformConfiguration
 @seealso VZMacAuxiliaryStorage
 */
@property (readonly, copy) VZMacHardwareModel *hardwareModel;

/*!
 @abstract The minimum supported number of CPUs for this configuration.
 @discussion
    A VZMacOSConfigurationRequirements object is associated with a specific VZMacOSRestoreImage object, and thus a specific macOS configuration.
    This property specifies the minimum number of CPUs required by the associated macOS configuration.
    Installing or running the associated configuration of macOS on a virtual machine with fewer than this number of CPUs will result in undefined behavior.
 */
@property (readonly) NSUInteger minimumSupportedCPUCount;

/*!
 @abstract The minimum supported memory size for this configuration.
 @discussion
    A VZMacOSConfigurationRequirements object is associated with a specific VZMacOSRestoreImage object, and thus a specific macOS configuration.
    This property specifies the minimum amount of memory required by the associated macOS configuration.
    Installing or running the associated configuration of macOS on a virtual machine with less than this amount of memory will result in undefined behavior.
 */
@property (readonly) uint64_t minimumSupportedMemorySize;

@end

NS_ASSUME_NONNULL_END

#endif
