/*
	NSBrowser.h
	Application Kit
	Copyright (c) 1994-2007, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSControl.h>
#import <AppKit/NSDragging.h>

#define NSAppKitVersionNumberWithContinuousScrollingBrowser 680.0
#define NSAppKitVersionNumberWithColumnResizingBrowser      685.0

@class NSMatrix, NSScroller, NSMutableArray, NSIndexSet;

typedef struct __Brflags {
#ifdef __BIG_ENDIAN__
    unsigned int        allowsMultipleSelection:1;
    unsigned int        allowsBranchSelection:1;
    unsigned int        reuseColumns:1;
    unsigned int        isTitled:1;
    unsigned int        titleFromPrevious:1;
    unsigned int        separateColumns:1;
    unsigned int        delegateImplementsWillDisplayCell:1;
    unsigned int        delegateSetsTitles:1;
    unsigned int        delegateSelectsCellsByString:1;
    unsigned int        delegateDoesNotCreateRowsInMatrix:1;
    unsigned int        delegateValidatesColumns:1;
    unsigned int        acceptArrowKeys:1;
    unsigned int        dontDrawTitles:1;
    unsigned int        sendActionOnArrowKeys:1;
    unsigned int        prohibitEmptySel:1;
    unsigned int        hasHorizontalScroller:1;
    unsigned int        time:1;
    unsigned int        allowsIncrementalSearching:1;
    unsigned int        delegateSelectsCellsByRow:1;
    unsigned int        disableCompositing:6;
    unsigned int        refusesFirstResponder:1;
    unsigned int	acceptsFirstMouse:1;
    unsigned int	actionNeedsToBeSent:1;
    unsigned int        usesSmallSizeTitleFont:1;
    unsigned int	usesSmallScrollers:1;
    unsigned int	prefersAllColumnUserResizing:1;
    unsigned int        firstVisibleCalculationDisabled:1;
#else
    unsigned int        firstVisibleCalculationDisabled:1;
    unsigned int 	prefersAllColumnUserResizing:1;
    unsigned int	usesSmallScrollers:1;
    unsigned int        usesSmallSizeTitleFont:1;
    unsigned int	actionNeedsToBeSent:1;
    unsigned int	acceptsFirstMouse:1;
    unsigned int        refusesFirstResponder:1;
    unsigned int        disableCompositing:6;
    unsigned int        delegateSelectsCellsByRow:1;
    unsigned int        allowsIncrementalSearching:1;
    unsigned int        time:1;
    unsigned int        hasHorizontalScroller:1;
    unsigned int        prohibitEmptySel:1;
    unsigned int        sendActionOnArrowKeys:1;
    unsigned int        dontDrawTitles:1;
    unsigned int        acceptArrowKeys:1;
    unsigned int        delegateValidatesColumns:1;
    unsigned int        delegateDoesNotCreateRowsInMatrix:1;
    unsigned int        delegateSelectsCellsByString:1;
    unsigned int        delegateSetsTitles:1;
    unsigned int        delegateImplementsWillDisplayCell:1;
    unsigned int        separateColumns:1;
    unsigned int        titleFromPrevious:1;
    unsigned int        isTitled:1;
    unsigned int        reuseColumns:1;
    unsigned int        allowsBranchSelection:1;
    unsigned int        allowsMultipleSelection:1;
#endif
} _Brflags;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

enum {
    NSBrowserNoColumnResizing = 0,    /* Column sizes are fixed and set by developer.     */
    NSBrowserAutoColumnResizing = 1,  /* No user resizing. Columns grow as window grows.  */
    NSBrowserUserColumnResizing = 2   /* Columns fixed as window grows.  User can resize. */
};
typedef NSUInteger NSBrowserColumnResizingType;

#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

/* In drag and drop, used to specify the drop operation from inside the delegate method browser:validateDrop:proposedRow:column:dropOperation. See the delegate method description for more information.
*/
enum { NSBrowserDropOn, NSBrowserDropAbove };
typedef NSUInteger NSBrowserDropOperation;

#endif 

