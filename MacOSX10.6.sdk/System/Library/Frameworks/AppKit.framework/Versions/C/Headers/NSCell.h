/*
	NSCell.h
	Application Kit
	Copyright (c) 1994-2009, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/NSText.h>
#import <AppKit/NSParagraphStyle.h>
#import <AppKit/NSApplication.h>

@class NSAttributedString, NSEvent, NSFont, NSFormatter, NSImage, NSMenu, NSText, NSView, NSTextView;

enum {
    NSAnyType				= 0,
    NSIntType				= 1,
    NSPositiveIntType			= 2,
    NSFloatType				= 3,
    NSPositiveFloatType			= 4,
    NSDoubleType			= 6,
    NSPositiveDoubleType		= 7
};

enum {
    NSNullCellType			= 0,
    NSTextCellType			= 1,
    NSImageCellType			= 2
};
typedef NSUInteger NSCellType;

enum {
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
};
typedef NSUInteger NSCellAttribute;

enum {
    NSNoImage				= 0,
    NSImageOnly				= 1,
    NSImageLeft				= 2,
    NSImageRight			= 3,
    NSImageBelow			= 4,
    NSImageAbove			= 5,
    NSImageOverlaps			= 6
};
typedef NSUInteger NSCellImagePosition;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
enum {
    NSImageScaleProportionallyDown = 0, // Scale image down if it is too large for destination. Preserve aspect ratio.
    NSImageScaleAxesIndependently,      // Scale each dimension to exactly fit destination. Do not preserve aspect ratio.
    NSImageScaleNone,                   // Do not scale.
    NSImageScaleProportionallyUpOrDown  // Scale image to maximum possible dimensions while (1) staying within destination area (2) preserving aspect ratio
};
#endif
typedef NSUInteger NSImageScaling;

enum {
    NSMixedState = -1,
    NSOffState   =  0,
    NSOnState    =  1    
};
typedef NSInteger NSCellStateValue;

/* ButtonCell highlightsBy and showsStateBy mask */

enum {
    NSNoCellMask			= 0,
    NSContentsCellMask			= 1,
    NSPushInCellMask			= 2,
    NSChangeGrayCellMask		= 4,
    NSChangeBackgroundCellMask		= 8
};

enum {
    NSDefaultControlTint  = 0,	// system 'default'
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
    NSBlueControlTint     = 1,
    NSGraphiteControlTint = 6,
#endif
    NSClearControlTint    = 7
};
typedef NSUInteger NSControlTint;

enum {
    NSRegularControlSize,
    NSSmallControlSize
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
    , NSMiniControlSize
#endif
};
typedef NSUInteger NSControlSize;

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
    unsigned int        cellReserved1:2;
    unsigned int        singleLineMode:1;
    unsigned int        actOnMouseDragged:1;
    unsigned int        isLoaded:1;
    unsigned int        truncateLastLine:1;
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
    unsigned int        layoutDirectionRTL:1;
    unsigned int        backgroundStyle:3;
    unsigned int        cellReserved2:4;
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
- (NSInteger)state;
- (void)setState:(NSInteger)value;
- (id)target;
- (void)setTarget:(id)anObject;
- (SEL)action;
- (void)setAction:(SEL)aSelector;
- (NSInteger)tag;
- (void)setTag:(NSInteger)anInt;
- (NSString*)title;
- (void)setTitle:(NSString*)aString;
- (BOOL)isOpaque;
- (BOOL)isEnabled;
- (void)setEnabled:(BOOL)flag;
- (NSInteger)sendActionOn:(NSInteger)mask;
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
- (BOOL)isEntryAcceptable:(NSString *)aString;
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
- (void)setControlTint:(NSControlTint)controlTint;
- (NSControlTint)controlTint;
- (void)setControlSize:(NSControlSize)size;
- (NSControlSize)controlSize;
- (id)representedObject;
- (void)setRepresentedObject:(id)anObject;
- (NSInteger)cellAttribute:(NSCellAttribute)aParameter;
- (void)setCellAttribute:(NSCellAttribute)aParameter to:(NSInteger)value;
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
- (NSInteger)mouseDownFlags;
- (void)getPeriodicDelay:(float *)delay interval:(float *)interval;
- (BOOL)startTrackingAt:(NSPoint)startPoint inView:(NSView *)controlView;
- (BOOL)continueTracking:(NSPoint)lastPoint at:(NSPoint)currentPoint inView:(NSView *)controlView;
- (void)stopTracking:(NSPoint)lastPoint at:(NSPoint)stopPoint inView:(NSView *)controlView mouseIsUp:(BOOL)flag;
- (BOOL)trackMouse:(NSEvent *)theEvent inRect:(NSRect)cellFrame ofView:(NSView *)controlView untilMouseUp:(BOOL)flag;
- (void)editWithFrame:(NSRect)aRect inView:(NSView *)controlView editor:(NSText *)textObj delegate:(id)anObject event:(NSEvent *)theEvent;
- (void)selectWithFrame:(NSRect)aRect inView:(NSView *)controlView editor:(NSText *)textObj delegate:(id)anObject start:(NSInteger)selStart length:(NSInteger)selLength;
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

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (NSInteger)integerValue;
- (void)setIntegerValue:(NSInteger)anInteger;
- (void)takeIntegerValueFrom:(id)sender;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5 */

