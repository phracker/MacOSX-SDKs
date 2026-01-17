/*
	File:  AVOutputSettingsAssistant.h

	Framework:  AVFoundation
 
	Copyright 2012-2017 Apple Inc. All rights reserved.

*/

#import <Foundation/Foundation.h>
#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVMediaFormat.h>
#import <CoreMedia/CMFormatDescription.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString * AVOutputSettingsPreset NS_STRING_ENUM;

/*
 Use these identifiers with +[AVOutputSettingsAssistant outputSettingsAssistantWithPreset:].
 
 When source format information is supplied with these presets, the resulting video settings will not scale up the video from a smaller size.
 */
AVF_EXPORT AVOutputSettingsPreset const AVOutputSettingsPreset640x480		NS_AVAILABLE(10_9, 7_0);
AVF_EXPORT AVOutputSettingsPreset const AVOutputSettingsPreset960x540   	NS_AVAILABLE(10_9, 7_0);
AVF_EXPORT AVOutputSettingsPreset const AVOutputSettingsPreset1280x720  	NS_AVAILABLE(10_9, 7_0);
AVF_EXPORT AVOutputSettingsPreset const AVOutputSettingsPreset1920x1080		NS_AVAILABLE(10_9, 7_0);
AVF_EXPORT AVOutputSettingsPreset const AVOutputSettingsPreset3840x2160		NS_AVAILABLE(10_10, 9_0);
AVF_EXPORT AVOutputSettingsPreset const AVOutputSettingsPresetHEVC1920x1080	NS_AVAILABLE(10_13, 11_0);
AVF_EXPORT AVOutputSettingsPreset const AVOutputSettingsPresetHEVC3840x2160	NS_AVAILABLE(10_13, 11_0);

@class AVOutputSettingsAssistantInternal;

/*!
	@class AVOutputSettingsAssistant
	@abstract
		A class, each instance of which specifies a set of parameters for configuring objects that use output settings dictionaries, for example AVAssetWriter & AVAssetWriterInput, so that the resulting media file conforms to some specific criteria
	@discussion
		Instances of AVOutputSettingsAssistant are typically created using a string constant representing a specific preset configuration, such as AVOutputSettingsPreset1280x720.  Once you have an instance, its properties can be used as a guide for creating and configuring an AVAssetWriter object and one or more AVAssetWriterInput objects.  If all the suggested properties are respected, the resulting media file will conform to the criteria implied by the preset.  Alternatively, the properties of an instance can be used as a "base" configuration which can be customized to suit your individual needs.
 
		The recommendations made by an instance get better as you tell it more about the format of your source data.  For example, if you set the sourceVideoFormat property, the recommendation made by the videoSettings property will ensure that your video frames are not scaled up from a smaller size.
 */
NS_CLASS_AVAILABLE(10_9, 7_0)
@interface AVOutputSettingsAssistant : NSObject
{
@private
	AVOutputSettingsAssistantInternal *_internal;
}
AV_INIT_UNAVAILABLE

/*!
	@method availableOutputSettingsPresets
	@abstract
		Returns the list of presets that can be used to create an instance of AVOutputSettingsAssistant
	@result
		An NSArray of NSString objects, each of which is a preset identifier
	@discussion
		Each preset in the returned list can be passed in to +outputSettingsAssistantWithPreset: to create a new instance of AVOutputSettingsAssistant.
 
		On iOS, the returned array may be different between different device models.
 */
+ (NSArray<AVOutputSettingsPreset> *)availableOutputSettingsPresets NS_AVAILABLE(10_10, 7_0);

/*!
	@method outputSettingsAssistantWithPreset:
	@abstract
		Returns an instance of AVOutputSettingsAssistant corresponding to the given preset
	@param presetIdentifier
		The string identifier, for example AVOutputSettingsPreset1280x720, for the desired preset
	@result
		An instance of AVOutputSettingsAssistant with properties corresponding to the given preset, or nil if there is no such available preset.
	@discussion
		The properties of the returned object can be used as a guide for creating and configuring an AVAssetWriter object and one or more AVAssetWriterInput objects.  If all the suggested properties are respected in creating the AVAssetWriter, the resulting media file will conform to the criteria implied by the preset.
 
		Use +availableOutputSettingsPresets to get a list of presets identifiers that can be used with this method.
 */
