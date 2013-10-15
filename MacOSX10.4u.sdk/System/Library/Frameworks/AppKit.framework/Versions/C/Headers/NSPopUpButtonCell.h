/*
        NSPopUpButtonCell.h
        Application Kit
        Copyright (c) 1997-2005, Apple Computer, Inc.
        All rights reserved.
*/

#import <AppKit/NSMenuItemCell.h>
#import <AppKit/NSMenuItem.h>

@class NSMenu;

typedef enum {
    NSPopUpNoArrow = 0,
    NSPopUpArrowAtCenter = 1,
    NSPopUpArrowAtBottom = 2
} NSPopUpArrowPosition;

@interface NSPopUpButtonCell : NSMenuItemCell {
    /*All instance variables are private*/
    @private
    NSMenu *_menu;
    int _selectedIndex;
    struct __pbcFlags {
        unsigned int pullsDown:1;
        unsigned int preferredEdge:3;
        unsigned int menuIsAttached:1;
        unsigned int usesItemFromMenu:1;
        unsigned int altersStateOfSelectedItem:1;
        unsigned int decoding:1;
        unsigned int arrowPosition:2;
        unsigned int ignoreMenuLayout:1;
        unsigned int drawing:1;
        unsigned int RESERVED:20;
    } _pbcFlags;
}

- (id)initTextCell:(NSString *)stringValue pullsDown:(BOOL)pullDown;

// Overrides behavior of NSCell.  This is the menu for the popup, not a context menu.  PopUpButtonCells do not have context menus.
- (void)setMenu:(NSMenu *)menu;
- (NSMenu *)menu;

// Behavior settings
- (void)setPullsDown:(BOOL)flag;
- (BOOL)pullsDown;
    
- (void)setAutoenablesItems:(BOOL)flag;
- (BOOL)autoenablesItems;

- (void)setPreferredEdge:(NSRectEdge)edge;
- (NSRectEdge)preferredEdge;
    // The preferred edge is used for pull down menus and for popups under severe screen position restrictions.  It indicates what edge of the cell the menu should pop out from.

- (void)setUsesItemFromMenu:(BOOL)flag;
- (BOOL)usesItemFromMenu;
    // If YES (the default) the popup button will display an item from the menu.  This will be the selected item for a popup or the first item for a pull-down.  If this is NO, then the menu item set with -setMenuItem: is always displayed.  This can be useful for a popup button that is an icon button that pops up a menu full of textual items, for example.

- (void)setAltersStateOfSelectedItem:(BOOL)flag;
- (BOOL)altersStateOfSelectedItem;
    // This only has an effect for popups (it is ignored for pulldowns).  If YES (the default) then the selected item gets its state set to NSOnState.  If NO the items in the menu are left alone.

// Adding and removing items
- (void)addItemWithTitle:(NSString *)title;
- (void)addItemsWithTitles:(NSArray *)itemTitles;
- (void)insertItemWithTitle:(NSString *)title atIndex:(int)index;

- (void)removeItemWithTitle:(NSString *)title;
- (void)removeItemAtIndex:(int)index;
- (void)removeAllItems;


// Accessing the items
- (NSArray *)itemArray;
- (int)numberOfItems;

- (int)indexOfItem:(id <NSMenuItem>)item;
- (int)indexOfItemWithTitle:(NSString *)title;
- (int)indexOfItemWithTag:(int)tag;
- (int)indexOfItemWithRepresentedObject:(id)obj;
- (int)indexOfItemWithTarget:(id)target andAction:(SEL)actionSelector;

- (id <NSMenuItem>)itemAtIndex:(int)index;
- (id <NSMenuItem>)itemWithTitle:(NSString *)title;
- (id <NSMenuItem>)lastItem;


// Dealing with selection
- (void)selectItem:(id <NSMenuItem>)item;
- (void)selectItemAtIndex:(int)index;
- (void)selectItemWithTitle:(NSString *)title;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (BOOL)selectItemWithTag:(int)tag;
#endif
- (void)setTitle:(NSString *)aString;

- (id <NSMenuItem>)selectedItem;
- (int)indexOfSelectedItem;
- (void)synchronizeTitleAndSelectedItem;


// Title conveniences
- (NSString *)itemTitleAtIndex:(int)index;
- (NSArray *)itemTitles;
- (NSString *)titleOfSelectedItem;

- (void)attachPopUpWithFrame:(NSRect)cellFrame inView:(NSView *)controlView;
- (void)dismissPopUp;
- (void)performClickWithFrame:(NSRect)frame inView:(NSView *)controlView;

// Arrow position for bezel style and borderless popups.
- (NSPopUpArrowPosition)arrowPosition;
- (void)setArrowPosition:(NSPopUpArrowPosition)position;

// Object values
- (id <NSCopying>)objectValue;
- (void)setObjectValue:(id <NSCopying>)obj;

@end


/* Notifications */
APPKIT_EXTERN NSString *NSPopUpButtonCellWillPopUpNotification;
