/*
 NSMenu.h
 Application Kit
 Copyright (c) 1996-2015, Apple Inc.
 All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSMenuItem.h>

NS_ASSUME_NONNULL_BEGIN

@class NSEvent, NSView, NSFont;
@class NSMenu;
@protocol NSMenuDelegate;

@interface NSMenu : NSObject <NSCopying, NSCoding>
{
    /*All instance variables are private*/
    @private
    NSMenu *_supermenu;
    NSString *_title;
    id _itemArray;
    id _extra;
    struct __mFlags {
        unsigned int noAutoenable:1;
        unsigned int inMain:1;
        unsigned int internalPerformAction:1;
        unsigned int condenseSeparators:1;
        unsigned int disabled:1;
        unsigned int ownedByPopUp:1;
	unsigned int delegateNeedsUpdate:1;
	unsigned int delegateUpdateItem:1;
	unsigned int delegateHasKeyEquiv:1;
	unsigned int delegateHasAltKeyEquiv:1;
	unsigned int excludeMarkColumn:1;
	unsigned int isContextualMenu:1;
        unsigned int cmPluginMode:2;
        unsigned int invertedCMPluginTypes:2;
        unsigned int allowsDifferentSelection:1;
        unsigned int noTopPadding:1;
        unsigned int noBottomPadding:1;
	unsigned int hasNCStyle:1;
	unsigned int delegateIsUnsafeUnretained:1;
        unsigned int RESERVED:11;
    } _mFlags;
    NSString *_uiid;
}

/* Designated initializer.  If this menu is used as a submenu of an item in the application's main menu, then the title is what appears in the menu bar.  Otherwise, the title is ignored.  Do not pass nil (an exception will result), but you may pass an empty string.
 */
- (instancetype)initWithTitle:(NSString *)aTitle;

/* Set and get the menu's title.  The titles of the submenus of the application's main menu items appear in the menu bar. */
@property (copy) NSString *title;

/* Pops up the receiver as a context menu.  The menu is positioned such that the top left corner lies at the given event's location, interpreted in the coordinate system of the given view.  If this would cause the menu to scroll offscreen, it will be moved up to be onscreen.  The event must not be nil.
 
 If a font is specified, then it will be applied to the menu.  In 10.6, the setFont: API below should be preferred.
*/
 
+ (void)popUpContextMenu:(NSMenu*)menu withEvent:(NSEvent*)event forView:(NSView*)view;
+ (void)popUpContextMenu:(NSMenu*)menu withEvent:(NSEvent*)event forView:(NSView*)view withFont:(nullable NSFont*)font;

/* Pops up the receiver as a popup menu. The top left or right corner of the given item (which must be present in the receiver) is positioned at the given location in the given view, interpreted in the view's own coordinate system.  If item is nil, the menu is positioned such that the top left or right of the menu content frame is at the given location.  If view is nil, the location is interpreted in the screen coordinate system. This allows you to pop up a menu disconnected from any window.  The method returns YES if menu tracking ended because an item was selected, and NO if menu tracking was cancelled for any reason.
 
   This method determines whether to use the top left or right corner by calling userInterfaceLayoutDirection on the view or its cell (if implemented).  If not implemented, or if the view is nil, it inspects the userInterfaceLayoutDirection of the NSApplication.
*/
- (BOOL)popUpMenuPositioningItem:(nullable NSMenuItem *)item atLocation:(NSPoint)location inView:(nullable NSView *)view NS_AVAILABLE_MAC(10_6);

/* Determines whether the menu bar is visible for this application.  Users cannot access the menu bar unless it is visible.  It is visible by default. */
+ (void)setMenuBarVisible:(BOOL)visible;
+ (BOOL)menuBarVisible;

/* Getter: Returns the menu containing the item that has the receiver as a submenu, or nil if this menu is not the submenu of an item in a menu. 
   Setter: If a menu item has the receiver as a submenu, then this method will be called when the menu containing that item changes.  You should never call this, but you may override it to take some action when the supermenu changes. */
@property (nullable, assign) NSMenu *supermenu;

/* Inserts a menu item at the given index, which must be at least zero and no more than the receiver's item count.  If newItem is nil, this raises an exception. */
- (void)insertItem:(NSMenuItem *)newItem atIndex:(NSInteger)index;

