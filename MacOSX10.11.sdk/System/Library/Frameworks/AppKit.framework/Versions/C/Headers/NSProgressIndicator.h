/*
        NSProgressIndicator.h
        Application Kit
        Copyright (c) 1997-2015, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSView.h>
#import <AppKit/NSCell.h>
#import <Foundation/NSDate.h>

NS_ASSUME_NONNULL_BEGIN

struct __NSProgressIndicatorThreadInfo;
typedef struct __NSProgressIndicatorThreadInfo _NSProgressIndicatorThreadInfo;

//================================================================================
//	NSprogressIndicator can support any size (for both determinate and indeterminate).
//	But to get the best result the height of a progress indicator should be as follow:
//
//           	    with bezel    without bezel
//	small		10		8	
//	regular		14		12	
//	large		18		16
//	Aqua		12		12

typedef NS_ENUM(NSUInteger, NSProgressIndicatorThickness) {
    NSProgressIndicatorPreferredThickness 	= 14,
    NSProgressIndicatorPreferredSmallThickness 	= 10,
    NSProgressIndicatorPreferredLargeThickness	= 18,
    NSProgressIndicatorPreferredAquaThickness	= 12
};

typedef NS_ENUM(NSUInteger, NSProgressIndicatorStyle) {
    NSProgressIndicatorBarStyle = 0,
    NSProgressIndicatorSpinningStyle = 1
};

//================================================================================
//	NSProgressIndicator interface
//
@interface NSProgressIndicator : NSView <NSAccessibilityProgressIndicator>
{
@private
    /* Persistent properties */
    BOOL		_isBezeled;		// has or not a 3D bezel around the progress indicator (invariant)
    BOOL		_isIndeterminate;	// YES by default
    BOOL		_threadedAnimation;
    
    double		_minimum;		// 0 by default
    double		_maximum;		// 100 by default
    
    /* Non-persistent properties */
    double		_value;			// _minimum by default
    
    unsigned int        _animationIndex;
    NSTimeInterval	_animationDelay;	// 5/60 of a seconds by default

    id			_timer;

    CGFloat     _drawingWidth;

    id		_roundColor;
    id          _reserved;

    volatile struct __progressIndicatorFlags {
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

    /* For future use */
    id _NSProgressIndicatorReserved1;
}

	/* Options */

@property (getter=isIndeterminate) BOOL indeterminate;				

@property (getter=isBezeled) BOOL bezeled;

@property NSControlTint controlTint;

@property NSControlSize controlSize;

	/* Determinate progress indicator */

@property double doubleValue;

- (void)incrementBy:(double)delta;			// equivalent to [self setDoubleValue:[self doubleValue] + delta]

@property double minValue;
@property double maxValue;

/* Indeterminate progress indicator */

@property BOOL usesThreadedAnimation;				// returns YES if the PI uses a thread instead of a timer (default in NO)

- (void)startAnimation:(nullable id)sender;
- (void)stopAnimation:(nullable id)sender;


@property NSProgressIndicatorStyle style;

// For the spinning style, it will size the spinning arrows to their default size.  
// For the bar style, the height will be set to the recommended height. 
- (void) sizeToFit;

@property (getter=isDisplayedWhenStopped) BOOL displayedWhenStopped;

@end

@interface NSProgressIndicator (NSProgressIndicatorDeprecated)
- (NSTimeInterval)animationDelay NS_DEPRECATED_MAC(10_0, 10_6);
- (void)setAnimationDelay:(NSTimeInterval)delay NS_DEPRECATED_MAC(10_0, 10_6);
- (void)animate:(nullable id)sender NS_DEPRECATED_MAC(10_0, 10_6);
@end

NS_ASSUME_NONNULL_END
