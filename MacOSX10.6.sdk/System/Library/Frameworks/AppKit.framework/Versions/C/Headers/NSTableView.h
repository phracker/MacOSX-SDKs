/*
    NSTableView.h
    Application Kit
    Copyright (c) 1995-2009, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSDragging.h>
#import <AppKit/NSUserInterfaceValidation.h>
#import <AppKit/NSTextView.h>

@class NSTableHeaderView;
@class NSTableColumn;
@class NSMutableArray;
@class NSIndexSet, NSMutableIndexSet;
@protocol NSTableViewDelegate, NSTableViewDataSource;

typedef struct __TvFlags {
#ifdef __BIG_ENDIAN__
    unsigned int        allowsColumnReordering:1;
    unsigned int        allowsColumnResizing:1;
    unsigned int        oldDrawsGridFlag:1;
    unsigned int        allowsEmptySelection:1;
    unsigned int        allowsMultipleSelection:1;
    unsigned int        allowsColumnSelection:1;
    unsigned int        selectionType:2;
    unsigned int        changingLayout:1; // Unused
    unsigned int        compareWidthWithSuperview:2;
    unsigned int        delegateWillDisplayCell:1;
    unsigned int        delegateShouldEditTableColumn:1;
    unsigned int        delegateShouldSelectRow:1;
    unsigned int        delegateShouldSelectTableColumn:1;
    unsigned int        delegateSelectionShouldChangeInTableView:1;
    unsigned int        oldAutoresizesAllColumnsToFit:1;
    unsigned int        dataSourceSetObjectValue:1;
    unsigned int        selectionPostingDisableCount:7;
    unsigned int        movedPostingDisableCount:6;
    unsigned int        refusesFirstResponder:1;
#else
    unsigned int        refusesFirstResponder:1;
    unsigned int        movedPostingDisableCount:6;
    unsigned int        selectionPostingDisableCount:7;
    unsigned int        dataSourceSetObjectValue:1;
    unsigned int        oldAutoresizesAllColumnsToFit:1;
    unsigned int        delegateSelectionShouldChangeInTableView:1;
    unsigned int        delegateShouldSelectTableColumn:1;
    unsigned int        delegateShouldSelectRow:1;
    unsigned int        delegateShouldEditTableColumn:1;
    unsigned int        delegateWillDisplayCell:1;
    unsigned int        compareWidthWithSuperview:2;
    unsigned int        changingLayout:1; // Unused
    unsigned int        selectionType:2;
    unsigned int        allowsColumnSelection:1;
    unsigned int        allowsMultipleSelection:1;
    unsigned int        allowsEmptySelection:1;
    unsigned int        oldDrawsGridFlag:1;
    unsigned int        allowsColumnResizing:1;
    unsigned int        allowsColumnReordering:1;
#endif
} _TvFlags;

/* In drag and drop, used to specify a dropOperation.  For example, given a table with N rows (numbered with row 0 at the top visually), a row of N-1 and operation of NSTableViewDropOn would specify a drop on the last row.  To specify a drop below the last row, one would use a row of N and NSTableViewDropAbove for the operation.
*/
enum { NSTableViewDropOn, NSTableViewDropAbove };
typedef NSUInteger NSTableViewDropOperation;


@interface NSTableView : NSControl <NSUserInterfaceValidations, NSTextViewDelegate>
{
    /* All instance variables are private */
    NSTableHeaderView        *_headerView;
    NSView                *_cornerView;
    NSMutableArray             *_tableColumns;
    NSCell                *_editingCell;
    id                        _delegate;
    id                        _dataSource;
    NSSize                _intercellSpacing;
    CGFloat                _rowHeight;
    NSInteger                _lastSelectedColumn;
    NSInteger                _lastSelectedRow;
    NSInteger                _editingRow;
    NSInteger                _editingColumn;
    NSMutableIndexSet        *_selectedColumns;
    NSMutableIndexSet        *_selectedRows;
    NSImage                *_bodyDragImage;
    NSColor                *_backgroundColor;
    NSColor                *_gridColor;
    CGFloat                _dragYPos;
    id                        _target;
    SEL                 _action;
    SEL                 _doubleAction;
    NSRect                _rectOfLastColumn;
    NSInteger                _lastCachedRectColumn;
    NSRect                _rectOfLastRow;
    NSInteger                _lastCachedRectRow;
    _TvFlags            _tvFlags;
    id                  _reserved;
}

/* Get and set the dataSource. The dataSource can implement methods in the category NSObject(NSTableViewDataSource). Some methods are required, unless bindings are used, in which case they are optional. The dataSource is a weak reference (non retained) in non garbage collected applications. Under garbage collected apps, it is a strong reference. The default value is 'nil'.
 */
- (void)setDataSource:(id <NSTableViewDataSource>)aSource;
- (id <NSTableViewDataSource>)dataSource;

/* Get and set the delegate. The delegate can implement methods in the category NSObject(NSTableViewDelegate). All delegate methods are optional. The delegate is a weak reference (non retained) in non garbage collected applications. Under garbage collected apps, it is a strong reference. The default value is 'nil'.
 */
- (void)setDelegate:(id <NSTableViewDelegate>)delegate;
- (id <NSTableViewDelegate>)delegate;

