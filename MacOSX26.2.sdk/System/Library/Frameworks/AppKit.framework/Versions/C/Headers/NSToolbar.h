/*
	NSToolbar.h
	Application Kit
	Copyright (c) 2000-2024, Apple Inc.
	All rights reserved.
*/

#import <AppKit/AppKitDefines.h>
#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NSString * NSToolbarIdentifier NS_SWIFT_BRIDGED_TYPEDEF API_AVAILABLE(ios(13.0));
typedef NSString * NSToolbarItemIdentifier NS_TYPED_EXTENSIBLE_ENUM API_AVAILABLE(ios(13.0));

typedef NSString * NSToolbarUserInfoKey NS_TYPED_ENUM;
APPKIT_EXTERN NSToolbarUserInfoKey const NSToolbarItemKey API_AVAILABLE(macos(13.0));
APPKIT_EXTERN NSToolbarUserInfoKey const NSToolbarNewIndexKey API_AVAILABLE(macos(15.0));

@class NSToolbarItem, NSWindow, NSView;
@protocol NSToolbarDelegate;

typedef NS_ENUM(NSUInteger, NSToolbarDisplayMode) {
    NSToolbarDisplayModeDefault,
    NSToolbarDisplayModeIconAndLabel,
    NSToolbarDisplayModeIconOnly,
    NSToolbarDisplayModeLabelOnly
} API_AVAILABLE(ios(13.0));


typedef NS_ENUM(NSUInteger, NSToolbarSizeMode) {
    NSToolbarSizeModeDefault,
    NSToolbarSizeModeRegular,
    NSToolbarSizeModeSmall
} API_DEPRECATED("NSToolbarSizeMode is no longer recommended and will be ignored in the future", macos(10.0, API_TO_BE_DEPRECATED));

API_AVAILABLE(ios(13.0)) NS_SWIFT_UI_ACTOR
@interface NSToolbar : NSObject

/**
 The identifier is used to form the toolbar's autosave name.
 Toolbars with the same identifier are implicitly synchronized so that they maintain the same state.
 */
- (instancetype)initWithIdentifier:(NSToolbarIdentifier)identifier NS_DESIGNATED_INITIALIZER;

/**
 Calls through to -initWithIdentifier: with an empty string identifier.
 Customizable toolbars should use `-initWithIdentifier:` with a unique identifier instead.
 */
- (instancetype)init API_AVAILABLE(macos(10.13));

/**
 Inserts an item with the specified identifier in the receiving toolbar at the specified index.
 
 Any change made will be propagated immediately to all other toolbars with the same identifier.
 */
- (void)insertItemWithItemIdentifier:(NSToolbarItemIdentifier)itemIdentifier atIndex:(NSInteger)index;

/**
 Removes the item at the specified index in the receiving toolbar.
 
 Any change made will be propagated immediately to all other toolbars with the same identifier.
 */
- (void)removeItemAtIndex:(NSInteger)index;

/**
 Removes the item with matching `itemIdentifier` in the receiving toolbar. If multiple items share the same identifier (as is the case with space items) all matching items will be removed. To remove only a single space item, use `-removeItemAtIndex:` instead.
 
 Any change made will be propagated immediately to all other toolbars with the same identifier.
 */
- (void)removeItemWithItemIdentifier:(NSToolbarItemIdentifier)itemIdentifier API_AVAILABLE(macos(15.0), ios(18.0)) NS_SWIFT_NAME(removeItem(identifier:));

/**
 Customizable toolbars must have a delegate, and must implement the required `NSToolbarDelegate` methods.
 */
@property (nullable, weak) id<NSToolbarDelegate> delegate;

/**
 Toggles the visibility of the toolbar.
 This property may be modified by the user in toolbars with `allowsUserCustomization` enabled.
 This property is key value observable on macOS 14.0 and higher.
 */
@property (getter=isVisible) BOOL visible;

/**
 Customizable toolbars (those with delegates) can show a palette which allows users to populate the toolbar with individual items or to reset the toolbar to some default set of items.
 The items and item sets in the palette are specified by the delegate (`-toolbarAllowedItemIdentifiers:` and `-toolbarDefaultItemIdentifiers:`).
 When the user is done configuring, they will dismiss the palette.
 */
- (void)runCustomizationPalette:(nullable id)sender;

/**
 Whether or not the customization palette is currently running.
 On macOS 15.0 and above this property is key value observable.
 */
@property (readonly) BOOL customizationPaletteIsRunning;


# pragma mark - Toolbar Attributes

/**
 The current display mode of items in the toolbar.
 In toolbars with `allowsDisplayModeCustomization` enabled this is a user modifiable property.
 This property is key value observable.
 */
@property NSToolbarDisplayMode displayMode;

/**
 Sets the toolbar's selected item by identifier.
 Use this to force an item identifier to be selected.
 Toolbar manages selection of image items automatically.
 This method can be used to select identifiers of custom view items, or to force a selection change.
 See `-toolbarSelectableItemIdentifiers:` delegate method for more details.
 This property is key value observable.
 */
