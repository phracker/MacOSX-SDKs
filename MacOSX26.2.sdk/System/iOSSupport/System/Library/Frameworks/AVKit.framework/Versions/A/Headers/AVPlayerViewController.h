/*
	File:  AVPlayerViewController.h
	
	Framework:  AVKit
	
	Copyright © 2013-2024 Apple Inc. All rights reserved.
	
	To report bugs, go to:  http://developer.apple.com/bugreporter/

 */

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#if TARGET_OS_MACCATALYST
#import <AVKit/AVKitTypes.h>
#else
#import <AVKit/AVKitTypes.h>
#endif // TARGET_OS_MACCATALYST


NS_ASSUME_NONNULL_BEGIN

/*!
	@constant	AVPlayerViewControllerSkippingBehaviorDefault
				The default skipping behavior.
	@constant	AVPlayerViewControllerSkippingBehaviorSkipItem
				Skip to next/previous item (as in a playlist).
 */
typedef NS_ENUM(NSInteger, AVPlayerViewControllerSkippingBehavior) {
	AVPlayerViewControllerSkippingBehaviorDefault = 0,
	AVPlayerViewControllerSkippingBehaviorSkipItem
} API_AVAILABLE(tvos(10.0)) API_UNAVAILABLE(macos, ios, watchos, visionos);


@class AVContentProposal;
@class AVGroupExperienceCoordinator;
@class AVInterstitialTimeRange;
@class AVPlaybackSpeed;

@protocol AVPlayerViewControllerAnimationCoordinator;
@protocol AVPlayerViewControllerDelegate;


// MARK: -

/**
	@class		AVPlayerViewController
	@abstract	AVPlayerViewController is a subclass of UIViewController that can be used to display the visual content of an AVPlayer object and the standard playback controls.
 */
