/*
	NSToolbar.h
	Application Kit
	Copyright (c) 2000-2015, Apple Inc.
	All rights reserved.
*/

#import <AppKit/AppKitDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class NSToolbarItem, NSWindow, NSView;
@protocol NSToolbarDelegate;

typedef NS_ENUM(NSUInteger, NSToolbarDisplayMode) {
    NSToolbarDisplayModeDefault,
    NSToolbarDisplayModeIconAndLabel,
    NSToolbarDisplayModeIconOnly,
    NSToolbarDisplayModeLabelOnly
};


typedef NS_ENUM(NSUInteger, NSToolbarSizeMode) {
    NSToolbarSizeModeDefault,
    NSToolbarSizeModeRegular,
    NSToolbarSizeModeSmall
};

@interface NSToolbar : NSObject {
@private
    NSString *			_toolbarIdentifier;

    NSMutableArray *		_currentItems;
    NSMutableArray *		_currentItemIdentifiers;

    NSView *_fullScreenAccessoryView;
    id				_res2; 
    
    NSString *			_selectedItemIdentifier;
    __strong void *		_metrics;

    id				_delegate;
    NSWindow *			_logicalWindow;
    id				_configPalette;
    id 				_toolbarView;
    NSInteger			_syncPostEnabledCount;
    
    struct __tbFlags {
	unsigned int allowsUserCustomization:1;
	unsigned int autosavesUsingIdentifier:1;
	unsigned int initialConfigurationDone:1;
	unsigned int doesNotAttachToMenuBar:1;
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
        unsigned int currentlyLoadingPlaceholders:1;
        unsigned int delegateItemWithItemIdentifier2:1;
        unsigned int inGlobalWindow:1;
        unsigned int hasOwnedFullscreenViewController:1;
        unsigned int usesServicesItems:1;
        unsigned int usingFSMetrics:1;
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

    NSInteger			_customizationSheetWidth;
    id				_tbReserved;
}

/* The identifier is used to form the toolbar's autosave name.  Also, toolbars with the same identifier are implicitly synchronized so that they maintain the same state. */
- (instancetype)initWithIdentifier:(NSString *)identifier NS_DESIGNATED_INITIALIZER;

/* Primitives for explicitly adding and removing items.  Any change made will be propogated immediately to all other toolbars with the same identifier. */
- (void)insertItemWithItemIdentifier:(NSString *)itemIdentifier atIndex:(NSInteger)index;
- (void)removeItemAtIndex:(NSInteger)index;

/* Customizable toolbars must have a delegate, and must implement the required NSToolbarDelegate methods. */
@property (nullable, assign) id<NSToolbarDelegate> delegate;

/* toggles the visibliity of the toolbar. */
@property (getter=isVisible) BOOL visible;

/* Customizable toolbars (those with delegates) can show a palette which allows users to populate the toolbar with individual items or to reset the toolbar to some default set of items.  The items and item sets in the palette are specified by the delegate (-toolbarAllowedItemIdentifiers: and -toolbarDefaultItemIdentifiers:).  When the user is done configuring, they will dismiss the palette. */
- (void)runCustomizationPalette:(nullable id)sender;
@property (readonly) BOOL customizationPaletteIsRunning;


// ----- Toolbar Attributes  -----

@property NSToolbarDisplayMode displayMode;

/* Sets the toolbar's selected item by identifier.  Use this to force an item identifier to be selected.  Toolbar manages selection of image items automatically.  This method can be used to select identifiers of custom view items, or to force a selection change.  (see toolbarSelectableItemIdentifiers: delegate method for more details). */
@property (nullable, copy) NSString *selectedItemIdentifier;

@property NSToolbarSizeMode sizeMode;

/* Use this API to hide the baseline NSToolbar draws between itself and the main window contents.  The default is YES.  This method should only be used before the toolbar is attached to its window (-[NSWindow setToolbar:]).
*/
@property BOOL showsBaselineSeparator;

/* This flag controls whether or not users can configure the toolbar by dragging items around, and whether or not the customization palette can be used.  The default value is NO, but can be changed at any time.  For instance, a developer may not want users to be able to edit the toolbar while some event is being processed.  */
@property BOOL allowsUserCustomization;


// ----- Accessing toolbar info -----

/* All toolbars with the same name will share the same display attributes, and item order.  Also, if a toolbar autosaves its configuration, the item identifier will be used as the autosave name. */
@property (readonly, copy) NSString *identifier;

/* Allows you to access all current items in the toolbar. */
@property (readonly, copy) NSArray<__kindof NSToolbarItem *> *items;

/* Allows you to access the current visible items (non clipped). */
@property (nullable, readonly, copy) NSArray<__kindof NSToolbarItem *> *visibleItems;


// ----- Autosaving The Configuration -----

/* If autosavesConfiguration is YES, the toolbar will automatically write changes the user makes to user defaults.  Customizable toolbars will want to set this flag to YES.  Setting this to NO means changes in configuration are not written automatically, however you can use the configurationDictionary method to do it yourself.  Default is NO. */
@property BOOL autosavesConfiguration;

/* Set and get the current toolbar configuration using a dictionary representation. */
- (void)setConfigurationFromDictionary:(NSDictionary<NSString *, id> *)configDict;
@property (readonly, copy) NSDictionary<NSString *, id> *configurationDictionary;


// ----- Validation of the items -----

/* Typically you should not invoke this method.  This method is called on window updates with the purpose of validating 
 each of the visible items.  The toolbar will iterate through the list of visible items, sending each a -validate message. */
- (void)validateVisibleItems;

// ----- Extension toolbar items -----
/* When YES, the receiver can dynamically create toolbar items for Action extensions in the toolbar configuration panel. To be included, an extension needs to declare NSExtensionServiceAllowsToolbarItem=YES in its Info.plist. The default value is NO.
*/
@property BOOL allowsExtensionItems NS_AVAILABLE_MAC(10_10);

@end

@protocol NSToolbarDelegate <NSObject>

/*The following three methods are required for toolbars that are not created in Interface Builder.  If the toolbar is created in IB, you may omit them.  If you do implement them, any  items returned by the delegate will be used alongside items created in Interface Builder. */
@optional

/* Given an item identifier, this method returns an item.  Note that, it is expected that each toolbar receives its own distinct copies.   If the item has a custom view, that view should be in place when the item is returned.  Finally, do not assume the returned item is going to be added as an active item in the toolbar.  In fact, the toolbar may ask for items here in order to construct the customization palette (it makes copies of the returned items).  if willBeInsertedIntoToolbar is YES, the returned item will be inserted, and you can expect toolbarWillAddItem: is about to be posted.  */
- (nullable NSToolbarItem *)toolbar:(NSToolbar *)toolbar itemForItemIdentifier:(NSString *)itemIdentifier willBeInsertedIntoToolbar:(BOOL)flag;
    
/* Returns the ordered list of items to be shown in the toolbar by default.   If during initialization, no overriding values are found in the user defaults, or if the user chooses to revert to the default items this set will be used. */
- (NSArray<NSString *> *)toolbarDefaultItemIdentifiers:(NSToolbar *)toolbar;

/* Returns the list of all allowed items by identifier.  By default, the toolbar does not assume any items are allowed, even the separator.  So, every allowed item must be explicitly listed.  The set of allowed items is used to construct the customization palette.  The order of items does not necessarily guarantee the order of appearance in the palette.  At minimum, you should return the default item list.*/
- (NSArray<NSString *> *)toolbarAllowedItemIdentifiers:(NSToolbar *)toolbar;

@optional

/* Optional method. Those wishing to indicate item selection in a toolbar should implement this method to return a non-empty array of selectable item identifiers.  If implemented, the toolbar will remember and display the selected item with a special highlight.  A selected item is one whose item identifier matches the current selected item identifier.  Clicking on an item whose identifier is selectable will automatically update the toolbar's selectedItemIdentifier when possible. (see setSelectedItemIdentifier: for more details) */
- (NSArray<NSString *> *)toolbarSelectableItemIdentifiers:(NSToolbar *)toolbar;

