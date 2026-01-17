//
//  PDFAnnotation.h
//  Copyright © 2019 Apple. All rights reserved.
//
//  PDFAnnotation is a wrapper class of all annotation types for a PDF document.
//  It is a container of key-value pairs that map directly to the PDF file format, defined
//  in the Adobe PDF Specification (file format version 1.7). You can manipulate
//  properties of an annotation by either assigning key-value pairs, where keys are always
//  strings defined in the specification and listed below (example: PDFAnnotationKeyFlags).
//  You can also replace existing key-values in the PDFAnnotation dictionary, or remove them.
//  Value types vary based on what the key is. For example, the value for a color key can either
//  be an array of numbers (0 for no color, 1 for gray, 3 for RGB, 4 for CMYK) or can be an
//  NSColor or UIColor instance. Some keys require complex values, typically as an array or
//  dictionaries of objects. PDFKit provides some classes as a convenience for these complex
//  type: PDFBorder, PDFAction (its subclasses), PDFDestination. Note that there are also
//  helper category functions that are specialized for many of the legacy PDFAnnotation
//  subclasses. You can find this in PDFAnnotationUtilities.h
//
//  Note that the preferred constructor for PDFAnnotation is -[initWithBounds:forType:withProperties:],
//  and at a minimum you must set bounds and type for the annotation. Calling -[init] will raise an
//  exception. To add an annotation to a page, you must do so via -[PDFPage addAnnotation:] on your
//  desired page. You may not change annotation subtype at runtime. If you want to change annotation
//  subtype, remove the annotation and add a new instance. If you use the deprecated constructor
//  -[initWithBounds:], you may set the annotation subtype only once. Any future assignments of subtype
//  will be ignored and produce a warning.
//
//  Note that PDFAnnotation can render any annotation with a content-stream entry in the annotation's
//  dictionary, though some are supported natively based on their annotation dictionary. Supported
//  annotations have their subtype declared via NSString defined in PDFAnnotationUtilities.h
//  using the naming convention "PDFAnnotationSubtypeX", where X is the subtype. Those not in
//  this list will only draw if there is an appearance stream.
//
//  Adobe PDF Specification (1.7) defines in Table 8.15 "Entries common to all annotation
//  dictionaries" 14 common properties among all annotations. 2-4 are required, the rest are
//  optional. PDFKit supports 13 of these annotations. For all common properties and each
//  annotation's specific properties, we define them as enumerations and enum-mapped strings at
//  the top of this file.
//
//  You can activate logging of any annotation key-value assignments that fails by setting the
//  environment variable "PDFKIT_LOG_ANNOTATIONS" to any value.
//

#import <PDFKit/PDFKitPlatform.h>
#import <PDFKit/PDFPage.h>
#import <PDFKit/PDFAction.h>

NS_ASSUME_NONNULL_BEGIN

// All PDF annotation subtypes that PDFKit can render: based on Adobe PDF specification, Table 8.20: Annotation types.
// Annotation subtypes not supported: Polygon, PolyLine, Squiggly, Caret, Caret, FileAttachment,
// Sound, Movie, Screen, PrinterMark, TrapNet, Watermark, 3D, Rect.
typedef NSString* const PDFAnnotationSubtype NS_STRING_ENUM;

// Common keys used for all annotations
// Adobe PDF Specification (1.7), Table 8.15: Entries common to all annotation dictionaries
typedef NSString* const PDFAnnotationKey NS_STRING_ENUM;

PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyAppearanceDictionary PDFKIT_AVAILABLE(10_13, 11_0);              // "/AP": Dictionary
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyAppearanceState PDFKIT_AVAILABLE(10_13, 11_0);                   // "/AS": Name
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyBorder PDFKIT_AVAILABLE(10_13, 11_0);                            // "/Border": Array of Integers; or a PDFBorder object
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyColor PDFKIT_AVAILABLE(10_13, 11_0);                             // "/C": Array of Floats; or a PDFKitPlatformColor object
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyContents PDFKIT_AVAILABLE(10_13, 11_0);                          // "/Contents": String
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyFlags PDFKIT_AVAILABLE(10_13, 11_0);                             // "/F": Integer
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyDate PDFKIT_AVAILABLE(10_13, 11_0);                              // "/M": Date or String
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyName PDFKIT_AVAILABLE(10_13, 11_0);                              // "/NM": String
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyPage PDFKIT_AVAILABLE(10_13, 11_0);                              // "/P": Dictionary; or a PDFPage object.
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyRect PDFKIT_AVAILABLE(10_13, 11_0);                              // "/Rect": CGRect
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeySubtype PDFKIT_AVAILABLE(10_13, 11_0);                           // "/Subtype": Name (See Table 8.20: Annotation types)

