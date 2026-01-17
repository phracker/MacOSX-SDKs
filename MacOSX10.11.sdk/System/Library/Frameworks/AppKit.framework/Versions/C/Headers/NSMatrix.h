/*
	NSMatrix.h
	Application Kit
	Copyright (c) 1994-2015, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <AppKit/NSControl.h>
#import <AppKit/NSUserInterfaceValidation.h>

NS_ASSUME_NONNULL_BEGIN

@class NSColor;
@protocol NSMatrixDelegate;

/* Matrix Constants */

typedef NS_ENUM(NSUInteger, NSMatrixMode) {
    NSRadioModeMatrix			= 0,
    NSHighlightModeMatrix		= 1,
    NSListModeMatrix			= 2,
    NSTrackModeMatrix			= 3
};

typedef struct __MFlags {
#ifdef __BIG_ENDIAN__
    unsigned int	highlightMode:1;
    unsigned int	radioMode:1;
    unsigned int	listMode:1;
    unsigned int	allowEmptySel:1;
    unsigned int	autoscroll:1;
    unsigned int	selectionByRect:1;
    unsigned int	drawsCellBackground:1;
    unsigned int	drawsBackground:1;
    unsigned int	autosizeCells:1;
    unsigned int	drawingAncestor:1;
    unsigned int	tabKeyTraversesCells:1;
    unsigned int	tabKeyTraversesCellsExplicitlySet:1;
    unsigned int	allowsIncrementalSearching:1;
    unsigned int	currentlySelectingCell:1;
    unsigned int	onlySetKeyCell:1;
    unsigned int	changingSelectionWithKeyboard:1;
    unsigned int	dontScroll:1;
    unsigned int	refusesFirstResponder:1;
    unsigned int	useSimpleTrackingMode:1;
    unsigned int	checkForSimpleTrackingMode:1;
    unsigned int	liveResizeImageCacheingEnabled:1;
    unsigned int 	hasCachedSubclassIsSafeForLiveResize:1;
    unsigned int	subclassIsSafeForLiveResize:1;
    unsigned int 	tmpAllowNonVisibleCellsToBecomeFirstResponder:1;
    unsigned int 	needsRedrawBeforeFirstLiveResizeCache:1;
    unsigned int        browserOptimizationsEnabled:1;
    unsigned int        drawingContextMenuHighlight:1;
    unsigned int	drawingContextMenuHighlightOnAllSelectedRows:1;
    unsigned int      autorecalculatesCellSize:1;
    unsigned int       cellSizeNeedsAutorecalc:1;
    unsigned int	reservedMatrix:2;
#else
    unsigned int	reservedMatrix:2;
    unsigned int       cellSizeNeedsAutorecalc:1;
    unsigned int      autorecalculatesCellSize:1;
    unsigned int	drawingContextMenuHighlightOnAllSelectedRows:1;
    unsigned int        drawingContextMenuHighlight:1;
    unsigned int        browserOptimizationsEnabled:1;
    unsigned int 	needsRedrawBeforeFirstLiveResizeCache:1;
    unsigned int 	tmpAllowNonVisibleCellsToBecomeFirstResponder:1;
    unsigned int	subclassIsSafeForLiveResize:1;
    unsigned int 	hasCachedSubclassIsSafeForLiveResize:1;
    unsigned int	liveResizeImageCacheingEnabled:1;
    unsigned int	checkForSimpleTrackingMode:1;
    unsigned int	useSimpleTrackingMode:1;
    unsigned int	refusesFirstResponder:1;
    unsigned int	dontScroll:1;
    unsigned int	changingSelectionWithKeyboard:1;
    unsigned int	onlySetKeyCell:1;
    unsigned int	currentlySelectingCell:1;
    unsigned int	allowsIncrementalSearching:1;
    unsigned int	tabKeyTraversesCellsExplicitlySet:1;
    unsigned int	tabKeyTraversesCells:1;
    unsigned int	drawingAncestor:1;
    unsigned int	autosizeCells:1;
    unsigned int	drawsBackground:1;
    unsigned int	drawsCellBackground:1;
    unsigned int	selectionByRect:1;
    unsigned int	autoscroll:1;
    unsigned int	allowEmptySel:1;
    unsigned int	listMode:1;
    unsigned int	radioMode:1;
    unsigned int	highlightMode:1;
#endif
} _MFlags;

/*
    NSMatrix is deprecated and will be unsupported in future releases.  For radio button grouping, sibling radio buttons that share the same action will operate in an exclusive mode.
 */
@interface NSMatrix : NSControl <NSUserInterfaceValidations>
{
    /*All instance variables are private*/
    id                  _reserved2;
    SEL                 _reserved3;
    SEL                 _doubleAction;
    SEL                 _errorAction;
    id                  _delegate;
    id                  _selectedCell;
    NSInteger           _selectedRow;
    NSInteger           _selectedCol;
    NSInteger           _numRows;
    NSInteger           _numCols;
    NSSize              _cellSize;
    NSSize              _intercell;
    id                  _font;
    id                  _protoCell;
    id                  _cellClass;
    NSColor             *_backgroundColor;
    id                  _private;
    NSMutableArray	*_cells;
    _MFlags              _mFlags;
}


- (instancetype)initWithFrame:(NSRect)frameRect;
- (instancetype)initWithFrame:(NSRect)frameRect mode:(NSMatrixMode)aMode prototype:(NSCell *)aCell numberOfRows:(NSInteger)rowsHigh numberOfColumns:(NSInteger)colsWide;
- (instancetype)initWithFrame:(NSRect)frameRect mode:(NSMatrixMode)aMode cellClass:(nullable Class)factoryId numberOfRows:(NSInteger)rowsHigh numberOfColumns:(NSInteger)colsWide;


