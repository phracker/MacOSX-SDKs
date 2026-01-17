//
// RPBroadcastExtension.h
// ReplayKit
//
// Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#if TARGET_OS_OSX
#import <AppKit/AppKit.h>
#else
#import <UIKit/UIKit.h>
#endif

#import <ReplayKit/RPBroadcastConfiguration.h>

NS_ASSUME_NONNULL_BEGIN
/*!
    @category NSExtensionContext (RPBroadcastExtension)
    @abstract Category which defines the method to call from on an extension context object when user interaction is complete during the broadcast setup flow.
 */
@interface NSExtensionContext (RPBroadcastExtension)

#if TARGET_OS_OSX
/*! @abstract Load information about the broadcasting app.
    @param handler block which will be supplied a bundleID, displayName and an optional appIcon.
 */
- (void)loadBroadcastingApplicationInfoWithCompletion:(void (^)(NSString *bundleID, NSString *displayName, NSImage *__nullable appIcon))handler API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios, tvos, macCatalyst);
#else
/*! @abstract Load information about the broadcasting app.
    @param handler block which will be supplied a bundleID, displayName and an optional appIcon.
 */
- (void)loadBroadcastingApplicationInfoWithCompletion:(void (^)(NSString *bundleID, NSString *displayName, UIImage *__nullable appIcon))handler;
#endif

/*! @abstract Method to be called when the extension should finish. Deprecated.
    @param broadcastURL URL that can be used to redirect the user to the ongoing or completed broadcast. This URL is made available to the running application via a property in RPBroadcastController.
    @param broadcastConfiguration Configuration to use for generating movie clips
    @param setupInfo Dictionary that can be used to share any setup information required by the upload extension. The values and keys in this dictionary are to be defined by the extension developer.
 */
#if !TARGET_OS_OSX
- (void)completeRequestWithBroadcastURL:(NSURL *)broadcastURL broadcastConfiguration:(RPBroadcastConfiguration *)broadcastConfiguration setupInfo:(nullable NSDictionary <NSString *, NSObject <NSCoding> *> *)setupInfo API_DEPRECATED("No longer supported", ios(10.0, 11.0), tvos(10.0, 11.0)) API_UNAVAILABLE(macos);

/*! @abstract Method to be called when the extension should finish.
    @param broadcastURL URL that can be used to redirect the user to the ongoing or completed broadcast. This URL is made available to the running application via a property in RPBroadcastController.
    @param setupInfo Dictionary that can be used to share any setup information required by the upload extension. The values and keys in this dictionary are to be defined by the extension developer.
 */
#endif

- (void)completeRequestWithBroadcastURL:(NSURL *)broadcastURL setupInfo:(nullable NSDictionary <NSString *, NSObject <NSCoding> *> *)setupInfo API_AVAILABLE(ios(11.0), tvos(11.0), macos(11.0));

@end

/*!
 @class RPBroadcastProcessExtension
 @abstract Base class for extensions that are responsible for handling video and audio data.
 */
API_AVAILABLE(ios(10.0), tvos(10.0), macos(11.0))
@interface RPBroadcastHandler : NSObject <NSExtensionRequestHandling>
/*! @abstract Call this method, supplying it with a dictionary defined by the service, to populate the serviceInfo property on RPBroadcastController. This can be used to communicate viewing stats or messages back to the broadcasting app.
 @param serviceInfo Dictionary that can be passed back to the broadcasting app that may contain information about the ongoing broadcast.
 */
- (void)updateServiceInfo:(NSDictionary<NSString *, NSObject <NSCoding> *> *)serviceInfo;

/*! @abstract Call this method, supplying it with a URL to update the broadcastURL property on RPBroadcastController.
 @param broadcastURL URL of the resource where broadcast can be viewed which will be passed to the broadcasting app.
 */
- (void)updateBroadcastURL:(NSURL *)broadcastURL API_AVAILABLE(ios(11.0), tvos(11.0), macos(11.0));
@end

#if !TARGET_OS_OSX
/*!
    @class RPBroadcastMP4ClipHandler
    @abstract Subclass this class to handle movie clips as they are recorded by ReplayKit during the broadcast flow. ReplayKit will call processMP4ClipWithURL when a movie clip is available for processing.
 */
API_DEPRECATED("No longer supported, use RPBroadcastSampleHandler instead.", ios(10.0, 11.0), tvos(10.0, 11.0)) API_UNAVAILABLE(macos)
@interface RPBroadcastMP4ClipHandler : RPBroadcastHandler
/*! @abstract Method which ReplayKit will call when an MP4 movie clip is ready for processing.
 @param mp4ClipURL URL that points to the location of the movie clip recorded by ReplayKit. Note that the URL may be nil in certain cases such as an error.
 @param setupInfo Dictionary supplied by the UI extension that may contain setup information required for processing. The values in this dictionary are to be defined by the extension developer.
 @param finished Boolean indicating that application requested the broadcast to end.
 */
