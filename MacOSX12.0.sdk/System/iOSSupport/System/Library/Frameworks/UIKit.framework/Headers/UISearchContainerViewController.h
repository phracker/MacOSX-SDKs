#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISearchContainerViewController.h>)
//
//  UISearchContainerViewController.h
//  UIKit
//
//  Copyright © 2015-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIViewController.h>

NS_ASSUME_NONNULL_BEGIN

@class UISearchController;

// Use this container view controller for UISearchController containment or presentation on tvOS
UIKIT_CLASS_AVAILABLE_IOS_TVOS(9_1, 9_0) NS_SWIFT_UI_ACTOR
@interface UISearchContainerViewController : UIViewController
@property (nonatomic, strong, readonly) UISearchController *searchController;

- (instancetype)initWithSearchController:(UISearchController *)searchController;

@end
NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UISearchContainerViewController.h>
#endif
