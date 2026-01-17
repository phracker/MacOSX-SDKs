/*
	NSCell.h
	Application Kit
	Copyright (c) 1994-2015, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/NSText.h>
#import <AppKit/NSParagraphStyle.h>
#import <AppKit/NSApplication.h>
#import <AppKit/NSUserInterfaceItemIdentification.h>
#import <AppKit/NSAccessibilityProtocols.h>

NS_ASSUME_NONNULL_BEGIN

@class NSAttributedString, NSEvent, NSFont, NSFormatter, NSImage, NSMenu, NSText, NSView, NSTextView, NSDraggingImageComponent;

typedef NS_ENUM(NSUInteger, NSCellType) {
    NSNullCellType			= 0,
    NSTextCellType			= 1,
    NSImageCellType			= 2
};


typedef NS_ENUM(NSUInteger, NSCellAttribute) {
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
    NSCellIsInsetButton		= 15,
    NSCellAllowsMixedState		= 16
};


typedef NS_ENUM(NSUInteger, NSCellImagePosition) {
    NSNoImage				= 0,
    NSImageOnly				= 1,
    NSImageLeft				= 2,
    NSImageRight			= 3,
    NSImageBelow			= 4,
    NSImageAbove			= 5,
    NSImageOverlaps			= 6
};


typedef NS_ENUM(NSUInteger, NSImageScaling) {
    NSImageScaleProportionallyDown = 0, // Scale image down if it is too large for destination. Preserve aspect ratio.
    NSImageScaleAxesIndependently,      // Scale each dimension to exactly fit destination. Do not preserve aspect ratio.
    NSImageScaleNone,                   // Do not scale.
    NSImageScaleProportionallyUpOrDown, // Scale image to maximum possible dimensions while (1) staying within destination area (2) preserving aspect ratio
    
    NSScaleProportionally NS_ENUM_DEPRECATED_MAC(10_0, 10_10, "Use NSImageScaleProportionallyDown instead") = 0,
    NSScaleToFit NS_ENUM_DEPRECATED_MAC(10_0, 10_10, "Use NSImageScaleAxesIndependently instead"),
    NSScaleNone NS_ENUM_DEPRECATED_MAC(10_0, 10_10, "Use NSImageScaleNone instead")
} NS_ENUM_AVAILABLE_MAC(10_5);


enum {
    NSMixedState = -1,
    NSOffState   =  0,
    NSOnState    =  1
};
typedef NSInteger NSCellStateValue;


/* ButtonCell highlightsBy and showsStateBy mask */
typedef NS_OPTIONS(NSUInteger, NSCellStyleMask) {
    NSNoCellMask			= 0,
    NSContentsCellMask			= 1,
    NSPushInCellMask			= 2,
    NSChangeGrayCellMask		= 4,
    NSChangeBackgroundCellMask		= 8
};

typedef NS_ENUM(NSUInteger, NSControlTint) {
    NSDefaultControlTint  = 0,	// system 'default'
    NSBlueControlTint     = 1,
    NSGraphiteControlTint = 6,
    NSClearControlTint    = 7
};


typedef NS_ENUM(NSUInteger, NSControlSize) {
    NSRegularControlSize,
    NSSmallControlSize, 
    NSMiniControlSize
};

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
    unsigned int        weakTargetHelperFlag:1;
    unsigned int        allowsAppearanceEffects:1;
    unsigned int        singleLineMode:1;
    unsigned int        actOnMouseDragged:1;
    unsigned int        isLoaded:1;
    unsigned int        truncateLastLine:1;
    unsigned int        dontActOnMouseUp:1;
    unsigned int        isWhite:1;
    unsigned int        useUserKeyEquivalent:1;
    unsigned int        showsFirstResponder:1;
    unsigned int        focusRingType:2;
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
    unsigned int        allowsMixedState:1;
    unsigned int        inMixedState:1;
    unsigned int        sendsActionOnEndEditing:1;
    unsigned int        inSendAction:1;
    unsigned int        menuWasSet:1;
    unsigned int        controlTint:3;
    unsigned int        controlSize:2;
    unsigned int        branchImageDisabled:1;
    unsigned int        drawingInRevealover:1;
    unsigned int        needsHighlightedTextHint:1;
} _CFlags;


