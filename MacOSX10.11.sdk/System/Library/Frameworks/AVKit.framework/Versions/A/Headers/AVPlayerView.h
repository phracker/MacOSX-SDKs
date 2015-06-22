/*
	File:  AVPlayerView.h
	
	Framework:  AVKit
	
	Copyright 2013-2015 Apple Inc. All rights reserved.
	
 */

#import <AppKit/AppKit.h>

NS_ASSUME_NONNULL_BEGIN

@class AVPlayer;

/*!
	@class		AVPlayerView
	@abstract	AVPlayerView is a subclass of NSView that can be used to display the visual content of an AVPlayer object and the standard playback controls.
 */

NS_CLASS_AVAILABLE_MAC(10_9)
@interface AVPlayerView : NSView

/*!
	@property	player
	@abstract	The player from which to source the media content for the view.
 */
@property (nullable) AVPlayer *player;

/*!
	@constant	AVPlayerViewControlsStyleNone
	@abstract	No controls pane is associated with the view.
	@constant	AVPlayerViewControlsStyleInline
	@abstract	The inline controls pane is associated with the view.
	@constant	AVPlayerViewControlsStyleFloating
	@abstract	The floating controls pane is associated with the view.
	@constant	AVPlayerViewControlsStyleMinimal
	@abstract	The minimal controls pane is associated with the view.
	@constant	AVPlayerViewControlsStyleDefault
	@abstract	The default controls pane is associated with the view.
 */
typedef NS_ENUM(NSInteger, AVPlayerViewControlsStyle) {
	AVPlayerViewControlsStyleNone,
	AVPlayerViewControlsStyleInline,
	AVPlayerViewControlsStyleFloating,
	AVPlayerViewControlsStyleMinimal,
	AVPlayerViewControlsStyleDefault = AVPlayerViewControlsStyleInline
} NS_ENUM_AVAILABLE_MAC(10_9);

/*!
	@property	controlsStyle
	@abstract	The style of the playback controls pane currently associated with the view.
 */
@property AVPlayerViewControlsStyle controlsStyle;

/*!
	@property	videoGravity
	@abstract	A string defining how the video is displayed within an AVPlayerLayer bounds rect.
	@discussion	Options are AVLayerVideoGravityResizeAspect, AVLayerVideoGravityResizeAspectFill and AVLayerVideoGravityResize. AVLayerVideoGravityResizeAspect is default.
				See <AVFoundation/AVAnimation.h> for a description of these options.
 */
@property (copy) NSString *videoGravity NS_AVAILABLE_MAC(10_10);

/*!
	@property	readyForDisplay
	@abstract	Boolean indicating that the first video frame has been made ready for display for the current item of the associated AVPlayer.
 */
@property (readonly, getter = isReadyForDisplay) BOOL readyForDisplay NS_AVAILABLE_MAC(10_10);

/*!
	@property	videoBounds
	@abstract	The current size and position of the video image as displayed within the receiver's view's bounds.
 */
@property (readonly) NSRect videoBounds NS_AVAILABLE_MAC(10_10);

/*!
	@property	contentOverlayView
	@abstract	Use the content overlay view to add additional custom views between the video content and the controls.
 */
@property (readonly, nullable) NSView *contentOverlayView NS_AVAILABLE_MAC(10_10);

@end


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
@property (nullable) NSMenu *actionPopUpButtonMenu;

/*!
	@property	showsFullScreenToggleButton
	@abstract	Whether or not the controls pane will show a full screen toggle button. Default is NO.
 */
@property BOOL showsFullScreenToggleButton;

@end


@interface AVPlayerView (AVPlayerViewTrimming)

/*!
	@property	canBeginTrimming
	@abstract	Whether or not the current media can be trimmed.
 */
@property (readonly) BOOL canBeginTrimming;

/*!
	@constant	AVPlayerViewTrimOKButton
	@abstract	The user selected the Trim button.
	@constant	AVPlayerViewTrimCancelButton
	@abstract	The user selected the Cancel button.
 */
typedef NS_ENUM(NSInteger, AVPlayerViewTrimResult) {
	AVPlayerViewTrimOKButton,
	AVPlayerViewTrimCancelButton
} NS_ENUM_AVAILABLE_MAC(10_9);

/*!
	@method		beginTrimmingWithCompletionHandler:
	@param		handler
				A completion handler that is executed when the user selects either the Trim or Cancel button in the trimming UI.
	@abstract	Sets the controls panel into trimming mode and blocks until the user selects either the Trim or the Cancel button.
 */
- (void)beginTrimmingWithCompletionHandler:(nullable void (^)(AVPlayerViewTrimResult result))handler;

@end


@interface AVPlayerView (AVPlayerViewChapterIndicator)

/*!
	@method		flashChapterNumber:chapterTitle:
	@param		chapterNumber
				The chapter number (required).
	@param		chapterTitle
				The chapter title (optional).
	@abstract	Display the provided chapter number and title momentarily.
 */
- (void)flashChapterNumber:(NSUInteger)chapterNumber chapterTitle:(NSString *)chapterTitle;

@end

NS_ASSUME_NONNULL_END
