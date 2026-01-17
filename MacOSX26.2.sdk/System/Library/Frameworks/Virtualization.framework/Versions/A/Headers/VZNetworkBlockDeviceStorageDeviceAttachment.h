//
//  VZNetworkBlockDeviceStorageDeviceAttachment.h
//  Virtualization
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDiskSynchronizationMode.h>
#import <Virtualization/VZStorageDeviceAttachment.h>

NS_ASSUME_NONNULL_BEGIN

@protocol VZNetworkBlockDeviceStorageDeviceAttachmentDelegate;

/*!
 @abstract Storage device attachment backed by a Network Block Device (NBD) client.
 @discussion
    This storage device attachment provides an NBD client implementation. The NBD client is connected
    to an NBD server referred to by an NBD Uniform Resource Indicator (URI), represented as an URL in
    this API. The NBD server runs outside of Virtualization framework and is not controlled by
    Virtualization framework. The NBD client forwards the guest's I/O operations to the NBD server,
    where the I/O operations are handled.

    The NBD client will attempt to connect to the NBD server referred to by the URL when you start the virtual
    machine (e.g. when `[VZVirtualMachine startWithCompletionHandler:]` is called). A connection attempt is NOT
    made when the attachment object is initialized. Reconnection attempts will take place throughout the life
    cycle of the virtual machine when the NBD client encounters a recoverable error such as connection timeout
    and unexpected connection errors. The NBD client will disconnect from the server when the virtual machine
    shuts down.

    Using this attachment requires the app to have the "com.apple.security.network.client" entitlement as this attachment opens an outgoing
    network connection.

    For more information about NBD, see https://github.com/NetworkBlockDevice/nbd/blob/master/doc/proto.md.
    For more information about the NBD URL format, see https://github.com/NetworkBlockDevice/nbd/blob/master/doc/uri.md.

    An example use of this API is:
    ```
    NSURL *url = [[NSURL alloc] initWithString:@"nbd://localhost:10809/myDisk"]
    NSError *error = nil;
    VZNetworkBlockDeviceStorageDeviceAttachment *attachment =
        [[VZNetworkBlockDeviceStorageDeviceAttachment alloc] initWithURL:url
                                                                 timeout:5.0
                                                          forcedReadOnly:NO
                                                     synchronizationMode:VZDiskSynchronizationModeFull
                                                                   error:&error];

    if (!attachment) {
        // Handle the `error`.
    }

    VZVirtioBlockDeviceConfiguration *blockDevice = [[VZVirtioBlockDeviceConfiguration alloc] initWithAttachment:attachment];
    ```
 */
VZ_EXPORT API_AVAILABLE(macos(14.0))
@interface VZNetworkBlockDeviceStorageDeviceAttachment : VZStorageDeviceAttachment

/*!
 @abstract Initialize the attachment from an NBD Uniform Resource Indicator (URI) represented as an URL.
 @param URL The URL referring to the NBD server to which the NBD client is to be connected.
 @param timeout The timeout value in seconds for the connection between the client and server. When the timeout expires, an attempt to reconnect with the server will take place.
 @param forcedReadOnly If YES, the disk attachment is forced to be read-only, regardless of whether or not the NBD server supports write requests.
 @param error If not nil, assigned with the error if the initialization failed.
 @return An initialized `VZNetworkBlockDeviceStorageDeviceAttachment` or nil if there was an error.
 @discussion
    The `forcedReadOnly` parameter affects how the NBD client is exposed to the guest operating system
    by the storage controller. As part of the NBD protocol, whether or not the disk exposed by the NBD client is
    read-only is advertised by the NBD server during the handshake phase of the protocol. Setting `forcedReadOnly`
    to YES will force the NBD client to show up as read-only to the guest regardless of whether or not the NBD
    server advertises itself as read-only.
 */
