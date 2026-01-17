/*
	NSToolbarItem.h
	Application Kit
	Copyright (c) 2000-2024, Apple Inc.
	All rights reserved.
*/

#import <TargetConditionals.h>

#if !TARGET_OS_IPHONE
#import <AppKit/NSText.h>
#import <AppKit/NSMenu.h>
#import <AppKit/NSUserInterfaceValidation.h>
#endif
#import <AppKit/NSToolbar.h>
#import <Foundation/Foundation.h>
#import <Foundation/NSGeometry.h>

// Visual styles for the toolbar item.
typedef NS_ENUM(NSInteger, NSToolbarItemStyle) {
    // A plain style maintains the item’s standard appearance.
    NSToolbarItemStylePlain,
    // A prominent style enhances the item’s relevance and visibility, akin to a “Done” button
    NSToolbarItemStyleProminent,
} NS_SWIFT_NAME(NSToolbarItem.Style) API_AVAILABLE(macos(26.0), ios(26.0));

#if TARGET_OS_IPHONE
@class UIImage, UIColor;
#endif

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class NSMenuItem, NSView, NSImage, CKShare, NSItemBadge;

typedef NSInteger NSToolbarItemVisibilityPriority NS_TYPED_EXTENSIBLE_ENUM API_AVAILABLE(ios(13.0));
static const NSToolbarItemVisibilityPriority NSToolbarItemVisibilityPriorityStandard API_AVAILABLE(ios(13.0)) = 0;
static const NSToolbarItemVisibilityPriority NSToolbarItemVisibilityPriorityLow API_AVAILABLE(ios(13.0)) = -1000;
static const NSToolbarItemVisibilityPriority NSToolbarItemVisibilityPriorityHigh API_AVAILABLE(ios(13.0)) = 1000;
static const NSToolbarItemVisibilityPriority NSToolbarItemVisibilityPriorityUser API_AVAILABLE(ios(13.0)) = 2000;

API_AVAILABLE(ios(13.0)) NS_SWIFT_UI_ACTOR
@interface NSToolbarItem : NSObject <NSCopying>

/**
 Initialize the toolbar item with an identifier which is a development language string used by the toolbar and its delegate for identification purposes.
 */
- (instancetype)initWithItemIdentifier:(NSToolbarItemIdentifier)itemIdentifier NS_DESIGNATED_INITIALIZER;
@property (readonly, copy) NSToolbarItemIdentifier itemIdentifier;

/**
 Use this to determine the toolbar in which an item is currently displayed.
 */
@property (readonly, nullable, weak) NSToolbar *toolbar;


# pragma mark - Setters and Getters

/**
 Use this to set the item's label that appears in the toolbar.
 The label may also be used for the default `menuFormRepresentation` of the item.
 Also, developers should make sure the length of the label is appropriate and not too long.
 */
@property (copy) NSString *label;

/**
 Use this to set the item's label that appears when the item is in the customization palette.
 All Items must have a palette label, and for most things it is reasonable to set them to the same string as the label used in the toolbar.
 */
@property (copy) NSString *paletteLabel;

/**
 An array of all alternate labels this item may display.
 The item will use the size of the longest label to prevent resizing when the label is changed.
 */
@property (copy) NSSet<NSString *> *possibleLabels API_AVAILABLE(macos(13.0));

/**
 Use this to set a tooltip to be used when the item is displayed in the toolbar. (forwards to `-view` if it responds)
 */
@property (nullable, copy) NSString *toolTip;

/**
 The menu form of a toolbar item's purpose is twofold.
 First, when the window is too small to display an item, it will be clipped but remain accessible from a "clipped items" menu containing the menu item returned here.
 Second, in text only mode, the menu returned will be used to create the displayed items.
 Singleton menu items will be clickable, while submenu items will be represented as a pull down.
 For instance, say you want a button that allows you to switch between modes A, B, and C.
 You could represent this as a menu by: a menu item "mode" with three submenu items "A", "B", and "C".
 By default, this method returns a singleton menu item with item label as the title.
 For standard items, the target, action is set.
 */
