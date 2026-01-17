//
//  GCGameControllerSceneDelegate.h
//  GameControllerFramework
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <GameController/GCExtern.h>
#import <GameController/GCGameControllerActivationContext.h>

#import <UIKit/UISceneOptions.h>

@class UIScene;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(ios(18.0))
API_UNAVAILABLE(macCatalyst, tvos, visionos)
API_UNAVAILABLE(macos)
@protocol GCGameControllerSceneDelegate <NSObject>

/** 
 *  The scene has activated in response to a game controller event.
 *
 *  @param  scene
 *  The activated scene
 *
 *  @param  context
 *  The game controller activation context
 */
- (void)scene:(UIScene *)scene didActivateGameControllerWithContext:(GCGameControllerActivationContext *)context;

@end


API_AVAILABLE(ios(18.0))
API_UNAVAILABLE(macCatalyst, tvos, visionos)
API_UNAVAILABLE(macos)
@interface UISceneConnectionOptions (GameController)

/** 
 *  The activation context if the scene is being connected in response to a
 *  game controller.
 */
@property (nonatomic, nullable, readonly) GCGameControllerActivationContext *gameControllerActivationContext;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
