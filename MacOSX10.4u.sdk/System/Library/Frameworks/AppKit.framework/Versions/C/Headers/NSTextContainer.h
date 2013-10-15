/*
        NSTextContainer.h
        Application Kit
        Copyright (c) 1994-2005, Apple Computer, Inc.
        All rights reserved.
*/

// An NSTextContainer defines a region in which to lay out text.  It's main responsibility is to calculate line fragments which fall within the region it represents.  Containers have a line fragment padding which is used by the typesetter to inset text from the edges of line fragments along the sweep direction.
// The container can enforce any other geometric constraints as well.  When drawing the text that has been laid in a container, a NSTextView will clip to the interior of the container (it clips to the container's rectagular area only, however, not to the arbitrary shape the container may define for text flow).

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>

@class NSLayoutManager;
@class NSTextView;

typedef enum {
    NSLineSweepLeft = 0,
    NSLineSweepRight = 1,
    NSLineSweepDown = 2,
    NSLineSweepUp = 3
} NSLineSweepDirection;

typedef enum {
    NSLineDoesntMove = 0, 
    NSLineMovesLeft = 1,
    NSLineMovesRight = 2,
    NSLineMovesDown = 3,
    NSLineMovesUp = 4
} NSLineMovementDirection;


@interface NSTextContainer : NSObject <NSCoding> {
    
  /*All instance variables are private*/
    
  @private
    NSLayoutManager *_layoutManager;
    NSTextView *_textView;
    NSSize _size;
    float _lineFragmentPadding;
    struct __tcFlags {
        unsigned short widthTracksTextView:1;
        unsigned short heightTracksTextView:1;
        unsigned short observingFrameChanges:1;
        unsigned short _reserved:13;
    } _tcFlags;
}

/**************************** Initialization ****************************/

- (id)initWithContainerSize:(NSSize)size;

/**************************** Layout and View ****************************/

- (NSLayoutManager *)layoutManager;
- (void)setLayoutManager:(NSLayoutManager *)layoutManager;
    // The set method generally should not be called directly, but you may want to override it.  Adding a container to a NSLayoutManager through the provided NSLayoutManager methods will cause the set method to be called appropriately.

- (void)replaceLayoutManager:(NSLayoutManager *)newLayoutManager;
    // This method should be used instead of the primitive -setLayoutManager: if you need to replace a container's layoutManager with a new one leaving the rest of the web intact.  All the NSTextContainers on the old NSLayoutManager get transferred to the new one.  This method deals with all the work of making sure the containers don't get deallocated and removing the old layoutManager from the text storage and replacing it with the new one.

- (NSTextView *)textView;
- (void)setTextView:(NSTextView *)textView;
    // Set/get the view which the container is drawn in.  Having a view is optional.

- (void)setWidthTracksTextView:(BOOL)flag;
- (BOOL)widthTracksTextView;
- (void)setHeightTracksTextView:(BOOL)flag;
- (BOOL)heightTracksTextView;
    // If a container tracks the size of it's view in one or both of these dimensions then those dimensions will be kept in synch with with the view's frame (taking into account the views textContainerInset).

/************************* Container size and padding *************************/

- (void)setContainerSize:(NSSize)size;
- (NSSize)containerSize;
    // Sets/Returns the current size of the container.  This size has nothing to do with how much text is in the container and how much space it takes up (which the container is not in a position to know).  It is basically the maximum flowable area of the container.  The NSTextView's size will not generally have much connection to this size.  The NSTextView will generally want to be big enough to display all the text which has been laid in the container at the moment and no bigger.  The NSLayoutManager will generally be in charge of telling the view what size it should be.

- (void)setLineFragmentPadding:(float)pad;
- (float)lineFragmentPadding;
    // This value is used by the typesetter to inset the line fragment rects it gets along the sweep direction to give a little default pad to each fragment.

/**************************** Line fragments ****************************/

- (NSRect)lineFragmentRectForProposedRect:(NSRect)proposedRect sweepDirection:(NSLineSweepDirection)sweepDirection movementDirection:(NSLineMovementDirection)movementDirection remainingRect:(NSRectPointer)remainingRect;
    // Returns the first and largest subrect of proposedRect which falls within the container's region.  All rects are given in the container's coordinate system.  sweepDirection determines what edge of the proposedRect to start from.  movementDirection determines in which direction (if any) the proposedRect can be translated if it is necessary to move the rect to find a non-empty fragment.  remainingRect is set to hold whatever portion of of the proposedRect (after any line movement translation) which is left after subtracting the returned fragment.  The proposed rect should fall within the frame area of the container.  remainingRect will only be non-empty if there are parts of the proposedRect left within the container's frame area ("after" the returned fragment rect in the sweep direction) that are not included in the returned rect.

- (BOOL)isSimpleRectangularTextContainer;
    // Subclasses should override this method to return NO if the containers area is not truly rectangular with no holes or concavities.  NSLayoutManager uses this method to determine whether it can make certain optimizations when relaying text in the container.  NSTextContainer's implementation returns YES.

/**************************** Hit testing ****************************/

- (BOOL)containsPoint:(NSPoint)point;
    // Returns YES if the point (given in the coordinate system of the container) falls within the region of the container.

@end