@property (nullable, copy) NSToolbarItemIdentifier selectedItemIdentifier;

/**
 This flag controls whether or not users can configure the toolbar by dragging items around, and whether or not the customization palette can be used.
 The default value is NO, but can be changed at any time.
 For instance, a developer may not want users to be able to edit the toolbar while some event is being processed.
 */
@property BOOL allowsUserCustomization;

/**
 Whether or not the user is allowed to change display modes at run time.
 This functionality is independent of customizing the order of the items themselves.
 Only disable when the functionality or legibility of your toolbar could not be improved by another display mode.
 The user's selection will be persisted using the toolbar's `identifier` when `autosavesConfiguration` is enabled.
 The default is YES for apps linked on macOS 15.0 and above.
 */
@property BOOL allowsDisplayModeCustomization API_AVAILABLE(macos(15.0), ios(18.0));


# pragma mark - Accessing toolbar info

/**
 All toolbars with the same name will share the same display attributes, and item order.
 If a toolbar autosaves its configuration, the item identifier will be used as the autosave name.
 */
@property (readonly, copy) NSToolbarIdentifier identifier;

/**
 Allows you to access all current items in the toolbar.
 */
@property (readonly, copy) NSArray<__kindof NSToolbarItem *> *items;

/**
 Allows you to access the current visible items (non clipped).
 */
@property (nullable, readonly, copy) NSArray<__kindof NSToolbarItem *> *visibleItems;

/**
 An array of itemIdentifiers that represent the current items in the toolbar.
 Setting this property will set the current items in the toolbar by diffing against items that already exist.
 Use this with great caution if `allowsUserCustomization` is enabled as it will override any customizations the user has made.
 This property is key value observable.
 */
@property (copy) NSArray<NSToolbarItemIdentifier> *itemIdentifiers API_AVAILABLE(macos(15.0), ios(18.0));

/**
 Items with centered identifiers will be centered together in the Toolbar relative to the window assuming space allows.
 The order of items is initially defined by the default set of identifiers, but may be customized by the user.
 Centered items may not be moved outside of the center set of items by the user.
 This property is archived.
 */
@property (copy) NSSet<NSToolbarItemIdentifier> *centeredItemIdentifiers API_AVAILABLE(macos(13.0), ios(16.0));


# pragma mark - Autosaving The Configuration

/**
 If `autosavesConfiguration` is YES, the toolbar will automatically write changes the user makes to user defaults.
 Customizable toolbars will want to set this flag to YES.
 Setting this to NO means changes in configuration are not written automatically, however you can use the `configurationDictionary` method to do it yourself.
 Default is NO.
 */
@property BOOL autosavesConfiguration;


# pragma mark - Item Validation

/**
 Typically you should not invoke this method.
 This method is called on window updates with the purpose of validating each of the visible items.
 The toolbar will iterate through the list of visible items, sending each a `-validate` message.
 If this method is invoked directly, all visible items including those with `autovalidates` disabled will get a `-validate` message.
 */
- (void)validateVisibleItems API_UNAVAILABLE(ios);


# pragma mark - Extension toolbar items

/**
 When YES, the receiver can dynamically create toolbar items for Action extensions in the toolbar configuration panel.
 To be included, an extension needs to declare NSExtensionServiceAllowsToolbarItem=YES in its Info.plist.
 The default value is NO.
*/
@property BOOL allowsExtensionItems API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios);

@end

# pragma mark - Delegate

API_AVAILABLE(ios(13.0))
@protocol NSToolbarDelegate <NSObject>

/**
 The following three methods are required for toolbars that are not created in Interface Builder.
 If the toolbar is created in IB, you may omit them.
 If you do implement them, any items returned by the delegate will be used alongside items created in Interface Builder.
 */
@optional

/**
 Given an item identifier, this method returns an item.
 Note that it is expected that each toolbar receives its own distinct copies and each time this method is called a new item must be returned.
 If the item has a custom view, that view should be in place when the item is returned.
 Finally, do not assume the returned item is going to be added as an active item in the toolbar.
 In fact, the toolbar may ask for items here in order to construct the customization palette.
 If `willBeInsertedIntoToolbar` is YES, the returned item will be inserted, and you can expect `toolbarWillAddItem:` is about to be posted.
 */
- (nullable NSToolbarItem *)toolbar:(NSToolbar *)toolbar itemForItemIdentifier:(NSToolbarItemIdentifier)itemIdentifier willBeInsertedIntoToolbar:(BOOL)flag NS_SWIFT_UI_ACTOR;
    
/**
 Returns the ordered list of items to be shown in the toolbar by default.
 If during initialization, no overriding values are found in the user defaults, or if the user chooses to revert to the default items this set will be used.
 */
