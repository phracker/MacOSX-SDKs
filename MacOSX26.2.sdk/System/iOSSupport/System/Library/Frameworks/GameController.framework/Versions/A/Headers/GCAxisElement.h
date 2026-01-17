//  
//  GCPhysicalInputElement.h
//  GameController
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <GameController/GCPhysicalInputElement.h>
#import <GameController/GCAxisInput.h>
#import <GameController/GCRelativeInput.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0))
@protocol GCAxisElement <GCPhysicalInputElement>

/**
 The input reporting the value of the axis as the position between a lower and
 upper bound, if available.
 */
@property (readonly, nullable) id<GCAxisInput> absoluteInput;

/**
 The input reporting axis values as the change (delta) since the last event.
 
 Certain kinds of axis elements are only able to report relative values.  The
 tracking of a computer mouse, for example, has no fixed origin - only the
 change in position since the last event is reported.  Some freely-rotating
 dials may also only report a value indicating which direction the dial was
 turned.
 */
@property (readonly) id<GCRelativeInput> relativeInput;

@end

NS_ASSUME_NONNULL_END
