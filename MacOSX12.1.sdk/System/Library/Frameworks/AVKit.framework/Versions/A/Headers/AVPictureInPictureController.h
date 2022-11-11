/*
	File:  AVPictureInPictureController.h
	
	Framework:  AVKit
	
	Copyright © 2015-2020 Apple Inc. All rights reserved.
	
 */

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

#import <AVKit/AVKitDefines.h>


NS_ASSUME_NONNULL_BEGIN

#if TARGET_OS_IPHONE
@class UIImage;
@class UITraitCollection;
#elif TARGET_OS_OSX
@class NSImage;
#endif // TARGET_OS_IPHONE

@class AVPictureInPictureControllerContentSource;
@protocol AVPictureInPictureControllerDelegate;

/*!
	@class		AVPictureInPictureController
	@abstract	AVPictureInPictureController is a subclass of NSObject that can be used to present the contents of an AVPlayerLayer or AVPlayerView floating on top of applications.
 */

API_AVAILABLE(ios(9.0), macos(10.15), tvos(14.0)) API_UNAVAILABLE(watchos)
@interface AVPictureInPictureController : NSObject

/*!
	@method		isPictureInPictureSupported
	@abstract	Whether or not Picture in Picture is supported on the current device.
	@discussion	When NO, all initializers will return nil.
 */
+ (BOOL)isPictureInPictureSupported;

#if TARGET_OS_IPHONE
/*!
	@method		pictureInPictureButtonStartImageCompatibleWithTraitCollection:
	@param		traitCollection
				Traits that describe the image to retrieve, pass nil to use traits that describe the main screen.
	@abstract	System default Picture in Picture start template image for use in client's Picture in Picture button.
 */
+ (UIImage *)pictureInPictureButtonStartImageCompatibleWithTraitCollection:(nullable UITraitCollection *)traitCollection;

/*!
	@method		pictureInPictureButtonStopImageCompatibleWithTraitCollection:
	@param		traitCollection
				Traits that describe the image to retrieve, pass nil to use traits that describe the main screen.
	@abstract	System default Picture in Picture stop template image for use in client's Picture in Picture button.
 */
+ (UIImage *)pictureInPictureButtonStopImageCompatibleWithTraitCollection:(nullable UITraitCollection *)traitCollection;

/*!
	@property	pictureInPictureButtonStartImage
	@abstract	System default Picture in Picture start template image for use in client's Picture in Picture button.
 */
@property (class, nonatomic, readonly) UIImage *pictureInPictureButtonStartImage API_AVAILABLE(ios(13.0), tvos(14.0));

/*!
 	@property	pictureInPictureButtonStopImage
 	@abstract	System default Picture in Picture stop template image for use in client's Picture in Picture button.
 */
@property (class, nonatomic, readonly) UIImage *pictureInPictureButtonStopImage API_AVAILABLE(ios(13.0), tvos(14.0));
#elif TARGET_OS_OSX
/*!
	@property	pictureInPictureButtonStartImage
	@abstract	System default Picture in Picture start template image for use in client's Picture in Picture button.
 */
@property (class, nonatomic, readonly) NSImage *pictureInPictureButtonStartImage;

/*!
	@property	pictureInPictureButtonStopImage
 	@abstract	System default Picture in Picture stop template image for use in client's Picture in Picture button.
 */
@property (class, nonatomic, readonly) NSImage *pictureInPictureButtonStopImage;
#endif // TARGET_OS_IPHONE

/*!
	@method     initWithContentSource:
	@param      contentSource
				The content source to be shown in Picture in Picture.
	@abstract   Use this initializer for content that may be a sample buffer display layer or a player layer.
 */
- (instancetype)initWithContentSource:(AVPictureInPictureControllerContentSource *)contentSource API_AVAILABLE(ios(15.0), tvos(15.0), macos(12.0)) API_UNAVAILABLE(watchos) NS_DESIGNATED_INITIALIZER;

