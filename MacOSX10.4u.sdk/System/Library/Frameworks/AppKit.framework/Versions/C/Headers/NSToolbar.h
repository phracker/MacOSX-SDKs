/*
	NSToolbar.h
	Application Kit
	Copyright (c) 2000-2004, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <AppKit/AppKitDefines.h>

@class NSToolbarItem;
@class NSWindow;
@class NSString;
@class NSMutableArray;

typedef enum { NSToolbarDisplayModeDefault, NSToolbarDisplayModeIconAndLabel, NSToolbarDisplayModeIconOnly, NSToolbarDisplayModeLabelOnly } NSToolbarDisplayMode;
typedef enum { NSToolbarSizeModeDefault, NSToolbarSizeModeRegular, NSToolbarSizeModeSmall } NSToolbarSizeMode;

@interface NSToolbar : NSObject {
@private
    NSString *			_toolbarIdentifier;

    NSMutableArray *		_currentItems;
    NSMutableArray *		_currentItemIdentifiers;

    NSDictionary *		_initPListDatabase;
    id				_initPListTarget; 
    
    NSString *			_selectedItemIdentifier;
    void *			_metrics;

    id				_delegate;
    NSWindow *			_window;
    id				_configPalette;
    id 				_toolbarView;
    int				_syncPostEnabledCount;
    
    struct __tbFlags {
	unsigned int allowsUserCustomization:1;
	unsigned int autosavesUsingIdentifier:1;
	unsigned int initialConfigurationDone:1;
	unsigned int shouldHideAfterCustomization:1;
        unsigned int delegateDefaultItemIdentifiers:1;
        unsigned int delegateAllowedItemIdentifiers:1;
        unsigned int delegateItemWithItemIdentifier:1;
	unsigned int delegateNotificationsEnabled:1;
        unsigned int prefersToBeShown:1;
        unsigned int loadItemsImmediately:1;
        unsigned int currentItemsContainsPlaceholder:1;
        unsigned int customizationPanelIsRunning:1;
        unsigned int usesCustomSheetWidth:1;
        unsigned int clickAndDragPerformsCustomization:1;
        unsigned int showsNoContextMenu:1;
        unsigned int firstMoveableItemIndex:6;
        unsigned int keyboardLoopNeedsUpdating:1;
        unsigned int showHideDuringConfigurationChangeDisabled:1;
	unsigned int displayMode:2;
	unsigned int sizeMode:2;
	unsigned int doNotShowBaselineSeparator:1;
        unsigned int hideWithoutResizingWindowHint:1;
        unsigned int autovalidatesItemsDisabled:1;
        unsigned int inAutovalidation:1;
	unsigned int loadedMetrics:1;
    } _tbFlags;

    int				_customizationSheetWidth;
    id				_tbReserved;
}

- (id)initWithIdentifier:(NSString *)identifier;
    /* The identifier is used to form the toolbar's autosave name.  Also, toolbars with the same identifier are implicitly synchronized so that they maintain the same state. */

- (void)insertItemWithItemIdentifier:(NSString *)itemIdentifier atIndex:(int)index;
- (void)removeItemAtIndex:(int)index;
    /* Primitives for explicitly adding and removing items.  Any change made will be propogated immediately to all other toolbars with the same identifier. */

- (void)setDelegate:(id)delegate;
- (id)delegate;
    /* Customizable toolbars must have a delegate, and must implement the required NSToolbarDelegate methods. */

- (void)setVisible:(BOOL)shown;
- (BOOL)isVisible;
    /* toggles the visibliity of the toolbar. */

- (void)runCustomizationPalette:(id)sender;
- (BOOL)customizationPaletteIsRunning;
    /* Customizable toolbars (those with delegates) can show a palette which allows users to populate the toolbar with individual items or to reset the toolbar to some default set of items.  The items and item sets in the palette are specified by the delegate (-toolbarAllowedItemIdentifiers: and -toolbarDefaultItemIdentifiers:).  When the user is done configuring, they will dismiss the palette. */


// ----- Toolbar Attributes  -----

- (void)setDisplayMode:(NSToolbarDisplayMode)displayMode;
- (NSToolbarDisplayMode)displayMode;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)setSelectedItemIdentifier:(NSString *)itemIdentifier;
- (NSString *)selectedItemIdentifier;
    /* Sets the toolbar's selected item by identifier.  Use this to force an item identifier to be selected.  Toolbar manages selection of image items automatically.  This method can be used to select identifiers of custom view items, or to force a selection change.  (see toolbarSelectableItemIdentifiers: delegate method for more details). */
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
- (void)setSizeMode:(NSToolbarSizeMode)sizeMode;
- (NSToolbarSizeMode)sizeMode;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
/* Use this API to hide the baseline NSToolbar draws between itself and the main window contents.  The default is YES.  This method should only be used before the toolbar is attached to its window (-[NSWindow setToolbar:]).
*/
- (void)setShowsBaselineSeparator:(BOOL)flag;
- (BOOL)showsBaselineSeparator;
#endif

