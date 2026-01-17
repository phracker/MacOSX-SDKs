/*	NSDistributedLock.h
	Copyright (c) 1995-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSDate;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

NS_SWIFT_SENDABLE // Locks are inherently Sendable by definition
@interface NSDistributedLock : NSObject

+ (nullable NSDistributedLock *)lockWithPath:(NSString *)path;  

- (instancetype)init NS_UNAVAILABLE;
- (nullable instancetype)initWithPath:(NSString *)path NS_DESIGNATED_INITIALIZER;

- (BOOL)tryLock;
- (void)unlock;
- (void)breakLock;
@property (readonly, copy) NSDate *lockDate;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
