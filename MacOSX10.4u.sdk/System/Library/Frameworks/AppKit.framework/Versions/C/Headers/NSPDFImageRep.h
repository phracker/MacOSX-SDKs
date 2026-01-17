/*
        NSPDFImageRep.h
        Application Kit
        Copyright (c) 1999-2005, Apple Computer, Inc.
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

- (void) setCurrentPage:(int)page;	// 0 based
- (int)  currentPage;
- (int)  pageCount;

@end

