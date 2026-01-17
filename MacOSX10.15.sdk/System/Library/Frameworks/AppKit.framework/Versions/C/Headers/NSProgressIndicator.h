/*
        NSProgressIndicator.h
        Application Kit
        Copyright (c) 1997-2019, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSView.h>
#import <AppKit/NSCell.h>
#import <Foundation/NSDate.h>

NS_ASSUME_NONNULL_BEGIN
API_UNAVAILABLE_BEGIN(ios)

typedef NS_ENUM(NSUInteger, NSProgressIndicatorStyle) {
    NSProgressIndicatorStyleBar = 0,
    NSProgressIndicatorStyleSpinning = 1
};

@interface NSProgressIndicator : NSView <NSAccessibilityProgressIndicator>

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
} API_DEPRECATED("", macos(10.0,10.14));

/* Please instead use the more modern versions of these constants.
 */
static const NSProgressIndicatorStyle NSProgressIndicatorBarStyle API_DEPRECATED_WITH_REPLACEMENT("NSProgressIndicatorStyleBar", macos(10.2,10.14)) = NSProgressIndicatorStyleBar;
static const NSProgressIndicatorStyle NSProgressIndicatorSpinningStyle API_DEPRECATED_WITH_REPLACEMENT("NSProgressIndicatorStyleSpinning", macos(10.2,10.14)) = NSProgressIndicatorStyleSpinning;

@interface NSProgressIndicator (NSProgressIndicatorDeprecated)
- (NSTimeInterval)animationDelay API_DEPRECATED("", macos(10.0,10.6));
- (void)setAnimationDelay:(NSTimeInterval)delay API_DEPRECATED("", macos(10.0,10.6));
- (void)animate:(nullable id)sender API_DEPRECATED("", macos(10.0,10.6));
@end

API_UNAVAILABLE_END
NS_ASSUME_NONNULL_END
