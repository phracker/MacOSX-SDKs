#if !__has_include(<AVFCore/AVVideoComposition.h>)
/*
    File:  AVVideoComposition.h

	Framework:  AVFoundation
 
	Copyright 2010-2017 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVAsset.h>
#import <AVFoundation/AVVideoCompositing.h>

#import <Foundation/Foundation.h>
#import <CoreVideo/CoreVideo.h>
#import <CoreMedia/CMTime.h>
#import <CoreMedia/CMTimeRange.h>

/*!
	@class		AVVideoComposition
 
	@abstract	An AVVideoComposition object represents an immutable video composition.
 
	@discussion	
		A video composition describes, for any time in the aggregate time range of its instructions, the number and IDs of video tracks that are to be used in order to produce a composed video frame corresponding to that time. When AVFoundation's built-in video compositor is used, the instructions an AVVideoComposition contain can specify a spatial transformation, an opacity value, and a cropping rectangle for each video source, and these can vary over time via simple linear ramping functions.
 
		A client can implement their own custom video compositor by implementing the AVVideoCompositing protocol; a custom video compositor is provided with pixel buffers for each of its video sources during playback and other operations and can perform arbitrary graphical operations on them in order to produce visual output.
*/

NS_ASSUME_NONNULL_BEGIN

@class AVVideoCompositionCoreAnimationTool;
@class AVVideoCompositionInternal;
@class AVVideoCompositionLayerInstruction;
@class AVVideoCompositionInstruction;
@class CIContext;
@class CIImage;

API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@interface AVVideoComposition : NSObject <NSCopying, NSMutableCopying> {
@private
    AVVideoCompositionInternal    *_videoComposition;
}

/*  
 @method		videoCompositionWithPropertiesOfAsset:
 @abstract
   Returns a new instance of AVVideoComposition with values and instructions suitable for presenting the video tracks of the specified asset according to its temporal and geometric properties and those of its tracks.
 @param			asset		An instance of AVAsset. Ensure that the duration and tracks properties of the asset are already loaded before invoking this method.
 @result		An instance of AVVideoComposition.
 @discussion
   The returned AVVideoComposition will have instructions that respect the spatial properties and timeRanges of the specified asset's video tracks.
   It will also have the following values for its properties:
   
   	- If the asset has exactly one video track, the original timing of the source video track will be used. If the asset has more than one video track, and the nominal frame rate of any of video tracks is known, the reciprocal of the greatest known nominalFrameRate will be used as the value of frameDuration. Otherwise, a default framerate of 30fps is used.
   	- If the specified asset is an instance of AVComposition, the renderSize will be set to the naturalSize of the AVComposition; otherwise the renderSize will be set to a value that encompasses all of the asset's video tracks.
   	- A renderScale of 1.0.
   	- A nil animationTool.
 
   If the specified asset has no video tracks, this method will return an AVVideoComposition instance with an empty collection of instructions.
 
*/
+ (AVVideoComposition *)videoCompositionWithPropertiesOfAsset:(AVAsset *)asset API_AVAILABLE(macos(10.9), ios(6.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/* indicates a custom compositor class to use. The class must implement the AVVideoCompositing protocol.
   If nil, the default, internal video compositor is used */
@property (nonatomic, readonly, nullable) Class<AVVideoCompositing> customVideoCompositorClass API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/* indicates the interval which the video composition, when enabled, should render composed video frames */
@property (nonatomic, readonly) CMTime frameDuration;

/* If sourceTrackIDForFrameTiming is not kCMPersistentTrackID_Invalid, frame timing for the video composition is derived from the source asset's track with the corresponding ID. This may be used to preserve a source asset's variable frame timing. If an empty edit is encountered in the source asset’s track, the compositor composes frames as needed up to the frequency specified in frameDuration property. */
@property (nonatomic, readonly) CMPersistentTrackID sourceTrackIDForFrameTiming API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);

/* indicates the size at which the video composition, when enabled, should render */
@property (nonatomic, readonly) CGSize renderSize;

/* indicates the scale at which the video composition should render. May only be other than 1.0 for a video composition set on an AVPlayerItem */
@property (nonatomic, readonly) float renderScale API_AVAILABLE(macos(10.14), ios(4.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/* Indicates instructions for video composition via an NSArray of instances of classes implementing the AVVideoCompositionInstruction protocol.
   For the first instruction in the array, timeRange.start must be less than or equal to the earliest time for which playback or other processing will be attempted
   (note that this will typically be kCMTimeZero). For subsequent instructions, timeRange.start must be equal to the prior instruction's end time. The end time of
   the last instruction must be greater than or equal to the latest time for which playback or other processing will be attempted (note that this will often be
   the duration of the asset with which the instance of AVVideoComposition is associated).
*/
@property (nonatomic, readonly, copy) NSArray<id <AVVideoCompositionInstruction>> *instructions;

/* indicates a special video composition tool for use of Core Animation; may be nil */
@property (nonatomic, readonly, retain, nullable) AVVideoCompositionCoreAnimationTool *animationTool;

@end

/*
 @category	   AVVideoCompositionColorimetery
 @abstract
    Indicates the color space of the frames output from the video composition.
 @discussion
    Collectively the properties colorPrimaries, colorYCbCrMatrix, and colorTransferFunction define the color space that the rendered frames will be tagged with. For custom video compositing these properties are also used to specify the required color space of the source frames.

    For examples of common color spaces see AVVideoSettings.h.

    How to preserve the color space of the source frames:
 
        Decide which color space to be preserved by examining the source asset's video tracks. Copy the source track's primaries, matrix and transfer function into the video composition's colorPrimaries, colorYCbCrMatrix and colorTransferFunction respectively.

        - When using custom video compositing
			Setting these properties will cause source frames to be converted into the specified color space and tagged as such. New frames allocated using -[AVVideoCompositionRenderContext newPixelBuffer] will also be tagged correctly.

        - When using Core Image via videoCompositionWithAsset:options:applyingCIFiltersWithHandler:
			Setting these properties will cause source frames to be converted into the specified color space and tagged as such. The source frames provided as CIImages will have the appropriate CGColorSpace applied. The color space is preserved when the output CIImage is finally rendered internally.

        - When using basic compositing (i.e. AVVideoCompositionLayerInstruction)
			Setting these properties will ensure that the internal compositor renders (or passes through) frames in specified color space and are tagged as such.
*/
@interface AVVideoComposition (AVVideoCompositionColorimetery)

/*
 @property     colorPrimaries
 @abstract
    Rendering will use these primaries and frames will be tagged as such. If the value of this property is nil then the source's primaries will be propagated and used.
 @discussion
    Default is nil. Valid values are those suitable for AVVideoColorPrimariesKey. Generally set as a triple along with colorYCbCrMatrix and colorTransferFunction.
*/
@property (nonatomic, readonly, nullable) NSString *colorPrimaries API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) API_UNAVAILABLE(watchos);

/*
 @property     colorYCbCrMatrix
 @abstract
    Rendering will use this matrix and frames will be tagged as such. If the value of this property is nil then the source's matrix will be propagated and used.
 @discussion
    Default is nil. Valid values are those suitable for AVVideoYCbCrMatrixKey. Generally set as a triple along with colorPrimaries and colorTransferFunction.
*/
@property (nonatomic, readonly, nullable) NSString *colorYCbCrMatrix API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) API_UNAVAILABLE(watchos);

/*
 @property     colorTransferFunction
 @abstract
    Rendering will use this transfer function and frames will be tagged as such. If the value of this property is nil then the source's transfer function will be propagated and used.
 @discussion
    Default is nil. Valid values are those suitable for AVVideoTransferFunctionKey. Generally set as a triple along with colorYCbCrMatrix and colorYCbCrMatrix.
*/
@property (nonatomic, readonly, nullable) NSString *colorTransferFunction API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) API_UNAVAILABLE(watchos);

