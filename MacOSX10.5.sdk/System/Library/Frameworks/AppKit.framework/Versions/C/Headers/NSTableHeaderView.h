/*
        NSTableHeaderView.h
        Application Kit
        Copyright (c) 1995-2007, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSView.h>

@class NSTableView;
@class NSColor;
@class NSImage;
@class NSCursor;

@interface NSTableHeaderView : NSView
{
    /*All instance variables are private*/
    NSTableView			*_tableView;
    NSInteger			_resizedColumn;
    NSInteger			_draggedColumn;
    NSInteger			_pressedColumn;
    NSImage			*_headerDragImage;
    CGFloat			_draggedDistance;
    BOOL			_isColumnResizing;
    BOOL			_showHandCursorFired;
    BOOL			_toolTipRectsDirty;
    BOOL			_reserved4;
    BOOL			_skipDrawingSeparator;
    id				_reserved;
}

- (void)setTableView:(NSTableView *)tableView;
- (NSTableView *)tableView;
- (NSInteger)draggedColumn;
- (CGFloat)draggedDistance;
- (NSInteger)resizedColumn;
- (NSRect)headerRectOfColumn:(NSInteger)column;
- (NSInteger)columnAtPoint:(NSPoint)point;

@end
