//
//  VZVirtioSocketDevice.h
//  Virtualization
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZSocketDevice.h>

NS_ASSUME_NONNULL_BEGIN

@class VZVirtioSocketConnection;
@class VZVirtioSocketListener;

/*!
 @abstract Virtio Socket Device
 @discussion
    This is a paravirtualized socket device which facilitates data transfer between the guest and the host without using Ethernet or IP protocols.
    This device is created through instantiating a VZVirtioSocketDeviceConfiguration in a VZVirtualMachineConfiguration and is available in the VZVirtualMachine.socketDevices property.
 @see VZVirtioSocketDeviceConfiguration
 @see VZVirtioSocketDeviceConnection
 @see VZVirtioSocketDeviceListener
 */
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZVirtioSocketDevice : VZSocketDevice

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Sets a listener at a specified port.
 @discussion
    There is only one listener per port, any existing listener will be removed, and the specified listener here will be set instead.
    The same listener can be registered on multiple ports.
    The listener's delegate will be called whenever the guest connects to that port.
 @param listener The VZVirtioSocketListener object to be set.
 @param port The port number to set the listener at.
 */
- (void)setSocketListener:(VZVirtioSocketListener *)listener forPort:(uint32_t)port;

/*!
 @abstract Removes the listener at a specfied port.
 @discussion Does nothing if the port had no listener.
 @param port The port number at which the listener is to be removed.
 */
- (void)removeSocketListenerForPort:(uint32_t)port;

/*!
 @abstract Connects to a specified port.
 @discussion Does nothing if the guest does not listen on that port.
 @param port The port number to connect to.
 @param completionHandler Block called after the connection has been successfully established or on error.
    The error parameter passed to the block is nil if the connection was successful.
 */
- (void)connectToPort:(uint32_t)port completionHandler:(void (^)(VZVirtioSocketConnection * _Nullable connection, NSError * _Nullable error))completionHandler NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
