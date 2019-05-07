/*
    NSPathComponentCell.h
    Application Kit
    Copyright (c) 2006-2018, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSObject.h>


#import <AppKit/NSTextFieldCell.h>

NS_ASSUME_NONNULL_BEGIN

@class NSImage, NSString, NSURL;

/* Use the 'stringValue' or 'attributedStringValue' to set the display title for this component cell. Use 'image' and 'setImage:' to control the icon displayed for this component cell.
*/

NS_CLASS_AVAILABLE(10_5, NA)
@interface NSPathComponentCell : NSTextFieldCell {
@private
    NSImage *_image APPKIT_IVAR;
    // The full size width for this component, shown when the mouse is over the cell. The result is cached from [self cellSize].width. The min size width for this component is acquired from [self cellSizeForBounds:NSZeroRect].width, and is always shown, no matter what.
    CGFloat _fullWidth APPKIT_IVAR;
    // The resized width, when there isn't a mouse over it, or set to the full width for items that can't be shrunk, or don't need to be
    CGFloat _resizedWidth APPKIT_IVAR;
    // The current width is the size we are using when drawing
    CGFloat _currentWidth APPKIT_IVAR;
    NSURL *_url APPKIT_IVAR;
    struct {
        unsigned int shouldDrawArrow:1;
        unsigned int drawsAsNavigationBar:1;
        unsigned int isFirstItem:1;
        unsigned int isLastItem:1;
        unsigned int isDropTarget:1;
        unsigned int reserved:27;
    } _flags APPKIT_IVAR; 
    NSImage *_originalImage APPKIT_IVAR;
}

/* See NSPathComponent.h for details on the image & URL properties.
*/
@property (nullable, strong) NSImage *image;

@property (nullable, copy) NSURL *URL;

@end

NS_ASSUME_NONNULL_END

