/*
        NSTabView.h
        Application Kit
        Copyright (c) 2000-2005, Apple Computer, Inc.
        All rights reserved.
*/

#import <AppKit/NSView.h>
#import <AppKit/NSCell.h>

@class NSArray, NSFont, NSTabViewItem;

#define NSAppKitVersionNumberWithDirectionalTabs 631.0

typedef enum _NSTabViewType {
    NSTopTabsBezelBorder	= 0,			// the default
    NSLeftTabsBezelBorder	= 1,
    NSBottomTabsBezelBorder	= 2,
    NSRightTabsBezelBorder	= 3,
    NSNoTabsBezelBorder		= 4,
    NSNoTabsLineBorder		= 5,
    NSNoTabsNoBorder		= 6
} NSTabViewType;

@interface NSTabView : NSView
{
    @private
    	
    	/* Persistent properties */
    
    id	_tabViewItems;                          	// array of NSTabViewItem
    NSTabViewItem	*_selectedTabViewItem;		// nil only if _tabViewItems is empty
    NSFont		*_font;				// font use to display the tab label
    NSTabViewType	_tabViewType;
    BOOL		_allowTruncatedLabels;
    id                  _delegate;

    	/* Non-Persistent properties */

    BOOL		_tabViewUnusedBOOL1;
    
    BOOL		_drawsBackground;		// YES if we draw the background when borderless
    NSTabViewItem	*_pressedTabViewItem;		// using during tracking
    int			_endTabWidth;			// Width of the end tab. It depends on the font used.
    int			_maxOverlap;			// Maximum tab overlap. Function of _enTabWidth
    int			_tabHeight;			// Cache height of tabs
    NSTabViewItem	*_tabViewItemWithKeyView;	// the tabViewItem with the keyView "outline"
    NSView 		*_originalNextKeyView;		// Original nextKeyView of the tabView. Needed to restore the keyViewLoop.
    struct __NSTabViewDelegateRespondTo {
        unsigned int shouldSelectTabViewItem:1;
        unsigned int willSelectTabViewItem:1;
        unsigned int didSelectTabViewItem:1;
        unsigned int didChangeNumberOfTabViewItems:1;
        unsigned int reserved:28;
    } _delegateRespondTo;
    
    struct __NSTabViewFlags {
        unsigned int needsLayout:1;
        unsigned int controlTint:3;	// archived
        unsigned int controlSize:2;	// archived
        unsigned int wiringNibConnections:1;
        unsigned int wiringInteriorLastKeyView:1;
        unsigned int originalNextKeyViewChanged:1;
	unsigned int liveResizeSkippedResetToolTips:1;
        unsigned int reserved:22;
    } _flags;

    	/* Unused fields */
    
    NSTabViewItem 	*_focusedTabViewItem;			
    void		*_tabViewUnused2;
}

	/* Select */

- (void)selectTabViewItem:(NSTabViewItem *)tabViewItem;
- (void)selectTabViewItemAtIndex:(int)index;				// May raise an NSRangeException
- (void)selectTabViewItemWithIdentifier:(id)identifier;			// May raise an NSRangeException if identifier not found
- (void)takeSelectedTabViewItemFromSender:(id)sender;			// May raise an NSRangeException

	/* Navigation */

- (void)selectFirstTabViewItem:(id)sender;
- (void)selectLastTabViewItem:(id)sender;
- (void)selectNextTabViewItem:(id)sender;
- (void)selectPreviousTabViewItem:(id)sender;

	/* Getters */

- (NSTabViewItem *)selectedTabViewItem;					// return nil if none are selected
- (NSFont *)font;							// returns font used for all tab labels.
- (NSTabViewType)tabViewType;
- (NSArray *)tabViewItems;
- (BOOL)allowsTruncatedLabels;
- (NSSize)minimumSize;							// returns the minimum size of the tab view
- (BOOL)drawsBackground;  						// only relevant for borderless tab view type
- (NSControlTint)controlTint;
- (NSControlSize)controlSize;

	/* Setters */

- (void)setFont:(NSFont *)font;
- (void)setTabViewType:(NSTabViewType)tabViewType;
- (void)setAllowsTruncatedLabels:(BOOL)allowTruncatedLabels;
- (void)setDrawsBackground:(BOOL)flag;  					// only relevant for borderless tab view type
- (void)setControlTint:(NSControlTint)controlTint;
- (void)setControlSize:(NSControlSize)controlSize;

	/* Add/Remove tabs */

- (void)addTabViewItem:(NSTabViewItem *)tabViewItem;				// Add tab at the end.
- (void)insertTabViewItem:(NSTabViewItem *)tabViewItem atIndex:(int)index;	// May raise an NSRangeException
- (void)removeTabViewItem:(NSTabViewItem *)tabViewItem;				// tabViewItem must be an existing tabViewItem

	/* Delegate */

- (void)setDelegate:(id)anObject;
- (id)delegate;

	/* Hit testing */

- (NSTabViewItem *)tabViewItemAtPoint:(NSPoint)point;			// point in local coordinates. returns nil if none.

	/* Geometry */

- (NSRect)contentRect;							// Return the rect available for a "page". 

	/* Query */

- (int)numberOfTabViewItems;
- (int)indexOfTabViewItem:(NSTabViewItem *)tabViewItem;			// NSNotFound if not found
- (NSTabViewItem *)tabViewItemAtIndex:(int)index;			// May raise an NSRangeException	
- (int)indexOfTabViewItemWithIdentifier:(id)identifier;			// NSNotFound if not found

@end

//================================================================================
//	NSTabViewDelegate protocol
//================================================================================

@interface NSObject(NSTabViewDelegate)
- (BOOL)tabView:(NSTabView *)tabView shouldSelectTabViewItem:(NSTabViewItem *)tabViewItem;
- (void)tabView:(NSTabView *)tabView willSelectTabViewItem:(NSTabViewItem *)tabViewItem;
- (void)tabView:(NSTabView *)tabView didSelectTabViewItem:(NSTabViewItem *)tabViewItem;
- (void)tabViewDidChangeNumberOfTabViewItems:(NSTabView *)TabView;
@end
