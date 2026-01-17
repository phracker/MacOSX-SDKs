/*
    NSImageView.h
    Application Kit
    Copyright (c) 1994-2018, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/NSImageCell.h>
#import <AppKit/NSMenu.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSImageView : NSControl <NSAccessibilityImage, NSMenuItemValidation> {
    /* All instance variables are private */
    struct __IVFlags {
        unsigned int _hasImageSubview:1;
        unsigned int _usesSubview:1;
        unsigned int _hasCachedUsesSubview:1;
        unsigned int _unused:23;
        unsigned int _rejectsMultiFileDrops:1;
        unsigned int _compatibleScalingAndAlignment:1;
        unsigned int _reserved:1;
        unsigned int _overridesDrawing:1;
        unsigned int _allowsCutCopyPaste:1;
        unsigned int _editable:1;
    } _ivFlags APPKIT_IVAR;
    id _target APPKIT_IVAR;                    // for action messages
    SEL _action APPKIT_IVAR;                   // call here after an image drag-drop
}

@property (nullable, strong) NSImage *image;

@property NSImageAlignment imageAlignment;
@property NSImageScaling imageScaling;
@property NSImageFrameStyle imageFrameStyle;

@property (getter=isEditable) BOOL editable;

/*! A tint color to be used when rendering template image content. This color may be combined with other effects to produce a theme-appropriate rendition of the template image. A nil value indicates the standard set of effects without color modification. The default value is nil. */
@property (nullable, copy) NSColor *contentTintColor NS_AVAILABLE_MAC(10_14);

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


