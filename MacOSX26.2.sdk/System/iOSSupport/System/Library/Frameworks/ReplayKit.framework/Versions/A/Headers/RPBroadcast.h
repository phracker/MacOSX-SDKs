//
// RPBroadcast.h
// ReplayKit
//
// The following guidelines can be followed to add broadcasting capabilities to an application:
//
// Use the RPScreenRecorder singleton to enable the microphone and front-facing camera recording.
//
// Load an instance of RPBroadcastActivityViewController and present it when the user intends to start  broadcasting. This will present a view controller thats allows the user to select from the broadcast servies available on the device. Selecting a broadcast service presents the service’s UI to the user and allows the user to sign-in and setup their broadcast.
//
// Once setup with the service is complete, an RPBroadcastController instance will be provided via the RPBroadcastActivityViewControllerDelegate protocol. This controller can be used to start, pause and finish the broadcast.
//
// RPBroadcastController will have an NSDictionary instance in its serviceInfo property which will contain a URL  to their broadcast (which can be provided to the user to share prior to starting a broadcast), as well as other optional meta data the service may wish to provide.
//
// Copyright © 2016 Apple Inc. All rights reserved.
//
#include <TargetConditionals.h>

#if TARGET_OS_OSX
#import <AppKit/AppKit.h>
#endif

#if !TARGET_OS_OSX
#import <UIKit/UIKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

@protocol RPBroadcastActivityViewControllerDelegate;
@protocol RPBroadcastControllerDelegate;
@class RPBroadcastController;

#if TARGET_OS_OSX
API_AVAILABLE(macos(11.0))

/*!
 @abstract RPBroadcastActivityControllerDelegate is used to notify the caller when the user has finshed with the RPBroadcastActivityController's picker.
*/
@protocol RPBroadcastActivityControllerDelegate;

/*!
 @class RPBroadcastActivityController
 @abstract Controller object that allows clients to present the macOS broadcast picker and returns the RPBroadcastController object that controls broadcast functionality.
*/
@interface RPBroadcastActivityController : NSObject
/*!
 @abstract Shows the broadcast picker at specified origin point from specified application window. Loads a RPBroadcastActivityController instance and returns it in the handler block. Calling this will present a macOS picker with a list of available broadcast services for the user to select and return the the RPBroadcastActivityController object. Note, the origin point represent the top left hand corner position of the picker that will be displayed. Upon completion of the picker, the picker object will be automatically dismissed and the delegate's broadcastActivityController:didFinishWithBroadcastController:error: will be called.
 @param point origin point where (0,0) is the bottom left of the specified application window
 @param window application window presenting the picker. nil specifies the picker is presented from the application main window.
 @param preferredExtension The extension bundle identifier for the preferred broadcast extension service. nil specifies all extensions will be shown.
 @discussion The handler will be called after the user us finished with the picker and has finish setting up the broadcast extension, which will provide an instance of RPBroadcastAcvityController and an error if one occured.
*/
+ (void)showBroadcastPickerAtPoint:(CGPoint)point fromWindow:(NSWindow *_Nullable)window preferredExtensionIdentifier:(NSString *_Nullable)preferredExtension completionHandler:(void (^)(RPBroadcastActivityController *_Nullable broadcastActivityController, NSError *_Nullable error))handler API_AVAILABLE(macos(11.0));

/*!
 @abstract Delegate that is notified when the activity view controller is complete.
 */
@property (nonatomic, weak, nullable) id<RPBroadcastActivityControllerDelegate> delegate;

@end

@protocol RPBroadcastActivityControllerDelegate <NSObject>

/*  @abstract Called when the controller is finished.
 @param broadcastActivityController The controller instance.
 @param broadcastController An RPBroadcastController instance that can be used to start and stop broadcasts to a user selected service.
 @param error Optional error in the RPRecordingErrorCode domain. A nil error signifies that the user has successfully set up the broadcast with a broadcast service and is ready to start broadcasting.
 */
