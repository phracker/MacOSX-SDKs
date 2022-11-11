/*
	File:  AVPlayerViewController.h
	
	Framework:  AVKit
	
	Copyright © 2014-2017 Apple Inc. All rights reserved.
	
 */

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol AVPlayerViewControllerDelegate;

/*!
	@class		AVPlayerViewController
	@abstract	AVPlayerViewController is a subclass of UIViewController that can be used to display the visual content of an AVPlayer object and the standard playback controls.
 */

API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface AVPlayerViewController : UIViewController

/*!
	@property	player
	@abstract	The player from which to source the media content for the view controller.
 */
@property (nonatomic, strong, nullable) AVPlayer *player;

/*!
	@property	showsPlaybackControls
	@abstract	Whether or not the receiver shows playback controls. Default is YES.
	@discussion	Clients can set this property to NO when they don't want to have any playback controls on top of the visual content (e.g. for a game splash screen).
 */
@property (nonatomic) BOOL showsPlaybackControls;

/*!
 	@property	showsTimecodes
 	@abstract	Controls whether timecodes can be displayed in the playback UI when playing media with embedded timecodes. Default NO.
 */
@property (nonatomic) BOOL showsTimecodes API_AVAILABLE(ios(13.0));

/*!
	@property	videoGravity
	@abstract	A string defining how the video is displayed within an AVPlayerLayer bounds rect.
	@discussion	Options are AVLayerVideoGravityResizeAspect, AVLayerVideoGravityResizeAspectFill and AVLayerVideoGravityResize. AVLayerVideoGravityResizeAspect is default.
 */
@property (nonatomic, copy) AVLayerVideoGravity videoGravity;

/*!
	@property	readyForDisplay
	@abstract	Boolean indicating that the first video frame has been made ready for display for the current item of the associated AVPlayer.
 */
@property (nonatomic, readonly, getter = isReadyForDisplay) BOOL readyForDisplay;

/*!
	@property	videoBounds
	@abstract	The current size and position of the video image as displayed within the receiver's view's bounds.
 */
@property (nonatomic, readonly) CGRect videoBounds;

/*!
	@property	contentOverlayView
	@abstract	Use the content overlay view to add additional custom views between the video content and the controls.
 */
@property (nonatomic, readonly, nullable) UIView *contentOverlayView;

/*!
	@property	allowsPictureInPicturePlayback
	@abstract	Whether or not the receiver allows Picture in Picture playback. Default is YES.
 */
@property (nonatomic) BOOL allowsPictureInPicturePlayback API_AVAILABLE(ios(9.0));

/*!
     @property    canStartPictureInPictureAutomaticallyFromInline
     @abstract    Indicates whether Picture in Picture should be allowed to start automatically when transitioning to background when the receiver’s content is embedded inline. Default is NO.
     @discussion  This property must only be set to YES for content intended to be the user's primary focus.
 */
@property (nonatomic) BOOL canStartPictureInPictureAutomaticallyFromInline API_AVAILABLE(ios(14.2));

/*!
	@property	updatesNowPlayingInfoCenter
	@abstract	Whether or not the now playing info center should be updated. Default is YES.
 */
@property (nonatomic) BOOL updatesNowPlayingInfoCenter API_AVAILABLE(ios(10.0));

/*!
	@property	entersFullScreenWhenPlaybackBegins
	@abstract	Whether or not the receiver automatically enters full screen when the play button is tapped. Default is NO.
	@discussion	If YES, the receiver will show a user interface tailored to this behavior.
 */
@property (nonatomic) BOOL entersFullScreenWhenPlaybackBegins API_AVAILABLE(ios(11.0));

/*!
	@property	exitsFullScreenWhenPlaybackEnds
	@abstract	Whether or not the receiver automatically exits full screen when playback ends. Default is NO.
	@discussion	If multiple player items have been enqueued, the receiver exits fullscreen once no more items are remaining in the queue.
 */
@property (nonatomic) BOOL exitsFullScreenWhenPlaybackEnds API_AVAILABLE(ios(11.0));

/*!
    @property    requiresLinearPlayback
    @abstract    Disables certain user operations (fast forward, forward skip, and scrubbing).
    @discussion  This can be used to enforce playback of mandatory content (such as legalese or advertisements).
 */
@property (nonatomic) BOOL requiresLinearPlayback API_AVAILABLE(ios(11.0));

/*!
 	@property	pixelBufferAttributes
 	@abstract	The client requirements for the visual output during playback.
 	@discussion	Pixel buffer attribute keys are defined in <CoreVideo/CVPixelBuffer.h>
 */
@property (nonatomic, copy, nullable) NSDictionary<NSString *,id> *pixelBufferAttributes API_AVAILABLE(ios(9.0));

/*!
	@property	delegate
	@abstract	The receiver's delegate.
 */
@property (nonatomic, weak, nullable) id <AVPlayerViewControllerDelegate> delegate API_AVAILABLE(ios(9.0));

@end


/*!
	@protocol	AVPlayerViewControllerDelegate
	@abstract	A protocol for delegates of AVPlayerViewController.
 */

