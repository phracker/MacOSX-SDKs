/*
        NSPopUpButtonCell.h
        Application Kit
        Copyright (c) 1997-2007, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSMenuItemCell.h>
#import <AppKit/NSMenuItem.h>

@class NSMenu;

enum {
    NSPopUpNoArrow = 0,
    NSPopUpArrowAtCenter = 1,
    NSPopUpArrowAtBottom = 2
};
typedef NSUInteger NSPopUpArrowPosition;

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
#if __LP64__
    id _popupReserved;
#endif
}

- (id)initTextCell:(NSString *)stringValue pullsDown:(BOOL)pullDown;

// Overrides behavior of NSCell.  This is the menu for the popup, not a context menu.  PopUpButtonCells do not have context menus.
- (void)setMenu:(NSMenu *)menu;
- (NSMenu *)menu;

// Behavior settings
// If usesItemFromMenu is true, then pull down popup buttons always show the first item in the menu.  That menu item is hidden via [menuItem setHidden:YES]; if you wish to make it visible you can unhide it with setHidden:NO
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
- (void)insertItemWithTitle:(NSString *)title atIndex:(NSInteger)index;

- (void)removeItemWithTitle:(NSString *)title;
- (void)removeItemAtIndex:(NSInteger)index;
- (void)removeAllItems;


// Accessing the items
- (NSArray *)itemArray;
- (NSInteger)numberOfItems;

- (NSInteger)indexOfItem:(NSMenuItem *)item;
- (NSInteger)indexOfItemWithTitle:(NSString *)title;
- (NSInteger)indexOfItemWithTag:(NSInteger)tag;
- (NSInteger)indexOfItemWithRepresentedObject:(id)obj;
- (NSInteger)indexOfItemWithTarget:(id)target andAction:(SEL)actionSelector;

- (NSMenuItem *)itemAtIndex:(NSInteger)index;
- (NSMenuItem *)itemWithTitle:(NSString *)title;
- (NSMenuItem *)lastItem;


// Dealing with selection
- (void)selectItem:(NSMenuItem *)item;
- (void)selectItemAtIndex:(NSInteger)index;
- (void)selectItemWithTitle:(NSString *)title;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (BOOL)selectItemWithTag:(NSInteger)tag;
#endif
- (void)setTitle:(NSString *)aString;

- (NSMenuItem *)selectedItem;
- (NSInteger)indexOfSelectedItem;
- (void)synchronizeTitleAndSelectedItem;


// Title conveniences
- (NSString *)itemTitleAtIndex:(NSInteger)index;
- (NSArray *)itemTitles;
- (NSString *)titleOfSelectedItem;

- (void)attachPopUpWithFrame:(NSRect)cellFrame inView:(NSView *)controlView;
- (void)dismissPopUp;
- (void)performClickWithFrame:(NSRect)frame inView:(NSView *)controlView;

// Arrow position for bezel style and borderless popups.
- (NSPopUpArrowPosition)arrowPosition;
- (void)setArrowPosition:(NSPopUpArrowPosition)position;

// Object values
- (id)objectValue;
- (void)setObjectValue:(id)obj;

@end


/* Notifications */
APPKIT_EXTERN NSString *NSPopUpButtonCellWillPopUpNotification;
