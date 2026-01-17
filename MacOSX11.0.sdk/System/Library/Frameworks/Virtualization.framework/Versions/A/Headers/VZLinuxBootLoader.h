//
//  VZLinuxBootLoader.h
//  Virtualization
//
//  Copyright © 2019-2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZBootLoader.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Boot loader configuration for a Linux kernel.
*/
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZLinuxBootLoader : VZBootLoader

/*!
 @abstract Create a VZLinuxBootLoader with the Linux kernel passed as URL.
 @param kernelURL The URL of Linux kernel on the local file system.
*/
- (instancetype)initWithKernelURL:(NSURL *)kernelURL NS_DESIGNATED_INITIALIZER;

/*!
 @abstract URL of the Linux kernel.
*/
@property (copy) NSURL *kernelURL;

/*!
 @abstract Define the command-line parameters passed to the kernel on boot.
 @link https://www.kernel.org/doc/html/latest/admin-guide/kernel-parameters.html
*/
@property (copy) NSString *commandLine;

/*!
 @abstract Set the optional initial RAM disk. The RAM disk is mapped into memory before booting the kernel.
*/
@property (nullable, copy) NSURL *initialRamdiskURL;

@end

NS_ASSUME_NONNULL_END