    /* Notifications */

/* Before an new item is added to the toolbar, this notification is posted.  This is the best place to notice a new item is going into the toolbar.  For instance, if you need to cache a reference to the toolbar item or need to set up some initial state, this is the best place to do it.   The notification object is the toolbar to which the item is being added.  The item being added is found by referencing the @"item" key in the userInfo.  */
- (void)toolbarWillAddItem:(NSNotification *)notification;

/* After an item is removed from a toolbar the notification is sent.  This allows the chance to tear down information related to the item that may have been cached.  The notification object is the toolbar from which the item is being removed.  The item being removed is found by referencing the @"item" key in the userInfo.  */
- (void)toolbarDidRemoveItem:(NSNotification *)notification;

@end

/* Notifications */
APPKIT_EXTERN NSString * NSToolbarWillAddItemNotification;
APPKIT_EXTERN NSString * NSToolbarDidRemoveItemNotification;



@interface NSToolbar(NSDeprecated)


/* 
 NOTE: this is deprecated in 10.10, and instead NSTitlebarAccessoryViewController should be used with NSWindow.
 
 Sets the toolbar full screen accessory view.  When entering full screen, the accessory view is removed from the window if necessary, and attaches underneath the toolbar.  When leaving full screen, the accessory view is returned to the window, if it was in the window previously. To customize this latter behavior, you can implement the NSWindow delegate method windowWillExitFullScreen:.
 */
@property (nullable, strong) NSView *fullScreenAccessoryView NS_AVAILABLE_MAC(10_7);

/* 
 NOTE: this is deprecated in 10.10, and instead NSTitlebarAccessoryViewController should be used with NSWindow. NSTitlebarAccessoryViewController has a fullScreenMinHeight property. The fullScreenMaxHeight is implied by the view's height.

 
 The following properties control the minimum and maximum height of the accessory view. The minimum height is used when the menu bar is hidden, and the max height to a fully revealed menu bar. During the reveal, the accessory view's frame is interpolated between its minimum and maximum height.
 
 If the minimum height is zero (which it is by default), the accessory view is not resized; instead a special transition is used to reveal it with the menu bar. This simplifies the accessory view's task, because it does not have to handle the case of being set to zero height. To create a fixed-height accessory view, set the min and max height to be equal.
 
 By default, the min height is 0 and the max height gets set to the height of the accessory view's frame when it is set.
 */
@property CGFloat fullScreenAccessoryViewMinHeight NS_AVAILABLE_MAC(10_7);
@property CGFloat fullScreenAccessoryViewMaxHeight NS_AVAILABLE_MAC(10_7);


@end

NS_ASSUME_NONNULL_END
