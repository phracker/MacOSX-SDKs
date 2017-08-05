// =====================================================================================================================
//  PDFAnnotationButtonWidget.h
// =====================================================================================================================


#import <PDFKit/PDFKitPlatform.h>

#import <PDFKit/PDFAnnotation.h>


@class PDFAnnotationButtonWidgetPrivateVars;


// Type of control.
NS_ENUM_DEPRECATED_MAC(10_4, 10_12)
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

NS_CLASS_DEPRECATED_MAC(10_4, 10_12, "Use the PDFAnnotation class directly, setting properties via kPDFAnnotationKey_* keys using method [setValue:forAnnotationKey:]")
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

- (BOOL) isHighlighted;

- (void) setHighlighted: (BOOL) flag;
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

// Label for the button.  Applies to kPDFWidgetPushButtonControl only.
- (NSString *) caption;
- (void) setCaption: (NSString *) name;

// Internal name for the field (optional).  Used for ResetForm actions.
- (NSString *) fieldName;
- (void) setFieldName: (NSString *) name;

// String required for kPDFWidgetRadioButtonControl and kPDFWidgetCheckBoxControl Widgets. This string is the label for 
// the 'on' state for the widget (the 'off' state is always labeled "Off").  For a single checkbox, a value of "On" is 
// adequate.  With multiple grouped radio buttons however you want to assign unique names such as "Married", "Single", 
// and "Widowed" (for example - and for this example, all radio buttons would share a field name such as 
// "MaritalStatus").
- (NSString *) onStateValue;
- (void) setOnStateValue: (NSString *) name;

@end
