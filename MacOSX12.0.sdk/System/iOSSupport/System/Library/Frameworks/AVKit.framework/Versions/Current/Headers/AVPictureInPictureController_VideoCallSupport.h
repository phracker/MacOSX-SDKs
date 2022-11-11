/*
 File: AVPictureInPictureController_VideoCallSupport.h
 
 Framework: AVKit
 
 Copyright © 2021 Apple Inc. All rights reserved.
 */

#import <AVKit/AVPictureInPictureController.h>
#import <UIKit/UIKit.h>

@class UIView;

NS_ASSUME_NONNULL_BEGIN

/*!
	@class      AVPictureInPictureVideoCallViewController
	@abstract   Subclass or directly use `AVPictureInPictureVideoCallViewController` as the container for content to be shown in Picture in Picture while video calls are active.
 */
API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(tvos, macos, watchos)
@interface AVPictureInPictureVideoCallViewController : UIViewController
@end


/*!
	@abstract   A category on `AVPictureInPictureControllerContentSource` for creating a content source to be used to support active video calls, including camera access, in Picture in Picture.
	@discussion
		- This class must only be used when a video call is active. When a video call ends, set `AVPictureInPictureController.contentSource` to `nil` or to another content source.
		- Use of this class requires an entitlement to use the camera in Picture in Picture. See http://developer.apple.com/contact/request/multitasking-camera-access.
		- Note that even when Picture in Picture is active, the device may be locked or Picture in Picture may be stashed off screen. In such cases, the camera will be unavailable until the device is unlocked or Picture in Picture is unstashed.
		- See `AVPictureInPictureController` for functionality common across all Picture in Picture scenarios, such as callbacks to determine when Picture In Picture starts or to indicate a preference for Picture in Picture to start automatically even when not full screen.
 */
@interface AVPictureInPictureControllerContentSource (VideoCallSupport)

/*!
	@method     initWithActiveVideoCallSourceView:contentViewController:
	@param      sourceView
				The view which contains content associated with the call.
	@param      contentViewController
				The view controller that should appear in the system's Picture in Picture window.
	@abstract   Initializes a new `AVPictureInPictureControllerContentSource` suitable for supporting an active video call. This object should only be used for the duration of the call.
*/
- (instancetype)initWithActiveVideoCallSourceView:(UIView *)sourceView contentViewController:(AVPictureInPictureVideoCallViewController *)contentViewController API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(macos, tvos, watchos);

/*!
	@property   activeVideoCallSourceView
	@abstract   When a video call is active and the application is foreground, this view contains content associated with the call.
	@discussion `AVPictureInPictureController` uses this view's layout frame and visibility to determine whether or not Picture in Picture should begin automatically when the app moves to background.
				The layout frame also influences the animation when entering and exiting Picture in Picture.
*/
@property (nonatomic, weak, readonly) UIView *activeVideoCallSourceView API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(macos, tvos, watchos);

/*!
	@property   activeVideoCallContentViewController
	@abstract   This view controller will appear in the system's Picture in Picture window when Picture in Picture is active.
	@discussion This view controller may set a custom `preferredContentSize` which will influence both the aspect ratio and the size of the Picture in Picture window.
				When this view controller's appearance methods indicate that it has appeared on screen, content associated with the video call should be placed in its view hierarchy.
				Although apps can choose to move content from their source view to this view controller, it is also valid to show different views, as long as they represent the same video call.
				The content should always fill the view controller's view's bounds.
				Note that this view controller's view is not interactive and will not receive touches or other user input.
*/
@property (nonatomic, readonly) AVPictureInPictureVideoCallViewController *activeVideoCallContentViewController API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(macos, tvos, watchos);

@end

NS_ASSUME_NONNULL_END
