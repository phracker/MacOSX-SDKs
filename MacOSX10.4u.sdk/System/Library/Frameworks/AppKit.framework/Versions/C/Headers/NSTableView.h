/*
        NSTableView.h
        Application Kit
        Copyright (c) 1995-2004, Apple Computer, Inc.
        All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSDragging.h>
#import <AppKit/NSUserInterfaceValidation.h>

@class NSTableHeaderView;
@class NSTableColumn;
@class NSMutableArray;
@class NSIndexSet, NSMutableIndexSet;

typedef struct __TvFlags {
#ifdef __BIG_ENDIAN__
    unsigned int	allowsColumnReordering:1;
    unsigned int	allowsColumnResizing:1;
    unsigned int	oldDrawsGridFlag:1;
    unsigned int	allowsEmptySelection:1;
    unsigned int	allowsMultipleSelection:1;
    unsigned int	allowsColumnSelection:1;
    unsigned int	selectionType:2;
    unsigned int	changingLayout:1;
    unsigned int	compareWidthWithSuperview:2;
    unsigned int	delegateWillDisplayCell:1;
    unsigned int	delegateShouldEditTableColumn:1;
    unsigned int	delegateShouldSelectRow:1;
    unsigned int	delegateShouldSelectTableColumn:1;
    unsigned int	delegateSelectionShouldChangeInTableView:1;
    unsigned int	oldAutoresizesAllColumnsToFit:1;
    unsigned int	dataSourceSetObjectValue:1;
    unsigned int	selectionPostingDisableCount:7;
    unsigned int	movedPostingDisableCount:6;
    unsigned int	refusesFirstResponder:1;
#else
    unsigned int	refusesFirstResponder:1;
    unsigned int	movedPostingDisableCount:6;
    unsigned int	selectionPostingDisableCount:7;
    unsigned int	dataSourceSetObjectValue:1;
    unsigned int	oldAutoresizesAllColumnsToFit:1;
    unsigned int	delegateSelectionShouldChangeInTableView:1;
    unsigned int	delegateShouldSelectTableColumn:1;
    unsigned int	delegateShouldSelectRow:1;
    unsigned int	delegateShouldEditTableColumn:1;
    unsigned int	delegateWillDisplayCell:1;
    unsigned int	compareWidthWithSuperview:2;
    unsigned int	changingLayout:1;
    unsigned int	selectionType:2;
    unsigned int	allowsColumnSelection:1;
    unsigned int	allowsMultipleSelection:1;
    unsigned int	allowsEmptySelection:1;
    unsigned int	oldDrawsGridFlag:1;
    unsigned int	allowsColumnResizing:1;
    unsigned int	allowsColumnReordering:1;
#endif
} _TvFlags;

/* In drag and drop, used to specify a dropOperation.  For example, given a table with N rows (numbered with row 0 at the top visually), a row of N-1 and operation of NSTableViewDropOn would specify a drop on the last row.  To specify a drop below the last row, one would use a row of N and NSTableViewDropAbove for the operation.
*/
typedef enum { NSTableViewDropOn, NSTableViewDropAbove } NSTableViewDropOperation;


@interface NSTableView : NSControl <NSUserInterfaceValidations>
{
    /*All instance variables are private*/
    NSTableHeaderView	*_headerView;
    NSView		*_cornerView;
    NSMutableArray     	*_tableColumns;
    NSCell		*_editingCell;
    id			_delegate;
    id			_dataSource;
    NSSize		_intercellSpacing;
    float		_rowHeight;
    int			_lastSelectedColumn;
    int			_lastSelectedRow;
    int			_editingRow;
    int			_editingColumn;
    NSMutableIndexSet	*_selectedColumns;
    NSMutableIndexSet	*_selectedRows;
    NSImage		*_bodyDragImage;
    NSColor		*_backgroundColor;
    NSColor		*_gridColor;
    float		_dragYPos;
    id			_target;
    SEL                 _action;
    SEL                 _doubleAction;
    NSRect		_rectOfLastColumn;
    int			_lastCachedRectColumn;
    NSRect		_rectOfLastRow;
    int			_lastCachedRectRow;
    _TvFlags            _tvFlags;
    id                  _reserved;
}

