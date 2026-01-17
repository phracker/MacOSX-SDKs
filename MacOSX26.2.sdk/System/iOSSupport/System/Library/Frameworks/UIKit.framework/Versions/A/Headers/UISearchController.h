#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISearchController.h>)
//
//  UISearchController.h
//  UIKit
//
//  Copyright (c) 2014-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIPresentationController.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIViewControllerTransitioning.h>
#import <UIKit/UISearchBar.h>
#import <UIKit/UINavigationItem.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, UISearchControllerScopeBarActivation) {
    /// System-defined automatic showing and hiding of the scope bar
    UISearchControllerScopeBarActivationAutomatic,
    /// Showing and hiding the scope bar will be controlled by client code through the `showsScopeBar` API on the UISearchController's `searchBar`
    UISearchControllerScopeBarActivationManual,
    /// The search controller shows the scope bar when typing begins in the search field, and hides it when search is cancelled
    UISearchControllerScopeBarActivationOnTextEntry,
    /// The search controller shows the scope bar when search becomes active, and hides it when search is cancelled
    UISearchControllerScopeBarActivationOnSearchActivation,
} API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_NAME(UISearchController.ScopeBarActivation);

@class UISearchController;

API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UISearchControllerDelegate <NSObject>
@optional
// These methods are called when automatic presentation or dismissal occurs. They will not be called if you present or dismiss the search controller yourself.
- (void)willPresentSearchController:(UISearchController *)searchController;
- (void)didPresentSearchController:(UISearchController *)searchController;
- (void)willDismissSearchController:(UISearchController *)searchController;
- (void)didDismissSearchController:(UISearchController *)searchController;

// Called after the search controller's search bar has agreed to begin editing or when 'active' is set to YES. If you choose not to present the controller yourself or do not implement this method, a default presentation is performed on your behalf.
- (void)presentSearchController:(UISearchController *)searchController;

- (void)searchController:(UISearchController *)searchController willChangeToSearchBarPlacement:(UINavigationItemSearchBarPlacement)newPlacement API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);
- (void)searchController:(UISearchController *)searchController didChangeFromSearchBarPlacement:(UINavigationItemSearchBarPlacement)previousPlacement API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);
@end

@protocol UISearchSuggestion;

API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UISearchResultsUpdating <NSObject>
@required
// Called when the search bar's text or scope has changed or when the search bar becomes first responder.
- (void)updateSearchResultsForSearchController:(UISearchController *)searchController;
@optional
// Called when user selects one of the search suggestion buttons displayed under the keyboard on tvOS.
- (void)updateSearchResultsForSearchController:(nonnull UISearchController *)searchController selectingSearchSuggestion:(nonnull id<UISearchSuggestion>)searchSuggestion API_AVAILABLE(tvos(14.0), ios(16.0)) API_UNAVAILABLE(watchos);
@end

UIKIT_EXTERN API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UISearchController : UIViewController <UIViewControllerTransitioningDelegate, UIViewControllerAnimatedTransitioning>

// Pass nil if you wish to display search results in the same view that you are searching. This is not supported on tvOS; please provide a results controller on tvOS.
- (instancetype)initWithSearchResultsController:(nullable UIViewController *)searchResultsController NS_DESIGNATED_INITIALIZER;

// Creates a search controller without a results controller
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_DESIGNATED_INITIALIZER;

- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

// The object responsible for updating the content of the searchResultsController.
@property (nullable, nonatomic, weak) id <UISearchResultsUpdating> searchResultsUpdater;

// Setting this property to YES is a convenience method that performs a default presentation of the search controller appropriate for how the controller is configured. Implement -presentSearchController: if the default presentation is not adequate.
@property (nonatomic, assign, getter = isActive) BOOL active;

@property (nullable, nonatomic, weak) id <UISearchControllerDelegate> delegate;
@property (nonatomic, assign) BOOL dimsBackgroundDuringPresentation API_DEPRECATED_WITH_REPLACEMENT("obscuresBackgroundDuringPresentation", ios(8.0, 12.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos); // default is YES, and has the same behavior as obscuresBackgroundDuringPresentation.

/* On iOS, default is NO for apps linked on iOS 15.0 and later, YES otherwise.
 On tvOS, default is NO when contained in UISearchContainerViewController, YES otherwise.
 */
@property (nonatomic, assign) BOOL obscuresBackgroundDuringPresentation API_AVAILABLE(ios(9.1));

/// Default is `YES` for apps linked before iOS 26.0, other than on MacCatalyst, where the default is `NO`.
/// On iOS 26.0 for apps linked on iOS 26.0 and later, the value is determined by context unless directly set through the API. The default remains `NO` on MacCatalyst.
@property (nonatomic, assign) BOOL hidesNavigationBarDuringPresentation;

@property (nullable, nonatomic, strong, readonly) UIViewController *searchResultsController;

// You are free to become the search bar's delegate to monitor for text changes and button presses.
@property (nonatomic, strong, readonly) UISearchBar *searchBar;

// For inspecting the current placement of the search bar when the search controller has been assigned to a UINavigationItem
@property (nonatomic, readonly) UINavigationItemSearchBarPlacement searchBarPlacement API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

@property (nonatomic) BOOL automaticallyShowsSearchResultsController API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos); // When true, UISearchController will automatically show its results controller based on the contents of its text property. Defaults to true. Setting the showsSearchResultsController property will change this property to false.
@property (nonatomic) BOOL showsSearchResultsController API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos); // Set this property to directly control the visibility of the search results controller. Setting this property changes the automaticallyShowsSearchResultsController property to false.