/* Appends an item to the end of the menu.  A nil item will raise an exception. */
- (void)addItem:(NSMenuItem *)newItem;

/* Inserts a new menu item with the given title, action, and key equivalent, at the given index.  The index must be at least zero and no more than the receiver's item count.  The title and key equivalent must not be nil (pass the empty string to indicate no key equivalent). This returns the new item.
 */
- (nullable NSMenuItem *)insertItemWithTitle:(NSString *)aString action:(nullable SEL)aSelector keyEquivalent:(NSString *)charCode atIndex:(NSInteger)index;

/* Appends a new menu item with the given properties to the end of the menu. */
- (nullable NSMenuItem *)addItemWithTitle:(NSString *)aString action:(nullable SEL)aSelector keyEquivalent:(NSString *)charCode;

/* Removes the item at the given index, which must be at least zero and less than the number of items.  All subsequent items will shift down one index. */
- (void)removeItemAtIndex:(NSInteger)index;

/* Removes the item from the menu.  If the item is nil, or is not present in the receiver, an exception will be raised. */
- (void)removeItem:(NSMenuItem *)item;

/* Same as [anItem setSubmenu:aMenu].  anItem may not be nil. */
- (void)setSubmenu:(nullable NSMenu *)aMenu forItem:(NSMenuItem *)anItem;

/* Removes all items.  This is more efficient than removing items one by one.  This does not post NSMenuDidRemoveItemNotification, for efficiency.
*/
- (void)removeAllItems NS_AVAILABLE_MAC(10_6);

/* Returns an array containing the receiver's menu items. */
@property (readonly, copy) NSArray<NSMenuItem *> *itemArray;

/* Returns the number of menu items in the menu. */
@property (readonly) NSInteger numberOfItems;

/* Returns the item at the given index, which must be at least zero and less than the number of items. */
 - (nullable NSMenuItem *)itemAtIndex:(NSInteger)index;

/* Returns the index of the item in the menu, or -1 if the item is not present in the menu */
- (NSInteger)indexOfItem:(NSMenuItem *)item;

/* Returns the first item in the menu that matches the given property, or -1 if no item in the menu matches. */
- (NSInteger)indexOfItemWithTitle:(NSString *)aTitle;
- (NSInteger)indexOfItemWithTag:(NSInteger)aTag;
- (NSInteger)indexOfItemWithRepresentedObject:(id)object;
- (NSInteger)indexOfItemWithSubmenu:(nullable NSMenu *)submenu;
- (NSInteger)indexOfItemWithTarget:(nullable id)target andAction:(SEL)actionSelector;

/* Returns the first item in the menu with the given property, or nil if no item in the menu matches. */
- (nullable NSMenuItem *)itemWithTitle:(NSString *)aTitle;
- (nullable NSMenuItem *)itemWithTag:(NSInteger)tag;

/* Set and get whether the menu autoenables items.  If a menu autoenables items, then calls to -[NSMenuItem setEnabled:] are ignored, and the enabled state is computed via the NSMenuValidation informal protocol below.  Autoenabling is on by default. */
@property BOOL autoenablesItems;
 
 /* If the receiver is set to autoenable items, then this triggers autovalidation of all menu items according to the NSMenuValidation informal protocol; otherwise this does nothing.  It is normally not necessary to call this; it will be called for you at the right time. */
- (void)update;
  
/* Attempts to perform the given key equivalent.  If the event is a key down event that matches the key equivalent of a menu item in the receiver or, recursively, any menu item in a submenu of the receiver, then this triggers that menu item's action and returns YES.  Otherwise, this returns NO.
*/
- (BOOL)performKeyEquivalent:(NSEvent *)theEvent;

/* This method is called when a menu item's enabled state, submenu, title, attributed title, image, key equivalent, key equivalent modifier mask, alternate status, indent, tooltip, view, or visibility (via isHidden) changes.  This method posts NSMenuDidChangeItemNotification.  Future properties will likely not call this method when they change, because posting a notification when a property changes is rather expensive.
 */
- (void)itemChanged:(NSMenuItem *)item;

/* Triggers the action for the item at the given index in the receiver.  This is useful as both an override point and something you may call directly.  As an override point, this is called when the user chooses the item during normal menu tracking; subclassers can override it to take some different action.  If you call it directly, it triggers the action for that item.  In SnowLeopard and later, calling it directly will also highlight the menu (if present in the main menu) and trigger accessibility notifications, including VoiceOver speaking the title.
*/
- (void)performActionForItemAtIndex:(NSInteger)index;

