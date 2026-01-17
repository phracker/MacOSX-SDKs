/*
	NSEPSImageRep.h
	Application Kit
	Copyright (c) 1994-2019, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSImageRep.h>

NS_ASSUME_NONNULL_BEGIN
API_UNAVAILABLE_BEGIN(ios)

@class NSPDFImageRep;

@interface NSEPSImageRep : NSImageRep

+ (nullable instancetype)imageRepWithData:(NSData *)epsData;	/* Convenience of initWithData: */
- (nullable instancetype)initWithData:(NSData *)epsData;

/* prepareGState is unused */
- (void)prepareGState API_DEPRECATED("", macos(10.0,10.10));

@property (readonly, copy) NSData *EPSRepresentation;

@property (readonly) NSRect boundingBox;

@end

API_UNAVAILABLE_END
NS_ASSUME_NONNULL_END

