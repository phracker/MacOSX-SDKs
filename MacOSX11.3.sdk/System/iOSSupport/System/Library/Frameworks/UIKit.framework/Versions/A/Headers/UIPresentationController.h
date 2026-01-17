#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIPresentationController.h>)
//
//  UIPresentationController.h
//  UIKit
//
//  Copyright (c) 2014-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIApplication.h>
#import <UIKit/UIViewController.h>
#import <UIKit/UIAppearance.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UITraitCollection.h>
#import <UIKit/UIViewControllerTransitionCoordinator.h>
#import <UIKit/UIFocus.h>

NS_ASSUME_NONNULL_BEGIN

@class UIPresentationController;

@protocol UIAdaptivePresentationControllerDelegate <NSObject>

@optional

// For iOS 8.0, the only supported adaptive presentation styles are UIModalPresentationFullScreen and UIModalPresentationOverFullScreen.
- (UIModalPresentationStyle)adaptivePresentationStyleForPresentationController:(UIPresentationController *)controller;

// Returning UIModalPresentationNone will indicate that an adaptation should not happen.
- (UIModalPresentationStyle)adaptivePresentationStyleForPresentationController:(UIPresentationController *)controller traitCollection:(UITraitCollection *)traitCollection API_AVAILABLE(ios(8.3));

// If this method is not implemented, or returns nil, then the originally presented view controller is used.
- (nullable UIViewController *)presentationController:(UIPresentationController *)controller viewControllerForAdaptivePresentationStyle:(UIModalPresentationStyle)style;

// If there is no adaptation happening and an original style is used UIModalPresentationNone will be passed as an argument.
- (void)presentationController:(UIPresentationController *)presentationController willPresentWithAdaptiveStyle:(UIModalPresentationStyle)style transitionCoordinator:(nullable id <UIViewControllerTransitionCoordinator>)transitionCoordinator API_AVAILABLE(ios(8.3));

// Called on the delegate when the presentation controller will dismiss in response to user action.
// This method is not called if the presentedViewController isModalInPresentation or if the presentation is dismissed programatically.
// Return NO to prevent dismissal of the view controller.
- (BOOL)presentationControllerShouldDismiss:(UIPresentationController *)presentationController API_AVAILABLE(ios(13.0));

// Called on the delegate when the user has taken action to dismiss the presentation, before interaction or animations begin.
// Use this callback to setup alongside animations or interaction notifications with the presentingViewController's transitionCoordinator.
// This is not called if the presentation is dismissed programatically.
- (void)presentationControllerWillDismiss:(UIPresentationController *)presentationController API_AVAILABLE(ios(13.0));

// Called on the delegate when the user has taken action to dismiss the presentation successfully, after all animations are finished.
// This is not called if the presentation is dismissed programatically.
- (void)presentationControllerDidDismiss:(UIPresentationController *)presentationController API_AVAILABLE(ios(13.0));

// Called on the delegate when the user attempts to dismiss the presentation, but user-initiated dismissal is prevented because the presentedViewController isModalInPresentation or presentationControllerShouldDismiss: returned NO.
// When this method is called, it is recommended that the user be informed why they cannot dismiss the presentation, such as by presenting an instance of UIAlertController.
- (void)presentationControllerDidAttemptToDismiss:(UIPresentationController *)presentationController API_AVAILABLE(ios(13.0));

@end

UIKIT_EXTERN API_AVAILABLE(ios(8.0)) @interface UIPresentationController : NSObject <UIAppearanceContainer, UITraitEnvironment, UIContentContainer, UIFocusEnvironment>

@property(nonatomic, strong, readonly) UIViewController *presentingViewController;
@property(nonatomic, strong, readonly) UIViewController *presentedViewController;

@property(nonatomic, readonly) UIModalPresentationStyle presentationStyle;

// The view in which a presentation occurs. It is an ancestor of both the presenting and presented view controller's views.
// This view is being passed to the animation controller.
@property(nullable, nonatomic, readonly, strong) UIView *containerView;

@property(nullable, nonatomic, weak) id <UIAdaptivePresentationControllerDelegate> delegate;

- (instancetype)initWithPresentedViewController:(UIViewController *)presentedViewController presentingViewController:(nullable UIViewController *)presentingViewController NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

// By default this implementation defers to the delegate, if one exists, or returns the current presentation style. UIFormSheetPresentationController, and
// UIPopoverPresentationController override this implementation to return UIModalPresentationStyleFullscreen if the delegate does not provide an
// implementation for adaptivePresentationStyleForPresentationController:
@property(nonatomic, readonly) UIModalPresentationStyle adaptivePresentationStyle;
- (UIModalPresentationStyle)adaptivePresentationStyleForTraitCollection:(UITraitCollection *)traitCollection API_AVAILABLE(ios(8.3));

- (void)containerViewWillLayoutSubviews;
- (void)containerViewDidLayoutSubviews;

// A view that's going to be animated during the presentation. Must be an ancestor of a presented view controller's view
// or a presented view controller's view itself.
// (Default: presented view controller's view)
@property(nonatomic, readonly, nullable) UIView *presentedView;

// Position of the presented view in the container view by the end of the presentation transition.
// (Default: container view bounds)
@property(nonatomic, readonly) CGRect frameOfPresentedViewInContainerView;

// By default each new presentation is full screen.
// This behavior can be overridden with the following method to force a current context presentation.
// (Default: YES)
@property(nonatomic, readonly) BOOL shouldPresentInFullscreen;

// Indicate whether the view controller's view we are transitioning from will be removed from the window in the end of the
// presentation transition
// (Default: NO)
@property(nonatomic, readonly) BOOL shouldRemovePresentersView;

- (void)presentationTransitionWillBegin;
- (void)presentationTransitionDidEnd:(BOOL)completed;
- (void)dismissalTransitionWillBegin;
- (void)dismissalTransitionDidEnd:(BOOL)completed;

// Modifies the trait collection for the presentation controller.
@property(nullable, nonatomic, copy) UITraitCollection *overrideTraitCollection;

@end

NS_ASSUME_NONNULL_END


#else
#import <UIKitCore/UIPresentationController.h>
#endif
