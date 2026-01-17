/*
    NSImageView.h
    Application Kit
    Copyright (c) 1994-2017, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/NSImageCell.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSImageView : NSControl <NSAccessibilityImage> {
    /* All instance variables are private */
    struct __IVFlags {
        unsigned int _hasImageView:1;
        unsigned int _usesCachedImage:1;
        unsigned int _unused:24;
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

@interface NSImageView(NSImageViewConvenience)

/*!
 Creates a non-editable image view containing the provided image. The image is scaled proportionally down to fit the view, and is centered within the view.
 @param image The image to display within the view.
 @return An initialized image view.
 */
+ (instancetype)imageViewWithImage:(NSImage *)image NS_AVAILABLE_MAC(10_12);

@end

NS_ASSUME_NONNULL_END


