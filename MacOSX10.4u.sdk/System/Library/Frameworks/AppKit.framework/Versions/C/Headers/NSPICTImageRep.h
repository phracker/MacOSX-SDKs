/*
        NSPICTImageRep.h
        Application Kit
        Copyright (c) 1997-2005, Apple Computer, Inc.
        All rights reserved.
*/

#import <AppKit/NSImageRep.h>

@interface NSPICTImageRep : NSImageRep
{
    /*All instance variables are private*/
    NSPoint      _pictOrigin;		/* topLeft of picFrame */
    NSData*      _pictData;
    unsigned int _reserved1;
    unsigned int _reserved2;
}

+ (id)imageRepWithData:(NSData*)pictData;
- (id)initWithData:(NSData*)pictData;

- (NSData*) PICTRepresentation;
- (NSRect)  boundingBox;

@end
