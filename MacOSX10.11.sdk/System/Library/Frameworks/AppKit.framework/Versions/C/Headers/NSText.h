/*
	NSText.h
	Application Kit
	Copyright (c) 1994-2015, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSView.h>
#import <AppKit/NSSpellProtocol.h>

NS_ASSUME_NONNULL_BEGIN

@class NSColor, NSFont, NSNotification;
@protocol NSTextDelegate;

/* Various important Unicode code points */
enum {
    NSEnterCharacter                = 0x0003,
    NSBackspaceCharacter            = 0x0008,
    NSTabCharacter                  = 0x0009,
    NSNewlineCharacter              = 0x000a,
    NSFormFeedCharacter             = 0x000c,
    NSCarriageReturnCharacter       = 0x000d,
    NSBackTabCharacter              = 0x0019,
    NSDeleteCharacter               = 0x007f,
    NSLineSeparatorCharacter        = 0x2028,
    NSParagraphSeparatorCharacter   = 0x2029
};

/* Values for NSTextAlignment */
typedef NS_ENUM(NSUInteger, NSTextAlignment) {
    NSTextAlignmentLeft      = 0,    // Visually left aligned
#if TARGET_OS_IPHONE
    NSTextAlignmentCenter    = 1,    // Visually centered
    NSTextAlignmentRight     = 2,    // Visually right aligned
#else /* !TARGET_OS_IPHONE */
    NSTextAlignmentRight     = 1,    // Visually right aligned
    NSTextAlignmentCenter    = 2,    // Visually centered
#endif
    NSTextAlignmentJustified = 3,    // Fully-justified. The last line in a paragraph is natural-aligned.
    NSTextAlignmentNatural   = 4     // Indicates the default alignment for script
};

/* Values for NSWritingDirection */
typedef NS_ENUM(NSInteger, NSWritingDirection) {
    NSWritingDirectionNatural       = -1,   // Determines direction using the Unicode Bidi Algorithm rules P2 and P3
    NSWritingDirectionLeftToRight   = 0,    // Left to right writing direction
    NSWritingDirectionRightToLeft   = 1     // Right to left writing direction
};

/* Movement codes for movement between fields; these codes are the integer values of the NSTextMovement key in NSTextDidEndEditing notifications, and are used when completions change in the NSTextView method insertCompletion:forPartialWordRange:movement:isFinal:.  Note that the value 0 is used for movements that do not fall under any of the other values, hence NSOtherTextMovement is a more appropriate name than the previous NSIllegalTextMovement.
*/
enum {
    NSIllegalTextMovement		= 0,
    NSReturnTextMovement		= 0x10,
    NSTabTextMovement			= 0x11,
    NSBacktabTextMovement		= 0x12,
    NSLeftTextMovement			= 0x13,
    NSRightTextMovement			= 0x14,
    NSUpTextMovement			= 0x15,
    NSDownTextMovement			= 0x16,
    NSCancelTextMovement		= 0x17,
    NSOtherTextMovement			= 0
};

@interface NSText : NSView <NSChangeSpelling, NSIgnoreMisspelledWords> {
    /*All instance variables are private*/
    id _ivars;
}

- (instancetype)initWithFrame:(NSRect)frameRect NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@property (nullable, copy) NSString *string;

- (void)replaceCharactersInRange:(NSRange)range withString:(NSString *)aString;
- (void)replaceCharactersInRange:(NSRange)range withRTF:(NSData *)rtfData;
- (void)replaceCharactersInRange:(NSRange)range withRTFD:(NSData *)rtfdData;

- (nullable NSData *)RTFFromRange:(NSRange)range;
- (nullable NSData *)RTFDFromRange:(NSRange)range;

- (BOOL)writeRTFDToFile:(NSString *)path atomically:(BOOL)flag;
- (BOOL)readRTFDFromFile:(NSString *)path;

@property (nullable, assign) id<NSTextDelegate> delegate;

