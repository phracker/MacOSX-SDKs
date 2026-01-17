/*	NSXPCConnection.h
        Copyright (c) 2011-2017, Apple Inc. All rights reserved.
 */

#import <dispatch/dispatch.h>
#import <bsm/audit.h>

#import <Foundation/NSObject.h> 
#import <Foundation/NSCoder.h>

#import <CoreFoundation/CFDictionary.h>

@class NSMutableDictionary, NSString, NSOperationQueue, NSSet<ObjectType>, NSLock, NSError;
@class NSXPCConnection, NSXPCListener, NSXPCInterface, NSXPCListenerEndpoint;
@protocol NSXPCListenerDelegate;

NS_ASSUME_NONNULL_BEGIN

// The connection itself and all proxies vended by the connection will conform with this protocol. This allows creation of new proxies from other proxies.
@protocol NSXPCProxyCreating

// Returns a proxy object with no error handling block. Messages sent to the proxy object will be sent over the wire to the other side of the connection. All messages must be 'oneway void' return type. Control may be returned to the caller before the message is sent. This proxy object will conform with the NSXPCProxyCreating protocol.
- (id)remoteObjectProxy;

// Returns a proxy object which will invoke the error handling block if an error occurs on the connection. If the message sent to the proxy has a reply handler, then either the error handler or the reply handler will be called exactly once. This proxy object will also conform with the NSXPCProxyCreating protocol.
- (id)remoteObjectProxyWithErrorHandler:(void (^)(NSError *error))handler;

@optional

// Make a synchronous IPC call instead of the default async behavior. The error handler block and reply block will be invoked on the calling thread before the message to the proxy returns, instead of on the queue for the connection.
- (id)synchronousRemoteObjectProxyWithErrorHandler:(void (NS_NOESCAPE ^)(NSError *error))handler API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

@end

// ----------------------------------

// Options that may be passed to a connection.
typedef NS_OPTIONS(NSUInteger, NSXPCConnectionOptions) {
    // Use this option if connecting to a service in the privileged Mach bootstrap (for example, a launchd.plist in /Library/LaunchDaemons).
    NSXPCConnectionPrivileged = (1 << 12UL)
} API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));

// This object is the main configuration mechanism for the communication between two processes. Each NSXPCConnection instance has a private serial queue. This queue is used when sending messages to reply handlers, interruption handlers, and invalidation handlers.
NS_CLASS_AVAILABLE(10_8, 6_0)
@interface NSXPCConnection : NSObject <NSXPCProxyCreating> {
@private
    void *_xconnection;
    id _repliesExpected;
    dispatch_queue_t _userQueue;
    uint32_t _state;
    uint32_t _state2;
    void (^_interruptionHandler)();
    void (^_invalidationHandler)();
    id _exportInfo;
    id _repliesRequested;
    id _importInfo;
    id <NSObject> _otherInfo;
    id _reserved1;
    id _lock;
    NSXPCInterface *_remoteObjectInterface;
    NSString *_serviceName;
    NSXPCListenerEndpoint *_endpoint;
    id _eCache;
    id _dCache;
}

// Initialize an NSXPCConnection that will connect to the specified service name. Note: Receiving a non-nil result from this init method does not mean the service name is valid or the service has been launched. The init method simply constructs the local object.
- (instancetype)initWithServiceName:(NSString *)serviceName __IOS_PROHIBITED __WATCHOS_PROHIBITED __TVOS_PROHIBITED;
@property (nullable, readonly, copy) NSString *serviceName;

// Use this if looking up a name advertised in a launchd.plist. For example, an agent with a launchd.plist in ~/Library/LaunchAgents. If the connection is being made to something in a privileged Mach bootstrap (for example, a daemon with a launchd.plist in /Library/LaunchDaemons), then use the NSXPCConnectionPrivileged option. Note: Receiving a non-nil result from this init method does not mean the service name is valid or the service has been launched. The init method simply constructs the local object.
- (instancetype)initWithMachServiceName:(NSString *)name options:(NSXPCConnectionOptions)options __IOS_PROHIBITED __WATCHOS_PROHIBITED __TVOS_PROHIBITED;

// Initialize an NSXPCConnection that will connect to an NSXPCListener (identified by its NSXPCListenerEndpoint).
- (instancetype)initWithListenerEndpoint:(NSXPCListenerEndpoint *)endpoint;
@property (readonly, retain) NSXPCListenerEndpoint *endpoint;

// The interface that describes messages that are allowed to be received by the exported object on this connection. This value is required if a exported object is set.
@property (nullable, retain) NSXPCInterface *exportedInterface;