// Additional annotation extensions...
// Adobe PDF Specification (1.7), Table 8.23: Additional entries specific to a text annotation
// Adobe PDF Specification (1.7), Table 8.24: Additional entries specific to a link annotation
// Adobe PDF Specification (1.7), Table 8.25: Additional entries specific to a free text annotation
// Adobe PDF Specification (1.7), Table 8.26: Additional entries specific to a line annotation
// Adobe PDF Specification (1.7), Table 8.28: Additional entries specific to a square or circle annotation
// Adobe PDF Specification (1.7), Table 8.30: Additional entries specific to text markup annotations (highlight, underline, strikeout)
// Adobe PDF Specification (1.7), Table 8.32: Additional entries specific to a rubber stamp annotation
// Adobe PDF Specification (1.7), Table 8.33: Additional entries specific to an ink annotation
// Adobe PDF Specification (1.7), Table 8.34: Additional entries specific to a pop-up annotation
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyAction PDFKIT_AVAILABLE(10_13, 11_0);                            // "/A": Dictionary; or a PDFAction object
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyAdditionalActions PDFKIT_AVAILABLE(10_13, 11_0);                 // "/AA": Dictionary; or a PDFAction object
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyBorderStyle PDFKIT_AVAILABLE(10_13, 11_0);                       // "/BS": Dictionary
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyDefaultAppearance PDFKIT_AVAILABLE(10_13, 11_0);                 // "/DA": String
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyDestination PDFKIT_AVAILABLE(10_13, 11_0);                       // "/Dest": Array, Name, or String
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyHighlightingMode PDFKIT_AVAILABLE(10_13, 11_0);                  // "/H": Name
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyInklist PDFKIT_AVAILABLE(10_13, 11_0);                           // "/Inklist": Array of Arrays (each array representing a stroked path)
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyInteriorColor PDFKIT_AVAILABLE(10_13, 11_0);                     // "/IC": Array of Floats; or a PDFKitPlatformColor object
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyLinePoints PDFKIT_AVAILABLE(10_13, 11_0);                        // "/L": Array of Floats
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyLineEndingStyles PDFKIT_AVAILABLE(10_13, 11_0);                  // "/LE": Array of Strings
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyIconName PDFKIT_AVAILABLE(10_13, 11_0);                          // "/Name": Name
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyOpen PDFKIT_AVAILABLE(10_13, 11_0);                              // "/Open": Boolean
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyParent PDFKIT_AVAILABLE(10_13, 11_0);                            // "/Parent": Dictionary; or a PDFAnnotation object
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyPopup PDFKIT_AVAILABLE(10_13, 11_0);                             // "/Popup": Dictionary; or a PDFAnnotation object of type "Popup"
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyQuadding PDFKIT_AVAILABLE(10_13, 11_0);                          // "/Q": Integer
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyQuadPoints PDFKIT_AVAILABLE(10_13, 11_0);                        // "/QuadPoints": Array of Floats
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyTextLabel PDFKIT_AVAILABLE(10_13, 11_0);                         // "/T": String

