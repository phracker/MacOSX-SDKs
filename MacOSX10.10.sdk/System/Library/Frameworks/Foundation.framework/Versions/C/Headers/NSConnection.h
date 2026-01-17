/*	NSConnection.h
	Copyright (c) 1989-2014, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>

@class NSMutableData, NSDistantObject, NSException, NSData;
@class NSPort, NSRunLoop, NSPortNameServer, NSDictionary, NSArray;
@class NSDistantObjectRequest;
@protocol NSConnectionDelegate;

NS_AUTOMATED_REFCOUNT_WEAK_UNAVAILABLE
@interface NSConnection : NSObject {
    @private
    id		receivePort;
    id		sendPort;
    id          delegate;
    int32_t	busy;
    int32_t	localProxyCount;
    int32_t	waitCount;
    id		delayedRL;
    id		statistics;
    unsigned char isDead;
    unsigned char isValid;
    unsigned char wantsInvalid;
    unsigned char authGen:1;
    unsigned char authCheck:1;
    unsigned char _reserved1:1;
    unsigned char _reserved2:1;
    unsigned char doRequest:1;
    unsigned char isQueueing:1;
    unsigned char isMulti:1;
    unsigned char invalidateRP:1;
    id          ___1;
    id          ___2;
    id          runLoops;
    id		requestModes;
    id          rootObject;
    void *	registerInfo;
    id		replMode;
    id          classInfoImported;
    id		releasedProxies;
    id		reserved;
}

@property (readonly, copy) NSDictionary *statistics;

+ (NSArray *)allConnections;

+ (NSConnection *)defaultConnection NS_DEPRECATED(10_0, 10_6, NA, NA);

+ (instancetype)connectionWithRegisteredName:(NSString *)name host:(NSString *)hostName;
+ (instancetype)connectionWithRegisteredName:(NSString *)name host:(NSString *)hostName usingNameServer:(NSPortNameServer *)server;
+ (NSDistantObject *)rootProxyForConnectionWithRegisteredName:(NSString *)name host:(NSString *)hostName;
+ (NSDistantObject *)rootProxyForConnectionWithRegisteredName:(NSString *)name host:(NSString *)hostName usingNameServer:(NSPortNameServer *)server;

+ (instancetype)serviceConnectionWithName:(NSString *)name rootObject:(id)root usingNameServer:(NSPortNameServer *)server NS_AVAILABLE(10_5, 2_0);
+ (instancetype)serviceConnectionWithName:(NSString *)name rootObject:(id)root NS_AVAILABLE(10_5, 2_0);

@property NSTimeInterval requestTimeout;
@property NSTimeInterval replyTimeout;
@property (retain) id rootObject;
@property (assign) id<NSConnectionDelegate> delegate;
@property BOOL independentConversationQueueing;
@property (readonly, getter=isValid) BOOL valid;

@property (readonly, retain) NSDistantObject *rootProxy;

- (void)invalidate;

- (void)addRequestMode:(NSString *)rmode;
- (void)removeRequestMode:(NSString *)rmode;
@property (readonly, copy) NSArray *requestModes;

- (BOOL)registerName:(NSString *) name;
- (BOOL)registerName:(NSString *) name withNameServer:(NSPortNameServer *)server;

+ (instancetype)connectionWithReceivePort:(NSPort *)receivePort sendPort:(NSPort *)sendPort;

+ (id)currentConversation;

- (instancetype)initWithReceivePort:(NSPort *)receivePort sendPort:(NSPort *)sendPort;

@property (readonly, retain) NSPort *sendPort;
@property (readonly, retain) NSPort *receivePort;

- (void)enableMultipleThreads;
@property (readonly) BOOL multipleThreadsEnabled;

- (void)addRunLoop:(NSRunLoop *)runloop;
- (void)removeRunLoop:(NSRunLoop *)runloop;

- (void)runInNewThread;

@property (readonly, copy) NSArray *remoteObjects;
@property (readonly, copy) NSArray *localObjects;

// NSPort subclasses should use this method to ask a connection object to dispatch Distributed Objects component data received over the wire. This will decode the data, authenticate, and send the message.
- (void)dispatchWithComponents:(NSArray *)components NS_AVAILABLE(10_7, 5_0);

@end

FOUNDATION_EXPORT NSString * const NSConnectionReplyMode;

FOUNDATION_EXPORT NSString * const NSConnectionDidDieNotification;


@protocol NSConnectionDelegate <NSObject>
@optional

// Use the NSConnectionDidInitializeNotification notification instead
// of this delegate method if possible.
- (BOOL)makeNewConnection:(NSConnection *)conn sender:(NSConnection *)ancestor;

// Use the NSConnectionDidInitializeNotification notification instead
// of this delegate method if possible.
- (BOOL)connection:(NSConnection *)ancestor shouldMakeNewConnection:(NSConnection *)conn;

- (NSData *)authenticationDataForComponents:(NSArray *)components;
- (BOOL)authenticateComponents:(NSArray *)components withData:(NSData *)signature;

- (id)createConversationForConnection:(NSConnection *)conn;

- (BOOL)connection:(NSConnection *)connection handleRequest:(NSDistantObjectRequest *)doreq;

@end

FOUNDATION_EXPORT NSString * const NSFailedAuthenticationException;

FOUNDATION_EXPORT NSString * const NSConnectionDidInitializeNotification;

@interface NSDistantObjectRequest : NSObject

@property (readonly, retain) NSInvocation *invocation;
@property (readonly, retain) NSConnection *connection;
@property (readonly, retain) id conversation;
- (void)replyWithException:(NSException *)exception;

@end