+ (nullable instancetype)outputSettingsAssistantWithPreset:(AVOutputSettingsPreset)presetIdentifier;

/*!
	@property audioSettings
	@abstract
		A dictionary of key/value pairs, as specified in AVAudioSettings.h, to be used when e.g. creating an instance of AVAssetWriterInput
	@discussion
		The value of this property may change as a result of setting a new value for the sourceAudioFormat property.
 */
@property (nonatomic, readonly, nullable) NSDictionary<NSString *, id> *audioSettings;

/*!
	@property videoSettings
	@abstract
		A dictionary of key/value pairs, as specified in AVVideoSettings.h, to be used when e.g. creating an instance of AVAssetWriterInput
	@discussion
		The value of this property may change as a result of setting a new value for the sourceVideoFormat property.
 */
@property (nonatomic, readonly, nullable) NSDictionary<NSString *, id> *videoSettings;

/*!
	@property outputFileType
	@abstract
		A UTI indicating the type of file to be written, to be used when e.g. creating an instance of AVAssetWriter
	@discussion
		Use UTTypeCopyPreferredTagWithClass / kUTTagClassFilenameExtension to get a suitable file extension for a given file type.
 */
@property (nonatomic, readonly) AVFileType outputFileType;

@end


// Use these properties to give more information about the attributes of your source data, in order to get more informed recommendations
@interface AVOutputSettingsAssistant (AVOutputSettingsAssistant_SourceInformation)

/*!
	@property sourceAudioFormat
	@abstract
		A CMAudioFormatDescription object describing the format of you audio data
	@discussion
		Setting this property will allow the receiver to make a more informed recommendation for the audio settings that should be used.  After setting this property, you should re-query the audioSettings property to get the new recommendation.  The default value is NULL, which means that the receiver does not know anything about the format of your audio data.

		If you set a non-NULL value for this property, and are using the receiver to initialize an AVAssetWriterInput, the same format description should be used to initialize the AVAssetWriterInput, along with the dictionary from the audioSettings property.
 */
@property (nonatomic, retain, nullable) __attribute__((NSObject)) CMAudioFormatDescriptionRef sourceAudioFormat;

/*!
	@property sourceVideoFormat
	@abstract
		A CMVideoFormatDescription object describing the format of your video data
	@discussion
		Setting this property will allow the receiver to make a more informed recommendation for the video settings that should be used.  After setting this property, you should re-query the videoSettings property to get the new recommendation.  The default value is NULL, which means that the receiver does not know anything about the format of your video data.

		If you set a non-NULL value for this property, and are using the receiver to initialize an AVAssetWriterInput, the same format description should be used to initialize the AVAssetWriterInput, along with the dictionary from the videoSettings property.
 */
@property (nonatomic, retain, nullable) __attribute__((NSObject)) CMVideoFormatDescriptionRef sourceVideoFormat;

/*!
	@property sourceVideoAverageFrameDuration
	@abstract
		A CMTime describing the average frame duration (reciprocal of average frame rate) of your video data
	@discussion
		Setting this property will allow the receiver to make a more informed recommendation for the video settings that should be used.  After setting this property, you should re-query the videoSettings property to get the new recommendation.
 
		The default value is 1/30, which means that the receiver is assuming that your source video has an average frame rate of 30fps.
 
		It is an error to set this property to a value that is not positive or not numeric.  See CMTIME_IS_NUMERIC.
 */
@property (nonatomic) CMTime sourceVideoAverageFrameDuration;

/*!
	@property sourceVideoMinFrameDuration
	@abstract
		A CMTime describing the minimum frame duration (reciprocal of the maximum frame rate) of your video data
	@discussion
		Setting this property will allow the receiver to make a more informed recommendation for the video settings that should be used.  After setting this property, you should re-query the videoSettings property to get the new recommendation.
 
		If your source of video data is an instance of AVAssetReaderOutput, you can discover the minimum frame duration of your source asset using the AVAssetTrack.minFrameDuration property.
 
		The default value is 1/30, which means that the receiver is assuming that your source video has a maximum frame rate of 30fps.
 
		It is an error to set this property to a value that is not positive or not numeric.  See CMTIME_IS_NUMERIC.
 */
@property (nonatomic) CMTime sourceVideoMinFrameDuration NS_AVAILABLE(10_10, 7_0);

@end

NS_ASSUME_NONNULL_END
