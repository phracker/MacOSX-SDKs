//
//  VZMacOSVirtualMachineStartOptions.h
//  Virtualization
//
//  Copyright © 2022-2023 Apple Inc. All rights reserved.
//

#ifdef __arm64__

#import <Virtualization/VZVirtualMachineStartOptions.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Options controlling startup behavior of a virtual machine using VZMacOSBootLoader.
 */
VZ_EXPORT API_AVAILABLE(macos(13.0))
@interface VZMacOSVirtualMachineStartOptions : VZVirtualMachineStartOptions

/*! @abstract Whether to start up from macOS Recovery. */
@property BOOL startUpFromMacOSRecovery;

@end

NS_ASSUME_NONNULL_END

#endif