@interface NSBrowser : NSControl
{
    /*All instance variables are private*/
    id                  _target;
    SEL                 _action;
    id                  _delegate;
    SEL                 _doubleAction;
    Class               _matrixClass;
    id                  _cellPrototype;
    NSSize		_columnSize;
    short		_numberOfVisibleColumns;
    short		_minColumnWidth;
    short		_firstVisibleColumn;
    short		_maxVisibleColumns;
    NSMutableArray	*_titles;
    NSString		*_pathSeparator;
    NSMutableArray	*_columns;
    id                  _brAuxiliaryStorage;
    NSString		*_firstColumnTitle;
    NSScroller		*_scroller;
    _Brflags            _brflags;
}

+ (Class)cellClass;

- (void)loadColumnZero;
- (BOOL)isLoaded;

- (void)setDoubleAction:(SEL)aSelector;
- (SEL)doubleAction;
- (void)setMatrixClass:(Class)factoryId;
- (Class)matrixClass;
- (void)setCellClass:(Class)factoryId;
- (void)setCellPrototype:(NSCell *)aCell;
- (id)cellPrototype;
- (void)setDelegate:(id)anObject;
- (id)delegate;
- (void)setReusesColumns:(BOOL)flag;
- (BOOL)reusesColumns;

- (void)setHasHorizontalScroller:(BOOL)flag;
- (BOOL)hasHorizontalScroller;
- (void)setSeparatesColumns:(BOOL)flag;
- (BOOL)separatesColumns;
- (void)setTitled:(BOOL)flag;
- (BOOL)isTitled;
- (void)setMinColumnWidth:(CGFloat)columnWidth;
- (CGFloat)minColumnWidth;

- (void)setMaxVisibleColumns:(NSInteger)columnCount;
- (NSInteger)maxVisibleColumns;
    // These methods are ignored, and not applicable when using a browser whose resize type is NSBrowserNoColumnResizing or NSBrowserUserColumnResizing.

- (void)setAllowsMultipleSelection:(BOOL)flag;
- (BOOL)allowsMultipleSelection;
- (void)setAllowsBranchSelection:(BOOL)flag;
- (BOOL)allowsBranchSelection;
- (void)setAllowsEmptySelection:(BOOL)flag;
- (BOOL)allowsEmptySelection;
- (void)setTakesTitleFromPreviousColumn:(BOOL)flag;
- (BOOL)takesTitleFromPreviousColumn;

- (void)setAcceptsArrowKeys:(BOOL)flag;
- (BOOL)acceptsArrowKeys;
- (void)setSendsActionOnArrowKeys:(BOOL)flag;
- (BOOL)sendsActionOnArrowKeys;

- (void)setTitle:(NSString *)aString ofColumn:(NSInteger)column;
- (NSString *)titleOfColumn:(NSInteger)column;
- (void)setPathSeparator:(NSString *)newString;
- (NSString *)pathSeparator;
- (BOOL)setPath:(NSString *)path;
- (NSString *)path;
- (NSString *)pathToColumn:(NSInteger)column;

- (NSInteger)selectedColumn;
- (id)selectedCell;
- (id)selectedCellInColumn:(NSInteger)column;
- (NSArray *)selectedCells;
- (void)selectRow:(NSInteger)row inColumn:(NSInteger)column;
- (NSInteger)selectedRowInColumn:(NSInteger)column;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

/* Sets the selected row 'indexes' in the matrix located at 'column'. 
 */
- (void)selectRowIndexes:(NSIndexSet *)indexes inColumn:(NSInteger)column;

/* Returns the selected cell indexes in the matrix located at 'column'. 
 */
- (NSIndexSet *)selectedRowIndexesInColumn:(NSInteger)column;

#endif

- (void)reloadColumn:(NSInteger)column;
- (void)validateVisibleColumns;
- (void)scrollColumnsRightBy:(NSInteger)shiftAmount;
- (void)scrollColumnsLeftBy:(NSInteger)shiftAmount;
- (void)scrollColumnToVisible:(NSInteger)column;