/* By default, UISearchController will show the search bar's cancel button when 
 search becomes active and hide it when search is dismissed.
 
 Clients can take over showing and hiding the cancel button by setting automaticallyShowsCancelButton to NO
 and using UISearchBar's showsCancelButton property to manage cancel button visibility.
 
 Additionally, setting the showsCancelButton property on the searchController's searchBar
 will change the UISearchController's automaticallyShowsCancelButton property to NO.
 */
@property (nonatomic) BOOL automaticallyShowsCancelButton API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos); // Default YES

/* By default, UISearchController will show the search bar's scope bar 
 (when there are at least two scope button titles for the search bar)
 when search becomes active and hide it when search is dismissed.
 
 Clients can take over showing and hiding the scope bar by setting automaticallyShowsScopeBar
 to NO and using UISearchBar's showsScopeBar property to manage scope bar visibility.
 
 Additionally, setting the showsScopeBar property on the searchController's searchBar
 will change the UISearchController's automaticallyShowsScopeBar property to NO.
 
 On iOS, this will be fully deprecated in a future release in favor of `scopeBarActivation`
 */
@property (nonatomic) BOOL automaticallyShowsScopeBar API_AVAILABLE(tvos(13.0)) API_DEPRECATED("Use scopeBarActivation instead", ios(13.0, API_TO_BE_DEPRECATED), visionos(1.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(watchos);

/// Controls if and when the UISearchController shows and hides the scope bar
/// However, UISearchBar will not show the scope bar if `scopeButtonTitles` contains fewer than two titles
/// Defaults to `UISearchControllerScopeBarActivationAutomatic`
/// `UISearchControllerScopeBarActivationAutomatic` is equivalent to earlier `automaticallyShowsScopeBar == YES`
/// `UISearchControllerScopeBarActivationManual` is equivalent to earlier `automaticallyShowsScopeBar == NO`
/// Similar to the behavior of `automaticallyShowsScopeBar`, setting the `showsScopeBar` property on the `searchController`'s `searchBar`
/// will change `scopeBarActivation` to `UISearchControllerScopeBarActivationManual`
@property (nonatomic) UISearchControllerScopeBarActivation scopeBarActivation API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

/// List of search hint objects to be displayed under keyboard on tvOS,
/// as a menu under the search field when the search bar is placed inline on iOS 16,
/// or as a list in front of the searchResultsController when the search bar is stacked.
/// Assigning with new array immediately updates the list on screen.
/// searchSuggestions is set to nil when user interaction selects a suggestion,
/// or when the user otherwise interacts with search (e.g., typing in the search field, choosing a different search scope, canceling search)
/// after dismissing the menu by tapping outside
@property (nonatomic, copy, nullable) NSArray<id<UISearchSuggestion>> *searchSuggestions API_AVAILABLE(tvos(14.0), ios(16.0)) API_UNAVAILABLE(watchos);

/// Default NO. When YES, the UISearchController will not create its internal child view controller
/// for presenting the list of search suggestions when the searchBarPlacement is stacked.
/// This property is intended to be set at the time that the search controller is initialized.
/// If set after that point, the internal view controller will not be destroyed, but its view will be hidden and remain so.
@property (nonatomic) BOOL ignoresSearchSuggestionsForSearchBarPlacementStacked API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos);

/* Deprecated on tvOS 15.0 in favor of  using -[UIViewController setContentScrollView:forEdge:]
 on the searchResultsController, passing the full-screen scroll view contained in the results view
 and NSDirectionalRectEdgeTop.
     
   If the search controller is embedded inside a tab bar controller, the tab bar controller
 will also observe this scroll view.
 */
@property(nullable, nonatomic, strong) UIScrollView *searchControllerObservedScrollView API_DEPRECATED("Use -[UIViewController setContentScrollView:forEdge:] on the searchResultsController instead.", tvos(13.0,API_TO_BE_DEPRECATED)) API_UNAVAILABLE(ios, watchos, visionos); // Set this property to the full screen scroll view in your results view on the results view controller, if one exists. If search controller is embedded inside a tab controller, this will forward the scroll view to the tab controller as tabBarObservedScrollView.

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UISearchController.h>
#endif
