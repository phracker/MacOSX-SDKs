//
//  PDFDestination.h
//  Copyright © 2016 Apple. All rights reserved.
//
//  PDFDestination represents a dictionary used in annotations, typically as
//  a property for an action. Destinations are a coordinate and zoom factor
//  for a specific page in a document.
//

#import <PDFKit/PDFKitPlatform.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFPage, PDFDestinationPrivate;

// To specify a destination point where you don't care about the x or y value (or either), use this value.
PDFKIT_EXTERN const CGFloat kPDFDestinationUnspecifiedValue PDFKIT_AVAILABLE(10_4, 11_0);

PDFKIT_CLASS_AVAILABLE(10_4, 11_0)
@interface PDFDestination : NSObject <NSCopying>
{
@private
    PDFDestinationPrivate *_private;
}

// -------- initializer

// Initializer. You do not often create PDFDestinations, but usually get them from link annotations or PDFOutline items.
- (instancetype)initWithPage:(PDFPage *)page atPoint:(PDFPoint)point NS_DESIGNATED_INITIALIZER;

// -------- accessors

// The page that the destination refers to (destination page).
@property (nonatomic, weak, readonly) PDFPage *page;

// The destination point on the page above (in page space).
@property (nonatomic, readonly) PDFPoint point;

// Get / set the scale factor the PDF viewer should assume for this destination.
// kPDFDestinationUnspecifiedValue indicates the scale factor is unaffected.
@property (nonatomic) CGFloat zoom PDFKIT_AVAILABLE(10_7, 11_0);

// If the destination passed in is further along in the document than the receiver, we return NSOrderedAscending. If
// the destination passed in precedes the receiver, we return NSOrderedDescending. Otherwise if the destination passed in
// matches the receiver, we return NSOrderedSame. For purposes of comparison, the horizontal component on the point is
// ignored. Also for purposes of comparison, having kPDFDestinationUnspecifiedValue for the vertical component of the
// destination point will be treated as the top point on the destination page.
// An exception will be raised if either destination does not have a page associated with it or if the pages of the two
// destinations are associated with different documents.
- (NSComparisonResult)compare:(PDFDestination *)destination PDFKIT_AVAILABLE(10_5, 11_0);

@end

NS_ASSUME_NONNULL_END