/* Truncates and adds the ellipsis character to the last visible line if the text doesn't fit into the cell bounds. The setting is ignored if -lineBreakMode is neither NSLineBreakByWordWrapping nor NSLineBreakByCharWrapping.
 */
- (BOOL)truncatesLastVisibleLine AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)setTruncatesLastVisibleLine:(BOOL)flag AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Bi-directional User Interface. It specifies the general UI layout flow directions.
*/
- (NSUserInterfaceLayoutDirection)userInterfaceLayoutDirection AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (void)setUserInterfaceLayoutDirection:(NSUserInterfaceLayoutDirection)layoutDirection AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Returns a custom field editor for editing inside aControlView. This is an override point for NSCell subclasses designed to work with its own custom field editor. This message is sent to the selected cell of aControlView in -[NSWindow fieldEditor:forObject:]. Returning non-nil from this method indicates skipping the standard field editor querying processes including -windowWillReturnFieldEditor:toObject: delegation. The default NSCell implementation returns nil. The field editor returned from this method should have isFieldEditor == YES.
 */
- (NSTextView *)fieldEditorForView:(NSView *)aControlView AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Tells the text cell to layout/render its content in single-line. If YES, the cell ignores the return value from -wraps, interprets NSLineBreakByWordWrapping and NSLineBreakByCharWrapping from -lineBreakMode as NSLineBreakByClipping, and configures the field editor to ignore key binding commands that insert paragraph/line separators. Also, the field editor bound to a single line cell filters paragraph/line separator insertion from user actions. Cells in the single line mode use the fixed baseline layout. The text baseline position is determined solely by the control size regardless of content font style/size.
 */
- (BOOL)usesSingleLineMode AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (void)setUsesSingleLineMode:(BOOL)flag AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
@end

@interface NSCell(NSKeyboardUI)
- (void)setRefusesFirstResponder:(BOOL)flag;
- (BOOL)refusesFirstResponder;
- (BOOL)acceptsFirstResponder;
- (void)setShowsFirstResponder:(BOOL)showFR;
- (BOOL)showsFirstResponder;
- (void)setMnemonicLocation:(NSUInteger)location;
- (NSUInteger)mnemonicLocation;
- (NSString *)mnemonic;
- (void)setTitleWithMnemonic:(NSString *)stringWithAmpersand;
- (void)performClick:(id)sender;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)setFocusRingType:(NSFocusRingType)focusRingType;
- (NSFocusRingType)focusRingType;
+ (NSFocusRingType)defaultFocusRingType;
#endif
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
- (BOOL)wantsNotificationForMarkedText; // If the receiver returns YES, the field editor initiated by it posts text change notifications (i.e. NSTextDidChangeNotification) while editing marked text; otherwise, they are delayed until the marked text confirmation. The NSCell's implementation returns NO.
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2 */
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
- (NSInteger)nextState;			/* get next state state in cycle */
- (void)setNextState;			/* toggle/cycle through states */
@end

APPKIT_EXTERN NSString *NSControlTintDidChangeNotification; /* sent after user changes control tint preference */

/* Cell Hit testing support */

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

enum {
    // An empty area, or did not hit in the cell
    NSCellHitNone = 0,
    // A content area in the cell
    NSCellHitContentArea = 1 << 0,
    // An editable text area of the cell
    NSCellHitEditableTextArea = 1 << 1,
    // A trackable area in the cell
    NSCellHitTrackableArea = 1 << 2,
};

@interface NSCell(NSCellHitTest)
/* Return hit testing information for the cell. Use a bit-wise mask to look for a specific value when calling the method. Generally, this should be overridden by custom NSCell subclasses to return the correct result. Currently, it is called by some multi-cell views, such as NSTableView.

    By default, NSCell will look at the cell type and do the following:

    NSImageCellType: 
        If the image exists, and the event point is in the image return NSCellHitContentArea, else NSCellHitNone.

    NSTextCellType (also applies to NSTextFieldCell): 
        If there is text:
            If the event point hits in the text, return NSCellHitContentArea. Additionally, if the cell is enabled return NSCellHitContentArea | NSCellHitEditableTextArea.
        If there is not text:
            Returns NSCellHitNone.

    NSNullCellType (this is the default that applies to non text or image cells who don't override hitTestForEvent:):
        Return NSCellHitContentArea by default.
        If the cell not disabled, and it would track, return NSCellHitContentArea | NSCellHitTrackableArea.
*/
- (NSUInteger)hitTestForEvent:(NSEvent *)event inRect:(NSRect)cellFrame ofView:(NSView *)controlView;
@end

