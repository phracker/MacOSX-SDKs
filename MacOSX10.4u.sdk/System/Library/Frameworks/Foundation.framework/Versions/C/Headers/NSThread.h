/*	NSThread.h
	Copyright (c) 1994-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSArray, NSMutableDictionary, NSDate;

@interface NSThread : NSObject  {
@private
    unsigned		seqNum;
    unsigned		state;
    NSMutableDictionary	*threadDictionary;
    id			runLoop;
    void		*excHandlers;
    void		*autoreleasePool;
    id			doQueue;
    id			doConversation;
    unsigned		doConversationCount;
    id			doConversationRequest;
    void		*params;
    void		*reserved;
}

+ (NSThread *)currentThread;

+ (void)detachNewThreadSelector:(SEL)selector toTarget:(id)target withObject:(id)argument;

+ (BOOL)isMultiThreaded;

- (NSMutableDictionary *)threadDictionary;

+ (void)sleepUntilDate:(NSDate *)date;

+ (void)exit;

#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
+ (double)threadPriority;
+ (BOOL)setThreadPriority:(double)priority;
#endif

@end

FOUNDATION_EXPORT NSString * const NSWillBecomeMultiThreadedNotification;
FOUNDATION_EXPORT NSString * const NSDidBecomeSingleThreadedNotification;
FOUNDATION_EXPORT NSString * const NSThreadWillExitNotification;

#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
@interface NSObject (NSMainThreadPerformAdditions)

- (void)performSelectorOnMainThread:(SEL)aSelector withObject:(id)arg waitUntilDone:(BOOL)wait modes:(NSArray *)array;
- (void)performSelectorOnMainThread:(SEL)aSelector withObject:(id)arg waitUntilDone:(BOOL)wait;
	// equivalent to the first method with kCFRunLoopCommonModes

@end
#endif