@property (nullable, strong) NSMenuItem *menuFormRepresentation API_UNAVAILABLE(ios);

/**
 Tag for your own custom purpose. (forwards to `-view` if it responds)
 */
@property NSInteger tag;

/**
 Set and get the action of an item. (forwards to `-view` if it responds)
 */
@property (nullable, weak) id target;

/**
 Set and get the action of an item.
 For custom views, this method will call `-setAction:` on the view if it responds. (forwards to `-view` if it responds)
 */
@property (nullable) SEL action;

/**
 Set and get the enabled flag of an item.
 For custom views, this method will call `-setEnabled:` on the view if it responds. (forwards to `-view` if it responds)
 */
@property (getter=isEnabled) BOOL enabled;

/**
 Set and get the image of an item.
 For custom views, this method will call `-setImage:` on the view if it responds. (forwards to `-view` if it responds)
 */
#if !TARGET_OS_IPHONE
@property (nullable, strong) NSImage *image;
#else
@property (nullable, strong) UIImage *image API_AVAILABLE(ios(13.0));
#endif

/**
 Set and get the title of an item.
 For custom views, this method will call `-setTitle:` on the view if it responds. (forwards to `-view` if it responds)
 */
@property (copy) NSString *title API_AVAILABLE(macos(10.15), ios(13.0));

/**
 When set on an item without a custom view, the button produced will have a bordered style.
 Defaults to NO.
 */
@property (getter=isBordered) BOOL bordered API_AVAILABLE(macos(10.15), ios(13.0));

/**
 A color applied to tint the background of the toolbar item only if the item's style is prominent.
 */
#if !TARGET_OS_IPHONE
@property (nullable, copy) NSColor* backgroundTintColor API_AVAILABLE(macos(26.0));
#else
@property (nullable, copy) UIColor* backgroundTintColor API_AVAILABLE(ios(26.0));
#endif

/**
 Defines the toolbar item’s appearance. The default style is plain.
 Prominent style tints the background. If a background tint color is set, it uses it; otherwise, it uses the app’s or system’s accent color. If grouped with other items,
 it moves to its own to avoid tinting other items' background.
 */
@property NSToolbarItemStyle style API_AVAILABLE(macos(26.0), ios(26.0));

/**
 Whether or not the item behaves as a navigation item (i.e. back/forward) in the toolbar.
 Navigation items may be specially positioned by the system outside the normal list of items of the toolbar in the order specified by `-toolbarDefaultItemIdentifiers:`.
 Defaults to NO.
 */
@property (getter=isNavigational) BOOL navigational API_AVAILABLE(macos(11.0), ios(14.0));

/**
 Items with automatically generated views will return nil from this getter.
 Custom views may be provided but not all `NSToolbarItem` subclasses support custom views.
 Note that, by default, many of the set/get methods will be implemented by calls forwarded to the view you set, if it responds to it.
 */
@property (nullable, strong) NSView *view API_UNAVAILABLE(ios);

/**
 An item is visible if it is present in the NSToolbar and not in the overflow menu.
 This property is key value observable.
 */
@property (readonly, getter=isVisible) BOOL visible API_AVAILABLE(macos(12.0), ios(16.0));

/**
 When an item is hidden it will not be visible in the toolbar. The item will still be visible in the customization panel. Because hidden items may be visible during user customization, use the `visible` property to determine if an item is currently displayed. Note that even hidden toolbar items are sync'd to other toolbars with a shared identifier, but its `hidden` state can be unique to each instance. Use this property to show a toolbar item in one toolbar instance but not another.
 */
@property (getter=isHidden) BOOL hidden API_AVAILABLE(macos(15.0), ios(18.0));

