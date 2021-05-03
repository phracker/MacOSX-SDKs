//
//  VZBootLoader.h
//  Virtualization
//
//  Copyright © 2019-2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Base class of boot loader configuration.
 @discussion
     VZVirtualMachineConfiguration requires a boot loader defining how to start the virtual machine.
     VZBootLoader is the abstract base class of boot loader definitions.

     Don't instantiate VZBootLoader directly, instead use its subclass VZLinuxBootloader.

 @see VZLinuxBootLoader.
 */
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZBootLoader : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
