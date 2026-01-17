#if !__has_include(<AVFCore/AVAudioMix.h>)
/*
	File:  AVAudioMix.h
 
	Framework:  AVFoundation
 
	Copyright 2010-2023 Apple Inc. All rights reserved.
 
 */

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVAudioProcessingSettings.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMBase.h>
#import <CoreMedia/CMTime.h>
#import <CoreMedia/CMTimeRange.h>

#define AVF_AUDIO_PROCESSING_TAP_AVAILABLE (__has_include(<MediaToolbox/MTAudioProcessingTap.h>))

#if AVF_AUDIO_PROCESSING_TAP_AVAILABLE
#import <MediaToolbox/MTAudioProcessingTap.h>
#endif

/*!
 
 @class          AVAudioMix
 
 @abstract       Allows custom audio processing to be performed on audio tracks during playback or other operations.
 
*/

@class AVAudioMixInternal;
@class AVAudioMixInputParameters;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0))
@interface AVAudioMix : NSObject <NSCopying, NSMutableCopying> {
@private
    AVAudioMixInternal    *_audioMix;
}

/* Indicates parameters for inputs to the mix; an NSArray of instances of AVAudioMixInputParameters. Note that an instance of AVAudioMixInputParameters is not required for each audio track that contributes to the mix; audio for those without associated AVAudioMixInputParameters will be included in the mix, processed according to default behavior.  */
@property (nonatomic, readonly, copy) NSArray<AVAudioMixInputParameters *> *inputParameters;

@end


@class AVMutableAudioMixInternal;

NS_SWIFT_NONSENDABLE
API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0))
@interface AVMutableAudioMix : AVAudioMix {
@private
    AVMutableAudioMixInternal    *_mutableAudioMix __attribute__((unused));
}

/*  
 @method		audioMix
 @abstract		Returns a new instance of AVMutableAudioMix with a nil array of inputParameters.
*/
+ (instancetype)audioMix;

/*!
 @property		inputParameters
 @abstract		Indicates parameters for inputs to the mix; an NSArray of instances of AVAudioMixInputParameters.
 @discussion	Note that an instance of AVAudioMixInputParameters is not required for each audio track that contributes to the mix; audio for those without associated AVAudioMixInputParameters will be included in the mix, processed according to default behavior.
*/
@property (nonatomic, copy) NSArray<AVAudioMixInputParameters *> *inputParameters;

@end


/*!
 
 @class          AVAudioMixInputParameters
 
 @abstract       Provides time-varying parameters to apply to an input of an audio mix. Audio volume is currently supported as a time-varying parameter.
 
 @discussion
 
 Use an instance of AVAudioMixInputParameters to apply audio volume ramps for an input to an audio mix.
 AVAudioMixInputParameters are associated with audio tracks via the trackID property.
 
 Notes on audio volume ramps:
 
 Before the first time at which a volume is set, a volume of 1.0 used; after the last time for which a volume has been set, the last volume is used.
 Within the timeRange of a volume ramp, the volume is interpolated between the startVolume and endVolume of the ramp.
 For example, setting the volume to 1.0 at time 0 and also setting a volume ramp from a volume of 0.5 to 0.2 with a timeRange of [4.0, 5.0]
 results in an audio volume parameters that hold the volume constant at 1.0 from 0.0 sec to 4.0 sec, then cause it to jump to 0.5 and
 descend to 0.2 from 4.0 sec to 9.0 sec, holding constant at 0.2 thereafter.
*/

@class AVAudioMixInputParametersInternal;

API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0))
@interface AVAudioMixInputParameters : NSObject <NSCopying, NSMutableCopying> {
@private
    AVAudioMixInputParametersInternal    *_inputParameters;
}

/*!
 @property		trackID
 @abstract		Indicates the trackID of the audio track to which the parameters should be applied.
*/
@property (nonatomic, readonly) CMPersistentTrackID trackID;

/*!
 @property		audioTimePitchAlgorithm
 @abstract		Indicates the processing algorithm used to manage audio pitch at varying rates and for scaled audio edits.
 @discussion
   Constants for various time pitch algorithms, e.g. AVAudioTimePitchSpectral, are defined in AVAudioProcessingSettings.h.
   Can be nil, in which case the audioTimePitchAlgorithm set on the AVPlayerItem, AVAssetExportSession, or AVAssetReaderAudioMixOutput on which the AVAudioMix is set will be used for the associated track.
*/
@property (nonatomic, readonly, copy, nullable) AVAudioTimePitchAlgorithm audioTimePitchAlgorithm API_AVAILABLE(macos(10.10), ios(7.0), tvos(9.0), watchos(1.0), visionos(1.0));