@interface NSCell : NSObject <NSCopying, NSCoding, NSUserInterfaceItemIdentification, NSAccessibilityElement, NSAccessibility>
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


- (instancetype)initTextCell:(NSString *)aString;
- (instancetype)initImageCell:(nullable NSImage *)image;

@property (nullable, assign) NSView *controlView; // Must be an NSControl subclass, non-control view subclasses not allowed!
@property NSCellType type;
@property NSInteger state;
@property (nullable, weak) id target; // Target is weak for zeroing-weak compatible objects in apps linked on 10.10 or later. Otherwise the behavior of this property is 'assign'.
@property (nullable) SEL action;
@property NSInteger tag;
@property (copy) NSString *title;
@property (getter=isOpaque, readonly) BOOL opaque;
@property (getter=isEnabled) BOOL enabled;
- (NSInteger)sendActionOn:(NSInteger)mask;
@property (getter=isContinuous) BOOL continuous;
@property (getter=isEditable) BOOL editable;
@property (getter=isSelectable) BOOL selectable;
@property (getter=isBordered) BOOL bordered;
@property (getter=isBezeled) BOOL bezeled;
@property (getter=isScrollable) BOOL scrollable; /* If YES, sets wraps to NO */
@property (getter=isHighlighted) BOOL highlighted;
@property NSTextAlignment alignment;
@property BOOL wraps;    /* If YES, sets scrollable to NO */
@property (nullable, strong) NSFont *font;
@property (readonly, copy) NSString *keyEquivalent;
@property (nullable, strong) __kindof NSFormatter *formatter;
@property (nullable, copy) id /* id <NSCopying> */ objectValue;
@property (readonly) BOOL hasValidObjectValue;
@property (copy) NSString *stringValue;
- (NSComparisonResult)compare:(id)otherCell;
@property int intValue;
@property float floatValue;
@property double doubleValue;
- (void)takeIntValueFrom:(nullable id)sender;
- (void)takeFloatValueFrom:(nullable id)sender;
- (void)takeDoubleValueFrom:(nullable id)sender;
- (void)takeStringValueFrom:(nullable id)sender;
- (void)takeObjectValueFrom:(nullable id)sender;
@property (nullable, strong) NSImage *image;
@property NSControlTint controlTint;
@property NSControlSize controlSize;
@property (nullable, strong) id representedObject;
- (NSInteger)cellAttribute:(NSCellAttribute)aParameter;
- (void)setCellAttribute:(NSCellAttribute)aParameter to:(NSInteger)value;
- (NSRect)imageRectForBounds:(NSRect)theRect;
- (NSRect)titleRectForBounds:(NSRect)theRect;
- (NSRect)drawingRectForBounds:(NSRect)theRect;
@property (readonly) NSSize cellSize;
- (NSSize)cellSizeForBounds:(NSRect)aRect;
- (NSColor *)highlightColorWithFrame:(NSRect)cellFrame inView:(NSView *)controlView;
- (void)calcDrawInfo:(NSRect)aRect;
- (NSText *)setUpFieldEditorAttributes:(NSText *)textObj;
- (void)drawInteriorWithFrame:(NSRect)cellFrame inView:(NSView *)controlView;
- (void)drawWithFrame:(NSRect)cellFrame inView:(NSView *)controlView;
- (void)highlight:(BOOL)flag withFrame:(NSRect)cellFrame inView:(NSView *)controlView;
@property (readonly) NSInteger mouseDownFlags;
- (void)getPeriodicDelay:(float *)delay interval:(float *)interval;
- (BOOL)startTrackingAt:(NSPoint)startPoint inView:(NSView *)controlView;
- (BOOL)continueTracking:(NSPoint)lastPoint at:(NSPoint)currentPoint inView:(NSView *)controlView;
- (void)stopTracking:(NSPoint)lastPoint at:(NSPoint)stopPoint inView:(NSView *)controlView mouseIsUp:(BOOL)flag;
- (BOOL)trackMouse:(NSEvent *)theEvent inRect:(NSRect)cellFrame ofView:(NSView *)controlView untilMouseUp:(BOOL)flag;
- (void)editWithFrame:(NSRect)aRect inView:(NSView *)controlView editor:(NSText *)textObj delegate:(nullable id)anObject event:(NSEvent *)theEvent;
- (void)selectWithFrame:(NSRect)aRect inView:(NSView *)controlView editor:(NSText *)textObj delegate:(nullable id)anObject start:(NSInteger)selStart length:(NSInteger)selLength;
- (void)endEditing:(NSText *)textObj;
- (void)resetCursorRect:(NSRect)cellFrame inView:(NSView *)controlView;

