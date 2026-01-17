#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIZoomTransitionOptions.h>)
//
//  UIZoomTransitionOptions.h
//  UIKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIView.h>
#import <UIKit/UIColor.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIBlurEffect, UIZoomTransitionInteractionContext, UIZoomTransitionAlignmentRectContext;

UIKIT_EXTERN API_AVAILABLE(ios(18.0)) API_UNAVAILABLE(watchos)
NS_SWIFT_NAME(UIViewControllerTransition.ZoomOptions)
@interface UIZoomTransitionOptions : NSObject <NSCopying>

/// Called when an interactive dismissal of this transition begins.
/// Return value indicates whether the interaction should begin for the given context.
@property (nonatomic, copy, nullable) BOOL (^interactiveDismissShouldBegin)(UIZoomTransitionInteractionContext *);

/// Return a frame in the zoomed view controller's view to which to align the source view.
/// Return `CGRectNull` to indicate no preference.
@property (nonatomic, copy, nullable) CGRect (^alignmentRectProvider)(UIZoomTransitionAlignmentRectContext *) NS_REFINED_FOR_SWIFT;

/// Dimming color to apply to the content behind the zoomed in view. Set to nil to use the default.
@property (nonatomic, strong, nullable) UIColor *dimmingColor;

/// Visual effect to apply to the content behind the zoomed in view. Defaults to nil.
@property (nonatomic, strong, nullable) UIBlurEffect *dimmingVisualEffect;

@end


UIKIT_EXTERN API_AVAILABLE(ios(18.0)) API_UNAVAILABLE(watchos)
NS_SWIFT_NAME(UIZoomTransitionOptions.InteractionContext)
@interface UIZoomTransitionInteractionContext : NSObject

/// Location of the interaction in the displayed view controller's view's coordinate space.
@property (nonatomic, readonly) CGPoint location;

/// The interaction's velocity.
@property (nonatomic, readonly) CGVector velocity;

/// Whether the interaction would begin under the current conditions by default.
@property (nonatomic, readonly) BOOL willBegin;

@end


UIKIT_EXTERN API_AVAILABLE(ios(18.0)) API_UNAVAILABLE(watchos)
NS_SWIFT_NAME(UIZoomTransitionOptions.AlignmentRectContext)
@interface UIZoomTransitionAlignmentRectContext : NSObject

/// The transition's source view.
@property (nonatomic, readonly) UIView *sourceView;

/// The zoomed view controller.
@property (nonatomic, readonly) UIViewController *zoomedViewController;

@end

NS_HEADER_AUDIT_END(nullability, sendability)


#else
#import <UIKitCore/UIZoomTransitionOptions.h>
#endif
