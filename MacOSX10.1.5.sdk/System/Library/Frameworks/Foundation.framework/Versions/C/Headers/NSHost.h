/*	NSHost.h
	Copyright 1994-2001, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSArray, NSMutableArray;

@interface NSHost : NSObject {
@private
    NSMutableArray 	*names;
    NSMutableArray 	*addresses;
    void		*reserved;
}

+ (NSHost *)currentHost;
+ (NSHost *)hostWithName:(NSString *)name;
+ (NSHost *)hostWithAddress:(NSString *)address;

+ (void)setHostCacheEnabled:(BOOL)flag;
+ (BOOL)isHostCacheEnabled;
+ (void)flushHostCache;

- (BOOL)isEqualToHost:(NSHost *)aHost;

- (NSString *)name;
- (NSArray *)names;

- (NSString *)address;
- (NSArray *)addresses;

@end

