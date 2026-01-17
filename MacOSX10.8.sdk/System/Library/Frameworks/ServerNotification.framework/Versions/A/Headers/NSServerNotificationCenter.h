/*	NSServerNotificationCenter.h
 Copyright (c) 2008-2011 Apple Inc. All rights reserved.
 */

#include <AvailabilityMacros.h>
#import <Foundation/Foundation.h>

#ifndef DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER
#define DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER
#endif

@interface NSServerNotificationCenter : NSNotificationCenter {
	__strong void * _internal;
}

// Get a notification center for a particular notification server (initiates a connection to that server)
+ (id)centerForService:(NSString *)serviceHost DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

// Utility functions
- (NSString *)serviceHost DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER; // accessor for the serviceAddress passed in when this center was created

// anObject is currently ignored.  set to nil.
- (void)addObserver:(id)observer selector:(SEL)aSelector name:(NSString *)aName object:(id)anObject DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

// posting of a notification will only work if the notification name exists on the server and the
// user has permission to post to it.  The node for the notification can be created using the
// notificationconf tool.
- (void)postNotification:(NSNotification *)notification DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;
- (void)postNotificationName:(NSString *)aName object:(id)anObject DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;
- (void)postNotificationName:(NSString *)aName object:(id)anObject userInfo:(NSDictionary *)aUserInfo DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

- (void)removeObserver:(id)observer DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;
// anObject is ignored
- (void)removeObserver:(id)observer name:(NSString *)aName object:(id)anObject DEPRECATED_IN_MAC_OS_X_VERSION_10_8_AND_LATER;

@end

