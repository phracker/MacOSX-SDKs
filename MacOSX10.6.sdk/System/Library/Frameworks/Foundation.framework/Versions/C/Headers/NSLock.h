/*	NSLock.h
	Copyright (c) 1994-2009, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSDate;
	
@protocol NSLocking

- (void)lock;
- (void)unlock;

@end

@interface NSLock : NSObject <NSLocking> {
@private
    void *_priv;
}

- (BOOL)tryLock;
- (BOOL)lockBeforeDate:(NSDate *)limit;

- (void)setName:(NSString *)n AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (NSString *)name AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

@end

@interface NSConditionLock : NSObject <NSLocking> {
@private
    void *_priv;
}

- (id)initWithCondition:(NSInteger)condition;

- (NSInteger)condition;
- (void)lockWhenCondition:(NSInteger)condition;
- (BOOL)tryLock;
- (BOOL)tryLockWhenCondition:(NSInteger)condition;
- (void)unlockWithCondition:(NSInteger)condition;
- (BOOL)lockBeforeDate:(NSDate *)limit;
- (BOOL)lockWhenCondition:(NSInteger)condition beforeDate:(NSDate *)limit;

- (void)setName:(NSString *)n AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (NSString *)name AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

@end

@interface NSRecursiveLock : NSObject <NSLocking> {
@private
    void *_priv;
}

- (BOOL)tryLock;
- (BOOL)lockBeforeDate:(NSDate *)limit;

- (void)setName:(NSString *)n AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (NSString *)name AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

@end


#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED

@interface NSCondition : NSObject <NSLocking> {
@private
    void *_priv;
}

- (void)wait;
- (BOOL)waitUntilDate:(NSDate *)limit;
- (void)signal;
- (void)broadcast;

- (void)setName:(NSString *)n AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (NSString *)name AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

@end

#endif

