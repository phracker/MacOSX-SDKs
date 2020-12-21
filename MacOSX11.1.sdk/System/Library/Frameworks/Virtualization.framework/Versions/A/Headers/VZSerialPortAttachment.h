//
//  VZSerialPortAttachment.h
//  Virtualization
//
//  Copyright © 2019-2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Base class for a serial port attachment.
 @discussion
    A serial port attachment defines how the virtual machine's serial port interfaces with the host system.
    VZSerialPortAttachment should not be instantiated directly.
    One of its subclasses like VZFileHandleSerialPortAttachment should be used instead.

 @see VZFileHandleSerialPortAttachment
 @see VZFileSerialPortAttachment
 */
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZSerialPortAttachment : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
