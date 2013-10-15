/*
        NSOutlineView.h
        Application Kit
        Copyright (c) 1997-2004, Apple Computer, Inc.
        All rights reserved.
*/

#import <AppKit/NSTableView.h>
#import <AppKit/AppKitDefines.h>
#import <CoreFoundation/CFDictionary.h>

@class NSButtonCell;
@class NSTableView;
@class NSTableHeaderView;
@class NSTableColumn;
@class NSMouseTracker;
@class NSNotification;
@class NSString;

typedef struct __OvFlags {
#ifdef __BIG_ENDIAN__
    unsigned int	delegateWillDisplayCell:1;
    unsigned int	delegateShouldEditTableColumn:1;
    unsigned int	delegateShouldSelectItem:1;
    unsigned int	delegateShouldSelectTableColumn:1;
    unsigned int	delegateSelectionShouldChangeInOutlineView:1;
    unsigned int	delegateShouldCollapseItem:1;
    unsigned int	delegateShouldExpandItem:1;
    unsigned int	autoresizesOutlineColumn:1;
    unsigned int	autoSaveExpandItems:1;
    unsigned int	enableExpandNotifications:1;
    unsigned int	delegateWillDisplayOutlineCell:1;
    unsigned int	removeChildInProgress:1;
    unsigned int 	selectionAdjustmentDisabled:1;
    unsigned int	autoExpandFlashState:1;
    unsigned int	compatCollapseForceClearsExpandState:1;
    unsigned int        delegateHeightOfRowByItem:1;
    unsigned int        delayRowEntryFreeDisabled:1;
    unsigned int        numberOfRowsDataExpandEntered:1;
    unsigned int	_reserved:14;
#else
    unsigned int	_reserved:14;
    unsigned int        numberOfRowsDataExpandEntered:1;
    unsigned int        delayRowEntryFreeDisabled:1;
    unsigned int        delegateHeightOfRowByItem:1;
    unsigned int	compatCollapseForceClearsExpandState:1;
    unsigned int	autoExpandFlashState:1;
    unsigned int 	selectionAdjustmentDisabled:1;
    unsigned int	removeChildInProgress:1;
    unsigned int	delegateWillDisplayOutlineCell:1;
    unsigned int	enableExpandNotifications:1;
    unsigned int	autoSaveExpandItems:1;
    unsigned int	autoresizesOutlineColumn:1;
    unsigned int	delegateShouldExpandItem:1;
    unsigned int	delegateShouldCollapseItem:1;
    unsigned int	delegateSelectionShouldChangeInOutlineView:1;
    unsigned int	delegateShouldSelectTableColumn:1;
    unsigned int	delegateShouldSelectItem:1;
    unsigned int	delegateShouldEditTableColumn:1;
    unsigned int	delegateWillDisplayCell:1;
#endif
} _OVFlags;

enum { NSOutlineViewDropOnItemIndex = -1 };  // May be used as a valid childIndex of a drop target item.  In this case, the drop will happen directly on the target item.

@interface NSOutlineView : NSTableView {
  @private
    int			    _numberOfRows;
    struct __NSOVRowEntry  *_rowEntryTree;
    CFMutableDictionaryRef  _itemToEntryMap;
    int			 _unused2;
    int			 _unused3;
    int			 _unused1;
    NSTableColumn	*_outlineTableColumn;
    BOOL                 _initedRows;
    BOOL		 _indentationMarkerInCell;
    int			 _indentationPerLevel;
    NSButtonCell       	*_outlineCell;
    NSRect		 _trackingOutlineFrame;
    NSMouseTracker 	*_tracker;
    id 			 _unused4;
    _OVFlags		 _ovFlags;
    id			 _ovLock;
    long       		*_indentArray;
    long		 _originalWidth;
    id			 _expandSet;
    id			 _expandSetToExpandItemsInto;
    long       		 _indentArraySize;
    NSButtonCell        *_trackingOutlineCell;
    int                 _trackingRow;
    id                  _ovReserved;
}

/* The OutlineTableColumn is the column that displays data in a hierarchical fashion, indented one identationlevel per level, decorated with indentation marker.
*/
- (void)setOutlineTableColumn: (NSTableColumn *)outlineTableColumn;
- (NSTableColumn *)outlineTableColumn;

/* Outline control
*/
- (BOOL)isExpandable:(id)item;		// can the item contain other items?
- (void)expandItem:(id)item expandChildren:(BOOL)expandChildren;
- (void)expandItem:(id)item;		// Above with expandChildren == NO.
- (void)collapseItem:(id)item collapseChildren:(BOOL)collapseChildren;
- (void)collapseItem:(id)item;		// Above with collapseChildren == NO.
- (void)reloadItem:(id)item reloadChildren:(BOOL)reloadChildren;
- (void)reloadItem:(id)item;		// Above with reloadChildren == NO.

