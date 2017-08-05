//
//  MPNowPlayingInfoLanguageOption.h
//  MobileMusicPlayer
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>
#import <MediaPlayer/AVFoundation+MPNowPlayingInfoLanguageOptionAdditions.h>

NS_ASSUME_NONNULL_BEGIN

// MPNowPlayingInfoLanguageOption and MPNowPlayingInfoLanguageOptionGroup provide
// interfaces for setting information about language options (ie audio and subtitles)
// in the current now playing information.
//
// When using AVFoundation the categories in
// <MediaPlayer/AVFoundation+MPNowPlayingInfoLanguageOptionAdditions.h>
// can automatically create these classes from various AVFoundation types.

// Common values used to to populate MPNowPlayingInfoLanguageOption's
// characteristics property.
// See the AVMediaSelectionOption documentation about Media Characteristics for more details.
MP_EXTERN NSString *const MPLanguageOptionCharacteristicIsMainProgramContent NS_AVAILABLE(10_12_2, 9_0);
MP_EXTERN NSString *const MPLanguageOptionCharacteristicIsAuxiliaryContent NS_AVAILABLE(10_12_2, 9_0);
MP_EXTERN NSString *const MPLanguageOptionCharacteristicContainsOnlyForcedSubtitles NS_AVAILABLE(10_12_2, 9_0);
MP_EXTERN NSString *const MPLanguageOptionCharacteristicTranscribesSpokenDialog NS_AVAILABLE(10_12_2, 9_0);
MP_EXTERN NSString *const MPLanguageOptionCharacteristicDescribesMusicAndSound NS_AVAILABLE(10_12_2, 9_0);
MP_EXTERN NSString *const MPLanguageOptionCharacteristicEasyToRead NS_AVAILABLE(10_12_2, 9_0);
MP_EXTERN NSString *const MPLanguageOptionCharacteristicDescribesVideo NS_AVAILABLE(10_12_2, 9_0);
MP_EXTERN NSString *const MPLanguageOptionCharacteristicLanguageTranslation NS_AVAILABLE(10_12_2, 9_0);
MP_EXTERN NSString *const MPLanguageOptionCharacteristicDubbedTranslation NS_AVAILABLE(10_12_2, 9_0);
MP_EXTERN NSString *const MPLanguageOptionCharacteristicVoiceOverTranslation NS_AVAILABLE(10_12_2, 9_0);

typedef NS_ENUM(NSUInteger, MPNowPlayingInfoLanguageOptionType) {
    MPNowPlayingInfoLanguageOptionTypeAudible,
    MPNowPlayingInfoLanguageOptionTypeLegible,
} NS_ENUM_AVAILABLE(10_12_2, 9_0);

// -----------------------------------------------------------------------------

/// Represents a single language option option.
MP_API(ios(9.0), tvos(9.0), macos(10.12.2))
@interface MPNowPlayingInfoLanguageOption : NSObject

- (instancetype)initWithType:(MPNowPlayingInfoLanguageOptionType)languageOptionType
                 languageTag:(NSString *)languageTag
             characteristics:(nullable NSArray<NSString *> *)languageOptionCharacteristics
                 displayName:(NSString *)displayName
                  identifier:(NSString *)identifier;

/// Represents a special case that is used to
/// represent the best legible language option based on system preferences.
/// See AVPlayerItem-selectMediaOptionAutomaticallyInMediaSelectionGroup
- (BOOL)isAutomaticLegibleLanguageOption;

/// Represents a special case that is used to
/// represent the best audible language option based on system preferences.
/// See AVPlayerItem-selectMediaOptionAutomaticallyInMediaSelectionGroup
- (BOOL)isAutomaticAudibleLanguageOption;

/// The type of language option.
@property (nonatomic, readonly) MPNowPlayingInfoLanguageOptionType languageOptionType;

/// The IETF BCP 47 language tag.
/// A nil languageTag reprsents that this option should be disabled.
/// A languageTag with the value of MPLangaugeOptionAutoLangaugeTag represents
/// that the best langauge based on the system preferences should be used.
@property (nonatomic, readonly, nullable) NSString *languageTag;

/// Characteristics describing the content of the language options.
/// See the LanguageOptionCharacteristics for the most commonly used values.
@property (nonatomic, readonly, nullable) NSArray<NSString *> *languageOptionCharacteristics;

/// A user presentable display name for this option.
@property (nonatomic, readonly, nullable) NSString *displayName;

/// A unique identifier representing this option.
@property (nonatomic, readonly, nullable) NSString *identifier;


@end

// -----------------------------------------------------------------------------

// Represents a mutually exclusive group of language options.
// Only one language option within a given group may be active at a time.
MP_API(ios(9.0), tvos(9.0), macos(10.12.2))
@interface MPNowPlayingInfoLanguageOptionGroup : NSObject

- (instancetype)initWithLanguageOptions:(NSArray<MPNowPlayingInfoLanguageOption *> *)languageOptions
                  defaultLanguageOption:(nullable MPNowPlayingInfoLanguageOption *)defaultLanguageOption
                    allowEmptySelection:(BOOL)allowEmptySelection;

/// The available language options within this group.
@property (nonatomic, readonly) NSArray<MPNowPlayingInfoLanguageOption *> *languageOptions;

/// The default language option, if any, within this group.
@property (nonatomic, readonly, nullable) MPNowPlayingInfoLanguageOption *defaultLanguageOption;

/// Indicates whether a selection in this group is required at all times.
@property (nonatomic, readonly) BOOL allowEmptySelection;

@end

NS_ASSUME_NONNULL_END
