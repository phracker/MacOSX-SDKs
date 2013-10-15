/*
        NSProgressIndicator.h
        Application Kit
        Copyright (c) 1997-2005, Apple Computer, Inc.
        All rights reserved.
*/

#import <AppKit/NSView.h>
#import <AppKit/NSCell.h>
#import <Foundation/NSDate.h>

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

typedef enum _NSProgressIndicatorThickness {
    NSProgressIndicatorPreferredThickness 	= 14,
    NSProgressIndicatorPreferredSmallThickness 	= 10,
    NSProgressIndicatorPreferredLargeThickness	= 18,
    NSProgressIndicatorPreferredAquaThickness	= 12
} NSProgressIndicatorThickness;


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
typedef enum _NSProgressIndicatorStyle {
    NSProgressIndicatorBarStyle = 0,
    NSProgressIndicatorSpinningStyle = 1
} NSProgressIndicatorStyle;
#endif

//================================================================================
//	NSProgressIndicator interface
//
@interface NSProgressIndicator : NSView
{
@private
    /* Persitent properties */
    BOOL		_isBezeled;		// has or not a 3D bezel around the progress indicator (invariant)
    BOOL		_isIndeterminate;	// YES by default
    BOOL		_threadedAnimation;
    
    double		_minimum;		// 0 by default
    double		_maximum;		// 100 by default
    
    /* Non-persitent properties */
    double		_value;			// _minimum by default
    
    int			_animationIndex;
    NSTimeInterval	_animationDelay;	// 5/60 of a seconds by default

    id			_timer;

    id			_animationThreadLock;
    
    id		_cachedImage;
    id		_cachedImageLock;

    volatile struct __progressIndicatorFlags {
        unsigned int isSpinning:1;
        unsigned int isVector:1;
        unsigned int isLocked:1;
        unsigned int controlTint:3;
        unsigned int controlSize:2;
	unsigned int style:1;
        unsigned int _delayedStartup:1;
        unsigned int _orderOutForResize:1;
        unsigned int _lastImageIndex:4;
 	unsigned int hideWhenStopped:1;
        unsigned int RESERVED:16;
    } _progressIndicatorFlags;

    /* For future use */
    void		*_NSProgressIndicatorReserved1;
}

	/* Options */

- (BOOL)isIndeterminate;				
- (void)setIndeterminate:(BOOL)flag;

- (BOOL)isBezeled;
- (void)setBezeled:(BOOL)flag;

- (NSControlTint)controlTint;
- (void)setControlTint:(NSControlTint)tint;

- (NSControlSize)controlSize;
- (void)setControlSize:(NSControlSize)size;

	/* Determinate progress indicator */

- (double)doubleValue;
- (void)setDoubleValue:(double)doubleValue;

- (void)incrementBy:(double)delta;			// equivalent to [self setDoubleValue:[self doubleValue] + delta]

- (double)minValue;
- (double)maxValue;
- (void)setMinValue:(double)newMinimum;
- (void)setMaxValue:(double)newMaximum;

	/* Indeterminate progress indicator */

- (NSTimeInterval)animationDelay;			// in seconds
- (void)setAnimationDelay:(NSTimeInterval)delay;	// in seconds

- (BOOL)usesThreadedAnimation;				// returns YES if the PI uses a thread instead of a timer (default in NO)
- (void)setUsesThreadedAnimation:(BOOL)threadedAnimation;

- (void)startAnimation:(id)sender;
- (void)stopAnimation:(id)sender;

- (void)animate:(id)sender;				// manual animation


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
- (void) setStyle: (NSProgressIndicatorStyle) style;
- (NSProgressIndicatorStyle) style;

// For the spinning style, it will size the spinning arrows to their default size.  
// For the bar style, the height will be set to the recommended height. 
- (void) sizeToFit;

- (BOOL) isDisplayedWhenStopped;
- (void) setDisplayedWhenStopped: (BOOL) isDisplayed;
#endif

@end
