/*
        NSProgressIndicator.h
        Application Kit
        Copyright (c) 1997-2017, Apple Inc.
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
    BOOL		_isBezeled;
    BOOL		_isIndeterminate;
    BOOL		_threadedAnimation;
    double		_minimum;
    double		_maximum;
    double		_value;
    unsigned int        _animationIndex;
    NSTimeInterval	_animationDelay;
    id			_timer;
    CGFloat     _drawingWidth;
    id		_roundColor;
    id          _reserved __unused;
    struct __progressIndicatorFlags {
        unsigned int isSpinning:1;
        unsigned int isVector:1;
        unsigned int isLocked:1;
        unsigned int controlTint:3;
        unsigned int controlSize:2;
	unsigned int style:1;
        unsigned int _delayedStartup:1;
 	unsigned int hideWhenStopped:1;
        unsigned int revive:1;
        unsigned int _temporarilyBlockHeartBeating:1;
        unsigned int _isHidden:1;
        unsigned int _isHeartBeatInstalled:1;
        unsigned int _customRenderer:1;
        unsigned int _lastFrame:8;
        unsigned int _isDetaching:1;
        unsigned int RESERVED:7;
    } _progressIndicatorFlags;
    id _NSProgressIndicatorReserved1 __unused;
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

/* For the spinning style, it will size the spinning arrows to their default size. For the bar style, the height will be set to the recommended height.
 */
- (void)sizeToFit;

@property (getter=isDisplayedWhenStopped) BOOL displayedWhenStopped;

@end

#pragma mark Deprecated declarations

/* These constants do not accurately represent the geometry of NSProgressIndicator.  Use `controlSize` and `sizeToFit` instead.  These declarations will be formally marked deprecated in a future release.
 */
typedef NS_ENUM(NSUInteger, NSProgressIndicatorThickness) {
    NSProgressIndicatorPreferredThickness      = 14,
    NSProgressIndicatorPreferredSmallThickness = 10,
    NSProgressIndicatorPreferredLargeThickness = 18,
    NSProgressIndicatorPreferredAquaThickness  = 12
};

/* These declarations will be formally marked deprecated in a future release.
 */
static const NSProgressIndicatorStyle NSProgressIndicatorBarStyle = NSProgressIndicatorStyleBar;
static const NSProgressIndicatorStyle NSProgressIndicatorSpinningStyle = NSProgressIndicatorStyleSpinning;

@interface NSProgressIndicator (NSProgressIndicatorDeprecated)
- (NSTimeInterval)animationDelay NS_DEPRECATED_MAC(10_0, 10_6);
- (void)setAnimationDelay:(NSTimeInterval)delay NS_DEPRECATED_MAC(10_0, 10_6);
- (void)animate:(nullable id)sender NS_DEPRECATED_MAC(10_0, 10_6);
@end

NS_ASSUME_NONNULL_END
