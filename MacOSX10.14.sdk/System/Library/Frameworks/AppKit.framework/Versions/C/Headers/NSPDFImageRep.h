/*
        NSPDFImageRep.h
        Application Kit
        Copyright (c) 1999-2018, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSImageRep.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSPDFImageRep : NSImageRep
{
  @private
    NSData *_pdfData APPKIT_IVAR;
#if !__OBJC2__
    int     _reserved1 __unused APPKIT_IVAR;
    int     _reserved2 __unused APPKIT_IVAR;
#endif /* !__OBJC2__ */
    id      _private APPKIT_IVAR;
}

+ (nullable instancetype)imageRepWithData:(NSData *)pdfData;
- (nullable instancetype)initWithData:(NSData *)pdfData;

@property (readonly, strong) NSData *PDFRepresentation;
@property (readonly) NSRect bounds;			// for current page
@property NSInteger currentPage;	// 0 based
@property (readonly) NSInteger pageCount;

@end

NS_ASSUME_NONNULL_END

