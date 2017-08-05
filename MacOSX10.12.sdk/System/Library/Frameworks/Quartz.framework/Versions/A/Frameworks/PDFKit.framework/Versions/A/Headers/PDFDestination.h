// =====================================================================================================================
//  PDFDestination.h
// =====================================================================================================================


#import <PDFKit/PDFKitPlatform.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFPage, PDFDestinationPrivate;

// To specify a destination point where you don't care about the x or y value (or either), use this value.
#define kPDFDestinationUnspecifiedValue FLT_MAX

NS_CLASS_AVAILABLE_MAC(10_4)
@interface PDFDestination : NSObject <NSCopying>
{
@private
    PDFDestinationPrivate* _private;
}

// -------- initializer

// Initializer.  You do not often create PDFDestinations but get them from link annotations or PDF outline items.
- (instancetype) initWithPage: (PDFPage *) page atPoint: (PDFPoint) point;

// -------- accessors

// Page the destination refers to (destination page).
@property(nonatomic, weak, readonly) PDFPage* page;

// Destination point on the page above (in page space).
@property(nonatomic, readonly) PDFPoint point;

// Get / set the scale factor the PDF viewer should assume for this destination.
// kPDFDestinationUnspecifiedValue indicates the scale factor is unaffected.
@property(nonatomic, assign) CGFloat zoom PDFKIT_AVAILABLE(10_7);

// If destination passed in is further along in the document than the receiver we return NSOrderedAscending.  If 
// destination passed in precedes receiver we return NSOrderedDescending.  Otherwise if the desitnation passed in 
// matches the receiver NSOrderedSame is returned.  For purposes of comparison the horizontal component on the point is 
// ignored.  Also for purposes of comparison, kPDFDestinationUnspecifiedValue for the vertical component of the 
// destination point will be treated as the top point on the destination page.
// Will raise an exception if either destination does not have a page associated with it or if the pages of the two 
// destinations are assciated with different documents.
- (NSComparisonResult) compare: (PDFDestination *) destination PDFKIT_AVAILABLE(10_5);

@end

NS_ASSUME_NONNULL_END
