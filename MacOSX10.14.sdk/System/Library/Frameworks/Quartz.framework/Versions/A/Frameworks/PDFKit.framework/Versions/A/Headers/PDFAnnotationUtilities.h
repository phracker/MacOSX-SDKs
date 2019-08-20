//
//  PDFAnnotationUtilities.h
//  Copyright © 2016 Apple. All rights reserved.
//
//  This file includes several helper functions that match legacy PDFAnnotation
//  subclass functions, helping simplify creating properties for common annotations.
//

#import <PDFKit/PDFKitPlatform.h>
#import <PDFKit/PDFAnnotation.h>

NS_ASSUME_NONNULL_BEGIN

// Style used for line end caps.
typedef NS_ENUM(NSInteger, PDFLineStyle)
{
    kPDFLineStyleNone = 0,
    kPDFLineStyleSquare = 1,
    kPDFLineStyleCircle = 2,
    kPDFLineStyleDiamond = 3,
    kPDFLineStyleOpenArrow = 4,
    kPDFLineStyleClosedArrow = 5
};

// Icon that appears indicating text annotation pop-up.
typedef NS_ENUM(NSInteger, PDFTextAnnotationIconType)
{
    kPDFTextAnnotationIconComment = 0,
    kPDFTextAnnotationIconKey = 1,
    kPDFTextAnnotationIconNote = 2,
    kPDFTextAnnotationIconHelp = 3,
    kPDFTextAnnotationIconNewParagraph = 4,
    kPDFTextAnnotationIconParagraph = 5,
    kPDFTextAnnotationIconInsert = 6
};

// Types of markup annotations.
typedef NS_ENUM(NSInteger, PDFMarkupType)
{
    kPDFMarkupTypeHighlight = 0,
    kPDFMarkupTypeStrikeOut = 1,
    kPDFMarkupTypeUnderline = 2
};

// Type of control.
typedef NS_ENUM(NSInteger, PDFWidgetControlType)
{
    kPDFWidgetUnknownControl = -1,
    kPDFWidgetPushButtonControl = 0,
    kPDFWidgetRadioButtonControl = 1,
    kPDFWidgetCheckBoxControl = 2
};

// Cell state.
typedef NS_ENUM(NSInteger, PDFWidgetCellState)
{
    kPDFWidgetMixedState = -1,
    kPDFWidgetOffState = 0,
    kPDFWidgetOnState = 1,
};

// All PDF annotation subtypes that PDFKit can render: based on Adobe PDF specification, Table 8.20: Annotation types.
// Annotation subtypes not supported: Polygon, PolyLine, Squiggly, Caret, Caret, FileAttachment,
// Sound, Movie, Screen, PrinterMark, TrapNet, Watermark, 3D, Rect.
PDFKIT_EXTERN PDFAnnotationSubtype PDFAnnotationSubtypeText PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationSubtype PDFAnnotationSubtypeLink PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationSubtype PDFAnnotationSubtypeFreeText PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationSubtype PDFAnnotationSubtypeLine PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationSubtype PDFAnnotationSubtypeSquare PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationSubtype PDFAnnotationSubtypeCircle PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationSubtype PDFAnnotationSubtypeHighlight PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationSubtype PDFAnnotationSubtypeUnderline PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationSubtype PDFAnnotationSubtypeStrikeOut PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationSubtype PDFAnnotationSubtypeInk PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationSubtype PDFAnnotationSubtypeStamp PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationSubtype PDFAnnotationSubtypePopup PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationSubtype PDFAnnotationSubtypeWidget PDFKIT_AVAILABLE(10_13, 11_0);

// Widget annotations have the following possible subtypes: Button, Choice, Signature, and Text
typedef NSString* const PDFAnnotationWidgetSubtype NS_STRING_ENUM;

PDFKIT_EXTERN PDFAnnotationWidgetSubtype PDFAnnotationWidgetSubtypeButton PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationWidgetSubtype PDFAnnotationWidgetSubtypeChoice PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationWidgetSubtype PDFAnnotationWidgetSubtypeSignature PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationWidgetSubtype PDFAnnotationWidgetSubtypeText PDFKIT_AVAILABLE(10_13, 11_0);

// Line annotation have the following line ending types (this maps directly to PDFLineStyle)
typedef NSString* const PDFAnnotationLineEndingStyle NS_STRING_ENUM;

PDFKIT_EXTERN PDFAnnotationLineEndingStyle PDFAnnotationLineEndingStyleNone PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationLineEndingStyle PDFAnnotationLineEndingStyleSquare PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationLineEndingStyle PDFAnnotationLineEndingStyleCircle PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationLineEndingStyle PDFAnnotationLineEndingStyleDiamond PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationLineEndingStyle PDFAnnotationLineEndingStyleOpenArrow PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationLineEndingStyle PDFAnnotationLineEndingStyleClosedArrow PDFKIT_AVAILABLE(10_13, 11_0);

