#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIWindowSceneActivationInteraction.h>)
//
//  UIWindowSceneActivationInteraction.h
//  UIKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitDefines.h>

#import <Foundation/Foundation.h>
#import <UIKit/UIInteraction.h>

@class UIWindowSceneActivationConfiguration, UIWindowSceneActivationInteraction;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Return a @c UIWindowSceneActivationConfiguration
///
/// @param interaction The @c UIWindowSceneActivationInteraction requesting a configuration.
/// @param location Location in the interaction's view for which a configuration is being requested.
typedef UIWindowSceneActivationConfiguration * _Nullable (^UIWindowSceneActivationInteractionConfigurationProvider)(UIWindowSceneActivationInteraction *interaction, CGPoint location) NS_SWIFT_NAME(UIWindowSceneActivationInteraction.ConfigurationProvider) API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos);

/// An interaction that facilitates activating a @c UIWindowScene when the user pinches out on the interaction's view.
UIKIT_EXTERN API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos) @interface UIWindowSceneActivationInteraction : NSObject <UIInteraction>

/// Returns a new @c UIWindowSceneActivationInteraction
///
/// @param configurationProvider Called when the interaction has been triggered. It should return a @c UIWindowSceneActivationConfiguration whose user activity will be used to request scene activation.
/// @param errorHandler Called when the activation request fails.
- (instancetype)initWithConfigurationProvider:(UIWindowSceneActivationInteractionConfigurationProvider)configurationProvider
                                 errorHandler:(void (^)(NSError *))errorHandler NS_DESIGNATED_INITIALIZER NS_SWIFT_NAME(init(_:errorHandler:));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIWindowSceneActivationInteraction.h>
#endif
