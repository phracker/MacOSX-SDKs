/*
        NSPICTImageRep.h
        Application Kit
        Copyright (c) 1997-2019, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSImageRep.h>

NS_ASSUME_NONNULL_BEGIN
API_UNAVAILABLE_BEGIN(ios)

@interface NSPICTImageRep : NSImageRep

+ (nullable instancetype)imageRepWithData:(NSData *)pictData;
- (nullable instancetype)initWithData:(NSData *)pictData;

@property (readonly, copy) NSData *PICTRepresentation;
@property (readonly) NSRect boundingBox;

@end

API_UNAVAILABLE_END
NS_ASSUME_NONNULL_END