/* Get and set the headerView. Calling -setHeaderView:nil will remove the headerView. Calling -setHeaderView: may have the side effect of tiling the enclosingScrollView to accommodate the size change. The default value is a new NSTableHeaderView instance.
 */
- (void)setHeaderView:(NSTableHeaderView *)headerView;
- (NSTableHeaderView *)headerView;

/* Get and set the cornerView. The cornerView is the view that appears directly to the right of the headerView above the vertical NSScroller. The scroller must be present for the cornerView to be shown. Calling -setCornerView: may have the side effect of tiling the enclosingScrollView to accomodate the size change. The default value is an internal class that properly fills in the corner.
 */
- (void)setCornerView:(NSView *)cornerView;
- (NSView *)cornerView;

/* Get and set the allowsColumnReordering. Controls whether or not columns can be drag-reordered. The default value is YES.
 */
- (void)setAllowsColumnReordering:(BOOL)flag;
- (BOOL)allowsColumnReordering;

/* Get and set the allowsColumnResizing. Controls whether the user can attempt to resize columns by dragging between headers. If flag is YES the user can resize columns; if flag is NO the user can't. Columns can only be resized if a column allows user resizing. See -[NSTableColumn setResizingMask:] for more details. You can always change columns programmatically regardless of this setting. The default value is YES. 
 */
- (void)setAllowsColumnResizing:(BOOL)flag;
- (BOOL)allowsColumnResizing;

enum {
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
};
typedef NSUInteger NSTableViewColumnAutoresizingStyle;

/* Get and set the columnAutoresizingStyle. This controls resizing in response to a tableView frame size change, usually done by dragging a window larger that has an auto-resized tableView inside it. The default value is NSTableViewLastColumnOnlyAutoresizingStyle.
   Compatability Note: This method replaces -setAutoresizesAllColumnsToFit: on 10.4 and higher.
 */
- (void)setColumnAutoresizingStyle:(NSTableViewColumnAutoresizingStyle)style AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (NSTableViewColumnAutoresizingStyle)columnAutoresizingStyle AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Grid styles for the gridStyleMask.
 */
enum {
    NSTableViewGridNone                    = 0,
    NSTableViewSolidVerticalGridLineMask   = 1 << 0,
    NSTableViewSolidHorizontalGridLineMask = 1 << 1
};

/* Get and set the gridStyleMask. Values can be bitwise or'ed together. The default value is NSTableViewGridNone.
 */
- (void)setGridStyleMask:(NSUInteger)gridType AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
- (NSUInteger)gridStyleMask AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Get and set the intercellSpacing. This is the spacing that appears between cells. The default value is NSMakeSize(3, 2).
 */
- (void)setIntercellSpacing:(NSSize)aSize;
- (NSSize)intercellSpacing;

/* Get and set the use of alternatingRowBackgroundColors. This configures the table to use either the standard alternating row colors, or a solid color for its background. The default value is NO.
 */
- (void)setUsesAlternatingRowBackgroundColors:(BOOL)useAlternatingRowColors AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
- (BOOL)usesAlternatingRowBackgroundColors AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Get and set the backgroundColor. On Mac OS 10.5 and higher, the alpha portion of 'color' is properly used when drawing the backgroundColor. To have a transparent tableView, set the backgroundColor to [NSColor clearColor], and set the enclosing NSScrollView to not draw its background with: [[tableView enclosingScrollView] setDrawsBackground:NO]. NSTableView uses NSCompositeSourceOver when drawing the background color. The default value is [NSColor controlBackgroundColor]. 
 */
- (void)setBackgroundColor:(NSColor *)color;
- (NSColor *)backgroundColor;

/* Get and set the gridColor. This value is only used when the gridStyleMask is not equal to NSTableViewGridNone. The default value is [NSColor gridColor].
 */
- (void)setGridColor:(NSColor *)color;
- (NSColor *)gridColor;

/* Get and set the rowHeight. The value must be greater than 0. Calling -setRowHeight: with a non-pixel aligning (fractional) value will be forced to a pixel alinging (integral) value. For variable row height tableViews (ones that have the delegate implement -tableView:heightOfRow:), -rowHeight will be used to draw alternating rows past the last row in the tableView. The default value is 17.0 for applications linked on 10.5 and higher (the height acceptable for [NSFont systemFontSize]). The default value is 16.0 for 10.4 and lower.
 */
- (void)setRowHeight:(CGFloat)rowHeight;
- (CGFloat)rowHeight;

/* If the delegate implements -tableView:heightOfRow:, this method immediately re-tiles the table view using row heights it provides.
*/
- (void)noteHeightOfRowsWithIndexesChanged:(NSIndexSet *)indexSet AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Returns a reference to the array of NSTableColumn instances in the NSTableView. Includes columns that are -isHidden. It is recommended to make a copy of the array if you are going to manipulate the NSTableView by using -addTableColumn:, -removeTableColumn: or -moveColumn:toColumn:.
 */
- (NSArray *)tableColumns;

/* Simply a cover method to return the number of NSTableColumn instances in the NSTableView. Includes columns that are -isHidden.
 */
- (NSInteger)numberOfColumns;

