#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITableViewController.h>)
//
//  UITableViewController.h
//  UIKit
//
//  Copyright (c) 2008-2018 Apple Inc. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <UIKit/UIViewController.h>
#import <UIKit/UITableView.h>
#import <UIKit/UIKitDefines.h>

// Creates a table view with the correct dimensions and autoresizing, setting the datasource and delegate to self.
// In -viewWillAppear:, it reloads the table's data if it's empty. Otherwise, it deselects all rows (with or without animation) if clearsSelectionOnViewWillAppear is YES.
// In -viewDidAppear:, it flashes the table's scroll indicators.
// Implements -setEditing:animated: to toggle the editing state of the table.

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) NS_SWIFT_UI_ACTOR
@interface UITableViewController : UIViewController <UITableViewDelegate, UITableViewDataSource>

- (instancetype)initWithStyle:(UITableViewStyle)style NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@property (nonatomic, strong, null_resettable) UITableView *tableView;
@property (nonatomic) BOOL clearsSelectionOnViewWillAppear API_AVAILABLE(ios(3.2)); // defaults to YES. If YES, any selection is cleared in viewWillAppear:

@property (nonatomic, strong, nullable) UIRefreshControl *refreshControl API_AVAILABLE(ios(6.0)) API_UNAVAILABLE(tvos);

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UITableViewController.h>
#endif
