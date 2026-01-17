/*
    FinderSync.h

    Copyright (c) 2014-2025, Apple Inc.
    All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <AppKit/NSMenu.h>

API_UNAVAILABLE_BEGIN(ios)

NS_ASSUME_NONNULL_BEGIN
/// A controller that acts as a bridge between your Finder Sync extension and the Finder itself.
///
/// Use the Finder Sync controller to configure your extension, to set badges
/// on items in the Finder’s window, and to get a list of selected and targeted
/// items.
@interface FIFinderSyncController : NSExtensionContext

/// Returns the shared Finder Sync controller object.
///
/// - Returns: The default Finder Sync controller object for this extension.
+ (instancetype)defaultController;

/// The directories managed by this extension.
///
/// The extension receives
/// ``FIFinderSync/beginObservingDirectoryAtURL:`` and
/// ``FIFinderSync/endObservingDirectoryAtURL:`` messages for every
/// directory in this set and for all of their subdirectories.
///
/// Always set `directoryURLs` when the extension starts. If there are no
/// directories to watch, set `directoryURLs` to an empty set.
@property (copy, null_resettable) NSSet<NSURL *> *directoryURLs;

/// Sets the badge image and label for the given ID.
///
/// Use this method to configure your badges. Finder may display the image, the
/// label or both. Your Finder Sync extension typically sets up a fixed number
/// of badges during its `init` method.
///
/// - Parameters:
///   - image: An <doc://com.apple.documentation/documentation/appkit/nsimage>
///     object. The system may or may not draw this image on top of the item’s
///     icon; when it does, the system determines the overlay position. Don't
///     add any padding to the image to adjust this positioning. The image draws
///     at up to 320 x 320 points.
///   - label: A label describing the sync state represented by this badge.
///     Each label should be a short localized string, such as "Waiting."
///   - badgeID: A unique ID, identifying this badge.
- (void)setBadgeImage:(NSImage *)image label:(nullable NSString *)label forBadgeIdentifier:(NSString *)badgeID;

/// Sets the badge for a file or directory.
///
/// Adds the specified badge to the given file or directory. Setting the
/// identifier to an empty string (`@""`) removes the badge.
///
/// Avoid adding badges to items that the Finder hasn't displayed yet.
/// When setting the initial badge, call this method from your Finder Sync
/// extension’s ``FIFinderSync/requestBadgeIdentifierForURL:``
/// method. When updating badges, call this method only for items that have
/// already received a badge.
///
/// - Parameters:
///   - badgeID: A unique ID, identifying the badge.
///   - url: The URL of the file or directory.
///
/// ## See Also
///   - ``FIFinderSync/requestBadgeIdentifierForURL:``
- (void)setBadgeIdentifier:(NSString *)badgeID forURL:(NSURL *)url;

/// Returns the URL of the Finder’s current target.
///
/// Use this method when creating a custom shortcut menu for the Finder. This
/// returns the URL of the item that the user Control-clicked, letting you
/// customize the menu for that item.
///
/// This method returns valid values only from the Finder Sync extension’s
/// ``FIFinderSync/menuForMenuKind:`` method or from one of the menu
/// actions created in this method. If the selected items are outside the
/// extension’s managed directories (for example, when the user clicks on the
/// toolbar button), this method returns `nil`.
///
/// - Returns: The URL of the Finder’s current target.
- (nullable NSURL *)targetedURL;

/// Returns an array of selected items.
///
/// Use this method when creating a shortcut menu or a menu for the extension’s
/// toolbar button. You can then modify the menu’s content based on the items
/// currently selected.
///
/// This method returns valid values only from the Finder Sync extension’s
/// ``FIFinderSync/menuForMenuKind:`` method or from one of the menu
/// actions created in this method. If the selected items are outside the
/// extension’s managed directories (for example, when the user clicks on the
/// toolbar button), this method returns `nil`.
///
/// - Returns: An array of items currently selected in the Finder window.
- (nullable NSArray<NSURL *> *)selectedItemURLs;


/* Collaboration, starting in macOS 10.13.
*/
- (nullable NSDate *)lastUsedDateForItemWithURL:(NSURL *)itemURL;

- (void)setLastUsedDate:(NSDate *)lastUsedDate forItemWithURL:(NSURL *)itemURL completion:(void(^)(NSError *error))completion;

- (nullable NSData *)tagDataForItemWithURL:(NSURL *)itemURL;

- (void)setTagData:(nullable NSData *)tagData forItemWithURL:(NSURL *)itemURL completion:(void(^)(NSError *error))completion;


/* The application hosting a Finder Sync Extension can determine whether the user has enabled the extension, and can show the UI for managing extensions. When the application becomes active again, it can check whether the user has enabled the extension.
 */
@property (class, readonly, getter=isExtensionEnabled) BOOL extensionEnabled API_AVAILABLE(macos(10.14));
+ (void)showExtensionManagementInterface API_AVAILABLE(macos(10.14));

@end


/// The different kinds of custom menus that the Finder Sync extension can
/// provide.
typedef NS_ENUM(NSUInteger, FIMenuKind) {
	/// A shortcut menu created when the user control-clicks on an item or a
	/// group of selected items inside the Finder window.
    FIMenuKindContextualMenuForItems = 0,
	/// A shortcut menu created when the user control-clicks on the Finder
	/// window’s background.
    FIMenuKindContextualMenuForContainer = 1,
	/// A shortcut menu created when the user control-clicks on an item in the
	/// sidebar.
    FIMenuKindContextualMenuForSidebar = 2,
	/// A menu created when the user clicks on the extension’s toolbar button.
    FIMenuKindToolbarItemMenu = 3
};


