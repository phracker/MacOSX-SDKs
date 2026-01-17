#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextSelectionHandleView.h>)
//
//  UITextSelectionHandleView.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitCore.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// @protocol   UITextSelectionHandleView
/// @abstract   A view that represents a selection handle drawn at the edges of contiguous selection ranges.
/// @discussion When a selection is ranged (i.e., length is > 0), and the device supports range adjustment via a gesture,
///             selection handles ("lollipops") are displayed at the edges of the contiguous selection (usually a UITextSelectionHighlightView).
UIKIT_EXTERN API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UITextSelectionHandleView <UICoordinateSpace>

/// Controls which direction the handle is oriented. For example, NSDirectionalRectEdgeLeading indicates the handle is on the leading
/// edge, so the dot will be rendered on top.
@property (nonatomic, assign) NSDirectionalRectEdge direction;

/// Convenience accessor for @c direction calculations.
@property (nonatomic, readonly, getter=isVertical) BOOL vertical;

/// If applicable, a custom shape for the lollipop stem. Default is @c nil, which results in a rounded rect style based on bounds.
@property (nonatomic, nullable, strong) UIBezierPath *customShape;

/// Provides a preferred frame given @c rect based on the current appearance configuration.
- (CGRect)preferredFrameForRect:(CGRect)rect;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITextSelectionHandleView.h>
#endif