@end

@interface AVVideoComposition (AVVideoCompositionFiltering)

/*  
 @method		videoCompositionWithAsset:options:applyingCIFiltersWithHandler:
 @abstract
	Returns a new instance of AVVideoComposition with values and instructions that will apply the specified handler block to video frames represented as instances of CIImage.
 @param			asset		An instance of AVAsset. For best performance, ensure that the duration and tracks properties of the asset are already loaded before invoking this method.
 @result		An instance of AVVideoComposition.
 @discussion
	The returned AVVideoComposition will cause the specified handler block to be called to filter each frame of the asset's first enabled video track. The handler block should use the properties of the provided AVAsynchronousCIImageFilteringRequest and respond using finishWithImage:context: with a "filtered" new CIImage (or the provided source image for no affect). In the event of an error, respond to the request using finishWithError:. The error can be observed via AVPlayerItemFailedToPlayToEndTimeNotification, see AVPlayerItemFailedToPlayToEndTimeErrorKey in notification payload.
 
	NOTE: The returned AVVideoComposition's properties are private and support only CIFilter-based operations. Mutations are not supported, either in the values of properties of the AVVideoComposition itself or in its private instructions. If rotations or other transformations are desired, they must be accomplished via the application of CIFilters during the execution of your specified handler.

	The video composition will also have the following values for its properties:

		- The original timing of the asset's first enabled video track will be used.
		- A renderSize that encompasses the asset's first enabled video track respecting the track's preferredTransform.
		- A renderScale of 1.0.

	The default CIContext has the following properties:

		- iOS: Device RGB color space
		- OS X: sRGB color space
 
	Example usage:

		playerItem.videoComposition = [AVVideoComposition videoCompositionWithAsset:srcAsset applyingCIFiltersWithHandler:
			^(AVAsynchronousCIImageFilteringRequest *request)
			{
				NSError *err = nil;
				CIImage *filtered = myRenderer(request, &err);
				if (filtered)
					[request finishWithImage:filtered context:nil];
				else
					[request finishWithError:err];
			}];
*/
+ (AVVideoComposition *)videoCompositionWithAsset:(AVAsset *)asset
			 applyingCIFiltersWithHandler:(void (^)(AVAsynchronousCIImageFilteringRequest *request))applier API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0)) API_UNAVAILABLE(watchos);

@end


/*!
	@class		AVMutableVideoComposition
 
	@abstract	The AVMutableVideoComposition class is a mutable subclass of AVVideoComposition.
*/

@class AVMutableVideoCompositionInternal;

API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@interface AVMutableVideoComposition : AVVideoComposition {
@private
    AVMutableVideoCompositionInternal    *_mutableVideoComposition __attribute__((unused));
}

/*  
 @method		videoComposition
 @abstract		Returns a new instance of AVMutableVideoComposition.
 @discussion
   The returned AVMutableVideoComposition will have a frameDuration of kCMTimeZero, a renderSize of {0.0, 0.0}, a nil array of instructions, and a nil animationTool.
*/
+ (AVMutableVideoComposition *)videoComposition;