- (void)broadcastActivityController:(RPBroadcastActivityController *)broadcastActivityController didFinishWithBroadcastController:(nullable RPBroadcastController *)broadcastController error:(nullable NSError *)error API_AVAILABLE(macos(11.0));
@end
#endif

#if !TARGET_OS_OSX
/*! @class RPBroadcastActivityViewController
 @abstract View controller that presents the user with a list of broadcast services installed on the device.
 */
API_AVAILABLE(ios(10.0), tvos(10.0))
@interface RPBroadcastActivityViewController : UIViewController

/*  @abstract Loads a RPBroadcastActivityViewController instance and returns it in the handler block.

 The view controller will present the user with a list of broadcast services available on the device and allow the user to set up a broadcast with the service through the service's UI.

 The RPBroadcastActivityViewController can be presented using [UIViewController presentViewController:animated:completion:] and should be dismissed when the delegate's broadcastActivityViewController:didFinishWithBroadcastController:error: method is called. Note that on large screen devices such as iPad, the default presentation style for view controllers is a popover. For an instance of RPBroadcastActivityViewController to present properly on iPad, it needs to have its popoverPresentationController's sourceRect and sourceView configured.

 @param broadcastActivityViewController The RPBroadcastActivityViewController which can be presented.
 @param error Optional error in the RPRecordingErrorCode domain which is supplied in the event the view controller could not be loaded.
 */
+ (void)loadBroadcastActivityViewControllerWithHandler:(void (^)(RPBroadcastActivityViewController *_Nullable broadcastActivityViewController, NSError *_Nullable error))handler;

/*  @abstract Loads a RPBroadcastActivityViewController instance and returns it in the handler block.

 The view controller will present the user with a view that shows the preferred streaming extension service and allow the user to set up a broadcast with the service through the service's UI.

 The RPBroadcastActivityViewController can be presented using [UIViewController presentViewController:animated:completion:] and should be dismissed when the delegate's broadcastActivityViewController:didFinishWithBroadcastController:error: method is called. Note that on large screen devices such as iPad, the default presentation style for view controllers is a popover. For an instance of RPBroadcastActivityViewController to present properly on iPad, it needs to have its popoverPresentationController's sourceRect and sourceView configured.

 @param preferredExtension The extension bundle identifier for the preferred broadcast extension service
 @param broadcastActivityViewController The RPBroadcastActivityViewController which can be presented, returns nil if ther eis no matching extension.
 @param error Optional error in the RPRecordingErrorCode domain which is supplied in the event the view controller could not be loaded.
 */
+ (void)loadBroadcastActivityViewControllerWithPreferredExtension:(NSString *_Nullable)preferredExtension handler:(nonnull void (^)(RPBroadcastActivityViewController *_Nullable broadcastActivityViewController, NSError *_Nullable error))handler API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos);

/*  @abstract Delegate that is notified when the activity view controller is complete. */
@property (nonatomic, weak, nullable) id<RPBroadcastActivityViewControllerDelegate> delegate;
@end

API_AVAILABLE(ios(10.0), tvos(10.0))
@protocol RPBroadcastActivityViewControllerDelegate <NSObject>

/*  @abstract Called when the view controller is finished.
 @param broadcastActivityViewController The view controller instance.
 @param broadcastController An RPBroadcastController instance that can be used to start and stop broadcasts to a user selected service.
 @param error Optional error in the RPRecordingErrorCode domain. A nil error signifies that the user has successfully set up the broadcast with a broadcast service and is ready to start broadcasting.
 */
- (void)broadcastActivityViewController:(RPBroadcastActivityViewController *)broadcastActivityViewController didFinishWithBroadcastController:(nullable RPBroadcastController *)broadcastController error:(nullable NSError *)error API_AVAILABLE(ios(10.0), tvos(10.0));
@end
#endif

/*! @class RPBroadcastController
 @abstract Available once a user has successfully initiated a broadcast using an RPBroadcastActivityViewController. Can be used to start, pause and stop a broadcast.
 */
