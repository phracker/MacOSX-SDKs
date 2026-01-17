/*	NSLock.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSDate;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@protocol NSLocking

- (void)lock NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");

- (void)unlock NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");

@end

NS_SWIFT_SENDABLE // Locks are inherently Sendable by definition
@interface NSLock : NSObject <NSLocking>

#if !0
- (BOOL)tryLock NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");

- (BOOL)lockBeforeDate:(NSDate *)limit NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");
#endif 

@property (nullable, copy) NSString *name API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

@end

#if !0
NS_SWIFT_SENDABLE // Locks are inherently Sendable by definition
@interface NSConditionLock : NSObject <NSLocking>

- (instancetype)initWithCondition:(NSInteger)condition NS_DESIGNATED_INITIALIZER;

@property (readonly) NSInteger condition;
- (void)lockWhenCondition:(NSInteger)condition NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");

- (BOOL)tryLock NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");

- (BOOL)tryLockWhenCondition:(NSInteger)condition NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");

- (void)unlockWithCondition:(NSInteger)condition NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");

- (BOOL)lockBeforeDate:(NSDate *)limit NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");

- (BOOL)lockWhenCondition:(NSInteger)condition beforeDate:(NSDate *)limit NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");

@property (nullable, copy) NSString *name API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

@end

NS_SWIFT_SENDABLE // Locks are inherently Sendable by definition
@interface NSRecursiveLock : NSObject <NSLocking>

- (BOOL)tryLock NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");

- (BOOL)lockBeforeDate:(NSDate *)limit NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");

@property (nullable, copy) NSString *name API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

@end


NS_SWIFT_SENDABLE // Locks are inherently Sendable by definition
API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0))
@interface NSCondition : NSObject <NSLocking>

- (void)wait NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");

- (BOOL)waitUntilDate:(NSDate *)limit NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");

- (void)signal NS_SWIFT_UNAVAILABLE_FROM_ASYNC("Use async-safe scoped locking instead");

- (void)broadcast;

@property (nullable, copy) NSString *name API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

@end
#endif 

NS_HEADER_AUDIT_END(nullability, sendability)
