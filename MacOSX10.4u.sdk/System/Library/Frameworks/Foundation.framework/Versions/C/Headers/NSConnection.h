/*	NSConnection.h
	Copyright (c) 1989-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>

@class NSMutableData, NSDistantObject, NSException, NSData;
@class NSPort, NSRunLoop, NSPortNameServer, NSDictionary, NSArray;

@interface NSConnection : NSObject {
    @private
    id		receivePort;
    id		sendPort;
    id          delegate;
    int32_t	busy;
    char	slack[12];
    id		statistics;
    unsigned char isDead;
    unsigned char isValid;
    unsigned char wantsInvalid;
    unsigned char authGen:1;
    unsigned char authCheck:1;
    unsigned char encryptFlag:1;
    unsigned char decryptFlag:1;
    unsigned char doRequest:1;
    unsigned char isQueueing:1;
    unsigned char isMulti:1;
    unsigned char invalidateRP:1;
    id          localProxies;
    id          remoteProxies;
    id          runLoops;
    id		requestModes;
    id          rootObject;
    void *	registerInfo;
    id		replMode;
    id          classInfoImported;
    id		releasedProxies;
    void *	reserved;
}

- (NSDictionary *)statistics;

+ (NSArray *)allConnections;

+ (NSConnection *)defaultConnection;

+ (NSConnection *)connectionWithRegisteredName:(NSString *)name host:(NSString *)hostName;
+ (NSConnection *)connectionWithRegisteredName:(NSString *)name host:(NSString *)hostName usingNameServer:(NSPortNameServer *)server;
+ (NSDistantObject *)rootProxyForConnectionWithRegisteredName:(NSString *)name host:(NSString *)hostName;
+ (NSDistantObject *)rootProxyForConnectionWithRegisteredName:(NSString *)name host:(NSString *)hostName usingNameServer:(NSPortNameServer *)server;

- (void)setRequestTimeout:(NSTimeInterval)ti;
- (NSTimeInterval)requestTimeout;
- (void)setReplyTimeout:(NSTimeInterval)ti;
- (NSTimeInterval)replyTimeout;

- (void)setRootObject:(id)anObject;
- (id)rootObject;

- (NSDistantObject *)rootProxy;
  
- (void)setDelegate:(id)anObject;
- (id)delegate;

- (void)setIndependentConversationQueueing:(BOOL)yorn;
- (BOOL)independentConversationQueueing;

- (BOOL)isValid;

- (void)invalidate;

- (void)addRequestMode:(NSString *)rmode;
- (void)removeRequestMode:(NSString *)rmode;
- (NSArray *)requestModes;

- (BOOL)registerName:(NSString *) name;
- (BOOL)registerName:(NSString *) name withNameServer:(NSPortNameServer *)server;

+ (NSConnection *)connectionWithReceivePort:(NSPort *)receivePort sendPort:(NSPort *)sendPort;

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

@end

FOUNDATION_EXPORT NSString * const NSConnectionReplyMode;

FOUNDATION_EXPORT NSString * const NSConnectionDidDieNotification;


@interface NSObject (NSConnectionDelegateMethods)

// Use the NSConnectionDidInitializeNotification notification instead
// of this delegate method if possible.
- (BOOL)makeNewConnection:(NSConnection *)conn sender:(NSConnection *)ancestor;

// Use the NSConnectionDidInitializeNotification notification instead
// of this delegate method if possible.
- (BOOL)connection:(NSConnection *)ancestor shouldMakeNewConnection:(NSConnection *)conn;

- (NSData *)authenticationDataForComponents:(NSArray *)components;
- (BOOL)authenticateComponents:(NSArray *)components withData:(NSData *)signature;

- (id)createConversationForConnection:(NSConnection *)conn;

@end

FOUNDATION_EXPORT NSString * const NSFailedAuthenticationException;

FOUNDATION_EXPORT NSString * const NSConnectionDidInitializeNotification;

@interface NSDistantObjectRequest : NSObject

- (NSInvocation *)invocation;
- (NSConnection *)connection;
- (id)conversation;
- (void)replyWithException:(NSException *)exception;

@end

@interface NSObject (NSDistantObjectRequestMethods)

- (BOOL)connection:(NSConnection *)connection handleRequest:(NSDistantObjectRequest *)doreq;

@end

