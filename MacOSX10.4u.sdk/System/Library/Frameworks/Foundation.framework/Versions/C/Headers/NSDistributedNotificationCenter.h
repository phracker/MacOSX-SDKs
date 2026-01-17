/*	NSDistributedNotificationCenter.h
	Copyright (c) 1996-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSNotification.h>

@class NSString, NSDictionary;

FOUNDATION_EXPORT NSString * const NSLocalNotificationCenterType;
// Distributes notifications to all tasks on the sender's machine.

typedef enum {
    NSNotificationSuspensionBehaviorDrop = 1,
    // The server will not queue any notifications with this name and object until setSuspended:NO is called.
    NSNotificationSuspensionBehaviorCoalesce = 2,
    // The server will only queue the last notification of the specified name and object; earlier notifications are dropped.  In cover methods for which suspension behavior is not an explicit argument, NSNotificationSuspensionBehaviorCoalesce is the default.
    NSNotificationSuspensionBehaviorHold = 3,
    // The server will hold all matching notifications until the queue has been filled (queue size determined by the server) at which point the server may flush queued notifications.
    NSNotificationSuspensionBehaviorDeliverImmediately = 4
    // The server will deliver notifications matching this registration irrespective of whether setSuspended:YES has been called.  When a notification with this suspension behavior is matched, it has the effect of first flushing
    // any queued notifications.  The effect is somewhat as if setSuspended:NO were first called if the app is suspended, followed by
    // the notification in question being delivered, followed by a transition back to the previous suspended or unsuspended state.
} NSNotificationSuspensionBehavior;

@interface NSDistributedNotificationCenter : NSNotificationCenter

+ (NSDistributedNotificationCenter *)notificationCenterForType:(NSString *)notificationCenterType;
// Currently there is only one type.

+ (id)defaultCenter;
// Returns the default distributed notification center - cover for [NSDistributedNotificationCenter notificationCenterForType:NSLocalNotificationCenterType]

- (void)addObserver:(id)observer selector:(SEL)selector name:(NSString *)name object:(NSString *)object suspensionBehavior:(NSNotificationSuspensionBehavior)suspensionBehavior;
// All other registration methods are covers of this one, with the default for suspensionBehavior = NSNotificationSuspensionBehaviorCoalesce.

- (void)postNotificationName:(NSString *)name object:(NSString *)object userInfo:(NSDictionary *)userInfo deliverImmediately:(BOOL)deliverImmediately;
// All other posting methods are covers of this one.  The deliverImmediately argument causes the notification to be received in the same manner as if matching registrants had registered with suspension
// behavior NSNotificationSuspensionBehaviorDeliverImmediately.  The default in covers is deliverImmediately = NO (respect suspension behavior of registrants).

#if MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED

enum {
    NSNotificationDeliverImmediately = (1 << 0),
    NSNotificationPostToAllSessions = (1 << 1)
};

- (void)postNotificationName:(NSString *)name object:(NSString *)object userInfo:(NSDictionary *)userInfo options:(unsigned)options;

#endif

- (void)setSuspended:(BOOL)suspended;
    // Called with suspended = YES, enables the variety of suspension behaviors enumerated above.  Called with suspended = NO disables them (immediate delivery of notifications is resumed).

- (BOOL)suspended;

// Methods from NSNotificationCenter that are re-declared in part because the anObject argument is typed to be an NSString.
- (void)addObserver:(id)observer selector:(SEL)aSelector name:(NSString *)aName object:(NSString *)anObject;

- (void)postNotificationName:(NSString *)aName object:(NSString *)anObject;
- (void)postNotificationName:(NSString *)aName object:(NSString *)anObject userInfo:(NSDictionary *)aUserInfo;
- (void)removeObserver:(id)observer name:(NSString *)aName object:(NSString *)anObject;

@end
