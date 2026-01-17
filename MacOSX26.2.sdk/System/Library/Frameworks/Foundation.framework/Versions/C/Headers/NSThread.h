/*	NSThread.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSNotification.h>

@class NSArray<ObjectType>, NSMutableDictionary, NSDate, NSNumber, NSString;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@interface NSThread : NSObject  {
@private
    id _private;
    uint8_t _bytes[44];
}

@property (class, readonly, strong) NSThread *currentThread NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Thread.current cannot be used from async contexts.");

+ (void)detachNewThreadWithBlock:(void (NS_SWIFT_SENDABLE ^)(void))block API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0)) NS_SWIFT_DISABLE_ASYNC;
+ (void)detachNewThreadSelector:(SEL)selector toTarget:(id)target withObject:(nullable id)argument;

+ (BOOL)isMultiThreaded;

@property (readonly, retain) NSMutableDictionary *threadDictionary;

+ (void)sleepUntilDate:(NSDate *)date NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use Task.sleep(until:clock:) instead.");

+ (void)sleepForTimeInterval:(NSTimeInterval)ti NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use Task.sleep(until:clock:) instead.");

+ (void)exit NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Threads used in asynchronous contexts cannot be explicitly exited.");

+ (double)threadPriority NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Threads used in asynchronous context cannot get priorities.");

+ (BOOL)setThreadPriority:(double)p NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Threads used in asynchronous context cannot set priorities.");

@property double threadPriority API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)); // To be deprecated; use qualityOfService below

@property NSQualityOfService qualityOfService API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0)); // read-only after the thread is started

@property (class, readonly, copy) NSArray<NSNumber *> *callStackReturnAddresses API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
@property (class, readonly, copy) NSArray<NSString *> *callStackSymbols API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

@property (nullable, copy) NSString *name API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

@property NSUInteger stackSize API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

@property (readonly) BOOL isMainThread API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

@property (class, readonly) BOOL isMainThread API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Work intended for the main actor should be marked with @MainActor"); // reports whether current thread is main
@property (class, readonly, strong) NSThread *mainThread API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

- (instancetype)init API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithTarget:(id)target selector:(SEL)selector object:(nullable id)argument API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
- (instancetype)initWithBlock:(void (NS_SWIFT_SENDABLE ^)(void))block API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

@property (readonly, getter=isExecuting) BOOL executing API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
@property (readonly, getter=isFinished) BOOL finished API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));
@property (readonly, getter=isCancelled) BOOL cancelled API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

- (void)cancel API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

- (void)start API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

- (void)main API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));	// thread body method

@end

FOUNDATION_EXPORT NSNotificationName const NSWillBecomeMultiThreadedNotification API_DEPRECATED("This notification does not protect against data races", macos(10.0, 26.0), ios(2.0, 26.0), watchos(2.0, 26.0), tvos(9.0, 26.0), visionos(1.0, 26.0));
FOUNDATION_EXPORT NSNotificationName const NSDidBecomeSingleThreadedNotification API_DEPRECATED("Programs no longer transition to single-threaded mode from threaded environments", macos(10.0, 26.0), ios(2.0, 26.0), watchos(2.0, 26.0), tvos(9.0, 26.0), visionos(1.0, 26.0));
FOUNDATION_EXPORT NSNotificationName const NSThreadWillExitNotification API_DEPRECATED("This notification does not protect against data races", macos(10.0, 26.0), ios(2.0, 26.0), watchos(2.0, 26.0), tvos(9.0, 26.0), visionos(1.0, 26.0));

@interface NSObject (NSThreadPerformAdditions)

- (void)performSelectorOnMainThread:(SEL)aSelector withObject:(nullable id)arg waitUntilDone:(BOOL)wait modes:(nullable NSArray<NSString *> *)array NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Work intended for the main actor should be marked with @MainActor");

- (void)performSelectorOnMainThread:(SEL)aSelector withObject:(nullable id)arg waitUntilDone:(BOOL)wait NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Work intended for the main actor should be marked with @MainActor");
	// equivalent to the first method with kCFRunLoopCommonModes

- (void)performSelector:(SEL)aSelector onThread:(NSThread *)thr withObject:(nullable id)arg waitUntilDone:(BOOL)wait modes:(nullable NSArray<NSString *> *)array API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Asynchronous work should be called from isolation from an actor");

- (void)performSelector:(SEL)aSelector onThread:(NSThread *)thr withObject:(nullable id)arg waitUntilDone:(BOOL)wait API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Asynchronous work should be called from isolation from an actor");
	// equivalent to the first method with kCFRunLoopCommonModes

- (void)performSelectorInBackground:(SEL)aSelector withObject:(nullable id)arg API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
