/*
        NSProgressIndicator.h
        Application Kit
        Copyright (c) 1997-2024, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSView.h>
#import <AppKit/NSCell.h>
#import <AppKit/AppKitDefines.h>
#import <Foundation/Foundation.h>
#import <Availability.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

typedef NS_ENUM(NSUInteger, NSProgressIndicatorStyle) {
    NSProgressIndicatorStyleBar = 0,
    NSProgressIndicatorStyleSpinning = 1
};

@interface NSProgressIndicator : NSView <NSAccessibilityProgressIndicator>

#pragma mark Options

@property (getter=isIndeterminate) BOOL indeterminate;

@property NSControlSize controlSize;

#pragma mark Determinate progress indicator

@property double doubleValue;

/* Equivalent to [self setDoubleValue:[self doubleValue] + delta].
 */
- (void)incrementBy:(double)delta;

@property double minValue;
@property double maxValue;

/* When set NSProgressIndicator will update doubleValue, minValue, maxValue, and indeterminate automatically.
 */
@property (nullable, strong) NSProgress *observedProgress API_AVAILABLE(macos(14.0));

#pragma mark Indeterminate progress indicator

/* YES if the NSProgressIndicator uses a thread instead of a timer (defaults to YES).
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
    NSProgressIndicatorPreferredThickness API_DEPRECATED("These constants do not accurately represent the geometry of NSProgressIndicator.  Use `controlSize` and `sizeToFit` instead.", macos(10.0,10.14)) = 14,
    NSProgressIndicatorPreferredSmallThickness API_DEPRECATED("These constants do not accurately represent the geometry of NSProgressIndicator.  Use `controlSize` and `sizeToFit` instead.", macos(10.0,10.14)) = 10,
    NSProgressIndicatorPreferredLargeThickness API_DEPRECATED("These constants do not accurately represent the geometry of NSProgressIndicator.  Use `controlSize` and `sizeToFit` instead.", macos(10.0,10.14)) = 18,
    NSProgressIndicatorPreferredAquaThickness API_DEPRECATED("These constants do not accurately represent the geometry of NSProgressIndicator.  Use `controlSize` and `sizeToFit` instead.", macos(10.0,10.14)) = 12,
} API_DEPRECATED("These constants do not accurately represent the geometry of NSProgressIndicator.  Use `controlSize` and `sizeToFit` instead.", macos(10.0,10.14));

/* Please instead use the more modern versions of these constants.
 */
static const NSProgressIndicatorStyle NSProgressIndicatorBarStyle API_DEPRECATED_WITH_REPLACEMENT("NSProgressIndicatorStyleBar", macos(10.2,10.14)) = NSProgressIndicatorStyleBar;
static const NSProgressIndicatorStyle NSProgressIndicatorSpinningStyle API_DEPRECATED_WITH_REPLACEMENT("NSProgressIndicatorStyleSpinning", macos(10.2,10.14)) = NSProgressIndicatorStyleSpinning;

@interface NSProgressIndicator (NSProgressIndicatorDeprecated)
- (NSTimeInterval)animationDelay API_DEPRECATED("The animationDelay property does nothing.", macos(10.0,10.6));
- (void)setAnimationDelay:(NSTimeInterval)delay API_DEPRECATED("The animationDelay property does nothing.", macos(10.0,10.6));
- (void)animate:(nullable id)sender API_DEPRECATED("Use -startAnimation and -stopAnimation instead.", macos(10.0,10.6));

@property (getter=isBezeled) BOOL bezeled API_DEPRECATED("The bezeled property is not respected on 10.15 and later", macos(10.0, 14.0));
@property NSControlTint controlTint API_DEPRECATED("The controlTint property is not respected on 10.15 and later", macos(10.0, 14.0));
@end

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
