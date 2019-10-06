/*
        NSPDFImageRep.h
        Application Kit
        Copyright (c) 1999-2019, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSImageRep.h>

NS_ASSUME_NONNULL_BEGIN
API_UNAVAILABLE_BEGIN(ios)

@interface NSPDFImageRep : NSImageRep

+ (nullable instancetype)imageRepWithData:(NSData *)pdfData;
- (nullable instancetype)initWithData:(NSData *)pdfData;

@property (readonly, strong) NSData *PDFRepresentation;
@property (readonly) NSRect bounds;			// for current page
@property NSInteger currentPage;	// 0 based
@property (readonly) NSInteger pageCount;

@end

API_UNAVAILABLE_END
NS_ASSUME_NONNULL_END

