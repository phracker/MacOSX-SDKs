/*
	NSCell.h
	Application Kit
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/NSText.h>
#import <AppKit/NSParagraphStyle.h>

@class NSAttributedString, NSEvent, NSFont, NSFormatter, NSImage, NSMenu, NSText, NSView;

enum {
    NSAnyType				= 0,
    NSIntType				= 1,
    NSPositiveIntType			= 2,
    NSFloatType				= 3,
    NSPositiveFloatType			= 4,
    NSDoubleType			= 6,
    NSPositiveDoubleType		= 7
};

typedef enum _NSCellType {
    NSNullCellType			= 0,
    NSTextCellType			= 1,
    NSImageCellType			= 2
} NSCellType;

typedef enum _NSCellAttribute {
    NSCellDisabled			= 0,
    NSCellState				= 1,
    NSPushInCell			= 2,
    NSCellEditable			= 3,
    NSChangeGrayCell			= 4,
    NSCellHighlighted			= 5,
    NSCellLightsByContents		= 6,
    NSCellLightsByGray			= 7,
    NSChangeBackgroundCell		= 8,
    NSCellLightsByBackground		= 9,
    NSCellIsBordered			= 10,
    NSCellHasOverlappingImage		= 11,
    NSCellHasImageHorizontal		= 12,
    NSCellHasImageOnLeftOrBottom	= 13,
    NSCellChangesContents		= 14,
    NSCellIsInsetButton			= 15,
    NSCellAllowsMixedState		= 16
} NSCellAttribute;

typedef enum _NSCellImagePosition {
    NSNoImage				= 0,
    NSImageOnly				= 1,
    NSImageLeft				= 2,
    NSImageRight			= 3,
    NSImageBelow			= 4,
    NSImageAbove			= 5,
    NSImageOverlaps			= 6
} NSCellImagePosition;

typedef enum _NSCellState {
    NSMixedState = -1,
    NSOffState   =  0,
    NSOnState    =  1    
} NSCellStateValue;

/* ButtonCell highlightsBy and showsStateBy mask */

enum {
    NSNoCellMask			= 0,
    NSContentsCellMask			= 1,
    NSPushInCellMask			= 2,
    NSChangeGrayCellMask		= 4,
    NSChangeBackgroundCellMask		= 8
};

typedef enum _NSControlTint {
    NSDefaultControlTint  = 0,	// system 'default'
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
    NSBlueControlTint     = 1,
    NSGraphiteControlTint = 6,
#endif
    NSClearControlTint    = 7
} NSControlTint;

typedef enum _NSControlSize {
    NSRegularControlSize,
    NSSmallControlSize
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
    , NSMiniControlSize
#endif
} NSControlSize;

typedef struct __CFlags {
    unsigned int        state:1;
    unsigned int        highlighted:1;
    unsigned int        disabled:1;
    unsigned int        editable:1;
    NSCellType          type:2;
    unsigned int        vCentered:1;
    unsigned int        hCentered:1;
    unsigned int        bordered:1;
    unsigned int        bezeled:1;
    unsigned int        selectable:1;
    unsigned int        scrollable:1;
    unsigned int        continuous:1;
    unsigned int        actOnMouseDown:1;
    unsigned int        isLeaf:1;
    unsigned int        invalidObjectValue:1;
    unsigned int        invalidFont:1;
    NSLineBreakMode     lineBreakMode:3;
    unsigned int        reserved1:3;
    unsigned int        actOnMouseDragged:1;
    unsigned int        isLoaded:1;
    unsigned int        reserved2:1;
    unsigned int        dontActOnMouseUp:1;
    unsigned int        isWhite:1;
    unsigned int        useUserKeyEquivalent:1;
    unsigned int        showsFirstResponder:1;
    unsigned int	focusRingType:2;
    unsigned int        wasSelectable:1;
    unsigned int        hasInvalidObject:1;
    unsigned int        allowsEditingTextAttributes:1;
    unsigned int        importsGraphics:1;
    NSTextAlignment     alignment:3;
    unsigned int        retainCountOverMax:1;
    unsigned int        retainCount:7;
    unsigned int        refusesFirstResponder:1;
    unsigned int        needsHighlightedText:1;
    unsigned int        dontAllowsUndo:1;
    unsigned int        currentlyEditing:1;
    unsigned int	allowsMixedState:1;
    unsigned int	inMixedState:1;
    unsigned int        sendsActionOnEndEditing:1;
    unsigned int	inSendAction:1;
    unsigned int	menuWasSet:1;
    unsigned int        controlTint:3;
    unsigned int        controlSize:2;
    unsigned int	branchImageDisabled:1;
    unsigned int	drawingInRevealover:1;
    unsigned int        needsHighlightedTextHint:1;
} _CFlags;



