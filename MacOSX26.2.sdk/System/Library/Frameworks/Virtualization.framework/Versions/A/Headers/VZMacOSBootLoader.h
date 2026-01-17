//
//  VZMacOSBootLoader.h
//  Virtualization
//
//  Copyright © 2021-2023 Apple Inc. All rights reserved.
//

#ifdef __arm64__

#import <Virtualization/VZBootLoader.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Boot loader configuration for booting macOS on Apple Silicon.
 @discussion
    You must use a VZMacPlatformConfiguration in conjunction with the macOS boot loader.
    It is invalid to use it with any other platform configuration.
 @see VZMacPlatformConfiguration
 @see VZVirtualMachineConfiguration.platform.
*/
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZMacOSBootLoader : VZBootLoader

/*!
 @abstract Create a VZMacOSBootLoader.
*/
- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END

#endif
