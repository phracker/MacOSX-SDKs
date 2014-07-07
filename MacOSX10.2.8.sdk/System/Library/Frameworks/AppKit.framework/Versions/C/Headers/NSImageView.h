/*
	NSImageView.h
	Application Kit
	Copyright (c) 1994-2001, Apple Computer, Inc.
	All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/NSImageCell.h>

@interface NSImageView : NSControl
{
    /*All instance variables are private*/
    BOOL _editable;
    id _target;                    // for action messages
    SEL _action;                   // call here after an image drag-drop
}


- (NSImage *)image;
- (void)setImage:(NSImage *)newImage;

- (NSImageAlignment)imageAlignment;
- (void)setImageAlignment:(NSImageAlignment)newAlign;
- (NSImageScaling)imageScaling;
- (void)setImageScaling:(NSImageScaling)newScaling;
- (NSImageFrameStyle)imageFrameStyle;
- (void)setImageFrameStyle:(NSImageFrameStyle)newStyle;
- (void)setEditable:(BOOL)yn;
- (BOOL)isEditable;


@end


