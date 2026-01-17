/*
        NSPopUpButton.h
        Application Kit
        Copyright (c) 1997-2007, Apple Inc.
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
#if __LP64__
    id _popupReserved;
#endif
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

@end

/* Notifications */
APPKIT_EXTERN NSString *NSPopUpButtonWillPopUpNotification;