- (void)setDataSource:(id)aSource;
- (id)dataSource;
- (void)setDelegate:(id)delegate;
- (id)delegate;
- (void)setHeaderView:(NSTableHeaderView *)headerView;
- (NSTableHeaderView *)headerView;
- (void)setCornerView:(NSView *)cornerView;
- (NSView *)cornerView;
- (void)setAllowsColumnReordering:(BOOL)flag;
- (BOOL)allowsColumnReordering;

/* Controls whether the user can attemp to resize columns by dragging between headers. If flag is YES the user can resize columns; if flag is NO the user canÕt. The default is YES. Columns can only be resized if a column allows user resizing.  See NSTableColumn setResizingMask: for more details.  You can always change columns programmatically regardless of this setting.
*/
- (void)setAllowsColumnResizing:(BOOL)flag;
- (BOOL)allowsColumnResizing;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* The column auto resizing style controls resizing in response to a table view frame change.
   Compatability Note: This method replaces -setAutoresizesAllColumnsToFit:.
*/
typedef enum {
    /* Turn off column autoresizing
    */
    NSTableViewNoColumnAutoresizing = 0,

    /* Autoresize all columns by distributing equal shares of space simultaeously
    */
    NSTableViewUniformColumnAutoresizingStyle,

    /* Autoresize each table column one at a time.  Proceed to the next column when 
       the current column can no longer be autoresized (when it reaches maximum/minimum size).
    */
    NSTableViewSequentialColumnAutoresizingStyle,        // Start with the last autoresizable column, proceed to the first.
    NSTableViewReverseSequentialColumnAutoresizingStyle, // Start with the first autoresizable column, proceed to the last.

    /* Autoresize only one table column one at a time.  When that table column can no longer be
       resized, stop autoresizing.  Normally you should use one of the Sequential autoresizing
       modes instead.
    */
    NSTableViewLastColumnOnlyAutoresizingStyle,
    NSTableViewFirstColumnOnlyAutoresizingStyle
} NSTableViewColumnAutoresizingStyle;

- (void)setColumnAutoresizingStyle:(NSTableViewColumnAutoresizingStyle)style;
- (NSTableViewColumnAutoresizingStyle)columnAutoresizingStyle;
#endif


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
/* Grid styles	
*/
enum {
    NSTableViewGridNone                    = 0,
    NSTableViewSolidVerticalGridLineMask   = 1 << 0,
    NSTableViewSolidHorizontalGridLineMask = 1 << 1
};

- (void)setGridStyleMask:(unsigned int)gridType;
- (unsigned int)gridStyleMask;
#endif

- (void)setIntercellSpacing:(NSSize)aSize;
- (NSSize)intercellSpacing;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
/* Configures the table to use either the standard alternating row colors, or a solid color for its background. 
*/
- (void)setUsesAlternatingRowBackgroundColors:(BOOL)useAlternatingRowColors;
- (BOOL)usesAlternatingRowBackgroundColors;
#endif

- (void)setBackgroundColor:(NSColor *)color;
- (NSColor *)backgroundColor;

- (void)setGridColor:(NSColor *)color;
- (NSColor *)gridColor;


- (void)setRowHeight:(float)rowHeight;
- (float)rowHeight;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* If the delegate implements -tableView:heightOfRow:, this method immediately re-tiles the table view using row heights it provides.
*/
- (void)noteHeightOfRowsWithIndexesChanged:(NSIndexSet *)indexSet;
#endif

- (NSArray *)tableColumns;
- (int)numberOfColumns;
- (int)numberOfRows;