/// The group of methods to implement for modifying the Finder user interface to express file synchronization status and control.
@protocol FIFinderSync
@optional

/// Requests a custom menu from the extension.
///
/// Override this method to provide custom menus in the Finder. You can
/// customize this menu based both on the menu’s kind and on the selected and
/// targeted items (if any). You can get the selected and targeted items from
/// the extension’s ``FIFinderSyncController``.
///
/// If `kind` is ``FIMenuKindToolbarItemMenu``, the system always calls this
/// method even if the target and selection are not related to the extension.
///
/// The extension's principal object provides a method for each menu item's
/// assigned action.
///
/// - Parameters:
///   - menu: The type of menu being displayed. For a list of possible values, see ``FinderSync/FIMenuKind``.
///
/// - Returns: A custom menu.
///
/// ## See Also
///   - ``FinderSync/FIFinderSyncController/targetedURL``
///   - ``FinderSync/FIFinderSyncController/selectedItemURLs``
- (nullable NSMenu*)menuForMenuKind:(FIMenuKind)menu;

/// Tells the extension that the user is looking at a monitored directory or at
/// one of its subdirectories.
///
/// Override this method to receive notifications when the user opens the
/// contents of a monitored directory or one of its subdirectories in the
/// Finder. The system calls `beginObservingDirectoryAtURL:` only once for each
/// unique URL. As long as the content remains visible in at least one Finder
/// window, any additional Finder windows that open to the same URL are ignored.
///
/// - Note: The system creates additional instances of your extension for any
/// Open and Save dialogs. These extensions receive their own calls to
/// `beginObservingDirectoryAtURL:`, even if the directory is already open in a
/// Finder window.
///
/// - Parameters:
///   - url: The URL of the directory.
- (void)beginObservingDirectoryAtURL:(NSURL *)url;

/// Tells the extension that the user has stopped looking at a monitored
/// directory or at one of its subdirectories.
///
/// Override this method to receive notifications when the user is no longer
/// looking at the contents of the given URL. As with
/// ``FIFinderSync/beginObservingDirectoryAtURL:``, the Open and Save
/// dialogs are tracked separately from the Finder.
///
/// - Parameters:
///   - url: The URL of the directory.
- (void)endObservingDirectoryAtURL:(NSURL *)url;

/// Requests a badge for the given file or directory.
///
/// Override this method to receive notifications whenever a new item becomes
/// visible in the Finder. Check the item’s state, and call
/// ``FIFinderSyncController/setBadgeIdentifier:forURL:`` to set an appropriate
/// badge.
///
/// - Parameters:
///   - url: The URL of a file or directory inside the extension’s monitored
/// directories.
///
/// ## See Also
///   - ``FinderSync/FIFinderSyncController/setBadgeIdentifier:forURL:``
- (void)requestBadgeIdentifierForURL:(NSURL *)url;

/// The name of the extension’s toolbar button.
///
/// To add a toolbar item to the Finder, override the getter method for the
/// toolbar image, name, and tooltip properties.
@property (copy, readonly) NSString *toolbarItemName;

/// The image for the extension’s toolbar button.
///
/// To add a toolbar item to the Finder, override the getter method for the
/// toolbar image, name, and tooltip properties.
@property (copy, readonly) NSImage *toolbarItemImage;

/// The tooltip text for the extension’s toolbar button.
///
/// To add a toolbar item to the Finder, override the getter method for the
/// toolbar image, name, and tooltip properties.
@property (copy, readonly) NSString *toolbarItemToolTip;


/* Collaboration, starting in macOS 10.13.
*/
- (NSArray <NSFileProviderServiceName> *)supportedServiceNamesForItemWithURL:(NSURL *)itemURL;
- (nullable NSXPCListenerEndpoint *)makeListenerEndpointForServiceName:(NSFileProviderServiceName)serviceName itemURL:(NSURL *)itemURL andReturnError:(NSError * _Nullable __autoreleasing *)error;

- (void)valuesForAttributes:(NSArray<NSURLResourceKey> *)attributes forItemWithURL:(NSURL *)itemURL completion:(void(^)(NSDictionary<NSURLResourceKey, id> *, NSError * _Nullable))completion;
@end

/// A type to subclass to add badges, custom shortcut menus, and toolbar buttons to the Finder.
///
/// Subclass the FIFinderSync class when you want to customize the appearance of
/// the Finder. Although the FIFinderSync class doesn’t provide any developer
/// accessible API, it does adopt the ``FIFinderSyncProtocol``
/// protocol. This protocol declares methods you can implement to modify the
/// appearance of the Finder. For more information on these methods, see
/// ``FIFinderSyncProtocol``. To learn more about creating a Finder Sync
/// extension, see [Finder
/// Sync](https://developer.apple.com/library/archive/documentation/General/Conceptual/ExtensibilityPG/Finder.html#//apple_ref/doc/uid/TP40014214-CH15)
/// in [App Extension Programming
/// Guide](https://developer.apple.com/library/archive/documentation/General/Conceptual/ExtensibilityPG/index.html#//apple_ref/doc/uid/TP40014214).
///
/// ## See Also
///   - ``FinderSync/FIFinderSyncProtocol``
@interface FIFinderSync : NSObject<FIFinderSync, NSExtensionRequestHandling>
@end
NS_ASSUME_NONNULL_END

API_UNAVAILABLE_END
