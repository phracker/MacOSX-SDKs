//
//  VZVirtioSocketListener.h
//  Virtualization
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class VZVirtioSocketConnection, VZVirtioSocketDevice;
@protocol VZVirtioSocketListenerDelegate;

/*!
 @abstract The VZVirtioSocketListener object represents a listener for the Virtio socket device.
 @discussion
    The listener encompasses a VZVirtioSocketListenerDelegate object.
    VZVirtioSocketListener is used with VZVirtioSocketDevice to listen to a particular port.
    The delegate is used when a guest connects to a port associated with the listener.
 @see VZVirtioSocketDevice
 @see VZVirtioSocketListenerDelegate
 */
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZVirtioSocketListener : NSObject

/*!
 @abstract Pointer to a delagate object for the listener.
 */
@property (readwrite, weak) id <VZVirtioSocketListenerDelegate> delegate;

@end

/*!
 @abstract Delegate object for VZVirtioSocketListener.
 @discussion
    A class conforming to VZVirtioSocketListenerDelegate protocol can provide a method establish a new connection to the socket.
 @see VZVirtioSocketDevice
 @see VZVirtioSocketListener
 @see VZVirtioSocketConnection
 */
@protocol VZVirtioSocketListenerDelegate <NSObject>
@optional

/*!
 @abstract Invoked when the Virtio socket device is accepting a new connection.
 @param listener The listener invoking the delegate method.
 @param connection The new connection to be established.
 @param socketDevice The Virtio socket device with which the new connection is to be established.
 @return YES if the connection should be established, NO otherwise.
 */
- (BOOL)listener:(VZVirtioSocketListener *)listener shouldAcceptNewConnection:(VZVirtioSocketConnection *)connection fromSocketDevice:(VZVirtioSocketDevice *)socketDevice;

@end

NS_ASSUME_NONNULL_END
