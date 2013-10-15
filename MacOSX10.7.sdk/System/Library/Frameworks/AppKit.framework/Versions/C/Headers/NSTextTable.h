/*
        NSTextTable.h
        Copyright (c) 2004-2011, Apple Inc.
        All rights reserved.

        Classes to represent text tables and other text blocks.
        NSTextBlock represents a single block of text.
        NSTextTableBlock is a subclass used to represent a block that is a cell in a table.
        NSTextTable represents a whole table.
*/

#import <AppKit/NSText.h>

@class NSTextTable;
@class NSLayoutManager;
@class NSTextContainer;


/* Values for NSTextBlockValueType */
enum {
    NSTextBlockAbsoluteValueType    = 0,    // Absolute value in points
    NSTextBlockPercentageValueType  = 1     // Percentage value (out of 100)
};
typedef NSUInteger NSTextBlockValueType;

/* Values for NSTextBlockDimension */
enum {
    NSTextBlockWidth            = 0,
    NSTextBlockMinimumWidth     = 1,
    NSTextBlockMaximumWidth     = 2,
    NSTextBlockHeight           = 4,
    NSTextBlockMinimumHeight    = 5,
    NSTextBlockMaximumHeight    = 6
};
typedef NSUInteger NSTextBlockDimension;

/* Values for NSTextBlockLayer */
enum {
    NSTextBlockPadding  = -1,
    NSTextBlockBorder   =  0,
    NSTextBlockMargin   =  1
};
typedef NSInteger NSTextBlockLayer;

/* Values for NSTextBlockVerticalAlignment */
enum {
    NSTextBlockTopAlignment         = 0,
    NSTextBlockMiddleAlignment      = 1,
    NSTextBlockBottomAlignment      = 2,
    NSTextBlockBaselineAlignment    = 3
};
typedef NSUInteger NSTextBlockVerticalAlignment;

/* Values for NSTextTableLayoutAlgorithm */
enum {
    NSTextTableAutomaticLayoutAlgorithm = 0,
    NSTextTableFixedLayoutAlgorithm     = 1
};
typedef NSUInteger NSTextTableLayoutAlgorithm;

/* NSTextBlock is the basic object for text block layout, and the superclass of the other classes. */
@interface NSTextBlock : NSObject <NSCoding, NSCopying> {
    /*All instance variables are private*/
    void *_propVals;
    NSUInteger _propMask;
    NSUInteger _typeMask;
    id _primParamVal;
    id _otherParamVals;
    void *_blockPrimary;
    void *_blockSecondary;
}

- (id)init;     // Designated initializer

/* Content size */
- (void)setValue:(CGFloat)val type:(NSTextBlockValueType)type forDimension:(NSTextBlockDimension)dimension;
- (CGFloat)valueForDimension:(NSTextBlockDimension)dimension;
- (NSTextBlockValueType)valueTypeForDimension:(NSTextBlockDimension)dimension;

/* Convenience methods for content width in particular, using the above methods with dimension == NSTextBlockWidth */
- (void)setContentWidth:(CGFloat)val type:(NSTextBlockValueType)type;
- (CGFloat)contentWidth;
- (NSTextBlockValueType)contentWidthValueType;

/* Margin, border, and padding */
- (void)setWidth:(CGFloat)val type:(NSTextBlockValueType)type forLayer:(NSTextBlockLayer)layer edge:(NSRectEdge)edge;
- (void)setWidth:(CGFloat)val type:(NSTextBlockValueType)type forLayer:(NSTextBlockLayer)layer;     // Convenience method sets all edges at once
- (CGFloat)widthForLayer:(NSTextBlockLayer)layer edge:(NSRectEdge)edge;
- (NSTextBlockValueType)widthValueTypeForLayer:(NSTextBlockLayer)layer edge:(NSRectEdge)edge;

