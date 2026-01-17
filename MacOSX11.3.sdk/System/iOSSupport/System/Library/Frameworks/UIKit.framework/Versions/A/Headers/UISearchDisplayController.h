#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISearchDisplayController.h>)
//
//  UISearchDisplayController.h
//  UIKit
//
//  Copyright (c) 2009-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UILabel.h>
#import <UIKit/UITableView.h>
#import <UIKit/UINavigationBar.h>

NS_ASSUME_NONNULL_BEGIN

@class UISearchBar, UITableView, UIViewController, UIPopoverController;
@protocol UITableViewDataSource, UITableViewDelegate, UISearchDisplayDelegate;

UIKIT_EXTERN API_DEPRECATED("UISearchDisplayController has been replaced with UISearchController", ios(3.0, 8.0)) API_UNAVAILABLE(tvos)
@interface UISearchDisplayController : NSObject

- (instancetype)initWithSearchBar:(UISearchBar *)searchBar contentsController:(UIViewController *)viewController;

@property(nullable,nonatomic,assign)                           id<UISearchDisplayDelegate> delegate;

@property(nonatomic,getter=isActive)  BOOL            active;  // configure the view controller for searching. default is NO. animated is NO
- (void)setActive:(BOOL)visible animated:(BOOL)animated;       // animate the view controller for searching

@property(nonatomic,readonly)                                  UISearchBar                *searchBar;
@property(nonatomic,readonly)                                  UIViewController           *searchContentsController; // the view we are searching (often a UITableViewController)
@property(nonatomic,readonly)                                  UITableView                *searchResultsTableView;   // will return non-nil. create if requested
@property(nullable,nonatomic,weak)                             id<UITableViewDataSource>  searchResultsDataSource;  // default is nil. delegate can provide
@property(nullable,nonatomic,weak)                             id<UITableViewDelegate>    searchResultsDelegate;    // default is nil. delegate can provide
@property(nullable,nonatomic,copy)                             NSString                   *searchResultsTitle API_AVAILABLE(ios(5.0)); // default is nil. If nil, the controller uses the default title string

/* Displaying the search bar in a navigation bar will override the contentsController's navigationItem if it has one. */
@property (nonatomic, assign) BOOL displaysSearchBarInNavigationBar API_AVAILABLE(ios(7.0));
@property (nullable, nonatomic, readonly) UINavigationItem *navigationItem API_AVAILABLE(ios(7.0));

@end

API_UNAVAILABLE(tvos)
@protocol UISearchDisplayDelegate <NSObject>

@optional

// when we start/end showing the search UI
- (void) searchDisplayControllerWillBeginSearch:(UISearchDisplayController *)controller API_DEPRECATED("", ios(3.0, 8.0));
- (void) searchDisplayControllerDidBeginSearch:(UISearchDisplayController *)controller API_DEPRECATED("", ios(3.0, 8.0));
- (void) searchDisplayControllerWillEndSearch:(UISearchDisplayController *)controller API_DEPRECATED("", ios(3.0, 8.0));
- (void) searchDisplayControllerDidEndSearch:(UISearchDisplayController *)controller API_DEPRECATED("", ios(3.0, 8.0));

// called when the table is created destroyed, shown or hidden. configure as necessary.
- (void)searchDisplayController:(UISearchDisplayController *)controller didLoadSearchResultsTableView:(UITableView *)tableView API_DEPRECATED("", ios(3.0, 8.0));
- (void)searchDisplayController:(UISearchDisplayController *)controller willUnloadSearchResultsTableView:(UITableView *)tableView API_DEPRECATED("", ios(3.0, 8.0));

// called when table is shown/hidden
- (void)searchDisplayController:(UISearchDisplayController *)controller willShowSearchResultsTableView:(UITableView *)tableView API_DEPRECATED("", ios(3.0, 8.0));
- (void)searchDisplayController:(UISearchDisplayController *)controller didShowSearchResultsTableView:(UITableView *)tableView API_DEPRECATED("", ios(3.0, 8.0));
- (void)searchDisplayController:(UISearchDisplayController *)controller willHideSearchResultsTableView:(UITableView *)tableView API_DEPRECATED("", ios(3.0, 8.0));
- (void)searchDisplayController:(UISearchDisplayController *)controller didHideSearchResultsTableView:(UITableView *)tableView API_DEPRECATED("", ios(3.0, 8.0));

// return YES to reload table. called when search string/option changes. convenience methods on top UISearchBar delegate methods
- (BOOL)searchDisplayController:(UISearchDisplayController *)controller shouldReloadTableForSearchString:(nullable NSString *)searchString API_DEPRECATED("", ios(3.0, 8.0));
- (BOOL)searchDisplayController:(UISearchDisplayController *)controller shouldReloadTableForSearchScope:(NSInteger)searchOption API_DEPRECATED("", ios(3.0, 8.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UISearchDisplayController.h>
#endif