API_AVAILABLE(ios(10.0), tvos(10.0), macos(11.0))
@interface RPBroadcastController : NSObject
/*  @abstract Indicates whether the controller is currently broadcasting. */
@property (nonatomic, readonly, getter = isBroadcasting) BOOL broadcasting;
/*  @abstract Indicates whether the controller is currently paused. */
@property (nonatomic, readonly, getter = isPaused) BOOL paused;
/*  @abstract URL that can be used to redirect the user to the on-going or completed broadcast. */
@property (nonatomic, readonly) NSURL *broadcastURL;
/*  @abstract Dictionary updated by the service during a broadcast. The keys and values of this dictionary are defined by the broadcast service. KVO observable. */
@property (nonatomic, readonly, nullable) NSDictionary <NSString *, NSObject <NSCoding> *> *serviceInfo;
/*  @abstract Delegate which will be notified when an error occurs during broadcast. */
@property (nonatomic, weak) id<RPBroadcastControllerDelegate> delegate;
/*  @abstract bundleID of the broadcast extension which was selected by the user. */
@property (nullable, nonatomic, readonly) NSString *broadcastExtensionBundleID API_DEPRECATED("No longer supported", ios(10.0, 11.0), tvos(10.0, 11.0)) API_UNAVAILABLE(macos);
/*  @abstract Start the broadcast.
 @param error Optional error in the RPRecordingErrorCode domain. A nil error signifies that broadcasting has started successfully.
 */
- (void)startBroadcastWithHandler:(void (^)(NSError *_Nullable error))handler;

/*  @abstract Pause the broadcast. The broadcast will pause immediately. */
- (void)pauseBroadcast;

/*  @abstract Resumes the broadcast. The broadcast will resume immediately. */
- (void)resumeBroadcast;

/*  @abstract Finish the broadcast.
 @param error Optional error in the RPRecordingErrorCode domain. A nil error signifies that broadcasting has finished successfully.
 */
- (void)finishBroadcastWithHandler:(void (^)(NSError *_Nullable error))handler;
@end

API_AVAILABLE(ios(10.0), tvos(10.0), macos(11.0))
@protocol RPBroadcastControllerDelegate <NSObject>
@optional

/*  @abstract Called when broadcasting finishes due to an error.
 @param broadcastController The controller instance.
 @param error Required error in the RPRecordingErrorCode domain.
 */

- (void)broadcastController:(RPBroadcastController *)broadcastController didFinishWithError:(nullable NSError *)error;
/*  @abstract Called when the broadcast service has data to pass back to broadcasting app.
 @param broadcastController The controller instance.
 @param serviceInfo NSDictionary instance with keys and values defined by the broadcasting service.
 */
- (void)broadcastController:(RPBroadcastController *)broadcastController didUpdateServiceInfo:(NSDictionary <NSString *, NSObject <NSCoding> *> *)serviceInfo;

/*  @abstract Called when the broadcast service has updated broadcastURL.
 @param broadcastController The controller instance.
 @param broadcastURL NSURL instance with URL of the resource where broacast can be viewed. Defined by broadcast service.
 */
- (void)broadcastController:(RPBroadcastController *)broadcastController didUpdateBroadcastURL:(NSURL *)broadcastURL API_AVAILABLE(ios(11.0), tvos(11.0));
@end

#if !TARGET_OS_OSX
/*! @class RPSystemBroadcastPickerView
 @abstract View that presents the user with a button for starting iOS system broadcast using preferred broadcast service.
 */
API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(tvos, macos)
@interface RPSystemBroadcastPickerView : UIView <NSCoding>
/*  @abstract Bundle identifier of extension that should be used for broadcast. Default is nil which means that all extensions will be presented */
@property (nonatomic, strong, nullable) NSString *preferredExtension;
/*  @abstract Indicates whether the Microphone button is visible in broadcast picker view. Default is YES. */
@property (nonatomic, assign) BOOL showsMicrophoneButton;
@end
#endif

NS_ASSUME_NONNULL_END