- (void)processMP4ClipWithURL:(nullable NSURL *)mp4ClipURL setupInfo:(nullable NSDictionary <NSString *, NSObject *> *)setupInfo finished:(BOOL)finished;

/*! @abstract Method that should be called when processing is complete.
    @param broadcastConfiguration Optional updated configuration that will be applied to the next MP4 clip.
    @param error Optional error to communicate to ReplayKit and the host application that there was an issue with the broadcast and to stop broadcasting. Note that once this is called, regardles of the existence of an error, the current MP4 clip will no longer be available.
 */
- (void)finishedProcessingMP4ClipWithUpdatedBroadcastConfiguration:(nullable RPBroadcastConfiguration *)broadcastConfiguration error:(nullable NSError *)error;
@end
#endif // !TARGET_OS_OSX

API_AVAILABLE(ios(10.0), tvos(10.0), macos(11.0))
typedef NS_ENUM (NSInteger, RPSampleBufferType) {
    RPSampleBufferTypeVideo = 1,
    RPSampleBufferTypeAudioApp,
    RPSampleBufferTypeAudioMic,
};

/*!
 @key RPVideoSampleOrientationKey
 @abstract Use this key in conjunction with CMGetAttachment on CMSampleBufferRef to get the orientation for the sample. The orientation will follow the enum CGImagePropertyOrientation
 */
API_AVAILABLE(ios(11.0), tvos(11.0), macos(11.0))
extern NSString * const RPVideoSampleOrientationKey;

/*!
 @key RPApplicationInfoBundleIdentifierKey
 @abstract Use this key to retrieve bundle identifier from dictionary provided by broadcastAnnotatedWithApplicationInfo
 */
API_AVAILABLE(ios(11.2), macos(11.0)) API_UNAVAILABLE(tvos)
extern NSString * const RPApplicationInfoBundleIdentifierKey;

/*!
 @class RPBroadcastSampleHandler
 @abstract Subclass this class to handle CMSampleBuffer objects as they are captured by ReplayKit. To enable this mode of handling, set the RPBroadcastProcessMode in the extension's info.plist to RPBroadcastProcessModeSampleBuffer.
 */
API_AVAILABLE(ios(10.0), tvos(10.0), macos(11.0))
@interface RPBroadcastSampleHandler : RPBroadcastHandler

/*! @abstract Method is called when the RPBroadcastController startBroadcast method is called from the broadcasting application.
    @param setupInfo Dictionary that can be supplied by the UI extension to the sample handler.
 */
- (void)broadcastStartedWithSetupInfo:(nullable NSDictionary <NSString *, NSObject *> *)setupInfo;

/*! @abstract Method is called when the RPBroadcastController pauseBroadcast method is called from the broadcasting application. */
- (void)broadcastPaused;

/*! @abstract Method is called when the RPBroadcastController resumeBroadcast method is called from the broadcasting application. */
- (void)broadcastResumed;

/*! @abstract Method is called when the RPBroadcastController finishBroadcast method is called from the broadcasting application. */
- (void)broadcastFinished;

/*! @abstract Method is called when broadcast is started from Control Center and provides extension information about the first application opened or used during the broadcast.
    @param applicationInfo Dictionary that contains information about the first application opened or used buring the broadcast.
 */
- (void)broadcastAnnotatedWithApplicationInfo:(NSDictionary *)applicationInfo API_AVAILABLE(ios(11.2)) API_UNAVAILABLE(tvos);

/*! @abstract Method is called as video and audio data become available during a broadcast session and is delivered as CMSampleBuffer objects.
    @param sampleBuffer CMSampleBuffer object which contains either video or audio data.
    @param sampleBufferType Determine's the type of the sample buffer defined by the RPSampleBufferType enum.
 */
- (void)processSampleBuffer:(CMSampleBufferRef)sampleBuffer withType:(RPSampleBufferType)sampleBufferType;

/*! @abstract Method that should be called when broadcasting can not proceed due to an error. Calling this method will stop the broadcast and deliver the error back to the broadcasting app through RPBroadcastController's delegate.
    @param error NSError object that will be passed back to the broadcasting app through RPBroadcastControllerDelegate's broadcastController:didFinishWithError: method.
 */
- (void)finishBroadcastWithError:(NSError *)error;

@end
NS_ASSUME_NONNULL_END
