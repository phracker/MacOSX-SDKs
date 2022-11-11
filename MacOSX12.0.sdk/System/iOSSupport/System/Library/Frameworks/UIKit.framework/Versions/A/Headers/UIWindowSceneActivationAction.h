#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIWindowSceneActivationAction.h>)
//
//  UIWindowSceneActivationAction.h
//  UIKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitDefines.h>

#import <Foundation/Foundation.h>
#import <UIKit/UIAction.h>

@class UIWindowSceneActivationConfiguration, UIWindowSceneActivationAction;

NS_ASSUME_NONNULL_BEGIN

/// Return a @c UIWindowSceneActivationConfiguration
///
/// @param action The @c UIWindowSceneActivationAction requesting a configuration.
typedef UIWindowSceneActivationConfiguration * _Nullable (^UIWindowSceneActivationActionConfigurationProvider)(__kindof UIWindowSceneActivationAction *action) NS_SWIFT_NAME(UIWindowSceneActivationAction.ConfigurationProvider) API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos);

UIKIT_EXTERN API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos)
/// An action that facilitates activating a @c UIWindowScene when performed.
@interface UIWindowSceneActivationAction: UIAction

/// The actions title. Set to nil to use the default title.
@property (nonatomic, copy, null_resettable) NSString *title;

/// Returns a new @c UIWindowSceneActivationAction
///
/// @param identifier The action's identifier. Pass nil to use an auto-generated identifier.
/// @param alternateAction If running on a platform that doesn't support multiple windows, the alternate action is used. Otherwise, the alternates handler is called if the scene activation request fails.
/// @param configurationProvider Called when the action has been triggered. It should return a @c UIWindowSceneActivationConfiguration whose user activity will be used to request scene activation.
+ (instancetype)actionWithIdentifier:(nullable UIActionIdentifier)identifier
                     alternateAction:(nullable UIAction *)alternateAction
               configurationProvider:(UIWindowSceneActivationActionConfigurationProvider)configurationProvider NS_SWIFT_UNAVAILABLE("Use init(title:image:identifier:discoverabilityTitle:attributes:alternate:_:) instead.");

+ (instancetype)actionWithHandler:(UIActionHandler)handler NS_UNAVAILABLE;
+ (instancetype)actionWithTitle:(NSString *)title
                          image:(nullable UIImage *)image
                     identifier:(nullable UIActionIdentifier)identifier
                        handler:(UIActionHandler)handler NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIWindowSceneActivationAction.h>
#endif