#if AVF_AUDIO_PROCESSING_TAP_AVAILABLE

/*!
 @property		audioTapProcessor
 @abstract		Indicates the audio processing tap that will be used for the audio track.
*/
@property (nonatomic, readonly, retain, nullable) __attribute__((NSObject)) MTAudioProcessingTapRef audioTapProcessor API_AVAILABLE(macos(10.9), ios(6.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

#endif

/*  
 @method		getVolumeRampForTime:startVolume:endVolume:timeRange:
 @abstract		Obtains the volume ramp that includes the specified time.
 @param			time
   If a ramp with a timeRange that contains the specified time has been set, information about the effective ramp for that time is supplied.
   Otherwise, information about the first ramp that starts after the specified time is supplied.
 @param			startVolume
   A pointer to a float to receive the starting volume value for the volume ramp. May be NULL.
 @param			endVolume
   A pointer to a float to receive the ending volume value for the volume ramp. May be NULL.
 @param			timeRange
   A pointer to a CMTimeRange to receive the timeRange of the volume ramp. May be NULL.
 @result
   An indication of success. NO will be returned if the specified time is beyond the duration of the last volume ramp that has been set.
*/
- (BOOL)getVolumeRampForTime:(CMTime)time startVolume:(nullable float *)startVolume endVolume:(nullable float *)endVolume timeRange:(nullable CMTimeRange *)timeRange;

@end


@class AVAssetTrack;
@class AVPlayerItemTrack;
@class AVMutableAudioMixInputParametersInternal;

NS_SWIFT_NONSENDABLE
API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0))
@interface AVMutableAudioMixInputParameters : AVAudioMixInputParameters {
@private
    AVMutableAudioMixInputParametersInternal    *_mutableInputParameters __attribute__((unused));
}

/*  
 @method		audioMixInputParametersWithTrack:
 @abstract		Returns a new instance of AVMutableAudioMixInputParameters with no volume ramps and a trackID set to the specified track's trackID.
 @param			track
   A reference to an AVAssetTrack.
*/
+ (instancetype)audioMixInputParametersWithTrack:(nullable AVAssetTrack *)track;

/*  
 @method		audioMixInputParameters
 @abstract		Returns a new instance of AVMutableAudioMixInputParameters with no volume ramps and a trackID initialized to kCMPersistentTrackID_Invalid.
*/
+ (instancetype)audioMixInputParameters;

/*!
 @property		trackID
 @abstract		Indicates the trackID of the audio track to which the parameters should be applied.
*/
@property (nonatomic) CMPersistentTrackID trackID;

/*!
 @property		audioTimePitchAlgorithm
 @abstract		Indicates the processing algorithm used to manage audio pitch at varying rates and for scaled audio edits.
 @discussion
   Constants for various time pitch algorithms, e.g. AVAudioTimePitchSpectral, are defined in AVAudioProcessingSettings.h.
   Can be nil, in which case the audioTimePitchAlgorithm set on the AVPlayerItem, AVAssetExportSession, or AVAssetReaderAudioMixOutput on which the AVAudioMix is set will be used for the associated track.
*/
@property (nonatomic, copy, nullable) AVAudioTimePitchAlgorithm audioTimePitchAlgorithm API_AVAILABLE(macos(10.10), ios(7.0), tvos(9.0), watchos(1.0), visionos(1.0));

#if AVF_AUDIO_PROCESSING_TAP_AVAILABLE

/*!
 @property		audioTapProcessor
 @abstract		Indicates the audio processing tap that will be used for the audio track.
*/
@property (nonatomic, retain, nullable) __attribute__((NSObject)) MTAudioProcessingTapRef audioTapProcessor API_AVAILABLE(macos(10.9), ios(6.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

#endif

/*  
 @method		setVolumeRampFromStartVolume:toEndVolume:timeRange:
 @abstract		Sets a volume ramp to apply during the specified timeRange.
 @discussion		This method throws an exception if the time range's start or duration is not numeric.
*/
- (void)setVolumeRampFromStartVolume:(float)startVolume toEndVolume:(float)endVolume timeRange:(CMTimeRange)timeRange;

/*  
 @method		setVolume:atTime:
 @abstract		Sets the value of the audio volume at a specific time.
 @discussion		This method throws an exception if the time is not numeric.
*/
- (void)setVolume:(float)volume atTime:(CMTime)time;

@end

NS_ASSUME_NONNULL_END


#else
#import <AVFCore/AVAudioMix.h>
#endif
