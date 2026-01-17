/*
	NSEPSImageRep.h
	Application Kit
	Copyright (c) 1994-2018, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSImageRep.h>

NS_ASSUME_NONNULL_BEGIN

@class NSPDFImageRep;

@interface NSEPSImageRep : NSImageRep {
    /*All instance variables are private*/
    NSPoint _bBoxOrigin APPKIT_IVAR;
    NSData *_epsData APPKIT_IVAR;
    NSPDFImageRep* _pdfImageRep APPKIT_IVAR;
}

+ (nullable instancetype)imageRepWithData:(NSData *)epsData;	/* Convenience of initWithData: */
- (nullable instancetype)initWithData:(NSData *)epsData;

/* prepareGState is unused */
- (void)prepareGState NS_DEPRECATED_MAC(10_0, 10_10);

@property (readonly, copy) NSData *EPSRepresentation;

@property (readonly) NSRect boundingBox;

@end

NS_ASSUME_NONNULL_END

