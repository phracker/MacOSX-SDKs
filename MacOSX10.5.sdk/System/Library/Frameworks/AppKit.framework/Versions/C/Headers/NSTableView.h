/*
        NSTableView.h
        Application Kit
        Copyright (c) 1995-2007, Apple Inc.
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
    unsigned int	changingLayout:1; // Unused
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
    unsigned int	changingLayout:1; // Unused
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
enum { NSTableViewDropOn, NSTableViewDropAbove };
typedef NSUInteger NSTableViewDropOperation;


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
    CGFloat		_rowHeight;
    NSInteger		_lastSelectedColumn;
    NSInteger		_lastSelectedRow;
    NSInteger		_editingRow;
    NSInteger		_editingColumn;
    NSMutableIndexSet	*_selectedColumns;
    NSMutableIndexSet	*_selectedRows;
    NSImage		*_bodyDragImage;
    NSColor		*_backgroundColor;
    NSColor		*_gridColor;
    CGFloat		_dragYPos;
    id			_target;
    SEL                 _action;
    SEL                 _doubleAction;
    NSRect		_rectOfLastColumn;
    NSInteger		_lastCachedRectColumn;
    NSRect		_rectOfLastRow;
    NSInteger		_lastCachedRectRow;
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

/* Controls whether the user can attemp to resize columns by dragging between headers. If flag is YES the user can resize columns; if flag is NO the user can't. The default is YES. Columns can only be resized if a column allows user resizing.  See NSTableColumn setResizingMask: for more details.  You can always change columns programmatically regardless of this setting.
*/
- (void)setAllowsColumnResizing:(BOOL)flag;
- (BOOL)allowsColumnResizing;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* The column auto resizing style controls resizing in response to a table view frame change.
   Compatability Note: This method replaces -setAutoresizesAllColumnsToFit:.
*/
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

- (void)setGridStyleMask:(NSUInteger)gridType;
- (NSUInteger)gridStyleMask;
#endif

- (void)setIntercellSpacing:(NSSize)aSize;
- (NSSize)intercellSpacing;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
/* Configures the table to use either the standard alternating row colors, or a solid color for its background. 
*/
- (void)setUsesAlternatingRowBackgroundColors:(BOOL)useAlternatingRowColors;
- (BOOL)usesAlternatingRowBackgroundColors;
#endif

/* The backgroundColor defaults to [NSColor controlBackgroundColor]. On Mac OS 10.5 and higher, the alpha portion of 'color' is properly used when drawing the backgroundColor. To have a transparent tableView, set the backgroundColor to [NSColor clearColor], and set the enclosing NSScrollView to not draw its background with: [[tableView enclosingScrollView] setDrawsBackground:NO]. NSTableView uses NSCompositeSourceOver when drawing the background color.
*/
- (void)setBackgroundColor:(NSColor *)color;
- (NSColor *)backgroundColor;

- (void)setGridColor:(NSColor *)color;
- (NSColor *)gridColor;

- (void)setRowHeight:(CGFloat)rowHeight;
- (CGFloat)rowHeight;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* If the delegate implements -tableView:heightOfRow:, this method immediately re-tiles the table view using row heights it provides.
*/
- (void)noteHeightOfRowsWithIndexesChanged:(NSIndexSet *)indexSet;
#endif

- (NSArray *)tableColumns;
- (NSInteger)numberOfColumns;
- (NSInteger)numberOfRows;

- (void)addTableColumn:(NSTableColumn *)column;
- (void)removeTableColumn:(NSTableColumn *)column;
- (NSInteger)columnWithIdentifier:(id)identifier;
- (NSTableColumn *)tableColumnWithIdentifier:(id)identifier;

- (void)tile;
- (void)sizeToFit;
- (void)sizeLastColumnToFit;
- (void)scrollRowToVisible:(NSInteger)row;
- (void)scrollColumnToVisible:(NSInteger)column;
- (void)moveColumn:(NSInteger)column toColumn:(NSInteger)newIndex;

