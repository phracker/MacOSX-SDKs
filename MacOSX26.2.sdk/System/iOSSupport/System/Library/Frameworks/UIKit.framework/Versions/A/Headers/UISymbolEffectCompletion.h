#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISymbolEffectCompletion.h>)
//
//  UISymbolEffectCompletion.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

@class NSSymbolEffect, NSSymbolContentTransition;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UISymbolEffectCompletionContext;

/// Completion handler for adding and removing symbol effects/content transitions.
typedef void(^UISymbolEffectCompletion)(UISymbolEffectCompletionContext *context) API_UNAVAILABLE(watchos);

/// Represents information about a symbol effect's completion.
/// You don't create one of these. Instead, UIKit creates one and passes it into the completion handler
/// of a symbol effect or symbol content transition.
UIKIT_EXTERN API_AVAILABLE(ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UISymbolEffectCompletionContext : NSObject

/// Whether or not the symbol effect was completely finished.
/// This will be YES for effects that have successfully run to completion.
@property (nonatomic, readonly, getter=isFinished) BOOL finished;

/// The object (such as an image view) that the symbol effect was added to.
@property (nonatomic, weak, nullable, readonly) id sender;

/// The symbol effect that has completed.
/// There is no guarantee that this effect will be the same instance as the effect originally added.
/// This will be `nil` if a symbol content transition was added instead.
@property (nonatomic, nullable, readonly) NSSymbolEffect *effect;

/// The symbol content transition that has completed.
/// There is no guarantee that this content transition will be the same instance as the content transition originally added.
/// This will be `nil` if a symbol effect was added instead.
@property (nonatomic, nullable, readonly) NSSymbolContentTransition *contentTransition;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UISymbolEffectCompletion.h>
#endif