@property (nullable, strong) NSMenu *menu;
- (nullable NSMenu *)menuForEvent:(NSEvent *)event inRect:(NSRect)cellFrame ofView:(NSView *)view;
+ (nullable NSMenu *)defaultMenu;

@property BOOL sendsActionOnEndEditing;

@property NSWritingDirection baseWritingDirection;

@property NSLineBreakMode lineBreakMode;

@property BOOL allowsUndo;

@property NSInteger integerValue NS_AVAILABLE_MAC(10_5);
- (void)takeIntegerValueFrom:(nullable id)sender NS_AVAILABLE_MAC(10_5);

/* Truncates and adds the ellipsis character to the last visible line if the text doesn't fit into the cell bounds. The setting is ignored if -lineBreakMode is neither NSLineBreakByWordWrapping nor NSLineBreakByCharWrapping.
 */
@property BOOL truncatesLastVisibleLine NS_AVAILABLE_MAC(10_5);

/* Bi-directional User Interface. It specifies the general UI layout flow directions.
*/
@property NSUserInterfaceLayoutDirection userInterfaceLayoutDirection NS_AVAILABLE_MAC(10_6);

/* Returns a custom field editor for editing inside aControlView. This is an override point for NSCell subclasses designed to work with its own custom field editor. This message is sent to the selected cell of aControlView in -[NSWindow fieldEditor:forObject:]. Returning non-nil from this method indicates skipping the standard field editor querying processes including -windowWillReturnFieldEditor:toObject: delegation. The default NSCell implementation returns nil. The field editor returned from this method should have isFieldEditor == YES.
 */
- (nullable NSTextView *)fieldEditorForView:(NSView *)aControlView NS_AVAILABLE_MAC(10_6);

/* Tells the text cell to layout/render its content in single-line. If YES, the cell ignores the return value from -wraps, interprets NSLineBreakByWordWrapping and NSLineBreakByCharWrapping from -lineBreakMode as NSLineBreakByClipping, and configures the field editor to ignore key binding commands that insert paragraph/line separators. Also, the field editor bound to a single line cell filters paragraph/line separator insertion from user actions. Cells in the single line mode use the fixed baseline layout. The text baseline position is determined solely by the control size regardless of content font style/size.
 */
@property BOOL usesSingleLineMode NS_AVAILABLE_MAC(10_6);

/* Multi-image Drag Support. The default implementation will return an array of up to two NSDraggingImageComponent instances -- one for the image portion and another for the text portion (if appropriate). This method can be subclassed and overridden to provide a custom set of NSDraggingImageComponents to create the drag image for the cell. This method is generally used by NSTableView/NSOutlineView.
 */
- (NSArray<NSDraggingImageComponent *> *)draggingImageComponentsWithFrame:(NSRect)frame inView:(NSView *)view NS_AVAILABLE_MAC(10_7);

@end

@interface NSCell(NSKeyboardUI)
@property BOOL refusesFirstResponder;
@property (readonly) BOOL acceptsFirstResponder;
@property BOOL showsFirstResponder;

- (void)performClick:(nullable id)sender;

@property NSFocusRingType focusRingType;
+ (NSFocusRingType)defaultFocusRingType;

