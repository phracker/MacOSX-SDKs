/*
	File:  AVPlayerView.h
	
	Framework:  AVKit
	
	Copyright © 2013-2022 Apple Inc. All rights reserved.
	
 */

#import <AppKit/AppKit.h>
#import <AVFoundation/AVFoundation.h>
#import <AVKit/AVKitTypes.h>


NS_ASSUME_NONNULL_BEGIN

@class AVPlaybackSpeed;

@protocol AVPlayerViewDelegate;
@protocol AVPlayerViewPictureInPictureDelegate;


// MARK: -

/*!
	@class		AVPlayerView
	@abstract	AVPlayerView is a subclass of NSView that can be used to display the visual content of an AVPlayer object and the standard playback controls.
 */
API_AVAILABLE(macosx(10.9))
@interface AVPlayerView : NSView

/*!
	@property	player
	@abstract	The player from which to source the media content for the view.
 */
@property (nullable, strong) AVPlayer *player;

/*!
	@constant	AVPlayerViewControlsStyleNone
				No controls pane is associated with the view.
	@constant	AVPlayerViewControlsStyleInline
				The inline controls pane is associated with the view.
	@constant	AVPlayerViewControlsStyleFloating
				The floating controls pane is associated with the view.
	@constant	AVPlayerViewControlsStyleMinimal
				The minimal controls pane is associated with the view.
	@constant	AVPlayerViewControlsStyleDefault
				The default controls pane is associated with the view.
 */
typedef NS_ENUM(NSInteger, AVPlayerViewControlsStyle) {
	AVPlayerViewControlsStyleNone,
	AVPlayerViewControlsStyleInline,
	AVPlayerViewControlsStyleFloating,
	AVPlayerViewControlsStyleMinimal,
	AVPlayerViewControlsStyleDefault = AVPlayerViewControlsStyleInline
} API_AVAILABLE(macosx(10.9));

/*!
	@property	controlsStyle
	@abstract	The style of the playback controls pane currently associated with the view.
 	@discussion	After macOS 11, the floating style controls will always be used when presenting in fullscreen and AVPlayerViewControlsStyleNone is not specified.
 */
@property AVPlayerViewControlsStyle controlsStyle;

/*!
	@property	videoGravity
	@abstract	A string defining how the video is displayed within an AVPlayerLayer bounds rect.
	@discussion	Options are AVLayerVideoGravityResizeAspect, AVLayerVideoGravityResizeAspectFill and AVLayerVideoGravityResize. AVLayerVideoGravityResizeAspect is default.
 */
@property (copy) AVLayerVideoGravity videoGravity API_AVAILABLE(macosx(10.10));

/*!
	@property	readyForDisplay
	@abstract	Boolean indicating that the first video frame has been made ready for display for the current item of the associated AVPlayer.
 */
@property (readonly, getter = isReadyForDisplay) BOOL readyForDisplay API_AVAILABLE(macosx(10.10));

/*!
	@property	videoBounds
	@abstract	The current size and position of the video image as displayed within the receiver's view's bounds.
 */
@property (readonly) NSRect videoBounds API_AVAILABLE(macosx(10.10));

/*!
	@property	contentOverlayView
	@abstract	Use the content overlay view to add additional custom views between the video content and the controls.
 */
@property (readonly, nullable) NSView *contentOverlayView API_AVAILABLE(macosx(10.10));

/*!
	@property	updatesNowPlayingInfoCenter
	@abstract	Whether or not the now playing info center should be updated. Default is YES.
 */
@property BOOL updatesNowPlayingInfoCenter API_AVAILABLE(macosx(10.13));

/*!
	@property	delegate
	@abstract	The receiver's delegate.
 */
@property (nonatomic, readwrite, nullable, weak) id<AVPlayerViewDelegate> delegate API_AVAILABLE(macos(12.0));

/**
 @property		speeds
 @abstract		A list of user selectable playback speeds to be shown in the playback speed control.
 @discussion	By default this property will be set to the systemDefaultSpeeds class property. Setting this property to nil will hide the playback speed selection UI.
	 
				To set the currently selected playback speed programmatically, either set the defaultRate on the AVPlayer associated with this view controller or use the selectSpeed method on AVPlayerView.
 */
@property (copy) NSArray<AVPlaybackSpeed *> *speeds API_AVAILABLE(macos(13.0));

/*!
 @property		selectedSpeed
 @abstract		The currently selected playback speed.
 @discussion	Changes to the associated AVPlayer's defaultRate will be reflected in this property and vice versa. If the associated AVPlayer's defaultRate is set to a value that does not match a speed in the speeds list property, the selected speed will be nil.
 */
@property (readonly, nullable) AVPlaybackSpeed *selectedSpeed API_AVAILABLE(macos(13.0));


/*!
 @property		selectSpeed
 @param			speed
				The playback speed to select.
 @abstract		Sets the input AVPlaybackSpeed as the selected speed.
 @discussion	Calls to selectSpeed with AVPlaybackSpeeds not contained within the speeds property array will be ignored.
 */
- (void)selectSpeed:(AVPlaybackSpeed *)speed API_AVAILABLE(macos(13.0));