- (void)setLastColumn:(NSInteger)column;
- (NSInteger)lastColumn;
- (void)addColumn;
- (NSInteger)numberOfVisibleColumns;
- (NSInteger)firstVisibleColumn;
- (NSInteger)lastVisibleColumn;
- (NSInteger)columnOfMatrix:(NSMatrix *)matrix;
- (NSMatrix *)matrixInColumn:(NSInteger)column;
- (id)loadedCellAtRow:(NSInteger)row column:(NSInteger)col;
- (void)selectAll:(id)sender;
- (void)tile;
- (void)doClick:(id)sender;
- (void)doDoubleClick:(id)sender;
- (BOOL)sendAction;

- (NSRect)titleFrameOfColumn:(NSInteger)column;
- (void)drawTitleOfColumn:(NSInteger)column inRect:(NSRect)aRect;
- (CGFloat)titleHeight;
- (NSRect)frameOfColumn:(NSInteger)column;
- (NSRect)frameOfInsideOfColumn:(NSInteger)column;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

/* These methods convert between column width (the column's scrollview), and the content width (the matrix in the scrollview).  For example, to guarantee that 16 pixels of your browser cell are always visible, call [browser setMinColumnWidth: [browser columnWidthForColumnContentWidth:16]] */
- (CGFloat)columnWidthForColumnContentWidth:(CGFloat)columnContentWidth;
- (CGFloat)columnContentWidthForColumnWidth:(CGFloat)columnWidth;

#endif


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

/* Default is NSBrowserAutoColumnResizing.  This setting is persistent. */
- (void)setColumnResizingType:(NSBrowserColumnResizingType)columnResizingType;
- (NSBrowserColumnResizingType)columnResizingType;

/* Default is NO.  This setting is persistent.  This setting only applies to NSBrowserUserColumnResizing type browsers.  If YES, the browser defaults to resizing all columns simultaneously, otherwise it defaults to single column resizing. Holding down the option key while resizing switches the type of resizing used. */
- (void)setPrefersAllColumnUserResizing:(BOOL)prefersAllColumnResizing;
- (BOOL)prefersAllColumnUserResizing;

/* setWidth:ofColumn: does nothing if columnResizingType is NSBrowserAutoColumnResizing.  Otherwise, Sets the width of the specified column.  To set the default width for new columns (which don't otherwise have initial width from defaults or via the delegate), use columnIndex of -1.  The value set for columnIndex of -1 is persistent.  NSBrowserColumnConfigurationDidChangeNotification will be posted (not immediately) if necessary.  The receiver will autosave its column configuration if necessary. */
- (void)setWidth:(CGFloat)columnWidth ofColumn:(NSInteger)columnIndex;
- (CGFloat)widthOfColumn:(NSInteger)column;

/* Sets the name used to automatically save the receivers column configuration.  This setting is persistent.  If name is different from the current name, this method also reads in the saved column configuration for the new name and applies the values to the browser.  Column configuration is defined as an array of column content widths.  One width is saved for each level the user has reached.  That is, browser saves column width based on depth, not based on unique paths.  To do more complex column persistence, you should register for NSBrowserColumnConfigurationDidChangeNotifications and handle persistence yourself. */
- (void)setColumnsAutosaveName:(NSString *)name;
- (NSString *)columnsAutosaveName;

/* Removes the column data stored under name from the applications user defaults. */
+ (void)removeSavedColumnsWithAutosaveName:(NSString *)name;
    
#endif


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

#pragma mark -
#pragma mark **** Drag and Drop Support ****

/* The return value indicates whether the receiver can attempt to initiate a drag for the given event. You can override this method and return NO to disallow initiating drags at the location in the given event. By default, the method will return YES if rowIndexes contains at least one item, and each item is enabled. If the equivalent delegate method is present, it will be preferred over this method, and you can safely call this method from your delegate. 
*/
- (BOOL)canDragRowsWithIndexes:(NSIndexSet *)rowIndexes inColumn:(NSInteger)column withEvent:(NSEvent *)event;

