/*
        NSPICTImageRep.h
        Application Kit
        Copyright (c) 1997-2001, Apple Computer, Inc.
        All rights reserved.
*/

#import <AppKit/NSImageRep.h>

@interface NSPICTImageRep : NSImageRep
{
    /*All instance variables are private*/
    NSPoint      _pictOrigin;		/* topLeft of picFrame */
    NSData*      _pictData;
    void*        _auxilliary;
    unsigned int _reserved;
}

+ (id)imageRepWithData:(NSData*)pictData;
- (id)initWithData:(NSData*)pictData;

- (NSData*) PICTRepresentation;
- (NSRect)  boundingBox;

@end
