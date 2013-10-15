// =====================================================================================================================
//  PDFActionRemoteGoTo.h
// =====================================================================================================================


#import <AppKit/AppKit.h>
#import <PDFKit/PDFAction.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

@class PDFActionRemoteGoToPrivateVars;


@interface PDFActionRemoteGoTo : PDFAction <NSCopying>
{
@private
    PDFActionRemoteGoToPrivateVars *_pdfPriv2;
}

// As with the calls below, note that PDFActionRemoteGoTo uses a zero-based page index and not a PDFPage object.
// This simplifies dealing with remote destinations for documents that may not be instantiated.
- (id) initWithPageIndex: (NSUInteger) pageIndex atPoint: (NSPoint) point fileURL: (NSURL *) url;

// Get and set the page index (zero-based) referenced by the action.
- (NSUInteger) pageIndex;
- (void) setPageIndex: (NSUInteger) pageIndex;

// Get and set thepoint on the above page referenced by the action.  Just like PDFDestination a value of 
// kPDFDestinationUnspecifiedValue for the x or the y of the point indicates that no position is specified.
- (NSPoint) point;
- (void) setPoint: (NSPoint) point;

// Get and set the URL of the document referenced fro the action.
- (NSURL *) URL;
- (void) setURL: (NSURL *) url;
@end

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
