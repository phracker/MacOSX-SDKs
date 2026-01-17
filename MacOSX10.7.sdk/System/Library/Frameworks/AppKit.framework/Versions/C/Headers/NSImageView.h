/*
	NSImageView.h
	Application Kit
	Copyright (c) 1994-2011, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/NSImageCell.h>

@interface NSImageView : NSControl
{
    /*All instance variables are private*/
    struct __IVFlags {
        unsigned int _unused:26;
        unsigned int _rejectsMultiFileDrops:1;
        unsigned int _compatibleScalingAndAlignment:1;
        unsigned int _reserved:1;
        unsigned int _overridesDrawing:1;
        unsigned int _allowsCutCopyPaste:1;
        unsigned int _editable:1;
    } _ivFlags;
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

- (void)setAnimates:(BOOL)flag;
- (BOOL)animates;

- (BOOL)allowsCutCopyPaste;
- (void)setAllowsCutCopyPaste:(BOOL)allow;

@end


