/*	NSNull.h
	Copyright (c) 1994-2017, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSNull : NSObject <NSCopying, NSSecureCoding>

+ (NSNull *)null;

@end

NS_ASSUME_NONNULL_END
