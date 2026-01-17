//
//  GCSwitchElement.h
//  GameController
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <GameController/GCPhysicalInputElement.h>
#import <GameController/GCSwitchPositionInput.h>

NS_ASSUME_NONNULL_BEGIN

/**
 An object conforming to \c GCSwitchElement represents a latching switch.
 A switch may be in one of several positions, and remains in its last position
 after the user stops interacting with it.
 */
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0))
@protocol GCSwitchElement <GCPhysicalInputElement>

/**
 Get the input containing the absolute position of the switch.
 */
@property (readonly) id<GCSwitchPositionInput> positionInput;

@end

NS_ASSUME_NONNULL_END
