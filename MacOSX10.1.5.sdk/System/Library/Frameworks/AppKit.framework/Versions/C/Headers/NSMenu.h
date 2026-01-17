/*
        NSMenu.h
        Application Kit
        Copyright (c) 1996-2001, Apple Computer, Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSMenuItem.h>

@class NSEvent, NSView;
@class NSMenu;
@class NSMutableArray, NSArray;

@interface NSMenu : NSObject <NSCopying, NSCoding> {
    /*All instance variables are private*/
    @private
    NSMenu *_supermenu;
    NSString *_title;
    void *_itemArray;
    id _menuImpl;
    struct __mFlags {
        unsigned int noAutoenable:1;
        unsigned int menuChangedMessagesDisabled:1;
        unsigned int needsMenuChangedMessage:1;
        unsigned int suppressAutoenable:1;
        unsigned int disabled:1;
        unsigned int ownedByPopUp:1;
        unsigned int RESERVED:26;
    } _mFlags;
    NSString *_name;
}

+ (void)setMenuZone:(NSZone *)aZone;
+ (NSZone *)menuZone;

+ (void)popUpContextMenu:(NSMenu*)menu withEvent:(NSEvent*)event forView:(NSView*)view;

- (id)initWithTitle:(NSString *)aTitle;

- (void)setTitle:(NSString *)aString;
- (NSString *)title;

- (void)setSupermenu:(NSMenu *)supermenu;
- (NSMenu *)supermenu;
    // Never call the set method directly it is there only for subclassers.

- (void)insertItem:(id <NSMenuItem>)newItem atIndex:(int)index;
- (void)addItem:(id <NSMenuItem>)newItem;
- (id <NSMenuItem>)insertItemWithTitle:(NSString *)aString action:(SEL)aSelector keyEquivalent:(NSString *)charCode atIndex:(int)index;
- (id <NSMenuItem>)addItemWithTitle:(NSString *)aString action:(SEL)aSelector keyEquivalent:(NSString *)charCode;
- (void)removeItemAtIndex:(int)index;
- (void)removeItem:(id <NSMenuItem>)item;
- (void)setSubmenu:(NSMenu *)aMenu forItem:(id <NSMenuItem>)anItem;

- (NSArray *)itemArray;
- (int)numberOfItems;

- (int)indexOfItem:(id <NSMenuItem>)index;
- (int)indexOfItemWithTitle:(NSString *)aTitle;
- (int)indexOfItemWithTag:(int)aTag;
- (int)indexOfItemWithRepresentedObject:(id)object;
- (int)indexOfItemWithSubmenu:(NSMenu *)submenu;
- (int)indexOfItemWithTarget:(id)target andAction:(SEL)actionSelector;

- (id <NSMenuItem>)itemAtIndex:(int)index;
- (id <NSMenuItem>)itemWithTitle:(NSString *)aTitle;
- (id <NSMenuItem>)itemWithTag:(int)tag;

- (void)setAutoenablesItems:(BOOL)flag;
- (BOOL)autoenablesItems;

- (BOOL)performKeyEquivalent:(NSEvent *)theEvent;
- (void)update;

- (void)setMenuChangedMessagesEnabled:(BOOL)flag;
- (BOOL)menuChangedMessagesEnabled;

- (void)itemChanged:(id <NSMenuItem>)item;

- (void)helpRequested:(NSEvent *)eventPtr;

- (void)setMenuRepresentation:(id)menuRep;
- (id)menuRepresentation;

- (void)setContextMenuRepresentation:(id)menuRep;
- (id)contextMenuRepresentation;

- (void)setTearOffMenuRepresentation:(id)menuRep;
- (id)tearOffMenuRepresentation;

- (BOOL)isTornOff;

// These methods are platform specific.  They really make little sense on Windows.  Their use is discouraged.
- (NSMenu *)attachedMenu;
- (BOOL)isAttached;
- (void)sizeToFit;
- (NSPoint)locationForSubmenu:(NSMenu *)aSubmenu;

- (void)performActionForItemAtIndex:(int)index;

@end

@interface NSMenu(NSSubmenuAction)
- (void)submenuAction:(id)sender;
@end

@interface NSObject(NSMenuValidation)
- (BOOL)validateMenuItem:(id <NSMenuItem>)menuItem;
@end

APPKIT_EXTERN NSString *NSMenuWillSendActionNotification;
APPKIT_EXTERN NSString *NSMenuDidSendActionNotification;

APPKIT_EXTERN NSString *NSMenuDidAddItemNotification;
APPKIT_EXTERN NSString *NSMenuDidRemoveItemNotification;
APPKIT_EXTERN NSString *NSMenuDidChangeItemNotification;
    // All three of these have a user info key NSMenuItemIndex with a NSNumber value.