/* This method computes and returns an image to use for dragging. You can override this to return a custom drag image, or call it to get the default drag image from the delegate method. 'rowIndexes' are the indexes of the cells being dragged in matrix 'column'. 'event' is a reference to the mouse down event that began the drag. 'dragImageOffset' is an in/out parameter. This method will be called with dragImageOffset set to NSZeroPoint, but it can be modified to re-position the returned image. A dragImageOffset of NSZeroPoint will cause the image to be centered under the mouse. By default, an image will be created that contain the visible cells within 'rowIndexes'. If the equivalent delegate method is present, it will be preferred over this method, and you can safely call this method from your delegate. 
*/
- (NSImage *)draggingImageForRowsWithIndexes:(NSIndexSet *)rowIndexes inColumn:(NSInteger)column withEvent:(NSEvent *)event offset:(NSPointPointer)dragImageOffset;

/* Configures the value returned from -draggingSourceOperationMaskForLocal:. An isLocal value of YES indicates that 'mask' applies when the destination object is in the same application. By default, NSDragOperationEvery will be returned. An isLocal value of NO indicates that 'mask' applies when the destination object in an application outside the receiver's application. By default, NSDragOperationNone is returned. NSBrowser will save the values you set for each isLocal setting. You typically will invoke this method, and not override it. 
    */
- (void)setDraggingSourceOperationMask:(NSDragOperation)mask forLocal:(BOOL)isLocal;

#pragma mark -

/* Allow type selection in this NSBrowser. The default for 'allowsTypeSelect' is YES.
*/
- (BOOL)allowsTypeSelect;
- (void)setAllowsTypeSelect:(BOOL)value;

/* The background color to be drawn. By default, it will be set [NSColor whiteColor]. You can use [NSColor clearColor] to make the background transparent. NSBrowser will return YES from isOpaque if the backgroundColor has an alphaComponent of 1.0 and it doesn't have a title, otherwise, it will return NO. Calling setBackgroundColor: will cause all NSMatrix instances have setDrawsBackground:NO be called in order for the NSBrowser's background color to show through. When drawing with the background color, NSCompositeSourceOver is used for the compositing operation.
 */
- (void)setBackgroundColor:(NSColor *)color;
- (NSColor *)backgroundColor;

#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5 */ 

#pragma mark **** Deprecated NSBrowser methods ****

// Use of -displayColumn: is deprecated in 10.3.  Use setNeedsDisplayInRect: instead.
- (void)displayColumn:(NSInteger)column;

// Use of -displayAllColumns; is deprecated in 10.3.  Use setNeedsDisplay/InRect: instead.
- (void)displayAllColumns;

// Use of -scrollViaScroller: is deprecated in 10.3.  Continuous scrolling no longer requires this functionality.
- (void)scrollViaScroller:(NSScroller *)sender;

// Use of -updateScroller is deprecated in 10.3.  Continuous scrolling no longer requires this functionality.
- (void)updateScroller;

#pragma mark -

@end


/*
 * Notifications
 */
APPKIT_EXTERN NSString * NSBrowserColumnConfigurationDidChangeNotification AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
    // Object   : browser - the browser whose column sizes need to be persisted.
    // UserInfo : No user info.


@interface NSObject(NSBrowserDelegate)
/* Exactly one of the following two methods is required */
- (NSInteger)browser:(NSBrowser *)sender numberOfRowsInColumn:(NSInteger)column;
- (void)browser:(NSBrowser *)sender createRowsForColumn:(NSInteger)column inMatrix:(NSMatrix *)matrix;

- (void)browser:(NSBrowser *)sender willDisplayCell:(id)cell atRow:(NSInteger)row column:(NSInteger)column;

- (NSString *)browser:(NSBrowser *)sender titleOfColumn:(NSInteger)column;
- (BOOL)browser:(NSBrowser *)sender selectCellWithString:(NSString *)title inColumn:(NSInteger)column;
- (BOOL)browser:(NSBrowser *)sender selectRow:(NSInteger)row inColumn:(NSInteger)column;
- (BOOL)browser:(NSBrowser *)sender isColumnValid:(NSInteger)column;
- (void)browserWillScroll:(NSBrowser *)sender;
- (void)browserDidScroll:(NSBrowser *)sender;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

/*
 * Delegate methods used by resizable column browsers.
 */

