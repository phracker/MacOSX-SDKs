//
//  PHASEDucker.h
//  PHASE
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#ifndef PHASEDucker_h
#define PHASEDucker_h

#import <PHASE/PHASETypes.h>
#import <PHASE/PHASEGroup.h>

NS_ASSUME_NONNULL_BEGIN

/****************************************************************************************************/
/*!
    @interface PHASEDucker
    @abstract A PHASEDucker is used to describe ducking behavior across different groups.
*/
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos)
@interface PHASEDucker : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @method initWithSourceGroups:targetGroups:attenuation:attackTime:releaseTime:
    @discussion
        Whenever a generator node from any source group plays, all the generator nodes in the target groups will be
        ducked by the given gain using the given attack and release times.
    @note
        The ducker is initialially inactive. The client must call activate() to make it active.
        Once a ducker is active, it will listen for generator nodes to start playback in source groups. Once triggered, it will duck its target groups.
        Deactivating a ducker will make it stop listening. Furthermore, it will enter the release phase if it has been previously triggered.
        Dealloc'ing a ducker will force the ducker into its release phase if it is actively ducking and remove it from the system when it finishes.
    @param engine
        The engine to register this ducker with.
    @param sourceGroups
        The source groups that will trigger the ducker when a sound in one of the source groups starts playback.
    @param targetGroups
        The target groups that will be ducked when a sound in one of the source groups triggers the ducker.
    @param gain
        The linear gain scalar to apply when the ducker is engaged. 0 means full attenuation. 1 is no attenuation. Values are clamped to the range [0, 1].
    @param attackTime
        The time for the attenuation gain to ramp into effect.
        This value is scaled by unitsPerSecond internally, so can be provided at the client's native time scale.
    @param releaseTime
        The time for the ducked sounds to ramp back to their original level.
        This value is scaled by unitsPerSecond internally, so can be provided at the client's native time scale.
    @param attackCurve
        The type of curve function to use during the attack phase of gain reduction.
    @param releaseCurve
        The type of curve function to use during the release phase of gain reduction.
*/
- (instancetype)initWithEngine:(PHASEEngine*)engine
                  sourceGroups:(NSSet<PHASEGroup*>*)sourceGroups
                  targetGroups:(NSSet<PHASEGroup*>*)targetGroups
                          gain:(double)gain
                    attackTime:(double)attackTime
                   releaseTime:(double)releaseTime
                   attackCurve:(PHASECurveType)attackCurve
                  releaseCurve:(PHASECurveType)releaseCurve
NS_SWIFT_NAME(init(engine:sourceGroups:targetGroups:gain:attackTime:releaseTime:attackCurve:releaseCurve:));

/*!
    @method activate
    @abstract Activates the ducker
*/
-(void)activate;

/*!
    @method deactivate
    @abstract Deactivates the ducker
*/
-(void)deactivate;

/*!
    @property sourceGroups
    @abstract The source groups that will trigger the ducker when a sound in one of the source groups starts playback.
*/
@property(nonatomic, readonly, copy) NSSet<PHASEGroup*>* sourceGroups;

/*!
    @property targetGroups
    @abstract The target groups that will be ducked when a sound in one of the source groups triggers the ducker.
*/
@property(nonatomic, readonly, copy) NSSet<PHASEGroup*>* targetGroups;

/*!
    @property active
    @abstract YES if the ducker is active; otherwise, NO.
*/
@property(readonly, getter=isActive) BOOL active;

/*!
    @property gain
    @abstract Linear gain scalar.
    @note
        Values are clamped to the range [0, 1]. Default value is 1.
*/
@property(nonatomic, readonly) double gain;

/*!
    @property attackTime
    @abstract The time for the attenuation gain to ramp into effect.
    @note
        The attack time is scaled by unitsPerSecond internally, so can be provided at the client's native time scale.
*/
@property(nonatomic, readonly) double attackTime;

/*! @property releaseTime
    @abstract The time for the ducked sounds to ramp back to their original level.
    @note
        The release time is scaled by unitsPerSecond internally, so can be provided at the client's native time scale.
*/
@property(nonatomic, readonly) double releaseTime;

/*!
    @property attackCurve
    @abstract The type of curve function to use during the attack phase of gain reduction.
*/
@property(nonatomic, readonly) PHASECurveType attackCurve;

/*!
    @property releaseCurve
    @abstract The type of curve function to use during the release phase of gain reduction.
*/
@property(nonatomic, readonly) PHASECurveType releaseCurve;

/*!
    @property identifier
    @abstract The identifier that uniquely represents this ducker.
*/
@property(nonatomic, readonly) NSString* identifier;

@end

NS_ASSUME_NONNULL_END

#endif /* PHASEDucker_h */
