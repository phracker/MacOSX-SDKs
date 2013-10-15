/*	NSDistributedLock.h
	Copyright (c) 1995-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSDate;

@interface NSDistributedLock : NSObject {
@private
    void *_priv;
}

+ (NSDistributedLock *)lockWithPath:(NSString *)path;  

- (id)initWithPath:(NSString *)path;

- (BOOL)tryLock;
- (void)unlock;
- (void)breakLock;
- (NSDate *)lockDate;

@end

