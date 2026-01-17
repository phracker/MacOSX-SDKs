/*
    File:  AVVideoComposition.h

	Framework:  AVFoundation
 
	Copyright 2010-2012 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVAsset.h>

#import <Foundation/Foundation.h>
#import <CoreVideo/CoreVideo.h>
#import <CoreMedia/CMTime.h>
#import <CoreMedia/CMTimeRange.h>

@class AVVideoCompositionCoreAnimationTool;
@class AVVideoCompositionInternal;

NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVVideoComposition : NSObject <NSCopying, NSMutableCopying> {
@private
    AVVideoCompositionInternal    *_videoComposition;
}

/* indicates the interval which the video composition, when enabled, should render composed video frames */
@property (nonatomic, readonly) CMTime frameDuration;

/* indicates the size at which the video composition, when enabled, should render */
@property (nonatomic, readonly) CGSize renderSize;

#if TARGET_OS_IPHONE

/* indicates the scale at which the video composition should render. May only be other than 1.0 for a video composition set on an AVPlayerItem */
@property (nonatomic, readonly) float renderScale;

#endif // TARGET_OS_IPHONE

/* Indicates instructions for video composition via an NSArray of instances of AVVideoCompositionInstruction.
   For the first instruction in the array, timeRange.start must be less than or equal to the earliest time for which playback or other processing will be attempted
   (note that this will typically be kCMTimeZero). For subsequent instructions, timeRange.start must be equal to the prior instruction's end time. The end time of
   the last instruction must be greater than or equal to the latest time for which playback or other processing will be attempted (note that this will often be
   the duration of the asset with which the instance of AVVideoComposition is associated).
*/
@property (nonatomic, readonly, copy) NSArray *instructions;

/* indicates a special video composition tool for use of Core Animation; may be nil */
@property (nonatomic, readonly, retain) AVVideoCompositionCoreAnimationTool *animationTool;

@end


@class AVMutableVideoCompositionInternal;

NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVMutableVideoComposition : AVVideoComposition {
@private
    AVMutableVideoCompositionInternal    *_mutableVideoComposition;
}

/*  
 @method		videoComposition
 @abstract		Returns a new instance of AVMutableVideoComposition.
 @discussion
   The returned AVMutableVideoComposition will have a frameDuration of kCMTimeZero, a renderSize of {0.0, 0.0}, a nil array of instructions, and a nil animationTool.
*/
+ (AVMutableVideoComposition *)videoComposition;

/* indicates the interval which the video composition, when enabled, should render composed video frames */
@property (nonatomic) CMTime frameDuration;

/* indicates the size at which the video composition, when enabled, should render */
@property (nonatomic) CGSize renderSize;

#if TARGET_OS_IPHONE

/* indicates the scale at which the video composition should render. May only be other than 1.0 for a video composition set on an AVPlayerItem */
@property (nonatomic) float renderScale;

#endif // TARGET_OS_IPHONE

/* Indicates instructions for video composition via an NSArray of instances of AVVideoCompositionInstruction.
   For the first instruction in the array, timeRange.start must be less than or equal to the earliest time for which playback or other processing will be attempted
   (note that this will typically be kCMTimeZero). For subsequent instructions, timeRange.start must be equal to the prior instruction's end time. The end time of
   the last instruction must be greater than or equal to the latest time for which playback or other processing will be attempted (note that this will often be
   the duration of the asset with which the instance of AVVideoComposition is associated).
*/
@property (nonatomic, copy) NSArray *instructions;

/* indicates a special video composition tool for use of Core Animation; may be nil */
@property (nonatomic, retain) AVVideoCompositionCoreAnimationTool *animationTool;

@end



@class AVVideoCompositionInstructionInternal;

NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVVideoCompositionInstruction : NSObject <NSCoding, NSCopying, NSMutableCopying> {
@private
	AVVideoCompositionInstructionInternal	*_instruction;
}

/* Indicates the timeRange during which the instruction is effective. Note requirements for the timeRanges of instructions described in connection with AVVideoComposition's instructions key above. */
@property (nonatomic, readonly) CMTimeRange timeRange;

/* Indicates the background color of the composition. Solid BGRA colors only are supported; patterns and other color refs that are not supported will be ignored.
   If the background color is not specified the video compositor will use a default backgroundColor of opaque black.
   If the rendered pixel buffer does not have alpha, the alpha value of the backgroundColor will be ignored. */
@property (nonatomic, retain) __attribute__((NSObject)) CGColorRef backgroundColor;

/* Provides an array of instances of AVVideoCompositionLayerInstruction that specify how video frames from source tracks should be layered and composed.
   Tracks are layered in the composition according to the top-to-bottom order of the layerInstructions array; the track with trackID of the first instruction
   in the array will be layered on top, with the track with the trackID of the second instruction immediately underneath, etc.
   If this key is nil, the output will be a fill of the background color. */
