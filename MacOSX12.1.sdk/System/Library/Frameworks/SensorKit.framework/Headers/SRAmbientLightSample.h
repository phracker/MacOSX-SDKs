//
//  SRALSSample.h
//  SensorKit
//
//  Copyright © 2017 Apple Inc All rights reserved.

#import <Foundation/Foundation.h>
#import <SensorKit/SRDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, SRAmbientLightSensorPlacement) {
    SRAmbientLightSensorPlacementUnknown,
    SRAmbientLightSensorPlacementFrontTop,
    SRAmbientLightSensorPlacementFrontBottom,
    SRAmbientLightSensorPlacementFrontRight,
    SRAmbientLightSensorPlacementFrontLeft,
    SRAmbientLightSensorPlacementFrontTopRight,
    SRAmbientLightSensorPlacementFrontTopLeft,
    SRAmbientLightSensorPlacementFrontBottomRight,
    SRAmbientLightSensorPlacementFrontBottomLeft,
} API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos) API_UNAVAILABLE(tvos);

typedef struct {
    Float32 x;
    Float32 y;
} SRAmbientLightChromaticity API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos) API_UNAVAILABLE(tvos);

SR_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos, macos)
@interface SRAmbientLightSample : NSObject

@property (readonly) SRAmbientLightSensorPlacement placement;

/// Chromaticity is only valid on supporting devices. If not supported,
/// the values will be zero.
@property (readonly) SRAmbientLightChromaticity chromaticity;

@property (readonly, copy) NSMeasurement<NSUnitIlluminance *> *lux;

@end

NS_ASSUME_NONNULL_END
