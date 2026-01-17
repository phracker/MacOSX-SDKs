// =====================================================================================================================
//  PDFAnnotation.h
// =====================================================================================================================

#import <PDFKit/PDFKitPlatform.h>

#import <PDFKit/PDFPage.h>

#import <PDFKit/PDFAction.h>

/***
 
 PDF Specification 32000-1:2008 (1.7) defines in Table 164 "Entries common to all annotation dictionaries" 14
 common properties among all annotations. 2-4 are required, the rest are optional. PDFKit supports 13 of these
 annotations. For all common properties and each annotation's specific properties, we define them as enumerations
 and enum-mapped strings at the top of this file. The below functions allow you to set these key-values using
 either string literals as values, or type-friendly values (for color, points, etc.).
 
 ***/

NS_ASSUME_NONNULL_BEGIN

// Common keys used for all annotations
// PDF Specification 32000-1:2008, Table 164
extern NSString* const kPDFAnnotationKey_AppearanceDictionary;              // "/AP": Dictionary
extern NSString* const kPDFAnnotationKey_AppearanceState;                   // "/AS": Name
extern NSString* const kPDFAnnotationKey_Border;                            // "/Border": Array of Integers; or a PDFBorder object
extern NSString* const kPDFAnnotationKey_Color;                             // "/C": Array of Floats; or a PDFKitPlatformColor object
extern NSString* const kPDFAnnotationKey_Contents;                          // "/Contents": String
extern NSString* const kPDFAnnotationKey_Flags;                             // "/F": Integer
extern NSString* const kPDFAnnotationKey_Date;                              // "/M": Date or String
extern NSString* const kPDFAnnotationKey_Name;                              // "/NM": String
extern NSString* const kPDFAnnotationKey_Page;                              // "/P": Dictionary; or a PDFPage object.
extern NSString* const kPDFAnnotationKey_Rect;                              // "/Rect": CGRect
extern NSString* const kPDFAnnotationKey_Subtype;                           // "/Subtype": Name

// Additional annotation extentions...
// Markup extentions: PDF Specification 32000-1:2008, Table 170
// Text extentions: PDF Specification 32000-1:2008, Table 172
// Link extentions: PDF Specification 32000-1:2008, Table 173
// Free Text extentions: PDF Specification 32000-1:2008, Table 174
// Line extentions: PDF Specification 32000-1:2008, Table 175
// Circle/Square extentions: PDF Specification 32000-1:2008, Table 177
// Stamp extentions: PDF Specification 32000-1:2008, Table 181
// Ink extentions: PDF Specification 32000-1:2008, Table 182
// Popup extentions: PDF Specification 32000-1:2008, Table 183
extern NSString* const kPDFAnnotationKey_Action;                            // "/A": Dictionary; or a PDFAction object
extern NSString* const kPDFAnnotationKey_AdditionalActions;                 // "/AA": Dictionary; or a PDFAction object
extern NSString* const kPDFAnnotationKey_AppleExtras;                       // "/AAPL:AKExtras": (various)
extern NSString* const kPDFAnnotationKey_BorderStyle;                       // "/BS": Dictionary
extern NSString* const kPDFAnnotationKey_DefaultAppearance;                 // "/DA": String
extern NSString* const kPDFAnnotationKey_Destination;                       // "/Dest": Array, Name, or String
extern NSString* const kPDFAnnotationKey_HighlightingMode;                  // "/H": Name
extern NSString* const kPDFAnnotationKey_Inklist;                           // "/Inklist": Array of Arrays (each array representing a stroked path)
extern NSString* const kPDFAnnotationKey_InteriorColor;                     // "/IC": Array of Floats; or a PDFKitPlatformColor object
extern NSString* const kPDFAnnotationKey_LinePoints;                        // "/L": Array of Floats
extern NSString* const kPDFAnnotationKey_LineEndingStyles;                  // "/LE": Array of Strings (See PDF Specification 32000-1:2008, Table 176)
extern NSString* const kPDFAnnotationKey_IconName;                          // "/Name": Name
extern NSString* const kPDFAnnotationKey_Open;                              // "/Open": Boolean
extern NSString* const kPDFAnnotationKey_Parent;                            // "/Parent": Dictionary; or a PDFAnnotation object
extern NSString* const kPDFAnnotationKey_Popup;                             // "/Popup": Dictionary; or a PDFAnnotation object of type "Popup"
extern NSString* const kPDFAnnotationKey_Quadding;                          // "/Q": Integer
extern NSString* const kPDFAnnotationKey_QuadPoints;                        // "/QuadPoints": Array of Floats (PDF Specification 32000-1:2008, Table 179)
extern NSString* const kPDFAnnotationKey_TextLabel;                         // "/T": String

