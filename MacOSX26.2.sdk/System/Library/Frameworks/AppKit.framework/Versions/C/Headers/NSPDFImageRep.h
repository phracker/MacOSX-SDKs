/*
        NSPDFImageRep.h
        Application Kit
        Copyright (c) 1999-2024, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSImageRep.h>
#import <AppKit/AppKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

@interface NSPDFImageRep : NSImageRep

+ (nullable instancetype)imageRepWithData:(NSData *)pdfData;
- (nullable instancetype)initWithData:(NSData *)pdfData;

@property (readonly, strong) NSData *PDFRepresentation;
@property (readonly) NSRect bounds;			// for current page
@property NSInteger currentPage;	// 0 based
@property (readonly) NSInteger pageCount;

@end

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)

