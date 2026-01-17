#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIScreenEdgePanGestureRecognizer.h>)
//
//  UIScreenEdgePanGestureRecognizer.h
//  Copyright (c) 2012-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIGeometry.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIPanGestureRecognizer.h>

NS_ASSUME_NONNULL_BEGIN

/*! This subclass of UIPanGestureRecognizer only recognizes if the user slides their finger
    in from the bezel on the specified edge. */
UIKIT_EXTERN API_AVAILABLE(ios(7.0)) API_UNAVAILABLE(tvos) @interface UIScreenEdgePanGestureRecognizer : UIPanGestureRecognizer
@property (readwrite, nonatomic, assign) UIRectEdge edges; //< The edges on which this gesture recognizes, relative to the current interface orientation
@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIScreenEdgePanGestureRecognizer.h>
#endif
