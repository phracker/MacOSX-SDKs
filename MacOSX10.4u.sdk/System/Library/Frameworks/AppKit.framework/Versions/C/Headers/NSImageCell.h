/*
	NSImageCell.h
	Application Kit
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.
*/


#import <AppKit/NSCell.h>

@class NSImage;

typedef enum {
    NSScaleProportionally = 0,   // Fit proportionally
    NSScaleToFit,                // Forced fit (distort if necessary)
    NSScaleNone                  // Don't scale (clip)
} NSImageScaling;

typedef enum {
    NSImageAlignCenter = 0,
    NSImageAlignTop,
    NSImageAlignTopLeft,
    NSImageAlignTopRight,
    NSImageAlignLeft,
    NSImageAlignBottom,
    NSImageAlignBottomLeft,
    NSImageAlignBottomRight,
    NSImageAlignRight
} NSImageAlignment;

typedef enum {
    NSImageFrameNone = 0,
    NSImageFramePhoto,
    NSImageFrameGrayBezel,
    NSImageFrameGroove,
    NSImageFrameButton
} NSImageFrameStyle;


@interface NSImageCell : NSCell <NSCopying, NSCoding>
{
    /*All instance variables are private*/
    id _controlView;      
    struct __ICFlags {
        unsigned int _unused:22;
        unsigned int _animates:1;
        unsigned int _align:4;
        unsigned int _scale:2;
        unsigned int _style:3;
    } _icFlags;
    struct _NSImageCellAnimationState *_animationState;
    NSImage *_scaledImage;
}

- (NSImageAlignment)imageAlignment;
- (void)setImageAlignment:(NSImageAlignment)newAlign;
- (NSImageScaling)imageScaling;
- (void)setImageScaling:(NSImageScaling)newScaling;
- (NSImageFrameStyle)imageFrameStyle;
- (void)setImageFrameStyle:(NSImageFrameStyle)newStyle;

@end

