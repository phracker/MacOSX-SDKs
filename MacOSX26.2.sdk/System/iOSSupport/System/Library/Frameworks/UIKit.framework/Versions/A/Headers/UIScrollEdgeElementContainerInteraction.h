#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIScrollEdgeElementContainerInteraction.h>)
//
//  UIScrollEdgeElementContainerInteraction.h
//  UIKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitDefines.h>
#import <UIKit/UIInteraction.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIScrollView;

/// Add this interaction to a container view of views that overlay the edge of a scroll view.
/// Any descendants of this view that should affect the shape of the edge effect, such as labels, images, glass views, and controls, will automatically do so.
///
/// In the following example, an interaction is added to a container view of buttons that overlay the bottom edge of a scroll view.
///
///     let interaction = UIScrollEdgeElementContainerInteraction()
///     interaction.scrollView = scrollView
///     interaction.edge = .bottom
///     buttonContainer.addInteraction(interaction)
///
UIKIT_FINAL UIKIT_EXTERN NS_SWIFT_UI_ACTOR API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos)
@interface UIScrollEdgeElementContainerInteraction : NSObject <UIInteraction>

/// The scroll view to affect
@property (nonatomic, nullable, weak) UIScrollView *scrollView;

/// The edge of the scroll view to affect
@property (nonatomic) UIRectEdge edge;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIScrollEdgeElementContainerInteraction.h>
#endif