// Widget annotation extensions
// PDF Specification 32000-1:2008, Table 188 & Table 220
extern NSString* const kPDFAnnotationKey_WidgetDefaultValue;                // "/DV": (various)
extern NSString* const kPDFAnnotationKey_WidgetFieldFlags;                  // "/Ff": Integer
extern NSString* const kPDFAnnotationKey_WidgetFieldType;                   // "/FT": Name
extern NSString* const kPDFAnnotationKey_WidgetAppearanceDictionary;        // "/MK": Dictionary
extern NSString* const kPDFAnnotationKey_WidgetMaxLen;                      // "/MaxLen": Integer (See PDF Specification 32000-1:2008, Table 229)
extern NSString* const kPDFAnnotationKey_WidgetOptions;                     // "/Opt": Array (each element is either a string, or an array of two strings (See PDF Specification 32000-1:2008, Table 231))
extern NSString* const kPDFAnnotationKey_WidgetTextLabelUI;                   // "/TU": String
extern NSString* const kPDFAnnotationKey_WidgetValue;                       // "/V": (various)

@class PDFAction, PDFBorder, PDFPage, PDFAnnotationPopup, PDFAnnotationPrivateVars;

NS_CLASS_AVAILABLE_MAC(10_4)
@interface PDFAnnotation : NSObject <NSCopying, NSCoding>
{
@private
    PDFAnnotationPrivateVars *_private;
}

// This is the base class for all annotations. A PDFAnnotation object by itself is not useful, only subclasses (like 
// PDFAnnotationCircle, PDFAnnotationText) are interesting. In parsing a PDF however, any unknown or unsupported 
// annotations will be represented as this base class.

// -------- initializer

// You should only call this method for the subclasses, otherwise you will get a type of nil Ñ which is not a legal annotation.
- (instancetype) initWithBounds: (PDFRect) bounds PDFKIT_DEPRECATED(10_4, 10_12);

// Create a custom annotation using a given annotation dictionary, assigning it to the (optional) page
- (instancetype) initWithDictionary: (NSDictionary*) dictionary forPage: (nullable PDFPage *) page PDFKIT_AVAILABLE(10_12);

// -------- accessors

// Returns the page the annotation is associated with (may return nil if annotation not associated with a page).
@property(nonatomic, readwrite, weak, nullable) PDFPage* page;

// Returns the annotation type (called "Subtype" in the PDF specification since "Annot" is the type). Examples include: 
// "Text", "Link", "Line", etc.  Required.
@property(nonatomic, readonly, nullable) NSString* type;

// Required for all annotations.  The bounding box in page-space of the annotation.
@property(nonatomic, readwrite) PDFRect bounds;

// Optional (-[modificationDate] may return nil).  Modification date of the annotation.
@property(nonatomic, retain, nullable) NSDate* modificationDate PDFKIT_DEPRECATED(10_5, 10_12);

// Optional (-[userName] may return nil).  Name of the user who created the annotation.
@property(nonatomic, retain, nullable) NSString* userName PDFKIT_DEPRECATED(10_5, 10_12);

// Optional (-[popup] may return nil).  Not used with links or widgets, a popup annotation associated with this 
// annotation.  The bounds and open state of the popup indicate the placement and open state of the popup window.
@property(nonatomic, retain, nullable) PDFAnnotationPopup* popup PDFKIT_DEPRECATED(10_5, 10_12);

