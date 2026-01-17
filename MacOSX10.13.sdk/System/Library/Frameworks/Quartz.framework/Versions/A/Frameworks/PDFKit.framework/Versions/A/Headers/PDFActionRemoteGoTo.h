//
//  PDFActionRemoteGoTo.h
//  Copyright © 2016 Apple. All rights reserved.
//
//  PDFActionRemoteGoTo is an interaction event tied with an annotation. This action
//  is the same action type as PDFActionGoTo, but references another document, allowing
//  you to jump to specific pages or positions in other PDF files.
//

#import <PDFKit/PDFKitPlatform.h>

#import <PDFKit/PDFAction.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFActionRemoteGoToPrivateVars;

PDFKIT_CLASS_AVAILABLE(10_5, 11_0)
@interface PDFActionRemoteGoTo : PDFAction <NSCopying>
{
@private
    PDFActionRemoteGoToPrivateVars *_private2;
}

// As with the calls below, note that PDFActionRemoteGoTo uses a zero-based page index and not a PDFPage object.
// This simplifies dealing with remote destinations for documents that may not be instantiated.
- (instancetype)initWithPageIndex:(NSUInteger)pageIndex atPoint:(PDFPoint)point fileURL:(NSURL *)url NS_DESIGNATED_INITIALIZER;

// Get and set the page index (zero-based) referenced by the action.
@property (nonatomic) NSUInteger pageIndex;

// Get and set the point on the above page referenced by the action.  Just like PDFDestination a value of 
// kPDFDestinationUnspecifiedValue for the x or the y of the point indicates that no position is specified.
@property (nonatomic) PDFPoint point;

// Get and set the URL of the document referenced from the action.
@property (nonatomic, copy) NSURL *URL;

@end

NS_ASSUME_NONNULL_END
