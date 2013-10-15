/*
    NSPathComponentCell.h
    Application Kit
    Copyright (c) 2006-2011, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSObject.h>


#import <AppKit/NSTextFieldCell.h>

@class NSImage, NSString, NSURL;

/* Use the 'stringValue' or 'attributedStringValue' to set the display title for this component cell. Use 'image' and 'setImage:' to control the icon displayed for this component cell.
*/

NS_CLASS_AVAILABLE(10_5, NA)
@interface NSPathComponentCell : NSTextFieldCell {
@private
    NSImage *_image;
    // The full size width for this component, shown when the mouse is over the cell. The result is cached from [self cellSize].width. The min size width for this component is acquired from [self cellSizeForBounds:NSZeroRect].width, and is always shown, no matter what.
    CGFloat _fullWidth;
    // The resized width, when there isn't a mouse over it, or set to the full width for items that can't be shrunk, or don't need to be
    CGFloat _resizedWidth;
    // The current width is the size we are using when drawing
    CGFloat _currentWidth;
    NSURL *_url;
    struct {
        unsigned int shouldDrawArrow:1;
        unsigned int drawsAsNavigationBar:1;
        unsigned int isFirstItem:1;
        unsigned int isLastItem:1;
        unsigned int isDropTarget:1;
        unsigned int reserved:27;
    } _flags; 
    id _aux;
}

/* Get and set the image (aka: icon) represented for this particular cell along the path. The NSPathComponentCell can display both an image and text set with stringValue/objectValue. Generally, you will want to use a 16x16 image when the pathStyle is NSPathStyleStandard or NSPathStylePopUp, and a 14x14 image when the style is NSPathStyleNavigationBar.
*/
- (NSImage *)image;
- (void)setImage:(NSImage *)value;

/* Get and set the url portion to this particular NSPathComponentCell along the path of cells.
*/
- (NSURL *)URL;
- (void)setURL:(NSURL *)url;

@end

