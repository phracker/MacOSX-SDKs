// =====================================================================================================================
//  PDFAction.h
// =====================================================================================================================


#import <AppKit/AppKit.h>


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

@class PDFActionPrivateVars;


@interface PDFAction : NSObject <NSCopying>
{
@private
    PDFActionPrivateVars *_pdfPriv;
}

// Type of action.  These won't always correspond to the PDFAction subclass in the way you might expect.  For example, 
// a PDFActionURL may return "URI" or "Launch" depending upon the original action (as defined in thePDF spec. - for 
// the PDFKit API we decided to handle the two actions within the same class and also use the more familiar 'URL' term 
// rather than 'URI').
- (NSString *) type;

@end

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
