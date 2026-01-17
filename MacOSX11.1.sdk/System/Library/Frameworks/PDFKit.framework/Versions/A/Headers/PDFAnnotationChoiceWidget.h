//
//  PDFAnnotationChoiceWidget.h
//  Copyright © 2019 Apple. All rights reserved.
//
//  Deprecated annotation class. Use PDFAnnotation directly to create this
//  kind of annotation by setting the subtype to "/Widget" and assign the key-
//  value pair { @"/FT" : @"/Ch" }. Use the helper methods in PDFAnnotationUtilities.h
//  to quickly build an appropriate dictionary for this annotation type.
//

#import <PDFKit/PDFKitPlatform.h>
#import <PDFKit/PDFAnnotation.h>

@class PDFAnnotationChoiceWidgetPrivateVars;

PDFKIT_CLASS_DEPRECATED(10_4, 10_12, NA, NA)
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