/*  
 @method		videoCompositionWithPropertiesOfAsset:
 @abstract
   Returns a new instance of AVMutableVideoComposition with values and instructions suitable for presenting the video tracks of the specified asset according to its temporal and geometric properties and those of its tracks.
 @param			asset		An instance of AVAsset. For best performance, ensure that the duration and tracks properties of the asset are already loaded before invoking this method.
 @result		An instance of AVMutableVideoComposition.
 @discussion
   The returned AVMutableVideoComposition will have instructions that respect the spatial properties and timeRanges of the specified asset's video tracks. The client can set sourceTrackIDForFrameTiming to kCMPersistentTrackID_Invalid and frameDuration to an appropriate value in order to specify the maximum output frame rate independent of the source track timing.
   It will also have the following values for its properties:
   
   	- If the asset has exactly one video track, the original timing of the source video track will be used. If the asset has more than one video track, and the nominal frame rate of any of video tracks is known, the reciprocal of the greatest known nominalFrameRate will be used as the value of frameDuration. Otherwise, a default framerate of 30fps is used.
   	- If the specified asset is an instance of AVComposition, the renderSize will be set to the naturalSize of the AVComposition; otherwise the renderSize will be set to a value that encompasses all of the asset's video tracks.
   	- A renderScale of 1.0.
   	- A nil animationTool.

   If the specified asset has no video tracks, this method will return an AVMutableVideoComposition instance with an empty collection of instructions.
 
*/
+ (AVMutableVideoComposition *)videoCompositionWithPropertiesOfAsset:(AVAsset *)asset API_AVAILABLE(macos(10.9), ios(6.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*
 @method		videoCompositionWithPropertiesOfAsset:prototypeInstruction:
 @abstract
    Returns a new instance of AVMutableVideoComposition with values and instructions suitable for presenting the video tracks of the specified asset according to its temporal and geometric properties and those of its tracks, and also overrides default properties with those from a prototypeInstruction.
 @param			asset		An instance of AVAsset. For best performance, ensure that the duration and tracks properties of the asset are already loaded before invoking this method.
 @param			prototypeInstruction		Custom instructions that the client can choose to override.
 @result		An instance of AVMutableVideoComposition.
 @discussion
   Also see videoCompositionWithPropertiesOfAsset:.
   The returned AVVideoComposition will have instructions that respect the spatial properties and timeRanges of the specified asset's video tracks. Anything not pertaining to spatial layout and timing, such as background color for their composition or post-processing behaviors, is eligible to be specified via a prototype instruction.
   Example: To add a background color,
   myPrototypeInstruction = [[AVMutableVideoCompositionInstruction alloc] init];
   myPrototypeInstruction.backgroundColor = myCGColorRef; // Do not use constant CGColorRef colors here.
   myVideoComposition = [AVVideoComposition videoCompositionWithPropertiesOfAsset:myAsset prototypeInstruction:myPrototypeInstruction];
 
 */
+ (AVMutableVideoComposition *)videoCompositionWithPropertiesOfAsset:(AVAsset *)asset prototypeInstruction:(AVVideoCompositionInstruction *)prototypeInstruction API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);

/* indicates the custom compositor class to use. If nil, the default, internal video compositor is used */
@property (nonatomic, retain, nullable) Class<AVVideoCompositing> customVideoCompositorClass API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/* indicates the interval which the video composition, when enabled, should render composed video frames */
@property (nonatomic) CMTime frameDuration;

/* If sourceTrackIDForFrameTiming is not kCMPersistentTrackID_Invalid, frame timing for the video composition is derived from the source asset's track with the corresponding ID. This may be used to preserve a source asset's variable frame timing. If an empty edit is encountered in the source asset’s track, the compositor composes frames as needed up to the frequency specified in frameDuration property. */
@property (nonatomic) CMPersistentTrackID sourceTrackIDForFrameTiming API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);

/* indicates the size at which the video composition, when enabled, should render */
@property (nonatomic) CGSize renderSize;

/* indicates the scale at which the video composition should render. May only be other than 1.0 for a video composition set on an AVPlayerItem */
@property (nonatomic) float renderScale API_AVAILABLE(macos(10.14), ios(4.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/* Indicates instructions for video composition via an NSArray of instances of classes implementing the AVVideoCompositionInstruction protocol.
   For the first instruction in the array, timeRange.start must be less than or equal to the earliest time for which playback or other processing will be attempted
   (note that this will typically be kCMTimeZero). For subsequent instructions, timeRange.start must be equal to the prior instruction's end time. The end time of
   the last instruction must be greater than or equal to the latest time for which playback or other processing will be attempted (note that this will often be
   the duration of the asset with which the instance of AVVideoComposition is associated).
*/
@property (nonatomic, copy) NSArray<id <AVVideoCompositionInstruction>> *instructions;

/* indicates a special video composition tool for use of Core Animation; may be nil */
@property (nonatomic, retain, nullable) AVVideoCompositionCoreAnimationTool *animationTool;

@end

/*
 @category	   AVMutableVideoCompositionColorimetery
 @abstract
    Indicates the color space of the frames output from the video composition.
 @discussion
    Collectively the properties colorPrimaries, colorYCbCrMatrix, and colorTransferFunction define the color space that the rendered frames will be tagged with. For custom video compositing these properties are also used to specify the required color space of the source frames.

    For examples of common color spaces see AVVideoSettings.h.

    How to preserve the color space of the source frames:
 
        Decide which color space to be preserved by examining the source asset's video tracks. Copy the source track's primaries, matrix and transfer function into the video composition's colorPrimaries, colorYCbCrMatrix and colorTransferFunction respectively.

        - When using custom video compositing
			Setting these properties will cause source frames to be converted into the specified color space and tagged as such. New frames allocated using -[AVVideoCompositionRenderContext newPixelBuffer] will also be tagged correctly.

        - When using Core Image via videoCompositionWithAsset:options:applyingCIFiltersWithHandler:
			Setting these properties will cause source frames to be converted into the specified color space and tagged as such. The source frames provided as CIImages will have the appropriate CGColorSpace applied. The color space is preserved when the output CIImage is finally rendered internally.

        - When using basic compositing (i.e. AVVideoCompositionLayerInstruction)
			Setting these properties will ensure that the internal compositor renders (or passes through) frames in specified color space and are tagged as such.
*/
@interface AVMutableVideoComposition (AVMutableVideoCompositionColorimetery)

/*
 @property     colorPrimaries
 @abstract
    Rendering will use these primaries and frames will be tagged as such. If the value of this property is nil then the source's primaries will be propagated and used.
 @discussion
    Default is nil. Valid values are those suitable for AVVideoColorPrimariesKey. Generally set as a triple along with colorYCbCrMatrix and colorTransferFunction.
*/
@property (nonatomic, copy, nullable) NSString *colorPrimaries API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) API_UNAVAILABLE(watchos);

/*
 @property     colorYCbCrMatrix
 @abstract
    Rendering will use this matrix and frames will be tagged as such. If the value of this property is nil then the source's matrix will be propagated and used.
 @discussion
    Default is nil. Valid values are those suitable for AVVideoYCbCrMatrixKey. Generally set as a triple along with colorPrimaries and colorTransferFunction.
*/
@property (nonatomic, copy, nullable) NSString *colorYCbCrMatrix API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) API_UNAVAILABLE(watchos);

