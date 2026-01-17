// =====================================================================================================================
//  PDFDestination.h
// =====================================================================================================================


#import <AppKit/AppKit.h>


@class PDFPage, PDFDestinationPrivateVars;


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// To specify a destination point where you don't care about the x or y value (or either), use this value.
#define kPDFDestinationUnspecifiedValue		FLT_MAX

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5


@interface PDFDestination : NSObject <NSCopying>
{
@private
    PDFDestinationPrivateVars *_pdfPriv;
}

// -------- initializer

// Initializer.  You do not often create PDFDestinations but get them from link annotations or PDF outline items.
- (id) initWithPage: (PDFPage *) page atPoint: (NSPoint) point;

// -------- accessors

// Page the destination refers to (destination page).
- (PDFPage *) page;

// Destination point on the page above (in page space).
- (NSPoint) point;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_7

// Returns the scale factor the PDF viewer should assume for this destination.
// kPDFDestinationUnspecifiedValue indicates the scale factor is unaffected.
- (CGFloat) zoom;

// Specify the scale factor the PDF viewer should assume for this destination.
// kPDFDestinationUnspecifiedValue indicates the scale factor is unaffected.
- (void) setZoom: (CGFloat) zoom;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_7

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// If destination passed in is further along in the document than the receiver we return NSOrderedAscending.  If 
// destination passed in precedes receiver we return NSOrderedDescending.  Otherwise if the desitnation passed in 
// matches the receiver NSOrderedSame is returned.  For purposes of comparison the horizontal component on the point is 
// ignored.  Also for purposes of comparison, kPDFDestinationUnspecifiedValue for the vertical component of the 
// destination point will be treated as the top point on the destination page.
// Will raise an exception if either destination does not have a page associated with it or if the pages of the two 
// destinations are assciated with different documents.
- (NSComparisonResult) compare: (PDFDestination *) destination;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5


@end
