//
//  VZConsolePortConfiguration.h
//  Virtualization
//
//  Copyright © 2022-2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class VZSerialPortAttachment;

/*!
 @abstract Base class for a console port configuration.
 @discussion
    VZConsolePortConfiguration should not be instantiated directly.
    One of its subclasses like VZVirtioConsolePortConfiguration should be used instead.

 @see VZVirtioConsolePortConfiguration
*/
VZ_EXPORT API_AVAILABLE(macos(13.0))
@interface VZConsolePortConfiguration : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Console port attachment. Defines how the virtual machine's console port interfaces with the host system. Default is nil.
 @see VZFileHandleSerialPortAttachment
 @see VZFileSerialPortAttachment
 @see VZSpiceAgentPortAttachment
 */
@property (nullable, strong) VZSerialPortAttachment *attachment;

@end

NS_ASSUME_NONNULL_END