- (void)setAllowsUserCustomization:(BOOL)allowCustomization;
- (BOOL)allowsUserCustomization;
    /* This flag controls whether or not users can configure the toolbar by dragging items around, and whether or not the customization palette can be used.  The default value is NO, but can be changed at any time.  For instance, a developer may not want users to be able to edit the toolbar while some event is being processed.  */

       
// ----- Accessing toolbar info -----

- (NSString *)identifier;
    /* All toolbars with the same name will share the same display attributes, and item order.  Also, if a toolbar autosaves its configuration, the item identifier will be used as the autosave name. */

- (NSArray *)items;
    /* Allows you to access all current items in the toolbar. */

- (NSArray *)visibleItems;
    /* Allows you to access the current visible items (non clipped). */


// ----- Autosaving The Configuration -----

- (void)setAutosavesConfiguration:(BOOL)flag;
- (BOOL)autosavesConfiguration;
    /* If autosavesConfiguration is YES, the toolbar will automatically write changes the user makes to user defaults.  Customizable toolbars will want to set this flag to YES.  Setting this to NO means changes in configuration are not written automatically, however you can use the configurationDictionary method to do it yourself.  Default is NO. */

- (void)setConfigurationFromDictionary:(NSDictionary *)configDict;
- (NSDictionary *)configurationDictionary;
    /* Set and get the current toolbar configuration using a dictionary representation. */


// ----- Validation of the items -----

- (void)validateVisibleItems;
    /* Typically you should not invoke this method.  This method is called on window updates with the purpose of validating 
each of the visible items.  The toolbar will iterate through the list of visible items, sending each a -validate message. */

@end

@interface NSObject (NSToolbarDelegate)

- (NSToolbarItem *)toolbar:(NSToolbar *)toolbar itemForItemIdentifier:(NSString *)itemIdentifier willBeInsertedIntoToolbar:(BOOL)flag;
    /* Required method.  Given an item identifier, this method returns an item.  Note that, it is expected that each toolbar receives its own distinct copies.   If the item has a custom view, that view should be in place when the item is returned.  Finally, do not assume the returned item is going to be added as an active item in the toolbar.  In fact, the toolbar may ask for items here in order to construct the customization palette (it makes copies of the returned items).  if willBeInsertedIntoToolbar is YES, the returned item will be inserted, and you can expect toolbarWillAddItem: is about to be posted.  */
    
- (NSArray *)toolbarDefaultItemIdentifiers:(NSToolbar*)toolbar;
    /* Required method.  Returns the ordered list of items to be shown in the toolbar by default.   If during initialization, no overriding values are found in the user defaults, or if the user chooses to revert to the default items this set will be used. */

- (NSArray *)toolbarAllowedItemIdentifiers:(NSToolbar*)toolbar;
    /* Required method.  Returns the list of all allowed items by identifier.  By default, the toolbar does not assume any items are allowed, even the separator.  So, every allowed item must be explicitly listed.  The set of allowed items is used to construct the customization palette.  The order of items does not necessarily guarantee the order of appearance in the palette.  At minimum, you should return the default item list.*/

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (NSArray *)toolbarSelectableItemIdentifiers:(NSToolbar *)toolbar;
    /* Optional method. Those wishing to indicate item selection in a toolbar should implement this method to return a non-empty array of selectable item identifiers.  If implemented, the toolbar will remember and display the selected item with a special highlight.  A selected item is one whose item identifier matches the current selected item identifier.  Clicking on an item whose identifier is selectable will automatically update the toolbars selected item identifier when possible. (see setSelectedItemIdentifier: for more details) */
#endif

@end


@interface NSObject (NSToolbarNotifications)

- (void)toolbarWillAddItem: (NSNotification *)notification;
    /* Before an new item is added to the toolbar, this notification is posted.  This is the best place to notice a new item is going into the toolbar.  For instance, if you need to cache a reference to the toolbar item or need to set up some initial state, this is the best place to do it.   The notification object is the toolbar to which the item is being added.  The item being added is found by referencing the @"item" key in the userInfo.  */

- (void)toolbarDidRemoveItem: (NSNotification *)notification;
    /* After an item is removed from a toolbar the notification is sent.  This allows the chance to tear down information related to the item that may have been cached.  The notification object is the toolbar to which the item is being added.  The item being added is found by referencing the @"item" key in the userInfo.  */

@end


/* Notifications */
APPKIT_EXTERN NSString *NSToolbarWillAddItemNotification;
APPKIT_EXTERN NSString *NSToolbarDidRemoveItemNotification;

