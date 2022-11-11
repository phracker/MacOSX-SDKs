//
//  PDFOutline.h
//  Copyright © 2019 Apple. All rights reserved.
//
//  PDFOutline represents a node in an outline hierarchy, which is always constructed
//  of these node types. A root PDFOutline node can have any number of children,
//  added via the below -[insertChild:atIndex:] method. These children can also have
//  any number of their own child node objects. The relationship between parent and
//  child nodes should never introduce any cycles: the resulting tree should always be
//  a directed acyclic graph.
//

#import <PDFKit/PDFKitPlatform.h>

NS_ASSUME_NONNULL_BEGIN

@class PDFAction, PDFDocument, PDFDestination, PDFOutlinePrivate;

PDFKIT_CLASS_AVAILABLE(10_4, 11_0)
@interface PDFOutline : NSObject // < NSCopying >
{
@private
    PDFOutlinePrivate *_private;
}

// -------- initializer

// Returns a PDFOutline object. If this object is to be the outline root, you will need to add additional PDFOutline
// objects to form the outline hierarchy you desire. You will then need to add it to a PDFDocument by passing it to 
// -[PDFDocument setOutlineRoot:]. If this is to be a child (non-root) outline you will need to set a label for it and 
// either a destination or action for it. Also, you will need to add it as a child of another PDFOutline object.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

// -------- accessors

// The PDFDocument the outline is associated with.
@property (nonatomic, readonly, weak, nullable) PDFDocument *document;

// Returns the parent outline (the root outline will return nil).
@property (nonatomic, readonly, nullable) PDFOutline *parent PDFKIT_AVAILABLE(10_5, 11_0);

// Number of PDFOutline children this PDFOutline has.
@property (nonatomic, readonly) NSUInteger numberOfChildren;

// Returns the index of the outline item - that is, relative to its siblings (and from the perspective of the parent).
// The root outline item (or any item with no parent) is always index 0.
@property (nonatomic, readonly) NSUInteger index PDFKIT_AVAILABLE(10_5, 11_0);

// PDFOutline child at index. Will throw exception if index is out of range.
- (nullable PDFOutline *)childAtIndex:(NSUInteger)index;

// To build up a PDFOutline hierarchy, you call this method to add children outline items. For the simplest of outlines 
// you would, at the very least, have to add items to the outline root item.
// NOTE: Be careful when calling this for a PDFOutline item which already has a parent (for example when moving items 
// around within an outline hierarchy) - you should retain the item and call -[removeFromParent] first.
- (void)insertChild:(PDFOutline *)child atIndex:(NSUInteger)index PDFKIT_AVAILABLE(10_5, 11_0);

// Removes self from parent (for root outline, does nothing since the root has no parent).
- (void)removeFromParent PDFKIT_AVAILABLE(10_5, 11_0);

// The label for the outline. The root PDFOutline has no label and is only a container for children PDFOutlines.
@property (nonatomic, copy, nullable) NSString *label;

// Indicates whether PDFOutline item is initially disclosed or not. If the outline item has no children, -[isOpen] is 
// always NO and calling -[setIsOpen] has no effect. The root item always returns YES for -[isOpen] and calling 
// -[setIsOpen] also has no effect.
@property (nonatomic) BOOL isOpen PDFKIT_AVAILABLE(10_5, 11_0);

// Get: The destination associated with the outline item. The root PDFOutline has no destination. May return nil if the
// outline item has an associated action instead. If however the associated action is a PDFActionGoTo type this method 
// will return the destination from the PDFActionGoTo action. The preferred way though is to call -[action] below.

// Set: Has no effect on the root PDFOutline item. If the item previously had an action associated with it, the action is
// released (PDFOutline items cannot have both an action and a destination, they are mutually exclusive).
// The preferred way though is to call -[setAction] below.
@property (nonatomic, strong, nullable) PDFDestination *destination;

// Action performed when a user clicks on the PDFOutline. Equivalent to calling -[destination] above when the outline 
// has a destination (-[action] will return a PDFActionGoTo object). Some outlines do not have destinations however and 
// you must therefore call this method. The root outline item will never return either an action or a destination.
// Calling -[setAction] on the root item has no effect.

@property (nonatomic, strong, nullable) PDFAction *action PDFKIT_AVAILABLE(10_5, 11_0);

@end

NS_ASSUME_NONNULL_END
