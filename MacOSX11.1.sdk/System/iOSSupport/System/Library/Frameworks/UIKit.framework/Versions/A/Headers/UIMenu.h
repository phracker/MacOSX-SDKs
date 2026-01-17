#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIMenu.h>)
//
//  UIMenu.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIMenuElement.h>

typedef NSString *UIMenuIdentifier NS_SWIFT_NAME(UIMenu.Identifier) NS_TYPED_EXTENSIBLE_ENUM API_AVAILABLE(ios(13.0));

typedef NS_OPTIONS(NSUInteger, UIMenuOptions) {
    /// Show children inline in parent, instead of hierarchically
    UIMenuOptionsDisplayInline  = 1 << 0,

    /// Indicates whether the menu should be rendered with a destructive appearance in its parent
    UIMenuOptionsDestructive    = 1 << 1,
    
} NS_SWIFT_NAME(UIMenu.Options) API_AVAILABLE(ios(13.0));

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) @interface UIMenu : UIMenuElement

/// Unique identifier.
@property (nonatomic, readonly) UIMenuIdentifier identifier;

/// Options.
@property (nonatomic, readonly) UIMenuOptions options;

/// The menu's sub-elements and sub-menus. On iOS 14.0, elements of your own menus are mutable, -copying a menu will produce mutable elements, and UIKit will take immutable copies of menus it receives. Prior to iOS 14.0, menus are always fully immutable.
@property (nonatomic, readonly) NSArray<UIMenuElement *> *children;

/*!
 * @abstract Creates a UIMenu with an empty title, nil image, automatically generated identifier, and default options.
 *
 * @param children    The menu's action-based sub-elements and sub-menus.
 *
 * @return A new UIMenu.
 */
+ (UIMenu *)menuWithChildren:(NSArray<UIMenuElement *> *)children API_AVAILABLE(ios(14.0)) NS_SWIFT_UNAVAILABLE("Use init(title:image:identifier:options:children:) instead");

/*!
 * @abstract Creates a UIMenu with the given arguments.
 *
 * @param title       The menu's title.
 * @param children    The menu's action-based sub-elements and sub-menus.
 *
 * @return A new UIMenu.
 */
+ (UIMenu *)menuWithTitle:(NSString *)title
                 children:(NSArray<UIMenuElement *> *)children NS_SWIFT_UNAVAILABLE("Use init(title:image:identifier:options:children:) instead");

/*!
 * @abstract Creates a UIMenu with the given arguments.
 *
 * @param title       The menu's title.
 * @param image       Image to be displayed alongside the menu's title.
 * @param identifier  The menu's unique identifier. Pass nil to use an auto-generated identifier.
 * @param options     The menu's options.
 * @param children    The menu's action-based sub-elements and sub-menus.
 *
 * @return A new UIMenu.
 */
+ (UIMenu *)menuWithTitle:(NSString *)title
                    image:(nullable UIImage *)image
               identifier:(nullable UIMenuIdentifier)identifier
                  options:(UIMenuOptions)options
                 children:(NSArray<UIMenuElement *> *)children NS_SWIFT_UNAVAILABLE("Use init(title:image:identifier:options:children:) instead");

- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
 * @abstract Copies this menu and replaces its children.
 *
 * @param newChildren  The replacement children.
 *
 * @return A copy of this menu with updated children.
 */
- (UIMenu *)menuByReplacingChildren:(NSArray<UIMenuElement *> *)newChildren;

@end

/// -- Identifiers for top-level menus

/// Application menu top-level menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuApplication API_AVAILABLE(ios(13.0));

/// File menu top-level menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuFile API_AVAILABLE(ios(13.0));

/// Edit menu top-level menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuEdit API_AVAILABLE(ios(13.0));

/// View menu top-level menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuView API_AVAILABLE(ios(13.0));

/// Window menu top-level menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuWindow API_AVAILABLE(ios(13.0));

/// Help menu top-level menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuHelp API_AVAILABLE(ios(13.0));

/// -- Identifiers for Application submenus

/// About menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuAbout API_AVAILABLE(ios(13.0));

/// Preferences menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuPreferences API_AVAILABLE(ios(13.0));

