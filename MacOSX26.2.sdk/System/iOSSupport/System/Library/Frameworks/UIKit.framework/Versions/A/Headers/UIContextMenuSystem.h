#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIContextMenuSystem.h>)
//
//  UIContextMenuSystem.h
//  UIKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <UIKit/UIMenuSystem.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The context menu system.
UIKIT_EXTERN API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIContextMenuSystem : UIMenuSystem

/// The shared context menu system.
@property (class, nonatomic, readonly) UIContextMenuSystem *sharedSystem;

@property (class, nonatomic, readonly) UIMenuSystem *mainSystem NS_UNAVAILABLE;
@property (class, nonatomic, readonly) UIMenuSystem *contextSystem NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIContextMenuSystem.h>
#endif