/*!
	@method		initWithPlayerLayer:
	@param		playerLayer
				The player layer from which to source the media content for the Picture in Picture controller.
	@abstract	Initialize the picture in picture controller with a player layer.
 */
- (nullable instancetype)initWithPlayerLayer:(AVPlayerLayer *)playerLayer;

/*!
	@property   contentSource
	@abstract   The receiver's content source. Can be changed while Picture in Picture is active, but the new content source must be ready for display (in the case of AVPlayerLayer, that means AVPlayerLayer.isReadyForDisplay must return YES), otherwise Picture in Picture will stop.
 */
@property (nonatomic, strong, nullable) AVPictureInPictureControllerContentSource *contentSource API_AVAILABLE(ios(15.0), tvos(15.0), macos(12.0)) API_UNAVAILABLE(watchos);

/*!
	@property	playerLayer
	@abstract	The receiver's player layer.
 */
@property (nonatomic, readonly) AVPlayerLayer *playerLayer;

/*!
	@property	delegate
	@abstract	The receiver's delegate.
 */
@property (nonatomic, weak, nullable) id <AVPictureInPictureControllerDelegate> delegate;

/*!
	@method		startPictureInPicture
	@abstract	Start Picture in Picture for the provided AVPlayerLayer if possible.
	@discussion	Receiver will call -pictureInPictureControllerWillStartPictureInPicture: if Picture in Picture is currently possible and -pictureInPictureControllerDidStartPictureInPicture: after a successful start. If starting Picture in Picture fails, -pictureInPictureControllerFailedToStartPictureInPicture:withError: is called on the delegate instead. Client can stop Picture in Picture by calling -stopPictureInPicture. In addition the user can stop Picture in Picture through user interaction. It is also possible that Picture in Picture is stopped by the Picture in Picture controller at any time. In all these cases receiver calls -pictureInPictureControllerWillStopPictureInPicture: on the delegate and -pictureInPictureControllerDidStopPictureInPicture:after the stop animation completed.
 */
- (void)startPictureInPicture;

/*!
	@method		stopPictureInPicture
	@abstract	Stop the local Picture in Picture if currently active. On tvOS, this can also stop Picture in Picture sessions for other applications.
	@discussion	See startPictureInPicture for details.
 */
- (void)stopPictureInPicture;

/*!
	@property	pictureInPicturePossible
	@abstract	Whether or not Picture in Picture is currently possible.
 */
@property (nonatomic, readonly, getter = isPictureInPicturePossible) BOOL pictureInPicturePossible;

/*!
	@property	pictureInPictureActive
	@abstract	Whether or not Picture in Picture is currently active.
 */
@property (nonatomic, readonly, getter = isPictureInPictureActive) BOOL pictureInPictureActive;

/*!
	@property	pictureInPictureSuspended
	@abstract	Whether or not Picture in Picture is currently suspended.
 */
@property (nonatomic, readonly, getter = isPictureInPictureSuspended) BOOL pictureInPictureSuspended;

/*!
	@property	canStopPictureInPicture
	@abstract	Whether or not any Picture in Picture is active, and can be stopped.
	@discussion	When true, stopPictureInPicture will stop the active Picture in Picture session. Apps should re-inspect the system-provided picture in picture start button image when this property changes. Observable.
 */
@property (nonatomic, readonly) BOOL canStopPictureInPicture API_AVAILABLE(tvos(14.0)) API_UNAVAILABLE(ios, macos, watchos);

/*!
	@property	requiresLinearPlayback
	@abstract	Disables certain user operations (fast forward, forward skip, and scrubbing).
	@discussion	This can be used to temporarily enforce playback of mandatory content (such as legalese or advertisements).
 */
@property (nonatomic) BOOL requiresLinearPlayback API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0)) API_UNAVAILABLE(watchos);

/*!
	@property    canStartPictureInPictureAutomaticallyFromInline
	@abstract    Indicates whether Picture in Picture should be allowed to start automatically when transitioning to background when the receiver’s content is embedded inline. Default is NO.
	@discussion  This property must only be set to YES for content intended to be the user's primary focus.
 */
