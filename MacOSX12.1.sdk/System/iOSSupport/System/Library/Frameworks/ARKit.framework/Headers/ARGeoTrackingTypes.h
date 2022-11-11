
//
//  ARGeoTrackingTypes.h
//  ARKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Keeps track of where an altitude value came from and informs the user about the expected accuracy.
 */
API_AVAILABLE(ios(14.0))
typedef NS_ENUM(NSInteger, ARAltitudeSource) {
    /** Altitude could not be determined (yet). */
    ARAltitudeSourceUnknown,

    /** ARKit determined altitude based on a coarse digital elevation model. The provided value is too imprecise to be used at close range, but is sufficient to anchor far away content. */
    ARAltitudeSourceCoarse,

    /** ARKit determined altitude based on a high resolution digital elevation model. */
    ARAltitudeSourcePrecise,

    /** Altitude was provided by the user. */
    ARAltitudeSourceUserDefined
} NS_SWIFT_NAME(ARGeoAnchor.AltitudeSource);

/**
 A value describing geo tracking state.
 */
API_AVAILABLE(ios(14.0))
typedef NS_ENUM(NSInteger, ARGeoTrackingState) {
    /** Geo tracking is not available. */
    ARGeoTrackingStateNotAvailable,
    
    /** Geo tracking is being initialized. */
    ARGeoTrackingStateInitializing,
    
    /** Geo tracking is attempting to localize against a Map. */
    ARGeoTrackingStateLocalizing,
    
    /** Geo tracking is localized. */
    ARGeoTrackingStateLocalized,
} NS_SWIFT_NAME(ARGeoTrackingStatus.State);

/**
 A value describing geo tracking accuracy.
 */
API_AVAILABLE(ios(14.0))
typedef NS_ENUM(NSInteger, ARGeoTrackingAccuracy) {
    /** Geo tracking has not localized yet. Accuracy is indeterminate. */
    ARGeoTrackingAccuracyUndetermined,

    /** Localized with low accuracy. */
    ARGeoTrackingAccuracyLow,
    
    /** Localized with medium accuracy. */
    ARGeoTrackingAccuracyMedium,
    
    /** Localized with high accuracy. */
    ARGeoTrackingAccuracyHigh
} NS_SWIFT_NAME(ARGeoTrackingStatus.Accuracy);

/**
 Reasons for geo tracking failure states.
 */
API_AVAILABLE(ios(14.0))
typedef NS_ENUM(NSInteger, ARGeoTrackingStateReason) {
    /** No issues reported. */
    ARGeoTrackingStateReasonNone,

    /** Geo tracking is not available at the location. */
    ARGeoTrackingStateReasonNotAvailableAtLocation,

    /** Geo tracking needs location permissions from the user. */
    ARGeoTrackingStateReasonNeedLocationPermissions,

    /** World tracking pose is not valid yet. */
    ARGeoTrackingStateReasonWorldTrackingUnstable,

    /** Waiting for a location point that meets accuracy threshold before starting geo tracking. */
    ARGeoTrackingStateReasonWaitingForLocation,

    /** Waiting for availability check on first location point to complete. */
    ARGeoTrackingStateReasonWaitingForAvailabilityCheck,

    /** Geo tracking data hasn't been downloaded yet. */
    ARGeoTrackingStateReasonGeoDataNotLoaded,

    /** The device is pointed at an angle too far down to use geo tracking. */
    ARGeoTrackingStateReasonDevicePointedTooLow,

    /** Visual localization failed, but no errors were found in the input. */
    ARGeoTrackingStateReasonVisualLocalizationFailed
} NS_SWIFT_NAME(ARGeoTrackingStatus.StateReason);

/**
 Collection of fields to give information on geo tracking status.
 */
API_AVAILABLE(ios(14.0))
@interface ARGeoTrackingStatus : NSObject <NSCopying, NSSecureCoding>

/**
 The state of geo tracking.
 */
@property (nonatomic, readonly) ARGeoTrackingState state;

/**
 The accuracy of geo tracking.
*/
@property (nonatomic, readonly) ARGeoTrackingAccuracy accuracy;

/**
 Reason for geo tracking state.
 */
@property (nonatomic, readonly) ARGeoTrackingStateReason stateReason;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

