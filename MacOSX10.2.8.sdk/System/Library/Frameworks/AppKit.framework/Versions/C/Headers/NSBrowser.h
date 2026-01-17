/*
	NSBrowser.h
	Application Kit
	Copyright (c) 1994-2001, Apple Computer, Inc.
	All rights reserved.
*/

#import <AppKit/NSControl.h>

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
    unsigned int        RESERVED:2;
#else
    unsigned int        RESERVED:2;
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
    NSMutableArray	*_unusedColumns;
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
- (void)displayColumn:(int)column;
- (void)displayAllColumns;
- (void)scrollColumnsRightBy:(int)shiftAmount;
- (void)scrollColumnsLeftBy:(int)shiftAmount;
- (void)scrollColumnToVisible:(int)column;
- (void)scrollViaScroller:(NSScroller *)sender;
- (void)updateScroller;
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

@end

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
@end

