//
//  VZFileHandleNetworkDeviceAttachment.h
//  Virtualization
//
//  Copyright © 2020 Apple Inc. All rights reserved.
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

@end

NS_ASSUME_NONNULL_END
