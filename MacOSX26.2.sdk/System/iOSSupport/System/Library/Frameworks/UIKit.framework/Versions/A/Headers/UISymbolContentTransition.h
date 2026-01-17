#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISymbolContentTransition.h>)
//
//  UISymbolContentTransition.h
//  UIKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

@class NSSymbolContentTransition, NSSymbolEffectOptions;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Represents a symbol content transition and options.
UIKIT_EXTERN API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos) NS_SWIFT_SENDABLE
@interface UISymbolContentTransition : NSObject <NSCopying, NSSecureCoding>

/// The symbol content transition.
@property (nonatomic, strong, readonly) NSSymbolContentTransition *contentTransition NS_REFINED_FOR_SWIFT;

/// Options for the symbol content transition.
@property (nonatomic, strong, readonly) NSSymbolEffectOptions *options NS_REFINED_FOR_SWIFT;

/// Initializes a `UISymbolContentTransition` with a symbol content transition.
+ (instancetype)transitionWithContentTransition:(NSSymbolContentTransition *)contentTransition NS_REFINED_FOR_SWIFT;

/// Initializes a `UISymbolContentTransition` with a symbol content transition and options.
+ (instancetype)transitionWithContentTransition:(NSSymbolContentTransition *)contentTransition options:(NSSymbolEffectOptions *)options NS_REFINED_FOR_SWIFT;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UISymbolContentTransition.h>
#endif
