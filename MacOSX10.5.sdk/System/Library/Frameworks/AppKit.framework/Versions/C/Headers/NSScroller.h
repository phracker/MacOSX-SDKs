/*
	NSScroller.h
	Application Kit
	Copyright (c) 1994-2007, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/NSCell.h>

enum {
    NSScrollerArrowsMaxEnd		= 0,	/* deprecated */
    NSScrollerArrowsMinEnd		= 1,	/* deprecated */
    NSScrollerArrowsDefaultSetting	= 0,
    NSScrollerArrowsNone	       	= 2
};
typedef NSUInteger NSScrollArrowPosition;

enum {
    NSNoScrollerParts			= 0,
    NSOnlyScrollerArrows		= 1,
    NSAllScrollerParts			= 2
};
typedef NSUInteger NSUsableScrollerParts;

enum {
    NSScrollerNoPart			= 0,
    NSScrollerDecrementPage		= 1,
    NSScrollerKnob			= 2,
    NSScrollerIncrementPage		= 3,
    NSScrollerDecrementLine    		= 4,
    NSScrollerIncrementLine	 	= 5,
    NSScrollerKnobSlot			= 6
};
typedef NSUInteger NSScrollerPart;

enum {
    NSScrollerIncrementArrow		= 0,
    NSScrollerDecrementArrow		= 1
};
typedef NSUInteger NSScrollerArrow;

@interface NSScroller : NSControl
{
    /*All instance variables are private*/
    CGFloat               _curValue;
    CGFloat               _percent;
    CGFloat		_knobSize;
    struct __sFlags2 {
        unsigned int   hitPart:4;
        unsigned int   controlSize:2;
        unsigned int   inMaxEnd:1;
        unsigned int   setFloatValueOverridden:1;
        unsigned int   setFloatValueKnobProportionOverridden:1;
        unsigned int   reserved:23;
    } _sFlags2;
    id                  _target;
    SEL                 _action;
    struct _sFlags {
	unsigned int		isHoriz:1;
        NSScrollArrowPosition	arrowsLoc:2;
        NSUsableScrollerParts	partsUsable:2;
	unsigned int		fine:1;
	unsigned int		needsEnableFlush:1;
	unsigned int		thumbing:1;
	unsigned int		slotDrawn:1;
	unsigned int		knobDrawn:1;
        unsigned int            lit:1;
        unsigned int            knobLit:1;
        unsigned int		reserved:1;
        unsigned int		controlTint:3;
	unsigned int		repeatCount:16;
    } sFlags;
}

+ (CGFloat)scrollerWidth;
+ (CGFloat)scrollerWidthForControlSize:(NSControlSize)controlSize;

- (void)drawParts;
- (NSRect)rectForPart:(NSScrollerPart)partCode;
- (void)checkSpaceForParts;
- (NSUsableScrollerParts)usableParts;
- (void)setArrowsPosition:(NSScrollArrowPosition)where;
- (NSScrollArrowPosition)arrowsPosition;
- (void)setControlTint:(NSControlTint)controlTint;
- (NSControlTint)controlTint;
- (void)setControlSize:(NSControlSize)controlSize;
- (NSControlSize)controlSize;
- (void)drawArrow:(NSScrollerArrow)whichArrow highlight:(BOOL)flag;
- (void)drawKnob;
- (void)drawKnobSlotInRect:(NSRect)slotRect highlight:(BOOL)flag;
- (void)highlight:(BOOL)flag;
- (NSScrollerPart)testPart:(NSPoint)thePoint;
- (void)trackKnob:(NSEvent *)theEvent;
- (void)trackScrollButtons:(NSEvent *)theEvent;
- (NSScrollerPart)hitPart;
- (CGFloat)knobProportion;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (void)setKnobProportion:(CGFloat)proportion;
#endif

@end

@interface NSScroller(NSDeprecated)
/* A method that was deprecated in Mac OS 10.5. To maintain binary compatibility, AppKit will continue to invoke overrides of this method. Code that targets Mac OS 10.5 and later should use -setDoubleValue: and -setKnobProportion: instead, and eliminate any overrides of -setFloatValue:knobProportion:. Code that needs to remain compatible with Mac OS 10.4 and earlier should continue to use -setFloatValue:knobProportion:. 
*/
- (void)setFloatValue:(float)aFloat knobProportion:(CGFloat)proportion;
@end
