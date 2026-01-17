//
//  GameController.h
//  GameController
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifdef __cplusplus
#define GAMECONTROLLER_EXTERN		extern "C" __attribute__((visibility ("default")))
#else
#define GAMECONTROLLER_EXTERN	        extern __attribute__((visibility ("default")))
#endif

#define GAMECONTROLLER_EXPORT NS_CLASS_AVAILABLE(10_9, 7_0)

#import <GameController/GCControllerElement.h>

#import <GameController/GCControllerAxisInput.h>
#import <GameController/GCControllerButtonInput.h>
#import <GameController/GCControllerDirectionPad.h>

#import <GameController/GCMotion.h>

#import <GameController/GCGamepad.h>
#import <GameController/GCGamepadSnapshot.h>

#import <GameController/GCExtendedGamepad.h>
#import <GameController/GCExtendedGamepadSnapshot.h>

#import <GameController/GCController.h>