- (nullable instancetype)initWithURL:(NSURL *)URL timeout:(NSTimeInterval)timeout forcedReadOnly:(BOOL)forcedReadOnly synchronizationMode:(VZDiskSynchronizationMode)synchronizationMode error:(NSError **)error NS_DESIGNATED_INITIALIZER NS_SWIFT_NAME(init(url:timeout:isForcedReadOnly:synchronizationMode:));

/*!
 @abstract Convenience initializer to create the attachment from an NBD URL.
 @param URL The URL referring to the NBD server to which the NBD client is to be connected.
 @param error If not nil, assigned with the error if the initialization failed.
 @return An initialized `VZNetworkBlockDeviceStorageDeviceAttachment` or nil if there was an error.
 @discussion
    This initializer automatically assigns optimized default values for the `timeout`,
    `forcedReadOnly`, and `synchronizationMode` properties.
 */
- (nullable instancetype)initWithURL:(NSURL *)URL error:(NSError **)error;

/*!
 @abstract Check if URL is a valid NBD URL.
 @param URL The NBD URL to validate.
 @param error If not nil, assigned with an error describing why the URL is not valid.
 @discussion
    See https://github.com/NetworkBlockDevice/nbd/blob/master/doc/uri.md for more detailed descriptions
    of valid URIs.

    This method checks that the URL is well-formed, it does not attempt to access the URL.
 */
+ (BOOL)validateURL:(NSURL *)URL error:(NSError **)error;

/*!
 @abstract URL referring to the NBD server to which the NBD client is to be connected.
 */
@property (readonly, copy) NSURL *URL;

/*!
 @abstract The timeout value in seconds for the connection between the client and server. When the timeout expires, an attempt to reconnect with the server will take place.
 */
@property (readonly) NSTimeInterval timeout;

/*!
 @abstract Whether the underlying disk attachment is forced to be read-only.
 @discussion
    The `forcedReadOnly` parameter affects how the NBD client is exposed to the guest operating system
    by the storage controller. As part of the NBD protocol, whether or not the disk exposed by the NBD client
    is read-only is advertised by the NBD server during the handshake phase of the protocol. Setting
    `forcedReadOnly` to YES will force the NBD client to show up as read-only to the
    guest regardless of whether or not the NBD server advertises itself as read-only.
 */
@property (readonly, getter=isForcedReadOnly) BOOL forcedReadOnly NS_SWIFT_NAME(isForcedReadOnly);

/*!
 @abstract The mode in which the NBD client synchronizes data with the NBD server.
 */
@property (readonly) VZDiskSynchronizationMode synchronizationMode;

/*!
 @abstract The attachment's delegate.
 */
@property (nullable, weak) id <VZNetworkBlockDeviceStorageDeviceAttachmentDelegate> delegate;

@end

/*!
 @abstract A class conforming to VZNetworkBlockDeviceStorageDeviceAttachmentDelegate can provide
    methods for tracking the attachment's state.
 */
VZ_EXPORT API_AVAILABLE(macos(14.0))
@protocol VZNetworkBlockDeviceStorageDeviceAttachmentDelegate <NSObject>

@optional

/*!
 @abstract Invoked when the NBD client has successfully connected/reconnected with the server.
 @param attachment The attachment object invoking the delegate method.
 @discussion
    Connection with the server will take place when the virtual machine is first started, and reconnection
    attempts will take place when the connection times out or when the NBD client has encountered a recoverable
    error, such as an I/O error from the server. The method may be invoked multiple times during a virtual
    machine's life cycle. Reconnections are transparent to the guest.
 */
- (void)attachmentWasConnected:(VZNetworkBlockDeviceStorageDeviceAttachment *)attachment;

/*!
 @abstract Invoked when the NBD client has encountered a non-recoverable error.
 @param attachment The attachment object invoking the delegate method.
 @param error The error.
 @discussion
    The NBD client will be in a non-functional state after this method is invoked.
 */
- (void)attachment:(VZNetworkBlockDeviceStorageDeviceAttachment *)attachment didEncounterError:(NSError *)error;

@end

NS_ASSUME_NONNULL_END