- (void)reloadData;
- (void)noteNumberOfRowsChanged;

- (NSInteger)editedColumn;
- (NSInteger)editedRow;
- (NSInteger)clickedColumn;
- (NSInteger)clickedRow;

- (void)setDoubleAction:(SEL)aSelector;
- (SEL)doubleAction;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

/* Sorting Support
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
   Drag and Drop
*/

- (void)setVerticalMotionCanBeginDrag:(BOOL)flag;
- (BOOL)verticalMotionCanBeginDrag;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* The return value indicates whether the receiver can attempt to initiate a row drag at 'mouseDownPoint'. Return NO to disallow initiating drags at the given location. 
    
    For applications linked on and after Leopard, NSCell hit testing will determine if a row can be dragged or not. Custom cells should properly implement [NSCell(NSCellHitTest) hitTestForEvent:inRect:ofView]; see NSCell.h for more information. NSTableView will not begin a drag if cell returns NSCellHitTrackableArea.
*/
- (BOOL)canDragRowsWithIndexes:(NSIndexSet *)rowIndexes atPoint:(NSPoint)mouseDownPoint;

/* This method computes and returns an image to use for dragging.  Override this to return a custom image.  'dragRows' represents the rows participating in the drag.  'tableColumns' represent the columns that should be in the output image.  Note that drawing may be clipped to the visible rows, and columns.  'dragEvent' is a reference to the mouse down event that began the drag.  'dragImageOffset' is an in/out parameter.  This method will be called with dragImageOffset set to NSZeroPoint, but it can be modified to re-position the returned image.  A dragImageOffset of NSZeroPoint will cause the image to be centered under the mouse.

   Compatability Note: This method replaces dragImageForRows:event:dragImageOffset:.  If present, this is used instead of the deprecated method.
*/
- (NSImage *)dragImageForRowsWithIndexes:(NSIndexSet *)dragRows tableColumns:(NSArray *)tableColumns event:(NSEvent*)dragEvent offset:(NSPointPointer)dragImageOffset;

/* Configures the default value returned from -draggingSourceOperationMaskForLocal:.  An isLocal value of YES indicates that 'mask' applies when the destination object is in the same application.  A isLocal value of NO indicates that 'mask' applies when the destination object in an application outside the receiver's application.  NSTableView will archive the values you set for each isLocal setting.
*/
- (void)setDraggingSourceOperationMask:(NSDragOperation)mask forLocal:(BOOL)isLocal;
#endif

/* To be used from validateDrop: if you wish to "re-target" the proposed drop. To specify a drop on the second row, one would specify row=2, and op=NSTableViewDropOn. To specify a drop below the last row, one would specify row=[tv numberOfRows], and op=NSTableViewDropAbove. To specify a drop on the entire tableview, one would specify row=-1 and op=NSTableViewDropOn.
*/
- (void)setDropRow:(NSInteger)row dropOperation:(NSTableViewDropOperation)op;


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

/* Sets the row selection using 'indexes'. Selection is set/extended based on the extend flag. On 10.5 and greater, selectRowIndexes:byExtendingSelection: will allow you to progrmatically select more than one index, regardless of the allowsMultipleSelection and allowsEmptySelection options set on the table.
 
   Compatability Note: This method replaces selectRow:byExtendingSelection:
       If a subclasser implements only the deprecated single-index method (selectRow:byExtendingSelection:), the single-index method will be invoked for each index.  If a subclasser implements the multi-index method (selectRowIndexes:byExtendingSelection:), the deprecated single-index version method will not be used.  This allows subclassers already overriding the single-index method to still receive a selection message.  Note: to avoid cycles, subclassers of this method and single-index method should not call each other.
*/
- (void)selectRowIndexes:(NSIndexSet *)indexes byExtendingSelection:(BOOL)extend;

- (NSIndexSet *)selectedColumnIndexes;
- (NSIndexSet *)selectedRowIndexes;
#endif

