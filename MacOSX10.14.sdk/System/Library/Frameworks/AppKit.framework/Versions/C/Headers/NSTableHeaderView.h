/*
    NSTableHeaderView.h
    Application Kit
    Copyright (c) 1995-2018, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSView.h>

NS_ASSUME_NONNULL_BEGIN

@class NSTableView;
@class NSColor;
@class NSImage;
@class NSCursor;

@interface NSTableHeaderView : NSView <NSViewToolTipOwner> {
@protected
    /* All instance variables are private */ 
    __weak NSTableView *_tableView APPKIT_IVAR;
    NSInteger _resizedColumn APPKIT_IVAR;
    NSInteger _draggedColumn APPKIT_IVAR;
    NSInteger _pressedColumn APPKIT_IVAR;
    NSImage *_headerDragImage APPKIT_IVAR;
    CGFloat _draggedDistance APPKIT_IVAR;
    unsigned int _isColumnResizing:1 APPKIT_IVAR;
    unsigned int _showHandCursorFired:1 APPKIT_IVAR;
    unsigned int _toolTipRectsDirty:1 APPKIT_IVAR;
    unsigned int _alignTitleWithDataCell:1 APPKIT_IVAR;
    unsigned int _nextColumnAfterDrawnOneIsSelected:1 APPKIT_IVAR;
    unsigned int _wantsTranslucency:1 APPKIT_IVAR;
    unsigned int _addedBlurToClipView:1 APPKIT_IVAR;
    unsigned int _usedNewHeight:1 APPKIT_IVAR;
@private
    unsigned int _drawsBackground:1 APPKIT_IVAR;
@protected
    unsigned int _reserved:23 APPKIT_IVAR;
    BOOL _skipDrawingSeparator APPKIT_IVAR;
    id _viewDataX APPKIT_IVAR;
}

@property (nullable, weak) NSTableView *tableView;

// Returns -1 if there is no column being dragged
@property (readonly) NSInteger draggedColumn;
@property (readonly) CGFloat draggedDistance;

@property (readonly) NSInteger resizedColumn;
- (NSRect)headerRectOfColumn:(NSInteger)column;
- (NSInteger)columnAtPoint:(NSPoint)point;

@end

NS_ASSUME_NONNULL_END
