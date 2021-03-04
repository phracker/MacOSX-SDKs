#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UINavigationItem.h>)
//
//  UINavigationItem.h
//  UIKit
//
//  Copyright © 2016-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIBarButtonItem.h>

@class UISearchController, UINavigationBarAppearance;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UINavigationItemLargeTitleDisplayMode) {
    /// Automatically use the large out-of-line title based on the state of the previous item in the navigation bar. An item with largeTitleDisplayMode=Automatic will show or hide the large title based on the request of the previous navigation item. If the first item pushed is set to Automatic, then it will show the large title if the navigation bar has prefersLargeTitles=YES.
    UINavigationItemLargeTitleDisplayModeAutomatic,
    /// Always use a larger title when this item is topmost.
    UINavigationItemLargeTitleDisplayModeAlways,
    /// Never use a larger title when this item is topmost.
    UINavigationItemLargeTitleDisplayModeNever,
} NS_SWIFT_NAME(UINavigationItem.LargeTitleDisplayMode);

typedef NS_ENUM(NSInteger, UINavigationItemBackButtonDisplayMode) {
    /// Default mode, uses an appropriate title, followed by a generic title (typically 'Back'), then no title.
    UINavigationItemBackButtonDisplayModeDefault = 0,
    /// Generic titles only. Ignores .title and .backButtonTitle (but *not* .backBarButtonItem.title).
    UINavigationItemBackButtonDisplayModeGeneric = 1,
    /// Don't use a title, just the back button indicator image.
    UINavigationItemBackButtonDisplayModeMinimal = 2,
} NS_SWIFT_NAME(UINavigationItem.BackButtonDisplayMode);

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) @interface UINavigationItem : NSObject <NSCoding>

- (instancetype)initWithTitle:(NSString *)title NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/// Title when topmost on the stack. default is nil
@property (nonatomic, readwrite, copy, nullable) NSString *title;
/// Custom view to use in lieu of a title. May be sized horizontally. Only used when item is topmost on the stack.
@property (nonatomic, readwrite, strong, nullable) UIView *titleView;
/// Explanatory text to display above the navigation bar buttons.
@property (nonatomic, readwrite, copy, nullable) NSString *prompt API_UNAVAILABLE(tvos);
/// Bar button item to use for the back button when this item is the navigation bar's backItem.
@property (nonatomic, readwrite, strong, nullable) UIBarButtonItem *backBarButtonItem API_UNAVAILABLE(tvos);
/// Title to use when this item is the navigation bar's backItem. Default is nil. backBarButtonItem takes precedence if both are specified.
@property (nonatomic, readwrite, copy, nullable) NSString *backButtonTitle API_AVAILABLE(ios(11.0));
/// If YES, this navigation item will hide the back button when it's on top of the stack.
@property (nonatomic, readwrite, assign) BOOL hidesBackButton API_UNAVAILABLE(tvos);
- (void)setHidesBackButton:(BOOL)hidesBackButton animated:(BOOL)animated API_UNAVAILABLE(tvos);
/// Controls how the back button sources its title.
@property (nonatomic, readwrite, assign) UINavigationItemBackButtonDisplayMode backButtonDisplayMode API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos);

/* Use these properties to set multiple items in a navigation bar.
 The older single properties (leftBarButtonItem and rightBarButtonItem) now refer to
 the first item in the respective array of items.
 
 NOTE: You'll achieve the best results if you use either the singular properties or
 the plural properties consistently and don't try to mix them.
 
 leftBarButtonItems are placed in the navigation bar left to right with the first
 item in the list at the left outside edge and left aligned.
 rightBarButtonItems are placed right to left with the first item in the list at
 the right outside edge and right aligned.
 */
@property (nonatomic, readwrite, copy, nullable) NSArray<UIBarButtonItem *> *leftBarButtonItems API_AVAILABLE(ios(5.0));
@property (nonatomic, readwrite, copy, nullable) NSArray<UIBarButtonItem *> *rightBarButtonItems API_AVAILABLE(ios(5.0));
- (void)setLeftBarButtonItems:(nullable NSArray<UIBarButtonItem *> *)items animated:(BOOL)animated API_AVAILABLE(ios(5.0));
- (void)setRightBarButtonItems:(nullable NSArray<UIBarButtonItem *> *)items animated:(BOOL)animated API_AVAILABLE(ios(5.0));

/* By default, the leftItemsSupplementBackButton property is NO. In this case,
 the back button is not drawn and the left item or items replace it. If you
 would like the left items to appear in addition to the back button (as opposed to instead of it)
 set leftItemsSupplementBackButton to YES.
 */
@property (nonatomic, readwrite, assign) BOOL leftItemsSupplementBackButton API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(tvos);

/// Some navigation items want to display a custom left or right item when they're on top of the stack. A custom left item replaces the regular back button unless you set leftItemsSupplementBackButton to YES
@property(nonatomic, readwrite, strong, nullable) UIBarButtonItem *leftBarButtonItem;
@property(nonatomic, readwrite, strong, nullable) UIBarButtonItem *rightBarButtonItem;
- (void)setLeftBarButtonItem:(nullable UIBarButtonItem *)item animated:(BOOL)animated;
- (void)setRightBarButtonItem:(nullable UIBarButtonItem *)item animated:(BOOL)animated;

/// When UINavigationBar.prefersLargeTitles=YES, this property controls when the larger out-of-line title is displayed. If prefersLargeTitles=NO, this property has no effect. The default value is Automatic.
@property (nonatomic, readwrite, assign) UINavigationItemLargeTitleDisplayMode largeTitleDisplayMode API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos);

/// A view controller that will be shown inside of a navigation controller can assign a UISearchController to this property to display the search controller’s search bar in its containing navigation controller’s navigation bar.
@property (nonatomic, readwrite, strong, nullable) UISearchController *searchController API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos);

/// If this property is true (the default), the searchController’s search bar will hide as the user scrolls in the top view controller’s scroll view. If false, the search bar will remain visible and pinned underneath the navigation bar.
@property (nonatomic, readwrite, assign) BOOL hidesSearchBarWhenScrolling API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos);

///  When set and this item is topmost, overrides the hosting navigation bar's standardAppearance. See UINavigationBar.standardAppearance for further details.
@property (nonatomic, readwrite, copy, nullable) UINavigationBarAppearance *standardAppearance API_AVAILABLE(ios(13.0), tvos(13.0));
///  When set and this item is topmost, overrides the hosting navigation bar's compactAppearance. See UINavigationBar.compactAppearance for further details.
@property (nonatomic, readwrite, copy, nullable) UINavigationBarAppearance *compactAppearance API_AVAILABLE(ios(13.0));
///  When set and this item is topmost, overrides the hosting navigation bar's scrollEdgeAppearance. See UINavigationBar.scrollEdgeAppearance for further details.
@property (nonatomic, readwrite, copy, nullable) UINavigationBarAppearance *scrollEdgeAppearance API_AVAILABLE(ios(13.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UINavigationItem.h>
#endif
