//
//  VZFileHandleNetworkDeviceAttachment.h
//  Virtualization
//
//  Copyright © 2020-2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZNetworkDeviceAttachment.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Network device attachment sending raw network packets over a file handle.
 @discussion
    The file handle attachment transmits the raw packets/frames between the virtual network interface and a file handle.
    The data transmitted through this attachment is at the level of the data link layer.

    The file handle must hold a connected datagram socket.

 @see VZNetworkDeviceConfiguration
 @see VZVirtioNetworkDeviceConfiguration
 */
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZFileHandleNetworkDeviceAttachment : VZNetworkDeviceAttachment

/*!
 @abstract Initialize the attachment with a file handle.
 @param fileHandle File handle holding a connected datagram socket.
 */
- (instancetype)initWithFileHandle:(NSFileHandle *)fileHandle NS_DESIGNATED_INITIALIZER;

/*!
 @abstract The file handle associated with this attachment.
 */
@property (readonly, strong) NSFileHandle *fileHandle;

/*!
 @abstract The maximum transmission unit (MTU) associated with this attachment.
 @discussion
    The client side of the associated datagram socket must be properly configured with the appropriate values for
    `SO_SNDBUF`, and `SO_RCVBUF`, which can be set using the `setsockopt` system call. The value of `SO_RCVBUF` is
    expected to be at least double the value of `SO_SNDBUF`, and for optimal performance, the value of `SO_RCVBUF`
    is recommended to be four times the value of `SO_SNDBUF`.

    The default MTU is 1500.
    The maximum MTU allowed is 65535, and the minimum MTU allowed is 1500. An invalid MTU value will result in an invalid
    virtual machine configuration.
 */
@property (readwrite) NSInteger maximumTransmissionUnit API_AVAILABLE(macos(13.0));

@end

NS_ASSUME_NONNULL_END
