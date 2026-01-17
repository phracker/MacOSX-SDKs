/*
    NSTableHeaderView.h
    Application Kit
    Copyright (c) 1995-2015, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSView.h>

NS_ASSUME_NONNULL_BEGIN

@class NSTableView;
@class NSColor;
@class NSImage;
@class NSCursor;

@interface NSTableHeaderView : NSView {
    /* All instance variables are private */ 
    NSTableView	*_tableView;
    NSInteger _resizedColumn;
    NSInteger _draggedColumn;
    NSInteger _pressedColumn;
    NSImage *_headerDragImage;
    CGFloat _draggedDistance;
    unsigned int _isColumnResizing:1;
    unsigned int _showHandCursorFired:1;
    unsigned int _toolTipRectsDirty:1;
    unsigned int _alignTitleWithDataCell:1;
    unsigned int _nextColumnAfterDrawnOneIsSelected:1;
    unsigned int _wantsTranslucency:1;
    unsigned int _addedBlurToClipView:1;
    unsigned int _usedNewHeight:1;
    unsigned int _reserved:24;
    BOOL _skipDrawingSeparator;
    id _viewDataX;
}

@property (nullable, assign) NSTableView *tableView;

// Returns -1 if there is no column being dragged
@property (readonly) NSInteger draggedColumn;
@property (readonly) CGFloat draggedDistance;

@property (readonly) NSInteger resizedColumn;
- (NSRect)headerRectOfColumn:(NSInteger)column;
- (NSInteger)columnAtPoint:(NSPoint)point;

@end

NS_ASSUME_NONNULL_END
