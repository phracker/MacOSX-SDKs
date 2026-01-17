//
//  PHASEDistanceModel.h
//  PHASE
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#ifndef PHASEDistanceModel_h
#define PHASEDistanceModel_h

#import <PHASE/PHASETypes.h>
#import <PHASE/PHASEEnvelope.h>

NS_ASSUME_NONNULL_BEGIN

/****************************************************************************************************/
/*!
    @interface PHASEDistanceModelFadeOutParameters
    @abstract Distance model fade out parameters.
*/
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEDistanceModelFadeOutParameters : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @method initWithCullDistance
    @abstract Initialize with a cullDistance.
    @param cullDistance
        The distance beyond which the sound will be culled. Values must be >= 1.
    @note
        The cullDistance is scaled by unitsPerMeter internally, so can be provided at the client's native spatial scale.
        The system will smoothly fade the sound to zero before reaching this distance to avoid any audible artifacts.
    @return
        An instance, or nil if initialization fails.
*/
- (instancetype)initWithCullDistance:(double)cullDistance NS_DESIGNATED_INITIALIZER;

/*!
    @property cullDistance
    @abstract The distance beyond which the sound will be culled.
    @note
        Values are clamped the range [1, DBL_MAX].
        This value is scaled by unitsPerMeter internally, so can be provided at the client's native spatial scale.
*/
@property(nonatomic,readonly) double cullDistance;

@end

/****************************************************************************************************/
/*!
    @interface PHASEDistanceModelParameters
    @abstract Distance model parameters.
*/
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEDistanceModelParameters : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @property fadeOutParameters
    @abstract Fade out parameters (optional).
*/
@property(nullable, nonatomic, strong) PHASEDistanceModelFadeOutParameters* fadeOutParameters;

@end

/****************************************************************************************************/
/*!
    @interface PHASEGeometricSpreadingDistanceModelParameters
    @abstract Geometric spreading distance model parameters.
    @discussion
        Standard geometric spreading loss as a function of geometry and distance.
*/
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEGeometricSpreadingDistanceModelParameters : PHASEDistanceModelParameters

- (instancetype)init;

/*!
    @property rolloffFactor
    @abstract Rolloff factor.
    @note
        Values are clamped to the range [0.0, DBL_MAX].
        Default value is 1.0.
        0.0 is no effect. 0.5 is half the effect. 1.0 is normal. 2.0 is double the effect.
*/
@property(nonatomic) double rolloffFactor;

@end

/****************************************************************************************************/
/*!
    @class PHASEEnvelopeDistanceModelParameters
    @abstract Envelope distance model parameters.
    @discussion
        Envelope-driven attenuation over distance.
*/
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEEnvelopeDistanceModelParameters : PHASEDistanceModelParameters

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @method initWithEnvelope
    @abstract Initialize a PHASEEnvelopeDistanceModelParameters with a PHASEEnvelope
    @param envelope
        An envelope object where x values are interpreted as distance and the y values interpreted as gain.
    @return
        An instance, or nil if initialization failed.
*/
- (instancetype)initWithEnvelope:(PHASEEnvelope*)envelope NS_DESIGNATED_INITIALIZER;

/*!
    @property envelope
    @abstract A PHASEEnvelope object
    @note
        The x values are interpreted as distance and the y values are interpreted as gain.
*/
@property(nonatomic, strong, readonly) PHASEEnvelope* envelope;

@end

NS_ASSUME_NONNULL_END

#endif /* PHASEDistanceModel_h */
