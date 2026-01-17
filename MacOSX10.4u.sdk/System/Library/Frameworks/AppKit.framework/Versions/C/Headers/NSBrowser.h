/*
	NSBrowser.h
	Application Kit
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <AppKit/NSControl.h>

#define NSAppKitVersionNumberWithContinuousScrollingBrowser 680.0
#define NSAppKitVersionNumberWithColumnResizingBrowser      685.0

@class NSMatrix, NSScroller, NSMutableArray;

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

typedef enum _NSBrowserColumnResizingType {
    NSBrowserNoColumnResizing = 0,    /* Column sizes are fixed and set by developer.     */
    NSBrowserAutoColumnResizing = 1,  /* No user resizing. Columns grow as window grows.  */
    NSBrowserUserColumnResizing = 2   /* Columns fixed as window grows.  User can resize. */
} NSBrowserColumnResizingType;

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
- (void)setMinColumnWidth:(float)columnWidth;
- (float)minColumnWidth;

- (void)setMaxVisibleColumns:(int)columnCount;
- (int)maxVisibleColumns;
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

- (void)setTitle:(NSString *)aString ofColumn:(int)column;
- (NSString *)titleOfColumn:(int)column;
- (void)setPathSeparator:(NSString *)newString;
- (NSString *)pathSeparator;
- (BOOL)setPath:(NSString *)path;
- (NSString *)path;
- (NSString *)pathToColumn:(int)column;
- (int)selectedColumn;
- (id)selectedCell;
- (id)selectedCellInColumn:(int)column;
- (NSArray *)selectedCells;
- (void)selectRow:(int)row inColumn:(int)column;
- (int)selectedRowInColumn:(int)column;

- (void)reloadColumn:(int)column;
- (void)validateVisibleColumns;
- (void)scrollColumnsRightBy:(int)shiftAmount;
- (void)scrollColumnsLeftBy:(int)shiftAmount;
- (void)scrollColumnToVisible:(int)column;

- (void)setLastColumn:(int)column;
- (int)lastColumn;
- (void)addColumn;
- (int)numberOfVisibleColumns;
- (int)firstVisibleColumn;
- (int)lastVisibleColumn;
- (int)columnOfMatrix:(NSMatrix *)matrix;
- (NSMatrix *)matrixInColumn:(int)column;
- (id)loadedCellAtRow:(int)row column:(int)col;
- (void)selectAll:(id)sender;
- (void)tile;
- (void)doClick:(id)sender;
- (void)doDoubleClick:(id)sender;
- (BOOL)sendAction;

- (NSRect)titleFrameOfColumn:(int)column;
- (void)drawTitleOfColumn:(int)column inRect:(NSRect)aRect;
- (float)titleHeight;
- (NSRect)frameOfColumn:(int)column;
- (NSRect)frameOfInsideOfColumn:(int)column;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

- (float)columnWidthForColumnContentWidth:(float)columnContentWidth;
- (float)columnContentWidthForColumnWidth:(float)columnWidth;
    // These methods convert between column width (the column's scrollview), and the content width (the matrix in the scrollview).  For example, to guarantee that 16 pixels of your browser cell are always visible, call [browser setMinColumnWidth: [browser columnWidthForColumnContentWidth:16]]

#endif


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

- (void)setColumnResizingType:(NSBrowserColumnResizingType)columnResizingType;
- (NSBrowserColumnResizingType)columnResizingType;
    // Default is NSBrowserAutoColumnResizing.  This setting is persistent.

- (void)setPrefersAllColumnUserResizing:(BOOL)prefersAllColumnResizing;
- (BOOL)prefersAllColumnUserResizing;
    // Default is NO.  This setting is persistent.  This setting only applies to NSBrowserUserColumnResizing type browsers.  If YES, the browser defaults to resizing all columns simultaneously, otherwise it defaults to single column resizing. Holding down the option key while resizing switches the type of resizing used.

- (void)setWidth:(float)columnWidth ofColumn:(int)columnIndex;
- (float)widthOfColumn:(int)column;
    // setWidth:ofColumn: does nothing if columnResizingType is NSBrowserAutoColumnResizing.  Otherwise, Sets the width of the specified column.  To set the default width for new columns (which don't otherwise have initial width from defaults or via the delegate), use columnIndex of -1.  The value set for columnIndex of -1 is persistent.  NSBrowserColumnConfigurationDidChangeNotification will be posted (not immediately) if necessary.  The receiver will autosave its column configuration if necessary.

