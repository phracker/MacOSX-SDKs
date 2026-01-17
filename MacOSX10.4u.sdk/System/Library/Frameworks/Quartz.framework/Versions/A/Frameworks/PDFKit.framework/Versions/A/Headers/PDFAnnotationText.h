// ======================================================================================================================
//  PDFAnnotationText.h
// ======================================================================================================================


#import "PDFAnnotation.h"


// Icon that appears indicating text annotaion pop-up.
typedef int PDFTextAnnotationIconType;

enum
{
    kPDFTextAnnotationIconComment = 0, 
    kPDFTextAnnotationIconKey = 1, 
    kPDFTextAnnotationIconNote = 2, 
    kPDFTextAnnotationIconHelp = 3, 
    kPDFTextAnnotationIconNewParagraph = 4, 
    kPDFTextAnnotationIconParagraph = 5, 
    kPDFTextAnnotationIconInsert = 6
};

@class PDFAnnotationTextPrivateVars;

@interface PDFAnnotationText : PDFAnnotation
{
@private
    PDFAnnotationTextPrivateVars *_pdfPriv2;
}

// Whether the pop-up window displaying the text is open or closed. This is used merely for storage as the 
// PDFAnnotationText does not open a window.
- (BOOL) windowIsOpen;
- (void) setWindowIsOpen: (BOOL) isOpen;

// The type of icon displayed in the PDF.  Supported icons: "Comment", "Key", "Note", "Help", "NewParagraph", 
// "Paragraph" and "Insert".
- (PDFTextAnnotationIconType) iconType;
- (void) setIconType: (PDFTextAnnotationIconType) type;
@end
