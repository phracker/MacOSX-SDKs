/*
        NSTabView.h
        Application Kit
        Copyright (c) 2000-2017, Apple Inc.
        All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <AppKit/NSView.h>
#import <AppKit/NSCell.h>
#import <AppKit/NSLayoutConstraint.h>
#import <AppKit/NSApplication.h>

NS_ASSUME_NONNULL_BEGIN

@class NSFont, NSTabViewItem;
@protocol NSTabViewDelegate;

static const NSAppKitVersion NSAppKitVersionNumberWithDirectionalTabs = 631.0;

// Use tabPosition and tabViewBorderType instead
typedef NS_ENUM(NSUInteger, NSTabViewType) {
    NSTopTabsBezelBorder	= 0,			// the default
    NSLeftTabsBezelBorder	= 1,
    NSBottomTabsBezelBorder	= 2,
    NSRightTabsBezelBorder	= 3,
    NSNoTabsBezelBorder		= 4,
    NSNoTabsLineBorder		= 5,
    NSNoTabsNoBorder		= 6
};

typedef NS_ENUM(NSUInteger, NSTabPosition) {
    NSTabPositionNone                  = 0,
    NSTabPositionTop                   = 1,
    NSTabPositionLeft                  = 2,
    NSTabPositionBottom                = 3,
    NSTabPositionRight                 = 4
} NS_AVAILABLE_MAC(10_12);

typedef NS_ENUM(NSUInteger, NSTabViewBorderType) {
    NSTabViewBorderTypeNone            = 0,
    NSTabViewBorderTypeLine            = 1,
    NSTabViewBorderTypeBezel           = 2
} NS_AVAILABLE_MAC(10_12);

@interface NSTabView : NSView
{
@private
    	/* Persistent properties */
    
    id                           _tabViewItems;                 // array of NSTabViewItem
    NSTabViewItem	        *_selectedTabViewItem;		// nil only if _tabViewItems is empty
    NSFont		        *_font;				// font use to display the tab label
    struct __NSTabViewTypeFlags {
        unsigned int tabViewBorderType:3;
        unsigned int tabPosition:5;
        unsigned int reserved:24;
    } _typeFlags;
    BOOL		         _allowTruncatedLabels;
    __weak id<NSTabViewDelegate> _delegate;

    	/* Non-Persistent properties */

    BOOL		         _tabViewUnusedBOOL1 __unused;
    
    BOOL		         _drawsBackground;		// YES if we draw the background when borderless
    NSTabViewItem	        *_pressedTabViewItem;		// using during tracking
    NSInteger		         _endTabWidth;			// Width of the end tab. It depends on the font used.
    NSInteger		         _maxOverlap;			// Maximum tab overlap. Function of _enTabWidth
    CGFloat		         _tabHeight;			// Cache height of tabs
    NSTabViewItem	        *_tabViewItemWithKeyView;	// the tabViewItem with the keyView "outline"
    NSView 		        *_originalNextKeyView;		// Original nextKeyView of the tabView. Needed to restore the keyViewLoop.
#if __LP64__
    NSLayoutConstraint          *_tabViewMinimumSizeConstraint; // Width constraint for the tab view based on its minimum size
#endif
    
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
        unsigned int subviewsAddedForTabs:1;
        unsigned int allowsPropertyChange:1;
        unsigned int ownedByTabViewController:1;
        unsigned int reserved:19;
    } _flags;
    NSTabViewItem 	*_focusedTabViewItem;

    void		*_tabViewUnused2 __unused;
}

	/* Select */

- (void)selectTabViewItem:(nullable NSTabViewItem *)tabViewItem;
- (void)selectTabViewItemAtIndex:(NSInteger)index;				// May raise an NSRangeException
- (void)selectTabViewItemWithIdentifier:(id)identifier;                         // May raise an NSRangeException if identifier not found
- (void)takeSelectedTabViewItemFromSender:(nullable id)sender;			// May raise an NSRangeException

	/* Navigation */

- (void)selectFirstTabViewItem:(nullable id)sender;
- (void)selectLastTabViewItem:(nullable id)sender;
- (void)selectNextTabViewItem:(nullable id)sender;
- (void)selectPreviousTabViewItem:(nullable id)sender;

	/* Getters */

@property (nullable, readonly, strong) NSTabViewItem *selectedTabViewItem;	// return nil if none are selected
@property (strong) NSFont *font;						// returns font used for all tab labels.
@property NSTabViewType tabViewType;                                            // Use tabPosition and tabViewBorderType instead. Setting this will also set the tabPosition and tabViewBorderType. Setting tabPosition or tabViewBorderType will affect tabViewType
@property NSTabPosition tabPosition NS_AVAILABLE_MAC(10_12);
@property NSTabViewBorderType tabViewBorderType NS_AVAILABLE_MAC(10_12);        // This will only be respected if NSTabPosition is NSTabPositionNone.
@property (readonly, copy) NSArray<__kindof NSTabViewItem *> *tabViewItems;
@property BOOL allowsTruncatedLabels;
@property (readonly) NSSize minimumSize;					// returns the minimum size of the tab view
@property BOOL drawsBackground;  						// only relevant for borderless tab view type
@property NSControlTint controlTint;
@property NSControlSize controlSize;

	/* Add/Remove tabs */

- (void)addTabViewItem:(NSTabViewItem *)tabViewItem;				// Add tab at the end.
- (void)insertTabViewItem:(NSTabViewItem *)tabViewItem atIndex:(NSInteger)index;// May raise an NSRangeException
- (void)removeTabViewItem:(NSTabViewItem *)tabViewItem;				// tabViewItem must be an existing tabViewItem

	/* Delegate */

@property (nullable, weak) id<NSTabViewDelegate> delegate;

	/* Hit testing */

- (nullable NSTabViewItem *)tabViewItemAtPoint:(NSPoint)point;			// point in local coordinates. returns nil if none.

	/* Geometry */

@property (readonly) NSRect contentRect;					// Return the rect available for a "page".

	/* Query */

@property (readonly) NSInteger numberOfTabViewItems;
- (NSInteger)indexOfTabViewItem:(NSTabViewItem *)tabViewItem;			// NSNotFound if not found
- (NSTabViewItem *)tabViewItemAtIndex:(NSInteger)index;                         // May raise an NSRangeException	
- (NSInteger)indexOfTabViewItemWithIdentifier:(id)identifier;			// NSNotFound if not found

@end

//================================================================================
//	NSTabViewDelegate protocol
//================================================================================

@protocol NSTabViewDelegate <NSObject>
@optional
- (BOOL)tabView:(NSTabView *)tabView shouldSelectTabViewItem:(nullable NSTabViewItem *)tabViewItem;
- (void)tabView:(NSTabView *)tabView willSelectTabViewItem:(nullable NSTabViewItem *)tabViewItem;
- (void)tabView:(NSTabView *)tabView didSelectTabViewItem:(nullable NSTabViewItem *)tabViewItem;
- (void)tabViewDidChangeNumberOfTabViewItems:(NSTabView *)tabView;
@end

NS_ASSUME_NONNULL_END