/*
 @property     colorTransferFunction
 @abstract
    Rendering will use this transfer function and frames will be tagged as such. If the value of this property is nil then the source's transfer function will be propagated and used.
 @discussion
    Default is nil. Valid values are those suitable for AVVideoTransferFunctionKey. Generally set as a triple along with colorYCbCrMatrix and colorYCbCrMatrix.
*/
@property (nonatomic, copy, nullable) NSString *colorTransferFunction API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) API_UNAVAILABLE(watchos);

@end

@interface AVMutableVideoComposition (AVMutableVideoCompositionFiltering)

/*  
 @method		videoCompositionWithAsset:options:applyingCIFiltersWithHandler:
 @abstract
	Returns a new instance of AVMutableVideoComposition with values and instructions that will apply the specified handler block to video frames represented as instances of CIImage.
 @param			asset		An instance of AVAsset. For best performance, ensure that the duration and tracks properties of the asset are already loaded before invoking this method.
 @result		An instance of AVMutableVideoComposition.
 @discussion
	The returned AVMutableVideoComposition will cause the specified handler block to be called to filter each frame of the asset's first enabled video track. The handler block should use the properties of the provided AVAsynchronousCIImageFilteringRequest and respond using finishWithImage:context: with a "filtered" new CIImage (or the provided source image for no affect). In the event of an error, respond to the request using finishWithError:. The error can be observed via AVPlayerItemFailedToPlayToEndTimeNotification, see AVPlayerItemFailedToPlayToEndTimeErrorKey in notification payload. The client can set sourceTrackIDForFrameTiming to kCMPersistentTrackID_Invalid and frameDuration to an appropriate value in order to specify the maximum output frame rate independent of the source track timing.
 
	The video composition will also have the following values for its properties:

		- The original timing of the asset's first enabled video track will be used.
		- A renderSize that encompasses the asset's first enabled video track respecting the track's preferredTransform.
		- A renderScale of 1.0.

	The default CIContext has the following properties:

		- iOS: Device RGB color space
		- OS X: sRGB color space
 
	Example usage:

		playerItem.videoComposition = [AVMutableVideoComposition videoCompositionWithAsset:srcAsset applyingCIFiltersWithHandler:
			^(AVAsynchronousCIImageFilteringRequest *request)
			{
				NSError *err = nil;
				CIImage *filtered = myRenderer(request, &err);
				if (filtered)
					[request finishWithImage:filtered context:nil];
				else
					[request finishWithError:err];
			}];
*/
+ (AVMutableVideoComposition *)videoCompositionWithAsset:(AVAsset *)asset
			 applyingCIFiltersWithHandler:(void (^)(AVAsynchronousCIImageFilteringRequest *request))applier API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0)) API_UNAVAILABLE(watchos);

@end

/*!
	@class		AVVideoCompositionInstruction
 
	@abstract	An AVVideoCompositionInstruction object represents an operation to be performed by a compositor.
 
	@discussion
		An AVVideoComposition object maintains an array of instructions to perform its composition.
*/


@class AVVideoCompositionInstructionInternal;

API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@interface AVVideoCompositionInstruction : NSObject <NSSecureCoding, NSCopying, NSMutableCopying, AVVideoCompositionInstruction> {
@private
	AVVideoCompositionInstructionInternal	*_instruction;
}

/* Indicates the timeRange during which the instruction is effective. Note requirements for the timeRanges of instructions described in connection with AVVideoComposition's instructions key above. */
@property (nonatomic, readonly) CMTimeRange timeRange;

/* Indicates the background color of the composition. Solid BGRA colors only are supported; patterns and other color refs that are not supported will be ignored.
   If the background color is not specified the video compositor will use a default backgroundColor of opaque black.
   If the rendered pixel buffer does not have alpha, the alpha value of the backgroundColor will be ignored. */
@property (nonatomic, readonly, retain, nullable) __attribute__((NSObject)) CGColorRef backgroundColor;

/* Provides an array of instances of AVVideoCompositionLayerInstruction that specify how video frames from source tracks should be layered and composed.
   Tracks are layered in the composition according to the top-to-bottom order of the layerInstructions array; the track with trackID of the first instruction
   in the array will be layered on top, with the track with the trackID of the second instruction immediately underneath, etc.
   If this key is nil, the output will be a fill of the background color. */
@property (nonatomic, readonly, copy) NSArray<AVVideoCompositionLayerInstruction *> *layerInstructions;

/* If NO, indicates that post-processing should be skipped for the duration of this instruction.  YES by default.
   See +[AVVideoCompositionCoreAnimationTool videoCompositionToolWithPostProcessingAsVideoLayer:inLayer:].*/
@property (nonatomic, readonly) BOOL enablePostProcessing;

/* List of video track IDs required to compose frames for this instruction. The value of this property is computed from the layer instructions. */
@property (nonatomic, readonly) NSArray<NSValue *> *requiredSourceTrackIDs API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/* If the video composition result is one of the source frames for the duration of the instruction, this property
   returns the corresponding track ID. The compositor won't be run for the duration of the instruction and the proper source
   frame will be used instead. The value of this property is computed from the layer instructions */
