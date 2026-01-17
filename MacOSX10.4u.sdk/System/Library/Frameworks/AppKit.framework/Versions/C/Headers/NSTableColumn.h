/*
        NSTableColumn.h
        Application Kit
        Copyright (c) 1995-2004, Apple Computer, Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSTableView;
@class NSCell;
@class NSImage;
@class NSSortDescriptor;

@interface NSTableColumn : NSObject <NSCoding>
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
        unsigned int	oldIsResizable:1;
        unsigned int	isEditable:1;
        unsigned int	resizedPostingDisableCount:8;
        unsigned int    canUseReorderResizeImageCache:1;
        unsigned int    userResizingAllowed:1;
        unsigned int    autoResizingAllowed:1;
        unsigned int	RESERVED:19;
    } _cFlags;
    id          _tcAuxiliaryStorage;
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

- (void)setHeaderCell:(NSCell *)cell; // Manage the cell used to draw the header for this column
- (id)headerCell;

/* Manage the cell used to draw the actual values in the column.  NSTableView will always call -dataCellForRow:.  By default, -dataCellForRow: just calls -dataCell.  Subclassers can override if they need to potentially use different cells for different rows.  Subclassers should be prepared to be called with -dataCellForRow:-1 in cases where no actual row is involved but the table view needs to get some generic cell info.
 */
- (void)setDataCell:(NSCell *)cell;
- (id)dataCell;
- (id)dataCellForRow:(int)row;
    
- (void)setEditable:(BOOL)flag;
- (BOOL)isEditable;
- (void)sizeToFit;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

/* A column is considered sortable if it has a sortDescriptorPrototype.  This prototype defines several things about the columns sorting.  The prototype's ascending value defines the default sorting direction.  Its key defines an arbitrary attribute which helps clients identify what to sort, while the selector defines how to sort.  Note that, it is not required that the key be the same as the identifier.  However, the key must be unique from the key used by other columns.  The sortDescriptor is archived.
 */
- (void)setSortDescriptorPrototype:(NSSortDescriptor *)sortDescriptor;
- (NSSortDescriptor *)sortDescriptorPrototype;

#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* The resizing mask controls the resizability of a table column.  Compatability Note: This method replaces setResizable.
*/ 
- (void)setResizingMask:(unsigned)resizingMask;
- (unsigned)resizingMask;

enum {
    NSTableColumnNoResizing = 0, // Disallow any kind of resizing.
    NSTableColumnAutoresizingMask = ( 1 << 0 ),     // This column can be resized as the table is resized.
    NSTableColumnUserResizingMask = ( 1 << 1 ),     // The user can resize this column manually.
};
#endif

/*
 * Deprecated Methods
 */

// Deprecated in Mac OS 10.4.  If flag is YES, calls setResizingMask:(NSTableColumnUserResizingMask | NSTableColumnAutoresizingMask).  If flag is NO, calls setResizingMask:(NSTableColumnNoResizing).
- (void)setResizable:(BOOL)flag;
- (BOOL)isResizable;

@end
