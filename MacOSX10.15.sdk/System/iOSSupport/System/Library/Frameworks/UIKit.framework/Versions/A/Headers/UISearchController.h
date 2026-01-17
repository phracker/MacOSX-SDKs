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

NS_ASSUME_NONNULL_BEGIN

@class UISearchController;

@protocol UISearchControllerDelegate <NSObject>
@optional
// These methods are called when automatic presentation or dismissal occurs. They will not be called if you present or dismiss the search controller yourself.
- (void)willPresentSearchController:(UISearchController *)searchController;
- (void)didPresentSearchController:(UISearchController *)searchController;
- (void)willDismissSearchController:(UISearchController *)searchController;
- (void)didDismissSearchController:(UISearchController *)searchController;

// Called after the search controller's search bar has agreed to begin editing or when 'active' is set to YES. If you choose not to present the controller yourself or do not implement this method, a default presentation is performed on your behalf.
- (void)presentSearchController:(UISearchController *)searchController;
@end

@protocol UISearchResultsUpdating <NSObject>
@required
// Called when the search bar's text or scope has changed or when the search bar becomes first responder.
- (void)updateSearchResultsForSearchController:(UISearchController *)searchController;
@end

UIKIT_EXTERN API_AVAILABLE(ios(8.0)) @interface UISearchController : UIViewController <UIViewControllerTransitioningDelegate, UIViewControllerAnimatedTransitioning>

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
@property (nonatomic, assign) BOOL dimsBackgroundDuringPresentation API_UNAVAILABLE(tvos) API_DEPRECATED_WITH_REPLACEMENT("obscuresBackgroundDuringPresentation", ios(8.0,12.0)); // default is YES, and has the same behavior as obscuresBackgroundDuringPresentation.
@property (nonatomic, assign) BOOL obscuresBackgroundDuringPresentation API_AVAILABLE(ios(9.1)); // default is YES. On tvOS, defaults to NO when contained in UISearchContainerViewController.
@property (nonatomic, assign) BOOL hidesNavigationBarDuringPresentation;     // default is YES

@property (nullable, nonatomic, strong, readonly) UIViewController *searchResultsController;

// You are free to become the search bar's delegate to monitor for text changes and button presses.
@property (nonatomic, strong, readonly) UISearchBar *searchBar;

@property (nonatomic) BOOL automaticallyShowsSearchResultsController API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos); // When true, UISearchController will automatically show its results controller based on the contents of its text property. Defaults to true. Setting the showsSearchResultsController property will change this property to false.
@property (nonatomic) BOOL showsSearchResultsController API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos); // Set this property to directly control the visibility of the search results controller. Setting this property changes the automaticallyShowsSearchResultsController property to false.

/* By default, UISearchController will show the search bar's cancel button when 
 search becomes active and hide it when search is dismissed.
 
 Clients can take over showing and hiding the cancel button by setting automaticallyShowsCancelButton to NO
 and using UISearchBar's showsCancelButton property to manage cancel button visibility.
 
 Additionally, setting the showsCancelButton property on the searchController's searchBar
 will change the UISearchController's automaticallyShowsCancelButton property to NO.
 */
@property (nonatomic) BOOL automaticallyShowsCancelButton API_AVAILABLE(ios(13.0)); // Default YES

/* By default, UISearchController will show the search bar's scope bar 
 (when there are at least two scope button titles for the search bar)
 when search becomes active and hide it when search is dismissed.
 
 Clients can take over showing and hiding the scope bar by setting automaticallyShowsScopeBar
 to NO and using UISearchBar's showsScopeBar property to manage scope bar visibility.
 
 Additionally, setting the showsScopeBar property on the searchController's searchBar
 will change the UISearchController's automaticallyShowsScopeBar property to NO.
 */
@property (nonatomic) BOOL automaticallyShowsScopeBar API_AVAILABLE(ios(13.0)); // Defaults to YES
@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UISearchController.h>
#endif
