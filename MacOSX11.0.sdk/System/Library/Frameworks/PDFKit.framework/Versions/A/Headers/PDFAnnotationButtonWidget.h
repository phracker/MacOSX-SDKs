//
//  PDFAnnotationButtonWidget.h
//  Copyright © 2019 Apple. All rights reserved.
//
//  Deprecated annotation class. Use PDFAnnotation directly to create this
//  kind of annotation by setting the subtype to "/Widget" and assign the key-
//  value pair { @"/FT" : @"/Btn" }. Use the helper methods in PDFAnnotationUtilities.h
//  to quickly build an appropriate dictionary for this annotation type.
//

#import <PDFKit/PDFKitPlatform.h>
#import <PDFKit/PDFAnnotation.h>

#import <PDFKit/PDFAnnotationUtilities.h>

@class PDFAnnotationButtonWidgetPrivateVars;

PDFKIT_CLASS_DEPRECATED(10_4, 10_12, NA, NA)
@interface PDFAnnotationButtonWidget : PDFAnnotation <NSCopying>
{
@private
    PDFAnnotationButtonWidgetPrivateVars *_private2;
}

// -------- accessors

- (PDFWidgetControlType) controlType;

- (void) setControlType: (PDFWidgetControlType) type;

- (NSInteger) state;
- (void) setState: (NSInteger) value;

- (PDFKitPlatformColor *) backgroundColor;
- (void) setBackgroundColor: (PDFKitPlatformColor *) color;

// For radio buttons, indicates whether clicking on widget whose state is already On toggles it Off.
- (BOOL) allowsToggleToOff;
- (void) setAllowsToggleToOff: (BOOL) allowOff;

// Font attributes.
- (PDFKitPlatformFont *) font;
- (void) setFont: (PDFKitPlatformFont *) font;
- (PDFKitPlatformColor *) fontColor;
- (void) setFontColor: (PDFKitPlatformColor *) color;

// Label for the button. Applies to kPDFWidgetPushButtonControl only.
- (NSString *) caption;
- (void) setCaption: (NSString *) name;

// Internal name for the field (optional). Used for ResetForm actions.
- (NSString *) fieldName;
- (void) setFieldName: (NSString *) name;

// String required for kPDFWidgetRadioButtonControl and kPDFWidgetCheckBoxControl Widgets. This string is the label for 
// the 'on' state for the widget (the 'off' state is always labeled "Off"). For a single checkbox, a value of "On" is 
// adequate. With multiple grouped radio buttons however you want to assign unique names such as "Married", "Single", 
// and "Widowed" (for example - and for this example, all radio buttons would share a field name such as 
// "MaritalStatus").
- (NSString *) onStateValue;
- (void) setOnStateValue: (NSString *) name;

@end
