/*
*  CMWaterSubmersionData.h
*  CoreMotion
*
*  Copyright (c) 2021 Apple Inc. All rights reserved.
*/
#import <Foundation/Foundation.h>
#import <CoreMotion/CMAvailability.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, CMWaterSubmersionState) {
	CMWaterSubmersionStateUnknown = 0,
	CMWaterSubmersionStateNotSubmerged,
	CMWaterSubmersionStateSubmerged
} NS_SWIFT_NAME(CMWaterSubmersionEvent.State);

typedef NS_ENUM(NSInteger, CMWaterSubmersionDepthState) {
	CMWaterSubmersionDepthStateUnknown = 0,
	CMWaterSubmersionDepthStateNotSubmerged = 100,
	CMWaterSubmersionDepthStateSubmergedShallow = 200,
	CMWaterSubmersionDepthStateSubmergedDeep = 300,
	CMWaterSubmersionDepthStateApproachingMaxDepth = 400,
	CMWaterSubmersionDepthStatePastMaxDepth = 500,
	CMWaterSubmersionDepthStateSensorDepthError = 600
} NS_SWIFT_NAME(CMWaterSubmersionMeasurement.DepthState);

/*
 * CMWaterSubmersionEvent
 *
 * Discussion:
 * 	   Datum representating a new state change of type CMWaterSubmersionState.
 */
COREMOTION_EXPORT API_AVAILABLE(watchos(9.0), ios(16.0)) API_UNAVAILABLE(macos, tvos, macCatalyst)
@interface CMWaterSubmersionEvent : NSObject <NSSecureCoding, NSCopying>
@property (readonly, nonatomic) NSDate* date;
@property (readonly, nonatomic) CMWaterSubmersionState state;
@end

/*
 * CMWaterSubmersionMeasurement
 *
 * Discussion:
 * 	   Datum representing a measurement update comprising of pressure, pressure uncertainty,
 *     depth, surface pressure, and submersion state. Depth value is positive when underwater.
 *     Depth, pressure, and pressureUncertainty are null when not submerged or when the state
 *     is CMWaterSubmersionDepthStateSensorDepthError.
 */
COREMOTION_EXPORT API_AVAILABLE(watchos(9.0), ios(16.0)) API_UNAVAILABLE(macos, tvos, macCatalyst)
@interface CMWaterSubmersionMeasurement : NSObject <NSSecureCoding, NSCopying>
@property (readonly, nonatomic) NSDate* date;
@property (readonly, nonatomic, nullable) NSMeasurement<NSUnitLength*>* depth;
@property (readonly, nonatomic, nullable) NSMeasurement<NSUnitPressure*>* pressure;
@property (readonly, nonatomic) NSMeasurement<NSUnitPressure*>* surfacePressure;
@property (readonly, nonatomic) CMWaterSubmersionDepthState submersionState;
@end

/*
 * CMWaterTemperature
 *
 * Discussion:
 * 	   Datum representing an update comprising of temperature, and temperature uncertainty
 */
COREMOTION_EXPORT API_AVAILABLE(watchos(9.0), ios(16.0)) API_UNAVAILABLE(macos, tvos, macCatalyst)
@interface CMWaterTemperature : NSObject <NSSecureCoding, NSCopying>
@property (readonly, nonatomic) NSDate* date;
@property (readonly, nonatomic) NSMeasurement<NSUnitTemperature*>* temperature;
@property (readonly, nonatomic) NSMeasurement<NSUnitTemperature*>* temperatureUncertainty;
@end

NS_ASSUME_NONNULL_END