@interface NSCell : NSObject <NSCopying, NSCoding>
{
    /*All instance variables are private*/
    id _contents;
    _CFlags _cFlags;
@private
    // This variable should *only* be accessed through the following methods:
    // setImage:, image, setFont:, and font
    id _support;
}


+ (BOOL)prefersTrackingUntilMouseUp;


- (id)initTextCell:(NSString *)aString;
- (id)initImageCell:(NSImage *)image;

- (NSView *)controlView;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (void)setControlView:(NSView*)view;
#endif
- (NSCellType)type;
- (void)setType:(NSCellType)aType;
- (int)state;
- (void)setState:(int)value;
- (id)target;
- (void)setTarget:(id)anObject;
- (SEL)action;
- (void)setAction:(SEL)aSelector;
- (int)tag;
- (void)setTag:(int)anInt;
- (NSString*)title;
- (void)setTitle:(NSString*)aString;
- (BOOL)isOpaque;
- (BOOL)isEnabled;
- (void)setEnabled:(BOOL)flag;
- (int)sendActionOn:(int)mask;
- (BOOL)isContinuous;
- (void)setContinuous:(BOOL)flag;
- (BOOL)isEditable;
- (void)setEditable:(BOOL)flag;
- (BOOL)isSelectable;
- (void)setSelectable:(BOOL)flag;
- (BOOL)isBordered;
- (void)setBordered:(BOOL)flag;
- (BOOL)isBezeled;
- (void)setBezeled:(BOOL)flag;
- (BOOL)isScrollable;
- (void)setScrollable:(BOOL)flag;	/* If YES, sets wraps to NO */
- (BOOL)isHighlighted;
- (void)setHighlighted:(BOOL)flag;
- (NSTextAlignment)alignment;
- (void)setAlignment:(NSTextAlignment)mode;
- (BOOL)wraps;
- (void)setWraps:(BOOL)flag;	/* If YES, sets scrollable to NO */
- (NSFont *)font;
- (void)setFont:(NSFont *)fontObj;
- (int)entryType;
- (void)setEntryType:(int)aType;
- (BOOL)isEntryAcceptable:(NSString *)aString;
- (void)setFloatingPointFormat:(BOOL)autoRange left:(unsigned)leftDigits right:(unsigned)rightDigits;
- (NSString *)keyEquivalent;
- (void)setFormatter:(NSFormatter *)newFormatter;
- (id)formatter;
- (id)objectValue;
- (void)setObjectValue:(id <NSCopying>)obj;
- (BOOL)hasValidObjectValue;
- (NSString *)stringValue;
- (void)setStringValue:(NSString *)aString;
- (NSComparisonResult)compare:(id)otherCell;
- (int)intValue;
- (void)setIntValue:(int)anInt;
- (float)floatValue;
- (void)setFloatValue:(float)aFloat;
- (double)doubleValue;
- (void)setDoubleValue:(double)aDouble;
- (void)takeIntValueFrom:(id)sender;
- (void)takeFloatValueFrom:(id)sender;
- (void)takeDoubleValueFrom:(id)sender;
- (void)takeStringValueFrom:(id)sender;
- (void)takeObjectValueFrom:(id)sender;
- (NSImage *)image;
- (void)setImage:(NSImage *)image;
- (void) setControlTint:(NSControlTint)controlTint;
- (NSControlTint)controlTint;
- (void)setControlSize:(NSControlSize)size;
- (NSControlSize)controlSize;
- (id)representedObject;
- (void)setRepresentedObject:(id)anObject;
- (int)cellAttribute:(NSCellAttribute)aParameter;
- (void)setCellAttribute:(NSCellAttribute)aParameter to:(int)value;
- (NSRect)imageRectForBounds:(NSRect)theRect;
- (NSRect)titleRectForBounds:(NSRect)theRect;
- (NSRect)drawingRectForBounds:(NSRect)theRect;
- (NSSize)cellSize;
- (NSSize)cellSizeForBounds:(NSRect)aRect;
- (NSColor *)highlightColorWithFrame:(NSRect)cellFrame inView:(NSView *)controlView;
- (void)calcDrawInfo:(NSRect)aRect;
- (NSText *)setUpFieldEditorAttributes:(NSText *)textObj;
- (void)drawInteriorWithFrame:(NSRect)cellFrame inView:(NSView *)controlView;
- (void)drawWithFrame:(NSRect)cellFrame inView:(NSView *)controlView;
- (void)highlight:(BOOL)flag withFrame:(NSRect)cellFrame inView:(NSView *)controlView;
- (int)mouseDownFlags;
- (void)getPeriodicDelay:(float *)delay interval:(float *)interval;
- (BOOL)startTrackingAt:(NSPoint)startPoint inView:(NSView *)controlView;
- (BOOL)continueTracking:(NSPoint)lastPoint at:(NSPoint)currentPoint inView:(NSView *)controlView;
- (void)stopTracking:(NSPoint)lastPoint at:(NSPoint)stopPoint inView:(NSView *)controlView mouseIsUp:(BOOL)flag;
- (BOOL)trackMouse:(NSEvent *)theEvent inRect:(NSRect)cellFrame ofView:(NSView *)controlView untilMouseUp:(BOOL)flag;
- (void)editWithFrame:(NSRect)aRect inView:(NSView *)controlView editor:(NSText *)textObj delegate:(id)anObject event:(NSEvent *)theEvent;
- (void)selectWithFrame:(NSRect)aRect inView:(NSView *)controlView editor:(NSText *)textObj delegate:(id)anObject start:(int)selStart length:(int)selLength;
- (void)endEditing:(NSText *)textObj;
- (void)resetCursorRect:(NSRect)cellFrame inView:(NSView *)controlView;

