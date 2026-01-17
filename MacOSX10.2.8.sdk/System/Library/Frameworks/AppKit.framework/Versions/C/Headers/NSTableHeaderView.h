/*
        NSTableHeaderView.h
        Application Kit
        Copyright (c) 1995-2001, Apple Computer, Inc.
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
    int				_resizedColumn;
    int				_draggedColumn;
    int				_mayDragColumn;
    NSImage			*_headerDragImage;
    float			_draggedDistance;
    BOOL			_isColumnResizing;
    BOOL			_reserved2;
    BOOL			_reserved3;
    BOOL			_reserved4;
    BOOL			_drawingLastColumn;
    id				_reserved;
}

- (void)setTableView:(NSTableView *)tableView;
- (NSTableView *)tableView;
- (int)draggedColumn;
- (float)draggedDistance;
- (int)resizedColumn;
- (NSRect)headerRectOfColumn:(int)column;
- (int)columnAtPoint:(NSPoint)point;

@end