// Widget annotation extensions
// Adobe PDF Specification (1.7), Table 8.39: Additional entries specific to a widget annotation
// Adobe PDF Specification (1.7), Table 8.40: Entries in an appearance characteristics dictionary
// Adobe PDF Specification (1.7), Table 8.69: Entries common to all field dictionaries
// Adobe PDF Specification (1.7), Table 8.76: Additional entry specific to check box and radio button fields
// Adobe PDF Specification (1.7), Table 8.78: Additional entry specific to a text field
// Adobe PDF Specification (1.7), Table 8.80: Additional entries specific to a choice field
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyWidgetDownCaption PDFKIT_AVAILABLE(10_13, 11_0);                 // "/AC": String
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyWidgetBorderColor PDFKIT_AVAILABLE(10_13, 11_0);                 // "/BC": Array of Floats; or a PDFKitPlatformColor object
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyWidgetBackgroundColor PDFKIT_AVAILABLE(10_13, 11_0);             // "/BG": Array of Floats; or a PDFKitPlatformColor object
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyWidgetCaption PDFKIT_AVAILABLE(10_13, 11_0);                     // "/CA": String
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyWidgetDefaultValue PDFKIT_AVAILABLE(10_13, 11_0);                // "/DV": (various)
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyWidgetFieldFlags PDFKIT_AVAILABLE(10_13, 11_0);                  // "/Ff": Integer
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyWidgetFieldType PDFKIT_AVAILABLE(10_13, 11_0);                   // "/FT": Name
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyWidgetAppearanceDictionary PDFKIT_AVAILABLE(10_13, 11_0);        // "/MK": Dictionary; or PDFAppearanceCharacteristics object
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyWidgetMaxLen PDFKIT_AVAILABLE(10_13, 11_0);                      // "/MaxLen": Integer
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyWidgetOptions PDFKIT_AVAILABLE(10_13, 11_0);                     // "/Opt": Array (each element is either a string, or an array of two strings)
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyWidgetRotation PDFKIT_AVAILABLE(10_13, 11_0);                    // "/R": Integer
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyWidgetRolloverCaption PDFKIT_AVAILABLE(10_13, 11_0);             // "/RC": String
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyWidgetTextLabelUI PDFKIT_AVAILABLE(10_13, 11_0);                 // "/TU": String
PDFKIT_EXTERN PDFAnnotationKey PDFAnnotationKeyWidgetValue PDFKIT_AVAILABLE(10_13, 11_0);                       // "/V": (various)

@class PDFAction, PDFBorder, PDFPage, PDFAnnotationPopup, PDFAnnotationPrivateVars;

PDFKIT_CLASS_AVAILABLE(10_4, 11_0)
@interface PDFAnnotation : NSObject <NSCopying, NSCoding>
{
@private
    PDFAnnotationPrivateVars *_private;
}

// This is the base class for all annotations. A PDFAnnotation object by itself is not useful, only subclasses (like 
// PDFAnnotationCircle, PDFAnnotationText) are interesting. In parsing a PDF however, any unknown or unsupported 
// annotations will be represented as this base class.

// -------- initializer

// Create a custom annotation with bounds, a type (PDFAnnotationSubtype), and an (optional) dictionary of annotation properties.
- (instancetype)initWithBounds:(PDFRect)bounds forType:(PDFAnnotationSubtype)annotationType withProperties:(nullable NSDictionary*)properties PDFKIT_AVAILABLE(10_13, 11_0) NS_DESIGNATED_INITIALIZER;

// -------- accessors

// Returns the page the annotation is associated with (may return nil if annotation not associated with a page).
@property (nonatomic, weak, nullable) PDFPage *page;

// Returns the annotation type (called "Subtype" in the PDF specification since "Annot" is the type). Examples include: 
// "Text", "Link", "Line", etc. Required. Note that you are only allowed to set the type of an annotation once.
@property (nonatomic, copy, nullable) NSString *type;

// Required for all annotations. The bounding box in page-space of the annotation.
@property (nonatomic) PDFRect bounds;

// Indicates whether the annotation should be displayed on screen (depending upon -[shouldPrint] it may still print).
@property (nonatomic) BOOL shouldDisplay;

// Indicates whether the annotation should be printed or not.
@property (nonatomic) BOOL shouldPrint;

// Optional (-[modificationDate] may return nil). Modification date of the annotation.
@property (nonatomic, copy, nullable) NSDate *modificationDate PDFKIT_AVAILABLE(10_5, 11_0);

// Optional (-[userName] may return nil). Name of the user who created the annotation.
@property (nonatomic, copy, nullable) NSString *userName PDFKIT_AVAILABLE(10_5, 11_0);

// Optional (-[popup] may return nil). Not used with links or widgets, a popup annotation associated with this
// annotation. The bounds and open state of the popup indicate the placement and open state of the popup window.
#if defined( PDFKIT_PLATFORM_OSX )
@property (nonatomic, strong, nullable) PDFAnnotationPopup *popup PDFKIT_AVAILABLE(10_5, 11_0);
#else
@property (nonatomic, strong, nullable) PDFAnnotation *popup PDFKIT_AVAILABLE(10_5, 11_0);
#endif

// Optional border or border style that describes how to draw the annotation border (if any). For the "geometry"
// annotations (Circle, Ink, Line, Square), the border indicates the line width and whether to draw with a dash pattern
// or solid pattern. PDFAnnotation markup types (Highlight, Strikethrough, Underline) ignores the border.
@property (nonatomic, strong, nullable) PDFBorder *border PDFKIT_AVAILABLE(10_4, 11_0);