/* Set and get the delegate for the menu.  See the NSMenuDelegate protocol for methods that the delegate may implement. */
@property (nullable, assign) id<NSMenuDelegate> delegate;

/* If called on the main menu, returns the height of the menu bar in pixels.  If called on any other menu, returns 0.
 */
@property (readonly) CGFloat menuBarHeight;

/* Dismisses the menu and ends all menu tracking */
- (void)cancelTracking NS_AVAILABLE_MAC(10_5);

/* Dismisses the menu immediately, without any fade or other effect, and ends all menu tracking */
- (void)cancelTrackingWithoutAnimation NS_AVAILABLE_MAC(10_6);

/* Returns the highlighted item in the menu, or nil if no item in the menu is highlighted */
@property (nullable, readonly, strong) NSMenuItem *highlightedItem NS_AVAILABLE_MAC(10_5);

/* Set the minimum width of the menu, in screen coordinates. The menu will prefer to not draw smaller than its minimum width, but may draw larger if it needs more space. The default value is 0.
*/
@property CGFloat minimumWidth NS_AVAILABLE_MAC(10_6);

/* Returns the size of the menu, in screen coordinates.  The menu may draw at a smaller size when shown, depending on its positioning and display configuration.
*/
@property (readonly) NSSize size NS_AVAILABLE_MAC(10_6);

/* Sets the font for the menu.  This also affects the font of all submenus that do not have their own font.
*/
@property (null_resettable, strong) NSFont *font NS_AVAILABLE_MAC(10_6);

/* Determines whether contextual menu plugins may be appended to the menu, if used as a context menu. The default is YES.
*/
@property BOOL allowsContextMenuPlugIns NS_AVAILABLE_MAC(10_6);

/* Determines whether the menu contains a column for the state image.  The default is YES. */
@property BOOL showsStateColumn NS_AVAILABLE_MAC(10_5);

/* Determines the layout direction for menu items in the menu. If no layout direction is explicitly set, the menu will default to the value of [NSApp userInterfaceLayoutDirection]. */
@property NSUserInterfaceLayoutDirection userInterfaceLayoutDirection NS_AVAILABLE_MAC(10_11);

@end

@interface NSMenu (NSSubmenuAction)
- (void)submenuAction:(nullable id)sender;
@end

@interface NSObject (NSMenuValidation)
- (BOOL)validateMenuItem:(NSMenuItem *)menuItem;
@end

@protocol NSMenuDelegate <NSObject>
@optional
- (void)menuNeedsUpdate:(NSMenu*)menu;

- (NSInteger)numberOfItemsInMenu:(NSMenu*)menu;
- (BOOL)menu:(NSMenu*)menu updateItem:(NSMenuItem*)item atIndex:(NSInteger)index shouldCancel:(BOOL)shouldCancel;
    // implement either the first one or the next two to populate the menu
- (BOOL)menuHasKeyEquivalent:(NSMenu*)menu forEvent:(NSEvent*)event target:(__nullable id* __nullable)target action:(__nullable SEL* __nullable)action;
    // bypasses populating the menu for checking for key equivalents. set target and action on return

/* indicates that the menu is being opened (displayed) or closed (hidden).  Do not modify the structure of the menu or the menu items from within these callbacks. */
- (void)menuWillOpen:(NSMenu *)menu NS_AVAILABLE_MAC(10_5);
- (void)menuDidClose:(NSMenu *)menu NS_AVAILABLE_MAC(10_5);

/* Indicates that menu is about to highlight item.  Only one item per menu can be highlighted at a time.  If item is nil, it means all items in the menu are about to be unhighlighted. */
- (void)menu:(NSMenu *)menu willHighlightItem:(nullable NSMenuItem *)item NS_AVAILABLE_MAC(10_5);


/* Given a menu that is about to be opened on the given screen, return a rect, in screen coordinates, within which the menu will be positioned.  If you return NSZeroRect, or if the delegate does not implement this method, the menu will be confined to the bounds appropriate for the given screen.  The returned rect may not be honored in all cases, such as if it would force the menu to be too small.
*/
- (NSRect)confinementRectForMenu:(NSMenu *)menu onScreen:(nullable NSScreen *)screen NS_AVAILABLE_MAC(10_6);

