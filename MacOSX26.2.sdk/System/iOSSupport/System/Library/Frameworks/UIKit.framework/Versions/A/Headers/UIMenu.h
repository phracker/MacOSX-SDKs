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
#import <UIKit/UIMenuDisplayPreferences.h>

typedef NSString *UIMenuIdentifier NS_SWIFT_NAME(UIMenu.Identifier) NS_TYPED_EXTENSIBLE_ENUM API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

typedef NS_OPTIONS(NSUInteger, UIMenuOptions) {
    /// Show children inline in parent, instead of hierarchically
    UIMenuOptionsDisplayInline  = 1 << 0,

    /// Indicates whether the menu should be rendered with a destructive appearance in its parent
    UIMenuOptionsDestructive    = 1 << 1,
    
    /// Indicates whether the menu (and any submenus) should only allow a single "on" menu item.
    UIMenuOptionsSingleSelection API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos) = 1 << 5,
    
    /// Indicates that this menu should be rendered as a palette.
    UIMenuOptionsDisplayAsPalette API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos) = 1 << 7,
    
} NS_SWIFT_NAME(UIMenu.Options) API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UIMenuElementSize) {
    UIMenuElementSizeSmall = 0,
    UIMenuElementSizeMedium,
    UIMenuElementSizeLarge,

    /// Automatically determine the appropriate element size for the current context.
    UIMenuElementSizeAutomatic API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos) = -1,
} API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos);

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIMenu : UIMenuElement

/// Unique identifier.
@property (nonatomic, readonly) UIMenuIdentifier identifier;

/// Options.
@property (nonatomic, readonly) UIMenuOptions options;

/// Size of this menu's child elements. This property has no effect on Mac Catalyst.
@property (nonatomic) UIMenuElementSize preferredElementSize API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos);

/// The menu's sub-elements and sub-menus. On iOS 14.0, elements of your own menus are mutable, -copying a menu will produce mutable elements, and UIKit will take immutable copies of menus it receives. Prior to iOS 14.0, menus are always fully immutable.
@property (nonatomic, readonly) NSArray<UIMenuElement *> *children;

/// The element(s) in the menu and sub-menus that have an "on" menu item state.
@property (nonatomic, readonly) NSArray <UIMenuElement *> *selectedElements API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos);

/// Display preferences for this menu's immediate children. Preferences are not inherited by sub menus,
/// and may be ignored or overridden by the system in certain element sizes or menu layouts.
@property (nonatomic, nullable, copy) UIMenuDisplayPreferences *displayPreferences API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(watchos);

/*!
 * @abstract Creates a UIMenu with an empty title, nil image, automatically generated identifier, and default options.
 *
 * @param children    The menu's action-based sub-elements and sub-menus.
 *
 * @return A new UIMenu.
 */
+ (UIMenu *)menuWithChildren:(NSArray<UIMenuElement *> *)children API_AVAILABLE(ios(14.0)) NS_SWIFT_UNAVAILABLE("Use init(title:image:identifier:options:children:) instead") API_UNAVAILABLE(watchos);

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
UIKIT_EXTERN const UIMenuIdentifier UIMenuApplication API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// File menu top-level menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuFile API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Edit menu top-level menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuEdit API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// View menu top-level menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuView API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Window menu top-level menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuWindow API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Help menu top-level menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuHelp API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// -- Identifiers for Application submenus

/// About menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuAbout API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Preferences menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuPreferences API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Services menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuServices API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Hide, Hide Others, Show All menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuHide API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Quit menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuQuit API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// -- Identifiers for File submenus

/// New item menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuNewItem API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos);

/// New scene menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuNewScene API_DEPRECATED_WITH_REPLACEMENT("UIMenuNewItem", ios(13.0, 26.0)) API_UNAVAILABLE(watchos);

/// Open menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuOpen API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);

/// Open Recent menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuOpenRecent API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos);

/// Close menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuClose API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Print menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuPrint API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Document-related menu items: Duplicate, Move, Rename, Export. The `.document` menu is added to Mac Catalyst applications by default. iOS Apps on the Mac will have the `.document` menu inserted when and if `UINavigationItem.titleMenuProvider` is set to a nonnull value, and from launch on subsequent executions.
UIKIT_EXTERN const UIMenuIdentifier UIMenuDocument API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos);

/// -- Identifiers for Edit submenus

/// Undo, Redo menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuUndoRedo API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Cut, Copy, Paste, Delete, Select, Select All menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuStandardEdit API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Find menu, containing Find Panel items and other finding operations like Use Selection for Find
UIKIT_EXTERN const UIMenuIdentifier UIMenuFind API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Find panel menu (Find, Find and Replace, Find Next, Find Previous)
UIKIT_EXTERN const UIMenuIdentifier UIMenuFindPanel API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos);

/// Replace..., Transliterate Chinese menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuReplace API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Share menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuShare API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Bold, Italics, Underline  menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuTextStyle API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Spelling menu contained within Edit menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuSpelling API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Show Spelling, Check Document Now menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuSpellingPanel API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Check Spelling While Typing and other spelling and grammar-checking options menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuSpellingOptions API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Substitutions menu contained within Edit menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuSubstitutions API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

// Show Substitutions menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuSubstitutionsPanel API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Smart Copy, Smart Paste, Smart Quotes, and other substitution options menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuSubstitutionOptions API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Transformations menu contained within Edit menu (contains Make Uppercase, Make Lowercase, Capitalize)
UIKIT_EXTERN const UIMenuIdentifier UIMenuTransformations API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Speech menu contained within Edit menu (contains Speak, Speak..., Pause)
UIKIT_EXTERN const UIMenuIdentifier UIMenuSpeech API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Lookup menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuLookup API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Learn menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuLearn API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Format top-level menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuFormat API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// AutoFill menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuAutoFill API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos);

/// Font menu contained within Format menu (contains UIMenuTextStyle)
UIKIT_EXTERN const UIMenuIdentifier UIMenuFont API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Bigger and Smaller menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuTextSize API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Show Colors menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuTextColor API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Copy Style and Paste Style menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuTextStylePasteboard API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Text menu contained within Format menu (contains UIMenuAlignment and UIMenuWritingDirection)
UIKIT_EXTERN const UIMenuIdentifier UIMenuText API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Default, Right to Left, Left to Right menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuWritingDirection API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Align Left, Center, Justify, Align Right menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuAlignment API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// -- Identifiers for View submenus

/// Show/Hide and Customize Toolbar menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuToolbar API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Sidebar menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuSidebar API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos);

/// Fullscreen menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuFullscreen API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// -- Identifiers for Window submenus

/// Minimize, Zoom menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuMinimizeAndZoom API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Bring All to Front, Arrange in Front menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuBringAllToFront API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

/// Root-level menu
UIKIT_EXTERN const UIMenuIdentifier UIMenuRoot API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIMenu.h>
#endif
