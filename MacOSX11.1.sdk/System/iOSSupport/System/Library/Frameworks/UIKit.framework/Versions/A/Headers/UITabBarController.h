#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITabBarController.h>)
//
//  UITabBarController.h
//  UIKit
//
//  Copyright (c) 2007-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIViewController.h>
#import <UIKit/UIViewControllerTransitioning.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UITabBar.h>

NS_ASSUME_NONNULL_BEGIN

@class UIView, UIImage, UINavigationController, UITabBarItem;
@protocol UITabBarControllerDelegate;

/*!
 UITabBarController manages a button bar and transition view, for an application with multiple top-level modes.
 
 To use in your application, add its view to the view hierarchy, then add top-level view controllers in order.
 Most clients will not need to subclass UITabBarController.

 If more than five view controllers are added to a tab bar controller, only the first four will display.
 The rest will be accessible under an automatically generated More item.
 
 UITabBarController is rotatable if all of its view controllers are rotatable.
 */

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) @interface UITabBarController : UIViewController <UITabBarDelegate, NSCoding>

@property(nullable, nonatomic,copy) NSArray<__kindof UIViewController *> *viewControllers;
// If the number of view controllers is greater than the number displayable by a tab bar, a "More" navigation controller will automatically be shown.
// The "More" navigation controller will not be returned by -viewControllers, but it may be returned by -selectedViewController.
- (void)setViewControllers:(NSArray<__kindof UIViewController *> * __nullable)viewControllers animated:(BOOL)animated;

@property(nullable, nonatomic, assign) __kindof UIViewController *selectedViewController; // This may return the "More" navigation controller if it exists.
@property(nonatomic) NSUInteger selectedIndex;

@property(nonatomic, readonly) UINavigationController *moreNavigationController API_UNAVAILABLE(tvos); // Returns the "More" navigation controller, creating it if it does not already exist.
@property(nullable, nonatomic, copy) NSArray<__kindof UIViewController *> *customizableViewControllers API_UNAVAILABLE(tvos); // If non-nil, then the "More" view will include an "Edit" button that displays customization UI for the specified controllers. By default, all view controllers are customizable.

@property(nonatomic,readonly) UITabBar *tabBar API_AVAILABLE(ios(3.0)); // Provided for -[UIActionSheet showFromTabBar:]. Attempting to modify the contents of the tab bar directly will throw an exception.

@property(nullable, nonatomic,weak) id<UITabBarControllerDelegate> delegate;

@end

@protocol UITabBarControllerDelegate <NSObject>
@optional
- (BOOL)tabBarController:(UITabBarController *)tabBarController shouldSelectViewController:(UIViewController *)viewController API_AVAILABLE(ios(3.0));
- (void)tabBarController:(UITabBarController *)tabBarController didSelectViewController:(UIViewController *)viewController;

- (void)tabBarController:(UITabBarController *)tabBarController willBeginCustomizingViewControllers:(NSArray<__kindof UIViewController *> *)viewControllers API_AVAILABLE(ios(3.0)) API_UNAVAILABLE(tvos);
- (void)tabBarController:(UITabBarController *)tabBarController willEndCustomizingViewControllers:(NSArray<__kindof UIViewController *> *)viewControllers changed:(BOOL)changed API_AVAILABLE(ios(3.0)) API_UNAVAILABLE(tvos);
- (void)tabBarController:(UITabBarController *)tabBarController didEndCustomizingViewControllers:(NSArray<__kindof UIViewController *> *)viewControllers changed:(BOOL)changed API_UNAVAILABLE(tvos);

- (UIInterfaceOrientationMask)tabBarControllerSupportedInterfaceOrientations:(UITabBarController *)tabBarController API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(tvos);
- (UIInterfaceOrientation)tabBarControllerPreferredInterfaceOrientationForPresentation:(UITabBarController *)tabBarController API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(tvos);

- (nullable id <UIViewControllerInteractiveTransitioning>)tabBarController:(UITabBarController *)tabBarController
                      interactionControllerForAnimationController: (id <UIViewControllerAnimatedTransitioning>)animationController API_AVAILABLE(ios(7.0));

- (nullable id <UIViewControllerAnimatedTransitioning>)tabBarController:(UITabBarController *)tabBarController
            animationControllerForTransitionFromViewController:(UIViewController *)fromVC
                                              toViewController:(UIViewController *)toVC  API_AVAILABLE(ios(7.0));

@end

@interface UIViewController (UITabBarControllerItem)

@property(null_resettable, nonatomic, strong) UITabBarItem *tabBarItem; // Automatically created lazily with the view controller's title if it's not set explicitly.

@property(nullable, nonatomic, readonly, strong) UITabBarController *tabBarController; // If the view controller has a tab bar controller as its ancestor, return it. Returns nil otherwise.

@property(nullable, nonatomic, strong) UIScrollView *tabBarObservedScrollView API_AVAILABLE(tvos(13.0)) API_UNAVAILABLE(ios, watchos); // Set this property to the full screen scroll view on the tab's top-level view controller, if one exists.

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UITabBarController.h>
#endif