API_AVAILABLE(ios(8.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(macos)
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
@property (nonatomic) BOOL showsPlaybackControls API_UNAVAILABLE(watchos);

/*!
	@property	showsTimecodes
	@abstract	Controls whether timecodes can be displayed in the playback UI when playing media with embedded timecodes. Default NO.
 */
@property (nonatomic) BOOL showsTimecodes API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, visionos);

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
@property (nonatomic, readonly, getter = isReadyForDisplay) BOOL readyForDisplay API_UNAVAILABLE(watchos, visionos);

/*!
	@property	videoBounds
	@abstract	The current size and position of the video image as displayed within the receiver's view's bounds.
 */
@property (nonatomic, readonly) CGRect videoBounds API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/*!
	@property	contentOverlayView
	@abstract	Use the content overlay view to add additional custom views between the video content and the controls.
 */
@property (nonatomic, readonly, nullable) UIView *contentOverlayView API_UNAVAILABLE(watchos);

/*!
	@property	allowsPictureInPicturePlayback
	@abstract	Whether or not the receiver allows Picture in Picture playback. Default is YES.
 */
@property (nonatomic) BOOL allowsPictureInPicturePlayback API_AVAILABLE(ios(9.0), tvos(14.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/*!
	@property	allowsVideoFrameAnalysis
	@abstract	When set to YES, the AVPlayerViewController will try to find objects, text and people while the media is paused. When an object is found, the user will be able to interact with it using long press to present a context menu. Default is YES.
*/
@property (nonatomic) BOOL allowsVideoFrameAnalysis API_AVAILABLE(ios(16.0), macCatalyst(18.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(tvos, watchos);

/*!
	@property 	videoFrameAnalysisTypes
	@abstract	The types of analysis AVPlayerViewController will perform on a paused video frame. The default value is AVVideoFrameAnalysisDefault.
 */
@property (nonatomic) AVVideoFrameAnalysisType videoFrameAnalysisTypes API_AVAILABLE(ios(17.0), macCatalyst(18.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(tvos, watchos);

/*!
	@property 	toggleLookupAction
	@abstract 	A UIAction used for enabling the visual lookup interface.
	@discussion	Use this action to toggle visual lookup UI. This action's attributes will be set to disabled when there is no visual lookup data available or when the media is playing. Make sure to 	update your user interface to reflect this change. When the lookup UI is toggled, the state property is set to UIMenuElementStateOn; otherwise it will be set to UIMenuElementStateOff.
 */
@property (nonatomic, readonly) UIAction *toggleLookupAction API_AVAILABLE(ios(17.0), macCatalyst(18.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(tvos, watchos);

/*!
	@property	canStartPictureInPictureAutomaticallyFromInline
	@abstract	Indicates whether Picture in Picture should be allowed to start automatically when transitioning to background when the receiver’s content is embedded inline. Default is NO.
	@discussion	This property must only be set to YES for content intended to be the user's primary focus.
 */
@property (nonatomic) BOOL canStartPictureInPictureAutomaticallyFromInline API_AVAILABLE(ios(14.2), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);

/*!
	@property	updatesNowPlayingInfoCenter
	@abstract	Whether or not the now playing info center should be updated. Default is YES.
 */
@property (nonatomic) BOOL updatesNowPlayingInfoCenter API_AVAILABLE(ios(10.0), visionos(1.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/*!
	@property	entersFullScreenWhenPlaybackBegins
	@abstract	Whether or not the receiver automatically enters full screen when the play button is tapped. Default is NO.
	@discussion	If YES, the receiver will show a user interface tailored to this behavior.
 */
@property (nonatomic) BOOL entersFullScreenWhenPlaybackBegins API_AVAILABLE(ios(11.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);

/*!
	@property	exitsFullScreenWhenPlaybackEnds
	@abstract	Whether or not the receiver automatically exits full screen when playback ends. Default is NO.
	@discussion	If multiple player items have been enqueued, the receiver exits fullscreen once no more items are remaining in the queue.
 */
@property (nonatomic) BOOL exitsFullScreenWhenPlaybackEnds API_AVAILABLE(ios(11.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);

/*!
	@property	requiresLinearPlayback
	@abstract	Disables certain user operations, such as scanning, skipping, and scrubbing.
	@discussion	This can be used to enforce playback of mandatory content (such as legalese or advertisements).
 */
@property (nonatomic) BOOL requiresLinearPlayback API_AVAILABLE(ios(11.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/*!
	@property	appliesPreferredDisplayCriteriaAutomatically
	@abstract	Whether or not the receiver automatically communicates the preferredDisplayCriteria of the asset being played to the AVDisplayManager.
	@discussion	If set, then when the receiver plays an asset full-screen the screen's display criteria will be set to the preferred display criteria of that asset. The preferredDisplayCriteria will be reset to the default when full-screen playback is complete. This should not be changed during full-screen presentation unless the player or player item has been removed. This should not be used in multiple window scenes simultaneously.
 */
@property (nonatomic) BOOL appliesPreferredDisplayCriteriaAutomatically API_AVAILABLE(tvos(11.2), visionos(1.0)) API_UNAVAILABLE(ios, watchos);

/*!
	@property	pixelBufferAttributes
	@abstract	The client requirements for the visual output during playback.
	@discussion	Pixel buffer attribute keys are defined in <CoreVideo/CVPixelBuffer.h>
 */
@property (nonatomic, copy, nullable) NSDictionary<NSString *,id> *pixelBufferAttributes API_AVAILABLE(ios(9.0), tvos(11.0)) API_UNAVAILABLE(watchos, visionos);

/*!
	@property	delegate
	@abstract	The receiver's delegate.
 */
@property (nonatomic, weak, nullable) id <AVPlayerViewControllerDelegate> delegate API_AVAILABLE(ios(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/*!
	@property	speeds
	@abstract	A list of user selectable playback speeds to be shown in the playback speed control.
	@discussion	By default this property will be set to the systemDefaultSpeeds class property. Setting this property to an empty list will hide the playback speed selection UI.
				To set the currently selected playback speed programmatically, either set the defaultRate on the AVPlayer associated with this view controller or use the selectSpeed: method on AVPlayerViewController.
 */
@property (nonatomic, copy) NSArray<AVPlaybackSpeed *> *speeds API_AVAILABLE(ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/*!
	@property	selectedSpeed
	@abstract	The currently selected playback speed.
	@discussion	Changes to the associated AVPlayer's defaultRate will be reflected in this property and vice versa. If the associated AVPlayer's defaultRate is set to a value that does not match a speed in the speeds list property, the selected speed will be nil.
 */
@property (nonatomic, readonly, nullable) AVPlaybackSpeed *selectedSpeed API_AVAILABLE(ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/*!
	@property	selectSpeed
	@param		speed
				The playback speed to select.
	@abstract	Sets the input AVPlaybackSpeed as the selected speed.
	@discussion	Calls to selectSpeed with AVPlaybackSpeeds not contained within the speeds property array will be ignored.
 */
- (void)selectSpeed:(AVPlaybackSpeed *)speed API_AVAILABLE(ios(16.0), tvos(16.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/*!
	@property	unobscuredContentGuide
	@abstract	A layout guide representing an area that will not be permanently obscured by fixed-position playback controls when they are visible.
 */
@property (nonatomic, readonly) UILayoutGuide *unobscuredContentGuide API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(ios, watchos, visionos);

/*!
	@property	allowedSubtitleOptionLanguages
	@abstract	An optional array of BCP 47 language codes to filter the subtitle options presented to the user.
	@discussion	When this property to nil (the default), all available subtitle options are presented. The "Auto" subtitle option is only available when this property is nil, and full subtitles are not required (see requiresFullSubtitles).
 */
@property (nonatomic, copy, nullable) NSArray <NSString *> *allowedSubtitleOptionLanguages API_AVAILABLE(tvos(9.0)) API_UNAVAILABLE(ios, watchos, visionos); /* BCP47 language codes; nil allows all languages */

/*!
	@property	requiresFullSubtitles
	@abstract	Determines whether the user is given the option to turn off subtitles.
	@discussion	When set to YES, the subtitle options will not present "Off" or "Auto" as options, and subtitles will always be displayed (if they are available). The default is NO.
 */
@property (nonatomic) BOOL requiresFullSubtitles API_AVAILABLE(tvos(9.0)) API_UNAVAILABLE(ios, watchos, visionos);

/*!
	@property	skippingBehavior
	@abstract	Specifies the behavior triggered by skipping gestures. AVPlayerViewControllerSkippingBehaviorDefault is the default value.
	@discussion	Use this property to override the default skipping behavior.
 */
@property (nonatomic) AVPlayerViewControllerSkippingBehavior skippingBehavior API_AVAILABLE(tvos(10.0)) API_UNAVAILABLE(ios, watchos, visionos);

/*!
	@property	skipForwardEnabled
	@abstract	Indicates whether forward-skipping is available.
	@discussion	This property affects the appearance of the forward-skipping indicator. The behavior associated with forward-skipping is identified by the skippingBehavior property.
 */
@property (nonatomic, getter = isSkipForwardEnabled) BOOL skipForwardEnabled API_AVAILABLE(tvos(10.0)) API_UNAVAILABLE(ios, watchos, visionos);

/*!
	@property	skipBackwardEnabled
	@abstract	Indicates whether backward-skipping is available.
	@discussion	This property affects the appearance of the backward-skipping indicator. The behavior associated with backward-skipping is identified by the skippingBehavior property.
 */
@property (nonatomic, getter = isSkipBackwardEnabled) BOOL skipBackwardEnabled API_AVAILABLE(tvos(10.0)) API_UNAVAILABLE(ios, watchos, visionos);

/*!
	@property	playbackControlsIncludeTransportBar
	@abstract	Whether or not the receiver shows the transport bar and related controls during user interaction. Default is YES.
	@discussion	Clients can set this property to NO, and set showsPlaybackControls to YES, to selectively prevent the transport bar from being displayed duration user interaction. Changing the value of this property does not immediately change the visibility of the transport bar.
 */
@property (nonatomic) BOOL playbackControlsIncludeTransportBar API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(ios, watchos, visionos);

/*!
	@property	playbackControlsIncludeInfoViews
	@abstract	Whether or not the receiver shows the views for video metadata, navigation markers, and playback settings when requested by the user. Default is YES.
	@discussion	Clients can set this property to NO, and showsPlaybackControls to YES, to selectively prevent the information and setting panels from being displayed. Changing the value of this property does not immediately change the visibility of the info views.
 */
@property (nonatomic) BOOL playbackControlsIncludeInfoViews API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(ios, watchos, visionos);

/*!
	@property	transportBarIncludesTitleView
	@abstract	Whether or not the receiver shows the title view above the scrubber. Enabled by default.
	@discussion	Clients can clear this property to disable the title view. Changing the value of this property may not immediately change visibility of the title view. This value is ignored when the transport bar is disabled by playbackControlsIncludeTransportBar.
	The title view requires metadata to be embedded in the media asset, or provided using externalMetadata property of AVPlayerItem. Supported keys are: AVMetadataCommonIdentifierTitle for title, AVMetadataIdentifieriTunesMetadataTrackSubTitle for subtitle.
		See also showsPlaybackControls, and playbackControlsIncludeTransportBar.
 */
@property (nonatomic) BOOL transportBarIncludesTitleView API_AVAILABLE(tvos(15.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(ios, watchos);

/*!
	@property	customOverlayViewController
	@abstract	A view controller containing custom, possibly interactive content, to be presented over the player view controller upon user request.
	@discussion	The custom overlay view controller can be accessed by swiping up during playback when the transport bar is hidden, or in response to selecting a button when the transport bar is visible. Clients should provide a view controller here rather than installing their own swipe gesture recognizer.
 */
@property (nonatomic, strong, nullable) UIViewController *customOverlayViewController API_AVAILABLE(tvos(13.0)) API_UNAVAILABLE(ios, watchos, visionos);

/*!
	@property	transportBarCustomMenuItems
	@abstract	An array of menu elements to be displayed in addition to standard built-in controls.
	@discussion	Use this property to provide client-specific controls above the transport bar. Only UIMenu and UIAction instance types are supported. Nested UIMenus are not supported. Unsupported types will be ignored.
 */
@property (nonatomic, readwrite, copy) NSArray<__kindof UIMenuElement *> *transportBarCustomMenuItems API_AVAILABLE(tvos(15.0)) API_UNAVAILABLE(ios) API_UNAVAILABLE(watchos, visionos);

/*!
	@property	requiresMonoscopicViewingMode
	@abstract	Whether or not monoscopic is the only permitted viewing mode. Default is NO.
 */
@property (nonatomic) BOOL requiresMonoscopicViewingMode API_AVAILABLE(visionos(1.0)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
 Describes how High Dynamic Range (HDR) video content renders.
 
 Defaults to ``AVDisplayDynamicRangeAutomatic``.
 
 - Note: This property will only have effect if the video content supports HDR.
 */
@property (nonatomic, assign, readwrite) AVDisplayDynamicRange preferredDisplayDynamicRange API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(tvos, visionos, watchos);


// MARK: - Contextual Actions

/*!
	@property	contextualActions
	@abstract	An array of action controls displayed during playback. Defaults to none.
	@discussion	Use this property to present one or more action controls during playback (for example, "Skip Intro"). The title and optionally the image of each action will be displayed by a control.
				The action handler will be called when the user selects the control.
 */
@property (nonatomic, copy) NSArray<UIAction *> *contextualActions API_AVAILABLE(tvos(15.0), visionos(1.0)) API_UNAVAILABLE(ios, watchos, macCatalyst);

/*!
	@property	contextualActionsInfoView
	@abstract	A view shown adjacent to the contextual actions suitable for showing related information.
	@discussion	Use this view to add additional metadata, information and/or artwork as subviews. This property is only supported when the receiver has been configured to have playback controls. Changing the configuration to remove the playback controls will invalidate this view..
 */
@property (nonatomic, readonly) UIView *contextualActionsInfoView API_AVAILABLE(visionos(1.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(ios, watchos, macCatalyst);

/*!
	@property	contextualActionsPreviewImage
	@abstract	An image to be shown alongside the contextual actions.
	@discussion Use this to enhance the action with more context, e.g. for a "Jump back" button, show a preview frame of where in the movie the action will skip to.
				This image is only shown if `AVPlayerViewController.contextualActions` contains exactly one action.
*/
@property (nonatomic, nullable, copy) UIImage *contextualActionsPreviewImage API_AVAILABLE(visionos(1.0)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);


// MARK: - Group Experiences

/*!
	@property	groupExperienceCoordinator
	@abstract	Retrieve the group experience coordinator for this view controller.
	@discussion	Use this property to coordinate a group experience among participating view controllers.
 */
@property (nonatomic, readonly) AVGroupExperienceCoordinator *groupExperienceCoordinator API_AVAILABLE(visionos(2.0)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);


// MARK: - Info Panel Customization

/*!
	@property	customInfoViewControllers
	@abstract	An array of view controllers to be displayed as tabs.
	@discussion	Use this property to provide tabs for client-specific content in the playback UI. The order of the view controllers in the array is also the order in which they are inserted in the tab bar. The display tab titles will be taken from the view controllers. Implement -preferredContentSize to provide the desired view size (subject to maximum height constraints).
 */
@property (nonatomic, copy) NSArray <UIViewController *> *customInfoViewControllers API_AVAILABLE(tvos(15.0), visionos(1.0)) API_UNAVAILABLE(ios) API_UNAVAILABLE(watchos, macCatalyst);

/*!
	@property	infoViewActions
	@abstract	Actions to be displayed in the content info view.
	@discussion	Use this property to provide up to 2 custom action controls displayed in the content info view. Default value is an array containing a single "Play From Beginning" action.
 */
@property (nonatomic, copy, null_resettable) NSArray<UIAction *> *infoViewActions API_AVAILABLE(tvos(15.0), visionos(1.0)) API_UNAVAILABLE(ios) API_UNAVAILABLE(watchos, macCatalyst);


// MARK: - Trim

/*!
	@property   canBeginTrimming
	@abstract   Whether or not the current media can be trimmed.
	@discussion This may return `false`, for example if the underlying asset is delivered via HLS, or if the content is protected.
				Consult this property to enable / disable the control which initiates trimming.
 */
@property (readonly) BOOL canBeginTrimming API_AVAILABLE(visionos(1.0)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@method     beginTrimmingWithCompletionHandler:
	@param      handler
				A completion handler that is executed when the user exits trim mode.
				The boolean passed to the completion handler indicates whether the user completed the trim operation, or if they cancelled.
	@abstract   Sets the controls panel into trimming mode and blocks until the user selects either the `Trim` or the `Cancel` button.
	@discussion Once trimming is completed the trimmed range can be accessed via the `forwardPlaybackEndTime` and `reversePlaybackEndTime` properties on the `AVPlayerItem`.
				Documentation on how to export a new copy of the asset via `AVAssetExportSession` after trimming can be found at https://developer.apple.com.
 */
- (void)beginTrimmingWithCompletionHandler:(nullable void (^)(BOOL success))handler API_AVAILABLE(visionos(1.0)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);


// MARK: - Custom Media Selection Schemes

/*!
	@property	mediaCharacteristicsForSupportedCustomMediaSelectionSchemes
	@abstract	Returns available AVKit supported media group types.
 */
@property (class, readonly) NSArray <AVMediaCharacteristic> *mediaCharacteristicsForSupportedCustomMediaSelectionSchemes API_AVAILABLE(ios(26.0), tvos(26.0)) API_UNAVAILABLE(macos, visionos, watchos);

@end


// MARK: -

/*!
	@protocol	AVPlayerViewControllerDelegate
	@abstract	A protocol for delegates of AVPlayerViewController.
 */
API_AVAILABLE(ios(9.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(macos)
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
- (void)playerViewController:(AVPlayerViewController *)playerViewController willBeginFullScreenPresentationWithAnimationCoordinator:(id<UIViewControllerTransitionCoordinator>)coordinator API_AVAILABLE(ios(12.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);

/*!
	@method		playerViewController:willEndFullScreenPresentationWithAnimationCoordinator:
	@param		playerViewController
				The player view controller.
	@param		coordinator
				An object conforming to UIViewControllerTransitionCoordinator.
	@abstract	Informs the delegate that AVPlayerViewController is about to stop displaying its contents full screen.
	@discussion	See the discussion of -[AVPlayerViewControllerDelegate playerViewController:willBeginFullScreenPresentationWithAnimationCoordinator:].
 */
- (void)playerViewController:(AVPlayerViewController *)playerViewController willEndFullScreenPresentationWithAnimationCoordinator:(id<UIViewControllerTransitionCoordinator>)coordinator API_AVAILABLE(ios(12.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);

/*!
	@method		playerViewController:restoreUserInterfaceForFullScreenExitWithCompletionHandler:
	@param		playerViewController
				The player view controller.
	@param		completionHandler
				The completion handler the delegate must call after restoring the interface for an exit full screen transition.
	@abstract	The delegate can implement this method to restore the user interface before exiting fullscreen.
 */
- (void)playerViewController:(AVPlayerViewController *)playerViewController restoreUserInterfaceForFullScreenExitWithCompletionHandler:(void (^)(BOOL restored))completionHandler API_AVAILABLE(ios(15.0), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);

/*!
	@method		playerViewControllerShouldDismiss:
	@param		playerViewController
				The player view controller.
	@abstract	The delegate can implement this method to be notified when the player view controller is about to be dismissed.
	@discussion	The player view controller will dismiss itself (with animation) if allowed and if it is possible to do so automatically. If the player view controller is embedded in another view, it may be necessary for the delegate to implement dismissal.
 */
- (BOOL)playerViewControllerShouldDismiss:(AVPlayerViewController *)playerViewController API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(ios, watchos, visionos);

/*!
	@method		playerViewControllerWillBeginDismissalTransition:
	@param		playerViewController
				The player view controller.
	@abstract	The delegate can implement this method to be notified when the player view controller is being dismissed and is about to start the dismissal transition.
 */
- (void)playerViewControllerWillBeginDismissalTransition:(AVPlayerViewController *)playerViewController API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(ios, watchos, visionos);

/*!
	@method		playerViewControllerDidEndDismissalTransition:
	@param		playerViewController
				The player view controller.
	@abstract	The delegate can implement this method to be notified when the player view controller is being dismissed and has completed the the dismissal transition.
 */
- (void)playerViewControllerDidEndDismissalTransition:(AVPlayerViewController *)playerViewController API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(ios, watchos, visionos);

/*!
	@method		playerViewControllerWillStartPictureInPicture:
	@param		playerViewController
				The player view controller.
	@abstract	Delegate can implement this method to be notified when Picture in Picture will start.
 */
- (void)playerViewControllerWillStartPictureInPicture:(AVPlayerViewController *)playerViewController API_AVAILABLE(ios(9.0), tvos(14.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/*!
	@method		playerViewControllerDidStartPictureInPicture:
	@param		playerViewController
				The player view controller.
	@abstract	Delegate can implement this method to be notified when Picture in Picture did start.
 */
- (void)playerViewControllerDidStartPictureInPicture:(AVPlayerViewController *)playerViewController API_AVAILABLE(ios(9.0), tvos(14.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/*!
	@method		playerViewController:failedToStartPictureInPictureWithError:
	@param		playerViewController
				The player view controller.
	@param		error
				An error describing why it failed.
	@abstract	Delegate can implement this method to be notified when Picture in Picture failed to start.
 */
- (void)playerViewController:(AVPlayerViewController *)playerViewController failedToStartPictureInPictureWithError:(NSError *)error API_AVAILABLE(ios(9.0), tvos(14.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/*!
	@method		playerViewControllerWillStopPictureInPicture:
	@param		playerViewController
				The player view controller.
	@abstract	Delegate can implement this method to be notified when Picture in Picture will stop.
 */
- (void)playerViewControllerWillStopPictureInPicture:(AVPlayerViewController *)playerViewController API_AVAILABLE(ios(9.0), tvos(14.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/*!
	@method		playerViewControllerDidStopPictureInPicture:
	@param		playerViewController
				The player view controller.
	@abstract	Delegate can implement this method to be notified when Picture in Picture did stop.
 */
- (void)playerViewControllerDidStopPictureInPicture:(AVPlayerViewController *)playerViewController API_AVAILABLE(ios(9.0), tvos(14.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/*!
	@method		playerViewControllerShouldAutomaticallyDismissAtPictureInPictureStart:
	@param		playerViewController
				The player view controller.
	@abstract	Delegate can implement this method and return NO to prevent player view controller from automatically being dismissed when Picture in Picture starts.
 */
- (BOOL)playerViewControllerShouldAutomaticallyDismissAtPictureInPictureStart:(AVPlayerViewController *)playerViewController API_AVAILABLE(ios(9.0), tvos(14.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/*!
	@method		playerViewController:restoreUserInterfaceForPictureInPictureStopWithCompletionHandler:
	@param		playerViewController
				The player view controller.
	@param		completionHandler
				The completion handler the delegate needs to call after restore.
	@abstract	Delegate can implement this method to restore the user interface before Picture in Picture stops.
 */
- (void)playerViewController:(AVPlayerViewController *)playerViewController restoreUserInterfaceForPictureInPictureStopWithCompletionHandler:(void (^)(BOOL restored))completionHandler API_AVAILABLE(ios(9.0), tvos(14.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/*!
	@method		playerViewController:willPresentInterstitialTimeRange:
	@param		playerViewController
				The player view controller.
	@param		interstitial
				The interstitial time range.
	@abstract	The delegate can implement this method to be notified when the player view controller is about to present interstitial content to the user.
 */
- (void)playerViewController:(AVPlayerViewController *)playerViewController willPresentInterstitialTimeRange:(AVInterstitialTimeRange *)interstitial API_AVAILABLE(ios(16.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos, macCatalyst);

/*!
	@method		playerViewController:didPresentInterstitialTimeRange:
	@param		playerViewController
				The player view controller.
	@param		interstitial
				The interstitial time range.
	@abstract	The delegate can implement this method to be notified when the player view controller has finished presenting interstitial content.
 */
- (void)playerViewController:(AVPlayerViewController *)playerViewController didPresentInterstitialTimeRange:(AVInterstitialTimeRange *)interstitial API_AVAILABLE(ios(16.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos, macCatalyst);

/*!
	@method		playerViewController:willResumePlaybackAfterUserNavigatedFromTime:toTime:
	@param		playerViewController
				The player view controller.
	@param		oldTime
				The playback time before the user began navigating.
	@param		targetTime
				The target playback time selected by the user.
	@abstract	The delegate can implement this method to be notified when the user has skipped, scrubbed, or otherwise navigated to a new time, and playback is about to start at the new time.
	@discussion	Compare with AVPlayerItemTimeJumpedNotification; this delegate method is delivered for (and only for) user-initiated changes to the playback time. If the user skips/scrubs several times before resuming playback, this method is only called once.
 */
- (void)playerViewController:(AVPlayerViewController *)playerViewController willResumePlaybackAfterUserNavigatedFromTime:(CMTime)oldTime toTime:(CMTime)targetTime API_AVAILABLE(tvos(9.0)) API_UNAVAILABLE(ios, watchos, macCatalyst, visionos);

/*!
	@method		playerViewController:timeToSeekAfterUserNavigatedFromTime:toTime:
	@param		playerViewController
				The player view controller.
	@param		oldTime
				The playback time before the user began navigating.
	@param		targetTime
				The playback time selected by the user.
	@abstract	The delegate can implement this method to be notified when the user has skipped, scrubbed, or otherwise navigated to a new time, and wants to resume playback at the target time.
	@discussion	This delegate method is delivered for (and only for) user-initiated changes to the playback time. If the user skips/scrubs several times before resuming playback, this method is only called once. This method should not be used to disable scrubbing; use the requiresLinearPlayback property of the AVPlayerViewController instead.
 */
- (CMTime)playerViewController:(AVPlayerViewController *)playerViewController timeToSeekAfterUserNavigatedFromTime:(CMTime)oldTime toTime:(CMTime)targetTime API_AVAILABLE(tvos(10.0)) API_UNAVAILABLE(ios, watchos, macCatalyst, visionos);

/*!
	@method		playerViewController:didSelectMediaSelectionOption:inMediaSelectionGroup:
	@param		playerViewController
				The player view controller.
	@param		mediaSelectionOption
				The selected media option.
	@param		mediaSelectionGroup
				The media selection group of the selected media option.
	@abstract	The delegate can implement this method to be notified when the user has selected a option from a media selection group or deselected all of the options in the group.
	@discussion	The media selection option will be nil when subtitles are turned off.
 */
- (void)playerViewController:(AVPlayerViewController *)playerViewController didSelectMediaSelectionOption:(nullable AVMediaSelectionOption *)mediaSelectionOption inMediaSelectionGroup:(AVMediaSelectionGroup *)mediaSelectionGroup API_AVAILABLE(tvos(9.0)) API_UNAVAILABLE(ios, watchos, macCatalyst, visionos);

/*!
	@method		playerViewController:didSelectExternalSubtitleOptionLanguage:
	@param		playerViewController
				The player view controller.
	@param		language
				The BCP 47 language code.
	@abstract	The delegate can implement this method to be notified when the user has selected a specific subtitle option.
	@discussion	This method is only called for external subtitle languages specified by the externalSubtitleOptionLanguages property of AVPlayerItem (see AVKit/AVPlayerItem.h). For all other options, playerViewController:didSelectMediaSelectionOption:inMediaSelectionGroup: will be called instead. The delegate is responsible for displaying the corresponding subtitles.
 */
- (void)playerViewController:(AVPlayerViewController *)playerViewController didSelectExternalSubtitleOptionLanguage:(NSString *)language API_AVAILABLE(tvos(9.0)) API_UNAVAILABLE(ios, watchos, macCatalyst, visionos) NS_SWIFT_UNAVAILABLE("External subtitle options are not supported");

/*!
	@method		skipToNextItemForPlayerViewController:
	@param		playerViewController
				The player view controller.
	@discussion	Clients that request non-default skipping behavior should implement this method. The delegate should update the playerViewController’s player to play the next player item.
 */
- (void)skipToNextItemForPlayerViewController:(AVPlayerViewController *)playerViewController API_AVAILABLE(tvos(10.0)) API_UNAVAILABLE(ios, watchos, macCatalyst, visionos);

/*!
	@method		skipToPreviousItemForPlayerViewController:
	@param		playerViewController
				The player view controller.
	@discussion	The delegate should update the playerViewController’s player to play the previous player item.
 */
- (void)skipToPreviousItemForPlayerViewController:(AVPlayerViewController *)playerViewController API_AVAILABLE(tvos(10.0)) API_UNAVAILABLE(ios, watchos, macCatalyst, visionos);

/*!
	@method		playerViewController:skipToNextChannel:
	@param		playerViewController
				The player view controller.
	@param		completion
				A block that should be called to dismiss the channel interstice.
	@abstract	Should change the player item to reflect the content of the next channel, and call the completion block when ready.
	@discussion	Each call to this method should advance one channel relative to the previous request, even if the prior request has not yet completed.
*/
- (void)playerViewController:(AVPlayerViewController *)playerViewController skipToNextChannel:(void (^)(BOOL success))completion API_AVAILABLE(tvos(13.0)) API_UNAVAILABLE(ios, watchos, macCatalyst, visionos) NS_SWIFT_ASYNC_NAME(playerViewControllerSkipToNextChannel(_:));

/*!
	@method		playerViewController:skipToPreviousChannel:
	@param		playerViewController
				The player view controller.
	@param		completion
				A block that should be called to dismiss the channel interstice.
	@abstract	Should change the player item to reflect the content of the previous channel, and call the completion block when ready.
	@discussion	Each call to this method should advance one channel relative to the previous request, even if the prior request has not yet completed.
*/
- (void)playerViewController:(AVPlayerViewController *)playerViewController skipToPreviousChannel:(void (^)(BOOL success))completion API_AVAILABLE(tvos(13.0)) API_UNAVAILABLE(ios, watchos, macCatalyst, visionos) NS_SWIFT_ASYNC_NAME(playerViewControllerSkipToPreviousChannel(_:));

/*!
	@method		nextChannelInterstitialViewControllerForPlayerViewController:
	@param		playerViewController
				The player view controller.
	@return		A view controller describing the channel that will be displayed; it will fill the screen until the new channel is ready.
	@abstract	Clients should provide a view controller describing the layout of the channel interstice.
	@discussion This method will be called when the user initiates, but has not yet committed, a change in channel. Clients must also implement playerViewController:skipToNextChannel:. This method may be called while a previous channel interstice is visible (on screen, or transitioning).
 */
- (UIViewController *)nextChannelInterstitialViewControllerForPlayerViewController:(AVPlayerViewController *)playerViewController API_AVAILABLE(tvos(13.0)) API_UNAVAILABLE(ios, watchos, macCatalyst, visionos);

/*!
	@method		previousChannelInterstitialViewControllerForPlayerViewController:
	@param		playerViewController
				The player view controller.
	@return		A view controller describing the channel that will be displayed; it will fill the screen until the new channel is ready.
	@abstract	Clients should provide a view controller describing the layout of the channel interstice.
	@discussion This method will be called when the user initiates, but has not yet committed, a change in channel. Clients must also implement playerViewController:skipToPreviousChannel:. This method may be called while a previous channel interstice is visible (on screen, or transitioning).
 */
- (UIViewController *)previousChannelInterstitialViewControllerForPlayerViewController:(AVPlayerViewController *)playerViewController API_AVAILABLE(tvos(13.0)) API_UNAVAILABLE(ios, watchos, macCatalyst, visionos);

/*!
	@method		playerViewController:shouldPresentContentProposal:
	@abstract	Should return YES, if implemented, to allow presentation of the content proposal.
	@discussion	The delegate may wish to create a custom view controller when this is called.
 */
- (BOOL)playerViewController:(AVPlayerViewController *)playerViewController shouldPresentContentProposal:(AVContentProposal *)proposal API_AVAILABLE(tvos(10.0)) API_UNAVAILABLE(ios, watchos, macCatalyst, visionos);

/*!
	@method		playerViewController:didAcceptContentProposal:
	@abstract	The delegate should replace the current player item with the next item.
	@discussion	Clients must implement this method when setting the nextContentProposal property of AVPlayerViewController. The delegate should create a new AVPlayerItem and update the AVPlayer or AVQueuePlayer.
 */
- (void)playerViewController:(AVPlayerViewController *)playerViewController didAcceptContentProposal:(AVContentProposal *)proposal API_AVAILABLE(tvos(10.0)) API_UNAVAILABLE(ios, watchos, macCatalyst, visionos);

/*!
	@method		playerViewController:didRejectContentProposal:
	@abstract	The delegate should react to the user rejecting the content proposal, typically by dismissing the player view controller.
	@discussion	If the client does not implement this method, the player view controller will be dismissed.
 */
- (void)playerViewController:(AVPlayerViewController *)playerViewController didRejectContentProposal:(AVContentProposal *)proposal API_AVAILABLE(tvos(10.0)) API_UNAVAILABLE(ios, watchos, macCatalyst, visionos);

/*!
	@method		playerViewController:willTransitionToVisibilityOfTransportBar:withAnimationCoordinator:
	@abstract	Called when the visibility of the transport bar changes.
	@param		playerViewController
				The player view controller.
	@param		visible
				Whether the transport bar will become visible.
	@param		coordinator
				An object conforming to AVPlayerViewControllerAnimationCoordinator.
	@discussion	Use the animation coordinator to synchronize animations with transport bar visibility.
 */
- (void)playerViewController:(AVPlayerViewController *)playerViewController willTransitionToVisibilityOfTransportBar:(BOOL)visible withAnimationCoordinator:(id<AVPlayerViewControllerAnimationCoordinator>)coordinator API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(ios, watchos, macCatalyst, visionos);

@end


// MARK: -

API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(ios, visionos) API_UNAVAILABLE(watchos)
@protocol AVPlayerViewControllerAnimationCoordinator <NSObject>
/*!
	@method		addCoordinatedAnimations:completion:
	@abstract	Add animations to be performed alongside the playback controls visibility animation.
 */
- (void)addCoordinatedAnimations:(void (^_Nullable)(void))animations completion:(void (^_Nullable)(BOOL finished))completion;

@end


// MARK: - Deprecated APIs

@interface AVPlayerViewController (Deprecated)

/*!
	@property	customInfoViewController
	@abstract	A view controller to be displayed alongside system-provided info and settings panels.
	@discussion	Use this property to provide client-specific content and controls in an additional info view. Implement -preferredContentSize to provide the desired view size.
 */
@property (nonatomic, strong, nullable) UIViewController *customInfoViewController API_DEPRECATED_WITH_REPLACEMENT("Use customInfoViewControllers", tvos(11.0, 15.0)) API_UNAVAILABLE(ios, watchos, visionos);

@end

NS_ASSUME_NONNULL_END
