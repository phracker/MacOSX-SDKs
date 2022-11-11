//
//  GCControllerCursor.h
//  GameController
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//


#import <GameController/GCControllerDirectionPad.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A cursor is a Direction Pad that has its axis extended from [-1; 1] to [width; height] range
 Up, down, left, right allows to use mouse to simulate DirectionaPad or Thumbstick since values are normalized for these elements
 */

API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
@interface GCDeviceCursor : GCControllerDirectionPad

@end

NS_ASSUME_NONNULL_END
