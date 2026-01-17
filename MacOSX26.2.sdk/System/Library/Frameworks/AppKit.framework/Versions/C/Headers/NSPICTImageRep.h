/*
        NSPICTImageRep.h
        Application Kit
        Copyright (c) 1997-2024, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSImageRep.h>
#import <AppKit/AppKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

@interface NSPICTImageRep : NSImageRep

+ (nullable instancetype)imageRepWithData:(NSData *)pictData;
- (nullable instancetype)initWithData:(NSData *)pictData;

@property (readonly, copy) NSData *PICTRepresentation;
@property (readonly) NSRect boundingBox;

@end

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