- (void)drawFocusRingMaskWithFrame:(NSRect)cellFrame inView:(NSView *)controlView NS_AVAILABLE_MAC(10_7);
- (NSRect)focusRingMaskBoundsForFrame:(NSRect)cellFrame inView:(NSView *)controlView NS_AVAILABLE_MAC(10_7);

@property (readonly) BOOL wantsNotificationForMarkedText; // If the receiver returns YES, the field editor initiated by it posts text change notifications (i.e. NSTextDidChangeNotification) while editing marked text; otherwise, they are delayed until the marked text confirmation. The NSCell's implementation returns NO.
@end

@interface NSCell(NSCellAttributedStringMethods)
@property (copy) NSAttributedString *attributedStringValue;
/* These methods determine whether the user can modify text attributes and import graphics in a rich cell.  Note that whatever these flags are, cells can still contain attributed text if programmatically set. */
@property BOOL allowsEditingTextAttributes;       /* If NO, also clears setImportsGraphics: */
@property BOOL importsGraphics;                   /* If YES, also sets setAllowsEditingTextAttributes: */
@end

@interface NSCell(NSCellMixedState)	/* allow button to have mixed state value*/
@property BOOL allowsMixedState;
@property (readonly) NSInteger nextState;			/* get next state state in cycle */
- (void)setNextState;			/* toggle/cycle through states */
@end

APPKIT_EXTERN NSString * NSControlTintDidChangeNotification; /* sent after user changes control tint preference */

/* Cell Hit testing support */

typedef NS_OPTIONS(NSUInteger, NSCellHitResult) {
    // An empty area, or did not hit in the cell
    NSCellHitNone = 0,
    // A content area in the cell
    NSCellHitContentArea = 1 << 0,
    // An editable text area of the cell
    NSCellHitEditableTextArea = 1 << 1,
    // A trackable area in the cell
    NSCellHitTrackableArea = 1 << 2,
} NS_ENUM_AVAILABLE_MAC(10_5);

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
- (NSCellHitResult)hitTestForEvent:(NSEvent *)event inRect:(NSRect)cellFrame ofView:(NSView *)controlView NS_AVAILABLE_MAC(10_5);
@end

@interface NSCell(NSCellExpansion)
/*  Allows the cell to return an expansion cell frame if cellFrame is too small for the entire contents in the view. When the mouse is hovered over the cell in certain controls, the full cell contents will be shown in a special floating tool tip view. If the frame is not too small, return an empty rect, and no expansion tool tip view will be shown. By default, NSCell returns NSZeroRect, while some subclasses (such as NSTextFieldCell) will return the proper frame when required. 
*/
- (NSRect)expansionFrameWithFrame:(NSRect)cellFrame inView:(NSView *)view NS_AVAILABLE_MAC(10_5);

/* Allows the cell to perform custom expansion tool tip drawing. Note that the view may be different from the original view that the cell appeared in. By default, NSCell simply calls drawWithFrame:inView:.
*/
- (void)drawWithExpansionFrame:(NSRect)cellFrame inView:(NSView *)view NS_AVAILABLE_MAC(10_5);
@end

typedef NS_ENUM(NSInteger, NSBackgroundStyle) {
    NSBackgroundStyleLight = 0,	// The background is a light color. Dark content contrasts well with this background.
    NSBackgroundStyleDark,	// The background is a dark color. Light content contrasts well with this background.
    NSBackgroundStyleRaised,	// The background is intended to appear higher than the content drawn on it. Content might need to be inset.
    NSBackgroundStyleLowered	// The background is intended to appear lower than the content drawn on it. Content might need to be embossed.
} NS_ENUM_AVAILABLE_MAC(10_5);

@interface NSCell (NSCellBackgroundStyle)

/* Describes the surface the cell is drawn onto in -[NSCell drawWithFrame:inView:]. A control typically sets this before it asks the cell to draw. A cell may draw differently based on background characteristics. For example, a tableview drawing a cell in a selected row might call [cell setBackgroundStyle:NSBackgroundStyleDark]. A text cell might decide to render its text white as a result. A rating-style level indicator might draw its stars white instead of gray.
 */
