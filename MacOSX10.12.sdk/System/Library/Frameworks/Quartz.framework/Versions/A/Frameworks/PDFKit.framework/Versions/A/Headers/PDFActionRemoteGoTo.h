// =====================================================================================================================
//  PDFActionRemoteGoTo.h
// =====================================================================================================================


#import <PDFKit/PDFKitPlatform.h>

#import <PDFKit/PDFAction.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFActionRemoteGoToPrivateVars;

NS_CLASS_AVAILABLE_MAC(10_5)
@interface PDFActionRemoteGoTo : PDFAction <NSCopying>
{
@private
    PDFActionRemoteGoToPrivateVars *_private2;
}

// As with the calls below, note that PDFActionRemoteGoTo uses a zero-based page index and not a PDFPage object.
// This simplifies dealing with remote destinations for documents that may not be instantiated.
- (nullable instancetype) initWithPageIndex: (NSUInteger) pageIndex atPoint: (PDFPoint) point fileURL: (NSURL *) url;

// Get and set the page index (zero-based) referenced by the action.
@property(nonatomic, assign) NSUInteger pageIndex;

// Get and set thepoint on the above page referenced by the action.  Just like PDFDestination a value of 
// kPDFDestinationUnspecifiedValue for the x or the y of the point indicates that no position is specified.
@property(nonatomic, assign) PDFPoint point;

// Get and set the URL of the document referenced from the action.
@property(nonatomic, retain) NSURL* URL;

@end

NS_ASSUME_NONNULL_END