- (void)addTableColumn:(NSTableColumn *)column;
- (void)removeTableColumn:(NSTableColumn *)column;
- (int)columnWithIdentifier:(id)identifier;
- (NSTableColumn *)tableColumnWithIdentifier:(id)identifier;

- (void)tile;
- (void)sizeToFit;
- (void)sizeLastColumnToFit;
- (void)scrollRowToVisible:(int)row;
- (void)scrollColumnToVisible:(int)column;
- (void)moveColumn:(int)column toColumn:(int)newIndex;

- (void)reloadData;
- (void)noteNumberOfRowsChanged;

- (int)editedColumn;
- (int)editedRow;
- (int)clickedColumn;
- (int)clickedRow;

- (void)setDoubleAction:(SEL)aSelector;
- (SEL)doubleAction;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

/* Sorting support
        The array of sort descriptors is archived.  Sort descriptors will persist along with other column information if an autosave name is set.
*/
- (void)setSortDescriptors:(NSArray *)array;
- (NSArray *)sortDescriptors;

#endif

/* Support for little "indicator" images in table header cells.
*/
- (void)setIndicatorImage:(NSImage *)anImage inTableColumn:(NSTableColumn *)tc;
- (NSImage *)indicatorImageInTableColumn:(NSTableColumn *)tc;

/* Support for highlightable column header, for use with row selection.
*/
- (void)setHighlightedTableColumn:(NSTableColumn *)tc;
- (NSTableColumn *)highlightedTableColumn;

/*
 * Drag and Drop
 */

- (void)setVerticalMotionCanBeginDrag:(BOOL)flag;
- (BOOL)verticalMotionCanBeginDrag;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* The return value indicates whether the receiver can attempt to initiate a row drag at 'mouseDownPoint'. Return NO to disallow initiating drags at the given location.
*/
- (BOOL)canDragRowsWithIndexes:(NSIndexSet *)rowIndexes atPoint:(NSPoint)mouseDownPoint;

/* This method computes and returns an image to use for dragging.  Override this to return a custom image.  'dragRows' represents the rows participating in the drag.  'tableColumns' represent the columns that should be in the output image.  Note that drawing may be clipped to the visible rows, and columns.  'dragEvent' is a reference to the mouse down event that began the drag.  'dragImageOffset' is an in/out parameter.  This method will be called with dragImageOffset set to NSZeroPoint, but it can be modified to re-position the returned image.  A dragImageOffset of NSZeroPoint will cause the image to be centered under the mouse.

   Compatability Note: This method replaces dragImageOffset:event:dragImageOffset:.  If present, this is used instead of the deprecated method.
*/
- (NSImage *)dragImageForRowsWithIndexes:(NSIndexSet *)dragRows tableColumns:(NSArray *)tableColumns event:(NSEvent*)dragEvent offset:(NSPointPointer)dragImageOffset;

/* Configures the default value returned from -draggingSourceOperationMaskForLocal:.  An isLocal value of YES indicates that 'mask' applies when the destination object is in the same application.  A isLocal value of NO indicates that 'mask' applies when the destination object in an application outside the receiver's application.  NSTableView will archive the values you set for each isLocal setting.
*/
- (void)setDraggingSourceOperationMask:(unsigned int)mask forLocal:(BOOL)isLocal;
#endif

/* To be used from validateDrop: if you wish to "re-target" the proposed drop.  To specify a drop on the second row, one would specify row=2, and op=NSTableViewDropOn.  To specify a drop below the last row, one would specify row=[tv numberOfRows], and op=NSTableViewDropAbove.
*/
- (void)setDropRow:(int)row dropOperation:(NSTableViewDropOperation)op;


/*
 * Selection
 */
- (void)setAllowsMultipleSelection:(BOOL)flag;
- (BOOL)allowsMultipleSelection;
- (void)setAllowsEmptySelection:(BOOL)flag;
- (BOOL)allowsEmptySelection;
- (void)setAllowsColumnSelection:(BOOL)flag;
- (BOOL)allowsColumnSelection;
- (void)selectAll:(id)sender;
- (void)deselectAll:(id)sender;


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

