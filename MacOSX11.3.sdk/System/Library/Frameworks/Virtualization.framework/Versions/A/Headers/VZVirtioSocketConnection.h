//
//  VZVirtioSocketConnection.h
//  Virtualization
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract The VZVirtioSocketConnection object represents a Virtio socket device's connection.
 @discussion The connection encompasses a source port, destination port, and an associated file descriptor.
 @see VZVirtioSocketDevice
 */
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZVirtioSocketConnection : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract The destination port number of the connection.
 */
@property (readonly) uint32_t destinationPort;

/*!
 @abstract The source port number of the connection.
 */
@property (readonly) uint32_t sourcePort;

/*!
 @abstract The file descriptor associated with the socket.
 @discussion
    Data is sent by writing to the file descriptor.
    Data is received by reading from the file descriptor.
    A file descriptor of -1 indicates a closed connection.
 */
@property (readonly) int fileDescriptor;

/*!
 @abstract Close the file descriptor that's associated with the socket.
 */
- (void)close;

@end

NS_ASSUME_NONNULL_END
