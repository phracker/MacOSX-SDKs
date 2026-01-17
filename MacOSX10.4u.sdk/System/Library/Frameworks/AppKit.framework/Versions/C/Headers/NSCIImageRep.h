/*
        NSCIImageRep.h
        Application Kit
        Copyright (c) 2003-2005, Apple Computer, Inc.
        All rights reserved.
*/

#import <AppKit/NSImageRep.h>
#import <AppKit/NSGraphics.h>
#import <QuartzCore/CIImage.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

@class NSBitmapImageRep;

@interface NSCIImageRep : NSImageRep
{
    CIImage *_ciImage;
}
+ (id)imageRepWithCIImage:(CIImage *)image;
- (id)initWithCIImage:(CIImage *)image;
- (CIImage *)CIImage;
@end

@interface CIImage (NSAppKitAdditions)
- (id)initWithBitmapImageRep:(NSBitmapImageRep *)bitmapImageRep;

- (void)drawInRect:(NSRect)rect fromRect:(NSRect)fromRect operation:(NSCompositingOperation)op fraction:(float)delta;
- (void)drawAtPoint:(NSPoint)point fromRect:(NSRect)fromRect operation:(NSCompositingOperation)op fraction:(float)delta;
@end

#endif
