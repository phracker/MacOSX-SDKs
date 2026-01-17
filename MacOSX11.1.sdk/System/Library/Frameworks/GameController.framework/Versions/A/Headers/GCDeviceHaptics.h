//
//  GCDeviceHaptics.h
//  GameController
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameController/GCExtern.h>

@class CHHapticEngine;

NS_ASSUME_NONNULL_BEGIN

/**
 A GCHapticsLocality represents the locations of haptic actuators on a controller. You can create a haptic engine with a given
 GCHapticsLocality, and any patterns you send to that engine will play on all specified actuators.
 
 ```
 CHHapticEngine *engine = [controller.haptics createEngineWithLocality:GCHapticsLocalityDefault];
 ```
 
 @see GCDeviceHaptics
*/
typedef NSString* GCHapticsLocality NS_TYPED_ENUM API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCHapticsLocality const GCHapticsLocalityDefault API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)); // guaranteed to be supported
GAMECONTROLLER_EXTERN GCHapticsLocality const GCHapticsLocalityAll API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)); // guaranteed to be supported
GAMECONTROLLER_EXTERN GCHapticsLocality const GCHapticsLocalityHandles API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCHapticsLocality const GCHapticsLocalityLeftHandle API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCHapticsLocality const GCHapticsLocalityRightHandle API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCHapticsLocality const GCHapticsLocalityTriggers API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCHapticsLocality const GCHapticsLocalityLeftTrigger API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
GAMECONTROLLER_EXTERN GCHapticsLocality const GCHapticsLocalityRightTrigger API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

GAMECONTROLLER_EXTERN const float GCHapticDurationInfinite API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
@interface GCDeviceHaptics : NSObject

/**
 The set of supported haptic localities for this device - representing the locations of its haptic actuators.
 
 @note GCHapticsLocalityDefault and GCHapticsLocalityAll are guaranteed to be supported - and they may be equivalent.
 
 @see GCHapticsLocality
*/
@property (nonatomic, strong, readonly) NSSet<GCHapticsLocality> *supportedLocalities;

- (instancetype)init NS_UNAVAILABLE;

/**
 Creates and returns a new instance of CHHapticEngine with a given GCHapticsLocality. Any patterns you send to this engine will play on
 all specified actuators.

 @note Often times, it is best to use GCHapticsLocalityDefault. Engines created with the default locality will give users an expected
 haptic experience. On most game controllers, this will cause your haptic patterns to play on the handles. If you want to play different
 experiences on different actuators (for example, using the left handle actuator as a woofer and the right actuator as a tweeter), you can
 create multiple engines (for example, one with a GCHapticsLocalityLeftHandle locality and another with a GCHapticsLocalityRightHandle
 locality).
 
 @see CHHapticEngine
 @see GCHapticsLocality
 */
- (CHHapticEngine * _Nullable)createEngineWithLocality:(GCHapticsLocality)locality;

@end

NS_ASSUME_NONNULL_END
