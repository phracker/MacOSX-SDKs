/*
    NSImageView.h
    Application Kit
    Copyright (c) 1994-2019, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/NSImageCell.h>
#import <AppKit/NSMenu.h>

NS_ASSUME_NONNULL_BEGIN
API_UNAVAILABLE_BEGIN(ios)

@interface NSImageView : NSControl <NSAccessibilityImage, NSMenuItemValidation>

@property (nullable, strong) NSImage *image;

@property NSImageAlignment imageAlignment;
@property NSImageScaling imageScaling;
@property NSImageFrameStyle imageFrameStyle;

@property (getter=isEditable) BOOL editable;

/*! A tint color to be used when rendering template image content. This color may be combined with other effects to produce a theme-appropriate rendition of the template image. A nil value indicates the standard set of effects without color modification. The default value is nil. */
@property (nullable, copy) NSColor *contentTintColor API_AVAILABLE(macos(10.14));

@property BOOL animates;

@property BOOL allowsCutCopyPaste;

@end

@interface NSImageView(NSImageViewConvenience)

/*!
 Creates a non-editable image view containing the provided image. The image is scaled proportionally down to fit the view, and is centered within the view.
 @param image The image to display within the view.
 @return An initialized image view.
 */
+ (instancetype)imageViewWithImage:(NSImage *)image API_AVAILABLE(macos(10.12));

@end

API_UNAVAILABLE_END
NS_ASSUME_NONNULL_END