/* Item/Row translation
*/
- (id)itemAtRow:(int)row;
- (int)rowForItem:(id)item;

/* Indentation
*/
- (int)levelForItem:(id)item;
- (int)levelForRow:(int)row;
- (BOOL)isItemExpanded:(id)item;
- (void)setIndentationPerLevel:(float)indentationPerLevel;
- (float)indentationPerLevel;
- (void)setIndentationMarkerFollowsCell: (BOOL)drawInCell; // The indentation marker is the visual indicator that shows an item is expandable (i.e. disclosure triangle).
- (BOOL)indentationMarkerFollowsCell;
- (void)setAutoresizesOutlineColumn: (BOOL)resize;
- (BOOL)autoresizesOutlineColumn;

/* Drag and Drop
*/

/* To be used from validateDrop: in order to "re-target" the proposed drop.  To specify a drop on an item I, one would specify item=I, and index=NSOutlineViewDropOnItemIndex.  To specify a drop between child 2 and 3 of an item I, on would specify item=I, and index=3 (children are zero-base indexed).  To specify a drop on an un-expandable item I, one would specify item=I, and index=NSOutlineViewDropOnItemIndex.
*/
- (void)setDropItem:(id)item dropChildIndex:(int)index;

/* This method returns YES to indicate that auto expanded items should return to their original collapsed state.  Override this method to provide custom behavior.  'deposited' tells wether or not the drop terminated due to a successful drop (as indicated by the return value from acceptDrop:).  Note that exiting the view will be treated the same as a failed drop.
*/
- (BOOL)shouldCollapseAutoExpandedItemsForDeposited:(BOOL)deposited;

/* Persistence
*/
- (BOOL)autosaveExpandedItems;
- (void)setAutosaveExpandedItems:(BOOL)save;

@end

// Data Source Note: Specifying nil as the item will refer to the "root" item(s).
@interface NSObject(NSOutlineViewDataSource)
/* required methods
*/
- (id)outlineView:(NSOutlineView *)outlineView child:(int)index ofItem:(id)item;
- (BOOL)outlineView:(NSOutlineView *)outlineView isItemExpandable:(id)item;
- (int)outlineView:(NSOutlineView *)outlineView numberOfChildrenOfItem:(id)item;
- (id)outlineView:(NSOutlineView *)outlineView objectValueForTableColumn:(NSTableColumn *)tableColumn byItem:(id)item;

/* optional methods
*/
- (void)outlineView:(NSOutlineView *)outlineView setObjectValue:(id)object forTableColumn:(NSTableColumn *)tableColumn byItem:(id)item;
- (id)outlineView:(NSOutlineView *)outlineView itemForPersistentObject:(id)object;
- (id)outlineView:(NSOutlineView *)outlineView persistentObjectForItem:(id)item;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

/* optional - sorting support
        This is the indication that sorting needs to be done. Typically the data source will sort its data, reload, and adjust selections.
*/
- (void)outlineView:(NSOutlineView *)outlineView sortDescriptorsDidChange:(NSArray *)oldDescriptors;

#endif

/* optional - drag and drop support
*/

/* This method is called after it has been determined that a drag should begin, but before the drag has been started.  To refuse the drag, return NO.  To start a drag, return YES and place the drag data onto the pasteboard (data, owner, etc...).  The drag image and other drag related information will be set up and provided by the outline view once this call returns with YES.  The items array is the list of items that will be participating in the drag.
*/
- (BOOL)outlineView:(NSOutlineView *)olv writeItems:(NSArray*)items toPasteboard:(NSPasteboard*)pboard;

/* This method is used by NSOutlineView to determine a valid drop target.  Based on the mouse position, the outline view will suggest a proposed drop location.  This method must return a value that indicates which dragging operation the data source will perform.  The data source may "re-target" a drop if desired by calling setDropItem:dropChildIndex: and returning something other than NSDragOperationNone.  One may choose to re-target for various reasons (eg. for better visual feedback when inserting into a sorted position).
*/
- (NSDragOperation)outlineView:(NSOutlineView*)olv validateDrop:(id <NSDraggingInfo>)info proposedItem:(id)item proposedChildIndex:(int)index;

/* This method is called when the mouse is released over an outline view that previously decided to allow a drop via the validateDrop method.  The data source should incorporate the data from the dragging pasteboard at this time.
*/
- (BOOL)outlineView:(NSOutlineView*)olv acceptDrop:(id <NSDraggingInfo>)info item:(id)item childIndex:(int)index;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* NSOutlineView data source objects can support file promised drags via by adding  NSFilesPromisePboardType to the pasteboard in outlineView:writeItems:toPasteboard:.  NSOutlineView implements -namesOfPromisedFilesDroppedAtDestination: to return the results of this data source method.  This method should returns an array of filenames for the created files (filenames only, not full paths).  The URL represents the drop location.  For more information on file promise dragging, see documentation on the NSDraggingSource protocol and -namesOfPromisedFilesDroppedAtDestination:.
*/
- (NSArray *)outlineView:(NSOutlineView *)olv namesOfPromisedFilesDroppedAtDestination:(NSURL *)dropDestination forDraggedItems:(NSArray *)items;
#endif

