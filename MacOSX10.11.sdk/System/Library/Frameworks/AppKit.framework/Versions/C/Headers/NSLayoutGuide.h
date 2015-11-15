/*
	NSLayoutGuide.h
	Application Kit
	Copyright (c) 2015, Apple Inc.
	All rights reserved.
 */

#import <AppKit/NSView.h>
#import <AppKit/NSLayoutAnchor.h>


NS_ASSUME_NONNULL_BEGIN
@class NSISVariable;

/* NSLayoutGuides will not show up in the view hierarchy, but may be used as items in an NSLayoutConstraint and represent a rectangle in the layout engine.
 */
NS_CLASS_AVAILABLE_MAC(10_11)
@interface NSLayoutGuide : NSObject <NSCoding, NSUserInterfaceItemIdentification>
{
    @private
    NSView       *_owningView;
    NSString     *_identifier;
    NSISVariable *_minYVariable;
    NSISVariable *_minXVariable;
    NSISVariable *_widthVariable;
    NSISVariable *_heightVariable;
    NSLayoutXAxisAnchor *_left;
    NSLayoutXAxisAnchor *_right;
    NSLayoutXAxisAnchor *_leading;
    NSLayoutXAxisAnchor *_trailing;
    NSLayoutYAxisAnchor *_top;
    NSLayoutYAxisAnchor *_bottom;
    NSLayoutDimension   *_width;
    NSLayoutDimension   *_height;
    NSLayoutXAxisAnchor *_centerX;
    NSLayoutYAxisAnchor *_centerY;
    
    NSRect  _frame;
    id  _reserved1;
    id  _reserved2;
    unsigned int    _shouldBeArchived:1;
    unsigned int    _weakHelper:1;
    unsigned int    _frameNeedsUpdate:1;
    unsigned int    _reservedFlags:29;
}


// The frame of the NSLayoutGuide in its owningView's coordinate system. Valid by the time the owningView is laid out.
@property (readonly) NSRect frame;

// A guide must be added to a view via -[NSView -addLayoutGuide:] before being used in a constraint.  The owningView setter is intended for subclasses to override, and should only be used directly by -addLayoutGuide and -removeLayoutGuide.
@property (weak, nullable) NSView *owningView;

// For ease of debugging.  'NS' prefix is reserved for system-created layout guides.
@property (copy) NSString *identifier;


/* 
 These properties aid concise creation of constraints.  Layout guides can be constrained using simple code like the following:
 [view.topAnchor constraintEqualTo:someLayoutGuide.topAnchor constant:10];
 
 See NSLayoutAnchor.h for more details.
 */
@property (readonly, strong) NSLayoutXAxisAnchor *leadingAnchor;
@property (readonly, strong) NSLayoutXAxisAnchor *trailingAnchor;
@property (readonly, strong) NSLayoutXAxisAnchor *leftAnchor;
@property (readonly, strong) NSLayoutXAxisAnchor *rightAnchor;
@property (readonly, strong) NSLayoutYAxisAnchor *topAnchor;
@property (readonly, strong) NSLayoutYAxisAnchor *bottomAnchor;
@property (readonly, strong) NSLayoutDimension *widthAnchor;
@property (readonly, strong) NSLayoutDimension *heightAnchor;
@property (readonly, strong) NSLayoutXAxisAnchor *centerXAnchor;
@property (readonly, strong) NSLayoutYAxisAnchor *centerYAnchor;

@end


/* A layout guide can be used in place of a view for layout purposes.
 */
@interface NSView (NSLayoutGuideSupport)

- (void)addLayoutGuide:(NSLayoutGuide *)guide NS_AVAILABLE_MAC(10_11);
- (void)removeLayoutGuide:(NSLayoutGuide *)guide NS_AVAILABLE_MAC(10_11);

@property (readonly, copy) NSArray<NSLayoutGuide *> *layoutGuides NS_AVAILABLE_MAC(10_11); // This array may contain guides owned by the system, and the ordering is not guaranteed.  Please be careful.

@end

NS_ASSUME_NONNULL_END
