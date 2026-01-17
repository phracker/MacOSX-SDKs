//
//  SKOverlayTransitionContext.h
//  StoreKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <StoreKit/StoreKitDefines.h>
#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS
SK_CLASS_FINAL
NS_SWIFT_NAME(SKOverlay.TransitionContext)
API_AVAILABLE(ios(14.0), visionos(1.0)) API_UNAVAILABLE(macos, watchos) __TVOS_PROHIBITED NS_SWIFT_NONSENDABLE
@interface SKOverlayTransitionContext : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Adds an animation that will be synchronized with an overlay's presentation/dismissal.
- (void)addAnimationBlock:(void (^)(void))block NS_SWIFT_NAME(addAnimation(_:)) API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos,watchos,visionos) __TVOS_PROHIBITED;

@property (nonatomic, readonly) CGRect startFrame API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos,watchos,visionos) __TVOS_PROHIBITED;

@property (nonatomic, readonly) CGRect endFrame API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos,watchos,visionos) __TVOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
