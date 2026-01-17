#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIViewControllerTransition.h>)
//
//  UIViewControllerTransition.h
//  UIKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIZoomTransitionOptions.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIView, UIViewController, UIZoomTransitionSourceViewProviderContext, UIBarButtonItem;

UIKIT_EXTERN API_AVAILABLE(ios(18.0)) API_UNAVAILABLE(watchos)
NS_SWIFT_NAME(UIViewController.Transition)
@interface UIViewControllerTransition : NSObject

/// Zoom from the view provided by the `sourceViewProvider` to the presented or pushed view controller's view.
/// The transition's `sourceViewProvider` is called whenever the transition needs to request a source view.
/// Note that it may be called multiple times during the transition's lifecycle in order
/// to ensure that the transition incorporates the most up-to-date visuals.
///
/// **Example**
///
/// Consider an interface where a user may tap a cell representing a city to present a detail view.
/// In the detail view, they may swipe left or right to go to the next city in the list. When the detail view
/// is dismissed, it should un-zoom to the currently selected city rather than the one that was first selected.
/// ```
/// cityViewController.preferredTransition = .zoom { context in
///     let displayed = context.displayedViewController as! CityViewController
///     let source = context.sourceViewController as! CityListViewController
///     return source.cell(for: displayed.cityId)
/// }
/// present(cityViewController, animated: true)
/// ```
+ (instancetype)zoomWithOptions:(nullable UIZoomTransitionOptions *)options sourceViewProvider:(UIView * _Nullable (^)(UIZoomTransitionSourceViewProviderContext *))sourceViewProvider NS_REFINED_FOR_SWIFT;

/// Zoom from the `UIBarButtonItem` provided by the `sourceBarButtonItemProvider` to the presented or pushed view controller's view.
+ (instancetype)zoomWithOptions:(nullable UIZoomTransitionOptions *)options sourceBarButtonItemProvider:(UIBarButtonItem * _Nullable (^)(UIZoomTransitionSourceViewProviderContext *))sourceBarButtonItemProvider API_AVAILABLE(ios(26.0)) NS_REFINED_FOR_SWIFT;

/// View slides up from the bottom of the screen. Same as `UIModalTransitionStyle.coverVertical`.
+ (instancetype)coverVerticalTransition NS_REFINED_FOR_SWIFT;

/// View flips horizontally in 3D. Same as `UIModalTransitionStyle.flipHorizontal`.
+ (instancetype)flipHorizontalTransition NS_REFINED_FOR_SWIFT;

/// Fades out the current view while fading in the new view. Same as `UIModalTransitionStyle.crossDissolve`.
+ (instancetype)crossDissolveTransition NS_REFINED_FOR_SWIFT;

/// One corner of the current view curls up to reveal the presented view underneath. Same as `UIModalTransitionStyle.partialCurl`.
+ (instancetype)partialCurlTransition NS_REFINED_FOR_SWIFT;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end


UIKIT_EXTERN API_AVAILABLE(ios(18.0)) API_UNAVAILABLE(watchos)
NS_SWIFT_NAME(UIViewControllerTransition.ZoomSourceViewProviderContext)
@interface UIZoomTransitionSourceViewProviderContext : NSObject

/// View controller that is the source of the zoom transition.
@property (nonatomic, strong, readonly) UIViewController *sourceViewController;

/// The view controller being zoomed into by the transition.
@property (nonatomic, strong, readonly) UIViewController *zoomedViewController;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end



NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIViewControllerTransition.h>
#endif