/* Returns the numberOfRows. It may call to the dataSource to aquire the count. numberOfRows will return 0 if there are no visible columns.
 */
- (NSInteger)numberOfRows;

/* Adds 'tableColumn' to the end of the -tableColumns array and retiles the tableView. 'tableColumn' must be non-nil, otherwise an exception will be raised.
 */
- (void)addTableColumn:(NSTableColumn *)tableColumn;

/* Removes 'tableColumn' from the -tableColumns array and retiles the tableView.
 */
- (void)removeTableColumn:(NSTableColumn *)tableColumn;

/* Moves the the tableColumn at 'oldIndex' to 'newIndex'. 'oldIndex' and 'newIndex' must be in the range: 0 to [tableView numberOfColumns]-1, otherwise an exception will be raised.
 */
- (void)moveColumn:(NSInteger)oldIndex toColumn:(NSInteger)newIndex;

/* Returns the first index of the NSTableColumn instance with the -identifier that isEqual to 'identifier'. Returns -1 if 'identifier' can not be found.
 */
- (NSInteger)columnWithIdentifier:(id)identifier;

/* Returns the first NSTableColumn instance with the -identifier that isEqual to 'identifier'. Returns nil if 'identifier' can not be found.
 */
- (NSTableColumn *)tableColumnWithIdentifier:(id)identifier;

- (void)tile;
- (void)sizeToFit;
- (void)sizeLastColumnToFit;

- (void)scrollRowToVisible:(NSInteger)row;
- (void)scrollColumnToVisible:(NSInteger)column;

- (void)reloadData;
- (void)noteNumberOfRowsChanged;

/* Updates a particular row of cells for a given set of 'rowIndexes' in 'columnIndexes'. For cells that are visible, appropriate dataSource and delegate methods will be called and the cells will be redrawn. For tables that support variable row heights, the row height will not be re-queried from the delegate; -noteHeightOfRowsWithIndexesChanged: should be used if a row height change is required..
 */
- (void)reloadDataForRowIndexes:(NSIndexSet *)rowIndexes columnIndexes:(NSIndexSet *)columnIndexes AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

- (NSInteger)editedColumn;
- (NSInteger)editedRow;

- (NSInteger)clickedColumn;
- (NSInteger)clickedRow;

- (void)setDoubleAction:(SEL)aSelector;
- (SEL)doubleAction;

/* Sorting Support
    The array of sort descriptors is archived.  Sort descriptors will persist along with other column information if an -autosaveName is set. Calling -setSortDescriptors: may have the side effect of calling -tableView:sortDescriptorsDidChange: on the -dataSource/
*/
- (void)setSortDescriptors:(NSArray *)array AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
- (NSArray *)sortDescriptors AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Support for little "indicator" images in table header cells.
*/
- (void)setIndicatorImage:(NSImage *)anImage inTableColumn:(NSTableColumn *)tableColumn;
- (NSImage *)indicatorImageInTableColumn:(NSTableColumn *)tableColumn;

/* Support for highlightable column header, for use with row selection.
*/
- (void)setHighlightedTableColumn:(NSTableColumn *)tableColumn;
- (NSTableColumn *)highlightedTableColumn;

/*
   Drag and Drop
*/

/* Get and set verticalMotionCanBeginDrag. If -verticalMotionCanBeginDrag is YES, then click + a vertical drag of the mouse will drag the clicked item(s). If NO, it will do a "drag select". The default value is YES.
 */
- (void)setVerticalMotionCanBeginDrag:(BOOL)flag;
- (BOOL)verticalMotionCanBeginDrag;

/* The return value indicates whether the receiver can attempt to initiate a row drag at 'mouseDownPoint'. Return NO to disallow initiating drags at the given location. 
    
    For applications linked on and after Leopard, NSCell hit testing will determine if a row can be dragged or not. Custom cells should properly implement [NSCell(NSCellHitTest) hitTestForEvent:inRect:ofView]; see NSCell.h for more information. NSTableView will not begin a drag if cell returns NSCellHitTrackableArea.
*/
- (BOOL)canDragRowsWithIndexes:(NSIndexSet *)rowIndexes atPoint:(NSPoint)mouseDownPoint AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* This method computes and returns an image to use for dragging.  Override this to return a custom image.  'dragRows' represents the rows participating in the drag.  'tableColumns' represent the columns that should be in the output image.  Note that drawing may be clipped to the visible rows, and columns.  'dragEvent' is a reference to the mouse down event that began the drag.  'dragImageOffset' is an in/out parameter.  This method will be called with dragImageOffset set to NSZeroPoint, but it can be modified to re-position the returned image.  A dragImageOffset of NSZeroPoint will cause the image to be centered under the mouse.

   Compatability Note: This method replaces dragImageForRows:event:dragImageOffset:.  If present, this is used instead of the deprecated method.
