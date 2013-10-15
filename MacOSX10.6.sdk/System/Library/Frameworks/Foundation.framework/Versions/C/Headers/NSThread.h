/*	NSThread.h
	Copyright (c) 1994-2009, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>

@class NSArray, NSMutableDictionary, NSDate;

@interface NSThread : NSObject  {
@private
    id _private;
    uint8_t _bytes[44];
}

+ (NSThread *)currentThread;

+ (void)detachNewThreadSelector:(SEL)selector toTarget:(id)target withObject:(id)argument;

+ (BOOL)isMultiThreaded;

- (NSMutableDictionary *)threadDictionary;

+ (void)sleepUntilDate:(NSDate *)date;
+ (void)sleepForTimeInterval:(NSTimeInterval)ti;

+ (void)exit;

+ (double)threadPriority AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
+ (BOOL)setThreadPriority:(double)p AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED

- (double)threadPriority AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (void)setThreadPriority:(double)p AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

+ (NSArray *)callStackReturnAddresses;
+ (NSArray *)callStackSymbols AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

- (void)setName:(NSString *)n;
- (NSString *)name;

- (NSUInteger)stackSize;
- (void)setStackSize:(NSUInteger)s;

- (BOOL)isMainThread;
+ (BOOL)isMainThread; // reports whether current thread is main
+ (NSThread *)mainThread;

- (id)init;	// designated initializer
- (id)initWithTarget:(id)target selector:(SEL)selector object:(id)argument;

- (BOOL)isExecuting;
- (BOOL)isFinished;

- (BOOL)isCancelled;
- (void)cancel;

- (void)start;

- (void)main;	// thread body method

#endif

@end

FOUNDATION_EXPORT NSString * const NSWillBecomeMultiThreadedNotification;
FOUNDATION_EXPORT NSString * const NSDidBecomeSingleThreadedNotification;
FOUNDATION_EXPORT NSString * const NSThreadWillExitNotification;

@interface NSObject (NSThreadPerformAdditions)

#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (void)performSelectorOnMainThread:(SEL)aSelector withObject:(id)arg waitUntilDone:(BOOL)wait modes:(NSArray *)array;
- (void)performSelectorOnMainThread:(SEL)aSelector withObject:(id)arg waitUntilDone:(BOOL)wait;
	// equivalent to the first method with kCFRunLoopCommonModes
#endif

#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (void)performSelector:(SEL)aSelector onThread:(NSThread *)thr withObject:(id)arg waitUntilDone:(BOOL)wait modes:(NSArray *)array;
- (void)performSelector:(SEL)aSelector onThread:(NSThread *)thr withObject:(id)arg waitUntilDone:(BOOL)wait;
	// equivalent to the first method with kCFRunLoopCommonModes
- (void)performSelectorInBackground:(SEL)aSelector withObject:(id)arg;
#endif

@end