@property (nonatomic, readonly) CMPersistentTrackID passthroughTrackID API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos); // kCMPersistentTrackID_Invalid if not a passthrough instruction

@end

/*!
	@class		AVMutableVideoCompositionInstruction
 
	@abstract	An AVMutableVideoCompositionInstruction object represents an operation to be performed by a compositor.
 
	@discussion
		An AVVideoComposition object maintains an array of instructions to perform its composition.
*/

@class AVMutableVideoCompositionInstructionInternal;

API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@interface AVMutableVideoCompositionInstruction : AVVideoCompositionInstruction {
@private
	AVMutableVideoCompositionInstructionInternal	*_mutableInstruction __attribute__((unused));
}

/*  
 @method		videoCompositionInstruction
 @abstract		Returns a new instance of AVMutableVideoCompositionInstruction.
 @discussion
   The returned AVMutableVideoCompositionInstruction will have a timeRange of kCMTimeRangeInvalid, a NULL backgroundColor, and a nil array of layerInstructions.
*/
+ (instancetype)videoCompositionInstruction;

/* Indicates the timeRange during which the instruction is effective. Note requirements for the timeRanges of instructions described in connection with AVVideoComposition's instructions key above. */
@property (nonatomic, assign) CMTimeRange timeRange;

/* Indicates the background color of the composition. Solid BGRA colors only are supported; patterns and other color refs that are not supported will be ignored.
   If the background color is not specified the video compositor will use a default backgroundColor of opaque black.
   If the rendered pixel buffer does not have alpha, the alpha value of the backgroundColor will be ignored. */
@property (nonatomic, retain, nullable) __attribute__((NSObject)) CGColorRef backgroundColor;

/* Provides an array of instances of AVVideoCompositionLayerInstruction that specify how video frames from source tracks should be layered and composed.
   Tracks are layered in the composition according to the top-to-bottom order of the layerInstructions array; the track with trackID of the first instruction
   in the array will be layered on top, with the track with the trackID of the second instruction immediately underneath, etc.
   If this key is nil, the output will be a fill of the background color. */
@property (nonatomic, copy) NSArray<AVVideoCompositionLayerInstruction *> *layerInstructions;

/* If NO, indicates that post-processing should be skipped for the duration of this instruction.  YES by default.
   See +[AVVideoCompositionCoreAnimationTool videoCompositionToolWithPostProcessingAsVideoLayer:inLayer:].*/
@property (nonatomic, assign) BOOL enablePostProcessing;

@end

/*!
	@class		AVVideoCompositionLayerInstruction
 
	@abstract	An AVVideoCompositionLayerInstruction object represents the transform, opacity, and cropping ramps to apply to a given track.
*/

@class AVVideoCompositionLayerInstructionInternal;

API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@interface AVVideoCompositionLayerInstruction : NSObject <NSSecureCoding, NSCopying, NSMutableCopying> {
@private
	AVVideoCompositionLayerInstructionInternal	*_layerInstruction;
};

/* Indicates the trackID of the source track to which the compositor will apply the instruction. */
@property (nonatomic, readonly, assign) CMPersistentTrackID trackID;

/*  
 @method		getTransformRampForTime:startTransform:endTransform:timeRange:
 @abstract		Obtains the transform ramp that includes the specified time.
 @param			time
   If a ramp with a timeRange that contains the specified time has been set, information about the effective ramp for that time is supplied.
   Otherwise, information about the first ramp that starts after the specified time is supplied.
 @param			startTransform
   A pointer to a float to receive the starting transform value for the transform ramp. May be NULL.
 @param			endTransform
   A pointer to a float to receive the ending transform value for the transform ramp. May be NULL.
 @param			timeRange
   A pointer to a CMTimeRange to receive the timeRange of the transform ramp. May be NULL.
 @result
   An indication of success. NO will be returned if the specified time is beyond the duration of the last transform ramp that has been set.
*/
- (BOOL)getTransformRampForTime:(CMTime)time startTransform:(nullable CGAffineTransform *)startTransform endTransform:(nullable CGAffineTransform *)endTransform timeRange:(nullable CMTimeRange *)timeRange;

/*  
 @method		getOpacityRampForTime:startOpacity:endOpacity:timeRange:
 @abstract		Obtains the opacity ramp that includes the specified time.
 @param			time
   If a ramp with a timeRange that contains the specified time has been set, information about the effective ramp for that time is supplied.
   Otherwise, information about the first ramp that starts after the specified time is supplied.
 @param			startOpacity
   A pointer to a float to receive the starting opacity value for the opacity ramp. May be NULL.
 @param			endOpacity
   A pointer to a float to receive the ending opacity value for the opacity ramp. May be NULL.
 @param			timeRange
   A pointer to a CMTimeRange to receive the timeRange of the opacity ramp. May be NULL.
 @result
   An indication of success. NO will be returned if the specified time is beyond the duration of the last opacity ramp that has been set.
*/
- (BOOL)getOpacityRampForTime:(CMTime)time startOpacity:(nullable float *)startOpacity endOpacity:(nullable float *)endOpacity timeRange:(nullable CMTimeRange *)timeRange;

/*  
 @method		getCropRectangleRampForTime:startCropRectangle:endCropRectangle:timeRange:
 @abstract		Obtains the crop rectangle ramp that includes the specified time.
 @param			time
   If a ramp with a timeRange that contains the specified time has been set, information about the effective ramp for that time is supplied.
   Otherwise, information about the first ramp that starts after the specified time is supplied.
 @param			startCropRectangle
   A pointer to a CGRect to receive the starting crop rectangle value for the crop rectangle ramp. May be NULL.
 @param			endCropRecrangle
   A pointer to a CGRect to receive the ending crop rectangle value for the crop rectangle ramp. May be NULL.
 @param			timeRange
   A pointer to a CMTimeRange to receive the timeRange of the crop rectangle ramp. May be NULL.
 @result
   An indication of success. NO will be returned if the specified time is beyond the duration of the last crop rectangle ramp that has been set.
*/
- (BOOL)getCropRectangleRampForTime:(CMTime)time startCropRectangle:(nullable CGRect *)startCropRectangle endCropRectangle:(nullable CGRect *)endCropRectangle timeRange:(nullable CMTimeRange *)timeRange API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos);

