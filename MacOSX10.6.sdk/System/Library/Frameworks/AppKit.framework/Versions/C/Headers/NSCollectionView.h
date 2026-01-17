/*
    NSCollectionView.h
    Application Kit
    Copyright (c) 2005-2009, Apple Inc.
    All rights reserved.
 */

#import <AppKit/NSView.h>
#import <AppKit/NSViewController.h>
#import <AppKit/NSDragging.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

@class NSCollectionView, NSIndexSet, NSMutableIndexSet, NSNib;
@protocol NSCollectionViewDelegate;

typedef NSInteger NSCollectionViewDropOperation;


@interface NSCollectionViewItem : NSViewController <NSCopying> {
@private
    NSCollectionView *_collectionView;
    struct {
        unsigned int isSelected:1;
        unsigned int suppressSelectionChangedNotification:1;
        unsigned int connectionsCopied:1;
        unsigned int reserved:29;
    } _cviFlags;
    NSData *_cachedArchive;
    void *_reserved2;
}

- (NSCollectionView *)collectionView;

- (void)setSelected:(BOOL)flag;
- (BOOL)isSelected;

@end

@interface NSCollectionView : NSView {
@private
    NSArray *_content;
    NSMutableIndexSet *_selectionIndexes;
    NSCollectionViewItem *_itemPrototype;
    NSSize _minItemSize;
    NSSize _maxItemSize;
    NSUInteger _maxGridRows;
    NSUInteger _maxGridColumns;
    NSArray *_backgroundColors;
    NSMutableArray *_displayedItems;
    NSTimeInterval _animationDuration;
    struct {
        unsigned int isFirstResponder:1;
        unsigned int invalidateItemViews:1;
        unsigned int selectable:1;
        unsigned int allowsMultipleSelection:1;
        unsigned int avoidsEmptySelection:1;
        unsigned int superviewIsClipView:1;
        unsigned int needsUpdateGrid:1;
        unsigned int needsUpdateBackground:1;
        unsigned int gridSettingsNeedUpdate:1;
        unsigned int guardSetFrameSize:1;
        unsigned int canDisplayItems:1;
        unsigned int animateForDrag:1;
        unsigned int unarchiving:1;
        unsigned int reserved:19;
    } _cvFlags;
    id _delegate;
    NSMutableArray *_backgroundLayers;
    NSSize _storedFrameSize;
    NSNib *_cachedNib;
    NSTimer *_animTimer;
    NSArray *_removedItems;
    NSTimer *_resizeTimer;
    
    NSIndexSet *_draggedIndexes;
    NSDragOperation _draggingSourceOperationMaskForLocal;
    NSDragOperation _draggingSourceOperationMaskForNonLocal;
    NSInteger _currentDropIndex;
    NSInteger _currentDropSpaceIndex;
    NSInteger _shiftRow;
    NSDragOperation _currentDragOperation;
    NSCollectionViewDropOperation _currentDropOperation;
    NSTimer *_dragTimer;
    
    id _private;
    void *_reserved[16];
}

- (void)setDelegate:(id <NSCollectionViewDelegate>)aDelegate;
- (id <NSCollectionViewDelegate>)delegate;

- (BOOL)isFirstResponder;    // fully KVO compliant - can be used determine different selection colors, etc.

- (void)setContent:(NSArray *)content;
- (NSArray *)content;
- (void)setSelectable:(BOOL)flag;
- (BOOL)isSelectable;
- (void)setAllowsMultipleSelection:(BOOL)flag;    // default: YES
- (BOOL)allowsMultipleSelection;
- (void)setSelectionIndexes:(NSIndexSet *)indexes;
- (NSIndexSet *)selectionIndexes;

- (NSCollectionViewItem *)newItemForRepresentedObject:(id)object;    // override if item should not be generated from prototype (or if view needs to be customized) - the returned object should not be autoreleased

- (void)setItemPrototype:(NSCollectionViewItem *)prototype;
- (NSCollectionViewItem *)itemPrototype;

- (void)setMaxNumberOfRows:(NSUInteger)number;    // default: 0, which means no limit 
- (NSUInteger)maxNumberOfRows;
- (void)setMaxNumberOfColumns:(NSUInteger)number;    // default: 0, which means no limit 
- (NSUInteger)maxNumberOfColumns;
- (void)setMinItemSize:(NSSize)size;    // default: (0; 0)
- (NSSize)minItemSize;
- (void)setMaxItemSize:(NSSize)size;    // default: (0; 0), which means no limit
- (NSSize)maxItemSize;

- (void)setBackgroundColors:(NSArray *)colors;    // passing nil or an empty array resets the background colors back to the default
- (NSArray *)backgroundColors;

/* Returns the NSCollectionViewItem instance associated with the represented object at the given index. You can also use this to access the view at the given index.
 */
- (NSCollectionViewItem *)itemAtIndex:(NSUInteger)index AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Returns the frame calculated by the receiver where it intends to place the subview for the NSCollectionViewItem at the given index. You can use this method in the draggingImage methods to determine which views are in the visible portion of the enclosing scroll view. Overriding this method will have no effect on the receiver's subview layout.
 */
- (NSRect)frameForItemAtIndex:(NSUInteger)index AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Drag and drop support */