@property (nonatomic, readonly, copy) NSArray *layerInstructions;

/* If NO, indicates that post-processing should be skipped for the duration of this instruction.  YES by default.
   See +[AVVideoCompositionCoreAnimationTool videoCompositionToolWithPostProcessingAsVideoLayer:inLayer:].*/
@property (nonatomic, readonly) BOOL enablePostProcessing;

@end


@class AVMutableVideoCompositionInstructionInternal;

NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVMutableVideoCompositionInstruction : AVVideoCompositionInstruction {
@private
	AVMutableVideoCompositionInstructionInternal	*_mutableInstruction;
}

/*  
 @method		videoCompositionInstruction
 @abstract		Returns a new instance of AVMutableVideoCompositionInstruction.
 @discussion
   The returned AVMutableVideoCompositionInstruction will have a timeRange of kCMTimeRangeInvalid, a NULL backgroundColor, and a nil array of layerInstructions.
*/
+ (AVMutableVideoCompositionInstruction *)videoCompositionInstruction;

/* Indicates the timeRange during which the instruction is effective. Note requirements for the timeRanges of instructions described in connection with AVVideoComposition's instructions key above. */
@property (nonatomic, assign) CMTimeRange timeRange;

/* Indicates the background color of the composition. Solid BGRA colors only are supported; patterns and other color refs that are not supported will be ignored.
   If the background color is not specified the video compositor will use a default backgroundColor of opaque black.
   If the rendered pixel buffer does not have alpha, the alpha value of the backgroundColor will be ignored. */
@property (nonatomic, retain) __attribute__((NSObject)) CGColorRef backgroundColor;

/* Provides an array of instances of AVVideoCompositionLayerInstruction that specify how video frames from source tracks should be layered and composed.
   Tracks are layered in the composition according to the top-to-bottom order of the layerInstructions array; the track with trackID of the first instruction
   in the array will be layered on top, with the track with the trackID of the second instruction immediately underneath, etc.
   If this key is nil, the output will be a fill of the background color. */
@property (nonatomic, copy) NSArray *layerInstructions;

/* If NO, indicates that post-processing should be skipped for the duration of this instruction.  YES by default.
   See +[AVVideoCompositionCoreAnimationTool videoCompositionToolWithPostProcessingAsVideoLayer:inLayer:].*/
@property (nonatomic, assign) BOOL enablePostProcessing;

@end


@class AVVideoCompositionLayerInstructionInternal;

NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVVideoCompositionLayerInstruction : NSObject <NSCoding, NSCopying, NSMutableCopying> {
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
- (BOOL)getTransformRampForTime:(CMTime)time startTransform:(CGAffineTransform *)startTransform endTransform:(CGAffineTransform *)endTransform timeRange:(CMTimeRange *)timeRange;

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
- (BOOL)getOpacityRampForTime:(CMTime)time startOpacity:(float *)startOpacity endOpacity:(float *)endOpacity timeRange:(CMTimeRange *)timeRange;

@end


@class AVMutableVideoCompositionLayerInstructionInternal;

NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVMutableVideoCompositionLayerInstruction : AVVideoCompositionLayerInstruction {
@private
	AVMutableVideoCompositionLayerInstructionInternal	*_mutableLayerInstruction;
};

/*  
 @method		videoCompositionLayerInstructionWithAssetTrack:
 @abstract		Returns a new instance of AVMutableVideoCompositionLayerInstruction with no transform or opacity ramps and a trackID set to the specified track's trackID.
 @param			track
   A reference to an AVAssetTrack.
*/
+ (AVMutableVideoCompositionLayerInstruction *)videoCompositionLayerInstructionWithAssetTrack:(AVAssetTrack *)track;

/*  
 @method		videoCompositionLayerInstruction
 @abstract		Returns a new instance of AVMutableVideoCompositionLayerInstruction with no transform or opacity ramps and a trackID initialized to kCMPersistentTrackID_Invalid.
*/
+ (AVMutableVideoCompositionLayerInstruction *)videoCompositionLayerInstruction;

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

NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVVideoCompositionCoreAnimationTool : NSObject {
@private
	AVVideoCompositionCoreAnimationToolInternal	*_videoCompositionTool;
}

/*!
 	@method						videoCompositionToolWithAdditionalLayer:asTrackID:
	@abstract					Add a Core Animation layer to the video composition
	@discussion					Include a Core Animation layer as an individual track input in video composition.
								This layer should not come from, or be added to, another layer tree.
								trackID should not match any real trackID in the source. Use -[AVAsset unusedTrackID] 
								to obtain a trackID that's guaranteed not to coincide with the trackID of any track of the asset.
								AVVideoCompositionInstructions should reference trackID where the rendered animation should be included.
								For best performance, no transform should be set in the AVVideoCompositionLayerInstruction for this trackID.
*/
+ (AVVideoCompositionCoreAnimationTool *)videoCompositionCoreAnimationToolWithAdditionalLayer:(CALayer *)layer asTrackID:(CMPersistentTrackID)trackID;

/*!
	@method						videoCompositionToolWithPostProcessingAsVideoLayer:inLayer:
	@abstract					Compose the composited video frames with the Core Animation layer
	@discussion					Place composited video frames in videoLayer and render animationLayer 
								to produce the final frame. Normally videoLayer should be in animationLayer's sublayer tree.
								The animationLayer should not come from, or be added to, another layer tree.
*/
+ (AVVideoCompositionCoreAnimationTool *)videoCompositionCoreAnimationToolWithPostProcessingAsVideoLayer:(CALayer *)videoLayer inLayer:(CALayer *)animationLayer;

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
    Pass a reference to an AVAsset if you wish to validate the timeRanges of the instructions against the duration of the asset and the trackIDs of the layer instructions against the asset's tracks. Pass nil to skip that validation.
 @param			timeRange
   A CMTimeRange.  Only those instuctions with timeRanges that overlap with the specified timeRange will be validated. To validate all instructions that may be used for playback or other processing, regardless of timeRange, pass CMTimeRangeMake(kCMTimeZero, kCMTimePositiveInfinity).
 @param			validationDelegate
   Indicates an object implementing the AVVideoCompositionValidationHandling protocol to receive information about troublesome portions of a video composition during processing of -isValidForAsset:. May be nil.
@discussion
   In the course of validation, the receiver will invoke its validationDelegate with reference to any trouble spots in the video composition.
   An exception will be raised if the delegate modifies the receiver's array of instructions or the array of layerInstructions of any AVVideoCompositionInstruction contained therein during validation.
*/
- (BOOL)isValidForAsset:(AVAsset *)asset timeRange:(CMTimeRange)timeRange validationDelegate:(id<AVVideoCompositionValidationHandling>)validationDelegate NS_AVAILABLE(10_8, 5_0);

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
- (BOOL)videoComposition:(AVVideoComposition *)videoComposition shouldContinueValidatingAfterFindingInvalidValueForKey:(NSString *)key NS_AVAILABLE(10_8, 5_0);

/*!
 @method		videoComposition:shouldContinueValidatingAfterFindingEmptyTimeRange:
 @abstract
   Invoked by an instance of AVVideoComposition when validating an instance of AVVideoComposition, to report a timeRange that has no corresponding video composition instruction.
 @result
   An indication of whether the AVVideoComposition should continue validation in order to report additional problems that may exist.
*/
- (BOOL)videoComposition:(AVVideoComposition *)videoComposition shouldContinueValidatingAfterFindingEmptyTimeRange:(CMTimeRange)timeRange NS_AVAILABLE(10_8, 5_0);

/*!
 @method		videoComposition:shouldContinueValidatingAfterFindingInvalidTimeRangeInInstruction:
 @abstract
   Invoked by an instance of AVVideoComposition when validating an instance of AVVideoComposition, to report a video composition instruction with a timeRange that's invalid, that overlaps with the timeRange of a prior instruction, or that contains times earlier than the timeRange of a prior instruction.
 @discussion
   Use CMTIMERANGE_IS_INVALID, defined in CMTimeRange.h, to test whether the timeRange itself is invalid. Refer to headerdoc for AVVideoComposition.instructions for a discussion of how timeRanges for instructions must be formulated.
 @result
   An indication of whether the AVVideoComposition should continue validation in order to report additional problems that may exist.
*/
- (BOOL)videoComposition:(AVVideoComposition *)videoComposition shouldContinueValidatingAfterFindingInvalidTimeRangeInInstruction:(AVVideoCompositionInstruction *)videoCompositionInstruction NS_AVAILABLE(10_8, 5_0);

/*!
 @method		videoComposition:shouldContinueValidatingAfterFindingInvalidTrackIDInInstruction:layerInstruction:asset:
 @abstract
   Invoked by an instance of AVVideoComposition when validating an instance of AVVideoComposition, to report a video composition layer instruction with a trackID that does not correspond either to the trackID used for the composition's animationTool or to a track of the asset specified in -[AVVideoComposition isValidForAsset:timeRange:delegate:].
 @result
   An indication of whether the AVVideoComposition should continue validation in order to report additional problems that may exist.
*/
- (BOOL)videoComposition:(AVVideoComposition *)videoComposition shouldContinueValidatingAfterFindingInvalidTrackIDInInstruction:(AVVideoCompositionInstruction *)videoCompositionInstruction layerInstruction:(AVVideoCompositionLayerInstruction *)layerInstruction asset:(AVAsset *)asset NS_AVAILABLE(10_8, 5_0);

@end
