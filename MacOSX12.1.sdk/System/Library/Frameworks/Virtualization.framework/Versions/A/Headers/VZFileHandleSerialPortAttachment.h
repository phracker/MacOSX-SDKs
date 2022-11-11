//
//  VZFileHandleSerialPortAttachment.h
//  Virtualization
//
//  Copyright © 2019-2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZSerialPortAttachment.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract File handle serial port attachment.
 @discussion
    VZFileHandleSerialPortAttachment defines a serial port attachment from a file handle.
    Data written to fileHandleForReading goes to the guest. Data sent from the guest appears on fileHandleForWriting.
*/
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZFileHandleSerialPortAttachment : VZSerialPortAttachment

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Initialize the VZFileHandleSerialPortAttachment from file handles.
 @param fileHandleForReading File handle for reading from the file.
 @param fileHandleForWriting File handle for writing to the file.
 @discussion
    Each file handle must either be nil or have a valid file descriptor.
*/
- (instancetype)initWithFileHandleForReading:(nullable NSFileHandle *)fileHandleForReading fileHandleForWriting:(nullable NSFileHandle *)fileHandleForWriting NS_DESIGNATED_INITIALIZER;

/*!
 @abstract File handle for reading from the file.
 @discussion Data written to fileHandleForReading goes to the guest.
 */
@property (readonly, nullable, strong) NSFileHandle *fileHandleForReading;

/*!
 @abstract File handle for writing to the file.
 @discussion Data sent from the guest appears on fileHandleForWriting.
*/
@property (readonly, nullable, strong) NSFileHandle *fileHandleForWriting;

@end

NS_ASSUME_NONNULL_END
