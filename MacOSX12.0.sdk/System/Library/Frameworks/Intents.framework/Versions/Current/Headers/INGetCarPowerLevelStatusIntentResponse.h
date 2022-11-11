//
//  INGetCarPowerLevelStatusIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResponse.h>

#import <Intents/INCarChargingConnectorType.h>

typedef NS_ENUM(NSInteger, INGetCarPowerLevelStatusIntentResponseCode) {
    INGetCarPowerLevelStatusIntentResponseCodeUnspecified = 0,
    INGetCarPowerLevelStatusIntentResponseCodeReady,
    INGetCarPowerLevelStatusIntentResponseCodeInProgress,
    INGetCarPowerLevelStatusIntentResponseCodeSuccess,
    INGetCarPowerLevelStatusIntentResponseCodeFailure,
    INGetCarPowerLevelStatusIntentResponseCodeFailureRequiringAppLaunch,
} API_AVAILABLE(ios(10.3), watchos(3.2)) API_UNAVAILABLE(macos, tvos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macos, tvos)
@interface INGetCarPowerLevelStatusIntentResponse : INIntentResponse

- (id)init NS_UNAVAILABLE;

// The app extension has the option of capturing its private state as an NSUserActivity and returning it as the 'currentActivity'.
// If the the app is launched, an NSUserActivity will be passed in with the private state.  The NSUserActivity may also be used to query the app's UI extension (if provided) for a view controller representing the current intent handling state.
// In the case of app launch, the NSUserActivity will have its activityType set to the name of the intent. This intent object will also be available in the NSUserActivity.interaction property.
- (instancetype)initWithCode:(INGetCarPowerLevelStatusIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INGetCarPowerLevelStatusIntentResponseCode code;

// An identifier for the vehicles. Use this same value as the carIdentifier property of INCar. Do not use the VIN (or the equivalent code) as the identifier.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *carIdentifier API_AVAILABLE(ios(14.0), watchos(7.0));

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *fuelPercentRemaining NS_REFINED_FOR_SWIFT;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *chargePercentRemaining NS_REFINED_FOR_SWIFT;

// The distance that the car can travel on the remaining resources.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSMeasurement<NSUnitLength *> *distanceRemaining;

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *charging NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(12.0), watchos(5.0));

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *minutesToFull NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(12.0), watchos(5.0));

// The maximum distance a vehicle can travel with full resources. As the vehicle drives, this value can change over time as a result of driving characteristics.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSMeasurement<NSUnitLength *> *maximumDistance API_AVAILABLE(ios(14.0), watchos(7.0));

// The maximum distance an electric vehicle can travel with the remaining charge.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSMeasurement<NSUnitLength *> *distanceRemainingElectric API_AVAILABLE(ios(14.0), watchos(7.0));

// The maximum distance an electric vehicle can travel on a full charge. This value can change overtime (and over several instances of the state of charge) as the vehicle drives.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSMeasurement<NSUnitLength *> *maximumDistanceElectric API_AVAILABLE(ios(14.0), watchos(7.0));

// The maximum distance a vehicle can travel with the remaining fuel.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSMeasurement<NSUnitLength *> *distanceRemainingFuel API_AVAILABLE(ios(14.0), watchos(7.0));

// The maximum distance a vehicle can travel with full resources. As the vehicle drives, this value can change over time as a result of driving characteristics.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSMeasurement<NSUnitLength *> *maximumDistanceFuel API_AVAILABLE(ios(14.0), watchos(7.0));

// A dictionary mapping NSStrings to serializable objects (NSString, NSNumber, NSArray, NSDictionary, or NSNull) that contains the OEM provided parameters for the consumption model used to calculate the vehicle’s energy consumption as the user drives. The keys of this dictionary describe the parameters that fit into the consumption model of the electric vehicle. The values of this dictionary represent the parameter values. model_id is a mandatory key in this dictionary.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSDictionary<NSString *, id> *consumptionFormulaArguments API_AVAILABLE(ios(14.0), watchos(7.0));

// A dictionary mapping NSStrings to serializable objects (NSString, NSNumber, NSArray, NSDictionary, or NSNull) that contains OEM provided parameters for the charging model that is used to calculate the duration of charging at a station. The keys of this dictionary describe the parameters that fit into the Charging model of the electric vehicle. The values of this dictionary represent the parameter values. model_id is a mandatory key in this dictionary.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSDictionary<NSString *, id> *chargingFormulaArguments API_AVAILABLE(ios(14.0), watchos(7.0));

// A time stamp for an instance of the state of charge. This time stamp should ideally indicate when the actual state of charge was captured from the vehicle.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *dateOfLastStateUpdate API_AVAILABLE(ios(14.0), watchos(7.0));

// The current connector being used to deliver charge to the vehicle’s battery. If isCharging is set, this property should contain the active connector that is currently being used to charge the vehicle.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INCarChargingConnectorType activeConnector API_AVAILABLE(ios(14.0), watchos(7.0));

// The maximum rated capacity of the vehicle’s battery. maximumBatteryCapacity should be set such that maximumBatteryCapacity >= currentBatteryCapacity >= minimumBatteryCapacity.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSMeasurement<NSUnitEnergy *> *maximumBatteryCapacity API_AVAILABLE(ios(14.0), watchos(7.0));

// The current capacity of the battery. currentBatteryCapacity should be set such that maximumBatteryCapacity >= currentBatteryCapacity >= minimumBatteryCapacity.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSMeasurement<NSUnitEnergy *> *currentBatteryCapacity API_AVAILABLE(ios(14.0), watchos(7.0));

// Minimum battery capacity. Used to display to the user as the minimum (not to be confused with the absolute 0 Wh). This represents the value that is displayed to the driver as 0% battery. minimumBatteryCapacity should be set such that maximumBatteryCapacity >= currentBatteryCapacity >= minimumBatteryCapacity.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSMeasurement<NSUnitEnergy *> *minimumBatteryCapacity API_AVAILABLE(ios(14.0), watchos(7.0));

@end

NS_ASSUME_NONNULL_END
