/*
 NSScrubberItemView.h
 Application Kit
 Copyright (c) 2016-2017, Apple Inc.
 All rights reserved.
 */

#import <AppKit/NSImageCell.h>
#import <AppKit/NSView.h>
#import <os/lock.h>

NS_ASSUME_NONNULL_BEGIN

@class NSScrubberLayoutAttributes, NSTextField, NSImageView;

#pragma mark - Arranged View

NS_CLASS_AVAILABLE_MAC(10_12_2)
@interface NSScrubberArrangedView : NSView {
@private
    id _cache __unused;
    os_unfair_lock _flagLock;
    unsigned int _selected:1;
    unsigned int _highlighted:1;
#if !__OBJC2__
    unsigned int _reservedArrangedViewFlags:30 __unused;
    id _arrangedViewReserved[2] __unused;
#endif
}

@property (getter=isSelected)    BOOL selected;
@property (getter=isHighlighted) BOOL highlighted;

- (void)applyLayoutAttributes:(__kindof NSScrubberLayoutAttributes *)layoutAttributes NS_REQUIRES_SUPER;

@end

#pragma mark - Selection View

/*!
 @class NSScrubberSelectionView
 @abstract The base view class for all selection decorations used by the @c NSScrubber control.
 */
NS_CLASS_AVAILABLE_MAC(10_12_2)
@interface NSScrubberSelectionView : NSScrubberArrangedView {
#if !__OBJC2__
    id _selectionViewReserved[4] __unused;
#endif
}
@end

#pragma mark - Item Views

/*!
 @class NSScrubberItemView
 @abstract The base view class that is arranged by a @c NSScrubber control.
 */
NS_CLASS_AVAILABLE_MAC(10_12_2)
@interface NSScrubberItemView : NSScrubberArrangedView {
@private
    id _background;
    id _foreground;
    id _maskOne;
    id _maskTwo;
    unsigned int _edge:2;
#if !__OBJC2__
    unsigned int _scrubberItemViewReservedFlags:30 __unused;
    id _scrubberItemViewReserved[3] __unused;
#endif
}

@end

#pragma mark Text Item

/*!
 @class NSScrubberTextItemView
 @abstract A simple @c NSScrubberItemView for displaying text. The -fittingSize method can be used to measure the smallest size for the view which fits the title without truncating.
 */
NS_CLASS_AVAILABLE_MAC(10_12_2)
@interface NSScrubberTextItemView : NSScrubberItemView {
@private
    NSTextField *_textField;
#if !__OBJC2__
    id _scrubberTextItemViewReserved[4] __unused;
#endif
}

@property (strong, readonly) NSTextField *textField;
@property (copy) NSString *title;

@end

#pragma mark Image Item

/*!
 @class NSScrubberTextItemView
 @abstract A simple @c NSScrubberItemView for displaying an image. 
 @discussion If the provided image is larger than the view's frame, it is scaled proportionally to fill the entire frame. The cropped portion of the image is determined by the @c imageAlignment property.
 */
NS_CLASS_AVAILABLE_MAC(10_12_2)
@interface NSScrubberImageItemView : NSScrubberItemView {
@private
    NSImageView *_imageView;
    NSImageAlignment _alignment;
#if !__OBJC2__
    id _scrubberImageItemViewReserved[4] __unused;
#endif
}

@property (strong, readonly) NSImageView *imageView;
@property (copy) NSImage *image;
@property NSImageAlignment imageAlignment;

@end

NS_ASSUME_NONNULL_END
