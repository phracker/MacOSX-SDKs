// =====================================================================================================================
//  PDFAnnotationText.h
// =====================================================================================================================


#import <PDFKit/PDFKitPlatform.h>
#import <PDFKit/PDFAnnotation.h>

// Icon that appears indicating text annotaion pop-up.
NS_ENUM_DEPRECATED(10_4, 10_12, NA, NA)
typedef NS_ENUM(NSInteger, PDFTextAnnotationIconType)
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

NS_CLASS_DEPRECATED_MAC(10_4, 10_12, "Use the PDFAnnotation class directly, setting properties via kPDFAnnotationKey_* keys using method [setValue:forAnnotationKey:]")
@interface PDFAnnotationText : PDFAnnotation <NSCopying, NSCoding>
{
@private
    PDFAnnotationTextPrivateVars *_private2;
}

// The type of icon displayed in the PDF.  Supported icons: "Comment", "Key", "Note", "Help", "NewParagraph", 
// "Paragraph" and "Insert".
- (PDFTextAnnotationIconType) iconType;
- (void) setIconType: (PDFTextAnnotationIconType) type;

@end
