/*
	NSImageCell.h
	Application Kit
	Copyright (c) 1994-2015, Apple Inc.
	All rights reserved.
*/


#import <AppKit/NSCell.h>

@class NSImage;

typedef NS_ENUM(NSUInteger, NSImageAlignment) {
    NSImageAlignCenter = 0,
    NSImageAlignTop,
    NSImageAlignTopLeft,
    NSImageAlignTopRight,
    NSImageAlignLeft,
    NSImageAlignBottom,
    NSImageAlignBottomLeft,
    NSImageAlignBottomRight,
    NSImageAlignRight
};

typedef NS_ENUM(NSUInteger, NSImageFrameStyle) {
    NSImageFrameNone = 0,
    NSImageFramePhoto,
    NSImageFrameGrayBezel,
    NSImageFrameGroove,
    NSImageFrameButton
};


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

@property NSImageAlignment imageAlignment;
@property NSImageScaling imageScaling;
@property NSImageFrameStyle imageFrameStyle;

@end

