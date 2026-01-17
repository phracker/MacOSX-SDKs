/*
        NSProgressIndicator.h
        Application Kit
        Copyright (c) 1997-2018, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSView.h>
#import <AppKit/NSCell.h>
#import <Foundation/NSDate.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, NSProgressIndicatorStyle) {
    NSProgressIndicatorStyleBar = 0,
    NSProgressIndicatorStyleSpinning = 1
};

@interface NSProgressIndicator : NSView <NSAccessibilityProgressIndicator> {
@private
    BOOL _isBezeled APPKIT_IVAR;
    BOOL _isIndeterminate APPKIT_IVAR;
    BOOL _threadedAnimation APPKIT_IVAR;
    double _minimum APPKIT_IVAR;
    double _maximum APPKIT_IVAR;
    double _value APPKIT_IVAR;
    unsigned int _animationIndex APPKIT_IVAR;
    NSTimeInterval _animationDelay APPKIT_IVAR;
    id<NSObject> _windowOcclusionChangedNotificationToken APPKIT_IVAR;
    CGFloat _drawingWidth APPKIT_IVAR;
    id _roundColor APPKIT_IVAR;
    id<NSObject> _systemColorsChangedNotificationToken APPKIT_IVAR;
    struct {
        unsigned int isSpinning:1;
        unsigned int isVector:1;
        unsigned int controlTint:3;
        unsigned int spinningTint:2;
        unsigned int controlSize:2;
        unsigned int style:1;
        unsigned int delayedStartup:1;
        unsigned int hideWhenStopped:1;
        unsigned int isHidden:1;
        unsigned int isHeartBeatInstalled:1;
        unsigned int customRenderer:1;
        unsigned int RESERVED:17;
    } _progressIndicatorFlags APPKIT_IVAR;
    id _NSProgressIndicatorReserved1 __unused APPKIT_IVAR;
}

#pragma mark Options

@property (getter=isIndeterminate) BOOL indeterminate;

@property (getter=isBezeled) BOOL bezeled;

@property NSControlTint controlTint;

@property NSControlSize controlSize;

#pragma mark Determinate progress indicator

@property double doubleValue;

/* Equivalent to [self setDoubleValue:[self doubleValue] + delta].
 */
- (void)incrementBy:(double)delta;

@property double minValue;
@property double maxValue;

#pragma mark Indeterminate progress indicator

/* YES if the NSProgressIndicator uses a thread instead of a timer (defaults to NO).
 */
@property BOOL usesThreadedAnimation;

- (void)startAnimation:(nullable id)sender;
- (void)stopAnimation:(nullable id)sender;

@property NSProgressIndicatorStyle style;

/* For the spinning style, it will size the view to its default size.  For the bar style, the height will be set to the recommended height.
 */
- (void)sizeToFit;

@property (getter=isDisplayedWhenStopped) BOOL displayedWhenStopped;

@end

#pragma mark Deprecated declarations

/* These constants do not accurately represent the geometry of NSProgressIndicator.  Use `controlSize` and `sizeToFit` instead.
 */
typedef NS_ENUM(NSUInteger, NSProgressIndicatorThickness) {
    NSProgressIndicatorPreferredThickness      = 14,
    NSProgressIndicatorPreferredSmallThickness = 10,
    NSProgressIndicatorPreferredLargeThickness = 18,
    NSProgressIndicatorPreferredAquaThickness  = 12
} NS_DEPRECATED_MAC(10_0, 10_14);

/* Please instead use the more modern versions of these constants.
 */
static const NSProgressIndicatorStyle NSProgressIndicatorBarStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSProgressIndicatorStyleBar", 10_2, 10_14) = NSProgressIndicatorStyleBar;
static const NSProgressIndicatorStyle NSProgressIndicatorSpinningStyle NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSProgressIndicatorStyleSpinning", 10_2, 10_14) = NSProgressIndicatorStyleSpinning;

@interface NSProgressIndicator (NSProgressIndicatorDeprecated)
- (NSTimeInterval)animationDelay NS_DEPRECATED_MAC(10_0, 10_6);
- (void)setAnimationDelay:(NSTimeInterval)delay NS_DEPRECATED_MAC(10_0, 10_6);
- (void)animate:(nullable id)sender NS_DEPRECATED_MAC(10_0, 10_6);
@end

NS_ASSUME_NONNULL_END