// Set an exported object for the connection. Messages sent to the remoteObjectProxy from the other side of the connection will be dispatched to this object. Messages delivered to exported objects are serialized and sent on a non-main queue. The receiver is responsible for handling the messages on a different queue or thread if it is required.
@property (nullable, retain) id exportedObject;

// The interface that describes messages that are allowed to be received by object that has been "imported" to this connection (exported from the other side). This value is required if messages are sent over this connection.
@property (nullable, retain) NSXPCInterface *remoteObjectInterface;

// Get a proxy for the remote object (that is, the object exported from the other side of this connection). See descriptions in NSXPCProxyCreating for more details.
@property (readonly, retain) id remoteObjectProxy;

- (id)remoteObjectProxyWithErrorHandler:(void (^)(NSError *error))handler;

// Make a synchronous IPC call instead of the default async behavior. The error handler block and reply block will be invoked on the calling thread before the message to the proxy returns, instead of on the queue for the connection.
- (id)synchronousRemoteObjectProxyWithErrorHandler:(void (^)(NSError *error))handler API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

// The interruption handler will be called if the remote process exits or crashes. It may be possible to re-establish the connection by simply sending another message. The handler will be invoked on the same queue as replies and other handlers, but there is no guarantee of ordering between those callbacks and this one.
// The interruptionHandler property is cleared after the connection becomes invalid. This is to mitigate the impact of a retain cycle created by referencing the NSXPCConnection instance inside this block.
@property (nullable, copy) void (^interruptionHandler)(void);

// The invalidation handler will be called if the connection can not be formed or the connection has terminated and may not be re-established. The invalidation handler will also be called if a connection created with an NSXPCListenerEndpoint is invalidated from the remote side, or if the NSXPCListener used to create that endpoint is invalidated. The handler will be invoked on the same queue as replies and other handlers, but there is no guarantee of ordering between those callbacks and this one.
// You may not send messages over the connection from within an invalidation handler block.
// The invalidationHandler property is cleared after the connection becomes invalid. This is to mitigate the impact of a retain cycle created by referencing the NSXPCConnection instance inside this block.
@property (nullable, copy) void (^invalidationHandler)(void);

// All connections start suspended. You must resume them before they will start processing received messages or sending messages through the remoteObjectProxy. Note: Calling resume does not immediately launch the XPC service. The service will be started on demand when the first message is sent. However, if the name specified when creating the connection is determined to be invalid, your invalidation handler will be called immediately (and asynchronously) after calling resume.
- (void)resume;

// Suspend the connection. Suspends must be balanced with resumes before the connection may be invalidated.
- (void)suspend;

// Invalidate the connection. All outstanding error handling blocks and invalidation blocks will be called on the message handling queue. The connection must be invalidated before it is deallocated. After a connection is invalidated, no more messages may be sent or received.
- (void)invalidate;

// These attributes describe the security attributes of the connection. They may be used by the listener delegate to accept or reject connections.
@property (readonly) au_asid_t auditSessionIdentifier;
@property (readonly) pid_t processIdentifier;
@property (readonly) uid_t effectiveUserIdentifier;
@property (readonly) gid_t effectiveGroupIdentifier;

@end


// Each NSXPCListener instance has a private serial queue. This queue is used when sending the delegate messages.
NS_CLASS_AVAILABLE(10_8, 6_0)
@interface NSXPCListener : NSObject {
@private
    void *_xconnection;
    dispatch_queue_t _userQueue;
    void *reserved0;
    id <NSXPCListenerDelegate> _delegate;
    NSString *_serviceName;
    uint64_t _state;
    id _reserved1;
    id _reserved2;
}

// If your listener is an XPCService (that is, in the XPCServices folder of an application or framework), then use this method to get the shared, singleton NSXPCListener object that will await new connections. When the resume method is called on this listener, it will not return. Instead it hands over control to the object and allows it to service the listener as appropriate. This makes it ideal for use in your main() function. For more info on XPCServices, please refer to the developer documentation.
+ (NSXPCListener *)serviceListener;

// Create an anonymous listener connection. Other processes may connect to this listener by passing this listener object's endpoint to NSXPCConnection's -initWithListenerEndpoint: method.
+ (NSXPCListener *)anonymousListener;