@interface NSCell(NSCellExpansion)
/*  Allows the cell to return an expansion cell frame if cellFrame is too small for the entire contents in the view. When the mouse is hovered over the cell in certain controls, the full cell contents will be shown in a special floating tool tip view. If the frame is not too small, return an empty rect, and no expansion tool tip view will be shown. By default, NSCell returns NSZeroRect, while some subclasses (such as NSTextFieldCell) will return the proper frame when required. 
*/
- (NSRect)expansionFrameWithFrame:(NSRect)cellFrame inView:(NSView *)view;

/* Allows the cell to perform custom expansion tool tip drawing. Note that the view may be different from the original view that the cell appeared in. By default, NSCell simply calls drawWithFrame:inView:.
*/
- (void)drawWithExpansionFrame:(NSRect)cellFrame inView:(NSView *)view;
@end

enum {
    NSBackgroundStyleLight = 0,	// The background is a light color. Dark content contrasts well with this background.
    NSBackgroundStyleDark,	// The background is a dark color. Light content contrasts well with this background.
    NSBackgroundStyleRaised,	// The background is intended to appear higher than the content drawn on it. Content might need to be inset.
    NSBackgroundStyleLowered	// The background is intended to appear lower than the content drawn on it. Content might need to be embossed.
};
typedef NSInteger NSBackgroundStyle;

@interface NSCell (NSCellBackgroundStyle)

/* Describes the surface the cell is drawn onto in -[NSCell drawWithFrame:inView:]. A control typically sets this before it asks the cell to draw. A cell may draw differently based on background characteristics. For example, a tableview drawing a cell in a selected row might call [cell setBackgroundStyle:NSBackgroundStyleDark]. A text cell might decide to render its text white as a result. A rating-style level indicator might draw its stars white instead of gray.
 */
- (NSBackgroundStyle)backgroundStyle;
- (void)setBackgroundStyle:(NSBackgroundStyle)style;


/* Describes the surface drawn onto in -[NSCell drawInteriorWithFrame:inView:]. This is often the same as the backgroundStyle, but a button that draws a bezel would have a different interiorBackgroundStyle.  
 
 This is both an override point and a useful method to call. A button that draws a custom bezel would override this to describe that surface. A cell that has custom interior drawing might query this method to help pick an image that looks good on the cell. Calling this method gives you some independence from changes in framework art style.
 */
- (NSBackgroundStyle)interiorBackgroundStyle;

@end

#endif

@interface NSCell (NSDeprecated)

enum {
    NSScaleProportionally = 0, // Deprecated. Use NSScaleProportionallyDown
    NSScaleToFit,              // Deprecated. Use NSScaleAxesIndependently
    NSScaleNone                // Deprecated. Use NSImageScaleNone
};

// Use formatters instead.  See -[NSCell formatter] and -[NSCell setFormatter:].
- (NSInteger)entryType DEPRECATED_IN_MAC_OS_X_VERSION_10_0_AND_LATER;
- (void)setEntryType:(NSInteger)aType DEPRECATED_IN_MAC_OS_X_VERSION_10_0_AND_LATER;
- (void)setFloatingPointFormat:(BOOL)autoRange left:(NSUInteger)leftDigits right:(NSUInteger)rightDigits DEPRECATED_IN_MAC_OS_X_VERSION_10_0_AND_LATER;

@end


/* Draw an image from two end caps and a fill.  The end caps are scaled proportionally to match the thickness of the destination frame.  In the horizontal case, the startCap is drawn into the left part of the destination, the endCap is drawn into the right part of the destination, and the fill is tiled over the remaining area.  The caps and the fill should all be the same height.  The vertical case is similar.  
 
 This is an appropriate way to draw the bezel of a button that can be resized in one dimension.
 */
APPKIT_EXTERN void NSDrawThreePartImage(NSRect frame, NSImage *startCap, NSImage *centerFill, NSImage *endCap, BOOL vertical, NSCompositingOperation op, CGFloat alphaFraction, BOOL flipped) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Draw an image from nine pieces.  When drawn, the destination rect is partitioned into nine rectangular regions: the corner pieces are the natural size of the corner images, the edge pieces are the natural size of the edge fill images in the direction perpendicular to the edge and flush with the corners.  The center rect fills the remaining space.  The supplied images and fills are drawn into the corresponding regions, with fill images tiled at their natural dimensions.  Images that share a border should have the same thickness in that dimension.  
 
 This method is appropriate for the bezel of a control, like a box, that can be resized in both dimensions.
 */
APPKIT_EXTERN void NSDrawNinePartImage(NSRect frame, NSImage *topLeftCorner, NSImage *topEdgeFill, NSImage *topRightCorner, NSImage *leftEdgeFill, NSImage *centerFill, NSImage *rightEdgeFill, NSImage *bottomLeftCorner, NSImage *bottomEdgeFill, NSImage *bottomRightCorner, NSCompositingOperation op, CGFloat alphaFraction, BOOL flipped) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