/**
 Unless you have already set your own custom view, you should not call these methods.
 The min size should be small enough to look nice in all display modes.
 If you do not set a min/max size, the view's size properties will be calculated using constraints. Apps linked before 10.14 will use the view's current size.
 In general, apps should rely on the automatic measurements and constraints to define min/max sizes rather than setting these properties since this will account for localizations.
 */
@property NSSize minSize API_DEPRECATED("This property is no longer recommended. Instead, let the system automatically measure the size of the view using constraints.", macos(10.0, 12.0)) API_UNAVAILABLE(ios);
@property NSSize maxSize API_DEPRECATED("This property is no longer recommended. Instead, let the system automatically measure the size of the view using constraints.", macos(10.0, 12.0)) API_UNAVAILABLE(ios);

/**
 When a toolbar does not have enough space to fit all its items, it must push some into the overflow menu.
 Items with the highest `visibilityPriority` level are chosen last for the overflow menu.
 The default `visibilityPriority` value is `NSToolbarItemVisibilityPriorityStandard`.
 To suggest that an item always remain visible, give it a value greater than `NSToolbarItemVisibilityPriorityStandard`, but less than `NSToolbarItemVisibilityPriorityUser`.
 In 10.7, users can no longer modify the toolbar item visibility priority.
 */
@property NSToolbarItemVisibilityPriority visibilityPriority;

/// A badge that can be attached to an NSToolbarItem. This provides a way to display small visual indicators that can be used to highlight important information, such as unread notifications or status indicators.
@property (nullable, copy) NSItemBadge* badge API_AVAILABLE(macos(26.0)) NS_REFINED_FOR_SWIFT;

# pragma mark - Validation of the items

/**
 Typically you should not invoke this method.
 This method is called by its toolbar during validation.
 Standard items validate themselves by sending the `-validateToolbarItem:` validate message to the current validator.
 Since items with custom views don't always have meaningful target/actions, they do nothing.
 So for your custom items it may be useful to override this method and invent your own validation.
 */
- (void)validate API_AVAILABLE(ios(13.0));


/**
 This property only affects automatic validation performed by NSToolbar.
 Explicit validation requests, such as the `-[NSToolbar validateVisibleItems]` method, will invoke the `-validate` method even if `autovalidates` is `NO`.
 Defaults to YES.
 */
@property BOOL autovalidates API_AVAILABLE(ios(13.0));


# pragma mark - Controlling Duplicates In The Toolbar

/**
 Duplicate items outside of spaces are not allowed.
 */
@property (readonly) BOOL allowsDuplicatesInToolbar API_UNAVAILABLE(ios) API_DEPRECATED("Duplicates are no longer supported.", macos(10.0, 15.0));

@end

#if !TARGET_OS_IPHONE
@interface NSToolbarItem () <NSMenuItemValidation, NSValidatedUserInterfaceItem>
@end
#endif

#if !TARGET_OS_IPHONE

@protocol NSToolbarItemValidation <NSObject>

/**
 `NSToolbarItemValidation` extends the standard validation idea by introducing this new method which is sent to validators for each visible standard `NSToolbarItem` with a valid target/action pair.
 Note: This message is sent from NSToolbarItem's validate method, however validate will not send this message for items that have custom views.
 */
- (BOOL)validateToolbarItem:(NSToolbarItem *)item NS_SWIFT_UI_ACTOR;

@end

#if __swift__ < 40200
@interface NSObject (NSToolbarItemValidation)
- (BOOL)validateToolbarItem:(NSToolbarItem *)item API_DEPRECATED("This is now a method of the NSToolbarItemValidation protocol.", macos(10.0, 11.0));
@end
#endif

@protocol NSCloudSharingValidation <NSObject>

/**
 `NSToolbarItems` created with `NSToolbarCloudSharingItemIdentifier` use this method for further validation after sending `-validateToolbarItem:` or `-validateUserInterfaceItem:`.
 The validator for the item's action should return the current CKShare corresponding to the selected item, if any.
 The state of the item will be changed reflect the state of the CKShare.
 */
