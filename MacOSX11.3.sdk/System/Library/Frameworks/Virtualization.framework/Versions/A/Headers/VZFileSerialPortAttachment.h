//
//  VZFileSerialPortAttachment.h
//  Virtualization
//
//  Copyright © 2019-2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZSerialPortAttachment.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract File serial port attachment.
 @discussion
    VZFileSerialPortAttachment defines a serial port attachment from a file.
    Any data sent by the guest on the serial interface is written to the file.
    No data is sent to the guest over serial with this attachment.
 */
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZFileSerialPortAttachment : VZSerialPortAttachment

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Initialize the VZFileSerialPortAttachment from a URL of a file.
 @param url The URL of the file for the attachment on the local file system.
 @param shouldAppend True if the file should be opened in append mode, false otherwise.
        When a file is opened in append mode, writing to that file will append to the end of it.
 @param error If not nil, used to report errors if initialization fails.
 @return A VZFileSerialPortAttachment on success. Nil otherwise and the error parameter is populated if set.
 */
- (nullable instancetype)initWithURL:(NSURL *)url append:(BOOL)shouldAppend error:(NSError * _Nullable *)error NS_DESIGNATED_INITIALIZER;

/*!
 @abstract The URL of the file for the attachment on the local file system.
 */
@property (readonly, copy) NSURL *URL;

/*!
 @abstract True if the file should be opened in append mode, false otherwise.
 */
@property (readonly) BOOL append;

@end

NS_ASSUME_NONNULL_END
