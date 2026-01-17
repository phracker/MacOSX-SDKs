//
//  VZVirtioConsolePortConfiguration.h
//  Virtualization
//
//  Copyright © 2022-2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZConsolePortConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Virtio Console Port
 @discussion
    A console port is a two-way communication channel between a host VZSerialPortAttachment and a virtual machine console port. One or more console ports are attached to a Virtio console device.

    An optional name may be set for a console port. A console port may also be configured for use as the system console.
 @see VZConsolePortConfiguration
 @see VZVirtualMachineConfiguration.consoleDevices
 */
VZ_EXPORT API_AVAILABLE(macos(13.0))
@interface VZVirtioConsolePortConfiguration : VZConsolePortConfiguration

- (instancetype)init NS_DESIGNATED_INITIALIZER;

/*!
 @abstract The console port's name. The default behavior is to not use a name unless set.
 */
@property (nullable, copy) NSString *name;

/*!
 @abstract The console port may be marked for use as the system console. The default is false.
 */
@property BOOL isConsole;

@end

NS_ASSUME_NONNULL_END
