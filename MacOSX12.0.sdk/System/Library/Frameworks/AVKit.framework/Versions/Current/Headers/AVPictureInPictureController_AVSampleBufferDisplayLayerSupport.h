/*
	File: AVPictureInPictureController_AVSampleBufferDisplayLayerSupport.h
 
	Framework: AVKit
 
	Copyright © 2020 Apple Inc. All rights reserved.
 */

#import <AVFoundation/AVSampleBufferDisplayLayer.h>
#import <AVKit/AVPictureInPictureController.h>

NS_ASSUME_NONNULL_BEGIN

@class AVPictureInPictureControllerContentSource;
@class AVPictureInPicturePlaybackState;
@protocol AVPictureInPictureSampleBufferPlaybackDelegate;

@interface AVPictureInPictureController ()

/*!
	@method		invalidatePlaybackState
	@abstract	Informs Picture in Picture controller that it should request an updated playback state from its sampleBufferPlaybackDelegate.
	@discussion	This should always be called whenever playback is paused or unpaused, or the underlying content duration changes.
*/
- (void)invalidatePlaybackState API_AVAILABLE(ios(15.0), tvos(15.0), macos(12.0)) API_UNAVAILABLE(watchos);

@end


/*!
	@protocol	AVPictureInPictureSampleBufferPlaybackDelegate
	@abstract	A protocol for controlling playback from an AVSampleBufferDisplayLayer in Picture in Picture.
*/
API_AVAILABLE(ios(15.0), tvos(15.0), macos(12.0)) API_UNAVAILABLE(watchos)
@protocol AVPictureInPictureSampleBufferPlaybackDelegate <NSObject>

/*!
	@method		pictureInPictureController:setPlaying:
	@param		pictureInPictureController
				The Picture in Picture controller.
	@param		playing
				Whether the content should play or pause.
	@abstract	Informs delegate that the user initiated a request to play or pause the content.
*/
- (void)pictureInPictureController:(AVPictureInPictureController *)pictureInPictureController setPlaying:(BOOL)playing NS_SWIFT_NAME(pictureInPictureController(_:setPlaying:));

/*!
	@method		pictureInPictureControllerTimeRangeForPlayback:
	@param		pictureInPictureController
				The Picture in Picture controller.
	@abstract	Allows delegate to inform Picture in Picture controller of the current playable time range. May be called multiple times during playback. Time ranges with finite duration should always contain the current time of the sample buffer display layer's timebase.
	@discussion	Clients should return a time range with a duration of kCMTimeInfinity to indicate live content. When there is no content to play, they should return kCMTimeRangeInvalid. This method will be called whenever -[AVPictureInPictureController invalidatePlaybackState] is called and at other times as needed by the system.
	@returns	A CMTimeRange indicating the content's time range.
*/
- (CMTimeRange)pictureInPictureControllerTimeRangeForPlayback:(AVPictureInPictureController *)pictureInPictureController NS_SWIFT_NAME(pictureInPictureControllerTimeRangeForPlayback(_:));

/*!
	@method		pictureInPictureControllerIsPlaybackPaused:
	@param		pictureInPictureController
				The Picture in Picture controller.
	@abstract	Allows delegate to indicate whether the playback UI should reflect a playing or paused state, regardless of what the current playback rate might be. May be called multiple times during playback.
	@discussion	This method will be called whenever -[AVPictureInPictureController invalidatePlaybackState] is called and at other times as needed by the system.
	@returns	A boolean value indicating whether or not the playback UI should indicate playback has been paused or is playing.
*/
- (BOOL)pictureInPictureControllerIsPlaybackPaused:(AVPictureInPictureController *)pictureInPictureController NS_SWIFT_NAME(pictureInPictureControllerIsPlaybackPaused(_:));