// Indicates whether the annotation should be displayed on screen (depending upon -[shouldPrint] it may still print).
@property(nonatomic, assign) BOOL shouldDisplay;

// Indicates whether the annotation should be printed or not.
@property(nonatomic, assign) BOOL shouldPrint;

// Optional border or border style that describes how to draw the annotation border (if any).  For the "geometry" 
// annotations (Circle, Ink, Line, Square), the border indicates the line width and whether to draw with a dash pattern 
// or solid pattern.  PDFAnnotationMarkup ignores the border.
// Deprecated in favor of [setValue: forKey:] methods
@property(nonatomic, retain, nullable) PDFBorder* border PDFKIT_DEPRECATED(10_4, 10_12);

// For many annotations ("Circle", "Square") the stroke color.  Used for other annotations as well.
@property(nonatomic, retain) PDFKitPlatformColor* color PDFKIT_DEPRECATED(10_4, 10_12);

// Optional action performed when a user releases the mouse within an annotation. PDF readers ignore actions except 
// for those associated with Link or button Widget annotations. 
@property(nonatomic, retain, nullable) PDFAction* mouseUpAction PDFKIT_DEPRECATED(10_5, 10_12);

// A string of text associated with an annotation. Often displayed in a window when the annotation is clicked on 
// ("FreeText" and "Text" especially).
@property(nonatomic, retain, nullable) NSString* contents PDFKIT_DEPRECATED(10_5, 10_12);

// String used for tooltips.  The base class returns [self contents], sub-classes may override as appropriate.
@property(nonatomic, readonly, nullable) NSString* toolTip PDFKIT_DEPRECATED(10_5, 10_12);

// Returns YES if the annotation has an appearance stream.  Annotations with appearance streams are drawn using their 
// stream. As a result setting many parameters (like -[setColor:] above) will have no visible effect.
@property(nonatomic, readonly) BOOL hasAppearanceStream;

// All appearance streams for the target annotation are removed.  Without an appearance stream, annotations are drawn 
// strictly according to their parameters (color, border, font, etc.).  When a PDF is saved, PDF Kit will always 
// write out an appearance stream(s) for each annotation.  If the PDF is reloaded, you will need to remove the 
// appearance streams in order to continue to edit the annotations parameters.
- (void) removeAllAppearanceStreams PDFKIT_DEPRECATED(10_5, 10_12);

// -------- drawing

// Draw method.  Draws in page-space relative to origin of "box" passed in.
- (void) drawWithBox: (PDFDisplayBox) box PDFKIT_DEPRECATED(10_4, 10_12);

// Draw method.  Draws in page-space relative to origin of "box" passed in and to the given context
- (void) drawWithBox: (PDFDisplayBox) box inContext: (CGContextRef) context PDFKIT_AVAILABLE(10_12);

// -------- attribute mutations

// Allows you to set a key-value pair in this annotation's dictionary. Returns true on successful
// assignment, false on error. Key must be valid for a PDF annotation's object type, and must have
// a value that is acceptable for the key type (for example, the key "/C" expects an array of 0, 1,
// 3, or 4 elements, with each element being a floating-point number in the range of 0.0 - 1.0 ).
- (BOOL)setValue:(id)value forAnnotationKey:(NSString*)key PDFKIT_AVAILABLE(10_12);
- (BOOL)setBoolean:(BOOL)value forAnnotationKey:(NSString*)key PDFKIT_AVAILABLE(10_12);
- (BOOL)setRect:(PDFRect)value forAnnotationKey:(NSString*)key PDFKIT_AVAILABLE(10_12);

// Retrieves a deep copy of the key-value pair based on the given key; key can either be
// from the keys kPDFAnnotationKey_*, or an appropriate string from the PDF specification
- (nullable id)valueForAnnotationKey:(NSString*)key PDFKIT_AVAILABLE(10_12);

// Remove the key-value pair from the annotation dictionary. Returns true on successful removal.
- (void)removeValueForAnnotationKey:(NSString*)key PDFKIT_AVAILABLE(10_12);

@end

NS_ASSUME_NONNULL_END