@end

@interface NSObject(NSOutlineViewDelegate)
/* NSOutlineView replacements
*/
- (void)outlineView:(NSOutlineView *)outlineView willDisplayCell:(id)cell forTableColumn:(NSTableColumn *)tableColumn item:(id)item;
- (BOOL)outlineView:(NSOutlineView *)outlineView shouldEditTableColumn:(NSTableColumn *)tableColumn item:(id)item;
- (BOOL)selectionShouldChangeInOutlineView:(NSOutlineView *)outlineView;
- (BOOL)outlineView:(NSOutlineView *)outlineView shouldSelectItem:(id)item;
- (BOOL)outlineView:(NSOutlineView *)outlineView shouldSelectTableColumn:(NSTableColumn *)tableColumn;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)outlineView:(NSOutlineView *)outlineView mouseDownInHeaderOfTableColumn:(NSTableColumn *)tableColumn;
- (void)outlineView:(NSOutlineView *)outlineView didClickTableColumn:(NSTableColumn *)tableColumn;
- (void)outlineView:(NSOutlineView *)outlineView didDragTableColumn:(NSTableColumn *)tableColumn;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* tool tip support
        When the user pauses over a cell, the value returned from this method will be displayed in a tooltip.  'point' represents the current mouse location in view coordinates.  If you don't want a tooltip at that location, return nil or the empty string.  On entry, 'rect' represents the proposed active area of the tooltip.  By default, rect is computed as [cell drawingRectForBounds:cellFrame].  To control the default active area, you can modify the 'rect' parameter.
*/
- (NSString *)outlineView:(NSOutlineView *)ov toolTipForCell:(NSCell *)cell rect:(NSRectPointer)rect tableColumn:(NSTableColumn *)tc item:(id)item mouseLocation:(NSPoint)mouseLocation;

/* Optional - Variable Row Heights
        Implement this method to support an outline view with varying row heights.  The height returned by this method should not include intercell spacing and must be >0.  Performance Considerations: For large tables in particular, you should make sure that this method is efficient.  NSTableView may cache the values this method returns.  So if you would like to change a row's height make sure to invalidate the row height by calling -noteHeightOfRowsWithIndexesChanged:.  NSTableView automatically invalidates its entire row height cache in -reloadData, and -noteNumberOfRowsChanged.
*/
- (float)outlineView:(NSOutlineView *)outlineView heightOfRowByItem:(id)item;
#endif

/* NSOutlineView specific
*/
- (BOOL)outlineView:(NSOutlineView *)outlineView shouldExpandItem:(id)item;
- (BOOL)outlineView:(NSOutlineView *)outlineView shouldCollapseItem:(id)item;
- (void)outlineView:(NSOutlineView *)outlineView willDisplayOutlineCell:(id)cell forTableColumn:(NSTableColumn *)tableColumn item:(id)item;

@end


/* Notifications */
APPKIT_EXTERN NSString *NSOutlineViewSelectionDidChangeNotification;
APPKIT_EXTERN NSString *NSOutlineViewColumnDidMoveNotification;		// @"NSOldColumn", @"NSNewColumn"
APPKIT_EXTERN NSString *NSOutlineViewColumnDidResizeNotification;	// @"NSTableColumn", @"NSOldWidth"
APPKIT_EXTERN NSString *NSOutlineViewSelectionIsChangingNotification;

APPKIT_EXTERN NSString *NSOutlineViewItemWillExpandNotification;	// NSObject
APPKIT_EXTERN NSString *NSOutlineViewItemDidExpandNotification;		// NSObject
APPKIT_EXTERN NSString *NSOutlineViewItemWillCollapseNotification;	// NSObject
APPKIT_EXTERN NSString *NSOutlineViewItemDidCollapseNotification;	// NSObject

@interface NSObject(NSOutlineViewNotifications)
- (void)outlineViewSelectionDidChange:(NSNotification *)notification;
- (void)outlineViewColumnDidMove:(NSNotification *)notification;
- (void)outlineViewColumnDidResize:(NSNotification *)notification;
- (void)outlineViewSelectionIsChanging:(NSNotification *)notification;
- (void)outlineViewItemWillExpand:(NSNotification *)notification;
- (void)outlineViewItemDidExpand:(NSNotification *)notification;
- (void)outlineViewItemWillCollapse:(NSNotification *)notification;
- (void)outlineViewItemDidCollapse:(NSNotification *)notification;
@end

