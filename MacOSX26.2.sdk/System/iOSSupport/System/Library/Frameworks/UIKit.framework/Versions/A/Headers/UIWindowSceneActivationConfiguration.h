#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIWindowSceneActivationConfiguration.h>)
//
//  UIWindowSceneActivationConfiguration.h
//  UIKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitDefines.h>

#import <Foundation/Foundation.h>

@class UIWindowSceneActivationRequestOptions;
@class UITargetedPreview;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos)
@interface UIWindowSceneActivationConfiguration : NSObject

/// The user activity that will be used to request a scene
@property (nonatomic, readonly, strong) NSUserActivity *userActivity;

/// Options for customizing the scene request. If omitted default options are used.
@property (nonatomic, nullable, strong) UIWindowSceneActivationRequestOptions *options;

/// An optional preview used to define the visual "source" of the newly activated scene for use in system animations.
@property (nonatomic, nullable, strong) UITargetedPreview *preview;

- (instancetype)initWithUserActivity:(NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIWindowSceneActivationConfiguration.h>
#endif
