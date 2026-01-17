/* CoreAnimation - CAMetalDisplayLink.h

   Copyright (c) 2023-2025, Apple Inc.
   All rights reserved. */

#ifdef __OBJC__

#if __has_include(<Metal/MTLDrawable.h>)

#import <QuartzCore/CABase.h>
#import <QuartzCore/CAFrameRateRange.h>
#import <QuartzCore/CAMetalLayer.h>
#import <Foundation/NSObject.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class CAMetalDisplayLink;

API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
CF_SWIFT_NAME(CAMetalDisplayLink.Update)
@interface CAMetalDisplayLinkUpdate : NSObject
@property(readonly, nonatomic) id<CAMetalDrawable> drawable;
@property(readonly, nonatomic) CFTimeInterval targetTimestamp;
@property(readonly, nonatomic) CFTimeInterval targetPresentationTimestamp;
@end

API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@protocol CAMetalDisplayLinkDelegate
- (void)metalDisplayLink:(CAMetalDisplayLink *)link needsUpdate:(CAMetalDisplayLinkUpdate *)update;
@end

API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface CAMetalDisplayLink : NSObject

- (instancetype)initWithMetalLayer:(CAMetalLayer *)layer;

- (void)addToRunLoop:(NSRunLoop *)runloop forMode:(NSRunLoopMode)mode;

- (void)removeFromRunLoop:(NSRunLoop *)runloop forMode:(NSRunLoopMode)mode;

- (void)invalidate;

@property(nonatomic, weak, nullable) id<CAMetalDisplayLinkDelegate> delegate;

@property(nonatomic) float preferredFrameLatency;

@property(nonatomic) CAFrameRateRange preferredFrameRateRange;

@property(getter=isPaused, nonatomic) BOOL paused;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#endif /* __has_include(<Metal/MTLDrawable.h>) */

#endif /* __OBJC__ */
