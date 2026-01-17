/*	NSGarbageCollector.h
	Copyright (c) 2006-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

NS_CLASS_DEPRECATED(10_5, 10_10, NA, NA, "Building Garbage Collected apps is no longer supported.")
NS_AUTOMATED_REFCOUNT_UNAVAILABLE

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_UNAVAILABLE("Garbage Collection is not supported")
@interface NSGarbageCollector : NSObject

+ (id)defaultCollector;

- (BOOL)isCollecting NS_DEPRECATED(10_0, 10_6, NA, NA);

- (void)disable;
- (void)enable;
- (BOOL)isEnabled;

- (void)collectIfNeeded;
- (void)collectExhaustively;

- (void)disableCollectorForPointer:(const void *)ptr;
- (void)enableCollectorForPointer:(const void *)ptr;

- (NSZone *)zone;

@end

NS_ASSUME_NONNULL_END
