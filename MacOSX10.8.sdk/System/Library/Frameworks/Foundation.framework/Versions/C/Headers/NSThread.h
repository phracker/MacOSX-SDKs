/*	NSThread.h
	Copyright (c) 1994-2012, Apple Inc. All rights reserved.
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

+ (double)threadPriority;
+ (BOOL)setThreadPriority:(double)p;

- (double)threadPriority NS_AVAILABLE(10_6, 4_0);
- (void)setThreadPriority:(double)p NS_AVAILABLE(10_6, 4_0);

+ (NSArray *)callStackReturnAddresses NS_AVAILABLE(10_5, 2_0);
+ (NSArray *)callStackSymbols NS_AVAILABLE(10_6, 4_0);

- (void)setName:(NSString *)n NS_AVAILABLE(10_5, 2_0);
- (NSString *)name NS_AVAILABLE(10_5, 2_0);

- (NSUInteger)stackSize NS_AVAILABLE(10_5, 2_0);
- (void)setStackSize:(NSUInteger)s NS_AVAILABLE(10_5, 2_0);

- (BOOL)isMainThread NS_AVAILABLE(10_5, 2_0);
+ (BOOL)isMainThread NS_AVAILABLE(10_5, 2_0); // reports whether current thread is main
+ (NSThread *)mainThread NS_AVAILABLE(10_5, 2_0);

- (id)init NS_AVAILABLE(10_5, 2_0);	// designated initializer
- (id)initWithTarget:(id)target selector:(SEL)selector object:(id)argument NS_AVAILABLE(10_5, 2_0);

- (BOOL)isExecuting NS_AVAILABLE(10_5, 2_0);
- (BOOL)isFinished NS_AVAILABLE(10_5, 2_0);

- (BOOL)isCancelled NS_AVAILABLE(10_5, 2_0);
- (void)cancel NS_AVAILABLE(10_5, 2_0);

- (void)start NS_AVAILABLE(10_5, 2_0);

- (void)main NS_AVAILABLE(10_5, 2_0);	// thread body method

@end

FOUNDATION_EXPORT NSString * const NSWillBecomeMultiThreadedNotification;
FOUNDATION_EXPORT NSString * const NSDidBecomeSingleThreadedNotification;
FOUNDATION_EXPORT NSString * const NSThreadWillExitNotification;

@interface NSObject (NSThreadPerformAdditions)

- (void)performSelectorOnMainThread:(SEL)aSelector withObject:(id)arg waitUntilDone:(BOOL)wait modes:(NSArray *)array;
- (void)performSelectorOnMainThread:(SEL)aSelector withObject:(id)arg waitUntilDone:(BOOL)wait;
	// equivalent to the first method with kCFRunLoopCommonModes

- (void)performSelector:(SEL)aSelector onThread:(NSThread *)thr withObject:(id)arg waitUntilDone:(BOOL)wait modes:(NSArray *)array NS_AVAILABLE(10_5, 2_0);
- (void)performSelector:(SEL)aSelector onThread:(NSThread *)thr withObject:(id)arg waitUntilDone:(BOOL)wait NS_AVAILABLE(10_5, 2_0);
	// equivalent to the first method with kCFRunLoopCommonModes
- (void)performSelectorInBackground:(SEL)aSelector withObject:(id)arg NS_AVAILABLE(10_5, 2_0);

@end

