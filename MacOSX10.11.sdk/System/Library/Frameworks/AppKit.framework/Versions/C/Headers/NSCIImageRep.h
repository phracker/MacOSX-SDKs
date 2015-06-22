/*
        NSCIImageRep.h
        Application Kit
        Copyright (c) 2003-2015, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSImageRep.h>
#import <AppKit/NSGraphics.h>
#import <QuartzCore/CIImage.h>


NS_ASSUME_NONNULL_BEGIN

@class NSBitmapImageRep;

@interface NSCIImageRep : NSImageRep
{
    CIImage *_ciImage;
}
+ (instancetype)imageRepWithCIImage:(CIImage *)image;
- (instancetype)initWithCIImage:(CIImage *)image;
@property (readonly, strong) CIImage *CIImage;
@end

@interface CIImage (NSAppKitAdditions)
- (nullable instancetype)initWithBitmapImageRep:(NSBitmapImageRep *)bitmapImageRep;

- (void)drawInRect:(NSRect)rect fromRect:(NSRect)fromRect operation:(NSCompositingOperation)op fraction:(CGFloat)delta;
- (void)drawAtPoint:(NSPoint)point fromRect:(NSRect)fromRect operation:(NSCompositingOperation)op fraction:(CGFloat)delta;
@end

NS_ASSUME_NONNULL_END

