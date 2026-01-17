/*
        NSPDFImageRep.h
        Application Kit
        Copyright (c) 1999-2017, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSImageRep.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSPDFImageRep : NSImageRep
{
  @private
    NSData* _pdfData;
    int     _reserved1 __unused;
    int     _reserved2 __unused;

    id      _private;
}

+ (nullable instancetype)imageRepWithData:(NSData*)pdfData;
- (nullable instancetype)initWithData:(NSData*)pdfData;

@property (readonly, strong) NSData *PDFRepresentation;
@property (readonly) NSRect bounds;			// for current page
@property NSInteger currentPage;	// 0 based
@property (readonly) NSInteger pageCount;

@end

NS_ASSUME_NONNULL_END