- (void)deselectColumn:(NSInteger)column;
- (void)deselectRow:(NSInteger)row;
- (NSInteger)selectedColumn;
- (NSInteger)selectedRow;
- (BOOL)isColumnSelected:(NSInteger)column;
- (BOOL)isRowSelected:(NSInteger)row;
- (NSInteger)numberOfSelectedColumns;
- (NSInteger)numberOfSelectedRows;


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

/* Allow type selection in this tableview. It is on by default.
*/

- (BOOL)allowsTypeSelect;
- (void)setAllowsTypeSelect:(BOOL)value;

enum {
/* The regular highlight style of NSTableView. On 10.5, a light blue ([NSColor alternateSelectedControlColor]) or light gray color ([NSColor secondarySelectedControlColor]) is used to highlight selected rows. 
*/
    NSTableViewSelectionHighlightStyleRegular = 0,
    
/* The source list style of NSTableView. On 10.5, a light blue gradient is used to highlight selected rows. Note: Cells that have a drawsBackground property should have it set to NO. Otherwise, they will draw over the highlighting that NSTableView does. Setting this style will have the side effect of setting the background color to the "source list" background color. Additionally in NSOutlineView, the following properties are changed to get the standard "source list" look: indentationPerLevel, rowHeight and intercellSpacing. After calling setSelectionHighlightStyle: one can change any of the other properties as required.
*/
    NSTableViewSelectionHighlightStyleSourceList = 1,
};
typedef NSInteger NSTableViewSelectionHighlightStyle;

/* Gets and sets the current selection highlight style. Defaults to NSTableViewSelectionHighlightStyleRegular. 
*/
- (NSTableViewSelectionHighlightStyle)selectionHighlightStyle;
- (void)setSelectionHighlightStyle:(NSTableViewSelectionHighlightStyle)selectionHighlightStyle;

#endif

/* Returns the rectangle for 'column'. Returns NSZeroRect if the NSTableColumn at 'column' has visible=NO, or if 'column' is less than 0, or if 'column' is greater than or equal to the number of columns in the NSTableView.
*/
- (NSRect)rectOfColumn:(NSInteger)column;

- (NSRect)rectOfRow:(NSInteger)row;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
/* Introduced in Mac OS 10.5. Returns the indexes for columns in 'rect'. NSTableColumns which have visible=NO are not returned. If 'rect' is empty, no indexes will be returned.
*/
- (NSIndexSet *)columnIndexesInRect:(NSRect)rect;
#endif

- (NSRange)rowsInRect:(NSRect)rect;

- (NSInteger)columnAtPoint:(NSPoint)point;

- (NSInteger)rowAtPoint:(NSPoint)point;

/* Returns the frame of the cell at 'row' / 'column'. If the 'row' is a "full width" row, the frame returned will be equal to the width of the row. If the NSTableColumn at 'column' has visible=NO, or if the values are outside acceptable ranges, NSZeroRect is returned.
*/
- (NSRect)frameOfCellAtColumn:(NSInteger)column row:(NSInteger)row;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

/* Returns the fully prepared cell that the view will normally use for drawing or any processing. The value for the cell will be correctly set, and the delegate method 'willDisplayCell:' will have be called. You can override this method to do any additional setting up of the cell that is required, or call it to retrieve a cell that will have its contents properly set for the particular column and row.
*/
- (NSCell *)preparedCellAtColumn:(NSInteger)column row:(NSInteger)row;

#endif

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

/*
 * For subclassers
 */
- (void)editColumn:(NSInteger)column row:(NSInteger)row withEvent:(NSEvent *)theEvent select:(BOOL)select;
- (void)drawRow:(NSInteger)row clipRect:(NSRect)clipRect;
- (void)highlightSelectionInClipRect:(NSRect)clipRect;
- (void)drawGridInClipRect:(NSRect)clipRect;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)drawBackgroundInClipRect:(NSRect)clipRect;
#endif

@end

@interface NSObject(NSTableViewDelegate)