/* Configures the value returned from -draggingSourceOperationMaskForLocal:. An isLocal value of YES indicates that 'dragOperationMask' applies when the destination object is in the same application. By default, NSDragOperationEvery will be returned. An isLocal value of NO indicates that 'dragOperationMask' applies when the destination object is in an application outside the receiver's application. By default, NSDragOperationNone is returned. NSCollectionView will save the values you set for each isLocal setting. You typically will invoke this method, and not override it.
 */
- (void)setDraggingSourceOperationMask:(NSDragOperation)dragOperationMask forLocal:(BOOL)localDestination AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* This method computes and returns an image to use for dragging. You can override this to return a custom drag image, or call it from the delegate method to get the default drag image. 'indexes' contains the indexes of the items being dragged. 'event' is a reference to the mouse down event that began the drag. 'dragImageOffset' is an in/out parameter. This method will be called with dragImageOffset set to NSZeroPoint, but it can be modified to re-position the returned image. A dragImageOffset of NSZeroPoint will cause the image to be centered under the mouse. By default, an image will be created that contains a rendering of the visible portions of the views for each item. If the delegate implements the equivalent delegate method, it will be preferred over this method.
 */
- (NSImage *)draggingImageForItemsAtIndexes:(NSIndexSet *)indexes withEvent:(NSEvent *)event offset:(NSPointPointer)dragImageOffset AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

@end

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6

enum {
    NSCollectionViewDropOn = 0,
    NSCollectionViewDropBefore = 1,
};

#endif

@protocol NSCollectionViewDelegate <NSObject>
@optional

/* Drag and drop support */

/* The return value indicates whether the collection view can attempt to initiate a drag for the given event and items. If the delegate does not implement this method, the collection view will act as if it returned YES.
 */
- (BOOL)collectionView:(NSCollectionView *)collectionView canDragItemsAtIndexes:(NSIndexSet *)indexes withEvent:(NSEvent *)event AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/*
 This method is called after it has been determined that a drag should begin, but before the drag has been started. To refuse the drag, return NO. To start the drag, declare the pasteboard types that you support with -[NSPasteboard declareTypes:owner:], place your data for the items at the given indexes on the pasteboard, and return YES from the method. The drag image and other drag related information will be set up and provided by the view once this call returns YES. You need to implement this method for your collection view to be a drag source.
 */
- (BOOL)collectionView:(NSCollectionView *)collectionView writeItemsAtIndexes:(NSIndexSet *)indexes toPasteboard:(NSPasteboard *)pasteboard AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* The delegate can support file promise drags by adding NSFilesPromisePboardType to the pasteboard in -collectionView:writeItemsAtIndexes:toPasteboard:. NSCollectionView implements -namesOfPromisedFilesDroppedAtDestination: to return the results of this delegate method. This method should return an array of filenames (not full paths) for the created files. The URL represents the drop location. For more information on file promise dragging, see documentation for the NSDraggingSource protocol and -namesOfPromisedFilesDroppedAtDestination:. You do not need to implement this method for your collection view to be a drag source.
 */
- (NSArray *)collectionView:(NSCollectionView *)collectionView namesOfPromisedFilesDroppedAtDestination:(NSURL *)dropURL forDraggedItemsAtIndexes:(NSIndexSet *)indexes AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Allows the delegate to construct a custom dragging image for the items being dragged. 'indexes' contains the indexes of the items being dragged. 'event' is a reference to the  mouse down event that began the drag. 'dragImageOffset' is an in/out parameter. This method will be called with dragImageOffset set to NSZeroPoint, but it can be modified to re-position the returned image. A dragImageOffset of NSZeroPoint will cause the image to be centered under the mouse. You can safely call -[NSCollectionView draggingImageForItemsAtIndexes:withEvent:offset:] from within this method. You do not need to implement this method for your collection view to be a drag source.
 */
- (NSImage *)collectionView:(NSCollectionView *)collectionView draggingImageForItemsAtIndexes:(NSIndexSet *)indexes withEvent:(NSEvent *)event offset:(NSPointPointer)dragImageOffset AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* This method is used by the collection view to determine a valid drop target. Based on the mouse position, the collection view will suggest a proposed index and drop operation. These values are in/out parameters and can be changed by the delegate to retarget the drop operation. The collection view will propose NSCollectionViewDropOn when the dragging location is closer to the middle of the item than either of its edges. Otherwise, it will propose NSCollectionViewDropBefore. You may override this default behavior by changing proposedDropOperation or proposedDropIndex. This method must return a value that indicates which dragging operation the data source will perform. It must return something other than NSDragOperationNone to accept the drop.
 
    Note: to receive drag messages, you must first send -registerForDraggedTypes: to the collection view with the drag types you want to support (typically this is done in -awakeFromNib). You must implement this method for your collection view to be a drag destination.
 */
- (NSDragOperation)collectionView:(NSCollectionView *)collectionView validateDrop:(id <NSDraggingInfo>)draggingInfo proposedIndex:(NSInteger *)proposedDropIndex dropOperation:(NSCollectionViewDropOperation *)proposedDropOperation AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* This method is called when the mouse is released over a collection view that previously decided to allow a drop via the above validateDrop method. At this time, the delegate should incorporate the data from the dragging pasteboard and update the collection view's contents. You must implement this method for your collection view to be a drag destination.
 */
- (BOOL)collectionView:(NSCollectionView *)collectionView acceptDrop:(id <NSDraggingInfo>)draggingInfo index:(NSInteger)index dropOperation:(NSCollectionViewDropOperation)dropOperation AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

@end

#endif