*/
- (NSImage *)dragImageForRowsWithIndexes:(NSIndexSet *)dragRows tableColumns:(NSArray *)tableColumns event:(NSEvent*)dragEvent offset:(NSPointPointer)dragImageOffset AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Configures the default value returned from -draggingSourceOperationMaskForLocal:.  An isLocal value of YES indicates that 'mask' applies when the destination object is in the same application.  A isLocal value of NO indicates that 'mask' applies when the destination object in an application outside the receiver's application.  NSTableView will archive the values you set for each isLocal setting.
*/
- (void)setDraggingSourceOperationMask:(NSDragOperation)mask forLocal:(BOOL)isLocal AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* To be used from validateDrop: if you wish to "re-target" the proposed drop. To specify a drop on the second row, one would specify row=2, and dropOperation=NSTableViewDropOn. To specify a drop below the last row, one would specify row=[tableView numberOfRows], and dropOperation=NSTableViewDropAbove. To specify a drop on the entire tableview, one would specify row=-1 and dropOperation=NSTableViewDropOn.
*/
- (void)setDropRow:(NSInteger)row dropOperation:(NSTableViewDropOperation)dropOperation;

/*
 * Selection
 */

/* Get and set allowsMultipleSelection. If -allowsMultipleSelection is YES, multiple items can be selected in various ways (modifier-clicking items, shift-arrow selection extending, etc). The default value is NO.
 */
- (void)setAllowsMultipleSelection:(BOOL)flag;
- (BOOL)allowsMultipleSelection;

/* Get and set allowsEmptySelection. If -allowsEmptySelection is YES, all rows can be deselected by the user. Otherwise, it is enforced that one row must be left selected at any given time. The default value is YES.
 */
- (void)setAllowsEmptySelection:(BOOL)flag;
- (BOOL)allowsEmptySelection;

/* Get and set allowsColumnSelection. If -allowsColumnSelection is YES, clicking on column headers can select that column (which is reflected in -selectedColumnIndexes). The default value is NO.
 */
- (void)setAllowsColumnSelection:(BOOL)flag;
- (BOOL)allowsColumnSelection;

- (void)selectAll:(id)sender;

- (void)deselectAll:(id)sender;

/* Sets the column selection using the indexes.  Selection is set/extended based on the extend flag. 
   Compatability Note: This method replaces selectColumn:byExtendingSelection:
       If a subclasser implements only the deprecated single-index method (selectColumn:byExtendingSelection:), the single-index method will be invoked for each index.  If a subclasser implements the multi-index method (selectColumnIndexes:byExtendingSelection:), the deprecated single-index version method will not be used.  This allows subclassers already overriding the single-index method to still receive a selection message.  Note: to avoid cycles, subclassers of this method and single-index method should not call each other.
*/
- (void)selectColumnIndexes:(NSIndexSet *)indexes byExtendingSelection:(BOOL)extend AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Sets the row selection using 'indexes'. Selection is set/extended based on the extend flag. On 10.5 and greater, selectRowIndexes:byExtendingSelection: will allow you to progrmatically select more than one index, regardless of the allowsMultipleSelection and allowsEmptySelection options set on the table.
 
   Compatability Note: This method replaces selectRow:byExtendingSelection:
       If a subclasser implements only the deprecated single-index method (selectRow:byExtendingSelection:), the single-index method will be invoked for each index.  If a subclasser implements the multi-index method (selectRowIndexes:byExtendingSelection:), the deprecated single-index version method will not be used.  This allows subclassers already overriding the single-index method to still receive a selection message.  Note: to avoid cycles, subclassers of this method and single-index method should not call each other.
*/
- (void)selectRowIndexes:(NSIndexSet *)indexes byExtendingSelection:(BOOL)extend AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

- (NSIndexSet *)selectedColumnIndexes AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
- (NSIndexSet *)selectedRowIndexes AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

- (void)deselectColumn:(NSInteger)column;
- (void)deselectRow:(NSInteger)row;
- (NSInteger)selectedColumn;
- (NSInteger)selectedRow;
- (BOOL)isColumnSelected:(NSInteger)column;
- (BOOL)isRowSelected:(NSInteger)row;
- (NSInteger)numberOfSelectedColumns;
- (NSInteger)numberOfSelectedRows;

/* Allow type selection in this tableView. The default value is YES.
*/

- (BOOL)allowsTypeSelect AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)setAllowsTypeSelect:(BOOL)value AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

enum {
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
    
/* The highlight style to show no highlight at all. 
 */
    NSTableViewSelectionHighlightStyleNone = -1,
    
#endif
    
/* The regular highlight style of NSTableView. On 10.5, a light blue ([NSColor alternateSelectedControlColor]) or light gray color ([NSColor secondarySelectedControlColor]) is used to highlight selected rows. 
 */
    NSTableViewSelectionHighlightStyleRegular = 0,
    
/* The source list style of NSTableView. On 10.5, a light blue gradient is used to highlight selected rows. Note: Cells that have a drawsBackground property should have it set to NO. Otherwise, they will draw over the highlighting that NSTableView does. Setting this style will have the side effect of setting the background color to the "source list" background color. Additionally in NSOutlineView, the following properties are changed to get the standard "source list" look: indentationPerLevel, rowHeight and intercellSpacing. After calling setSelectionHighlightStyle: one can change any of the other properties as required.
 */
    NSTableViewSelectionHighlightStyleSourceList = 1,
};
typedef NSInteger NSTableViewSelectionHighlightStyle;

