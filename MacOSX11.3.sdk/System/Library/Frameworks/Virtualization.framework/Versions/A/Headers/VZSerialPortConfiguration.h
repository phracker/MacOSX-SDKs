//
//  VZSerialPortConfiguration.h
//  Virtualization
//
//  Copyright © 2019-2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class VZSerialPortAttachment;

/*!
 @abstract Base class for a serial port configuration.
 @discussion
    VZSerialPortConfiguration should not be instantiated directly.
    One of its subclasses like VZVirtioConsoleDeviceSerialPortConfiguration should be used instead.

 @see VZVirtioConsoleDeviceSerialPortConfiguration
*/
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZSerialPortConfiguration : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Serial port attachment. Defines how the virtual machine's serial port interfaces with the host system. Default is nil.
 @see VZFileHandleSerialPortAttachment
 @see VZFileSerialPortAttachment
 */
@property (readwrite, nullable, strong) VZSerialPortAttachment *attachment;

@end

NS_ASSUME_NONNULL_END
