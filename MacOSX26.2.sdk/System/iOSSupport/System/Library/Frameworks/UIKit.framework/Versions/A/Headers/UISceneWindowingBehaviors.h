#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISceneWindowingBehaviors.h>)
//
//  UISceneWindowingBehaviors.h
//  UIKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

UIKIT_EXTERN API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UISceneWindowingBehaviors : NSObject

// Clients should never make one of these directly. Access through UIWindowScene.windowingBehaviors.
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*
 Used to set and get window behaviors which are represented by the "traffic light" window control buttons on the NSWindow associated with this scene.
 */
@property (nonatomic, getter=isClosable) BOOL closable;
@property (nonatomic, getter=isMiniaturizable) BOOL miniaturizable;

@end

#else
#import <UIKitCore/UISceneWindowingBehaviors.h>
#endif
