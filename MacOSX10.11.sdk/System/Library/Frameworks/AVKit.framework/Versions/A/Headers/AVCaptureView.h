/*
	File:  AVCaptureView.h
	
	Framework:  AVKit
	
	Copyright 2014-2015 Apple Inc. All rights reserved.
	
 */

#import <AppKit/AppKit.h>

NS_ASSUME_NONNULL_BEGIN

@class AVCaptureSession;
@class AVCaptureFileOutput;
@protocol AVCaptureViewDelegate;

/*!
	@class		AVCaptureView
	@abstract	AVCaptureView is a subclass of NSView that can be used to display standard user interface controls for capturing media data.
 */

NS_CLASS_AVAILABLE_MAC(10_10)
@interface AVCaptureView : NSView

/*!
	@property	session
	@abstract	A capture session represented by this view.
	@discussion	Modifying the capture session will impact its visual representation in the view. The default value is a session configured for movie file recordings of audio and video media data. Use -setSession:showVideoPreview:showAudioPreview: to change the value of this property.
 */
@property (readonly, nullable) AVCaptureSession *session;

/*!
	@method		setSession:allowVideoSourceSelection:allowAudioSourceSelection:
	@abstract	Sets the session represented by this view.
	@param		session
				The session to be represented.
	@param		showVideoPreview
				Whether or not video preview should be shown. If YES, capture inputs for video media data will be added, removed, or modified depending on device availability and user selection.
	@param		showAudioPreview
				Whether or not audio preview should be shown. If YES, capture inputs for audio media data will be added, removed, or modified depending on device availability and user selection.
	@discussion The view must either show audio preview or video preview or both. Furthermore, the view may modify the capture session, for example, to access media data for preview or when the user select a new capture source. Only the default session is started and stopped automatically. The provided session must be manually started and stopped.
 */
- (void)setSession:(nullable AVCaptureSession *)session showVideoPreview:(BOOL)showVideoPreview showAudioPreview:(BOOL)showAudioPreview;

/*!
	@property	fileOutput
	@abstract	A capture file output used to record media data.
	@discussion	The value of this property is the first instance of AVCaptureFileOutput contained in the session's outputs array or nil if no such instance is found. In the latter case the capture view's start recording button will be disabled. However, the controls for choosing input sources may still be enabled.
 */
@property (readonly, nullable) AVCaptureFileOutput *fileOutput;

/*!
	@property	delegate
	@abstract	The capture view's delegate.
	@discussion	The start recording button will be disabled if the delegate is not set.
 */
@property (weak, nullable) id <AVCaptureViewDelegate> delegate;

/*!
	@constant	AVCaptureViewControlsStyleInline
	@abstract	The inline controls pane for media recording is associated with the view.
	@constant	AVCaptureViewControlsStyleFloating
	@abstract	The floating controls pane for media recordings is associated with the view.
	@constant	AVCaptureViewControlsStyleInlineDeviceSelection
	@abstract	The inline controls pane for selection capture devices is associated with the view.
	@constant	AVCaptureViewControlsStyleDefault
	@abstract	The default controls pane is associated with the view.
 */
typedef NS_ENUM(NSInteger, AVCaptureViewControlsStyle) {
	AVCaptureViewControlsStyleInline,
	AVCaptureViewControlsStyleFloating,
	AVCaptureViewControlsStyleInlineDeviceSelection,
	AVCaptureViewControlsStyleDefault = AVCaptureViewControlsStyleInline
} NS_ENUM_AVAILABLE_MAC(10_10);

/*!
	@property	controlsStyle
	@abstract	The style of the capture controls pane associated with the view.
 */
@property AVCaptureViewControlsStyle controlsStyle;

/*!
	@property	videoGravity
	@abstract	A string defining how the video is displayed within the views bounds rect.
	@discussion	Options are AVLayerVideoGravityResize, AVLayerVideoGravityResizeAspect and AVLayerVideoGravityResizeAspectFill. AVLayerVideoGravityResizeAspect is default. See <AVFoundation/AVAnimation.h> for a description of these options.
 */
@property (copy) NSString *videoGravity;

@end


/*!
	@protocol	AVCaptureViewDelegate
	@abstract	Defines an interface for delegates of AVCaptureView.
 */

@protocol AVCaptureViewDelegate <NSObject>

/*!
	@method		captureView:startRecordingToFileOutput:
	@abstract	Informs the delegate that a new media recording should be started.
	@discussion	If captureFileOutput is an instance of AVCaptureMovieFileOutput this can be achieved by calling startRecordingToOutputFileURL:recordingDelegate: on the captureFileOutput.
 */
- (void)captureView:(AVCaptureView *)captureView startRecordingToFileOutput:(AVCaptureFileOutput *)fileOutput;

@end

NS_ASSUME_NONNULL_END