/*!
	@method		pictureInPictureController:didTransitionToRenderSize:
	@param		pictureInPictureController
				The Picture in Picture controller.
	@param		newRenderSize
				The rendered size, in pixels, of Picture in Picture content.
	@abstract	This method is called when the system Picture in Picture window changes size. Delegate take the new render size and AVPictureInPictureController.isPictureInPictureActive into account when choosing media variants in order to avoid uncessary decoding overhead.
*/
- (void)pictureInPictureController:(AVPictureInPictureController *)pictureInPictureController didTransitionToRenderSize:(CMVideoDimensions)newRenderSize NS_SWIFT_NAME(pictureInPictureController(_:didTransitionToRenderSize:));

/*!
	@method		pictureInPictureController:skipByInterval:completionHandler:
	@param		pictureInPictureController
				The Picture in Picture controller.
	@param		skipInterval
				The interval by which to skip playback.
	@param		completionHandler
				A closure that must be invoked to indicate that the skip operation has completed.
	@abstract	Informs delegate that the user has requested skipping forward or backward by the time indicated by the interval.
	@discussion	Clients may choose to seek by a different interval for efficiency reasons (for example, seeking to a keyframe) or if the requested interval falls outside of the playable timeline. Clients must invoke the completion handler to indicate the seek operation has finished or failed. By the time the completion handler has been invoked, the timebase should reflect the current time and playback rate. Failure to invoke this completion handler is an application error and will result in playback UI permanently stuck in a “seeking” state.
*/
- (void)pictureInPictureController:(AVPictureInPictureController *)pictureInPictureController skipByInterval:(CMTime)skipInterval completionHandler:(void (^)(void))completionHandler NS_SWIFT_NAME(pictureInPictureController(_:skipByInterval:completion:));


@optional

/*!
	@method		pictureInPictureControllerShouldProhibitBackgroundAudioPlayback:
	@param		pictureInPictureController
				The Picture in Picture controller.
	@abstract	Allows the delegate to indicate whether background audio playback should always be prohibited.
	@discussion	If implemented, this optional method will be called once for each invocation of invalidatePlaybackState to allow the delegate to indicate whether or not audio playback should be prohibited when the picture in picture window is in the background.
 
				Note that background in this context has a seperate meaning from application background used in UIKit. Here, background defines the state of the picture in picture window itself rather than the application.
	@returns	A boolean value indicating whether or not background audio playback is always prohibited.
*/
- (BOOL)pictureInPictureControllerShouldProhibitBackgroundAudioPlayback:(AVPictureInPictureController *)pictureInPictureController NS_SWIFT_NAME(pictureInPictureControllerShouldProhibitBackgroundAudioPlayback(_:));

@end


API_AVAILABLE(ios(15.0), tvos(15.0), macos(12.0)) API_UNAVAILABLE(watchos)
@interface AVPictureInPictureControllerContentSource (AVSampleBufferDisplayLayerSupport)

/*!
	@method		initWithSampleBufferDisplayLayer:
	@param		sampleBufferDisplayLayer
				The sample buffer display layer to be shown in Picture in Picture.
	@param		playbackDelegate
				The playback delegate for controlling sample buffer display layer's playback in Picture in Picture.
	@abstract	Use this initializer for a content source with a sample buffer display layer and playback delegate.
*/
- (instancetype)initWithSampleBufferDisplayLayer:(AVSampleBufferDisplayLayer *)sampleBufferDisplayLayer playbackDelegate:(id<AVPictureInPictureSampleBufferPlaybackDelegate>)playbackDelegate;

/*!
	@property	sampleBufferDisplayLayer
	@abstract	The receiver's sample buffer display layer.
*/
@property (nonatomic, nullable, readonly) AVSampleBufferDisplayLayer *sampleBufferDisplayLayer;

/*!
	@property	sampleBufferPlaybackDelegate
	@abstract	The receiver's sample buffer playback delegate.
*/
@property (nonatomic, nullable, weak, readonly) id<AVPictureInPictureSampleBufferPlaybackDelegate> sampleBufferPlaybackDelegate;

@end

NS_ASSUME_NONNULL_END
