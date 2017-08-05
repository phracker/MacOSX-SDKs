// =====================================================================================================================
//  PDFAnnotationChoiceWidget.h
// =====================================================================================================================


#import <PDFKit/PDFKitPlatform.h>

#import <PDFKit/PDFAnnotation.h>

@class PDFAnnotationChoiceWidgetPrivateVars;

NS_CLASS_DEPRECATED_MAC(10_5, 10_12, "Use the PDFAnnotation class directly, setting properties via kPDFAnnotationKey_* keys using method [setValue:forAnnotationKey:]")
@interface PDFAnnotationChoiceWidget : PDFAnnotation <NSCopying>
{
@private
    PDFAnnotationChoiceWidgetPrivateVars *_private2;
}

// -------- accessors

// The string value associated with the widget.
- (NSString *) stringValue;
- (void) setStringValue: (NSString *) value;

// Background color characteristics.
- (PDFKitPlatformColor *) backgroundColor;
- (void) setBackgroundColor: (PDFKitPlatformColor *) color;

// Font characteristics.
- (PDFKitPlatformFont *) font;
- (void) setFont: (PDFKitPlatformFont *) font;

// Font color characteristics.
- (PDFKitPlatformColor *) fontColor;
- (void) setFontColor: (PDFKitPlatformColor *) color;

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
