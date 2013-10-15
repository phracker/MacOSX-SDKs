// =====================================================================================================================
//  PDFActionNamed.h
// =====================================================================================================================


#import <AppKit/AppKit.h>
#import <PDFKit/PDFAction.h>


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

@class PDFActionNamedPrivateVars;


// Action names.
typedef NSInteger PDFActionNamedName;
enum
{
    kPDFActionNamedNone = 0, 
    kPDFActionNamedNextPage = 1, 
    kPDFActionNamedPreviousPage = 2, 
    kPDFActionNamedFirstPage = 3, 
    kPDFActionNamedLastPage = 4, 
    kPDFActionNamedGoBack = 5, 
    kPDFActionNamedGoForward = 6, 
    kPDFActionNamedGoToPage = 7, 
    kPDFActionNamedFind = 8, 
    kPDFActionNamedPrint = 9, 
    kPDFActionNamedZoomIn = 10, 
    kPDFActionNamedZoomOut = 11
};


@interface PDFActionNamed : PDFAction <NSCopying>
{
@private
    PDFActionNamedPrivateVars *_pdfPriv2;
}

- (id) initWithName: (PDFActionNamedName) name;
- (PDFActionNamedName) name;
- (void) setName: (PDFActionNamedName) name;

@end

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
