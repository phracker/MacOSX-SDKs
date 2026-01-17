#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIAccessibilityZoom.h>)
//
//  UIAccessibilityZoom.h
//  UIKit
//
//  Copyright (c) 2011-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/* 
 Use to inform system Zoom that focus has changed to a new location. 
 The frame should be in the coordinate space of the view.
 */
typedef NS_ENUM(NSInteger, UIAccessibilityZoomType) {
    UIAccessibilityZoomTypeInsertionPoint,      // Used when the text insertion point has moved
} API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(watchos);

UIKIT_EXTERN void UIAccessibilityZoomFocusChanged(UIAccessibilityZoomType type, CGRect frame, UIView * __nonnull view) API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR;

/*
 If your app uses multi-finger gestures that conflict with system Zoom gestures (by using three fingers), 
 calling this method will warn users of the conflict.
 */
UIKIT_EXTERN void UIAccessibilityRegisterGestureConflictWithZoom(void) API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR;

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIAccessibilityZoom.h>
#endif