@end

/*!
	@class		AVMutableVideoCompositionLayerInstruction
 
	@abstract	AVMutableVideoCompositionLayerInstruction is a mutable subclass of AVVideoCompositionLayerInstruction that is used to modify the transform, cropping, and opacity ramps to apply to a given track in a composition.
*/

@class AVMutableVideoCompositionLayerInstructionInternal;

API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@interface AVMutableVideoCompositionLayerInstruction : AVVideoCompositionLayerInstruction {
@private
	AVMutableVideoCompositionLayerInstructionInternal	*_mutableLayerInstruction __attribute__((unused));
};

/*  
 @method		videoCompositionLayerInstructionWithAssetTrack:
 @abstract		Returns a new instance of AVMutableVideoCompositionLayerInstruction with no transform or opacity ramps and a trackID set to the specified track's trackID.
 @param			track
   A reference to an AVAssetTrack.
*/
+ (instancetype)videoCompositionLayerInstructionWithAssetTrack:(AVAssetTrack *)track;

/*  
 @method		videoCompositionLayerInstruction
 @abstract		Returns a new instance of AVMutableVideoCompositionLayerInstruction with no transform or opacity ramps and a trackID initialized to kCMPersistentTrackID_Invalid.
*/
+ (instancetype)videoCompositionLayerInstruction;

/* Indicates the trackID of the source track to which the compositor will apply the instruction. */
@property (nonatomic, assign) CMPersistentTrackID trackID;

/*  
 @method		setTransformRampFromStartTransform:toEndTransform:timeRange:
 @abstract		Sets a transform ramp to apply during the specified timerange.
 @param			startTransform
   The transform to be applied at the starting time of the timeRange. See the discussion below of how transforms are applied to video frames.
 @param			endTransform
   The transform to be applied at the end time of the timeRange.
 @param			timeRange
   The timeRange over which the value of the transform will be interpolated between startTransform and endTransform.
 @discussion
   For purposes of spatial positioning of video frames, the origin is in the top-left corner, so
   (a) positive translation values in an affine transform move a video frame right and down; and
   (b) with an identity transform a video frame is positioned with its top-left corner in the top-left corner of the composited frame.
   Video frames shall be interpreted at their display sizes (as described by CVImageBufferGetDisplaySize,
   ie, taking pixel aspect ratio attachments into account) before any affine transform is applied.

   During a transform ramp, the affine transform is interpolated between the values set at the ramp's start time and end time.
   Before the first specified time for which a transform is set, the affine transform is held constant at the value of CGAffineTransformIdentity;
   after the last time for which a transform is set, the affine transform is held constant at that last value;
*/
- (void)setTransformRampFromStartTransform:(CGAffineTransform)startTransform toEndTransform:(CGAffineTransform)endTransform timeRange:(CMTimeRange)timeRange;

/*  
 @method		setTransform:atTime:
 @abstract		Sets a value of the transform at a time within the timeRange of the instruction.
 @param			transform
   The transform to be applied at the specified time. See the discussion below of how transforms are applied to video frames.
 @param			time
   A time value within the timeRange of the composition instruction.
 @discussion
   For purposes of spatial positioning of video frames, the origin is in the top-left corner, so
   (a) positive translation values in an affine transform move a video frame right and down; and
   (b) with an identity transform a video frame is positioned with its top-left corner in the top-left corner of the composited frame.
   Video frames shall be interpreted at their display sizes (as described by CVImageBufferGetDisplaySize,
   ie, taking pixel aspect ratio attachments into account) before any affine transform is applied.

   Sets a fixed transform to apply from the specified time until the next time at which a transform is set; this is the same as setting a flat ramp for that time range.
   Before the first specified time for which a transform is set, the affine transform is held constant at the value of CGAffineTransformIdentity;
   after the last time for which a transform is set, the affine transform is held constant at that last value;
*/
- (void)setTransform:(CGAffineTransform)transform atTime:(CMTime)time;

/*  
 @method		setOpacityRampFromStartOpacity:toEndOpacity:timeRange:
 @abstract		Sets an opacity ramp to apply during the specified timerange.
 @param			startOpacity
   The opacity to be applied at the starting time of the timeRange. The value must be between 0.0 and 1.0.
 @param			endOpacity
   The opacity to be applied at the end time of the timeRange. The value must be between 0.0 and 1.0.
 @param			timeRange
   The timeRange over which the value of the opacity will be interpolated between startOpacity and endOpacity.
 @discussion
   During an opacity ramp, opacity is computed using a linear interpolation.
   Before the first time for which an opacity is set, the opacity is held constant at 1.0; after the last specified time, the opacity is held constant at the last value.
*/
- (void)setOpacityRampFromStartOpacity:(float)startOpacity toEndOpacity:(float)endOpacity timeRange:(CMTimeRange)timeRange;

/*  
 @method		setOpacity:atTime:
 @abstract		Sets a value of the opacity at a time within the timeRange of the instruction.
 @param			opacity
   The opacity to be applied at the specified time. The value must be between 0.0 and 1.0.
 @param			time
   A time value within the timeRange of the composition instruction.
 @discussion
   Sets a fixed opacity to apply from the specified time until the next time at which an opacity is set; this is the same as setting a flat ramp for that time range.
   Before the first time for which an opacity is set, the opacity is held constant at 1.0; after the last specified time, the opacity is held constant at the last value.
*/
- (void)setOpacity:(float)opacity atTime:(CMTime)time;