- (NSArray<NSToolbarItemIdentifier> *)toolbarDefaultItemIdentifiers:(NSToolbar *)toolbar NS_SWIFT_UI_ACTOR;

/**
 Returns the list of all allowed items by identifier.
 By default, the toolbar does not assume any items are allowed so every allowed item must be explicitly listed.
 The set of allowed items is used to construct the customization palette.
 The order of items does not necessarily guarantee the order of appearance in the palette.
 At minimum, you should return the default item list.
 */
- (NSArray<NSToolbarItemIdentifier> *)toolbarAllowedItemIdentifiers:(NSToolbar *)toolbar NS_SWIFT_UI_ACTOR;

@optional

/**
 Optional method.
 Those wishing to indicate item selection in a toolbar should implement this method to return a non-empty array of selectable item identifiers.
 If implemented, the toolbar will remember and display the selected item with a special highlight.
 A selected item is one whose item identifier matches the current selected item identifier.
 Clicking on an item whose identifier is selectable will automatically update the toolbar's `selectedItemIdentifier` when possible.
 See `selectedItemIdentifier` for more details.
 */
- (NSArray<NSToolbarItemIdentifier> *)toolbarSelectableItemIdentifiers:(NSToolbar *)toolbar NS_SWIFT_UI_ACTOR;

/**
 Items in this set cannot be dragged or removed by the user.
 */
- (NSSet<NSToolbarItemIdentifier> *)toolbarImmovableItemIdentifiers:(NSToolbar *)toolbar NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(13.0), ios(16.0));

/**
 Whether or not an item can be moved to a specified position in the toolbar.
 If implemented, this method will be called during a user drag and does not necessarily indicate the final position of an item.
 An index of NSNotFound indicates the item would be removed from the toolbar.
 */
- (BOOL)toolbar:(NSToolbar *)toolbar itemIdentifier:(NSToolbarItemIdentifier)itemIdentifier canBeInsertedAtIndex:(NSInteger)index NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(13.0), ios(16.0));


# pragma mark - Notifications

/**
 Before a new item is added to the toolbar, this notification is posted.
 This is the best place to notice a new item is going into the toolbar.
 For instance, if you need to cache a reference to the toolbar item or need to set up some initial state, this is the best place to do it.
 The notification object is the toolbar to which the item is being added.
 The item being added and its new index can be found by referencing `NSToolbarItemKey` and `NSToolbarNewIndexKey` in the userInfo dictionary respectively.
 */
- (void)toolbarWillAddItem:(NSNotification *)notification NS_SWIFT_UI_ACTOR;

/**
 After an item is removed from a toolbar the notification is sent.
 This allows the chance to tear down information related to the item that may have been cached.
 The notification object is the toolbar from which the item is being removed.
 The item being removed is found by referencing the `NSToolbarItemKey` in the userInfo.
 */
- (void)toolbarDidRemoveItem:(NSNotification *)notification NS_SWIFT_UI_ACTOR;

@end

/** Notifications */
APPKIT_EXTERN NSNotificationName NSToolbarWillAddItemNotification API_AVAILABLE(ios(13.0));
APPKIT_EXTERN NSNotificationName NSToolbarDidRemoveItemNotification API_AVAILABLE(ios(13.0));

APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

@interface NSToolbar(NSDeprecated)

@property NSToolbarSizeMode sizeMode API_UNAVAILABLE(ios) API_DEPRECATED("NSToolbarSizeMode is no longer recommended and will be ignored in the future", macos(10.0, API_TO_BE_DEPRECATED));
@property (nullable, copy) NSToolbarItemIdentifier centeredItemIdentifier API_DEPRECATED("Use the centeredItemIdentifiers property instead", macos(10.14, API_TO_BE_DEPRECATED), ios(13.0, API_TO_BE_DEPRECATED));
@property (nullable, strong) NSView *fullScreenAccessoryView API_DEPRECATED("Use NSTitlebarAccessoryViewController with NSWindow instead", macos(10.7,10.13));
@property CGFloat fullScreenAccessoryViewMinHeight API_DEPRECATED("Use NSTitlebarAccessoryViewController and its fullScreenMinHeight property with NSWindow instead.", macos(10.7,10.13));
@property CGFloat fullScreenAccessoryViewMaxHeight API_DEPRECATED("Use NSTitlebarAccessoryViewController with NSWindow instead. The max height of a titlebar accessory is implied by its view's height.", macos(10.7,10.13));
@property BOOL showsBaselineSeparator API_DEPRECATED("No longer supported", macos(10.0, 15.0));
@property (readonly, copy) NSDictionary<NSString *, id> *configurationDictionary API_DEPRECATED("Use -itemIdentifiers and -displayMode instead.", macos(10.0, 15.0));
- (void)setConfigurationFromDictionary:(NSDictionary<NSString *, id> *)configDict API_DEPRECATED("Use -setItemIdentifiers: and -setDisplayMode: instead.", macos(10.0, 15.0));

@end

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
