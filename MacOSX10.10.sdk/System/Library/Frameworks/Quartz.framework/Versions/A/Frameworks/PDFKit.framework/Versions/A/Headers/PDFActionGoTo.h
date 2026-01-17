// =====================================================================================================================
//  PDFActionGoTo.h
// =====================================================================================================================


#import <AppKit/AppKit.h>
#import <PDFKit/PDFAction.h>


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

@class PDFDestination, PDFActionGoToPrivateVars;


@interface PDFActionGoTo : PDFAction <NSCopying>
{
@private
    PDFActionGoToPrivateVars *_pdfPriv2;
}

- (id) initWithDestination: (PDFDestination *) destination;
- (PDFDestination *) destination;
- (void) setDestination: (PDFDestination *) destination;
@end

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
