// =====================================================================================================================
//  PDFOutline.m
// =====================================================================================================================


#import <AppKit/AppKit.h>


@class PDFAction, PDFDocument, PDFDestination, PDFOutlinePrivateVars;


@interface PDFOutline : NSObject /*<NSCopying>*/
{
@private
    PDFOutlinePrivateVars *_pdfPriv;
}

// -------- initializer

// Returns a PDFOutline object.  If this object is to be the outlne root, you will need to add additional PDFOutline 
// objects to form the outline heirarchy you desire.  You will then need to add it to a PDFDocument by passing it to 
// -[PDFDocument setOutlineRoot:].  If this is to be a child (non-root) outline you will need to set a label for it and 
// either a destination or action for it.  Also, you will need to add it as a child of another PDFOutline object.
- (id) init;

// -------- accessors

// The PDFDocument the outline is associated with.
- (PDFDocument *) document;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Returns the parent outline (the root outline will return nil).
- (PDFOutline *) parent;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Number of PDFOutline children this PDFOutline has.
- (NSUInteger) numberOfChildren;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Returns the index of the outline item - that is, relative to its siblings (and from the perspective of the parent).
// The root outline item (or any item with no parent) is always index 0.
- (NSUInteger) index;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// PDFOutline child at index.  Will throw exception if index is out of range.
- (PDFOutline *) childAtIndex: (NSUInteger) index;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// To build up a PDFOutline heirarchy, you call this method to add children outline items. For the simplest of outlines 
// you would, at the very least, have to add items to the outline root item.
// NOTE: Be careful when calling this for a PDFOutline item which already has a parent (for example when moving items 
// around within an outline heirarchy) - you should retain the item and call -[removeFromParent] first.
- (void) insertChild: (PDFOutline *) child atIndex: (NSUInteger) index;

// Removes self from parent (for root outline, does nothing since the root has no parent).
- (void) removeFromParent;

#endif	// MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// The label for the outline.  The root PDFOutline has no label and is only a container for children PDFOutlines.
- (NSString *) label;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Calling -[setLabel] on the root item has no effect.
- (void) setLabel: (NSString *) label;

// Indicates whether PDFOutline item is initially disclosed or not.  If the outline item has no children, -[isOpen] is 
// always NO and calling -[setIsOpen] has no effect.  The root item always returns YES for -[isOpen] and calling 
// -[setIsOpen] also has no effect.
- (BOOL) isOpen;
- (void) setIsOpen: (BOOL) open;

#endif	 // MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// The destination associated with the outline item.  The root PDFOutline has no destination.  May return nil if the 
// outline item has an associated action instead.  If however the associated action is a PDFActionGoTo type this method 
// will return the destination from the PDFActionGoTo action. The preferred way though is to call -[action] below.

- (PDFDestination *) destination;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

// Has no effect on the root PDFOutline item.  If the item previously had an actio nasscoiated with it, the action is 
// released (PDFOutline items cannot have both an action and a destination, they are mutually exclusive).
// The preferred way though is to call -[setAction] below.

- (void) setDestination: (PDFDestination *) destination;

// Action performed when a user clicks on the PDFOutline.  Equivalent to calling -[destination] above when the outline 
// has a destination (-[action] will return a PDFActionGoTo object). Some outlines do not have destinations however and 
// you must therefore call this method.  The root outline item will never return either an action or a destination.
// Calling -[setAction] on the root item has no effect.

- (PDFAction *) action;
- (void) setAction: (PDFAction *) action;

#endif	 // MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

@end
