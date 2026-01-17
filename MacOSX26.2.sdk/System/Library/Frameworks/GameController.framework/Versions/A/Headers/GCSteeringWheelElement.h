//  
//  GCSteeringWheelElement.h
//  GameController
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <GameController/GCPhysicalInputElement.h>
#import <GameController/GCAxisElement.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(13.0), macCatalyst(16.0)) API_UNAVAILABLE(ios, tvos)
@interface GCSteeringWheelElement : NSObject <GCAxisElement>

- (instancetype)init NS_UNAVAILABLE;

/* The maximum angle, in degrees, the wheel can be rotated. */
@property (readonly) float maximumDegreesOfRotation;

@end

NS_ASSUME_NONNULL_END