/*  
 @method		setCropRectangleRampFromStartCropRectangle:toEndCropRectangle:timeRange:
 @abstract		Sets an crop rectangle ramp to apply during the specified timerange.
 @param			startCropRectangle
   The crop rectangle to be applied at the starting time of the timeRange. See the discussion below of how crop rectangles are applied to video frames.
 @param			endCropRectangle
   The crop rectangle to be applied at the end time of the timeRange.
 @param			timeRange
   The timeRange over which the value of the opacity will be interpolated between startCropRectangle and endCropRectangle.
 @discussion
   The origin of the crop rectangle is the top-left corner of the buffer clean aperture rectangle. The crop rectangle is defined in
   square pixel space, i.e. without taking the pixel aspect ratio into account. Crop rectangles extending outside of the clean aperture,
   are cropped to the clean aperture.

   During a crop rectangle ramp, the rectangle is interpolated between the values set at the ramp's start time and end time. 
   When the starting or ending rectangle is empty, interpolations take into account the origin and size of the empty rectangle.
   Before the first specified time for which a crop rectangle is set, the crop rectangle is held constant to CGRectInfinite
   after the last time for which a crop rectangle is set, the crop rectangle is held constant at that last value.
*/
- (void)setCropRectangleRampFromStartCropRectangle:(CGRect)startCropRectangle toEndCropRectangle:(CGRect)endCropRectangle timeRange:(CMTimeRange)timeRange API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*  
 @method		setCropRectangle:atTime:
 @abstract		Sets a value of the crop rectangle at a time within the timeRange of the instruction.
 @param			cropRectangle
   The crop rectangle to be applied at the specified time. See the discussion below of how crop rectangles are applied to video frames.
 @param			time
   A time value within the timeRange of the composition instruction.
 @discussion
   The origin of the crop rectangle is the top-left corner of the buffer clean aperture rectangle. The crop rectangle is defined in
   square pixel space, i.e. without taking the pixel aspect ratio into account. Crop rectangles extending outside of the clean aperture,
   are cropped to the clean aperture.

   Sets a fixed crop rectangle to apply from the specified time until the next time at which a crop rectangle is set; this is the same as setting a flat ramp for that time range.
   Before the first specified time for which a crop rectangle is set, the crop rectangle is held constant to CGRectInfinite
   after the last time for which a crop rectangle is set, the crop rectangle is held constant at that last value.
*/
- (void)setCropRectangle:(CGRect)cropRectangle atTime:(CMTime)time API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos);

@end



/*!
    @class			AVVideoCompositionCoreAnimationTool

    @abstract		A tool for using Core Animation in a video composition.
    
 @discussion
   Instances of AVVideoCompositionCoreAnimationTool are for use with offline rendering (AVAssetExportSession and AVAssetReader), not with AVPlayer.
   To synchronize real-time playback with other CoreAnimation layers, use AVSynchronizedLayer.

   Any animations will be interpreted on the video's timeline, not real-time, so 
		(a) set animation beginTimes to small positive value such as AVCoreAnimationBeginTimeAtZero rather than 0, 
		    because CoreAnimation will replace a value of 0 with CACurrentMediaTime(); 
		(b) set removedOnCompletion to NO on animations so they are not automatically removed;
		(c) do not use layers associated with UIViews.
*/

@class CALayer;
@class AVVideoCompositionCoreAnimationToolInternal;

API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@interface AVVideoCompositionCoreAnimationTool : NSObject {
@private
	AVVideoCompositionCoreAnimationToolInternal	*_videoCompositionTool;
}

/*!
 	@method						videoCompositionCoreAnimationToolWithAdditionalLayer:asTrackID:
	@abstract					Add a Core Animation layer to the video composition
	@discussion					Include a Core Animation layer as an individual track input in video composition.
								This layer should not come from, or be added to, another layer tree.
								trackID should not match any real trackID in the source. Use -[AVAsset unusedTrackID] 
								to obtain a trackID that's guaranteed not to coincide with the trackID of any track of the asset.
								AVVideoCompositionInstructions should reference trackID where the rendered animation should be included.
								For best performance, no transform should be set in the AVVideoCompositionLayerInstruction for this trackID.
								Be aware that on iOS, CALayers backing a UIView usually have their content flipped (as defined by the
								-contentsAreFlipped method). It may be required to insert a CALayer with its geometryFlipped property set
								to YES in the layer hierarchy to get the same result when attaching a CALayer to a AVVideoCompositionCoreAnimationTool
								as when using it to back a UIView.
*/
+ (instancetype)videoCompositionCoreAnimationToolWithAdditionalLayer:(CALayer *)layer asTrackID:(CMPersistentTrackID)trackID;

/*!
	@method						videoCompositionCoreAnimationToolWithPostProcessingAsVideoLayer:inLayer:
	@abstract					Compose the composited video frames with the Core Animation layer
	@discussion					Place composited video frames in videoLayer and render animationLayer 
								to produce the final frame. Normally videoLayer should be in animationLayer's sublayer tree.
								The animationLayer should not come from, or be added to, another layer tree.
								Be aware that on iOS, CALayers backing a UIView usually have their content flipped (as defined by the
								-contentsAreFlipped method). It may be required to insert a CALayer with its geometryFlipped property set
								to YES in the layer hierarchy to get the same result when attaching a CALayer to a AVVideoCompositionCoreAnimationTool
								as when using it to back a UIView.
*/
+ (instancetype)videoCompositionCoreAnimationToolWithPostProcessingAsVideoLayer:(CALayer *)videoLayer inLayer:(CALayer *)animationLayer;