/* Sets the column selection using the indexes.  Selection is set/extended based on the extend flag. 
   Compatability Note: This method replaces selectColumn:byExtendingSelection:
       If a subclasser implements only the deprecated single-index method (selectColumn:byExtendingSelection:), the single-index method will be invoked for each index.  If a subclasser implements the multi-index method (selectColumnIndexes:byExtendingSelection:), the deprecated single-index version method will not be used.  This allows subclassers already overriding the single-index method to still receive a selection message.  Note: to avoid cycles, subclassers of this method and single-index method should not call each other.
*/
- (void)selectColumnIndexes:(NSIndexSet *)indexes byExtendingSelection:(BOOL)extend;

/* Sets the row selection using the indexes.  Selection is set/extended based on the extend flag. 
   Compatability Note: This method replaces selectRow:byExtendingSelection:
       If a subclasser implements only the deprecated single-index method (selectRow:byExtendingSelection:), the single-index method will be invoked for each index.  If a subclasser implements the multi-index method (selectRowIndexes:byExtendingSelection:), the deprecated single-index version method will not be used.  This allows subclassers already overriding the single-index method to still receive a selection message.  Note: to avoid cycles, subclassers of this method and single-index method should not call each other.
*/
- (void)selectRowIndexes:(NSIndexSet *)indexes byExtendingSelection:(BOOL)extend;

- (NSIndexSet *)selectedColumnIndexes;
- (NSIndexSet *)selectedRowIndexes;
#endif

- (void)deselectColumn:(int)column;
- (void)deselectRow:(int)row;
- (int)selectedColumn;
- (int)selectedRow;
- (BOOL)isColumnSelected:(int)row;
- (BOOL)isRowSelected:(int)row;
- (int)numberOfSelectedColumns;
- (int)numberOfSelectedRows;


/*
 * Layout support
 */
- (NSRect)rectOfColumn:(int)column;
- (NSRect)rectOfRow:(int)row;
- (NSRange)columnsInRect:(NSRect)rect;
- (NSRange)rowsInRect:(NSRect)rect;
- (int)columnAtPoint:(NSPoint)point;
- (int)rowAtPoint:(NSPoint)point;
- (NSRect)frameOfCellAtColumn:(int)column row:(int)row;


/*
 * Text delegate methods
 */
- (BOOL)textShouldBeginEditing:(NSText *)textObject;
- (BOOL)textShouldEndEditing:(NSText *)textObject;
- (void)textDidBeginEditing:(NSNotification *)notification;
- (void)textDidEndEditing:(NSNotification *)notification;
- (void)textDidChange:(NSNotification *)notification;

/*
 * Persistence methods
 */
- (void)setAutosaveName:(NSString *)name;
- (NSString *)autosaveName;
- (void)setAutosaveTableColumns:(BOOL)save;
- (BOOL)autosaveTableColumns;

/*
 * For subclassers
 */
- (void)editColumn:(int)column row:(int)row withEvent:(NSEvent *)theEvent select:(BOOL)select;
- (void)drawRow:(int)row clipRect:(NSRect)rect;
- (void)highlightSelectionInClipRect:(NSRect)rect;
- (void)drawGridInClipRect:(NSRect)rect;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)drawBackgroundInClipRect:(NSRect)clipRect;
#endif


/*
 * Deprecated Methods
 */
 
// Deprecated in Mac OS 10.3.  Calls setGridStyleMask:, setting grid style to either None, or vertical and horizonal solid grid lines as appropriate.
- (void)setDrawsGrid:(BOOL)flag;
// Deprecated in Mac OS 10.3.  Returns YES if gridStyleMask returns anything other than NSTableViewGridNone.
- (BOOL)drawsGrid;

