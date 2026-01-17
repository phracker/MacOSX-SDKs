/*
    NSImageView.h
    Application Kit
    Copyright (c) 1994-2015, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/NSImageCell.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSImageView : NSControl <NSAccessibilityImage> {
    /*All instance variables are private*/
    struct __IVFlags {
        unsigned int _hasImageView:1;
        unsigned int _unused:25;
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

@property (nullable, strong) NSImage *image;

@property NSImageAlignment imageAlignment;
@property NSImageScaling imageScaling;
@property NSImageFrameStyle imageFrameStyle;
@property (getter=isEditable) BOOL editable;

@property BOOL animates;

@property BOOL allowsCutCopyPaste;

@end

NS_ASSUME_NONNULL_END


