//
//  VZEFIBootLoader.h
//  Virtualization
//
//  Copyright © 2019-2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZBootLoader.h>
#import <Virtualization/VZEFIVariableStore.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Boot loader configuration for booting guest operating systems expecting an EFI ROM.
 @discussion
    You must use a VZGenericPlatformConfiguration in conjunction with the EFI boot loader.
    It is invalid to use it with any other platform configuration.
 @see VZGenericPlatformConfiguration
 @see VZVirtualMachineConfiguration.platform.
*/
VZ_EXPORT API_AVAILABLE(macos(13.0))
@interface VZEFIBootLoader : VZBootLoader

- (instancetype)init NS_DESIGNATED_INITIALIZER;

/*!
 @abstract The EFI variable store.
 */
@property (nullable, strong) VZEFIVariableStore *variableStore;

@end

NS_ASSUME_NONNULL_END