// Deprecated in Mac OS 10.3.  You should use selectColumnIndexes:byExtendingSelection: instead.  See that method for more details.
- (void)selectColumn:(int)column byExtendingSelection:(BOOL)extend;
// Deprecated in Mac OS 10.3.  You should use selectRowIndexes:byExtendingSelection: instead.  See that method for more details.
- (void)selectRow:(int)row byExtendingSelection:(BOOL)extend;
// Deprecated in Mac OS 10.3.  You should use selectedColumnIndexes instead.
- (NSEnumerator *)selectedColumnEnumerator;
// Deprecated in Mac OS 10.3.  You should use selectedRowIndexes instead.
- (NSEnumerator *)selectedRowEnumerator;

// Deprecated in Mac OS 10.4.  You should use / override dragImageForRowsWithIndexes:tableColumns:event:dragImageOffset: instead.
- (NSImage*)dragImageForRows:(NSArray*)dragRows event:(NSEvent*)dragEvent dragImageOffset:(NSPointPointer)dragImageOffset;

// Deprecated in Mac OS 10.4.  You should use setColumnAutoresizingStyle: instead.  To preserve compatibility, if flag is YES, This method calls setColumnAutoresizingStyle:NSTableViewUniformColumnAutoresizingStyle.  If flag is NO, this method calls setColumnAutoresizingStyle:NSTableViewLastColumnOnlyAutoresizingStyle.
- (void)setAutoresizesAllColumnsToFit:(BOOL)flag;
- (BOOL)autoresizesAllColumnsToFit;

@end

@interface NSObject(NSTableViewDelegate)

- (void)tableView:(NSTableView *)tableView willDisplayCell:(id)cell forTableColumn:(NSTableColumn *)tableColumn row:(int)row;
- (BOOL)tableView:(NSTableView *)tableView shouldEditTableColumn:(NSTableColumn *)tableColumn row:(int)row;
- (BOOL)selectionShouldChangeInTableView:(NSTableView *)aTableView;
- (BOOL)tableView:(NSTableView *)tableView shouldSelectRow:(int)row;
- (BOOL)tableView:(NSTableView *)tableView shouldSelectTableColumn:(NSTableColumn *)tableColumn;

- (void) tableView:(NSTableView*)tableView mouseDownInHeaderOfTableColumn:(NSTableColumn *)tableColumn;
- (void) tableView:(NSTableView*)tableView didClickTableColumn:(NSTableColumn *)tableColumn;
- (void) tableView:(NSTableView*)tableView didDragTableColumn:(NSTableColumn *)tableColumn;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* tool tip support
        When the user pauses over a cell, the value returned from this method will be displayed in a tooltip.  'point' represents the current mouse location in view coordinates.  If you don't want a tooltip at that location, return nil or the empty string.  On entry, 'rect' represents the proposed active area of the tooltip.  By default, rect is computed as [cell drawingRectForBounds:cellFrame].  To control the default active area, you can modify the 'rect' parameter.
*/
- (NSString *)tableView:(NSTableView *)tv toolTipForCell:(NSCell *)cell rect:(NSRectPointer)rect tableColumn:(NSTableColumn *)tc row:(int)row mouseLocation:(NSPoint)mouseLocation;

/* Optional - Variable Row Heights
        Implement this method to support a table with varying row heights.  The height returned by this method should not include intercell spacing and must be >0.  Performance Considerations: For large tables in particular, you should make sure that this method is efficient.  NSTableView may cache the values this method returns.  So if you would like to change a row's height make sure to invalidate the row height by calling -noteHeightOfRowsWithIndexesChanged:.  NSTableView automatically invalidates its entire row height cache in -reloadData, and -noteNumberOfRowsChanged.
*/
- (float)tableView:(NSTableView *)tableView heightOfRow:(int)row;
#endif

@end

/*
 * Notifications
 */
