#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UILargeContentViewer.h>)
//
//  UILargeContentViewer.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIImage.h>
#import <UIKit/UIInteraction.h>
#import <UIKit/UIView.h>

#if TARGET_OS_IOS

NS_ASSUME_NONNULL_BEGIN

@protocol UILargeContentViewerInteractionDelegate;

// The large content viewer allow users with relevant settings to view content at a larger size.
// For example, users with an accessibility content size category can long press on a tab bar button to view a larger version.
// The viewer should not be used as a replacement for proper Dynamic Type support in general.
// It is intended only for use with items that must remain small due to unavoidable design constraints.
// For example, buttons in a tab bar remain small to leave more room for the main content.

API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos) @protocol UILargeContentViewerItem <NSObject>

/// Returns whether the item shows the large content viewer.
/// In general, only views that cannot scale for the full range of Dynamic Type sizes should return YES.
/// For this property to take effect, the item or an ancestor view must have a UILargeContentViewerInteraction.
@property (nonatomic, assign, readonly) BOOL showsLargeContentViewer;

/// Returns a title that should be shown in the large content viewer.
@property (nullable, nonatomic, copy, readonly) NSString *largeContentTitle;

/// Returns an image that should be shown in the large content viewer.
@property (nullable, nonatomic, strong, readonly) UIImage *largeContentImage;

/// Returns whether the image should be scaled to a larger size appropriate for the viewer.
/// If not, the image will be shown at its intrinsic size.
/// For best results when scaling, use a PDF asset with its "Preserve Vector Data" checkbox checked.
@property (nonatomic, assign, readonly) BOOL scalesLargeContentImage;

/// Returns insets appropriate for positioning the image in the viewer so that it appears visually centered.
@property (nonatomic, assign, readonly) UIEdgeInsets largeContentImageInsets;

@end

@interface UIView (UILargeContentViewer) <UILargeContentViewerItem>

// Defaults to NO.
@property (nonatomic, assign, readwrite) BOOL showsLargeContentViewer API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos);

// Defaults to nil, or an appropriate default value for UIKit classes.
@property (nullable, nonatomic, copy, readwrite) NSString *largeContentTitle API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos);

// Defaults to nil, or an appropriate default value for UIKit classes.
@property (nullable, nonatomic, strong, readwrite) UIImage *largeContentImage API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos);

// Defaults to NO, or an appropriate default value for UIKit classes.
@property (nonatomic, assign, readwrite) BOOL scalesLargeContentImage API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos);

// Defaults to UIEdgeInsetsZero.
@property (nonatomic, assign, readwrite) UIEdgeInsets largeContentImageInsets API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos);

@end

/// UILargeContentViewerInteraction enables a gesture to present and dismiss the large content viewer on a device with relevant settings.
/// Use methods in <UIKit/UIInteraction.h> to add the interaction to an appropriate view, such as a custom tab bar.
UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos) @interface UILargeContentViewerInteraction : NSObject <UIInteraction>

- (instancetype)initWithDelegate:(nullable id<UILargeContentViewerInteractionDelegate>)delegate NS_DESIGNATED_INITIALIZER;

@property (nonatomic, nullable, weak, readonly) id<UILargeContentViewerInteractionDelegate> delegate;

/// Returns a gesture recognizer that can be used to set up simultaneous recognition or failure relationships with other gesture recognizers.
@property (nonatomic, strong, readonly) UIGestureRecognizer *gestureRecognizerForExclusionRelationship;

/// Returns whether the large content viewer is enabled on the device.
/// It is not necessary to check this value before adding a UILargeContentViewerInteraction to a view,
/// but it may be helpful if you need to adjust the behavior of coexisting gesture handlers.
/// For example, a button with a long press handler might increase its long press duration,
/// so that a user can read text in the large content viewer first.
@property (class, nonatomic, readonly, getter=isEnabled) BOOL enabled;

@end

API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos) @protocol UILargeContentViewerInteractionDelegate <NSObject>

@optional

/// Performs an action when the large content viewer gesture ends at the location of the given item.
/// (The point in the interaction's view's coordinate system is also provided.)
/// For example, you may wish to perform the action that would have occurred if the user had tapped on that item.
/// If this is not implemented and the gesture ends at the location of a UIControl object, it will send a UIControlEventTouchUpInside event.
/// This method is called only if the gesture ends successfully (not if it fails or gets canceled).
- (void)largeContentViewerInteraction:(UILargeContentViewerInteraction *)interaction didEndOnItem:(nullable id<UILargeContentViewerItem>)item atPoint:(CGPoint)point;

/// Returns the item at a given point in the interaction's view's coordinate system.
/// If this is not implemented, -[UIView pointInside:withEvent:] will be called recursively on the interaction's view to find an appropriate view.
- (nullable id<UILargeContentViewerItem>)largeContentViewerInteraction:(UILargeContentViewerInteraction *)interaction itemAtPoint:(CGPoint)point;

/// Returns the view controller whose region of the screen should be used to display the large content viewer.
/// If this is not implemented, a view controller that contains the interaction's view will be chosen.
- (UIViewController *)viewControllerForLargeContentViewerInteraction:(UILargeContentViewerInteraction *)interaction;

@end

/// Posted when the large content viewer gets enabled or disabled on the device.
UIKIT_EXTERN NSNotificationName const UILargeContentViewerInteractionEnabledStatusDidChangeNotification API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos);

NS_ASSUME_NONNULL_END

#endif

#else
#import <UIKitCore/UILargeContentViewer.h>
#endif
