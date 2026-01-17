/*	NSConnection.h
	Copyright (c) 1989-2011, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>

@class NSMutableData, NSDistantObject, NSException, NSData;
@class NSPort, NSRunLoop, NSPortNameServer, NSDictionary, NSArray;
@class NSDistantObjectRequest;
@protocol NSConnectionDelegate;

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

- (NSDictionary *)statistics;

+ (NSArray *)allConnections;

+ (NSConnection *)defaultConnection NS_DEPRECATED(10_0, 10_6, NA, NA);

+ (id)connectionWithRegisteredName:(NSString *)name host:(NSString *)hostName;
+ (id)connectionWithRegisteredName:(NSString *)name host:(NSString *)hostName usingNameServer:(NSPortNameServer *)server;
+ (NSDistantObject *)rootProxyForConnectionWithRegisteredName:(NSString *)name host:(NSString *)hostName;
+ (NSDistantObject *)rootProxyForConnectionWithRegisteredName:(NSString *)name host:(NSString *)hostName usingNameServer:(NSPortNameServer *)server;

+ (id)serviceConnectionWithName:(NSString *)name rootObject:(id)root usingNameServer:(NSPortNameServer *)server NS_AVAILABLE(10_5, 2_0);
+ (id)serviceConnectionWithName:(NSString *)name rootObject:(id)root NS_AVAILABLE(10_5, 2_0);

- (void)setRequestTimeout:(NSTimeInterval)ti;
- (NSTimeInterval)requestTimeout;
- (void)setReplyTimeout:(NSTimeInterval)ti;
- (NSTimeInterval)replyTimeout;

- (void)setRootObject:(id)anObject;
- (id)rootObject;

- (NSDistantObject *)rootProxy;
  
- (void)setDelegate:(id <NSConnectionDelegate>)anObject;
- (id <NSConnectionDelegate>)delegate;

- (void)setIndependentConversationQueueing:(BOOL)yorn;
- (BOOL)independentConversationQueueing;

- (BOOL)isValid;

- (void)invalidate;

- (void)addRequestMode:(NSString *)rmode;
- (void)removeRequestMode:(NSString *)rmode;
- (NSArray *)requestModes;

- (BOOL)registerName:(NSString *) name;
- (BOOL)registerName:(NSString *) name withNameServer:(NSPortNameServer *)server;

+ (id)connectionWithReceivePort:(NSPort *)receivePort sendPort:(NSPort *)sendPort;

+ (id)currentConversation;

- (id)initWithReceivePort:(NSPort *)receivePort sendPort:(NSPort *)sendPort;
- (NSPort *)sendPort;
- (NSPort *)receivePort;

- (void)enableMultipleThreads;
- (BOOL)multipleThreadsEnabled;

- (void)addRunLoop:(NSRunLoop *)runloop;
- (void)removeRunLoop:(NSRunLoop *)runloop;

- (void)runInNewThread;

- (NSArray *)remoteObjects;
- (NSArray *)localObjects;

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

- (NSInvocation *)invocation;
- (NSConnection *)connection;
- (id)conversation;
- (void)replyWithException:(NSException *)exception;

@end
