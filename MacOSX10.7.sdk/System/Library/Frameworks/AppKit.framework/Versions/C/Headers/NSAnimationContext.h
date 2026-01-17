/*
    NSAnimationContext.h
    Application Kit
    Copyright (c) 2006-2011, Apple Inc.
    All rights reserved.
*/

#import <AppKit/AppKitDefines.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>

@class CAMediaTimingFunction;

NS_CLASS_AVAILABLE(10_5, NA)
@interface NSAnimationContext : NSObject
{
    NSTimeInterval _duration;
    id _reserved[5];
}
+ (void)runAnimationGroup:(void (^)(NSAnimationContext *context))changes completionHandler:(void (^)(void))completionHandler NS_AVAILABLE_MAC(10_7);

+ (void)beginGrouping;
+ (void)endGrouping;

+ (NSAnimationContext *)currentContext;

- (void)setDuration:(NSTimeInterval)duration;
- (NSTimeInterval)duration;

- (CAMediaTimingFunction *)timingFunction NS_AVAILABLE_MAC(10_7);
- (void)setTimingFunction:(CAMediaTimingFunction *)newTimingFunction NS_AVAILABLE_MAC(10_7);

#if NS_BLOCKS_AVAILABLE
- (void (^)(void))completionHandler NS_AVAILABLE_MAC(10_7);
- (void)setCompletionHandler:(void (^)(void))handler NS_AVAILABLE_MAC(10_7);
#endif

@end
