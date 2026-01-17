//
//  SRAcousticSettings.h
//  SensorKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SensorKit/SRDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, SRAcousticSettingsSampleLifetime) {
    SRAcousticSettingsSampleLifetimeEightDays = 1,
    SRAcousticSettingsSampleLifetimeUntilUserDeletes
} API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);

typedef NS_ENUM(NSInteger, SRAcousticSettingsAccessibilityBackgroundSoundsName) {
    SRAcousticSettingsAccessibilityBackgroundSoundsNameBalancedNoise = 1,
    SRAcousticSettingsAccessibilityBackgroundSoundsNameBrightNoise,
    SRAcousticSettingsAccessibilityBackgroundSoundsNameDarkNoise,
    SRAcousticSettingsAccessibilityBackgroundSoundsNameOcean,
    SRAcousticSettingsAccessibilityBackgroundSoundsNameRain,
    SRAcousticSettingsAccessibilityBackgroundSoundsNameStream,
    SRAcousticSettingsAccessibilityBackgroundSoundsNameNight,
    SRAcousticSettingsAccessibilityBackgroundSoundsNameFire,
    SRAcousticSettingsAccessibilityBackgroundSoundsNameBabble,
    SRAcousticSettingsAccessibilityBackgroundSoundsNameSteam,
    SRAcousticSettingsAccessibilityBackgroundSoundsNameAirplane,
    SRAcousticSettingsAccessibilityBackgroundSoundsNameBoat,
    SRAcousticSettingsAccessibilityBackgroundSoundsNameBus,
    SRAcousticSettingsAccessibilityBackgroundSoundsNameTrain,
    SRAcousticSettingsAccessibilityBackgroundSoundsNameRainOnRoof,
    SRAcousticSettingsAccessibilityBackgroundSoundsNameQuietNight
} API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);

typedef NS_ENUM(NSInteger, SRAcousticSettingsAccessibilityHeadphoneAccommodationsMediaEnhanceTuning) {
    SRAcousticSettingsAccessibilityHeadphoneAccommodationsMediaEnhanceTuningBalancedTone = 1,
    SRAcousticSettingsAccessibilityHeadphoneAccommodationsMediaEnhanceTuningVocalRange,
    SRAcousticSettingsAccessibilityHeadphoneAccommodationsMediaEnhanceTuningBrightness
} API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);

typedef NS_ENUM(NSInteger, SRAcousticSettingsAccessibilityHeadphoneAccommodationsMediaEnhanceBoosting) {
    SRAcousticSettingsAccessibilityHeadphoneAccommodationsMediaEnhanceBoostingSlight = 1,
    SRAcousticSettingsAccessibilityHeadphoneAccommodationsMediaEnhanceBoostingModerate,
    SRAcousticSettingsAccessibilityHeadphoneAccommodationsMediaEnhanceBoostingStrong
} API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);

typedef NS_ENUM(NSInteger, SRAcousticSettingsAccessibilityHeadphoneAccommodationsMediaEnhanceApplication) {
    SRAcousticSettingsAccessibilityHeadphoneAccommodationsMediaEnhanceApplicationNone = 1,
    SRAcousticSettingsAccessibilityHeadphoneAccommodationsMediaEnhanceApplicationPhone,
    SRAcousticSettingsAccessibilityHeadphoneAccommodationsMediaEnhanceApplicationMedia,
    SRAcousticSettingsAccessibilityHeadphoneAccommodationsMediaEnhanceApplicationPhoneAndMedia
} API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos);

NS_SWIFT_SENDABLE
SR_EXTERN API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos)
@interface SRAcousticSettingsMusicEQ: NSObject <NSSecureCoding, NSCopying>

/*!
 *  @property soundCheckEnabled
 *
 *  @brief Sound Check is turned on/off
 */
@property (nonatomic, assign, readonly, getter=isSoundCheckEnabled) BOOL soundCheckEnabled;

/*!
 *  @property lateNightModeEnabled
 *
 *  @brief Late Night Mode is turned on/off
 *
 *  @discussion
 *  Music EQ Setting to dynamically compress system level audio
 */
@property (nonatomic, assign, readonly, getter=isLateNightModeEnabled) BOOL lateNightModeEnabled;

@end

NS_SWIFT_SENDABLE
SR_EXTERN API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos)
@interface SRAcousticSettingsAccessibilityBackgroundSounds: NSObject <NSSecureCoding, NSCopying>

/*!
 *  @property enabled
 *
 *  @brief Background Sounds is turned on/off
 *
 *  @discussion
 *  Plays background sounds to mask unwanted environmental noise.
 */
@property (nonatomic, assign, readonly, getter=isEnabled) BOOL enabled;

/*!
 *  @property soundName
 *
 *  @brief Accessibility Background sounds name
 */
@property (nonatomic, assign, readonly) SRAcousticSettingsAccessibilityBackgroundSoundsName soundName;

/*!
 *  @property relativeVolume
 *
 *  @brief Accessibility Background sounds volume
 *
 *  @discussion
 *  Background sounds volume relative to system volume. Units is a percentage.
 */
@property (nonatomic, assign, readonly) double relativeVolume;

