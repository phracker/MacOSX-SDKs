/*
        NSPDFImageRep.h
        Application Kit
        Copyright (c) 1999-2014, Apple Inc.
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

+ (instancetype)imageRepWithData:(NSData*)pdfData;
- (instancetype)initWithData:(NSData*)pdfData;

@property (readonly, strong) NSData *PDFRepresentation;
@property (readonly) NSRect bounds;			// for current page
@property NSInteger currentPage;	// 0 based
@property (readonly) NSInteger pageCount;

@end

