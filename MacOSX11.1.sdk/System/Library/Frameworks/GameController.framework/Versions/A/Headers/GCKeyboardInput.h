//
//  GCKeyboardInput.h
//  GameController
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <GameController/GCExtern.h>
#import <GameController/GCPhysicalInputProfile.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Keyboard profile. Contains the current state of buttons specified in GCKeyCodes.h.
        
 GCKeyboardInput is designed primarly for input polling. For the best text input experience, UIKit/AppKit usage is recommended.
 */
API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
@interface GCKeyboardInput : GCPhysicalInputProfile

/**
 Set this block if you want to be notified when a value of a key changed. If multiple keys have changed this block will be called
cd  for each key that changed.
 
 @param keyboard this keyboard that is being used to map the raw input data into logical values on keyboard keys.
 @param key the key that has been modified
 @param pressed the state of the key at the moment of block calling
 */
typedef void (^GCKeyboardValueChangedHandler)(GCKeyboardInput *keyboard, GCDeviceButtonInput *key, GCKeyCode keyCode, BOOL pressed);
@property (nonatomic, copy, nullable) GCKeyboardValueChangedHandler keyChangedHandler;

/**
 Before querying any key for a value it might be useful to check if any key is actually pressed
 */
@property (nonatomic, readonly, getter = isAnyKeyPressed) BOOL anyKeyPressed;

/**
 Alongside general subscript notation of GCPhysicalInputProfile keys can be accessed using this method.
 
 @example [keyboard buttonForKey:GCKeyCode.UpArrow] == keyboard[GCKeyUpArrow]
 @param code is a low level key code that can be used for accessing a keyboard button.
 @note Full list of supported key constants can be found in GCKeyCodes.h and GCKeyNames.h
 */
- (GCDeviceButtonInput * _Nullable)buttonForKeyCode:(GCKeyCode)code;

@end

NS_ASSUME_NONNULL_END