/*!
 *  @property playWithMediaEnabled
 *
 *  @brief Background sounds is to be played while media is also playing
 */
@property (nonatomic, assign, readonly, getter=isPlayWithMediaEnabled) BOOL playWithMediaEnabled;

/*!
 *  @property relativeVolumeWithMedia
 *
 *  @brief Accessibility Background sounds volume with media
 *
 *  @discussion
 *  Background sounds volume while media is playing. Units is a percentage.
 */
@property (nonatomic, assign, readonly) double relativeVolumeWithMedia;

/*!
 *  @property stopOnLockEnabled
 *
 *  @brief Stop background sounds when iPhone is locked
 */
@property (nonatomic, assign, readonly, getter=isStopOnLockEnabled) BOOL stopOnLockEnabled;

@end

NS_SWIFT_SENDABLE
SR_EXTERN API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos)
@interface SRAcousticSettingsAccessibilityHeadphoneAccommodations: NSObject <NSSecureCoding, NSCopying>

/*!
 *  @property enabled
 *
 *  @brief Headphone Accommodations is turned on/off
 */
@property (nonatomic, assign, readonly, getter=isEnabled) BOOL enabled;

/*!
 *  @property mediaEnhanceTuning
 *
 *  @brief Tune for different range of frequencies
 *
 *  @discussion
 *  Optimize for providing audio tuning for different ranges of frequencies.
 */
@property (nonatomic, assign, readonly) SRAcousticSettingsAccessibilityHeadphoneAccommodationsMediaEnhanceTuning mediaEnhanceTuning;

/*!
 *  @property mediaEnhanceBoosting
 *
 *  @brief Soft Sounds boost level
 *
 *  @discussion
 *  Soft sounds will be boosted slightly, moderately, or strongly.
 */
@property (nonatomic, assign, readonly) SRAcousticSettingsAccessibilityHeadphoneAccommodationsMediaEnhanceBoosting mediaEnhanceBoosting;

/*!
 *  @property mediaEnhanceApplication
 *
 *  @brief Headphone Accommodations Application
 *
 *  @discussion
 *  Headphone Accommodations Apply to phone, media, or both.
 */
@property (nonatomic, assign, readonly) SRAcousticSettingsAccessibilityHeadphoneAccommodationsMediaEnhanceApplication mediaEnhanceApplication;

@end

NS_SWIFT_SENDABLE
SR_EXTERN API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos)
@interface SRAcousticSettingsAccessibility: NSObject <NSSecureCoding, NSCopying>

/*!
 *  @property leftRightBalance
 *
 *  @brief Audio volume between left and right channels
 */
@property (nonatomic, assign, readonly) double leftRightBalance;

/*!
 *  @property monoAudioEnabled
 *
 *  @brief When in mono mode, audio output is the same audio from both the left and right channels
 */
@property (nonatomic, assign, readonly, getter=isMonoAudioEnabled) BOOL monoAudioEnabled;

/*!
 *  @property backgroundSounds
 *
 *  @brief Background Sounds Settings
 */
@property (nonatomic, strong, readonly) SRAcousticSettingsAccessibilityBackgroundSounds *backgroundSounds;

/*!
 *  @property headphoneAccommodations
 *
 *  @brief Headphone Accommodations Settings
 */
@property (nonatomic, strong, readonly) SRAcousticSettingsAccessibilityHeadphoneAccommodations *headphoneAccommodations;

@end

NS_SWIFT_SENDABLE
SR_EXTERN API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos)
@interface SRAcousticSettings : NSObject <NSSecureCoding, NSCopying>

/*!
 *  @property environmentalSoundMeasurementsEnabled
 *
 *  @brief Environmental Sound Measurements
 *
 *  @discussion
 *  Setting for Apple Watch Environmental Sound Measurements.
 */
@property (nonatomic, assign, readonly, getter=isEnvironmentalSoundMeasurementsEnabled) BOOL environmentalSoundMeasurementsEnabled;

/*!
 *  @property audioExposureSampleLifetime
 *
 *  @brief Expected lifetime of headphone audio exposure samples in HealthKit
 */
@property (nonatomic, assign, readonly) SRAcousticSettingsSampleLifetime audioExposureSampleLifetime;

/*!
 *  @property headphoneSafetyAudioLevel
 *
 *  @brief Reduce Loud Audio
 *
 *  @discussion
 *  iPhone can analyze headphone audio and reduce any sound that is over a set decibel level. A nil value
 *  means the setting is disabled. If the setting is enabled, the property will hold the decibel value
 *  that headphone audio sound volume is not to exceed.
 */
@property (nonatomic, strong, readonly, nullable) NSNumber *headphoneSafetyAudioLevel;

/*!
 *  @property musicEQSettings
 *
 *  @brief Music EQ Settings
 */
@property (nonatomic, strong, readonly) SRAcousticSettingsMusicEQ *musicEQSettings;

/*!
 *  @property accessibilitySettings
 *
 *  @brief Accessibility Settings
 */
@property (nonatomic, strong, readonly) SRAcousticSettingsAccessibility *accessibilitySettings;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new  NS_UNAVAILABLE;
@end

NS_HEADER_AUDIT_END(nullability, sendability)
