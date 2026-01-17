// =====================================================================================================================
//  PDFAnnotationButtonWidget.h
// =====================================================================================================================


#import <AppKit/AppKit.h>
#import <PDFKit/PDFAnnotation.h>


@class PDFAnnotationButtonWidgetPrivateVars;


// Type of control.
typedef NSInteger PDFWidgetControlType;
enum
{
	kPDFWidgetUnknownControl = -1, 
    kPDFWidgetPushButtonControl = 0, 
    kPDFWidgetRadioButtonControl = 1, 
    kPDFWidgetCheckBoxControl = 2
};


@interface PDFAnnotationButtonWidget : PDFAnnotation <NSCopying>
{
@private
    PDFAnnotationButtonWidgetPrivateVars *_pdfPriv2;
}

// -------- accessors
- (PDFWidgetControlType) controlType;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

- (void) setControlType: (PDFWidgetControlType) type;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

- (NSInteger) state;
- (void) setState: (NSInteger) value;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

- (BOOL) isHighlighted;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

- (void) setHighlighted: (BOOL) flag;
- (NSColor *) backgroundColor;
- (void) setBackgroundColor: (NSColor *) color;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// For radio buttons, indicates whether clicking on widget whose state is already On toggles it Off.
- (BOOL) allowsToggleToOff;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6

- (void) setAllowsToggleToOff: (BOOL) allowOff;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Font attributes.
- (NSFont *) font;
- (void) setFont: (NSFont *) font;
- (NSColor *) fontColor;
- (void) setFontColor: (NSColor *) color;

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

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5


@end