/*
 Optional for browsers with resize type NSBrowserNoColumnResizing, and NSBrowserUserColumnResizing.
 This method is used for both constraining column resize, and determining a columns initial size.  If 'forUserResize' is NO, this method should return the initial width for a newly added column.  If 'forUserResize' is YES, this method can be used to constrain resizing on a per-column basis.  (Currently per-column constraining is not implemented, so forUserResize will always be NO).
 */
- (CGFloat)browser:(NSBrowser *)browser shouldSizeColumn:(NSInteger)columnIndex forUserResize:(BOOL)forUserResize toWidth:(CGFloat)suggestedWidth;

/* 
 Optional for browsers with resize type NSBrowserUserColumnResizing only.
 This method returns the "ideal" width for a column.  This method is used when performing a "right-size-each" or "right-size-one" operation.  If columnIndex is -1, the result is used for a "right-size-all-simultaneous" operation.  In this case, you should return a best uniform right size for all column (every column will be set to this size).  It is assumed that the implementation may be expensive, so it will be called only when necessary.  (See documentation for definitions of right-size one/each/all). 
 */
- (CGFloat)browser:(NSBrowser *)browser sizeToFitWidthOfColumn:(NSInteger)columnIndex;

/*
 Optional and used for browsers with resize type NSBrowserUserColumnResizing only.
 This method is intended to be used by clients wishing to implement their own column width persistence.  It is called when the width of any browser columns has changed.  User column resizing will cause a single notification to be posted when the user is finished resizing.  (See NSBrowserColumnConfigurationDidChangeNotification for more information.)  */
- (void)browserColumnConfigurationDidChange:(NSNotification *)notification;

#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3 */ 


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

/* Optional - Expansion ToolTip support.
    Implement this method and return NO to prevent an expansion tooltip from appearing for a particular cell at 'row' in 'column'. See NSCell.h for more information on expansion tool tips. */
- (BOOL)browser:(NSBrowser *)browser shouldShowCellExpansionForRow:(NSInteger)row column:(NSInteger)column;


#pragma mark -
#pragma mark **** Optional Drag and Drop Support Methods ****

#pragma mark ** Dragging Source Methods **

/* This method is called after it has been determined that a drag should begin, but before the drag has been started.  To refuse the drag, return NO. To start a drag, declared the pasteboard types that you support with [pasteboard declareTypes:owner:], place your data on the pasteboard, and return YES from the method. The drag image and other drag related information will be set up and provided by the view once this call returns with YES. You need to implement this method for your browser to be a drag source. 
*/
- (BOOL)browser:(NSBrowser *)browser writeRowsWithIndexes:(NSIndexSet *)rowIndexes inColumn:(NSInteger)column toPasteboard:(NSPasteboard *)pasteboard;

/* The delegate can support file promise drags by adding NSFilesPromisePboardType to the pasteboard in browser:writeRowsWithIndexes:inColumn:toPasteboard:. NSBrowser implements -namesOfPromisedFilesDroppedAtDestination: to return the results of this data source method.  This method should returns an array of filenames for the created files (filenames only, not full paths).  The URL represents the drop location.  For more information on file promise dragging, see documentation on the NSDraggingSource protocol and -namesOfPromisedFilesDroppedAtDestination:. You do not need to implement this method for your browser to be a drag source.
    */
- (NSArray *)browser:(NSBrowser *)browser namesOfPromisedFilesDroppedAtDestination:(NSURL *)dropDestination forDraggedRowsWithIndexes:(NSIndexSet *)rowIndexes inColumn:(NSInteger)column;

/* The delegate can control if some particular rows can be dragged or not for a particular event. You do not need to implement this method for your browser to be a drag source. 
*/
- (BOOL)browser:(NSBrowser *)browser canDragRowsWithIndexes:(NSIndexSet *)rowIndexes inColumn:(NSInteger)column withEvent:(NSEvent *)event;