- (nullable CKShare *)cloudShareForUserInterfaceItem:(id <NSValidatedUserInterfaceItem>)item NS_SWIFT_UI_ACTOR;

@end

#endif

/**
 These are the standard toolbar item identifiers that AppKit will automatically create when they appear in the default or allowed item sets.
 As such, the delegate method `-toolbar:itemForItemIdentifier:willBeInsertedIntoToolbar:` will not be called for these items.
 */

/** A space item of a standard fixed size. */
APPKIT_EXTERN NSToolbarItemIdentifier NSToolbarSpaceItemIdentifier API_AVAILABLE(ios(13.0));

/** A space item of flexible width. */
APPKIT_EXTERN NSToolbarItemIdentifier NSToolbarFlexibleSpaceItemIdentifier API_AVAILABLE(ios(13.0));

/** A standard item that is configured to show the color panel when invoked. */
APPKIT_EXTERN NSToolbarItemIdentifier NSToolbarShowColorsItemIdentifier API_AVAILABLE(ios(13.0));

/** A standard item that is configured to show the font panel when invoked. */
APPKIT_EXTERN NSToolbarItemIdentifier NSToolbarShowFontsItemIdentifier API_AVAILABLE(ios(13.0));

/** A standard item that is configured to send -printDocument: to the firstResponder when invoked */
APPKIT_EXTERN NSToolbarItemIdentifier NSToolbarPrintItemIdentifier API_AVAILABLE(ios(13.0));

/** A standard item that is configured to send -toggleSidebar: to the firstResponder when invoked. */
APPKIT_EXTERN NSToolbarItemIdentifier NSToolbarToggleSidebarItemIdentifier API_AVAILABLE(macos(10.11), ios(13.0));

/** A standard item that is configured to send -toggleInspector: to the firstResponder when invoked. */
APPKIT_EXTERN NSToolbarItemIdentifier NSToolbarToggleInspectorItemIdentifier API_AVAILABLE(macos(14.0), ios(17.0));

/** A standard item for cloud sharing via NSSharingServiceNameCloudSharing. It validates itself and modifies its appearance by using the NSCloudSharingValidation protocol. It sends -performCloudSharing: to the firstResponder. */
APPKIT_EXTERN NSToolbarItemIdentifier NSToolbarCloudSharingItemIdentifier API_AVAILABLE(macos(10.12));

/** A standard item that is configured to send -showWritingTools: to the firstResponder when invoked. */
APPKIT_EXTERN NSToolbarItemIdentifier NSToolbarWritingToolsItemIdentifier API_AVAILABLE(macos(15.2));

/**
 Creates a new NSTrackingSeparatorToolbarItem and automatically configures it to track the divider of the sidebar if one is discovered.
 Only applies to windows with `NSWindowStyleMaskFullSizeContentView` applied.
 */
APPKIT_EXTERN NSToolbarItemIdentifier NSToolbarSidebarTrackingSeparatorItemIdentifier API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios);

/**
 Creates a new NSTrackingSeparatorToolbarItem and automatically configures it to track the divider of the inspector if one is discovered.
 Only applies to windows with `NSWindowStyleMaskFullSizeContentView` applied.
 */
APPKIT_EXTERN NSToolbarItemIdentifier NSToolbarInspectorTrackingSeparatorItemIdentifier API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios);

/**
 Deprecated Item Identifiers
 */
APPKIT_EXTERN NSToolbarItemIdentifier NSToolbarSeparatorItemIdentifier API_DEPRECATED("This item is no longer recommended and will be ignored on 10.7 and later.", macos(10.0, 11.0)) API_UNAVAILABLE(ios);
APPKIT_EXTERN NSToolbarItemIdentifier NSToolbarCustomizeToolbarItemIdentifier API_DEPRECATED("This item is no longer recommended and will be ignored on 10.7 and later.", macos(10.0, 11.0)) API_UNAVAILABLE(ios);

NS_HEADER_AUDIT_END(nullability, sendability)