APPKIT_EXTERN NSString *NSTableViewSelectionDidChangeNotification;
APPKIT_EXTERN NSString *NSTableViewColumnDidMoveNotification;       // @"NSOldColumn", @"NSNewColumn"
APPKIT_EXTERN NSString *NSTableViewColumnDidResizeNotification;     // @"NSTableColumn", @"NSOldWidth"
APPKIT_EXTERN NSString *NSTableViewSelectionIsChangingNotification;


@interface NSObject(NSTableViewNotifications)
- (void)tableViewSelectionDidChange:(NSNotification *)notification;
- (void)tableViewColumnDidMove:(NSNotification *)notification;
- (void)tableViewColumnDidResize:(NSNotification *)notification;
- (void)tableViewSelectionIsChanging:(NSNotification *)notification;
@end

@interface NSObject(NSTableDataSource)
/* required methods
*/
- (int)numberOfRowsInTableView:(NSTableView *)tableView;
- (id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(int)row;

/* optional - editing support
*/
- (void)tableView:(NSTableView *)tableView setObjectValue:(id)object forTableColumn:(NSTableColumn *)tableColumn row:(int)row;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

/* optional - sorting support
        This is the indication that sorting needs to be done.  Typically the data source will sort its data, reload, and adjust selections.
*/
- (void)tableView:(NSTableView *)tableView sortDescriptorsDidChange:(NSArray *)oldDescriptors;

#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* optional - drag and drop support
        This method is called after it has been determined that a drag should begin, but before the drag has been started.  To refuse the drag, return NO.  To start a drag, return YES and place the drag data onto the pasteboard (data, owner, etc...).  The drag image and other drag related information will be set up and provided by the table view once this call returns with YES.  'rowIndexes' contains the row indexes that will be participating in the drag.

   Compatability Note: This method replaces tableView:writeRows:toPasteboard:.  If present, this is used instead of the deprecated method.
*/
- (BOOL)tableView:(NSTableView *)tv writeRowsWithIndexes:(NSIndexSet *)rowIndexes toPasteboard:(NSPasteboard*)pboard;
#endif

/* This method is used by NSTableView to determine a valid drop target.  Based on the mouse position, the table view will suggest a proposed drop location.  This method must return a value that indicates which dragging operation the data source will perform.  The data source may "re-target" a drop if desired by calling setDropRow:dropOperation: and returning something other than NSDragOperationNone.  One may choose to re-target for various reasons (eg. for better visual feedback when inserting into a sorted position).
*/
- (NSDragOperation)tableView:(NSTableView*)tv validateDrop:(id <NSDraggingInfo>)info proposedRow:(int)row proposedDropOperation:(NSTableViewDropOperation)op;

/* This method is called when the mouse is released over an outline view that previously decided to allow a drop via the validateDrop method.  The data source should incorporate the data from the dragging pasteboard at this time.
*/
- (BOOL)tableView:(NSTableView*)tv acceptDrop:(id <NSDraggingInfo>)info row:(int)row dropOperation:(NSTableViewDropOperation)op;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* NSTableView data source objects can support file promised drags via by adding  NSFilesPromisePboardType to the pasteboard in tableView:writeRowsWithIndexes:toPasteboard:.  NSTableView implements -namesOfPromisedFilesDroppedAtDestination: to return the results of this data source method.  This method should returns an array of filenames for the created files (filenames only, not full paths).  The URL represents the drop location.  For more information on file promise dragging, see documentation on the NSDraggingSource protocol and -namesOfPromisedFilesDroppedAtDestination:.
*/
- (NSArray *)tableView:(NSTableView *)tv namesOfPromisedFilesDroppedAtDestination:(NSURL *)dropDestination forDraggedRowsWithIndexes:(NSIndexSet *)indexSet;
#endif


/*
 * Deprecated Methods
 */
 
// Deprecated in Mac OS 10.4.  You should implement tableView:writeRowsWithIndexes:toPasteboard: instead.  See that method for more details.
- (BOOL)tableView:(NSTableView *)tv writeRows:(NSArray*)rows toPasteboard:(NSPasteboard*)pboard;
@end