/*!
	@method						videoCompositionCoreAnimationToolWithPostProcessingAsVideoLayers:inLayer:
	@abstract					Compose the composited video frames with the Core Animation layer
	@discussion					Duplicate the composited video frames in each videoLayer and render animationLayer 
								to produce the final frame. Normally videoLayers should be in animationLayer's sublayer tree.
								The animationLayer should not come from, or be added to, another layer tree.
								Be aware that on iOS, CALayers backing a UIView usually have their content flipped (as defined by the
								-contentsAreFlipped method). It may be required to insert a CALayer with its geometryFlipped property set
								to YES in the layer hierarchy to get the same result when attaching a CALayer to a AVVideoCompositionCoreAnimationTool
								as when using it to back a UIView.
*/
+ (instancetype)videoCompositionCoreAnimationToolWithPostProcessingAsVideoLayers:(NSArray<CALayer *> *)videoLayers inLayer:(CALayer *)animationLayer API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0)) API_UNAVAILABLE(watchos);

@end


@interface AVAsset (AVAssetVideoCompositionUtility)

- (CMPersistentTrackID)unusedTrackID;

@end


@protocol AVVideoCompositionValidationHandling;

@interface AVVideoComposition (AVVideoCompositionValidation)

/*!
 @method		isValidForAsset:timeRange:validationDelegate:
 @abstract
   Indicates whether the timeRanges of the receiver's instructions conform to the requirements described for them immediately above (in connection with the instructions property) and also whether all of the layer instructions have a value for trackID that corresponds either to a track of the specified asset or to the receiver's animationTool. 
 @param			asset
    Pass a reference to an AVAsset if you wish to validate the timeRanges of the instructions against the duration of the asset and the trackIDs of the layer instructions against the asset's tracks. Pass nil to skip that validation. Clients should ensure that the keys @"tracks" and @"duration" are already loaded on the AVAsset before validation is attempted.
 @param			timeRange
   A CMTimeRange.  Only those instuctions with timeRanges that overlap with the specified timeRange will be validated. To validate all instructions that may be used for playback or other processing, regardless of timeRange, pass CMTimeRangeMake(kCMTimeZero, kCMTimePositiveInfinity).
 @param			validationDelegate
   Indicates an object implementing the AVVideoCompositionValidationHandling protocol to receive information about troublesome portions of a video composition during processing of -isValidForAsset:. May be nil.
@discussion
   In the course of validation, the receiver will invoke its validationDelegate with reference to any trouble spots in the video composition.
   An exception will be raised if the delegate modifies the receiver's array of instructions or the array of layerInstructions of any AVVideoCompositionInstruction contained therein during validation.
*/
- (BOOL)isValidForAsset:(nullable AVAsset *)asset timeRange:(CMTimeRange)timeRange validationDelegate:(nullable id<AVVideoCompositionValidationHandling>)validationDelegate API_AVAILABLE(macos(10.8), ios(5.0), tvos(9.0)) API_UNAVAILABLE(watchos);

@end

@protocol AVVideoCompositionValidationHandling <NSObject>

@optional

/*!
 @method		videoComposition:shouldContinueValidatingAfterFindingInvalidValueForKey:
 @abstract
   Invoked by an instance of AVVideoComposition when validating an instance of AVVideoComposition, to report a key that has an invalid value.
 @result
   An indication of whether the AVVideoComposition should continue validation in order to report additional problems that may exist.
*/
- (BOOL)videoComposition:(AVVideoComposition *)videoComposition shouldContinueValidatingAfterFindingInvalidValueForKey:(NSString *)key API_AVAILABLE(macos(10.8), ios(5.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*!
 @method		videoComposition:shouldContinueValidatingAfterFindingEmptyTimeRange:
 @abstract
   Invoked by an instance of AVVideoComposition when validating an instance of AVVideoComposition, to report a timeRange that has no corresponding video composition instruction.
 @result
   An indication of whether the AVVideoComposition should continue validation in order to report additional problems that may exist.
*/
- (BOOL)videoComposition:(AVVideoComposition *)videoComposition shouldContinueValidatingAfterFindingEmptyTimeRange:(CMTimeRange)timeRange API_AVAILABLE(macos(10.8), ios(5.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*!
 @method		videoComposition:shouldContinueValidatingAfterFindingInvalidTimeRangeInInstruction:
 @abstract
   Invoked by an instance of AVVideoComposition when validating an instance of AVVideoComposition, to report a video composition instruction with a timeRange that's invalid, that overlaps with the timeRange of a prior instruction, or that contains times earlier than the timeRange of a prior instruction.
 @discussion
   Use CMTIMERANGE_IS_INVALID, defined in CMTimeRange.h, to test whether the timeRange itself is invalid. Refer to headerdoc for AVVideoComposition.instructions for a discussion of how timeRanges for instructions must be formulated.
 @result
   An indication of whether the AVVideoComposition should continue validation in order to report additional problems that may exist.
*/
- (BOOL)videoComposition:(AVVideoComposition *)videoComposition shouldContinueValidatingAfterFindingInvalidTimeRangeInInstruction:(id<AVVideoCompositionInstruction>)videoCompositionInstruction API_AVAILABLE(macos(10.8), ios(5.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*!
 @method		videoComposition:shouldContinueValidatingAfterFindingInvalidTrackIDInInstruction:layerInstruction:asset:
 @abstract
   Invoked by an instance of AVVideoComposition when validating an instance of AVVideoComposition, to report a video composition layer instruction with a trackID that does not correspond either to the trackID used for the composition's animationTool or to a track of the asset specified in -[AVVideoComposition isValidForAsset:timeRange:delegate:].
 @result
   An indication of whether the AVVideoComposition should continue validation in order to report additional problems that may exist.
*/
- (BOOL)videoComposition:(AVVideoComposition *)videoComposition shouldContinueValidatingAfterFindingInvalidTrackIDInInstruction:(id<AVVideoCompositionInstruction>)videoCompositionInstruction layerInstruction:(AVVideoCompositionLayerInstruction *)layerInstruction asset:(AVAsset *)asset API_AVAILABLE(macos(10.8), ios(5.0), tvos(9.0)) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVVideoComposition.h>
#endif