- (void)setMenu:(NSMenu *)aMenu;
- (NSMenu *)menu;
- (NSMenu *)menuForEvent:(NSEvent *)event inRect:(NSRect)cellFrame ofView:(NSView *)view;
+ (NSMenu *)defaultMenu;

- (void)setSendsActionOnEndEditing:(BOOL)flag;
- (BOOL)sendsActionOnEndEditing;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (NSWritingDirection)baseWritingDirection;
- (void)setBaseWritingDirection:(NSWritingDirection)writingDirection;

- (void)setLineBreakMode:(NSLineBreakMode)mode;
- (NSLineBreakMode)lineBreakMode;

- (void)setAllowsUndo:(BOOL)allowsUndo;
- (BOOL)allowsUndo;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4 */
@end

@interface NSCell(NSKeyboardUI)
- (void)setRefusesFirstResponder:(BOOL)flag;
- (BOOL)refusesFirstResponder;
- (BOOL)acceptsFirstResponder;
- (void)setShowsFirstResponder:(BOOL)showFR;
- (BOOL)showsFirstResponder;
- (void)setMnemonicLocation:(unsigned)location;
- (unsigned)mnemonicLocation;
- (NSString *)mnemonic;
- (void)setTitleWithMnemonic:(NSString *)stringWithAmpersand;
- (void)performClick:(id)sender;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)setFocusRingType:(NSFocusRingType)focusRingType;
- (NSFocusRingType)focusRingType;
+ (NSFocusRingType)defaultFocusRingType;
#endif
@end

@interface NSCell(NSCellAttributedStringMethods)
- (NSAttributedString *)attributedStringValue;
- (void)setAttributedStringValue:(NSAttributedString *)obj;
/* These methods determine whether the user can modify text attributes and import graphics in a rich cell.  Note that whatever these flags are, cells can still contain attributed text if programmatically set. */
- (BOOL)allowsEditingTextAttributes;
- (void)setAllowsEditingTextAttributes:(BOOL)flag;	/* If NO, also clears setImportsGraphics: */
- (BOOL)importsGraphics;
- (void)setImportsGraphics:(BOOL)flag;			/* If YES, also sets setAllowsEditingTextAttributes: */
@end

@interface NSCell(NSCellMixedState)
- (void)setAllowsMixedState:(BOOL)flag;	/* allow button to have mixed state value*/
- (BOOL)allowsMixedState;
- (int)nextState;			/* get next state state in cycle */
- (void)setNextState;			/* toggle/cycle through states */
@end

APPKIT_EXTERN NSString *NSControlTintDidChangeNotification; /* sent after user changes control tint preference */