// For many annotations ("Circle", "Square") the stroke color. Used for other annotations as well.
@property (nonatomic, copy) PDFKitPlatformColor *color PDFKIT_AVAILABLE(10_4, 11_0);

// A string of text associated with an annotation. Often displayed in a window when the annotation is clicked on
// ("FreeText" and "Text" especially).
@property (nonatomic, copy, nullable) NSString *contents PDFKIT_AVAILABLE(10_5, 11_0);

// Optional action performed when a user clicks / taps an annotation. PDF readers ignore actions except
// for those associated with Link or button Widget annotations.
@property (nonatomic, strong, nullable) PDFAction *action PDFKIT_AVAILABLE(10_5, 11_0);

// Returns YES if the annotation has an appearance stream. Annotations with appearance streams are drawn using their
// stream. As a result setting many parameters (like -[setColor:] above) will have no visible effect.
@property (nonatomic, readonly) BOOL hasAppearanceStream;

// The highlight state dictates how the annotation is drawn. For example, if a user has clicked on a
// "Link" annotation, you should set highlighted to YES and redraw it. When the user lets up, set highlighted to
// NO and redraw again.
@property (nonatomic, getter=isHighlighted) BOOL highlighted PDFKIT_AVAILABLE(10_13, 11_0);

// -------- drawing

// Draw method. Draws in page-space relative to origin of "box" passed in and to the given context
- (void)drawWithBox:(PDFDisplayBox)box inContext:(CGContextRef)context PDFKIT_AVAILABLE(10_12, 11_0);

// -------- attribute mutations

// Allows you to set a key-value pair in this annotation's dictionary. Returns true on successful
// assignment, false on error. Key must be valid for a PDF annotation's object type, and must have
// a value that is acceptable for the key type. These values can either be an NSString, NSNumber,
// NSArray of strings or numbers, or an NSDictionary of the previously listed types. Some keys expect
// a complex type, for example the key "/C" expects a color in the format of an array of 0, 1, 3,
// or 4 elements, with each element being a floating-point number in the range of 0.0 - 1.0 ). As
// a convenience, these kind of keys will directly accept NSColor / UIColor values. Other convenience
// functions provide similar support can be found in PDFAnnotationUtilities header file. Note that you
// can set the environment variable "PDFKIT_LOG_ANNOTATIONS" to log any key-value assignment failures.
- (BOOL)setValue:(id)value forAnnotationKey:(PDFAnnotationKey)key PDFKIT_AVAILABLE(10_12, 11_0);
- (BOOL)setBoolean:(BOOL)value forAnnotationKey:(PDFAnnotationKey)key PDFKIT_AVAILABLE(10_12, 11_0);
- (BOOL)setRect:(PDFRect)value forAnnotationKey:(PDFAnnotationKey)key PDFKIT_AVAILABLE(10_12, 11_0);

// List all key-value pairs for this annotation; returns a deep copy of all pairs.
// Note that this method will not include a copy of the value for /Parent. This is by design as to avoid
// introduing a memory cycle. If you would like to get the /Parent propery, use -[PDFAnnotation valueForAnnotationKey:]
// with key PDFAnnotationKeyParent.
@property (nonatomic, readonly, copy) NSDictionary *annotationKeyValues PDFKIT_AVAILABLE(10_13, 11_0);

// Retrieves a deep copy of the key-value pair based on the given key; key can either be
// from the keys PDFAnnotationKey, or an appropriate string from the PDF specification.
- (nullable id)valueForAnnotationKey:(PDFAnnotationKey)key PDFKIT_AVAILABLE(10_12, 11_0);

// Remove the key-value pair from the annotation dictionary. Returns true on successful removal.
- (void)removeValueForAnnotationKey:(PDFAnnotationKey)key PDFKIT_AVAILABLE(10_12, 11_0);

@end

#if defined( PDFKIT_PLATFORM_OSX )

@interface PDFAnnotation (PDFAnnotationDeprecated)

// -------- initializer

// Create a custom annotation using a given annotation dictionary, self-assigning it to the (optional) page.
// Use -[initWithBounds:type:properties] instead.
- (instancetype)initWithDictionary:(NSDictionary *)dictionary forPage:(nullable PDFPage *)page PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);

// You should only call this method for the subclasses, otherwise you will get a type of nil Ñ which is not a legal annotation.
// Use -[initWithBounds:type:properties] instead.
- (instancetype)initWithBounds:(PDFRect)bounds PDFKIT_DEPRECATED(10_4, 10_12, NA, NA);

