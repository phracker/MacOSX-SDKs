/*
	NSEPSImageRep.h
	Application Kit
	Copyright (c) 1994-2014, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSImageRep.h>

@class NSPDFImageRep;

@interface NSEPSImageRep : NSImageRep {
    /*All instance variables are private*/
    NSPoint _bBoxOrigin;
    NSData *_epsData;
    NSPDFImageRep* _pdfImageRep;
}

+ (instancetype)imageRepWithData:(NSData *)epsData;	/* Convenience of initWithData: */
- (instancetype)initWithData:(NSData *)epsData;

/* prepareGState is unused */
- (void)prepareGState NS_DEPRECATED_MAC(10_0, 10_10);

@property (readonly, copy) NSData *EPSRepresentation;

@property (readonly) NSRect boundingBox;

@end