/* Allows the delegate to compute a dragging image for the particular cells being dragged. 'rowIndexes' are the indexes of the cells being dragged in the matrix in 'column'. 'event' is a reference to the mouse down event that began the drag. 'dragImageOffset' is an in/out parameter. This method will be called with dragImageOffset set to NSZeroPoint, but it can be modified to re-position the returned image.  A dragImageOffset of NSZeroPoint will cause the image to be centered under the mouse. You can safely call [browser dragImageForRowsWithIndexes:inColumn:withEvent:offset:] from inside this method. You do not need to implement this method for your browser to be a drag source. You can safely call the corresponding NSBrowser method.
*/
- (NSImage *)browser:(NSBrowser *)browser draggingImageForRowsWithIndexes:(NSIndexSet *)rowIndexes inColumn:(NSInteger)column withEvent:(NSEvent *)event offset:(NSPointPointer)dragImageOffset;

#pragma mark ** Dragging Destination Methods **

/* This method is used by the browser to determine a valid drop target. Based on the mouse position, the browser will suggest a proposed row, column and dropOperation. These values are in/out parameters and can be changed by the delegate to retarget the drop operation. The dropOperation suggested will be NSBrowserDropOn if the drag location is closer to the middle of a row. If it is closer to being between two rows, it will be NSBrowserDropAbove, indicating a drop above 'row' and below 'row - 1'. This method must return a value that indicates which dragging operation the data source will perform. It must return something other than NSDragOperationNone to accept the drop.

    To retarget a drop and specify a drop on row 2 (with the first visual row being row 0), one would set *row=2, and set *dropOperation=NSBrowserDropOn. To specify a drop below the last row, one would specify *row=[browser numberOfRows], and *dropOperation=NSBrowserDropAbove. To specify a drop on the entire column, you will specify *row=-1, and *dropOperation=NSBrowserDropOn. To specify a drop between rows 2 and 3, one would set *row=3 and *dropOperation=NSBrowserDropAbove.

    Note: to receive drag messages, you must first call [NSBrowser registerForDraggedTypes:] for the drag types you want to support (typically this is done in awakeFromNib). You must implement this method for your browser to be a drag destination. 
*/
- (NSDragOperation)browser:(NSBrowser *)browser validateDrop:(id <NSDraggingInfo>)info proposedRow:(NSInteger *)row column:(NSInteger *)column  dropOperation:(NSBrowserDropOperation *)dropOperation;

/* This method is called when the mouse is released over a browser that previously decided to allow a drop via the above validateDrop method.  The delegate should incorporate the data from the dragging pasteboard at this time. You must implement this method for your browser to be a drag destination.
*/
- (BOOL)browser:(NSBrowser *)browser acceptDrop:(id <NSDraggingInfo>)info atRow:(NSInteger)row column:(NSInteger)column dropOperation:(NSBrowserDropOperation)dropOperation;

#pragma mark -

#pragma mark **** Type Select Support ****

/* Optional - Type select support
    Implement this method if you want to control the string that is used for type selection. You may want to change what is searched for based on what is displayed, or simply return an empty string for that row and/or column to not be searched. You can also return 'nil' if the cell does not contain any text. By default, all cells with text in them are searched. The default value when this delegate method is not implemented is the stringValue for the cell at that location.
*/
- (NSString *)browser:(NSBrowser *)browser typeSelectStringForRow:(NSInteger)row inColumn:(NSInteger)column;

/* Optional - Type select support
    Implement this method if you would like to prevent a type select from happening based on the current event and current search string. Generally, this will be called from keyDown: and the event will be a key event. The search string will be nil if no type select has began. 
*/
- (BOOL)browser:(NSBrowser *)browser shouldTypeSelectForEvent:(NSEvent *)event withCurrentSearchString:(NSString *)searchString;

/* Optional - Type select support
    Implement this method if you want to control how type selection works. Return the first row that matches searchString from within the range of startRow to endRow. It is possible for endRow to be less than startRow if the search will wrap. Return -1 when there is no match. Include startRow as a possible match, but do not include endRow. It is not necessary to implement this method in order to support type select.
*/
- (NSInteger)browser:(NSBrowser *)browser nextTypeSelectMatchFromRow:(NSInteger)startRow toRow:(NSInteger)endRow inColumn:(NSInteger)column forString:(NSString *)searchString;

#pragma mark -

#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5 */

@end

