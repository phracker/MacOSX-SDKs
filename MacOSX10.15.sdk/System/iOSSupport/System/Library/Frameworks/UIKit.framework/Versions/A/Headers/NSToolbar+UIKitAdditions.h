#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/NSToolbar+UIKitAdditions.h>)
//
//  NSToolbar+UIKitAdditions.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <TargetConditionals.h>

#if TARGET_OS_MACCATALYST

#import <Foundation/Foundation.h>
#import <UIKit/UIWindowScene.h>
#import <UIKit/UIActivityItemsConfigurationReading.h>
#import <AppKit/NSToolbarItem.h>
#import <AppKit/NSMenuToolbarItem.h>
#import <AppKit/NSSharingServicePickerToolbarItem.h>

@class UITitlebar, NSToolbar, UIBarButtonItem;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UITitlebarTitleVisibility) {
    UITitlebarTitleVisibilityVisible,   // The title will be visible on top of the toolbar if there is one
    UITitlebarTitleVisibilityHidden     // No title will be visible. Window chrome will only appear if there is a toolbar
} API_AVAILABLE(macCatalyst(13.0));

@interface UIWindowScene (NSToolbarAdditions)
@property (nonatomic, readonly, nullable) UITitlebar *titlebar API_AVAILABLE(macCatalyst(13.0));
@end

API_AVAILABLE(macCatalyst(13.0))
@interface UITitlebar : NSObject

/*
 The visible state of the title of the titlebar.
 If the value is UITitlebarVisiblityHidden and there is no toolbar, the result will hide any window chrome at the top of the window.
 Defaults to UITitlebarVisiblityVisible.
 */
@property UITitlebarTitleVisibility titleVisibility;

/*
 Sets and gets the NSToolbar displayed at the top of the NSWindow associated with this scene
 */
@property (nonatomic, nullable, strong) NSToolbar *toolbar;

/*
 When set and the window enters fullscreen mode, the toolbar is detached from the window and hides and shows with the menu bar.
 */
@property (nonatomic) BOOL autoHidesToolbarInFullScreen;

/*
 If representedURL is not nil and its path is not empty, the window will show a document icon in the titlebar.
 If the url represents a filename or other resource with a known icon, that icon will be used as the document icon.  Otherwise the default document icon will be used. If url is not nil and its path is not empty, the window will have a pop-up menu which can be shown via command-click on the area containing the document icon and title.  By default, this menu will display the path components of the url. If the url is nil or has an empty path, the window will not show a document icon and will not have a pop-up menu available via command-click.
 */
@property (nonatomic, nullable, copy) NSURL *representedURL;

@end

@interface NSToolbarItem (NSToolbarAdditions)
/*
 Constructs a standard NSToolbarItem as a button with values from a UIBarButtonItem.
 UIBarButtonItems configured with custom views will not be honored.
 The NSToolbarItem will be populated with the -title and/or -image from the UIBarButtonItem.
 UIBarButtonItems with a UIBarButtonSystemItem will be appropriately configured as well.
 */
+ (instancetype)itemWithItemIdentifier:(NSToolbarItemIdentifier)itemIdentifier barButtonItem:(UIBarButtonItem *)barButtonItem API_AVAILABLE(macCatalyst(13.0));

/*
 When the window is too small to display an item, it will be clipped but remain accessible from a "clipped items" menu containing the menu item returned here.
 Singleton menu items will be clickable, while submenu items will be represented as a pull down.
 By default, this method returns a singleton menu item with item label as the title. For standard items, the target, action is set.
 */
@property (nonatomic, nullable, copy) UIMenuElement *itemMenuFormRepresentation API_AVAILABLE(macCatalyst(13.0));
@end

@interface NSMenuToolbarItem (NSToolbarAdditions)
/*
 The menu presented to the user from the item.
 If the item has an action, an arrow will be shown to the user next to the button to access the menu.
 This will also be shown as the actionMenuFormRepresentation unless otherwise set.
 */
@property (nonatomic, copy) UIMenu *itemMenu API_AVAILABLE(macCatalyst(13.0));
@end

@interface NSSharingServicePickerToolbarItem (UIActivityItemsConfiguration)

@property (nonatomic, strong, nullable) id<UIActivityItemsConfigurationReading> activityItemsConfiguration API_AVAILABLE(macCatalyst(13.0));

@end

NS_ASSUME_NONNULL_END

#endif

#else
#import <UIKitCore/NSToolbar+UIKitAdditions.h>
#endif
