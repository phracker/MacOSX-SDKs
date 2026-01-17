/*	NSLock.h
	Copyright (c) 1994-2005, Apple, Inc. All rights reserved.
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

@end

@interface NSConditionLock : NSObject <NSLocking> {
@private
    void *_priv;
}

- (id)initWithCondition:(int)condition;

- (int)condition;
- (void)lockWhenCondition:(int)condition;
- (BOOL)tryLock;
- (BOOL)tryLockWhenCondition:(int)condition;
- (void)unlockWithCondition:(int)condition;
- (BOOL)lockBeforeDate:(NSDate *)limit;
- (BOOL)lockWhenCondition:(int)condition beforeDate:(NSDate *)limit;

@end

@interface NSRecursiveLock : NSObject <NSLocking> {
@private
    void *_priv;
}

- (BOOL)tryLock;
- (BOOL)lockBeforeDate:(NSDate *)limit;

@end
