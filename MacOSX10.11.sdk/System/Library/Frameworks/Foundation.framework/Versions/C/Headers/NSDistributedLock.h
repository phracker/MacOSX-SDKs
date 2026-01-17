/*	NSDistributedLock.h
	Copyright (c) 1995-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSDate;

NS_ASSUME_NONNULL_BEGIN

@interface NSDistributedLock : NSObject {
@private
    void *_priv;
}

+ (nullable NSDistributedLock *)lockWithPath:(NSString *)path;  

- (instancetype)init NS_UNAVAILABLE;
- (nullable instancetype)initWithPath:(NSString *)path NS_DESIGNATED_INITIALIZER;

- (BOOL)tryLock;
- (void)unlock;
- (void)breakLock;
@property (readonly, copy) NSDate *lockDate;

@end

NS_ASSUME_NONNULL_END