// Text annotations have the following icon types:
typedef NSString* const PDFAnnotationTextIconType NS_STRING_ENUM;

PDFKIT_EXTERN PDFAnnotationTextIconType PDFAnnotationTextIconTypeComment PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationTextIconType PDFAnnotationTextIconTypeKey PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationTextIconType PDFAnnotationTextIconTypeNote PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationTextIconType PDFAnnotationTextIconTypeHelp PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationTextIconType PDFAnnotationTextIconTypeNewParagraph PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationTextIconType PDFAnnotationTextIconTypeParagraph PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationTextIconType PDFAnnotationTextIconTypeInsert PDFKIT_AVAILABLE(10_13, 11_0);

// Highlighting styles
typedef NSString* const PDFAnnotationHighlightingMode NS_STRING_ENUM;

PDFKIT_EXTERN PDFAnnotationHighlightingMode PDFAnnotationHighlightingModeNone PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationHighlightingMode PDFAnnotationHighlightingModeInvert PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationHighlightingMode PDFAnnotationHighlightingModeOutline PDFKIT_AVAILABLE(10_13, 11_0);
PDFKIT_EXTERN PDFAnnotationHighlightingMode PDFAnnotationHighlightingModePush PDFKIT_AVAILABLE(10_13, 11_0);

@class PDFDestination;

// Helper functions for directly manipulating annotation dictionaries
@interface PDFAnnotation (PDFAnnotationUtilities)

// Font and font color associated with the text field.
// Used by annotations type(s): /FreeText, /Popup, /Widget (field type(s): /Btn, /Ch, and /Tx).
@property (nonatomic, copy, nullable) PDFKitPlatformFont *font;

// Width of line used to stroke border.
// Used by annotations type(s): /FreeText, /Widget (field type(s): /Btn, /Ch, and /Tx).
@property (nonatomic, copy, nullable) PDFKitPlatformColor *fontColor;

// Interior color of the annotation.
// Used by annotations type(s): /Circle, /Line, /Square.
@property (nonatomic, copy, nullable) PDFKitPlatformColor *interiorColor;

// Alignment of text within annotation bounds.  Supported: NSLeftTextAlignment, NSRightTextAlignment and
// NSCenterTextAlignment.
// Used by annotations type(s): /FreeText, /Widget (field type(s): /Tx).
@property (nonatomic) NSTextAlignment alignment;

// Points specifying start and end points for line annotation (required).
// Points are specified in annotation space.
// Used by annotations type(s): /Line.
@property (nonatomic) PDFPoint startPoint;
@property (nonatomic) PDFPoint endPoint;

// Style used for ornaments at the lines start and end (optional, PDF 1.4).
// Used by annotations type(s): /Line.
@property (nonatomic) PDFLineStyle startLineStyle;
@property (nonatomic) PDFLineStyle endLineStyle;

// Class methods to help with mapping PDFLineStyle to the associated name based on PDF specification
// Used by annotations type(s): /Line.
+ (PDFLineStyle) lineStyleFromName:(NSString *)name;
+ (NSString *) nameForLineStyle:(PDFLineStyle)style;

// The type of icon displayed in the PDF.  Supported icons: "Comment", "Key", "Note", "Help", "NewParagraph",
// "Paragraph" and "Insert".
// Used by annotations type(s): /Text.
@property (nonatomic) PDFTextAnnotationIconType iconType;

// Array of n * 4 points, packed as NSValue pointValue / CGPointValue, defining n quadrilaterals in page space where n is the number of quad points.
// The points for each quad are ordered in a 'Z' pattern. That is, the first point should represent the upper left
// point representing the start of the marked-up text, the next point will be the upper right, the third point will
// represent the lower left of the text and the last point the lower right.
// Points are specified relative to the annotation's bound's origin.
@property (nonatomic, copy, nullable) NSArray<NSValue *> *quadrilateralPoints;

// Type of mark-up (highlight, strike-out or underline). Changing the markup type also changes the annotations type.
// Used by annotations type(s): /Highlight, /StrikeOut, /Underline.
@property (nonatomic) PDFMarkupType markupType;

// The specific field type of a widget annotation (button, choice, or text).
// Used by annotations type(s): /Widget (field type(s): /Btn, /Ch, /Tx).
@property (nonatomic, copy) PDFAnnotationWidgetSubtype widgetFieldType;

// The type of button widget control type (radio button, push button, or checkbox).
// Used by annotations type(s): /Widget (field type(s): /Btn).
@property (nonatomic) PDFWidgetControlType widgetControlType;

// Used to configure multiline PDF text fields.
// Used by annotations type(s): /Widget (field type(s): /Tx).
@property (nonatomic, getter=isMultiline) BOOL multiline;

// Used to determine if a PDF text field is a password field.
// Used by annotations type(s): /Widget (field type(s): /Tx).
@property (nonatomic, readonly) BOOL isPasswordField;