@protocol AVPlayerViewControllerDelegate <NSObject>
@optional

/*!
 	@method		playerViewController:willBeginFullScreenPresentationWithAnimationCoordinator:
 	@param		playerViewController
 				The player view controller.
 	@param		coordinator
 				An object conforming to UIViewControllerTransitionCoordinator.
 	@abstract	Informs the delegate that AVPlayerViewController is about to start displaying its contents full screen.
 	@discussion	This method will not be called if a playerViewController is embedded inside a view controller that is being presented. If the receiver is embedded in a parent view controller, its content will be presented in a new full screen view controller and perhaps in a new window. Use the coordinator to determine whether the playerViewController or its full screen counterpart is being transitioned. Transitions can be interrupted -- use a completion block of one of the coordinator's animation methods to determine whether it has completed.
 */
- (void)playerViewController:(AVPlayerViewController *)playerViewController willBeginFullScreenPresentationWithAnimationCoordinator:(id<UIViewControllerTransitionCoordinator>)coordinator API_AVAILABLE(ios(12.0));

/*!
 	@method		playerViewController:willEndFullScreenPresentationWithAnimationCoordinator:
 	@param		playerViewController
 				The player view controller.
	@param		coordinator
				An object conforming to UIViewControllerTransitionCoordinator.
	@abstract	Informs the delegate that AVPlayerViewController is about to stop displaying its contents full screen.
	@discussion	See the discussion of -[AVPlayerViewControllerDelegatePrivate playerViewController:willBeginFullScreenPresentationWithAnimationCoordinator:].
 */
- (void)playerViewController:(AVPlayerViewController *)playerViewController willEndFullScreenPresentationWithAnimationCoordinator:(id<UIViewControllerTransitionCoordinator>)coordinator API_AVAILABLE(ios(12.0));

/*!
 @method		playerViewController:restoreUserInterfaceForFullScreenExitWithCompletionHandler:
 @param			playerViewController
 				The player view controller.
 @param			completionHandler
 				The completion handler the delegate must call after restoring the interface for an exit full screen transition.
 @abstract		The delegate can implement this method to restore the user interface before exiting fullscreen.
 */
- (void)playerViewController:(AVPlayerViewController *)playerViewController restoreUserInterfaceForFullScreenExitWithCompletionHandler:(void (^)(BOOL restored))completionHandler API_AVAILABLE(ios(15.0));

/*!
	@method		playerViewControllerWillStartPictureInPicture:
	@param		playerViewController
				The player view controller.
	@abstract	Delegate can implement this method to be notified when Picture in Picture will start.
 */
- (void)playerViewControllerWillStartPictureInPicture:(AVPlayerViewController *)playerViewController;

/*!
	@method		playerViewControllerDidStartPictureInPicture:
	@param		playerViewController
				The player view controller.
	@abstract	Delegate can implement this method to be notified when Picture in Picture did start.
 */
- (void)playerViewControllerDidStartPictureInPicture:(AVPlayerViewController *)playerViewController;

/*!
	@method		playerViewController:failedToStartPictureInPictureWithError:
	@param		playerViewController
				The player view controller.
	@param		error
				An error describing why it failed.
	@abstract	Delegate can implement this method to be notified when Picture in Picture failed to start.
 */
- (void)playerViewController:(AVPlayerViewController *)playerViewController failedToStartPictureInPictureWithError:(NSError *)error;

/*!
	@method		playerViewControllerWillStopPictureInPicture:
	@param		playerViewController
				The player view controller.
	@abstract	Delegate can implement this method to be notified when Picture in Picture will stop.
 */
- (void)playerViewControllerWillStopPictureInPicture:(AVPlayerViewController *)playerViewController;

/*!
	@method		playerViewControllerDidStopPictureInPicture:
	@param		playerViewController
				The player view controller.
	@abstract	Delegate can implement this method to be notified when Picture in Picture did stop.
 */
- (void)playerViewControllerDidStopPictureInPicture:(AVPlayerViewController *)playerViewController;

/*!
	@method		playerViewControllerShouldAutomaticallyDismissAtPictureInPictureStart:
	@param		playerViewController
				The player view controller.
	@abstract	Delegate can implement this method and return NO to prevent player view controller from automatically being dismissed when Picture in Picture starts.
 */
- (BOOL)playerViewControllerShouldAutomaticallyDismissAtPictureInPictureStart:(AVPlayerViewController *)playerViewController;

/*!
	@method		playerViewController:restoreUserInterfaceForPictureInPictureStopWithCompletionHandler:
	@param		playerViewController
				The player view controller.
	@param		completionHandler
				The completion handler the delegate needs to call after restore.
	@abstract	Delegate can implement this method to restore the user interface before Picture in Picture stops.
 */
- (void)playerViewController:(AVPlayerViewController *)playerViewController restoreUserInterfaceForPictureInPictureStopWithCompletionHandler:(void (^)(BOOL restored))completionHandler;

@end

NS_ASSUME_NONNULL_END
