/*
    NSCollectionView.h
    Application Kit
    Copyright (c) 2005-2011, Apple Inc.
    All rights reserved.
 */

#import <AppKit/NSView.h>
#import <AppKit/NSViewController.h>
#import <AppKit/NSDragging.h>


@class NSCollectionView, NSImageView, NSIndexSet, NSMutableIndexSet, NSNib, NSTextField;
@protocol NSCollectionViewDelegate;

typedef NSInteger NSCollectionViewDropOperation;

NS_CLASS_AVAILABLE(10_5, NA)
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

@property (readonly) NSCollectionView *collectionView;

@property (getter=isSelected) BOOL selected;

@property (assign) IBOutlet NSImageView *imageView NS_AVAILABLE_MAC(10_7);
@property (assign) IBOutlet NSTextField *textField NS_AVAILABLE_MAC(10_7);

/* Multi-image drag and drop support. The default implementation will return an array of up to two NSDraggingImageComponent instances -- one for the imageView and another for the textField (if not nil). This methods can be subclassed and overridden to provide a custom set of NSDraggingImageComponents to create the drag image. Note: the component frames are relative to a coordinate system that has its origin at the bottom left, so you need to take into account the flippedness of your view when computing the component frames.
 */
@property (readonly) NSArray *draggingImageComponents NS_AVAILABLE_MAC(10_7);

@end

NS_CLASS_AVAILABLE(10_5, NA)
@interface NSCollectionView : NSView <NSDraggingSource, NSDraggingDestination> {
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
    BOOL *_animTimerCancel;
    NSArray *_removedItems;
    NSArray *_addedItems;
    NSIndexSet *_addedItemIndexes;
    BOOL *_resizeTimerCancel;
    
    NSIndexSet *_draggedIndexes;
    NSDragOperation _draggingSourceOperationMaskForLocal;
    NSDragOperation _draggingSourceOperationMaskForNonLocal;
    NSInteger _currentDropIndex;
    NSInteger _currentDropSpaceIndex;
    NSInteger _shiftRow;
    NSDragOperation _currentDragOperation;
    NSCollectionViewDropOperation _currentDropOperation;
    id _draggingInfo;
    BOOL *_dragTimerCancel;
    
