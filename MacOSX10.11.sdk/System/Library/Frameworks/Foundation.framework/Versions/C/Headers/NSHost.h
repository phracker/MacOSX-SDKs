/*	NSHost.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSArray<ObjectType>, NSMutableArray;

NS_ASSUME_NONNULL_BEGIN

@interface NSHost : NSObject {
@private
    NSArray 	*names;
    NSArray 	*addresses;
    id		reserved;
}

+ (instancetype)currentHost;
+ (instancetype)hostWithName:(nullable NSString *)name;
+ (instancetype)hostWithAddress:(NSString *)address;

- (BOOL)isEqualToHost:(NSHost *)aHost;

@property (nullable, readonly, copy) NSString *name;	// arbitrary choice
@property (readonly, copy) NSArray<NSString *> *names;	// unordered list

@property (nullable, readonly, copy) NSString *address;	// arbitrary choice
@property (readonly, copy) NSArray<NSString *> *addresses;	// unordered list of IPv6 and IPv4 addresses

@property (nullable, readonly, copy) NSString *localizedName NS_AVAILABLE(10_6, NA);

// NSHost does not implement any caching any longer
+ (void)setHostCacheEnabled:(BOOL)flag NS_DEPRECATED_MAC(10_0, 10_7);
+ (BOOL)isHostCacheEnabled NS_DEPRECATED_MAC(10_0, 10_7);
+ (void)flushHostCache NS_DEPRECATED_MAC(10_0, 10_7);
@end

NS_ASSUME_NONNULL_END