/* Gets and sets the current selection highlight style. The default value is NSTableViewSelectionHighlightStyleRegular. 
 */
- (NSTableViewSelectionHighlightStyle)selectionHighlightStyle AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)setSelectionHighlightStyle:(NSTableViewSelectionHighlightStyle)selectionHighlightStyle AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6

enum {
/* Provides no feedback when the user drags over the table view. This option exists to allow subclasses to implement their dragging destination highlighting, or to make it not show anything all.
 */
    NSTableViewDraggingDestinationFeedbackStyleNone = -1,
    
/* Draws a solid round-rect background on drop target rows, and an insertion marker between rows. This style should be used in most cases.
 */
    NSTableViewDraggingDestinationFeedbackStyleRegular = 0,

/* Draws an outline on drop target rows, and an insertion marker between rows. This style will automatically be set for source lists when [table setSelectionHighlightStyle:NSTableViewSelectionHighlightStyleSourceList] is called, as it is the standard look for Source Lists, but may be used in other areas as needed.
 */
    NSTableViewDraggingDestinationFeedbackStyleSourceList = 1,
};

#endif

typedef NSInteger NSTableViewDraggingDestinationFeedbackStyle;

/* Gets and sets the dragging destination feedback style. The default value is NSTableViewDraggingDestinationFeedbackStyleRegular for all tables. However, changing the -selectionHighlightStyle to NSTableViewSelectionHighlightStyleSourceList will automatically change the -draggingDestinationFeedbackStyle to NSTableViewDraggingDestinationFeedbackStyleSourceList.
 */
- (void)setDraggingDestinationFeedbackStyle:(NSTableViewDraggingDestinationFeedbackStyle)style AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (NSTableViewDraggingDestinationFeedbackStyle)draggingDestinationFeedbackStyle AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Returns the rectangle for 'column'. Returns NSZeroRect if the NSTableColumn at 'column' has -isHidden == YES, or if 'column' is less than 0, or if 'column' is greater than or equal to the number of columns in the NSTableView.
 */
- (NSRect)rectOfColumn:(NSInteger)column;

/* Returns the rectange for 'row'. If 'row' is < 0 or >= [self numberOfRows], then NSZeroRect is returned.
 */
- (NSRect)rectOfRow:(NSInteger)row;

/* Returns the indexes for columns in 'rect'. NSTableColumns which have -isHidden == YES are not returned. If 'rect' is empty, no indexes will be returned. Introduced in Mac OS 10.5. 
 */
- (NSIndexSet *)columnIndexesInRect:(NSRect)rect AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Returns the range of rows in 'rect'. If 'rect' is empty, or if there are no rows, an empty range will be returned. If 'rect' is outside of -[NSTableView bounds], 'rect' will be intersected to only look in the bounds.
 */
- (NSRange)rowsInRect:(NSRect)rect;

/* Returns the column index at 'point', or -1 if 'point' is outside of all table columns.
 */
- (NSInteger)columnAtPoint:(NSPoint)point;

- (NSInteger)rowAtPoint:(NSPoint)point;

/* Returns the frame of the cell at 'row' / 'column'. If the 'row' is a "full width" row, the frame returned will be equal to the width of the row. If the NSTableColumn at 'column' has -isHidden == YES, or if the values are outside acceptable ranges, NSZeroRect is returned.
 */
- (NSRect)frameOfCellAtColumn:(NSInteger)column row:(NSInteger)row;

/* Returns the fully prepared cell that the view will normally use for drawing or any processing. The value for the cell will be correctly set, and the delegate method 'willDisplayCell:' will have be called. You can override this method to do any additional setting up of the cell that is required, or call it to retrieve a cell that will have its contents properly set for the particular column and row.
*/
- (NSCell *)preparedCellAtColumn:(NSInteger)column row:(NSInteger)row AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

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

/* On Mac OS 10.4 and higher, the NSTableColumn width and location is saved. On Mac OS 10.5 and higher, the NSTableColumn 'isHidden' state is also saved. The 'autosaveName' must be set for 'autosaveTableColumns' to take effect.
*/
- (void)setAutosaveTableColumns:(BOOL)save;
- (BOOL)autosaveTableColumns;

/* On Mac OS 10.5 and higher, NSTableView supports sub-cell focusing. The following set of methods control the focusing.
 */

/* Returns YES if the fully prepared 'cell' at 'row'/'column' can be made the focused cell or not. By default, only cells that are enabled can be focused. In addition, if the cell is an NSTextFieldCell, it will can only be focused if it is selectable or editable, and the delegate responds YES to -table:shouldEditTableColumn:row:. Subclasses can override this to further control what cells can and cannot be made focused.
 */
- (BOOL)shouldFocusCell:(NSCell *)cell atColumn:(NSInteger)column row:(NSInteger)row AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Returns the focused column that the user has tabbed to, or -1 if there is no focused column. The focus interaction will always be on [tableView selectedRow]. If the selectedRow is a "full width" cell, then focusedColumn will return "1" if focused.
 */
- (NSInteger)focusedColumn AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Sets the focused column, redisplays the old 'focusedColumn', and redisplays the new 'focusedColumn' (if required). The focused column has a focus ring drawn around the [tableView selectedRow] that intersects with 'focusedColumn'. A value of -1 indicates there is no focused column. You should not override this method.
 */