// -------- accessors

// String used for tooltips. The base class returns [self contents], sub-classes may override as appropriate.
@property (nonatomic, readonly, nullable) NSString *toolTip PDFKIT_DEPRECATED(10_5, 10_12, NA, NA);

// Optional action performed when a user releases the mouse within an annotation. PDF readers ignore actions except
// for those associated with Link or button Widget annotations. This has been replaced by -[PDFAnnotation action] and
// -[PDFAnnotation setAction:] methods, which do the same behavior for both mouse-up driven actions and tap-gestures.
@property (nonatomic, strong, nullable) PDFAction *mouseUpAction PDFKIT_DEPRECATED(10_5, 10_13, NA, NA);

// All appearance streams for the target annotation are removed. Without an appearance stream, annotations are drawn
// strictly according to their parameters (color, border, font, etc.). When a PDF is saved, PDFKit will always
// write out an appearance stream(s) for each annotation. If the PDF is reloaded, you will need to remove the
// appearance streams in order to continue to edit the annotations parameters.
- (void)removeAllAppearanceStreams PDFKIT_DEPRECATED(10_5, 10_12, NA, NA);

// -------- drawing

// This method is deprecated in favor of the of the context aware -[PDFAnnotation drawWithBox:inContext:]. If you subclass
// PDFAnnotation, rendering code will first call -[PDFAnnotation drawWithBox:inContext:]. If your subclass does not override
// the context-aware function, this original -[PDFAnnotation drawWithBox:] method will be called.
// Draw method. Draws in page-space relative to origin of "box" passed in.
- (void)drawWithBox:(PDFDisplayBox)box PDFKIT_DEPRECATED(10_4, 10_12, NA, NA);

@end

// These keys are deprecated in favor of the annotation keys as defined by type PDFAnnotationKey at the top of this header file.
// Common keys used for all annotations.

PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_AppearanceDictionary PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);              // "/AP": Dictionary
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_AppearanceState PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                   // "/AS": Name
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_Border PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                            // "/Border": Array of Integers; or a PDFBorder object
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_Color PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                             // "/C": Array of Floats; or a PDFKitPlatformColor object
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_Contents PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                          // "/Contents": String
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_Flags PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                             // "/F": Integer
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_Date PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                              // "/M": Date or String
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_Name PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                              // "/NM": String
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_Page PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                              // "/P": Dictionary; or a PDFPage object.
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_Rect PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                              // "/Rect": CGRect
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_Subtype PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                           // "/Subtype": Name (See Table 8.20: Annotation types)
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_Action PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                            // "/A": Dictionary; or a PDFAction object
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_AdditionalActions PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                 // "/AA": Dictionary; or a PDFAction object
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_BorderStyle PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                       // "/BS": Dictionary
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_DefaultAppearance PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                 // "/DA": String
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_Destination PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                       // "/Dest": Array, Name, or String
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_HighlightingMode PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                  // "/H": Name
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_Inklist PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                           // "/Inklist": Array of Arrays (each array representing a stroked path)
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_InteriorColor PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                     // "/IC": Array of Floats; or a PDFKitPlatformColor object
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_LinePoints PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                        // "/L": Array of Floats
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_LineEndingStyles PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                  // "/LE": Array of Strings
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_IconName PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                          // "/Name": Name
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_Open PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                              // "/Open": Boolean
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_Parent PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                            // "/Parent": Dictionary; or a PDFAnnotation object
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_Popup PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                             // "/Popup": Dictionary; or a PDFAnnotation object of type "Popup"
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_Quadding PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                          // "/Q": Integer
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_QuadPoints PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                        // "/QuadPoints": Array of Floats
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_TextLabel PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                         // "/T": String
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_WidgetDefaultValue PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                // "/DV": (various)
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_WidgetFieldFlags PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                  // "/Ff": Integer
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_WidgetFieldType PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                   // "/FT": Name
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_WidgetAppearanceDictionary PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);        // "/MK": Dictionary; or PDFAppearanceCharacteristics object
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_WidgetMaxLen PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                      // "/MaxLen": Integer
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_WidgetOptions PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                     // "/Opt": Array (each element is either a string, or an array of two strings)
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_WidgetTextLabelUI PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                 // "/TU": String
PDFKIT_EXTERN PDFAnnotationKey kPDFAnnotationKey_WidgetValue PDFKIT_DEPRECATED(10_12, 10_13, NA, NA);                       // "/V": (various)

#endif


NS_ASSUME_NONNULL_END