- (void)setColumnsAutosaveName:(NSString *)name;
- (NSString *)columnsAutosaveName;
    // Sets the name used to automatically save the receiverÕs column configuration.  This setting is persistent.  If name is different from the current name, this method also reads in the saved column configuration for the new name and applies the values to the browser.  Column configuration is defined as an array of column content widths.  One width is saved for each level the user has reached.  That is, browser saves column width based on depth, not based on unique paths.  To do more complex column persistence, you should register for NSBrowserColumnConfigurationDidChangeNotifications and handle persistence yourself.

+ (void)removeSavedColumnsWithAutosaveName:(NSString *)name;
    // Removes the column data stored under name from the applicationÕs user defaults.
    

#endif


// Use of -displayColumn: is deprecated in 10.3.  Use setNeedsDisplayInRect: instead.
- (void)displayColumn:(int)column;

// Use of -displayAllColumns; is deprecated in 10.3.  Use setNeedsDisplay/InRect: instead.
- (void)displayAllColumns;

// Use of -scrollViaScroller: is deprecated in 10.3.  Continuous scrolling no longer requires this functionality.
- (void)scrollViaScroller:(NSScroller *)sender;

// Use of -updateScroller is deprecated in 10.3.  Continuous scrolling no longer requires this functionality.
- (void)updateScroller;

@end

/*
 * Notifications
 */
APPKIT_EXTERN NSString * NSBrowserColumnConfigurationDidChangeNotification AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
    // Object   : browser - the browser whose column sizes need to be persisted.
    // UserInfo : No user info.


@interface NSObject(NSBrowserDelegate)
/* Exactly one of the following two methods is required */
- (int)browser:(NSBrowser *)sender numberOfRowsInColumn:(int)column;
- (void)browser:(NSBrowser *)sender createRowsForColumn:(int)column inMatrix:(NSMatrix *)matrix;

- (void)browser:(NSBrowser *)sender willDisplayCell:(id)cell atRow:(int)row column:(int)column;

- (NSString *)browser:(NSBrowser *)sender titleOfColumn:(int)column;
- (BOOL)browser:(NSBrowser *)sender selectCellWithString:(NSString *)title inColumn:(int)column;
- (BOOL)browser:(NSBrowser *)sender selectRow:(int)row inColumn:(int)column;
- (BOOL)browser:(NSBrowser *)sender isColumnValid:(int)column;
- (void)browserWillScroll:(NSBrowser *)sender;
- (void)browserDidScroll:(NSBrowser *)sender;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

/*
 * Delegate methods used by resizable column browsers.
 */
- (float)browser:(NSBrowser *)browser shouldSizeColumn:(int)columnIndex forUserResize:(BOOL)forUserResize toWidth:(float)suggestedWidth;
    // Optional for browsers with resize type NSBrowserNoColumnResizing, and NSBrowserUserColumnResizing.
    // This method is used for both constraining column resize, and determining a columns initial size.  If 'forUserResize' is NO, this method should return the initial width for a newly added column.  If 'forUserResize' is YES, this method can be used to constrain resizing on a per-column basis.  (Currently per-column constraining is not implemented, so forUserResize will always be NO).

- (float)browser:(NSBrowser *)browser sizeToFitWidthOfColumn:(int)columnIndex;
    // Optional for browsers with resize type NSBrowserUserColumnResizing only.
    // This method returns the "ideal" width for a column.  This method is used when performing a "right-size-each" or "right-size-one" operation.  If columnIndex is -1, the result is used for a "right-size-all-simultaneous" operation.  In this case, you should return a best uniform right size for all column (every column will be set to this size).  It is assumed that the implementation may be expensive, so it will be called only when necessary.  (See documentation for definitions of right-size one/each/all).

- (void)browserColumnConfigurationDidChange:(NSNotification *)notification;
    // Optional and used for browsers with resize type NSBrowserUserColumnResizing only.
    // This method is intended to be used by clients wishing to implement their own column width persistence.  It is called when the width of any browser columns has changed.  User column resizing will cause a single notification to be posted when the user is finished resizing.  (See NSBrowserColumnConfigurationDidChangeNotification for more information.)

#endif

@end