- (void)setFocusedColumn:(NSInteger)focusedColumn AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Acquires the preparedCell located at 'column'/'row', copies it, invokes performClick: or performClickWithFrame:inView: (for NSPopUpButtonCell), and then updates the datasource - if required. This method does not do any checks to see if the cell is enabled.
 */
- (void)performClickOnCellAtColumn:(NSInteger)column row:(NSInteger)row AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/*
 * For subclassers
 */
- (void)editColumn:(NSInteger)column row:(NSInteger)row withEvent:(NSEvent *)theEvent select:(BOOL)select;
- (void)drawRow:(NSInteger)row clipRect:(NSRect)clipRect;
- (void)highlightSelectionInClipRect:(NSRect)clipRect;
- (void)drawGridInClipRect:(NSRect)clipRect;
- (void)drawBackgroundInClipRect:(NSRect)clipRect AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

@end

@protocol NSTableViewDelegate <NSControlTextEditingDelegate>
@optional

/* Allows the delegate to provide further setup for 'cell' in 'tableColumn'/'row'. It is not safe to do drawing inside this method, and you should only setup state for 'cell'.
 */ 
- (void)tableView:(NSTableView *)tableView willDisplayCell:(id)cell forTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row;
- (BOOL)tableView:(NSTableView *)tableView shouldEditTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row;
- (BOOL)selectionShouldChangeInTableView:(NSTableView *)tableView;

/* Optional - Return YES if 'row' should be selected and NO if it should not. For better performance and better control over the selection, you should use tableView:selectionIndexesForProposedSelection:. 
*/
- (BOOL)tableView:(NSTableView *)tableView shouldSelectRow:(NSInteger)row;

/* Optional - Return a set of new indexes to select when the user changes the selection with the keyboard or mouse. If implemented, this method will be called instead of tableView:shouldSelectRow:. This method may be called multiple times with one new index added to the existing selection to find out if a particular index can be selected when the user is extending the selection with the keyboard or mouse. Note that 'proposedSelectionIndexes' will contain the entire newly suggested selection, and you can return the exsiting selection to avoid changing the selection.
*/
- (NSIndexSet *)tableView:(NSTableView *)tableView selectionIndexesForProposedSelection:(NSIndexSet *)proposedSelectionIndexes AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (BOOL)tableView:(NSTableView *)tableView shouldSelectTableColumn:(NSTableColumn *)tableColumn;

- (void)tableView:(NSTableView *)tableView mouseDownInHeaderOfTableColumn:(NSTableColumn *)tableColumn;
- (void)tableView:(NSTableView *)tableView didClickTableColumn:(NSTableColumn *)tableColumn;
- (void)tableView:(NSTableView *)tableView didDragTableColumn:(NSTableColumn *)tableColumn;

/* Optional - Tool Tip Support
    When the user pauses over a cell, the value returned from this method will be displayed in a tooltip.  'point' represents the current mouse location in view coordinates.  If you don't want a tooltip at that location, return nil or the empty string.  On entry, 'rect' represents the proposed active area of the tooltip.  By default, rect is computed as [cell drawingRectForBounds:cellFrame].  To control the default active area, you can modify the 'rect' parameter.
*/
- (NSString *)tableView:(NSTableView *)tableView toolTipForCell:(NSCell *)cell rect:(NSRectPointer)rect tableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row mouseLocation:(NSPoint)mouseLocation AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Optional - Variable Row Heights
    Implement this method to support a table with varying row heights. The height returned by this method should not include intercell spacing and must be greater than zero. Performance Considerations: For large tables in particular, you should make sure that this method is efficient. NSTableView may cache the values this method returns, but this should NOT be depended on, as all values may not be cached. To signal a row height change, call -noteHeightOfRowsWithIndexesChanged:. For a given row, the same row height should always be returned until -noteHeightOfRowsWithIndexesChanged: is called, otherwise unpredicable results will happen. NSTableView automatically invalidates its entire row height cache in -reloadData, and -noteNumberOfRowsChanged.
*/
- (CGFloat)tableView:(NSTableView *)tableView heightOfRow:(NSInteger)row AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Optional - Type select support
    Implement this method if you want to control the string that is used for type selection. You may want to change what is searched for based on what is displayed, or simply return nil for that 'tableColumn' or 'row' to not be searched. By default, all cells with text in them are searched. The default value when this delegate method is not implemented is [[tableView preparedCellForColumn:tableColumn row:row] stringValue], and this value can be returned from the delegate method if desired.
*/
- (NSString *)tableView:(NSTableView *)tableView typeSelectStringForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Optional - Type select support
    Implement this method if you want to control how type selection works. Return the first row that matches searchString from within the range of startRow to endRow. It is possible for endRow to be less than startRow if the search will wrap. Return -1 when there is no match. Include startRow as a possible match, but do not include endRow. It is not necessary to implement this method in order to support type select.
*/
- (NSInteger)tableView:(NSTableView *)tableView nextTypeSelectMatchFromRow:(NSInteger)startRow toRow:(NSInteger)endRow forString:(NSString *)searchString AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Optional - Type select support
    Implement this method if you would like to prevent a type select from happening based on the current event and current search string. Generally, this will be called from keyDown: and the event will be a key event. The search string will be nil if no type select has began. 
