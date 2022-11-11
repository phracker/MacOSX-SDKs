#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIPopoverPresentationController.h>)
//
//  UIPopoverPresentationController.h
//  UIKit
//
//  Copyright (c) 2014-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIPresentationController.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIPopoverSupport.h>
#import <UIKit/UIPopoverBackgroundView.h>

NS_ASSUME_NONNULL_BEGIN

@class UIPopoverPresentationController, UISheetPresentationController;

API_UNAVAILABLE(tvos) NS_SWIFT_UI_ACTOR
@protocol UIPopoverPresentationControllerDelegate <UIAdaptivePresentationControllerDelegate>
@optional

- (void)prepareForPopoverPresentation:(UIPopoverPresentationController *)popoverPresentationController;

// Called on the delegate when the popover controller will dismiss the popover. Return NO to prevent the
// dismissal of the view.
- (BOOL)popoverPresentationControllerShouldDismissPopover:(UIPopoverPresentationController *)popoverPresentationController API_DEPRECATED_WITH_REPLACEMENT("presentationControllerShouldDismiss:", ios(8.0, 13.0));;

// Called on the delegate when the user has taken action to dismiss the popover. This is not called when the popover is dismissed programatically.
- (void)popoverPresentationControllerDidDismissPopover:(UIPopoverPresentationController *)popoverPresentationController API_DEPRECATED_WITH_REPLACEMENT("presentationControllerDidDismiss:", ios(8.0, 13.0));

// -popoverPresentationController:willRepositionPopoverToRect:inView: is called on your delegate when the
// popover may require a different view or rectangle.
- (void)popoverPresentationController:(UIPopoverPresentationController *)popoverPresentationController willRepositionPopoverToRect:(inout CGRect *)rect inView:(inout UIView  * __nonnull * __nonnull)view;

@end

UIKIT_EXTERN API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(tvos) NS_SWIFT_UI_ACTOR
@interface UIPopoverPresentationController : UIPresentationController

@property (nullable, nonatomic, weak) id <UIPopoverPresentationControllerDelegate> delegate;

@property (nonatomic, assign) UIPopoverArrowDirection permittedArrowDirections;

@property (nullable, nonatomic, strong) UIView *sourceView;

// The rectangle in the coordinate space of sourceView that the popover should point at. This property is ignored if a barButtonItem is set.
// Starting in iOS 13.2, a value of CGRectNull will cause the popover to point at the current frame of sourceView and automatically update when the size of sourceView changes. Prior to iOS 13.2, a null rectangle was not supported.
// The default value in iOS 13.2 is CGRectNull. Prior to iOS 13.2, the default value was CGRectZero.
@property (nonatomic, assign) CGRect sourceRect;

// By default, a popover is not allowed to overlap its source view rect.
// When this is set to YES, popovers with more content than available space are allowed to overlap the source view rect in order to accommodate the content.
@property (nonatomic, assign) BOOL canOverlapSourceViewRect API_AVAILABLE(ios(9.0));

@property (nullable, nonatomic, strong) UIBarButtonItem *barButtonItem;

// Returns the direction the arrow is pointing on a presented popover. Before presentation, this returns UIPopoverArrowDirectionUnknown.
@property (nonatomic, readonly) UIPopoverArrowDirection arrowDirection;

// By default, a popover disallows interaction with any view outside of the popover while the popover is presented.
// This property allows the specification of an array of UIView instances which the user is allowed to interact with
// while the popover is up.
@property (nullable, nonatomic, copy) NSArray<UIView *> *passthroughViews;

// Set popover background color. Set to nil to use default background color. Default is nil.
@property (nullable, nonatomic, copy) UIColor *backgroundColor;

// Clients may wish to change the available area for popover display. The default implementation of this method always
// returns a system defined inset from the edges of the display, and presentation of popovers always accounts
// for the status bar. The rectangle being inset is always expressed in terms of the current device orientation; (0, 0)
// is always in the upper-left of the device. This may require insets to change on device rotation.
@property (nonatomic, readwrite) UIEdgeInsets popoverLayoutMargins;

// Clients may customize the popover background chrome by providing a class which subclasses `UIPopoverBackgroundView`
// and which implements the required instance and class methods on that class.
@property (nullable, nonatomic, readwrite, strong) Class <UIPopoverBackgroundViewMethods> popoverBackgroundViewClass;

// The UISheetPresentationController instance this popover will adapt to in compact size classes. Access this instance to customize or adjust the adaptive sheet.
@property (nonatomic, readonly, strong) UISheetPresentationController *adaptiveSheetPresentationController API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(tvos, watchos);

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIPopoverPresentationController.h>
#endif