/* Alignment */
- (void)setVerticalAlignment:(NSTextBlockVerticalAlignment)alignment;
- (NSTextBlockVerticalAlignment)verticalAlignment;

/* Colors */
- (void)setBackgroundColor:(NSColor *)color;
- (NSColor *)backgroundColor;
- (void)setBorderColor:(NSColor *)color forEdge:(NSRectEdge)edge;
- (void)setBorderColor:(NSColor *)color;        // Convenience method sets all edges at once
- (NSColor *)borderColorForEdge:(NSRectEdge)edge;

/* These methods will be called during layout to determine the size and position of the block.  The first will be called before the block is laid out to determine the rect within which glyphs should be laid.  The second will be called after the block is laid out to determine the rect the block occupies with borders and margins. */
- (NSRect)rectForLayoutAtPoint:(NSPoint)startingPoint inRect:(NSRect)rect textContainer:(NSTextContainer *)textContainer characterRange:(NSRange)charRange;
- (NSRect)boundsRectForContentRect:(NSRect)contentRect inRect:(NSRect)rect textContainer:(NSTextContainer *)textContainer characterRange:(NSRange)charRange;

/* This method will be called during drawing to draw any colors and other decorations before the text is drawn. */
- (void)drawBackgroundWithFrame:(NSRect)frameRect inView:(NSView *)controlView characterRange:(NSRange)charRange layoutManager:(NSLayoutManager *)layoutManager;

@end

/* NSTextTableBlock is a subclass of NSTextBlock used for a block that appears as a cell in a text table. */
@interface NSTextTableBlock : NSTextBlock {
    NSTextTable *_table;
    NSInteger _rowNum;
    NSInteger _colNum;
    NSInteger _rowSpan;
    NSInteger _colSpan;
    void *_tableBlockPrimary;
    void *_tableBlockSecondary;
}

- (id)initWithTable:(NSTextTable *)table startingRow:(NSInteger)row rowSpan:(NSInteger)rowSpan startingColumn:(NSInteger)col columnSpan:(NSInteger)colSpan;     // Designated initializer

/* These methods determine the block's role in its enclosing table. */
- (NSTextTable *)table;
- (NSInteger)startingRow;
- (NSInteger)rowSpan;
- (NSInteger)startingColumn;
- (NSInteger)columnSpan;

@end

/* NSTextTable represents a table as a whole. */
@interface NSTextTable : NSTextBlock {
    NSUInteger _numCols;
    NSUInteger _tableFlags;
    id _lcache;
    void *_tablePrimary;
    void *_tableSecondary;
}

/* These methods control the basic parameters of the table. */
- (NSUInteger)numberOfColumns;
- (void)setNumberOfColumns:(NSUInteger)numCols;
- (NSTextTableLayoutAlgorithm)layoutAlgorithm;
- (void)setLayoutAlgorithm:(NSTextTableLayoutAlgorithm)algorithm;
- (BOOL)collapsesBorders;
- (void)setCollapsesBorders:(BOOL)flag;
- (BOOL)hidesEmptyCells;
- (void)setHidesEmptyCells:(BOOL)flag;

/* An NSTextTableBlock delegates its layout and drawing operations to its enclosing table, using the following NSTextTable methods. */
- (NSRect)rectForBlock:(NSTextTableBlock *)block layoutAtPoint:(NSPoint)startingPoint inRect:(NSRect)rect textContainer:(NSTextContainer *)textContainer characterRange:(NSRange)charRange;
- (NSRect)boundsRectForBlock:(NSTextTableBlock *)block contentRect:(NSRect)contentRect inRect:(NSRect)rect textContainer:(NSTextContainer *)textContainer characterRange:(NSRange)charRange;
- (void)drawBackgroundForBlock:(NSTextTableBlock *)block withFrame:(NSRect)frameRect inView:(NSView *)controlView characterRange:(NSRange)charRange layoutManager:(NSLayoutManager *)layoutManager;

@end