/*!
	@property	allowsVideoFrameAnalysis
	@abstract	When set to YES, the AVPlayerView will try to find objects, text and people while the media is paused. When an object is found, the user will be able to interact with it selecting and right clicking to present a context menu. Default is YES.
 */
@property (nonatomic) BOOL allowsVideoFrameAnalysis API_AVAILABLE(macos(13.0)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@property	videoFrameAnalysisTypes
	@abstract	The types of items AVPlayerView looks for in a paused video frame.
 */
@property (nonatomic) AVVideoFrameAnalysisType videoFrameAnalysisTypes API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(tvos, watchos, macCatalyst, ios);

/*!
	@property	allowsMagnification
	@abstract	Whether the magnify gesture will change the video's view magnification.
	@discussion	The default value is NO. This property only effects whether the magnify gesture triggers magnification. A client can still programmatically change magnification even when the value of this is NO. This behavior matches the behavior of NSScrollView.
 */
@property (nonatomic, setter = setAllowsMagnification:) BOOL allowsMagnification API_AVAILABLE(macos(13.0));

/*!
	@property	magnification
	@abstract	The factor by which the video's view is currently scaled.
	@discussion	The default value is 1.0. The value cannot be smaller than 1.0 or larger 64.0. Nearest neighbor interpolation will be used once the content has been zoomed past a certain factor.
 */
@property (nonatomic, setter = setMagnification:) CGFloat magnification API_AVAILABLE(macos(13.0));

/*!
	@method		setMagnification:centeredAtPoint:
	@abstract	Scales the video's view by a specified factor and centers the result on a specified point.
	@param		magnification The factor by which to scale the video's view.
	@param		point The point (in view space) on which to center magnification.
	@discussion	The magnification cannot be smaller than 1.0 or larger 64.0. Nearest neighbor interpolation will be used once the content has been zoomed past a certain factor.
 */
- (void)setMagnification:(CGFloat)magnification centeredAtPoint:(CGPoint)point API_AVAILABLE(macos(13.0));

/*!
 Describes how High Dynamic Range (HDR) video content renders.
 
 Defaults to ``AVDisplayDynamicRangeAutomatic``.
 
 - Note: This property will only have effect if the video content supports HDR.
 */
@property (nonatomic, assign, readwrite) AVDisplayDynamicRange preferredDisplayDynamicRange API_AVAILABLE(macos(26.0));

@end


// MARK: -

@interface AVPlayerView (AVPlayerViewCustomization)

/*!
	@property	showsFrameSteppingButtons
	@abstract	Replace scanning controls in the playback UI with frame stepping buttons. Default is NO.
 */
@property BOOL showsFrameSteppingButtons;

/*!
	@property	showsSharingServiceButton
	@abstract	Whether or not the controls pane will show a sharing service button when the current player item can be shared. Default is NO.
 */
@property BOOL showsSharingServiceButton;

/*!
	@property	actionPopUpButtonMenu
	@abstract	Clients can set this property in order to show an action pop up button. Default is nil.
 */
@property (nullable) IBOutlet NSMenu *actionPopUpButtonMenu;

/*!
	@property	showsFullScreenToggleButton
	@abstract	Whether or not the controls pane will show a full screen toggle button. Default is NO.
 */
@property BOOL showsFullScreenToggleButton;

/*!
	@property    showsTimecodes
	@abstract    If timecodes are available, allow the AVPlayerView controls to enter timecode mode. Default is NO.
 */
@property BOOL showsTimecodes API_AVAILABLE(macos(10.15));

@end


// MARK: -

@interface AVPlayerView (AVPlayerViewTrimming)

/*!
	@property	canBeginTrimming
	@abstract	Whether or not the current media can be trimmed.
 */
@property (readonly) BOOL canBeginTrimming;

/*!
	@constant	AVPlayerViewTrimOKButton
				The user selected the Trim button.
	@constant	AVPlayerViewTrimCancelButton
				The user selected the Cancel button.
 */
typedef NS_ENUM(NSInteger, AVPlayerViewTrimResult) {
	AVPlayerViewTrimOKButton,
	AVPlayerViewTrimCancelButton
} API_AVAILABLE(macosx(10.9));

/*!
	@method		beginTrimmingWithCompletionHandler:
	@param		handler
				A completion handler that is executed when the user selects either the Trim or Cancel button in the trimming UI.
	@abstract	Sets the controls panel into trimming mode and blocks until the user selects either the Trim or the Cancel button.
 */
- (void)beginTrimmingWithCompletionHandler:(nullable void (^)(AVPlayerViewTrimResult result))handler;

@end


// MARK: -

@interface AVPlayerView (AVPlayerViewChapterIndicator)

/*!
	@method		flashChapterNumber:chapterTitle:
	@param		chapterNumber
				The chapter number (required).
	@param		chapterTitle
				The chapter title (optional).
	@abstract	Display the provided chapter number and title momentarily.
 */
- (void)flashChapterNumber:(NSUInteger)chapterNumber chapterTitle:(nullable NSString *)chapterTitle;

@end


// MARK: -

@interface AVPlayerView (AVPlayerViewPictureInPictureSupport)

/*!
 	@property	allowsPictureInPicturePlayback
 	@abstract	Whether or not the receiver allows Picture in Picture playback. Default is NO.
 */
@property (nonatomic) BOOL allowsPictureInPicturePlayback API_AVAILABLE(macos(10.15));

/*!
 	@property	pictureInPictureDelegate
 	@abstract	A delegate for customizing Picture in Picture playback experience.
 */
@property (nonatomic, nullable, weak) id<AVPlayerViewPictureInPictureDelegate> pictureInPictureDelegate API_AVAILABLE(macos(10.15));

@end


// MARK: -

/*!
	@protocol	AVPlayerViewDelegate
	@abstract	A protocol for delegates of AVPlayerView.
 */
API_AVAILABLE(macos(12.0))
@protocol AVPlayerViewDelegate <NSObject>
@optional

/*!
	@method		playerViewWillEnterFullScreen:
	@param		playerView
				The player view.
	@abstract	The delegate can implement this method to be notified when the AVPlayerView will enter full screen.
 */
- (void)playerViewWillEnterFullScreen:(AVPlayerView *)playerView;

/*!
	@method		playerViewDidEnterFullScreen:
	@param		playerView
				The player view.
	@abstract	The delegate can implement this method to be notified when the AVPlayerView did enter full screen.
 */
- (void)playerViewDidEnterFullScreen:(AVPlayerView *)playerView;

/*!
	@method		playerViewWillExitFullScreen:
	@param		playerView
				The player view.
	@abstract	The delegate can implement this method to be notified when the AVPlayerView will exit full screen.
 */
- (void)playerViewWillExitFullScreen:(AVPlayerView *)playerView;

/*!
	@method		playerViewDidExitFullScreen:
	@param		playerView
				The player view.
	@abstract	The delegate can implement this method to be notified when the AVPlayerView did exit full screen.
 */
- (void)playerViewDidExitFullScreen:(AVPlayerView *)playerView;

/*!
	@method		playerView:restoreUserInterfaceForFullScreenExitWithCompletionHandler:
	@param		playerView
				The player view.
	@param		completionHandler
 				The completion handler the delegate must call after restoring the interface for an exit full screen transition.
	@abstract	The delegate can implement this method to restore the user interface before exiting fullscreen.
 */
- (void)playerView:(AVPlayerView *)playerView restoreUserInterfaceForFullScreenExitWithCompletionHandler:(void (^)(BOOL restored))completionHandler;

@end


// MARK: -

API_AVAILABLE(macos(10.15))
@protocol AVPlayerViewPictureInPictureDelegate <NSObject>
@optional

/*!
 	@method		playerViewWillStartPictureInPicture:
 	@param		playerView
 				The player view.
 	@abstract	Delegate can implement this method to be notified when Picture in Picture will start.
 */
- (void)playerViewWillStartPictureInPicture:(AVPlayerView *)playerView;

/*!
 	@method		playerViewDidStartPictureInPicture:
 	@param		playerView
 				The player view.
 	@abstract	Delegate can implement this method to be notified when Picture in Picture did start.
 */
- (void)playerViewDidStartPictureInPicture:(AVPlayerView *)playerView;

/*!
 	@method		playerView:failedToStartPictureInPictureWithError:
 	@param		playerView
 				The player view.
 	@param		error
 				An error describing why it failed.
 	@abstract	Delegate can implement this method to be notified when Picture in Picture failed to start.
 */
- (void)playerView:(AVPlayerView *)playerView failedToStartPictureInPictureWithError:(NSError *)error;

/*!
 	@method		playerViewWillStopPictureInPicture:
 	@param		playerView
 				The player view.
 	@abstract	Delegate can implement this method to be notified when Picture in Picture will stop.
 */
- (void)playerViewWillStopPictureInPicture:(AVPlayerView *)playerView;

/*!
 	@method		playerViewDidStopPictureInPicture:
 	@param		playerView
 				The player view.
 	@abstract	Delegate can implement this method to be notified when Picture in Picture did stop.
 */
- (void)playerViewDidStopPictureInPicture:(AVPlayerView *)playerView;

/*!
 	@method		playerView:restoreUserInterfaceForPictureInPictureStopWithCompletionHandler:
 	@param		playerView
 				The player view.
 	@param		completionHandler
 				The completion handler the delegate needs to call after restore.
 	@abstract	Delegate can implement this method to restore the user interface before Picture in Picture stops.
 */
- (void)playerView:(AVPlayerView *)playerView restoreUserInterfaceForPictureInPictureStopWithCompletionHandler:(void (^)(BOOL restored))completionHandler;

/*!
 	@method		playerViewShouldAutomaticallyDismissAtPictureInPictureStart:
 	@param		playerView
 				The player view.
 	@abstract	Delegate can implement this method and return NO to prevent player view from automatically being miniaturized or losing focus when Picture in Picture starts.
 */
- (BOOL)playerViewShouldAutomaticallyDismissAtPictureInPictureStart:(AVPlayerView *)playerView;

@end

NS_ASSUME_NONNULL_END
