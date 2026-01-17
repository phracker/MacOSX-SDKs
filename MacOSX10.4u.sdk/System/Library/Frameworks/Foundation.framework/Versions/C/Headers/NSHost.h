/*	NSHost.h
	Copyright (c) 1994-2005, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSArray, NSMutableArray;

@interface NSHost : NSObject {
@private
    NSArray 	*names;
    NSArray 	*addresses;
    void	*reserved;
}

+ (NSHost *)currentHost;
+ (NSHost *)hostWithName:(NSString *)name;
+ (NSHost *)hostWithAddress:(NSString *)address;

// NSHost does not implement any caching any longer
+ (void)setHostCacheEnabled:(BOOL)flag;
+ (BOOL)isHostCacheEnabled;
+ (void)flushHostCache;

- (BOOL)isEqualToHost:(NSHost *)aHost;

- (NSString *)name;	// arbitrary choice
- (NSArray *)names;	// unordered list

- (NSString *)address;	// arbitrary choice
- (NSArray *)addresses;	// unordered list of IPv6 and IPv4 addresses

@end

