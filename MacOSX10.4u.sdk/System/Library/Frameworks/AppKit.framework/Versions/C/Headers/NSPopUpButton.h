/*
        NSPopUpButton.h
        Application Kit
        Copyright (c) 1997-2005, Apple Computer, Inc.
        All rights reserved.
*/

#import <AppKit/NSButton.h>
#import <AppKit/NSMenuItemCell.h>
#import <AppKit/NSMenuItem.h>

@class NSMenu;

@interface NSPopUpButton : NSButton {
    /*All instance variables are private*/
    @private
    struct __pbFlags {
        unsigned int needsPullsDownFromTemplate:1;  // for decoding old nibs only!
        unsigned int RESERVED:31;
    } _pbFlags;
}

- (id)initWithFrame:(NSRect)buttonFrame pullsDown:(BOOL)flag;

// Overrides behavior of NSView.  This is the menu for the popup, not a context menu.  PopUpButtons do not have context menus.
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

@end

/* Notifications */
APPKIT_EXTERN NSString *NSPopUpButtonWillPopUpNotification;