// Use this if listening on name advertised in a launchd.plist For example, an agent with a launchd.plist in ~/Library/LaunchAgents, or a daemon with a launchd.plist in /Library/LaunchDaemons.
- (instancetype)initWithMachServiceName:(NSString *)name NS_DESIGNATED_INITIALIZER __IOS_PROHIBITED __WATCHOS_PROHIBITED __TVOS_PROHIBITED;

// The delegate for the connection listener. If no delegate is set, all new connections will be rejected. See the protocol for more information on how to implement it.
@property (nullable, assign) id <NSXPCListenerDelegate> delegate;

// Get an endpoint object which may be sent over an existing connection. This allows the receiver of the endpoint to create a new connection to this NSXPCListener. The NSXPCListenerEndpoint uniquely names this listener object across connections.
@property (readonly, retain) NSXPCListenerEndpoint *endpoint;

// All listeners start suspended and must be resumed before they will process incoming requests. If called on the serviceListener, this method will never return. Call it as the last step inside your main function in your XPC service after setting up desired initial state and the listener itself. If called on any other NSXPCListener, the connection is resumed and the method returns immediately.
- (void)resume;

// Suspend the listener. Suspends must be balanced with resumes before the listener may be invalidated.
- (void)suspend;

// Invalidate the listener. No more connections will be created. Once a listener is invalidated it may not be resumed or suspended.
- (void)invalidate;

@end

@protocol NSXPCListenerDelegate <NSObject>
@optional
// Accept or reject a new connection to the listener. This is a good time to set up properties on the new connection, like its exported object and interfaces. If a value of NO is returned, the connection object will be invalidated after this method returns. Be sure to resume the new connection and return YES when you are finished configuring it and are ready to receive messages. You may delay resuming the connection if you wish, but still return YES from this method if you want the connection to be accepted.
- (BOOL)listener:(NSXPCListener *)listener shouldAcceptNewConnection:(NSXPCConnection *)newConnection;

@end

// ----------------------------------

// This object holds all information about the interface of an exported or imported object. This includes: what messages are allowed, what kinds of objects are allowed as arguments, what the signature of any reply blocks are, and any information about additional proxy objects.
NS_CLASS_AVAILABLE(10_8, 6_0)
@interface NSXPCInterface : NSObject {
@private
    Protocol *_protocol;
    void *_reserved2;
    id _reserved1;
}

// Factory method to get an NSXPCInterface instance for a given protocol. Most interfaces do not need any further configuration. Interfaces with collection classes or additional proxy objects should be configured using the methods below.
+ (NSXPCInterface *)interfaceWithProtocol:(Protocol *)protocol;

// The Objective C protocol this NSXPCInterface is based upon.
@property (assign) Protocol *protocol;

// If an argument to a method in your protocol is a collection class (for example, NSArray or NSDictionary), then the interface must be configured with the set of expected classes contained inside of the collection. The classes argument to this method should be an NSSet containing Class objects, like [MyObject class]. The selector argument specifies which method in the protocol is being configured. The argumentIndex parameter specifies which argument of the method the NSSet applies to. If the NSSet is for an argument of the reply block in the method, pass YES for the ofReply: argument. The first argument is index 0 for both the method and the reply block.
// If the expected classes are all property list types, calling this method is optional (property list types are automatically whitelisted for collection objects). You may use this method to further restrict the set of allowed classes.
- (void)setClasses:(NSSet<Class> *)classes forSelector:(SEL)sel argumentIndex:(NSUInteger)arg ofReply:(BOOL)ofReply;
- (NSSet<Class> *)classesForSelector:(SEL)sel argumentIndex:(NSUInteger)arg ofReply:(BOOL)ofReply;

// If an argument to a method in your protocol should be sent as a proxy object instead of by copy, then the interface must be configured with the interface of that new proxy object. If the proxy object is to be an argument of the reply block, pass YES for ofReply. The first argument is index 0 for both the method and the reply block.
- (void)setInterface:(NSXPCInterface *)ifc forSelector:(SEL)sel argumentIndex:(NSUInteger)arg ofReply:(BOOL)ofReply;
- (nullable NSXPCInterface *)interfaceForSelector:(SEL)sel argumentIndex:(NSUInteger)arg ofReply:(BOOL)ofReply;

@end

// ----------------------------------

// An instance of this class is a reference to an NSXPCListener that may be encoded and sent over a connection. The receiver may use the object to create a new connection to the listener that supplied the NSXPCListenerEndpoint object.
NS_CLASS_AVAILABLE(10_8, 6_0)
@interface NSXPCListenerEndpoint : NSObject <NSSecureCoding> {
@private
    void *_internal;
}
@end

NS_ASSUME_NONNULL_END