@property (getter=isEditable) BOOL editable;
@property (getter=isSelectable) BOOL selectable;
@property (getter=isRichText) BOOL richText;        //If NO, also clears setImportsGraphics:
@property BOOL importsGraphics; // If YES, also sets setRichText:
@property (getter=isFieldEditor) BOOL fieldEditor;     // Indicates whether to end editing on CR, TAB, etc.
@property BOOL usesFontPanel;
@property BOOL drawsBackground;
@property (nullable, copy) NSColor *backgroundColor; // Default is nil. If nil, it implies -drawsBackground=NO

@property (getter=isRulerVisible, readonly) BOOL rulerVisible;

@property NSRange selectedRange;

- (void)scrollRangeToVisible:(NSRange)range;

@property (nullable, strong) NSFont *font;
@property (nullable, copy) NSColor *textColor; // Default is nil. If nil, draws with blackColor
@property NSTextAlignment alignment;
@property NSWritingDirection baseWritingDirection;

- (void)setTextColor:(nullable NSColor *)color range:(NSRange)range; // Passing nil removes NSForegroundColorAttributeName from range
- (void)setFont:(NSFont *)font range:(NSRange)range;

@property NSSize maxSize;
@property NSSize minSize;

@property (getter=isHorizontallyResizable) BOOL horizontallyResizable;
@property (getter=isVerticallyResizable) BOOL verticallyResizable;

- (void)sizeToFit;

- (void)copy:(nullable id)sender;
- (void)copyFont:(nullable id)sender;
- (void)copyRuler:(nullable id)sender;
- (void)cut:(nullable id)sender;
- (void)delete:(nullable id)sender;
- (void)paste:(nullable id)sender;
- (void)pasteFont:(nullable id)sender;
- (void)pasteRuler:(nullable id)sender;
- (void)selectAll:(nullable id)sender;
- (void)changeFont:(nullable id)sender;
- (void)alignLeft:(nullable id)sender;
- (void)alignRight:(nullable id)sender;
- (void)alignCenter:(nullable id)sender;
- (void)subscript:(nullable id)sender;
- (void)superscript:(nullable id)sender;
- (void)underline:(nullable id)sender;
- (void)unscript:(nullable id)sender;
- (void)showGuessPanel:(nullable id)sender;
- (void)checkSpelling:(nullable id)sender;
- (void)toggleRuler:(nullable id)sender;

@end

@protocol NSTextDelegate <NSObject>
@optional
- (BOOL)textShouldBeginEditing:(NSText *)textObject;        // YES means do it
- (BOOL)textShouldEndEditing:(NSText *)textObject;          // YES means do it
- (void)textDidBeginEditing:(NSNotification *)notification;
- (void)textDidEndEditing:(NSNotification *)notification;
- (void)textDidChange:(NSNotification *)notification;       // Any keyDown or paste which changes the contents causes this
@end

/* Notifications */
APPKIT_EXTERN NSString * NSTextDidBeginEditingNotification;
APPKIT_EXTERN NSString * NSTextDidEndEditingNotification;    // userInfo key:  @"NSTextMovement"
APPKIT_EXTERN NSString * NSTextDidChangeNotification;


/* Deprecated */
/* Additional values to be added to NSWritingDirectionLeftToRight or NSWritingDirectionRightToLeft, when used with NSWritingDirectionAttributeName */
enum {
    NSTextWritingDirectionEmbedding NS_DEPRECATED_MAC(10_0, 10_11, "Use NSWritingDirectionEmbedding instead")     = (0 << 1),
    NSTextWritingDirectionOverride NS_DEPRECATED_MAC(10_0, 10_11, "Use NSWritingDirectionOverride instead")      = (1 << 1)
};

static const NSTextAlignment NSLeftTextAlignment = NSTextAlignmentLeft;
static const NSTextAlignment NSRightTextAlignment = NSTextAlignmentRight;
static const NSTextAlignment NSCenterTextAlignment = NSTextAlignmentCenter;
static const NSTextAlignment NSJustifiedTextAlignment = NSTextAlignmentJustified;
static const NSTextAlignment NSNaturalTextAlignment = NSTextAlignmentNatural;

NS_ASSUME_NONNULL_END
