/*
    FinderSync.h

    Copyright (c) 2014-2015, Apple Inc.
    All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <AppKit/NSMenu.h>

#if __OBJC2__

NS_ASSUME_NONNULL_BEGIN
@interface FIFinderSyncController : NSExtensionContext

+ (instancetype)defaultController;

/* For each directory present in directoryURLs, the extension can receive -beginObservingDirectoryAtURL: and -endObservingDirectoryAtURL: for that directory and for any directories inside.
 */
@property (copy, null_resettable) NSSet<NSURL *> *directoryURLs;

/* Configure badge images and labels for a fixed set of badge identifiers, chosen by the extension. Each image should be able to draw at up to 320x320, and it should be "full frame" rather than include padding to control its position. The image may or may not draw on top of an icon; when it does, the system determines the overlay position. Each label should be a short localized string, such as "Waiting"; the system may present the image, or the label, or both.
 */
- (void)setBadgeImage:(NSImage *)image label:(nullable NSString *)label forBadgeIdentifier:(NSString *)badgeID;

/* Attach a particular badge to a file or folder. Setting the identifier to the empty string removes the badge.
 */
- (void)setBadgeIdentifier:(NSString *)badgeID forURL:(NSURL *)url;

/* Determine what directory the user is viewing, and what relevant items are selected, when displaying a menu or executing a command. Valid only during -menuForMenuKind:, or when executing an action specified in that menu. If the target or selected items are outside the extension's directories, these values will be nil.
 */
- (nullable NSURL *)targetedURL;
- (nullable NSArray<NSURL *> *)selectedItemURLs;
@end


typedef NS_ENUM(NSUInteger, FIMenuKind) {
    FIMenuKindContextualMenuForItems = 0,       /* contextual menu for one or more files/directories */
    FIMenuKindContextualMenuForContainer = 1,   /* contextual menu for the directory being displayed */
    FIMenuKindContextualMenuForSidebar = 2,     /* contextual menu for an item in the sidebar */
    FIMenuKindToolbarItemMenu = 3               /* the menu displayed when the user clicks the sync extension's toolbar item */
};


@protocol FIFinderSync
@optional

/* The extension should build a list of menu items to be displayed in the specified kind of menu. See FIFinderSyncController's -targetedURL and -selectedItemURLs. This will be called for any of the menu kinds when the target or selection is inside the directoryURLs. For FIToolbarItemMenu it will always be called, even if the target and selection are not related to the extension. The extension's principal object provides a method for each menu item's assigned action.

    Specific menu item properties are used: title, action, image, and enabled. Starting in OS X 10.11: tag, state, and indentationLevel also work, and submenus are allowed.
 */
- (nullable NSMenu*)menuForMenuKind:(FIMenuKind)menu;

/* Notify the extension that the user has started or stopped viewing the immediate children of a directory. The extension does not need to keep count of these; there will only be a single "begin" in effect for any particular URL.
 */
- (void)beginObservingDirectoryAtURL:(NSURL *)url;
- (void)endObservingDirectoryAtURL:(NSURL *)url;

/* The extension should respond by calling [[FIFinderSyncController defaultController] setBadgeIdentifier:forURL:], and call it whenever a different badge is required, until -endObservingDirectoryAtURL: says it's no longer necessary.
 */
- (void)requestBadgeIdentifierForURL:(NSURL *)url;

/* To provide a toolbar item, the extension must implement toolbarItemName and toolbarItemImage. When the user clicks the item, -menuForMenuKind: will be called with FIExtensionToolbarMenu.
 */
@property (copy, readonly) NSString *toolbarItemName;
@property (copy, readonly) NSImage *toolbarItemImage;
@property (copy, readonly) NSString *toolbarItemToolTip;
@end

/* The extension's NSExtensionPrincipalClass must be a subclass of FIFinderSync.
 */
@interface FIFinderSync : NSObject<FIFinderSync, NSExtensionRequestHandling>
@end
NS_ASSUME_NONNULL_END

#endif // OBJC2