/// Services menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuServices API_AVAILABLE(ios(13.0));

/// Hide, Hide Others, Show All menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuHide API_AVAILABLE(ios(13.0));

/// Quit menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuQuit API_AVAILABLE(ios(13.0));

/// -- Identifiers for File submenus

/// New scene menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuNewScene API_AVAILABLE(ios(13.0));

/// Open Recent menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuOpenRecent API_AVAILABLE(ios(14.0));

/// Close menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuClose API_AVAILABLE(ios(13.0));

/// Print menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuPrint API_AVAILABLE(ios(13.0));

/// -- Identifiers for Edit submenus

/// Undo, Redo menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuUndoRedo API_AVAILABLE(ios(13.0));

/// Cut, Copy, Paste, Delete, Select, Select All menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuStandardEdit API_AVAILABLE(ios(13.0));

/// Find menu; empty in the default menubar configuration. Applications should use this when adding their own Find-related menu items.
UIKIT_EXTERN const UIMenuIdentifier UIMenuFind API_AVAILABLE(ios(13.0));

/// Replace..., Transliterate Chinese menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuReplace API_AVAILABLE(ios(13.0));

/// Share menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuShare API_AVAILABLE(ios(13.0));

/// Bold, Italics, Underline  menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuTextStyle API_AVAILABLE(ios(13.0));

/// Spelling menu contained within Edit menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuSpelling API_AVAILABLE(ios(13.0));

/// Show Spelling, Check Document Now menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuSpellingPanel API_AVAILABLE(ios(13.0));

/// Check Spelling While Typing and other spelling and grammar-checking options menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuSpellingOptions API_AVAILABLE(ios(13.0));

/// Substitutions menu contained within Edit menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuSubstitutions API_AVAILABLE(ios(13.0));

// Show Substitutions menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuSubstitutionsPanel API_AVAILABLE(ios(13.0));

/// Smart Copy, Smart Paste, Smart Quotes, and other substitution options menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuSubstitutionOptions API_AVAILABLE(ios(13.0));

/// Transformations menu contained within Edit menu (contains Make Uppercase, Make Lowercase, Capitalize)
UIKIT_EXTERN const UIMenuIdentifier UIMenuTransformations API_AVAILABLE(ios(13.0));

/// Speech menu contained within Edit menu (contains Speak, Speak..., Pause)
UIKIT_EXTERN const UIMenuIdentifier UIMenuSpeech API_AVAILABLE(ios(13.0));

/// Lookup menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuLookup API_AVAILABLE(ios(13.0));

/// Learn menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuLearn API_AVAILABLE(ios(13.0));

/// Format top-level menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuFormat API_AVAILABLE(ios(13.0));

/// Font menu contained within Format menu (contains UIMenuTextStyle)
UIKIT_EXTERN const UIMenuIdentifier UIMenuFont API_AVAILABLE(ios(13.0));

/// Bigger and Smaller menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuTextSize API_AVAILABLE(ios(13.0));

/// Show Colors menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuTextColor API_AVAILABLE(ios(13.0));

/// Copy Style and Paste Style menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuTextStylePasteboard API_AVAILABLE(ios(13.0));

/// Text menu contained within Format menu (contains UIMenuAlignment and UIMenuWritingDirection)
UIKIT_EXTERN const UIMenuIdentifier UIMenuText API_AVAILABLE(ios(13.0));

/// Default, Right to Left, Left to Right menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuWritingDirection API_AVAILABLE(ios(13.0));

/// Align Left, Center, Justify, Align Right menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuAlignment API_AVAILABLE(ios(13.0));

/// -- Identifiers for View submenus

/// Show/Hide and Customize Toolbar menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuToolbar API_AVAILABLE(ios(13.0));

/// Fullscreen menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuFullscreen API_AVAILABLE(ios(13.0));

/// -- Identifiers for Window submenus

/// Minimize, Zoom menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuMinimizeAndZoom API_AVAILABLE(ios(13.0));

/// Bring All to Front, Arrange in Front menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuBringAllToFront API_AVAILABLE(ios(13.0));

/// Root-level menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuRoot API_AVAILABLE(ios(13.0));

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIMenu.h>
#endif
