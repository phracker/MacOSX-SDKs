#if !__has_include(<AVFCore/AVAssetVariant.h>)
/*
	File:           AVAssetVariant.h

	Framework:      AVFoundation

	Copyright © 2021-2024 Apple Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVVideoSettings.h>
#import <AVFoundation/AVMediaFormat.h>
#import <AVFoundation/AVAsynchronousKeyValueLoading.h>
#import <CoreGraphics/CGGeometry.h>
#import <CoreMedia/CMTag.h>

NS_ASSUME_NONNULL_BEGIN

@class AVMediaSelectionOption;
@class AVAssetVariantVideoAttributes;
@class AVAssetVariantVideoLayoutAttributes;
@class AVAssetVariantAudioAttributes;
@class AVAssetVariantAudioRenditionSpecificAttributes;

/// An AVAssetVariant represents a bit rate variant. Each asset contains a collection of variants that represent a combination of audio, video, text, closed captions, and subtitles for a particular bit rate. Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0))
@interface AVAssetVariant : NSObject

AV_INIT_UNAVAILABLE

/// If it is not declared, the value will be negative.
@property (nonatomic, readonly) double peakBitRate;

/// If it is not declared, the value will be negative.
@property (nonatomic, readonly) double averageBitRate;

/// Provides variant's video rendition attributes. If no video attributes are declared, it will be nil.
@property (nonatomic, readonly, nullable) AVAssetVariantVideoAttributes *videoAttributes;

/// Provides variant's audio rendition attributes. If no audio attributes are declared, it will be nil.
@property (nonatomic, readonly, nullable) AVAssetVariantAudioAttributes *audioAttributes;

/// Provides URL to media playlist corresponding to variant
@property (nonatomic, readonly) NSURL *URL API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

@end

/// Video attributes for an asset variant.
/// 
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0))
@interface AVAssetVariantVideoAttributes : NSObject

AV_INIT_UNAVAILABLE

/// Provides the video range of the variant. If it is not declared, it will be AVVideoRangeSDR.
@property (nonatomic, readonly) AVVideoRange videoRange;

/// Provides an array of video sample codec types present in the variant's renditions if any are declared. Each value in the array is a NSNumber representation of CMVideoCodecType.
@property (nonatomic, readonly) NSArray <NSNumber *> *codecTypes;

/// If it is not declared, it will be CGSizeZero.
@property (nonatomic, readonly) CGSize presentationSize;

/// If it is not declared, the value will be negative.
@property (nonatomic, readonly) double nominalFrameRate;

/// Describes the video layout attributes.
/// 
/// videoLayoutAttributes' count may be greater than one if this variant contains a collection of differing video layout media attributes over time.
@property (nonatomic, readonly) NSArray <AVAssetVariantVideoLayoutAttributes *> *videoLayoutAttributes API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

@end

/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0))
@interface AVAssetVariantVideoLayoutAttributes : NSObject

AV_INIT_UNAVAILABLE

/// Describes the stereo components. If not declared, the value will be `kCMStereoViewComponent_None`. In case of monoscopic content, the value will be `kCMStereoViewComponent_None` and incase of stereoscopic content, the value will be `(kCMStereoViewComponent_LeftEye | kCMStereoViewComponent_RightEye)`.
@property (nonatomic, readonly) CMStereoViewComponents stereoViewComponents;

/// Describes the video projection.
@property (nonatomic, readonly) CMProjectionType projectionType;

@end

/// Audio attributes for an asset variant.
/// 
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0))
@interface AVAssetVariantAudioAttributes : NSObject

AV_INIT_UNAVAILABLE

/// Provides an array of audio formats present in the variant's renditions if any are declared. Each value in the array is a NSNumber representation of AudioFormatID.
@property (nonatomic, readonly) NSArray <NSNumber *> *formatIDs;

/// Provides attributes for a specific audio media selection option. If no rendition specific attributes are declared, it will be nil.
/// 
/// - Parameter mediaSelectionOption: The option to return rendition specific information for.
- (nullable AVAssetVariantAudioRenditionSpecificAttributes *)renditionSpecificAttributesForMediaOption:(AVMediaSelectionOption *)mediaSelectionOption;

@end

/// Audio rendition attributes for an asset variant.
/// 
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0))
@interface AVAssetVariantAudioRenditionSpecificAttributes : NSObject

/// If it is not declared, the value will be negative.
/// 
/// A channel count greater than two indicates that the variant offers a rich multichannel authoring.
@property (nonatomic, readonly) NSInteger channelCount;

/// Indicates that the variant is best suited for delivery to headphones.
/// 
/// A binaural variant may originate from a direct binaural recording or from the processing of a multichannel audio source.
@property (nonatomic, readonly, getter=isBinaural) BOOL binaural API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));

/// Indicates that this variant contains virtualized or otherwise pre-processed audio content that is suitable for a variety of purposes.
/// 
/// If a variant audio redition is immersive it is eligible for rendering either to headphones or speakers.
@property (nonatomic, readonly, getter=isImmersive) BOOL immersive API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/// Indicates that this variant is declared as a downmix derivative of other media of greater channel count.
/// 
/// If one or more multichannel variants are also provided, the dowmix is assumed to be compatible in its internal timing and other attributes with those variants. Typically this is because it has been derived from the same source. A downmix can be used as a suitable substitute for a multichannel variant under some conditions.
@property (nonatomic, readonly, getter=isDownmix) BOOL downmix API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0), watchos(9.0), visionos(1.0));

@end

/// The qualifier of an asset variant.
/// 
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(10.0), visionos(1.0))
@interface AVAssetVariantQualifier : NSObject <NSCopying>

AV_INIT_UNAVAILABLE

/// Returns a qualifer for a predicate.
/// 
/// - Parameter predicate: The variant predicate. Must be a valid, non-nil NSPredicate.
+ (instancetype)assetVariantQualifierWithPredicate:(nonnull NSPredicate *)predicate;

/// Returns a qualifer for a particular asset variant.
/// 
/// - Parameter variant: A variant obtained from the -[AVAsset variants] or -[AVAssetDownloadConfiguration playableVariants]. Must be a valid, non-nil AVAssetVariant.
+ (instancetype)assetVariantQualifierWithVariant:(nonnull AVAssetVariant *)variant;

/// Returns a qualifer for finding variant with minimum value in the input key path.
/// 
/// - Parameter keyPath: AVAssetVariant keyPath. Allowed keyPath values are peakBitRate, averageBitRate, videoAttributes.presentationSize. Must be a valid, non-nil NSString.
+ (instancetype)assetVariantQualifierForMinimumValueInKeyPath:(nonnull NSString *)keyPath API_UNAVAILABLE(macos, ios, tvos, watchos, visionos);

/// Returns a qualifer for finding variant with maximum value in the input key path
/// 
/// - Parameter keyPath: AVAssetVariant keyPath. Allowed keyPath values are peakBitRate, averageBitRate, videoAttributes.presentationSize. Must be a valid, non-nil NSString.
+ (instancetype)assetVariantQualifierForMaximumValueInKeyPath:(nonnull NSString *)keyPath API_UNAVAILABLE(macos, ios, tvos, watchos, visionos);

/// Creates a NSPredicate for audio channel count which can be used with other NSPredicates to express variant preferences.
/// 
/// - Parameter channelCount: The RHS value for the channel count in the predicate equation.
/// - Parameter mediaSelectionOption: The audio media selection option under consideration.
/// - Parameter operatorType: The valid values are NSLessThanPredicateOperatorType, NSLessThanOrEqualToPredicateOperatorType, NSGreaterThanPredicateOperatorType, NSGreaterThanOrEqualToPredicateOperatorType, NSEqualToPredicateOperatorType and NSNotEqualToPredicateOperatorType.
+ (NSPredicate *)predicateForChannelCount:(NSInteger)channelCount mediaSelectionOption:(nullable AVMediaSelectionOption *)mediaSelectionOption operatorType:(NSPredicateOperatorType)operatorType;

/// Creates a NSPredicate for binaural which can be used with other NSPredicates to express variant preferences.
/// 
/// - Parameter isBinaural: The RHS value for the value of isBinauralAudio in the predicate equation.
/// - Parameter mediaSelectionOption: The audio media selection option under consideration.
+ (NSPredicate *)predicateForBinauralAudio:(BOOL)isBinauralAudio mediaSelectionOption:(nullable AVMediaSelectionOption *)mediaSelectionOption API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/// Creates a NSPredicate for immersive audio which can be used with other NSPredicates to express variant preferences.
/// 
/// - Parameter isImmersiveAudio: The RHS value for the value of isImmersiveAudio in the predicate equation.
/// - Parameter mediaSelectionOption: The audio media selection option under consideration.
+ (NSPredicate *)predicateForImmersiveAudio:(BOOL)isImmersiveAudio mediaSelectionOption:(nullable AVMediaSelectionOption *)mediaSelectionOption API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/// Creates a NSPredicate for immersive audio which can be used with other NSPredicates to express variant preferences.
/// 
/// - Parameter isDownmixAudio: The RHS value for the value of isDownmixAudio in the predicate equation.
/// - Parameter mediaSelectionOption: The audio media selection option under consideration.
+ (NSPredicate *)predicateForDownmixAudio:(BOOL)isDownmixAudio mediaSelectionOption:(nullable AVMediaSelectionOption *)mediaSelectionOption API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0), watchos(10.0), visionos(1.0));

/// Creates a NSPredicate for presentation size width which can be used with other NSPredicates to express variant preferences.
/// 
/// - Parameter width: The RHS value for the presentation size width in the predicate equation.
/// - Parameter operatorType: The valid values are NSLessThanPredicateOperatorType, NSLessThanOrEqualToPredicateOperatorType, NSGreaterThanPredicateOperatorType, NSGreaterThanOrEqualToPredicateOperatorType, NSEqualToPredicateOperatorType and NSNotEqualToPredicateOperatorType.
+ (NSPredicate *)predicateForPresentationWidth:(CGFloat)width operatorType:(NSPredicateOperatorType)operatorType;

/// Creates a NSPredicate for presentation size height which can be used with other NSPredicates to express variant preferences.
/// 
/// - Parameter height: The RHS value for the presentation size height in the predicate equation.
/// - Parameter operatorType: The valid values are NSLessThanPredicateOperatorType, NSLessThanOrEqualToPredicateOperatorType, NSGreaterThanPredicateOperatorType, NSGreaterThanOrEqualToPredicateOperatorType, NSEqualToPredicateOperatorType and NSNotEqualToPredicateOperatorType.
+ (NSPredicate *)predicateForPresentationHeight:(CGFloat)height operatorType:(NSPredicateOperatorType)operatorType;

/// Creates a NSPredicate for audio sample rate which can be used with other NSPredicates to express variant preferences.
/// 
/// - Parameter sampleRate: The RHS value for the sample rate in the predicate equation.
/// - Parameter mediaSelectionOption: The audio media selection option under consideration.
/// - Parameter operatorType: The valid values are NSLessThanPredicateOperatorType, NSLessThanOrEqualToPredicateOperatorType, NSGreaterThanPredicateOperatorType, NSGreaterThanOrEqualToPredicateOperatorType, NSEqualToPredicateOperatorType and NSNotEqualToPredicateOperatorType.
+ (NSPredicate *)predicateForAudioSampleRate:(double)sampleRate mediaSelectionOption:(nullable AVMediaSelectionOption *)mediaSelectionOption operatorType:(NSPredicateOperatorType)operatorType API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0), visionos(2.0));

/// Creates a NSPredicate for audio channel count which can be used with other NSPredicates to express variant preferences.
/// 
/// Predicate will be evaluated on the media selection option selected for the asset.
/// Media selection options for primary assets may be specified in the AVAssetDownloadConfiguration mediaSelections property.
/// Media selection options for interstitial assets may be circumscribed by -[AVAssetDownloadConfiguration setInterstitialMediaSelectionCriteria: forMediaCharacteristic:].
/// 
/// - Parameter channelCount: The RHS value for the channel count in the predicate equation.
/// - Parameter operatorType: The valid values are NSLessThanPredicateOperatorType, NSLessThanOrEqualToPredicateOperatorType, NSGreaterThanPredicateOperatorType, NSGreaterThanOrEqualToPredicateOperatorType, NSEqualToPredicateOperatorType and NSNotEqualToPredicateOperatorType.
+ (NSPredicate *)predicateForChannelCount:(NSInteger)channelCount operatorType:(NSPredicateOperatorType)operatorType API_AVAILABLE(macos(15.5), ios(18.5), tvos(18.5), watchos(11.5), visionos(2.5));

/// Creates a NSPredicate for binaural which can be used with other NSPredicates to express variant preferences.
/// 
/// - Parameter isBinaural: The RHS value for the value of isBinauralAudio in the predicate equation.
+ (NSPredicate *)predicateForBinauralAudio:(BOOL)isBinauralAudio API_AVAILABLE(macos(15.5), ios(18.5), tvos(18.5), watchos(11.5), visionos(2.5));

/// Creates a NSPredicate for immersive audio which can be used with other NSPredicates to express variant preferences.
/// 
/// Predicate will be evaluated on the media selection option selected for the asset.
/// Media selection options for primary assets may be specified in the AVAssetDownloadConfiguration mediaSelections property.
/// Media selection options for interstitial assets may be circumscribed by -[AVAssetDownloadConfiguration setInterstitialMediaSelectionCriteria: forMediaCharacteristic:].
/// 
/// - Parameter isImmersiveAudio: The RHS value for the value of isImmersiveAudio in the predicate equation.
+ (NSPredicate *)predicateForImmersiveAudio:(BOOL)isImmersiveAudio API_AVAILABLE(macos(15.5), ios(18.5), tvos(18.5), watchos(11.5), visionos(2.5));

/// Creates a NSPredicate for immersive audio which can be used with other NSPredicates to express variant preferences.
/// 
/// Predicate will be evaluated on the media selection option selected for the asset.
/// Media selection options for primary assets may be specified in the AVAssetDownloadConfiguration mediaSelections property.
/// Media selection options for interstitial assets may be circumscribed by -[AVAssetDownloadConfiguration setInterstitialMediaSelectionCriteria: forMediaCharacteristic:].
/// 
/// - Parameter isDownmixAudio: The RHS value for the value of isDownmixAudio in the predicate equation.
+ (NSPredicate *)predicateForDownmixAudio:(BOOL)isDownmixAudio API_AVAILABLE(macos(15.5), ios(18.5), tvos(18.5), watchos(11.5), visionos(2.5));

/// Creates a NSPredicate for audio sample rate which can be used with other NSPredicates to express variant preferences.
/// 
/// Predicate will be evaluated on the media selection option selected for the asset.
/// Media selection options for primary assets may be specified in the AVAssetDownloadConfiguration mediaSelections property.
/// Media selection options for interstitial assets may be circumscribed by -[AVAssetDownloadConfiguration setInterstitialMediaSelectionCriteria: forMediaCharacteristic:].
/// 
/// - Parameter sampleRate: The RHS value for the sample rate in the predicate equation.
/// - Parameter operatorType: The valid values are NSLessThanPredicateOperatorType, NSLessThanOrEqualToPredicateOperatorType, NSGreaterThanPredicateOperatorType, NSGreaterThanOrEqualToPredicateOperatorType, NSEqualToPredicateOperatorType and NSNotEqualToPredicateOperatorType.
+ (NSPredicate *)predicateForAudioSampleRate:(double)sampleRate operatorType:(NSPredicateOperatorType)operatorType API_AVAILABLE(macos(15.5), ios(18.5), tvos(18.5), watchos(11.5), visionos(2.5));

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVAssetVariant.h>
#endif