@property (assign) Class cellClass;
@property (nullable, copy) __kindof NSCell *prototype;
- (NSCell *)makeCellAtRow:(NSInteger)row column:(NSInteger)col;
@property NSMatrixMode mode;
@property BOOL allowsEmptySelection;
- (void)sendAction:(SEL)aSelector to:(id)anObject forAllCells:(BOOL)flag;
@property (readonly, copy) NSArray<NSCell *> *cells;
- (void)sortUsingSelector:(SEL)comparator;
- (void)sortUsingFunction:(NSInteger (*)(id, id, void * __nullable))compare context:(nullable void *)context;
@property (nullable, readonly, strong) __kindof NSCell *selectedCell;
@property (readonly, copy) NSArray<__kindof NSCell *> *selectedCells;
@property (readonly) NSInteger selectedRow;
@property (readonly) NSInteger selectedColumn;
@property (getter=isSelectionByRect) BOOL selectionByRect;
- (void)setSelectionFrom:(NSInteger)startPos to:(NSInteger)endPos anchor:(NSInteger)anchorPos highlight:(BOOL)lit;
- (void)deselectSelectedCell;
- (void)deselectAllCells;
- (void)selectCellAtRow:(NSInteger)row column:(NSInteger)col;
- (void)selectAll:(nullable id)sender;
- (BOOL)selectCellWithTag:(NSInteger)anInt;
@property NSSize cellSize;
@property NSSize intercellSpacing;
- (void)setScrollable:(BOOL)flag;
@property (copy) NSColor *backgroundColor;
@property (nullable, copy) NSColor *cellBackgroundColor;
@property BOOL drawsCellBackground;
@property BOOL drawsBackground;
- (void)setState:(NSInteger)value atRow:(NSInteger)row column:(NSInteger)col;
- (void)getNumberOfRows:(nullable NSInteger *)rowCount columns:(nullable NSInteger *)colCount;
@property (readonly) NSInteger numberOfRows;
@property (readonly) NSInteger numberOfColumns;
- (nullable __kindof NSCell *)cellAtRow:(NSInteger)row column:(NSInteger)col;
- (NSRect)cellFrameAtRow:(NSInteger)row column:(NSInteger)col;
- (BOOL)getRow:(NSInteger *)row column:(NSInteger *)col ofCell:(NSCell *)aCell;
- (BOOL)getRow:(NSInteger *)row column:(NSInteger *)col forPoint:(NSPoint)aPoint;
- (void)renewRows:(NSInteger)newRows columns:(NSInteger)newCols;
- (void)putCell:(NSCell *)newCell atRow:(NSInteger)row column:(NSInteger)col;
- (void)addRow;
- (void)addRowWithCells:(NSArray<NSCell *> *)newCells;
- (void)insertRow:(NSInteger)row;
- (void)insertRow:(NSInteger)row withCells:(NSArray<NSCell *> *)newCells;
- (void)removeRow:(NSInteger)row;
- (void)addColumn;
- (void)addColumnWithCells:(NSArray<NSCell *> *)newCells;
- (void)insertColumn:(NSInteger)column;
- (void)insertColumn:(NSInteger)column withCells:(NSArray<NSCell *> *)newCells;
- (void)removeColumn:(NSInteger)col;
- (nullable __kindof NSCell *)cellWithTag:(NSInteger)anInt;
@property (nullable) SEL doubleAction;
@property BOOL autosizesCells;
- (void)sizeToCells;
- (void)setValidateSize:(BOOL)flag;
- (void)drawCellAtRow:(NSInteger)row column:(NSInteger)col;
- (void)highlightCell:(BOOL)flag atRow:(NSInteger)row column:(NSInteger)col;

@property (getter=isAutoscroll) BOOL autoscroll;
- (void)scrollCellToVisibleAtRow:(NSInteger)row column:(NSInteger)col;
@property (readonly) NSInteger mouseDownFlags;
- (void)mouseDown:(NSEvent *)theEvent;
- (BOOL)performKeyEquivalent:(NSEvent *)theEvent;
- (BOOL)sendAction;
- (void)sendDoubleAction;
@property (nullable, assign) id<NSMatrixDelegate> delegate;
- (BOOL)textShouldBeginEditing:(NSText *)textObject;
- (BOOL)textShouldEndEditing:(NSText *)textObject;
- (void)textDidBeginEditing:(NSNotification *)notification;
- (void)textDidEndEditing:(NSNotification *)notification;
- (void)textDidChange:(NSNotification *)notification;
- (void)selectText:(nullable id)sender;
- (nullable __kindof NSCell *)selectTextAtRow:(NSInteger)row column:(NSInteger)col;
- (BOOL)acceptsFirstMouse:(nullable NSEvent *)theEvent;
- (void)resetCursorRects;
- (void)setToolTip:(nullable NSString *)toolTipString forCell:(NSCell *)cell;
- (nullable NSString *)toolTipForCell:(NSCell *)cell;

/* Determine whether the receiver autorecalculates its cellSize. The default is NO. If set to YES, then the receiver will adjust its cellSize to accommodate its largest cell. Changing the cellSize does not directly affect the frame of the receiver; however it does affect the intrinsic content size, which may cause the receiver to resize under autolayout. 
 
   The default is NO. When using autolayout, you typically want this to be set to YES.
 */
@property BOOL autorecalculatesCellSize NS_AVAILABLE_MAC(10_8);

@end

@interface NSMatrix(NSKeyboardUI)
@property BOOL tabKeyTraversesCells;
@property (nullable, assign) __kindof NSCell *keyCell;
@end

@protocol NSMatrixDelegate <NSControlTextEditingDelegate> @end

NS_ASSUME_NONNULL_END