@property (nonatomic) BOOL canStartPictureInPictureAutomaticallyFromInline API_AVAILABLE(ios(14.2)) API_UNAVAILABLE(watchos, tvos, macos);

@end


/*!
	@class      AVPictureInPictureControllerContentSource
	@abstract   A content source for AVPictureInPictureController.
	@discussion Create a content source with an appropriate layer, and use it to initialize the AVPictureInPictureController.
 */
API_AVAILABLE(ios(15.0), tvos(15.0), macos(12.0)) API_UNAVAILABLE(watchos)
NS_SWIFT_NAME(AVPictureInPictureController.ContentSource)
@interface AVPictureInPictureControllerContentSource : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
	@method     initWithPlayerLayer:
	@param      playerLayer
				The player layer to be shown in Picture in Picture.
	@abstract   Use this initializer for a content source with a player layer.
*/
- (instancetype)initWithPlayerLayer:(AVPlayerLayer *)playerLayer;

/*!
	@property   playerLayer
	@abstract   The receiver's player layer.
*/
@property (nonatomic, nullable, readonly) AVPlayerLayer *playerLayer;

@end


/*!
	@protocol	AVPictureInPictureControllerDelegate
	@abstract	A protocol for delegates of AVPictureInPictureController.
 */

API_AVAILABLE(ios(9.0), macos(10.15), tvos(14.0)) API_UNAVAILABLE(watchos)
@protocol AVPictureInPictureControllerDelegate <NSObject>
@optional

/*!
	@method		pictureInPictureControllerWillStartPictureInPicture:
	@param		pictureInPictureController
				The Picture in Picture controller.
	@abstract	Delegate can implement this method to be notified when Picture in Picture will start.
 */
- (void)pictureInPictureControllerWillStartPictureInPicture:(AVPictureInPictureController *)pictureInPictureController;

/*!
	@method		pictureInPictureControllerDidStartPictureInPicture:
	@param		pictureInPictureController
				The Picture in Picture controller.
	@abstract	Delegate can implement this method to be notified when Picture in Picture did start.
 */
- (void)pictureInPictureControllerDidStartPictureInPicture:(AVPictureInPictureController *)pictureInPictureController;

/*!
	@method		pictureInPictureController:failedToStartPictureInPictureWithError:
	@param		pictureInPictureController
				The Picture in Picture controller.
	@param		error
				An error describing why it failed.
	@abstract	Delegate can implement this method to be notified when Picture in Picture failed to start.
 */
- (void)pictureInPictureController:(AVPictureInPictureController *)pictureInPictureController failedToStartPictureInPictureWithError:(NSError *)error;

/*!
	@method		pictureInPictureControllerWillStopPictureInPicture:
	@param		pictureInPictureController
				The Picture in Picture controller.
	@abstract	Delegate can implement this method to be notified when Picture in Picture will stop.
 */
- (void)pictureInPictureControllerWillStopPictureInPicture:(AVPictureInPictureController *)pictureInPictureController;

/*!
	@method		pictureInPictureControllerDidStopPictureInPicture:
	@param		pictureInPictureController
				The Picture in Picture controller.
	@abstract	Delegate can implement this method to be notified when Picture in Picture did stop.
 */
- (void)pictureInPictureControllerDidStopPictureInPicture:(AVPictureInPictureController *)pictureInPictureController;

/*!
	@method		pictureInPictureController:restoreUserInterfaceForPictureInPictureStopWithCompletionHandler:
	@param		pictureInPictureController
				The Picture in Picture controller.
	@param		completionHandler
				The completion handler the delegate needs to call after restore.
	@abstract	Delegate can implement this method to restore the user interface before Picture in Picture stops.
 */
- (void)pictureInPictureController:(AVPictureInPictureController *)pictureInPictureController restoreUserInterfaceForPictureInPictureStopWithCompletionHandler:(void (^)(BOOL restored))completionHandler;

@end

NS_ASSUME_NONNULL_END