- (void)tableView:(NSTableView *)tableView willDisplayCell:(id)cell forTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row;
- (BOOL)tableView:(NSTableView *)tableView shouldEditTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row;
- (BOOL)selectionShouldChangeInTableView:(NSTableView *)tableView;

/* Optional - Return YES if 'row' should be selected and 'NO' if it should not. For better performance and better control over the selection, you should use tableView:selectionIndexesForProposedSelection:. 
*/
- (BOOL)tableView:(NSTableView *)tableView shouldSelectRow:(NSInteger)row;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

/* Optional - Return a set of new indexes to select when the user changes the selection with the keyboard or mouse. If implemented, this method will be called instead of tableView:shouldSelectRow:. This method may be called multiple times with one new index added to the existing selection to find out if a particular index can be selected when the user is extending the selection with the keyboard or mouse. Note that 'proposedSelectionIndexes' will contain the entire newly suggested selection, and you can return the exsiting selection to avoid changing the selection.
*/
- (NSIndexSet *)tableView:(NSTableView *)tableView selectionIndexesForProposedSelection:(NSIndexSet *)proposedSelectionIndexes;

#endif

- (BOOL)tableView:(NSTableView *)tableView shouldSelectTableColumn:(NSTableColumn *)tableColumn;

- (void)tableView:(NSTableView *)tableView mouseDownInHeaderOfTableColumn:(NSTableColumn *)tableColumn;
- (void)tableView:(NSTableView *)tableView didClickTableColumn:(NSTableColumn *)tableColumn;
- (void)tableView:(NSTableView *)tableView didDragTableColumn:(NSTableColumn *)tableColumn;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* Optional - Tool Tip Support
    When the user pauses over a cell, the value returned from this method will be displayed in a tooltip.  'point' represents the current mouse location in view coordinates.  If you don't want a tooltip at that location, return nil or the empty string.  On entry, 'rect' represents the proposed active area of the tooltip.  By default, rect is computed as [cell drawingRectForBounds:cellFrame].  To control the default active area, you can modify the 'rect' parameter.
*/
- (NSString *)tableView:(NSTableView *)tableView toolTipForCell:(NSCell *)cell rect:(NSRectPointer)rect tableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row mouseLocation:(NSPoint)mouseLocation;

/* Optional - Variable Row Heights
    Implement this method to support a table with varying row heights.  The height returned by this method should not include intercell spacing and must be greater than zero.  Performance Considerations: For large tables in particular, you should make sure that this method is efficient.  NSTableView may cache the values this method returns.  So if you would like to change a row's height make sure to invalidate the row height by calling -noteHeightOfRowsWithIndexesChanged:.  NSTableView automatically invalidates its entire row height cache in -reloadData, and -noteNumberOfRowsChanged.
*/
- (CGFloat)tableView:(NSTableView *)tableView heightOfRow:(NSInteger)row;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

/* Optional - Type select support
    Implement this method if you want to control the string that is used for type selection. You may want to change what is searched for based on what is displayed, or simply return nil for that 'tableColumn' or 'row' to not be searched. By default, all cells with text in them are searched. The default value when this delegate method is not implemented is [[tableView preparedCellForColumn:tableColumn row:row] stringValue], and this value can be returned from the delegate method if desired.
*/
- (NSString *)tableView:(NSTableView *)tableView typeSelectStringForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row;

/* Optional - Type select support
    Implement this method if you want to control how type selection works. Return the first row that matches searchString from within the range of startRow to endRow. It is possible for endRow to be less than startRow if the search will wrap. Return -1 when there is no match. Include startRow as a possible match, but do not include endRow. It is not necessary to implement this method in order to support type select.
*/
- (NSInteger)tableView:(NSTableView *)tableView nextTypeSelectMatchFromRow:(NSInteger)startRow toRow:(NSInteger)endRow forString:(NSString *)searchString;

