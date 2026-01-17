/*
	NSScroller.h
	Application Kit
	Copyright (c) 1994-2015, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/NSCell.h>

/* deprecated in 10.7; this enum is no longer needed */
NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, NSScrollArrowPosition) {
    NSScrollerArrowsMaxEnd		= 0,	/* previously deprecated */
    NSScrollerArrowsMinEnd		= 1,	/* previously deprecated */
    NSScrollerArrowsDefaultSetting	= 0,
    NSScrollerArrowsNone	       	= 2
};

typedef NS_ENUM(NSUInteger, NSUsableScrollerParts) {
    NSNoScrollerParts			= 0,
    NSOnlyScrollerArrows		= 1,    /* deprecated in 10.7 */
    NSAllScrollerParts			= 2
};

typedef NS_ENUM(NSUInteger, NSScrollerPart) {
    NSScrollerNoPart			= 0,
    NSScrollerDecrementPage		= 1,
    NSScrollerKnob			= 2,
    NSScrollerIncrementPage		= 3,
    NSScrollerDecrementLine    		= 4,    /* deprecated in 10.7 */
    NSScrollerIncrementLine	 	= 5,    /* deprecated in 10.7 */
    NSScrollerKnobSlot			= 6
};

/* deprecated in 10.7; this enum is no longer needed */
typedef NS_ENUM(NSUInteger, NSScrollerArrow) {
    NSScrollerIncrementArrow		= 0,
    NSScrollerDecrementArrow		= 1
};

typedef NS_ENUM(NSInteger, NSScrollerStyle) {
    NSScrollerStyleLegacy       = 0,
    NSScrollerStyleOverlay      = 1
} NS_ENUM_AVAILABLE_MAC(10_7);

typedef NS_ENUM(NSInteger, NSScrollerKnobStyle) {
    NSScrollerKnobStyleDefault  = 0,    // dark with light border; good against any background
    NSScrollerKnobStyleDark     = 1,    // dark; good against a light background
    NSScrollerKnobStyleLight    = 2     // light; good against a dark background
} NS_ENUM_AVAILABLE_MAC(10_7);

@interface NSScroller : NSControl
{
    /*All instance variables are private*/
    CGFloat _curValue;
    CGFloat _percent;
    CGFloat _knobSize;
    struct __sFlags2 {
        unsigned int hitPart:4;
        unsigned int controlSize:2;
        unsigned int inMaxEnd:1;
        unsigned int setFloatValueOverridden:1;
        unsigned int setFloatValueKnobProportionOverridden:1;
        unsigned int style:1;
        unsigned int styleCompatibility:1;
        unsigned int overlayScrollerState:2;
        unsigned int knobStyle:2;
        unsigned int sbPaused:1;
        unsigned int isAnimatingKnob:1;
        unsigned int isTrackingMouse:1;
        unsigned int reserved:14;
    } _sFlags2;
    id _reserved;
    SEL _reserved2;
    struct _sFlags {
        unsigned int            isHoriz:1;
        NSScrollArrowPosition   arrowsLoc:2;
        NSUsableScrollerParts   partsUsable:2;
        unsigned int            fine:1;
        unsigned int            needsEnableFlush:1;
        unsigned int            thumbing:1;
        unsigned int            slotDrawn:1;
        unsigned int            knobDrawn:1;
        unsigned int            lit:1;
        unsigned int            knobLit:1;
        unsigned int            reserved:1;
        unsigned int            controlTint:3;
        unsigned int            repeatCount:16;
    } sFlags;
}

/* A subclass of NSScroller can override this method to certify that its customizations are compatible with 10.7's new iOS-like "Overlay" scroller style and behaviors.  By default, AppKit assumes that instances of NSScroller subclasses may not be compatible with the way that Overlay scrollers are presented, and falls back to the more compatible 10.6-like scroller metrics and behavior for subclassed scrollers.  The recommended override technique for a subclass "MyCustomScroller" that wants to delcare itself compatible with Overlay scroller presentation is:

    @implementation MyCustomScroller
    ...
    + (BOOL)isCompatibleWithOverlayScrollers {
        return self == [MyCustomScroller class];
    }

In this way, compatibility will be properly assessed for both "MyCustomScroller", and for potentially unknown subclasses thereof.

When it opts in in this manner, an NSScroller subclass certifies that:
- It performs any appearance customization by overriding the parts-drawing methods -drawKnob and -drawKnobSlotInRect:highlight:, and not by overriding -drawRect: wholesale.  (This is necessary to allow for separate knob and track fade in/out.  AppKit automatically applies the necessary fade alpha to whatever is drawn by -drawKnob and -drawKnobSlotInRect:highlight:.)
- It likewise performs any event-handling customization by overriding the parts-based methods -testPart: and -trackKnob:, and not by overriding -mouseDown: wholesale.
- It can deal with the fact that scroller arrows no longer exist, and -rectForPart: returns empty rects for them.
- It can accommodate the potentially different size and layout metrics used by Overlay scrollers.
*/
+ (BOOL)isCompatibleWithOverlayScrollers NS_AVAILABLE_MAC(10_7);

