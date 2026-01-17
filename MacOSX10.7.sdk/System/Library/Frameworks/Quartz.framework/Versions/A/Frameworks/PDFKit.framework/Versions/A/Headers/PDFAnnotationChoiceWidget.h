// =====================================================================================================================
//  PDFAnnotationChoiceWidget.h
// =====================================================================================================================


#import <AppKit/AppKit.h>
#import <PDFKit/PDFAnnotation.h>


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

@class PDFAnnotationChoiceWidgetPrivateVars;


@interface PDFAnnotationChoiceWidget : PDFAnnotation <NSCopying>
{
@private
    PDFAnnotationChoiceWidgetPrivateVars *_pdfPriv2;
}

// -------- accessors

// The string value associated with the widget.
- (NSString *) stringValue;
- (void) setStringValue: (NSString *) value;

// Background color characteristics.
- (NSColor *) backgroundColor;
- (void) setBackgroundColor: (NSColor *) color;

// Font characteristics.
- (NSFont *) font;
- (void) setFont: (NSFont *) font;

// Font color characteristics.
- (NSColor *) fontColor;
- (void) setFontColor: (NSColor *) color;

// Widget annotations backed by form data have (internal) field names with which to associate a value or data.
- (NSString *) fieldName;
- (void) setFieldName: (NSString *) name;

// There are two flavors of Choice widget annotations, lists and pop-up menus. These methods allow you to differentiate.
- (BOOL) isListChoice;
- (void) setIsListChoice: (BOOL) isList;

// The choices are an array of strings indicating the options (items) in either a list or pop-up menu.
- (NSArray *) choices;
- (void) setChoices: (NSArray *) options;

@end

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