*/
- (BOOL)tableView:(NSTableView *)tableView shouldTypeSelectForEvent:(NSEvent *)event withCurrentSearchString:(NSString *)searchString AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Optional - Expansion ToolTip support
    Implement this method and return NO to prevent an expansion tooltip from appearing for a particular cell in a given row and tableColumn. See NSCell.h for more information on expansion tool tips. 
*/
- (BOOL)tableView:(NSTableView *)tableView shouldShowCellExpansionForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*  Optional - Custom tracking support
    It is possible to control the ability to track a cell or not. Normally, only selectable or selected cells can be tracked. If you implement this method, cells which are not selectable or selected can be tracked, and vice-versa. For instance, this allows you to have an NSButtonCell in a table which does not change the selection, but can still be clicked on and tracked.
*/
- (BOOL)tableView:(NSTableView *)tableView shouldTrackCell:(NSCell *)cell forTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*  Optional - Different cells for each row
    A different data cell can be returned for any particular tableColumn and row, or a cell that will be used for the entire row (a full width cell). The returned cell should properly implement copyWithZone:, since the cell may be copied by NSTableView. If the tableColumn is non-nil, you should return a cell, and generally you will want to default to returning the result from [tableColumn dataCellForRow:row].

    When each row is being drawn, this method will first be called with a nil tableColumn. At this time, you can return a cell that will be used to draw the entire row, acting like a group. If you do return a cell for the 'nil' tableColumn, be prepared to have the other corresponding datasource and delegate methods to be called with a 'nil' tableColumn value. If don't return a cell, the method will be called once for each tableColumn in the tableView, as usual.
*/
- (NSCell *)tableView:(NSTableView *)tableView dataCellForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Optional - Group rows. 
    Implement this method and return YES to indicate a particular row should have the "group row" style drawn for that row. If the cell in that row is an NSTextFieldCell and contains only a stringValue, the "group row" style attributes will automatically be applied for that cell. Group rows are drawn differently depending on the selectionHighlightStyle. For NSTableViewSelectionHighlightStyleRegular, there is a blue gradient background. For NSTableViewSelectionHighlightStyleSourceList, the text is light blue, and there is no background.
*/
- (BOOL)tableView:(NSTableView *)tableView isGroupRow:(NSInteger)row AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Optional - Autosizing table columns
 Implement this method if you want to control how wide a column is made when the user double clicks on the resize divider. By default, NSTableView iterates every row in the table, accesses a cell via preparedCellAtRow:column:, and requests the "cellSize" to find the appropriate largest width to use. For large row counts, a monte carlo simulation is done instead of interating every row. For performance and accurate results, it is recommended that this method is implemented when using large tables.
 */

- (CGFloat)tableView:(NSTableView *)tableView sizeToFitWidthOfColumn:(NSInteger)column AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/*  Optional - Control of column reordering.
 Specifies if the column can be reordered to a new location, or not. 'columnIndex' is the column that is being dragged. The actual NSTableColumn instance can be retrieved from the [tableView tableColumns] array. 'newColumnIndex' is the new proposed target location for 'columnIndex'. When a column is initially dragged by the user, the delegate is first called with a 'newColumnIndex' of -1. Returning NO will disallow that column from being reordered at all. Returning YES allows it to be reordered, and the delegate will be called again when the column reaches a new location. If this method is not implemented, all columns are considered reorderable. 
 */
- (BOOL)tableView:(NSTableView *)tableView shouldReorderColumn:(NSInteger)columnIndex toColumn:(NSInteger)newColumnIndex AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/*  Notifications
 */
- (void)tableViewSelectionDidChange:(NSNotification *)notification;
- (void)tableViewColumnDidMove:(NSNotification *)notification;
- (void)tableViewColumnDidResize:(NSNotification *)notification;
- (void)tableViewSelectionIsChanging:(NSNotification *)notification;

@end

/*
 * Notifications
 */
APPKIT_EXTERN NSString *NSTableViewSelectionDidChangeNotification;
APPKIT_EXTERN NSString *NSTableViewColumnDidMoveNotification;       // @"NSOldColumn", @"NSNewColumn"
APPKIT_EXTERN NSString *NSTableViewColumnDidResizeNotification;     // @"NSTableColumn", @"NSOldWidth"
APPKIT_EXTERN NSString *NSTableViewSelectionIsChangingNotification;

@protocol NSTableViewDataSource <NSObject>
@optional

