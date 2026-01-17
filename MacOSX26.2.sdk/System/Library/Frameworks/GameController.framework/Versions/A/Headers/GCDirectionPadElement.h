//  
//  GCDirectionPadElement.h
//  GameController
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <GameController/GCPhysicalInputElement.h>
#import <GameController/GCLinearInput.h>
#import <GameController/GCAxisInput.h>
#import <GameController/GCAxis2DInput.h>
#import <GameController/GCPressedStateInput.h>

NS_ASSUME_NONNULL_BEGIN

/**
 An object conforming to \c GCDirectionPadElement represents a four-way
 directional control element.
 
 A direction pad element contains a common grouping of 2 axis inputs, which can
 also be interpreted as 2 sets of mutually exclusive button pairs. Only one
 button in each pair, {up, down} and {left, right}, can be pressed at any
 given time.
 */
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0))
@protocol GCDirectionPadElement <GCPhysicalInputElement>

/** The x,y position of the dpad input. */
@property (readonly) id<GCAxis2DInput> xyAxes API_AVAILABLE(macos(14.3), ios(17.4), tvos(17.4), visionos(1.1));

/** The horizontal/x-component of the dpad input. */
@property (readonly) id<GCAxisInput> xAxis;
/** The vertical/y-component of the dpad input. */
@property (readonly) id<GCAxisInput> yAxis;

/** The positive y-component of the dpad input. */
@property (readonly) id<GCLinearInput, GCPressedStateInput> up;
/** The negative y-component of the dpad input. */
@property (readonly) id<GCLinearInput, GCPressedStateInput> down;
/** The negative x-component of the dpad input. */
@property (readonly) id<GCLinearInput, GCPressedStateInput> left;
/** The positive x-component of the dpad input. */
@property (readonly) id<GCLinearInput, GCPressedStateInput> right;

@end

NS_ASSUME_NONNULL_END
