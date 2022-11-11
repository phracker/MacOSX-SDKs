#if !__has_include(<AVFCore/AVAssetVariant.h>)
/*
	File:           AVAssetVariant.h

	Framework:      AVFoundation

	Copyright © 2021 Apple Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVVideoSettings.h>
#import <AVFoundation/AVMediaFormat.h>
#import <AVFoundation/AVAsynchronousKeyValueLoading.h>
#import <CoreGraphics/CGGeometry.h>

NS_ASSUME_NONNULL_BEGIN

@class AVMediaSelectionOption;
@class AVAssetVariantVideoAttributes;
@class AVAssetVariantAudioAttributes;
@class AVAssetVariantAudioRenditionSpecificAttributes;

/*!
  @class		AVAssetVariant
  @abstract		An AVAssetVariant represents a bit rate variant.
				Each asset contains a collection of variants that represent a combination of audio, video, text, closed captions, and subtitles for a particular bit rate.
*/
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
@interface AVAssetVariant : NSObject

AV_INIT_UNAVAILABLE

/*!
 @property		peakBitRate
 @abstract		If it is not declared, the value will be negative.
 */
@property (nonatomic, readonly) double peakBitRate;

/*!
 @property		averageBitRate
 @abstract		If it is not declared, the value will be negative.
 */
@property (nonatomic, readonly) double averageBitRate;

/*!
 @property		videoAttributes
 @abstract		Provides  variant's video rendition attributes. If no video attributes are declared, it will be nil.
 */
@property (nonatomic, readonly, nullable) AVAssetVariantVideoAttributes *videoAttributes;

/*!
 @property		audioAttributes
 @abstract		Provides  variant's audio rendition attributes. If no audio attributes are declared, it will be nil.
 */
@property (nonatomic, readonly, nullable) AVAssetVariantAudioAttributes *audioAttributes;

@end

API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
@interface AVAssetVariantVideoAttributes : NSObject

AV_INIT_UNAVAILABLE

/*!
 @property		videoRange
 @abstract		Provides the video range of the variant. If it is not declared, it will be AVVideoRangeSDR.
 */
@property (nonatomic, readonly) AVVideoRange videoRange;

/*!
 @property		codecTypes
 @abstract		Provides an array of video sample codec types present in the variant's renditions if any are declared. Each value in the array is a NSNumber representation of CMVideoCodecType.
 */
@property (nonatomic, readonly) NSArray <NSNumber *> *codecTypes;

/*!
 @property		presentationSize
 @abstract		If it is not declared, it will be CGSizeZero.
 */
@property (nonatomic, readonly) CGSize presentationSize;

/*!
 @property		nominalFrameRate
 @abstract		If it is not declared, the value will be negative.
 */
@property (nonatomic, readonly) double nominalFrameRate;

@end

API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
@interface AVAssetVariantAudioAttributes : NSObject

AV_INIT_UNAVAILABLE

/*!
 @property		formatIDs
 @abstract		Provides an array of audio formats present in the variant's renditions if any are declared. Each value in the array is a NSNumber representation of AudioFormatID.
 */
@property (nonatomic, readonly) NSArray <NSNumber *> *formatIDs;

/*!
 @method		renditionSpecificAttributesForMediaOption:
 @abstract		Provides attributes for a specific audio media selection option. If no rendition specific attributes are declared, it will be nil.
 @param			mediaSelectionOption
				The option to return rendition specific information for.
 */
- (nullable AVAssetVariantAudioRenditionSpecificAttributes *)renditionSpecificAttributesForMediaOption:(AVMediaSelectionOption *)mediaSelectionOption;

@end

API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0))
@interface AVAssetVariantAudioRenditionSpecificAttributes : NSObject

/*!
 @property		channelCount
 @abstract		If it is not declared, the value will be negative.
 */
@property (nonatomic, readonly) NSInteger channelCount;

@end

API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0)) API_UNAVAILABLE(watchos)
@interface AVAssetVariantQualifier : NSObject <NSCopying>

AV_INIT_UNAVAILABLE

/*!
 @method 		assetVariantQualifierWithPredicate:
 @abstract		Returns a qualifer for a predicate.
 @param			predicate
				The variant predicate.
 */
+ (instancetype)assetVariantQualifierWithPredicate:(NSPredicate *)predicate;

/*!
 @method 		assetVariantQualifierWithVariant:
 @abstract		Returns a qualifer for a particular asset variant.
 @param			variant
				A variant obtained from the -[AVAsset variants] or -[AVAssetDownloadConfiguration playableVariants].
 */
+ (instancetype)assetVariantQualifierWithVariant:(AVAssetVariant *)variant;

/*!
 @method		predicateForChannelCount:mediaSelectionOption:operatorType:
 @abstract		Creates a NSPredicate for audio channel count which can be used with other NSPredicates' to express variant preferences.
 @param			channelCount
				The RHS value for the channel count in the predicate equation.
 @param			mediaSelectionOption
				The audio media selection option under consideration.
 @param			operatorType
				The valid values are NSLessThanPredicateOperatorType, NSLessThanOrEqualToPredicateOperatorType, NSGreaterThanPredicateOperatorType, NSGreaterThanOrEqualToPredicateOperatorType, NSEqualToPredicateOperatorType and NSNotEqualToPredicateOperatorType.
 */
+ (NSPredicate *)predicateForChannelCount:(NSInteger)channelCount mediaSelectionOption:(AVMediaSelectionOption *)mediaSelectionOption operatorType:(NSPredicateOperatorType)operatorType;

/*!
 @method		predicateForPresentationWidth:operatorType:
 @abstract		Creates a NSPredicate for presentation size width which can be used with other NSPredicates to express variant preferences.
 @param			width
				The RHS value for the presentation size width in the predicate equation.
 @param			operatorType
				The valid values are NSLessThanPredicateOperatorType, NSLessThanOrEqualToPredicateOperatorType, NSGreaterThanPredicateOperatorType, NSGreaterThanOrEqualToPredicateOperatorType, NSEqualToPredicateOperatorType and NSNotEqualToPredicateOperatorType.
 */
+ (NSPredicate *)predicateForPresentationWidth:(CGFloat)width operatorType:(NSPredicateOperatorType)operatorType;

/*!
 @method		predicateForPresentationHeight:operatorType:
 @abstract		Creates a NSPredicate for presentation size height which can be used with other NSPredicates to express variant preferences.
 @param			height
				The RHS value for the presentation size height in the predicate equation.
 @param			operatorType
				The valid values are NSLessThanPredicateOperatorType, NSLessThanOrEqualToPredicateOperatorType, NSGreaterThanPredicateOperatorType, NSGreaterThanOrEqualToPredicateOperatorType, NSEqualToPredicateOperatorType and NSNotEqualToPredicateOperatorType.
 */
+ (NSPredicate *)predicateForPresentationHeight:(CGFloat)height operatorType:(NSPredicateOperatorType)operatorType;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVAssetVariant.h>
#endif
