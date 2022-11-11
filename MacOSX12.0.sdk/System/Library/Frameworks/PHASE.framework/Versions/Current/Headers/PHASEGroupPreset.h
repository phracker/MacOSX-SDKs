//
//  PHASEGroupPreset.h
//  PHASE
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#ifndef PHASEGroupPreset_h
#define PHASEGroupPreset_h

#import <PHASE/PHASEGroup.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark - PHASEGroupPresetSetting

/****************************************************************************************************/
/*!
    @interface PHASEGroupPresetSetting
    @abstract A PHASEGroupPresetSetting is an object that holds settings that can be applied to a PHASEGroup object.
    @discussion
        These can be either be manually created and added to a PHASEGroupPreset object, or created inline using PHASEGroupPreset addGroup.
*/
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos)
@interface PHASEGroupPresetSetting : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @method initWithGain:rate:gainCurveType:rateCurveType
    @abstract Initialize the PHASEGroupPresetSetting object with an existing PHASEGroup object.
    @param gain
        The main gain setting to apply to the group. Values are clamped to the range [0, 1]. Default value is 1.
    @param rate
        The playback rate setting to apply to the group. Values are clamped to the range [0.25, 4]. Default value is 1.
    @param gainCurveType
        The type of curve to apply to the gain as the preset changes to this new setting.
    @param rateCurveType
        The type of curve to apply to the rate as the preset changes to this new setting.
 */
- (instancetype)initWithGain:(double)gain
                        rate:(double)rate
               gainCurveType:(PHASECurveType)gainCurveType
               rateCurveType:(PHASECurveType)rateCurveType
NS_SWIFT_NAME(init(gain:rate:gainCurveType:rateCurveType:));

/*!
    @property gain
    @abstract Linear gain scalar.
    @note
        Values are clamped to the range [0, 1]. Default value is 1.
*/
@property(nonatomic, readonly) double gain;

/*!
    @property rate
    @abstract Linear rate scalar.
*/
@property(nonatomic, readonly) double rate;

/*!
    @property gainCurveType
    @abstract The type of curve to apply to the gain as the preset changes to this new setting.
*/
@property(nonatomic, readonly) PHASECurveType gainCurveType;

/*!
    @property rateCurveType
    @abstract The type of curve to apply to the rate as the preset changes to this new setting.
*/
@property(nonatomic, readonly) PHASECurveType rateCurveType;

@end

#pragma mark - PHASEGroupPreset

/****************************************************************************************************/
/*!
    @interface PHASEGroupPreset
    @abstract A PHASEGroupPreset holds a collection of PHASEGroupPresetSetting objects and other parameters to be applied all at once during playback.
    @discussion
        Initialize beforehand, and use activate or deactivate to switch to the new preset during playback.
        Activating a preset will automatically deactivate the current one.
*/
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos)
@interface PHASEGroupPreset : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @method initWithEngine
    @abstract
        Create a new PHASEGroupPreset object with a given PHASEEngine object.
    @param engine
        The PHASEEngine object to register this preset with.
    @param settings
            A dictionary containing PHASEGroupPresetSetting objects paired with PHASEGroup objects as keys.
    @param timeToTarget
        The time interval that all group settings in this preset will take to gradually fade to the new value
    @param timeToReset
        The time interval that all group settings in this preset will take to gradually fade to the unity value
    @note
        The timeToTarget and timeToReset are scaled by unitsPerSecond internally, so can be provided at the client's native time scale.
*/
- (instancetype)initWithEngine:(PHASEEngine*)engine
                      settings:(NSDictionary<NSString*, PHASEGroupPresetSetting*>*)settings
                  timeToTarget:(double)timeToTarget
                   timeToReset:(double)timeToReset NS_DESIGNATED_INITIALIZER;

/*!
    @property settings
    @abstract The collection of PHASEGroupPresetSetting objects to apply when this preset is activated.
*/
@property(nonatomic, readonly) NSDictionary<NSString*, PHASEGroupPresetSetting*>* settings;

/*!
    @property timeToTarget
    @abstract The time interval that all group settings in this preset will take to gradually fade to the new value
    @note
        The timeToTarget is scaled by unitsPerSecond internally, so can be provided at the client's native time scale.
*/
@property(nonatomic, readonly) double timeToTarget;

/*! @property timeToReset
    @abstract The time interval that all group settings in this preset will take to gradually fade to the unity value
    @note
        The timeToReset is scaled by unitsPerSecond internally, so can be provided at the client's native time scale.
*/
@property(nonatomic, readonly) double timeToReset;

/*!
    @method activate
    @abstract
        Activate this preset in the PHASEEngine object it was initialized with. The internal timeToTarget value is used.
        The current preset will be deactivated automatically.
 */
- (void)activate;

/*!
    @method activateWithTimeToTargetOverride
    @abstract
        Activate this preset in the PHASEEngine object it was initialized with.
        The current preset will be deactivated automatically.
    @param timeToTargetOverride
        Override the timeToTarget value in the preset with this value.
    @note
        The timeToTargetOverride is scaled by unitsPerSecond internally, so can be provided at the client's native time scale.
 */
- (void)activateWithTimeToTargetOverride:(double)timeToTargetOverride
NS_SWIFT_NAME(activate(timeToTargetOverride:));

/*!
    @method deactivate
    @abstract
        Deactivate this preset and return the system to default unity values. The internal timeToReset value is used.
 */
- (void)deactivate;

/*!
    @method deactivateWithTimeToResetOverride
    @abstract
        Deactivate this preset and return the system to default unity values.
    @param timeToResetOverride
        Override the timeToReset value in the preset with this value.
    @note
        The timeToResetOverride is scaled by unitsPerSecond internally, so can be provided at the client's native time scale.
 */
- (void)deactivateWithTimeToResetOverride:(double)timeToResetOverride
NS_SWIFT_NAME(deactivate(timeToResetOverride:));

@end

NS_ASSUME_NONNULL_END

#endif /* PHASEGroupPreset_h */
