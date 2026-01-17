//
//  PHASEGroup.h
//  PHASE
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#ifndef PHASEGroup_h
#define PHASEGroup_h

#import <PHASE/PHASETypes.h>

@class PHASEEngine;

NS_ASSUME_NONNULL_BEGIN

/****************************************************************************************************/
/*!
    @interface PHASEGroup
    @discussion
        A PHASEGroup allows clients to group generator nodes for shared processing.
        Clients can set the gain and playback rate, as well as mute and solo the generator nodes in a group.
*/
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface PHASEGroup : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @method initWithIdentifier:
    @abstract Create a new group.
    @param identifier
        The identifier that uniquely represents this group.
*/
- (instancetype)initWithIdentifier:(NSString*)identifier NS_DESIGNATED_INITIALIZER;

/*!
    @method registerWithEngine
    @abstract Registers a group with a particular engine so that referenced assets can find it.
    @note
        An exception will be thrown if the engine is invalid or the group already exists.
    @param engine
        An engine object to associate this group with.
*/
- (void)registerWithEngine:(PHASEEngine*)engine
NS_SWIFT_NAME(register(engine:));

/*!
    @method unregisterFromEngine
    @abstract Unregister the group from a particular engine.
*/
- (void)unregisterFromEngine;

/*!
    @method fadeGain:duration:curveType:
    @abstract Fade the gain of this group over a specified duration and curve.
    @note
        The fade gain is applied on top of the base gain of the group.
    @param gain
        A target linear gain scalar. Values are clamped to the range [0, 1].
    @param duration
        The duration over which to ramp to the target linear gain scalar. Values must be >= 0.
        The duration is scaled by unitsPerSecond internally, so can be provided at the client's native time scale.
    @param curveType
        The type of curve function that is applied during the fade.
*/
- (void)fadeGain:(double)gain duration:(double)duration curveType:(PHASECurveType)curveType
NS_SWIFT_NAME(fadeGain(gain:duration:curveType:));

/*!
    @method fadeRate:duration:curveType:
    @abstract Fade the playback rate of this group over a specified duration and curve.
    @note
        The fade gain is applied on top of the base gain of the group.
    @param rate
        A target linear rate scalar. Values are clamped to the range [0.25, 4.0].
    @param duration
        The duration over which to ramp to the target linear rate scalar. Values must be >= 0.
        The duration is scaled by unitsPerSecond internally, so can be provided at the client's native time scale.
    @param curveType
        The type of curve function that is applied during the fade.
*/
- (void)fadeRate:(double)rate duration:(double)duration curveType:(PHASECurveType)curveType
NS_SWIFT_NAME(fadeRate(rate:duration:curveType:));

/*!
    @method mute
    @abstract Mute the group.
*/
- (void)mute;

/*!
    @method unmute
    @abstract Unmute the group.
*/
- (void)unmute;

/*!
    @method solo
    @abstract Solo the group.
*/
- (void)solo;

/*!
    @method unsolo
    @abstract Unsolo the group.
*/
- (void)unsolo;

/*!
    @property identifier
    @abstract The identifier that uniquely represents this group.
*/
@property(nonatomic, readonly) NSString* identifier;

/*!
    @property gain
    @abstract Linear gain scalar.
    @note
        Values are clamped to the range [0, 1]. Default value is 1.
*/
@property(nonatomic, assign) double gain;

/*!
    @property rate
    @abstract Linear rate scalar.
    @note
        Values are clamped to the range [0.25, 4]. Default value is 1.
*/
@property(nonatomic, assign) double rate;

/*!
    @property muted
    @abstract Whether or not this group is muted.
*/
@property(readonly, getter=isMuted) BOOL muted;

/*!
    @property soloed
    @abstract Whether or not this group is soloed.
*/
@property(readonly, getter=isSoloed) BOOL soloed;

@end

NS_ASSUME_NONNULL_END

#endif /* PHASEGroup_h*/
