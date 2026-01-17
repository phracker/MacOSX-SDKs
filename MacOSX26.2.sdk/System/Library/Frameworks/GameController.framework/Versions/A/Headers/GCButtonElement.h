//  
//  GCButtonElement.h
//  GameController
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <GameController/GCPhysicalInputElement.h>
#import <GameController/GCLinearInput.h>
#import <GameController/GCPressedStateInput.h>
#import <GameController/GCTouchedStateInput.h>

NS_ASSUME_NONNULL_BEGIN

/**
 An object conforming to \c GCButtonElement represents a momentary switch,
 such as a push button.  A button's input only asserts while the user is
 interacting with it, and then returns to a preferred state (not pressed, not
 touched).
 */
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0))
@protocol GCButtonElement <GCPhysicalInputElement>

/**
 Get the input containing the pressed state of the button.
 */
@property (readonly) id<GCPressedStateInput, GCLinearInput> pressedInput;

/**
 Get the input containing the touched state of the button.
 
 Some buttons feature capacitive touch capabilities where the user can touch the
 button without pressing it.
 */
@property (readonly, nullable) id<GCTouchedStateInput> touchedInput;

/**
 Get the input containing the measured force applied to the button.
 
 Some buttons feature load cells (also known as button force transducers)
 capable of measuring applied mechanical force.
 */
@property (readonly, nullable) id<GCLinearInput> forceInput API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0));

@end

NS_ASSUME_NONNULL_END

