/*
        NSTableView.h
        Application Kit
        Copyright (c) 1995-2001, Apple Computer, Inc.
        All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSDragging.h>

@class NSTableHeaderView;
@class NSTableColumn;
@class _NSSparseArray;
@class NSMutableArray;

typedef struct __TvFlags {
#ifdef __BIG_ENDIAN__
    unsigned int	allowsColumnReordering:1;
    unsigned int	allowsColumnResizing:1;
    unsigned int	drawsGrid:1;
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
    unsigned int	autoresizesAllColumnsToFit:1;
    unsigned int	dataSourceSetObjectValue:1;
    unsigned int	selectionPostingDisableCount:7;
    unsigned int	movedPostingDisableCount:6;
    unsigned int	refusesFirstResponder:1;
#else
    unsigned int	refusesFirstResponder:1;
    unsigned int	movedPostingDisableCount:6;
    unsigned int	selectionPostingDisableCount:7;
    unsigned int	dataSourceSetObjectValue:1;
    unsigned int	autoresizesAllColumnsToFit:1;
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
    unsigned int	drawsGrid:1;
    unsigned int	allowsColumnResizing:1;
    unsigned int	allowsColumnReordering:1;
#endif
} _TvFlags;

typedef enum { NSTableViewDropOn, NSTableViewDropAbove } NSTableViewDropOperation;
        // In drag and drop, used to specify a dropOperation.  For example, given a table with N rows (numbered with row 0 at the top visually), a row of N-1 and operation of NSTableViewDropOn would specify a drop on the last row.  To specify a drop below the last row, one would use a row of N and NSTableViewDropAbove for the operation.


@interface NSTableView : NSControl
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
    _NSSparseArray	*_selectedColumns;
    _NSSparseArray	*_selectedRows;
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
    void*               _reserved;
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
- (void)setAllowsColumnResizing:(BOOL)flag;
- (BOOL)allowsColumnResizing;
- (void)setAutoresizesAllColumnsToFit:(BOOL)flag;
- (BOOL)autoresizesAllColumnsToFit;
- (void)setDrawsGrid:(BOOL)flag;
- (BOOL)drawsGrid;
- (void)setIntercellSpacing:(NSSize)aSize;
- (NSSize)intercellSpacing;
- (void)setBackgroundColor:(NSColor *)color;
- (NSColor *)backgroundColor;
- (void)setGridColor:(NSColor *)color;
- (NSColor *)gridColor;
- (void)setRowHeight:(float)rowHeight;
- (float)rowHeight;

- (NSArray *)tableColumns;
- (int)numberOfColumns;
- (int)numberOfRows;

- (void)addTableColumn:(NSTableColumn *)column;
- (void)removeTableColumn:(NSTableColumn *)column;
- (int)columnWithIdentifier:(id)identifier;
- (NSTableColumn *)tableColumnWithIdentifier:(id)identifier;

- (void)tile;
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

- (NSImage*)dragImageForRows:(NSArray*)dragRows event:(NSEvent*)dragEvent dragImageOffset:(NSPointPointer)dragImageOffset;
    // This method computes and returns an image to use for dragging.  Override this to return a custom image.  'dragRows' represents the rows participating in the drag.  'dragEvent' is a reference to the mouse down event that began the drag.  'dragImageOffset' is an in/out parameter.  This method will be called with dragImageOffset set to NSZeroPoint, but it can be modified to re-position the returned image.  A dragImageOffset of NSZeroPoint will cause the image to be centered under the mouse.

- (void)setDropRow:(int)row dropOperation:(NSTableViewDropOperation)op;
    // To be used from validateDrop: if you wish to "re-target" the proposed drop.  To specify a drop on the second row, one would specify row=2, and op=NSTableViewDropOn.  To specify a drop below the last row, one would specify row=[tv numberOfRows], and op=NSTableViewDropAbove.

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
- (void)selectColumn:(int)column byExtendingSelection:(BOOL)extend;
- (void)selectRow:(int)row byExtendingSelection:(BOOL)extend;
- (void)deselectColumn:(int)column;
- (void)deselectRow:(int)row;
- (int)selectedColumn;
- (int)selectedRow;
- (BOOL)isColumnSelected:(int)row;
- (BOOL)isRowSelected:(int)row;
- (int)numberOfSelectedColumns;
- (int)numberOfSelectedRows;
- (NSEnumerator *)selectedColumnEnumerator;
- (NSEnumerator *)selectedRowEnumerator;


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

@end

/*
 * Notifications
 */
APPKIT_EXTERN NSString *NSTableViewSelectionDidChangeNotification;
APPKIT_EXTERN NSString *NSTableViewColumnDidMoveNotification;		// @"NSOldColumn", @"NSNewColumn"
APPKIT_EXTERN NSString *NSTableViewColumnDidResizeNotification;	// @"NSTableColumn", @"NSOldWidth"
APPKIT_EXTERN NSString *NSTableViewSelectionIsChangingNotification;


@interface NSObject(NSTableViewNotifications)
- (void)tableViewSelectionDidChange:(NSNotification *)notification;
- (void)tableViewColumnDidMove:(NSNotification *)notification;
- (void)tableViewColumnDidResize:(NSNotification *)notification;
- (void)tableViewSelectionIsChanging:(NSNotification *)notification;
@end

@interface NSObject(NSTableDataSource)
- (int)numberOfRowsInTableView:(NSTableView *)tableView;
- (id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(int)row;
// optional
- (void)tableView:(NSTableView *)tableView setObjectValue:(id)object forTableColumn:(NSTableColumn *)tableColumn row:(int)row;

// optional - drag and drop support
- (BOOL)tableView:(NSTableView *)tv writeRows:(NSArray*)rows toPasteboard:(NSPasteboard*)pboard;
    // This method is called after it has been determined that a drag should begin, but before the drag has been started.  To refuse the drag, return NO.  To start a drag, return YES and place the drag data onto the pasteboard (data, owner, etc...).  The drag image and other drag related information will be set up and provided by the table view once this call returns with YES.  The rows array is the list of row numbers that will be participating in the drag.

- (NSDragOperation)tableView:(NSTableView*)tv validateDrop:(id <NSDraggingInfo>)info proposedRow:(int)row proposedDropOperation:(NSTableViewDropOperation)op;
    // This method is used by NSTableView to determine a valid drop target.  Based on the mouse position, the table view will suggest a proposed drop location.  This method must return a value that indicates which dragging operation the data source will perform.  The data source may "re-target" a drop if desired by calling setDropRow:dropOperation: and returning something other than NSDragOperationNone.  One may choose to re-target for various reasons (eg. for better visual feedback when inserting into a sorted position).

- (BOOL)tableView:(NSTableView*)tv acceptDrop:(id <NSDraggingInfo>)info row:(int)row dropOperation:(NSTableViewDropOperation)op;
    // This method is called when the mouse is released over an outline view that previously decided to allow a drop via the validateDrop method.  The data source should incorporate the data from the dragging pasteboard at this time.

@end

