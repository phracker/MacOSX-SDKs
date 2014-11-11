/*	NSNotification.h
	Copyright (c) 1994-2014, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSDictionary, NSOperationQueue;

/****************	Notifications	****************/

@interface NSNotification : NSObject <NSCopying, NSCoding>

@property (readonly, copy) NSString *name;
@property (readonly, retain) id object;
@property (readonly, copy) NSDictionary *userInfo;

- (instancetype)initWithName:(NSString *)name object:(id)object userInfo:(NSDictionary *)userInfo NS_AVAILABLE(10_6, 4_0) NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end

@interface NSNotification (NSNotificationCreation)

+ (instancetype)notificationWithName:(NSString *)aName object:(id)anObject;
+ (instancetype)notificationWithName:(NSString *)aName object:(id)anObject userInfo:(NSDictionary *)aUserInfo;

- (instancetype)init /*NS_UNAVAILABLE*/;	/* do not invoke; not a valid initializer for this class */

@end

/****************	Notification Center	****************/

@interface NSNotificationCenter : NSObject {
    @package
    void * __strong _impl;
    void * __strong _callback;
    void *_pad[11];
}

+ (NSNotificationCenter *)defaultCenter;

- (void)addObserver:(id)observer selector:(SEL)aSelector name:(NSString *)aName object:(id)anObject;

- (void)postNotification:(NSNotification *)notification;
- (void)postNotificationName:(NSString *)aName object:(id)anObject;
- (void)postNotificationName:(NSString *)aName object:(id)anObject userInfo:(NSDictionary *)aUserInfo;

- (void)removeObserver:(id)observer;
- (void)removeObserver:(id)observer name:(NSString *)aName object:(id)anObject;

- (id <NSObject>)addObserverForName:(NSString *)name object:(id)obj queue:(NSOperationQueue *)queue usingBlock:(void (^)(NSNotification *note))block NS_AVAILABLE(10_6, 4_0);
    // The return value is retained by the system, and should be held onto by the caller in
    // order to remove the observer with removeObserver: later, to stop observation.

@end

