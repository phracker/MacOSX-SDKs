/*
        NSTableColumn.h
        Application Kit
        Copyright (c) 1995-2001, Apple Computer, Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSTableView;
@class NSCell;
@class NSImage;

@interface NSTableColumn : NSObject
{
    /*All instance variables are private*/
    id		_identifier;
    float	_width;
    float	_minWidth;
    float	_maxWidth;
    NSTableView *_tableView;
    NSCell	*_headerCell;
    NSCell	*_dataCell;
    struct __colFlags {
        unsigned int	isResizable:1;
        unsigned int	isEditable:1;
        unsigned int	resizedPostingDisableCount:8;
        unsigned int    canUseReorderResizeImageCache:1;
        unsigned int	RESERVED:21;
    } _cFlags;
    NSImage 	*_reorderResizeImageCache;
}

- (id)initWithIdentifier:(id)identifier;

- (void)setIdentifier:(id)identifier;
- (id)identifier;
- (void)setTableView:(NSTableView *)tableView;
- (NSTableView *)tableView;
- (void)setWidth:(float)width;
- (float)width;
- (void)setMinWidth:(float)minWidth;
- (float)minWidth;
- (void)setMaxWidth:(float)maxWidth;
- (float)maxWidth;

- (void)setHeaderCell:(NSCell *)cell;
- (id)headerCell;
    // Manage the cell used to draw the header view for this column

- (void)setDataCell:(NSCell *)cell;
- (id)dataCell;
- (id)dataCellForRow:(int)row;
    // Manage the cell used to draw the actual values in the column.  NSTableView will always call -dataCellForRow:.  By default, -dataCellForRow: just calls -dataCell.  Subclassers can override if they need to potentially use different cells for different rows.  Subclassers should be prepared to be called with -dataCellForRow:-1 in cases where no actual row is involved but the table view needs to get some generic cell info.
    
- (void)setResizable:(BOOL)flag;
- (BOOL)isResizable;
- (void)setEditable:(BOOL)flag;
- (BOOL)isEditable;
- (void)sizeToFit;

@end
