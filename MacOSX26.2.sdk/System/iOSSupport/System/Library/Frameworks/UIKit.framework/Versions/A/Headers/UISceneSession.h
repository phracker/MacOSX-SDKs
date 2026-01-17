#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISceneSession.h>)
//
//  UISceneSession.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UISceneConfiguration.h>
#import <UIKit/UISceneDefinitions.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIScene;

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UISceneSession : NSObject <NSSecureCoding>
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

// If already instantiated, the UIScene instance that is represented by this definition.
@property (nonatomic, readonly, nullable) UIScene *scene;

@property (nonatomic, readonly) UISceneSessionRole role;
@property (nonatomic, readonly, copy) UISceneConfiguration *configuration;

@property (nonatomic, readonly) NSString *persistentIdentifier;

// The initial value of stateRestorationActivity may not be immediately available when the scene
// is connected, depending on the app's default protection class and the lock state of the device.
@property (nonatomic, nullable, strong) NSUserActivity *stateRestorationActivity;

// objects must be plist types
@property (nonatomic, nullable, copy) NSDictionary<NSString *, id> *userInfo;
@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UISceneSession.h>
#endif
