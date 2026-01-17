// ======================================================================================================================
//  PDFAnnotationButtonWidget.h
// ======================================================================================================================


#import "PDFAnnotation.h"


@class NSColor, PDFAnnotationButtonWidgetPrivateVars;


// Type of control.
typedef int PDFWidgetControlType;

enum
{
	kPDFWidgetUnknownControl = -1, 
    kPDFWidgetPushButtonControl = 0, 
    kPDFWidgetRadioButtonControl = 1, 
    kPDFWidgetCheckBoxControl = 2
};


@interface PDFAnnotationButtonWidget : PDFAnnotation
{
@private
    PDFAnnotationButtonWidgetPrivateVars *_pdfPriv2;
}

// -------- accessors
- (PDFWidgetControlType) controlType;
- (unsigned) parentID;
- (int) state;
- (void) setState: (int) value;
- (void) setHighlighted: (BOOL) flag;
- (NSColor *) backgroundColor;
- (void) setBackgroundColor: (NSColor *) color;

@end
