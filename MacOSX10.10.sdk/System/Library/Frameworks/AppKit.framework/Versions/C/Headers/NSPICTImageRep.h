/*
        NSPICTImageRep.h
        Application Kit
        Copyright (c) 1997-2014, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSImageRep.h>

@interface NSPICTImageRep : NSImageRep
{
    /*All instance variables are private*/
    NSPoint      _pictOrigin;		/* topLeft of picFrame */
    NSData*      _pictData;
#if !__LP64__
    unsigned int _reserved1;
    unsigned int _reserved2;
#else
    id		 _imageRep;
    NSUInteger   _pictOffset;
    unsigned int _reserved1;
    unsigned int _reserved2;
#endif
}

+ (instancetype)imageRepWithData:(NSData*)pictData;
- (instancetype)initWithData:(NSData*)pictData;

@property (readonly, copy) NSData *PICTRepresentation;
@property (readonly) NSRect boundingBox;

@end
