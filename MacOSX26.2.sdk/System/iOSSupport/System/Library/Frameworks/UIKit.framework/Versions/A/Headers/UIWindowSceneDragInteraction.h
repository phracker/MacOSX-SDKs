#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIWindowSceneDragInteraction.h>)
//
//  UIWindowSceneDragInteraction.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIInteraction.h>
#import <UIKit/UIGestureRecognizer.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@interface UIWindowSceneDragInteraction : NSObject <UIInteraction>

/// Use this to set up failure relationships with other gesture recognizers that may conflict.
/// Note that this is only available on platforms where gesture recognizers are used for window dragging.
@property (nonatomic, readonly) UIGestureRecognizer *gestureForFailureRelationships API_UNAVAILABLE(macCatalyst);

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIWindowSceneDragInteraction.h>
#endif
