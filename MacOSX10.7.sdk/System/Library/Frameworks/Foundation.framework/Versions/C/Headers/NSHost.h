/*	NSHost.h
	Copyright (c) 1994-2011, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSArray, NSMutableArray;

@interface NSHost : NSObject {
@private
    NSArray 	*names;
    NSArray 	*addresses;
    id		reserved;
}

+ (NSHost *)currentHost;
+ (NSHost *)hostWithName:(NSString *)name;
+ (NSHost *)hostWithAddress:(NSString *)address;

- (BOOL)isEqualToHost:(NSHost *)aHost;

- (NSString *)name;	// arbitrary choice
- (NSArray *)names;	// unordered list

- (NSString *)address;	// arbitrary choice
- (NSArray *)addresses;	// unordered list of IPv6 and IPv4 addresses

- (NSString *)localizedName NS_AVAILABLE(10_6, NA);

// NSHost does not implement any caching any longer
+ (void)setHostCacheEnabled:(BOOL)flag NS_DEPRECATED_MAC(10_0, 10_7);
+ (BOOL)isHostCacheEnabled NS_DEPRECATED_MAC(10_0, 10_7);
+ (void)flushHostCache NS_DEPRECATED_MAC(10_0, 10_7);
@end

