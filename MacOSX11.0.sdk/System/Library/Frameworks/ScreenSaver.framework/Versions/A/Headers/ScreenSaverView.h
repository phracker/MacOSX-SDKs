/*
	ScreenSaverView.h
	ScreenSaver
	Copyright (c) 2000-2020, Apple Inc.
	All rights reserved.
*/

#import <AppKit/AppKit.h>

API_UNAVAILABLE_BEGIN(ios, tvos, watchos)

#include <stdlib.h>
#include <limits.h>

@interface ScreenSaverView : NSView
{
@private
    NSTimer *_animationTimer;
    NSTimeInterval _timeInterval;
    BOOL _isPreview;
    void *_reserved1;
    void *_reserved2;
    void *_reserved3;
}

+ (NSBackingStoreType)backingStoreType;
+ (BOOL)performGammaFade;

- (nullable instancetype)initWithFrame:(NSRect)frame isPreview:(BOOL)isPreview NS_DESIGNATED_INITIALIZER;

@property (NS_NONATOMIC_IOSONLY) NSTimeInterval animationTimeInterval;

- (void)startAnimation;
- (void)stopAnimation;
@property (NS_NONATOMIC_IOSONLY, getter=isAnimating, readonly) BOOL animating;

- (void)drawRect:(NSRect)rect;
- (void)animateOneFrame;

@property (readonly) BOOL hasConfigureSheet;
@property (readonly, strong) NSWindow * _Nullable configureSheet;

@property (NS_NONATOMIC_IOSONLY, getter=isPreview, readonly) BOOL preview;

@end

static __inline__ int SSRandomIntBetween(int a, int b)
{
    int range = b - a < 0 ? b - a - 1 : b - a + 1;
    int value = (int)(range * ((float) random() / (float) RAND_MAX));
    return value == range ? a : a + value;
}

static __inline__ CGFloat SSRandomFloatBetween(CGFloat a, CGFloat b)
{
    return a + (b - a) * ((CGFloat) random() / (CGFloat) RAND_MAX);
}

static __inline__ NSPoint SSRandomPointForSizeWithinRect(NSSize size, NSRect rect)
{
    return NSMakePoint (
                SSRandomFloatBetween(rect.origin.x, (rect.origin.x + rect.size.width - size.width)), 
                SSRandomFloatBetween(rect.origin.y, (rect.origin.y + rect.size.height - size.height)));
}

static __inline__ NSRect SSCenteredRectInRect(NSRect innerRect, NSRect outerRect)
{
#if CGFLOAT_IS_DOUBLE
    innerRect.origin.x = outerRect.origin.x + floor((outerRect.size.width - innerRect.size.width) / 2);
    innerRect.origin.y = outerRect.origin.y + floor((outerRect.size.height - innerRect.size.height) / 2);
#else
    innerRect.origin.x = outerRect.origin.x + floorf((outerRect.size.width - innerRect.size.width) / 2);
    innerRect.origin.y = outerRect.origin.y + floorf((outerRect.size.height - innerRect.size.height) / 2);
#endif
    return innerRect;
}

API_UNAVAILABLE_END
