/*
        NSPDFImageRep.h
        Application Kit
        Copyright (c) 1999-2011, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSImageRep.h>

@interface NSPDFImageRep : NSImageRep
{
  @private
    NSData* _pdfData;
    int     _reserved1;
    int     _reserved2;

    id      _private;
}

+ (id)imageRepWithData:(NSData*)pdfData;
- (id)initWithData:(NSData*)pdfData;

- (NSData*)PDFRepresentation;
- (NSRect)bounds;			// for current page

- (void) setCurrentPage:(NSInteger)page;	// 0 based
- (NSInteger)  currentPage;
- (NSInteger)  pageCount;

@end