/* Returns the with for scrollers of the receiving class, given the specified controlSize and scrollerStyle.  This method should be used in preference to +scrollerWidthForControlSize:, which assumes a scrollerStyle of NSScrollerStyleLegacy, and +scrollerWidth:, which assumes that and a controlSize of NSRegularControlSize.
*/
+ (CGFloat)scrollerWidthForControlSize:(NSControlSize)controlSize scrollerStyle:(NSScrollerStyle)scrollerStyle NS_AVAILABLE_MAC(10_7);

/* Returns the with for scrollers of the receiving class, given the specified controlSize and assuming a scrollerStyle of NSScrollerStyleLegacy.  This method should be considered deprecated; use +scrollerWidthForControlSize:scrollerStyle: instead.
*/
+ (CGFloat)scrollerWidthForControlSize:(NSControlSize)controlSize NS_DEPRECATED_MAC(10_0, 10_7, "Use +scrollerWidthForControlSize:scrollerStyle: instead");

/* Returns the width for scrollers of the receiving class, assuming a controlSize NSRegularControlSize, and a scrollerStyle of NSScrollerStyleLegacy.  This method should be considered deprecated; use +scrollerWidthForControlSize:scrollerStyle: instead.
*/
+ (CGFloat)scrollerWidth NS_DEPRECATED_MAC(10_0, 10_7, "Use +scrollerWidthForControlSize:scrollerStyle: instead");

/* Returns the style of scrollers that applications should use wherever possible.  This value is determined by the Appearance preference panel's "Show scroll bars" setting for the current user, and -- when the user's prefernce is set to "Automatically based on input device" -- by the set of built-in and connected pointing devices and the user's scroll capability preference settings for them.  The preferredScrollerStyle will therefore change over time, and applications should be prepared to adapt their user interfaces to the new scroller style if needed.  In most cases, the updating is automatic: When the preferredScrollerStyle changes, AppKit notifies all NSScrollView instances, sending -setScrollerStyle: to each with the new style, which causees each NSScrollView to automatically re-tile (update its layout) to adapt to the new scroller style.  Some NSScrollView instances may refuse the new scroller style setting if they cannot accommodate it for compatibility reasons (presence of accessory views or legacy scroller subclasses prevent use of Overlay scrollers), but most instances will switch to the specified new preferredScrollerStyle.  Clients that wish to be notified of changes to +preferredScrollerStyle's return value can subscribe to NSPreferredScrollerStyleDidChangeNotification (declared below).
*/
+ (NSScrollerStyle)preferredScrollerStyle NS_AVAILABLE_MAC(10_7);

/* Accessors for scroller's style.  For a scroller that's managed by an NSScrollView, the setter is automatically invoked by the ScrollView with the appropriate setting, according to the user's Appearance preference settings and possibly what pointing device(s) are present.
*/
@property NSScrollerStyle scrollerStyle NS_AVAILABLE_MAC(10_7);

/* Accessors for the scroller's knob style.  The value of this property does not affect Legacy scrollers.  NSScrollerKnobStyleDefault is appropriate for a wide range of content, but in some cases choosing an alternative knob style may enhance visibility of the scroller knob atop some kinds of content.
*/
@property NSScrollerKnobStyle knobStyle NS_AVAILABLE_MAC(10_7);

- (void)drawParts NS_DEPRECATED_MAC(10_0, 10_7);                    // not invoked on any OS X version
- (NSRect)rectForPart:(NSScrollerPart)partCode;
- (void)checkSpaceForParts;
@property (readonly) NSUsableScrollerParts usableParts;
@property NSScrollArrowPosition arrowsPosition;                            // has no effect on 10.7
@property NSControlTint controlTint;                                       // has no effect on 10.7
@property NSControlSize controlSize;
- (void)drawArrow:(NSScrollerArrow)whichArrow highlight:(BOOL)flag; // normally not invoked on 10.7, because -rectForPart: is empty for NSScrollerDecrementLine and NSScrollerIncrementLine
- (void)drawKnob;
- (void)drawKnobSlotInRect:(NSRect)slotRect highlight:(BOOL)flag;
- (void)highlight:(BOOL)flag;                                       // has no effect on 10.7
- (NSScrollerPart)testPart:(NSPoint)thePoint;
- (void)trackKnob:(NSEvent *)theEvent;
- (void)trackScrollButtons:(NSEvent *)theEvent;                     // not invoked on 10.7
@property (readonly) NSScrollerPart hitPart;
@property CGFloat knobProportion;
- (void)setKnobProportion:(CGFloat)proportion NS_AVAILABLE_MAC(10_5);

@end

@interface NSScroller(NSDeprecated)
/* A method that was deprecated in Mac OS 10.5. To maintain binary compatibility, AppKit will continue to invoke overrides of this method. Code that targets Mac OS 10.5 and later should use -setDoubleValue: and -setKnobProportion: instead, and eliminate any overrides of -setFloatValue:knobProportion:. Code that needs to remain compatible with Mac OS 10.4 and earlier should continue to use -setFloatValue:knobProportion:. 
*/
- (void)setFloatValue:(float)aFloat knobProportion:(CGFloat)proportion NS_DEPRECATED_MAC(10_0, 10_5);
@end

/* Posted when the preferred scroller style changes.  The notification object is private; disregard it.  Consult NSScroller's +preferredScrollerStyle method when this notification is received, or thereafter, to determine the new scroller style to use.
*/
APPKIT_EXTERN NSString * const NSPreferredScrollerStyleDidChangeNotification NS_AVAILABLE_MAC(10_7);

NS_ASSUME_NONNULL_END