// Used to configure combing for PDF text fields.
// If set, the field is automatically divided into as many equally spaced positions, or combs, as the value of the
// maximum length of the field. To get the maximum length, use annotaiton key: PDFAnnotationKeyWidgetMaxLen.
// Used by annotations type(s): /Widget (field type(s): /Tx).
@property (nonatomic, getter=hasComb) BOOL comb;

// Maximum characters allowed (optional, zero indicates no specified maximum).
// Used by annotations type(s): /Widget (field type(s): /Tx).
@property (nonatomic) NSInteger maximumLength;

// The string value for a widget annotation.
// Used by annotations type(s): /Widget (field type(s): /Btn, /Ch, /Tx).
@property (nonatomic, copy, nullable) NSString *widgetStringValue;

// The string value for a widget annotation.
// Used by annotations type(s): /Widget (field type(s): /Btn, /Ch, /Tx).
@property (nonatomic, copy, nullable) NSString *widgetDefaultStringValue;

// For radio buttons, indicates whether clicking on widget whose state is already On toggles it Off.
// Used by annotations type(s): /Widget (field type(s): /Btn).
@property (nonatomic) BOOL allowsToggleToOff;

// For radio buttons, indicates whether a group of radio buttons will turn on and off in
// unison; that is if one is checked, they are all checked. If clear, the buttons are mutually exclusive.
// Used by annotations type(s): /Widget (field type(s): /Btn).
@property (nonatomic) BOOL radiosInUnison;

// Determines if a text field should be editable or not.
// Used by annotations type(s): /Widget (field type(s): /Tx).
@property (nonatomic, getter=isReadOnly) BOOL readOnly;

// There are two flavors of Choice widget annotations, lists and pop-up menus. This method allow you to differentiate.
// Used by annotations type(s): /Widget (field type(s): /Ch).
@property (nonatomic, getter=isListChoice) BOOL listChoice;

// The choices are an array of strings indicating the options (items) in either a list or pop-up menu.
// Used by annotations type(s): /Widget (field type(s): /Ch).
@property (nonatomic, copy, nullable) NSArray<NSString *> *choices;

// The choices are an array of strings indicating the  option’s export values in either a list or pop-up menu.
// Used by annotations type(s): /Widget (field type(s): /Ch).
@property (nonatomic, copy, nullable) NSArray<NSString *> *values;

// The current state of a button widget annotation.
// Used by annotations type(s): /Widget (field type(s): /Btn).
@property (nonatomic) PDFWidgetCellState buttonWidgetState;

// The string that represents the ON state of a button widget annotation.
// This should be set when trying to, for example, group together a set of radio buttons with the same field name.
// When buttons share the same field name, their individual state strings set them apart from one another.
// Used by annotations type(s): /Widget (field type(s): /Btn).
@property (nonatomic, copy) NSString *buttonWidgetStateString;

// Used to tell if an annotation is open or closed.
// Used by annotations type(s): /Popup.
@property (nonatomic, getter=isOpen) BOOL open;

// Array of NSBezierPaths / UIBezierPaths that comprise the annotation.
// Paths are specified in annotation space.
// Used by annotations type(s): /Ink.
@property (nonatomic, readonly, nullable) NSArray<PDFKitPlatformBezierPath *> *paths;

// Add or remove paths from the annotation.
// Path points are specified in annotation space.
// Used by annotations type(s): /Ink.
- (void)addBezierPath:(PDFKitPlatformBezierPath *)path;
- (void)removeBezierPath:(PDFKitPlatformBezierPath *)path;

// Destination for the link. May be nil if no destination associated with link; in this case the -[URL] may be valid.
// The preferred way though is to call -[PDFAnnotation action] and -[PDFAnnotation setAction:].
// Used by annotations type(s): /Link.
@property (nonatomic, strong, nullable) PDFDestination *destination;

// URL for the link. May be nil if no URL action associated with link; in this case the -[destination] may be valid.
// The preferred way though is to call -[PDFAnnotation action] and -[PDFAnnotation setAction:].
// Used by annotations type(s): /Link.
@property (nonatomic, copy, nullable) NSURL *URL;

// Widget annotations backed by form data have (internal) field names with which to associate a value or data.
// Can also be used for ResetForm actions.
// Used by annotations type(s): /Widget (field type(s): /Btn, /Ch, /Tx).
@property (nonatomic, copy, nullable) NSString *fieldName;

// Label for the button. Applies to kPDFWidgetPushButtonControl only.
// Used by annotations type(s): /Widget (field type(s): /Btn).
@property (nonatomic, copy, nullable) NSString *caption;

// Background color characteristics.
// Used by annotations type(s): /Widget (field type(s): /Btn, /Ch, /Tx).
@property (nonatomic, copy, nullable) PDFKitPlatformColor *backgroundColor;

// Name of stamp annotation. Standard stamps include names like, "Approved", "Draft", "TopSecret", etc.
// The name must be representable as ASCII. Very little is rendered if the annotation has no appearance stream.
// Used by annotations type(s): /Stamp
@property (nonatomic, copy, nullable) NSString *stampName;

@end

NS_ASSUME_NONNULL_END