/* Required Methods
*/
- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView;
- (id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row;

/* Optional - Editing Support
*/
- (void)tableView:(NSTableView *)tableView setObjectValue:(id)object forTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row;

/* Optional - sorting support
        This is the indication that sorting needs to be done.  Typically the data source will sort its data, reload, and adjust selections.
*/
- (void)tableView:(NSTableView *)tableView sortDescriptorsDidChange:(NSArray *)oldDescriptors AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Optional - Drag and Drop support
    This method is called after it has been determined that a drag should begin, but before the drag has been started.  To refuse the drag, return NO.  To start a drag, return YES and place the drag data onto the pasteboard (data, owner, etc...).  The drag image and other drag related information will be set up and provided by the table view once this call returns with YES.  'rowIndexes' contains the row indexes that will be participating in the drag.

   Compatability Note: This method replaces tableView:writeRows:toPasteboard:.  If present, this is used instead of the deprecated method.
*/
- (BOOL)tableView:(NSTableView *)tableView writeRowsWithIndexes:(NSIndexSet *)rowIndexes toPasteboard:(NSPasteboard *)pboard AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* This method is used by NSTableView to determine a valid drop target. Based on the mouse position, the table view will suggest a proposed drop 'row' and 'dropOperation'. This method must return a value that indicates which NSDragOperation the data source will perform. The data source may "re-target" a drop, if desired, by calling setDropRow:dropOperation: and returning something other than NSDragOperationNone. One may choose to re-target for various reasons (eg. for better visual feedback when inserting into a sorted position).
*/
- (NSDragOperation)tableView:(NSTableView *)tableView validateDrop:(id <NSDraggingInfo>)info proposedRow:(NSInteger)row proposedDropOperation:(NSTableViewDropOperation)dropOperation;

/* This method is called when the mouse is released over an outline view that previously decided to allow a drop via the validateDrop method.  The data source should incorporate the data from the dragging pasteboard at this time. 'row' and 'dropOperation' contain the values previously set in the validateDrop: method.
*/
- (BOOL)tableView:(NSTableView *)tableView acceptDrop:(id <NSDraggingInfo>)info row:(NSInteger)row dropOperation:(NSTableViewDropOperation)dropOperation;

/* NSTableView data source objects can support file promised drags via by adding  NSFilesPromisePboardType to the pasteboard in tableView:writeRowsWithIndexes:toPasteboard:.  NSTableView implements -namesOfPromisedFilesDroppedAtDestination: to return the results of this data source method.  This method should returns an array of filenames for the created files (filenames only, not full paths).  The URL represents the drop location.  For more information on file promise dragging, see documentation on the NSDraggingSource protocol and -namesOfPromisedFilesDroppedAtDestination:.
*/
- (NSArray *)tableView:(NSTableView *)tableView namesOfPromisedFilesDroppedAtDestination:(NSURL *)dropDestination forDraggedRowsWithIndexes:(NSIndexSet *)indexSet AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

@end

@interface NSObject(NSTableViewDataSourceDeprecated)

/*
 * Deprecated delegate methods
 */
 
/* Deprecated in Mac OS 10.4.  You should implement tableView:writeRowsWithIndexes:toPasteboard: instead.  See that method for more details.
*/
- (BOOL)tableView:(NSTableView *)tableView writeRows:(NSArray *)rows toPasteboard:(NSPasteboard *)pboard DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;

@end


/* Deprecated methods */

@interface NSTableView(NSDeprecated) 

/* Deprecated in Mac OS 10.3.  Calls setGridStyleMask:, setting grid style to either None, or vertical and horizonal solid grid lines as appropriate.
*/
- (void)setDrawsGrid:(BOOL)flag DEPRECATED_IN_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Deprecated in Mac OS 10.3.  Returns YES if gridStyleMask returns anything other than NSTableViewGridNone.
*/
- (BOOL)drawsGrid DEPRECATED_IN_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Deprecated in Mac OS 10.3.  You should use selectColumnIndexes:byExtendingSelection: instead.  See that method for more details.
*/
- (void)selectColumn:(NSInteger)column byExtendingSelection:(BOOL)extend DEPRECATED_IN_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Deprecated in Mac OS 10.3.  You should use selectRowIndexes:byExtendingSelection: instead.  See that method for more details.
*/
- (void)selectRow:(NSInteger)row byExtendingSelection:(BOOL)extend DEPRECATED_IN_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Deprecated in Mac OS 10.3.  You should use selectedColumnIndexes instead.
*/
- (NSEnumerator *)selectedColumnEnumerator DEPRECATED_IN_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Deprecated in Mac OS 10.3.  You should use selectedRowIndexes instead.
*/
- (NSEnumerator *)selectedRowEnumerator DEPRECATED_IN_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Deprecated in Mac OS 10.4.  You should use / override dragImageForRowsWithIndexes:tableColumns:event:dragImageOffset: instead.
*/ 
- (NSImage *)dragImageForRows:(NSArray*)dragRows event:(NSEvent *)dragEvent dragImageOffset:(NSPointPointer)dragImageOffset DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Deprecated in Mac OS 10.4.  You should use setColumnAutoresizingStyle: instead.  To preserve compatibility, if flag is YES, This method calls setColumnAutoresizingStyle:NSTableViewUniformColumnAutoresizingStyle.  If flag is NO, this method calls setColumnAutoresizingStyle:NSTableViewLastColumnOnlyAutoresizingStyle.
*/
- (void)setAutoresizesAllColumnsToFit:(BOOL)flag DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (BOOL)autoresizesAllColumnsToFit DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Deprecated in Mac OS 10.5. Since an NSTableColumn can have visible=NO, it is no longer possible to return a valid range of columns given a rect. Use columnIndexesInRect: 
*/
- (NSRange)columnsInRect:(NSRect)rect DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

@end
