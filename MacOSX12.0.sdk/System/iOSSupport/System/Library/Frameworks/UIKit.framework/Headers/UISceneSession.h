#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISceneSession.h>)
//
//  UISceneSession.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UISceneDefinitions.h>

NS_ASSUME_NONNULL_BEGIN

@class UIScene, UIStoryboard;

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) NS_SWIFT_UI_ACTOR
@interface UISceneConfiguration : NSObject <NSCopying, NSSecureCoding>
// creates a UISceneConfiguration instance from your Info.plist using the name & system type provided.
// If nil is provided for the name, the first matching instance of the provided sessionType is used.
// If no matching name is found, or no descriptions of the provided sessionType exist in your Info.plist,
// then an instance with a nil sceneSubclass, delegateClass, and storyboard is returned.
// The name parameter passed in is used to lookup a predefined configuration from your app's Info.plist.
// the returned UISceneConfiguration instance is not guaranteed to share the value of the parameter.
+ (instancetype)configurationWithName:(nullable NSString *)name sessionRole:(UISceneSessionRole)sessionRole;
- (instancetype)initWithName:(nullable NSString *)name sessionRole:(UISceneSessionRole)sessionRole NS_DESIGNATED_INITIALIZER;

@property (nonatomic, nullable, readonly) NSString *name;
@property (nonatomic, readonly) UISceneSessionRole role;

@property (nonatomic, nullable) Class sceneClass;
@property (nonatomic, nullable) Class delegateClass;
@property (nonatomic, nullable, strong) UIStoryboard *storyboard;
@end

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) NS_SWIFT_UI_ACTOR
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

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UISceneSession.h>
#endif