@end

/* The NSMenuProperties type is a bitmask used for specifying a set of menu or menu item properties, used in the following method.
 */
typedef NS_OPTIONS(NSUInteger, NSMenuProperties) {
    NSMenuPropertyItemTitle = 1 << 0,            // the menu item's title
    NSMenuPropertyItemAttributedTitle = 1 << 1,  // the menu item's attributed title
    NSMenuPropertyItemKeyEquivalent = 1 << 2,    // the menu item's key equivalent
    NSMenuPropertyItemImage = 1 << 3,            // the menu item's image
    NSMenuPropertyItemEnabled = 1 << 4,          // whether the menu item is enabled or disabled
    NSMenuPropertyItemAccessibilityDescription = 1 << 5 // the menu item's accessibility description
};

/* The following method may be called from delegate callbacks to determine which properties need to be updated and which may be skipped.  It is intended to allow more efficient updating of the menu in certain circumstances.  For example, if the NSMenuPropertyItemImage bit is zero, your delegate does not need to update the images of the menu items, because the images are not needed (for example, during key equivalent matching).  Calling this is optional: it is always acceptable to fully update the menu.
 
 This may be called from the menu delegate method -menuNeedsUpdate:.  Calling this at other times will raise an exception.
 */
@interface NSMenu (NSMenuPropertiesToUpdate)
@property (readonly) NSMenuProperties propertiesToUpdate NS_AVAILABLE_MAC(10_6);
@end

APPKIT_EXTERN NSString *NSMenuWillSendActionNotification;
APPKIT_EXTERN NSString *NSMenuDidSendActionNotification;

APPKIT_EXTERN NSString *NSMenuDidAddItemNotification;
APPKIT_EXTERN NSString *NSMenuDidRemoveItemNotification;
APPKIT_EXTERN NSString *NSMenuDidChangeItemNotification;
// All three of these have a user info key NSMenuItemIndex with a NSNumber value.

APPKIT_EXTERN NSString *NSMenuDidBeginTrackingNotification;
APPKIT_EXTERN NSString *NSMenuDidEndTrackingNotification;

// The remainder of this file contains deprecated methods
@interface NSMenu (NSDeprecated)

- (void)setMenuRepresentation:(null_unspecified id)menuRep NS_DEPRECATED_MAC(10_0, 10_2);
- (null_unspecified id)menuRepresentation NS_DEPRECATED_MAC(10_0, 10_2);

- (void)setContextMenuRepresentation:(null_unspecified id)menuRep NS_DEPRECATED_MAC(10_0, 10_2);
- (null_unspecified id)contextMenuRepresentation NS_DEPRECATED_MAC(10_0, 10_2);

- (void)setTearOffMenuRepresentation:(null_unspecified id)menuRep NS_DEPRECATED_MAC(10_0, 10_2);
- (null_unspecified id)tearOffMenuRepresentation NS_DEPRECATED_MAC(10_0, 10_2);

/* Returns the zone used to allocate NSMenu objects.  This is left in for compatibility and has returned NSDefaultMallocZone() since OS X 10.2.  It is not necessary to use this - menus can be allocated the usual way. */
+ (null_unspecified NSZone *)menuZone NS_DEPRECATED_MAC(10_0, 10_11);
+ (void)setMenuZone:(null_unspecified NSZone *)aZone NS_DEPRECATED_MAC(10_0, 10_2);

- (null_unspecified NSMenu *)attachedMenu NS_DEPRECATED_MAC(10_0, 10_2);
- (BOOL)isAttached NS_DEPRECATED_MAC(10_0, 10_2);
- (void)sizeToFit NS_DEPRECATED_MAC(10_0, 10_2);
- (NSPoint)locationForSubmenu:(null_unspecified NSMenu *)aSubmenu NS_DEPRECATED_MAC(10_0, 10_2);

/* In OS X 10.6 and later, the following methods no longer do anything useful. */
@property BOOL menuChangedMessagesEnabled NS_DEPRECATED_MAC(10_0, 10_11);
- (void)helpRequested:(NSEvent *)eventPtr NS_DEPRECATED_MAC(10_0, 10_11);
@property (getter=isTornOff, readonly) BOOL tornOff NS_DEPRECATED_MAC(10_0, 10_11);

@end

NS_ASSUME_NONNULL_END
