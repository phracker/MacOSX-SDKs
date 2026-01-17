// ======================================================================================================================
//  PDFActionURL.h
// =====================================================================================================================


#import <AppKit/AppKit.h>
#import <PDFKit/PDFAction.h>


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

@class PDFActionURLPrivateVars;


@interface PDFActionURL : PDFAction <NSCopying>
{
@private
    PDFActionURLPrivateVars *_pdfPriv2;
}

- (id) initWithURL: (NSURL *) url;
- (NSURL *) URL;
- (void) setURL: (NSURL *) url;
@end

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
