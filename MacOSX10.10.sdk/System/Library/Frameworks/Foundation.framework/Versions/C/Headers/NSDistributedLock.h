/*	NSDistributedLock.h
	Copyright (c) 1995-2014, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSDate;

@interface NSDistributedLock : NSObject {
@private
    void *_priv;
}

+ (NSDistributedLock *)lockWithPath:(NSString *)path;  

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithPath:(NSString *)path NS_DESIGNATED_INITIALIZER;

- (BOOL)tryLock;
- (void)unlock;
- (void)breakLock;
@property (readonly, copy) NSDate *lockDate;

@end

