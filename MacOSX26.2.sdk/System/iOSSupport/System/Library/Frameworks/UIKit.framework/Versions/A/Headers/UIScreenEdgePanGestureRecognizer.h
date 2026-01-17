#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIScreenEdgePanGestureRecognizer.h>)
//
//  UIScreenEdgePanGestureRecognizer.h
//  Copyright (c) 2012-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIGeometry.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIPanGestureRecognizer.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*! This subclass of UIPanGestureRecognizer only recognizes if the user slides their finger
    in from the bezel on the specified edge. */
UIKIT_EXTERN API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(tvos, visionos, watchos) NS_SWIFT_UI_ACTOR
@interface UIScreenEdgePanGestureRecognizer : UIPanGestureRecognizer
@property (readwrite, nonatomic, assign) UIRectEdge edges; // The edges on which this gesture recognizes, relative to the current interface orientation
@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIScreenEdgePanGestureRecognizer.h>
#endif