    id _private;
    void *_reserved[13];
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
- (NSCollectionViewItem *)itemAtIndex:(NSUInteger)index NS_AVAILABLE_MAC(10_6);

/* Returns the frame calculated by the receiver where it intends to place the subview for the NSCollectionViewItem at the given index. You can use this method in the draggingImage methods to determine which views are in the visible portion of the enclosing scroll view. Overriding this method will have no effect on the receiver's subview layout.
 */
- (NSRect)frameForItemAtIndex:(NSUInteger)index NS_AVAILABLE_MAC(10_6);

/* Returns the frame calculated by the receiver where it would place a subview for an NSCollectionViewItem at the given index in a collection with the given number of items. You should use this method when updating NSDraggingItem frames when your collection is a drag destination. You should not use -frameForItemAtIndex:, since a drag and drop operation may change the number of items in the collection, which affects the layout of the item views.
 */
- (NSRect)frameForItemAtIndex:(NSUInteger)index withNumberOfItems:(NSUInteger)numberOfItems NS_AVAILABLE_MAC(10_7);

/* Drag and drop support */

/* Configures the value returned from -draggingSourceOperationMaskForLocal:. An isLocal value of YES indicates that 'dragOperationMask' applies when the destination object is in the same application. By default, NSDragOperationEvery will be returned. An isLocal value of NO indicates that 'dragOperationMask' applies when the destination object is in an application outside the receiver's application. By default, NSDragOperationNone is returned. NSCollectionView will save the values you set for each isLocal setting. You typically will invoke this method, and not override it.
 */
- (void)setDraggingSourceOperationMask:(NSDragOperation)dragOperationMask forLocal:(BOOL)localDestination NS_AVAILABLE_MAC(10_6);

/* This method computes and returns an image to use for dragging. You can override this to return a custom drag image, or call it from the delegate method to get the default drag image. 'indexes' contains the indexes of the items being dragged. 'event' is a reference to the mouse down event that began the drag. 'dragImageOffset' is an in/out parameter. This method will be called with dragImageOffset set to NSZeroPoint, but it can be modified to re-position the returned image. A dragImageOffset of NSZeroPoint will cause the image to be centered under the mouse. By default, an image will be created that contains a rendering of the visible portions of the views for each item. If the delegate implements the equivalent delegate method, it will be preferred over this method.
 */
- (NSImage *)draggingImageForItemsAtIndexes:(NSIndexSet *)indexes withEvent:(NSEvent *)event offset:(NSPointPointer)dragImageOffset NS_AVAILABLE_MAC(10_6);

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
- (BOOL)collectionView:(NSCollectionView *)collectionView canDragItemsAtIndexes:(NSIndexSet *)indexes withEvent:(NSEvent *)event NS_AVAILABLE_MAC(10_6);

/*
 This method is called after it has been determined that a drag should begin, but before the drag has been started. To refuse the drag, return NO. To start the drag, declare the pasteboard types that you support with -[NSPasteboard declareTypes:owner:], place your data for the items at the given indexes on the pasteboard, and return YES from the method. The drag image and other drag related information will be set up and provided by the view once this call returns YES. You need to implement this method for your collection view to be a drag source.
 */
- (BOOL)collectionView:(NSCollectionView *)collectionView writeItemsAtIndexes:(NSIndexSet *)indexes toPasteboard:(NSPasteboard *)pasteboard NS_AVAILABLE_MAC(10_6);

/* The delegate can support file promise drags by adding NSFilesPromisePboardType to the pasteboard in -collectionView:writeItemsAtIndexes:toPasteboard:. NSCollectionView implements -namesOfPromisedFilesDroppedAtDestination: to return the results of this delegate method. This method should return an array of filenames (not full paths) for the created files. The URL represents the drop location. For more information on file promise dragging, see documentation for the NSDraggingSource protocol and -namesOfPromisedFilesDroppedAtDestination:. You do not need to implement this method for your collection view to be a drag source.
 */
- (NSArray *)collectionView:(NSCollectionView *)collectionView namesOfPromisedFilesDroppedAtDestination:(NSURL *)dropURL forDraggedItemsAtIndexes:(NSIndexSet *)indexes NS_AVAILABLE_MAC(10_6);

/* Allows the delegate to construct a custom dragging image for the items being dragged. 'indexes' contains the indexes of the items being dragged. 'event' is a reference to the  mouse down event that began the drag. 'dragImageOffset' is an in/out parameter. This method will be called with dragImageOffset set to NSZeroPoint, but it can be modified to re-position the returned image. A dragImageOffset of NSZeroPoint will cause the image to be centered under the mouse. You can safely call -[NSCollectionView draggingImageForItemsAtIndexes:withEvent:offset:] from within this method. You do not need to implement this method for your collection view to be a drag source.
 */
- (NSImage *)collectionView:(NSCollectionView *)collectionView draggingImageForItemsAtIndexes:(NSIndexSet *)indexes withEvent:(NSEvent *)event offset:(NSPointPointer)dragImageOffset NS_AVAILABLE_MAC(10_6);

/* This method is used by the collection view to determine a valid drop target. Based on the mouse position, the collection view will suggest a proposed index and drop operation. These values are in/out parameters and can be changed by the delegate to retarget the drop operation. The collection view will propose NSCollectionViewDropOn when the dragging location is closer to the middle of the item than either of its edges. Otherwise, it will propose NSCollectionViewDropBefore. You may override this default behavior by changing proposedDropOperation or proposedDropIndex. This method must return a value that indicates which dragging operation the data source will perform. It must return something other than NSDragOperationNone to accept the drop.
 
    Note: to receive drag messages, you must first send -registerForDraggedTypes: to the collection view with the drag types you want to support (typically this is done in -awakeFromNib). You must implement this method for your collection view to be a drag destination.
    
    Multi-image drag and drop: You can set draggingFormation, animatesToDestination, numberOfValidItemsForDrop within this method.
 */
- (NSDragOperation)collectionView:(NSCollectionView *)collectionView validateDrop:(id <NSDraggingInfo>)draggingInfo proposedIndex:(NSInteger *)proposedDropIndex dropOperation:(NSCollectionViewDropOperation *)proposedDropOperation NS_AVAILABLE_MAC(10_6);

/* This method is called when the mouse is released over a collection view that previously decided to allow a drop via the above validateDrop method. At this time, the delegate should incorporate the data from the dragging pasteboard and update the collection view's contents. You must implement this method for your collection view to be a drag destination.

    Multi-image drag and drop: If draggingInfo.animatesToDestination is set to YES, you should enumerate and update the dragging items with the proper image components and frames so that they dragged images animate to the proper locations.
 */
- (BOOL)collectionView:(NSCollectionView *)collectionView acceptDrop:(id <NSDraggingInfo>)draggingInfo index:(NSInteger)index dropOperation:(NSCollectionViewDropOperation)dropOperation NS_AVAILABLE_MAC(10_6);


/* Multi-image drag and drop */

/* Dragging Source Support - Required for multi-image drag and drop. Return a custom object that implements NSPasteboardWriting (or simply use NSPasteboardItem), or nil to prevent dragging for the item. For each valid item returned, NSCollectionView will create an NSDraggingItem with the draggingFrame equal to the frame of the item view at the given index and components from -[NSCollectionViewItem draggingItem]. If this method is implemented, then -collectionView:writeItemsAtIndexes:toPasteboard: and -collectionView:draggingImageForItemsAtIndexes:withEvent:offset: will not be called.
 */
- (id <NSPasteboardWriting>)collectionView:(NSCollectionView *)collectionView pasteboardWriterForItemAtIndex:(NSUInteger)index;

/* Dragging Source Support - Optional. Implement this method to know when the dragging session is about to begin and to potentially modify the dragging session.
 */
- (void)collectionView:(NSCollectionView *)collectionView draggingSession:(NSDraggingSession *)session willBeginAtPoint:(NSPoint)screenPoint forItemsAtIndexes:(NSIndexSet *)indexes;

/* Dragging Source Support - Optional. Implement this method to know when the dragging session has ended. This delegate method can be used to know when the dragging source operation ended at a specific location, such as the trash (by checking for an operation of NSDragOperationDelete).
 */
- (void)collectionView:(NSCollectionView *)collectionView draggingSession:(NSDraggingSession *)session endedAtPoint:(NSPoint)screenPoint dragOperation:(NSDragOperation)operation;

/* Dragging Destination Support - Required for multi-image drag and drop. Implement this method to update dragging items as they are dragged over the view. Typically this will involve calling [draggingInfo enumerateDraggingItemsWithOptions:forView:classes:searchOptions:usingBlock:] and setting the draggingItem's imageComponentsProvider to a proper image based on the NSDraggingItem's -item value.
 */
- (void)collectionView:(NSCollectionView *)collectionView updateDraggingItemsForDrag:(id <NSDraggingInfo>)draggingInfo;

@end

