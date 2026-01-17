#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISceneConfiguration.h>)
//
//  UISceneConfiguration.h
//  UIKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UISceneDefinitions.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIStoryboard;

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UISceneConfiguration : NSObject <NSCopying, NSSecureCoding>
// Creates a UISceneConfiguration instance from your Info.plist using the name and session role provided.
// If nil is provided for the name, the first matching instance of the provided session role is used.
// If no matching name is found, or no descriptions of the provided session role exist in your Info.plist,
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

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UISceneConfiguration.h>
#endif