@property NSBackgroundStyle backgroundStyle NS_AVAILABLE_MAC(10_5);


/* Describes the surface drawn onto in -[NSCell drawInteriorWithFrame:inView:]. This is often the same as the backgroundStyle, but a button that draws a bezel would have a different interiorBackgroundStyle.  
 
 This is both an override point and a useful method to call. A button that draws a custom bezel would override this to describe that surface. A cell that has custom interior drawing might query this method to help pick an image that looks good on the cell. Calling this method gives you some independence from changes in framework art style.
 */
@property (readonly) NSBackgroundStyle interiorBackgroundStyle NS_AVAILABLE_MAC(10_5);

@end


@interface NSCell (NSDeprecated)

// Use formatters instead.  See -[NSCell formatter] and -[NSCell setFormatter:].
- (NSInteger)entryType NS_DEPRECATED_MAC(10_0, 10_0);
- (void)setEntryType:(NSInteger)aType NS_DEPRECATED_MAC(10_0, 10_0);
- (BOOL)isEntryAcceptable:(NSString *)aString NS_DEPRECATED_MAC(10_0, 10_0);
- (void)setFloatingPointFormat:(BOOL)autoRange left:(NSUInteger)leftDigits right:(NSUInteger)rightDigits NS_DEPRECATED_MAC(10_0, 10_0);

/* In 10.8 and higher, all the *Mnemonic* methods are deprecated. On MacOS they have typically not been used.
 */
- (void)setMnemonicLocation:(NSUInteger)location NS_DEPRECATED_MAC(10_0, 10_8);
- (NSUInteger)mnemonicLocation NS_DEPRECATED_MAC(10_0, 10_8);
- (NSString *)mnemonic NS_DEPRECATED_MAC(10_0, 10_8);
- (void)setTitleWithMnemonic:(NSString *)stringWithAmpersand NS_DEPRECATED_MAC(10_0, 10_8);

@end


/* Draw an image from two end caps and a fill.  The end caps are scaled proportionally to match the thickness of the destination frame.  In the horizontal case, the startCap is drawn into the left part of the destination, the endCap is drawn into the right part of the destination, and the fill is tiled over the remaining area.  The caps and the fill should all be the same height.  The vertical case is similar.  
 
 This is an appropriate way to draw the bezel of a button that can be resized in one dimension.
 */
APPKIT_EXTERN void NSDrawThreePartImage(NSRect frame, NSImage * __nullable startCap, NSImage * __nullable centerFill, NSImage * __nullable endCap, BOOL vertical, NSCompositingOperation op, CGFloat alphaFraction, BOOL flipped) NS_AVAILABLE_MAC(10_5);

/* Draw an image from nine pieces.  When drawn, the destination rect is partitioned into nine rectangular regions: the corner pieces are the natural size of the corner images, the edge pieces are the natural size of the edge fill images in the direction perpendicular to the edge and flush with the corners.  The center rect fills the remaining space.  The supplied images and fills are drawn into the corresponding regions, with fill images tiled at their natural dimensions.  Images that share a border should have the same thickness in that dimension.  
 
 This method is appropriate for the bezel of a control, like a box, that can be resized in both dimensions.
 */
APPKIT_EXTERN void NSDrawNinePartImage(NSRect frame, NSImage * topLeftCorner, NSImage * topEdgeFill, NSImage * topRightCorner, NSImage * leftEdgeFill, NSImage * centerFill, NSImage * rightEdgeFill, NSImage * bottomLeftCorner, NSImage * bottomEdgeFill, NSImage * bottomRightCorner, NSCompositingOperation op, CGFloat alphaFraction, BOOL flipped) NS_AVAILABLE_MAC(10_5);

enum {
    NSAnyType				= 0,
    NSIntType				= 1,
    NSPositiveIntType			= 2,
    NSFloatType				= 3,
    NSPositiveFloatType		= 4,
    NSDoubleType			= 6,
    NSPositiveDoubleType		= 7
} NS_ENUM_DEPRECATED_MAC(10_0, 10_10, "Use formatters instead");

NS_ASSUME_NONNULL_END
