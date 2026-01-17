//
//  VZVirtioConsolePort.h
//  Virtualization
//
//  Copyright © 2022-2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZSerialPortAttachment.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Class representing a Virtio console port in a virtual machine.
 @discussion
    VZVirtioConsolePort should not be instantiated directly. This object can be retrieved from the VZVirtioConsoleDevice ports property.
 */
VZ_EXPORT API_AVAILABLE(macos(13.0))
@interface VZVirtioConsolePort : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract The console port name currently being used by this port.
 @discussion
    This property may not change while the VM is running. A null value indicates no name has been set.
 */
@property (readonly, nullable, copy) NSString *name;

/*!
 @abstract The console port attachment that's currently connected to this console port.
 @discussion
    This property may change at any time while the VM is running.
 */
@property (nullable, strong) VZSerialPortAttachment *attachment;

@end

NS_ASSUME_NONNULL_END
