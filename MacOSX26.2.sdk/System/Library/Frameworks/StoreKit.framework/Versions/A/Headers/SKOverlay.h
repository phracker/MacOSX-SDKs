//
//  SKOverlay.h
//  StoreKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>
#if !TARGET_OS_OSX
#import <UIKit/UIKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

@class SKOverlay, SKOverlayTransitionContext;

API_AVAILABLE(ios(14.0), visionos(1.0)) API_UNAVAILABLE(macos, watchos) __TVOS_PROHIBITED
@protocol SKOverlayDelegate <NSObject>

@optional

- (void)storeOverlay:(SKOverlay *)overlay didFailToLoadWithError:(NSError *)error NS_SWIFT_NAME(storeOverlayDidFailToLoad(_:error:));
- (void)storeOverlay:(SKOverlay *)overlay willStartPresentation:(SKOverlayTransitionContext *)transitionContext NS_SWIFT_NAME(storeOverlayWillStartPresentation(_:transitionContext:));
- (void)storeOverlay:(SKOverlay *)overlay didFinishPresentation:(SKOverlayTransitionContext *)transitionContext NS_SWIFT_NAME(storeOverlayDidFinishPresentation(_:transitionContext:));
- (void)storeOverlay:(SKOverlay *)overlay willStartDismissal:(SKOverlayTransitionContext *)transitionContext NS_SWIFT_NAME(storeOverlayWillStartDismissal(_:transitionContext:));
- (void)storeOverlay:(SKOverlay *)overlay didFinishDismissal:(SKOverlayTransitionContext *)transitionContext NS_SWIFT_NAME(storeOverlayDidFinishDismissal(_:transitionContext:));

@end

@class SKOverlayConfiguration;

SK_EXTERN_CLASS
SK_CLASS_FINAL
API_AVAILABLE(ios(14.0), visionos(1.0)) API_UNAVAILABLE(macos, watchos) __TVOS_PROHIBITED NS_SWIFT_NONSENDABLE
@interface SKOverlay : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Creates an overlay with the provided configuration.
/// @param configuration the configuration for the overlay.
- (instancetype)initWithConfiguration:(SKOverlayConfiguration *)configuration NS_DESIGNATED_INITIALIZER;

#if !TARGET_OS_OSX
/// Attempts to present an app overlay in a `UIWindowScene`.
- (void)presentInScene:(UIWindowScene *)scene API_AVAILABLE(ios(14.0), visionos(1.0)) NS_EXTENSION_UNAVAILABLE("Overlays are not available in extensions") NS_SWIFT_UI_ACTOR;

/// Dismisses an overlay being presented in a `UIWindowScene`.
+ (void)dismissOverlayInScene:(UIWindowScene *)scene API_AVAILABLE(ios(14.0), visionos(1.0)) NS_EXTENSION_UNAVAILABLE("Overlays are not available in extensions") NS_SWIFT_UI_ACTOR;
#endif

/// A delegate for overlay events.
@property (nonatomic, weak, nullable) id <SKOverlayDelegate> delegate;

/// The overlay configuration.
@property (readonly, copy) SKOverlayConfiguration *configuration;

@end

NS_ASSUME_NONNULL_END