/* Optional - Type select support
    Implement this method if you would like to prevent a type select from happening based on the current event and current search string. Generally, this will be called from keyDown: and the event will be a key event. The search string will be nil if no type select has began. 
*/
- (BOOL)tableView:(NSTableView *)tableView shouldTypeSelectForEvent:(NSEvent *)event withCurrentSearchString:(NSString *)searchString;

/* Optional - Expansion ToolTip support
    Implement this method and return NO to prevent an expansion tooltip from appearing for a particular cell in a given row and tableColumn. See NSCell.h for more information on expansion tool tips. 
*/
- (BOOL)tableView:(NSTableView *)tableView shouldShowCellExpansionForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row;

/*  Optional - Custom tracking support
    It is possible to control the ability to track a cell or not. Normally, only selectable or selected cells can be tracked. If you implement this method, cells which are not selectable or selected can be tracked, and vice-versa. For instance, this allows you to have an NSButtonCell in a table which does not change the selection, but can still be clicked on and tracked.
*/
- (BOOL)tableView:(NSTableView *)tableView shouldTrackCell:(NSCell *)cell forTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row;

/*  Optional - Different cells for each row
    A different data cell can be returned for any particular tableColumn and row, or a cell that will be used for the entire row (a full width cell). The returned cell should properly implement copyWithZone:, since the cell may be copied by NSTableView. If the tableColumn is non-nil, you should return a cell, and generally you will want to default to returning the result from [tableColumn dataCellForRow:row].

    When each row is being drawn, this method will first be called with a nil tableColumn. At this time, you can return a cell that will be used to draw the entire row, acting like a group. If you do return a cell for the 'nil' tableColumn, be prepared to have the other corresponding datasource and delegate methods to be called with a 'nil' tableColumn value. If don't return a cell, the method will be called once for each tableColumn in the tableView, as usual.
*/
- (NSCell *)tableView:(NSTableView *)tableView dataCellForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row;

