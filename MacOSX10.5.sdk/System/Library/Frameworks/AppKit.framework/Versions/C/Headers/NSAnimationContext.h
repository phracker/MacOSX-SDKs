/*
    NSAnimationContext.h
    Application Kit
    Copyright (c) 2006-2007, Apple Inc.
    All rights reserved.
*/

#import <AppKit/AppKitDefines.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

@interface NSAnimationContext : NSObject
{
    NSTimeInterval _duration;
    id _reserved[5];
}
+ (void)beginGrouping;
+ (void)endGrouping;

+ (NSAnimationContext *)currentContext;

- (void)setDuration:(NSTimeInterval)duration;
- (NSTimeInterval)duration;
@end

#endif
