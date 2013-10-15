/*	NSServerNotificationCenter.h
 Copyright (c) 2008-2011 Apple Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>

@interface NSServerNotificationCenter : NSNotificationCenter {
	__strong void * _internal;
}

// Get a notification center for a particular notification server (initiates a connection to that server)
+ (id)centerForService:(NSString *)serviceHost;

// Utility functions
- (NSString *)serviceHost; // accessor for the serviceAddress passed in when this center was created

// anObject is currently ignored.  set to nil.
- (void)addObserver:(id)observer selector:(SEL)aSelector name:(NSString *)aName object:(id)anObject;

// posting of a notification will only work if the notification name exists on the server and the
// user has permission to post to it.  The node for the notification can be created using the
// notificationconf tool.
- (void)postNotification:(NSNotification *)notification;
- (void)postNotificationName:(NSString *)aName object:(id)anObject;
- (void)postNotificationName:(NSString *)aName object:(id)anObject userInfo:(NSDictionary *)aUserInfo;

- (void)removeObserver:(id)observer;
// anObject is ignored
- (void)removeObserver:(id)observer name:(NSString *)aName object:(id)anObject;

@end