/* Optional - Group rows. 
    Implement this method and return YES to indicate a particular row should have the "group row" style drawn for that row. If the cell in that row is an NSTextFieldCell and contains only a stringValue, the "group row" style attributes will automatically be applied for that cell. Group rows are drawn differently depending on the selectionHighlightStyle. For NSTableViewSelectionHighlightStyleRegular, there is a blue gradient background. For NSTableViewSelectionHighlightStyleSourceList, the text is light blue, and there is no background.
*/
- (BOOL)tableView:(NSTableView *)tableView isGroupRow:(NSInteger)row;

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
/* Required Methods
*/
- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView;
- (id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row;

/* Optional - Editing Support
*/
- (void)tableView:(NSTableView *)tableView setObjectValue:(id)object forTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

/* Optional - sorting support
        This is the indication that sorting needs to be done.  Typically the data source will sort its data, reload, and adjust selections.
*/
- (void)tableView:(NSTableView *)tableView sortDescriptorsDidChange:(NSArray *)oldDescriptors;

#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* Optional - Drag and Drop support
    This method is called after it has been determined that a drag should begin, but before the drag has been started.  To refuse the drag, return NO.  To start a drag, return YES and place the drag data onto the pasteboard (data, owner, etc...).  The drag image and other drag related information will be set up and provided by the table view once this call returns with YES.  'rowIndexes' contains the row indexes that will be participating in the drag.

   Compatability Note: This method replaces tableView:writeRows:toPasteboard:.  If present, this is used instead of the deprecated method.
*/
- (BOOL)tableView:(NSTableView *)tableView writeRowsWithIndexes:(NSIndexSet *)rowIndexes toPasteboard:(NSPasteboard*)pboard;
#endif

/* This method is used by NSTableView to determine a valid drop target. Based on the mouse position, the table view will suggest a proposed drop 'row' and 'dropOperation'. This method must return a value that indicates which NSDragOperation the data source will perform. The data source may "re-target" a drop, if desired, by calling setDropRow:dropOperation: and returning something other than NSDragOperationNone. One may choose to re-target for various reasons (eg. for better visual feedback when inserting into a sorted position).
*/
- (NSDragOperation)tableView:(NSTableView*)tableView validateDrop:(id <NSDraggingInfo>)info proposedRow:(NSInteger)row proposedDropOperation:(NSTableViewDropOperation)dropOperation;

/* This method is called when the mouse is released over an outline view that previously decided to allow a drop via the validateDrop method.  The data source should incorporate the data from the dragging pasteboard at this time. 'row' and 'dropOperation' contain the values previously set in the validateDrop: method.
*/
- (BOOL)tableView:(NSTableView*)tableView acceptDrop:(id <NSDraggingInfo>)info row:(NSInteger)row dropOperation:(NSTableViewDropOperation)dropOperation;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* NSTableView data source objects can support file promised drags via by adding  NSFilesPromisePboardType to the pasteboard in tableView:writeRowsWithIndexes:toPasteboard:.  NSTableView implements -namesOfPromisedFilesDroppedAtDestination: to return the results of this data source method.  This method should returns an array of filenames for the created files (filenames only, not full paths).  The URL represents the drop location.  For more information on file promise dragging, see documentation on the NSDraggingSource protocol and -namesOfPromisedFilesDroppedAtDestination:.
*/
- (NSArray *)tableView:(NSTableView *)tableView namesOfPromisedFilesDroppedAtDestination:(NSURL *)dropDestination forDraggedRowsWithIndexes:(NSIndexSet *)indexSet;
#endif


/*
 * Deprecated delegate methods
 */
 
// Deprecated in Mac OS 10.4.  You should implement tableView:writeRowsWithIndexes:toPasteboard: instead.  See that method for more details.
- (BOOL)tableView:(NSTableView *)tableView writeRows:(NSArray *)rows toPasteboard:(NSPasteboard *)pboard;
@end


/* Deprecated methods */

@interface NSTableView (NSDeprecated) 
// Deprecated in Mac OS 10.3.  Calls setGridStyleMask:, setting grid style to either None, or vertical and horizonal solid grid lines as appropriate.
- (void)setDrawsGrid:(BOOL)flag;
// Deprecated in Mac OS 10.3.  Returns YES if gridStyleMask returns anything other than NSTableViewGridNone.
- (BOOL)drawsGrid;

// Deprecated in Mac OS 10.3.  You should use selectColumnIndexes:byExtendingSelection: instead.  See that method for more details.
- (void)selectColumn:(NSInteger)column byExtendingSelection:(BOOL)extend;
// Deprecated in Mac OS 10.3.  You should use selectRowIndexes:byExtendingSelection: instead.  See that method for more details.
- (void)selectRow:(NSInteger)row byExtendingSelection:(BOOL)extend;
// Deprecated in Mac OS 10.3.  You should use selectedColumnIndexes instead.
- (NSEnumerator *)selectedColumnEnumerator;
// Deprecated in Mac OS 10.3.  You should use selectedRowIndexes instead.
- (NSEnumerator *)selectedRowEnumerator;

// Deprecated in Mac OS 10.4.  You should use / override dragImageForRowsWithIndexes:tableColumns:event:dragImageOffset: instead.
- (NSImage*)dragImageForRows:(NSArray*)dragRows event:(NSEvent *)dragEvent dragImageOffset:(NSPointPointer)dragImageOffset;

// Deprecated in Mac OS 10.4.  You should use setColumnAutoresizingStyle: instead.  To preserve compatibility, if flag is YES, This method calls setColumnAutoresizingStyle:NSTableViewUniformColumnAutoresizingStyle.  If flag is NO, this method calls setColumnAutoresizingStyle:NSTableViewLastColumnOnlyAutoresizingStyle.
- (void)setAutoresizesAllColumnsToFit:(BOOL)flag;
- (BOOL)autoresizesAllColumnsToFit;

/* Deprecated in Mac OS 10.5. Since an NSTableColumn can have visible=NO, it is no longer possible to return a valid range of columns given a rect. Use columnIndexesInRect: 
*/
- (NSRange)columnsInRect:(NSRect)rect;

@end
