// =====================================================================================================================
//  PDFAnnotationText.h
// =====================================================================================================================


#import <AppKit/AppKit.h>
#import <PDFKit/PDFAnnotation.h>


@class PDFAnnotationTextPrivateVars;


// Icon that appears indicating text annotaion pop-up.
typedef NSInteger PDFTextAnnotationIconType;
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


@interface PDFAnnotationText : PDFAnnotation <NSCopying, NSCoding>
{
@private
    PDFAnnotationTextPrivateVars *_pdfPriv2;
}


// The type of icon displayed in the PDF.  Supported icons: "Comment", "Key", "Note", "Help", "NewParagraph", 
// "Paragraph" and "Insert".
- (PDFTextAnnotationIconType) iconType;
- (void) setIconType: (PDFTextAnnotationIconType) type;
@end
