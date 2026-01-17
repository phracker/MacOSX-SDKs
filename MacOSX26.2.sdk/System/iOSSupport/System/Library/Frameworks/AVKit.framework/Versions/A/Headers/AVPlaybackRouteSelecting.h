/*
 File:  AVPlaybackRouteSelecting.h
 
 Framework:  AVKit
 
 Copyright © 2019 Apple Inc. All rights reserved.
 
 */

#import <AVFoundation/AVFoundation.h>

@class AVAudioSession;

NS_ASSUME_NONNULL_BEGIN

/*!
 	@constant	AVAudioSessionRouteSelectionNone
 				Indicates no route was selected.
 	@constant	AVAudioSessionRouteSelectionLocal
 				Indicates that the local device was selected.
 	@constant	AVAudioSessionRouteSelectionExternal
 				Indicates that an external device was selected.
 */
typedef NS_ENUM(NSInteger, AVAudioSessionRouteSelection) {
	AVAudioSessionRouteSelectionNone = 0,
	AVAudioSessionRouteSelectionLocal = 1,
	AVAudioSessionRouteSelectionExternal = 2
} NS_SWIFT_NAME(AVAudioSession.RouteSelection) API_AVAILABLE(ios(13.0), visionos(1.0)) API_UNAVAILABLE(macos, tvos, watchos);


API_AVAILABLE(ios(13.0), visionos(1.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface AVAudioSession (AVPlaybackRouteSelecting)

/*!
 	@method		prepareRouteSelectionForPlaybackWithCompletionHandler:
 	@param		completionHandler
 				Once any potential routing is complete, the completion handler is called with the selected route type and with a BOOL indicating whether playback should begin or not.
 	@abstract	A call to this method is an indication that playback is about to start. This gives the receiver an opportunity to prompt the user to pick an output destination if necessary.
 				The receiver will only prompt if the audio session has been configured with a long-form video route sharing policy. 
 	@discussion	Presenting playback UI (e.g. AVPlayerViewController) and commencing playback should be performed in the completionHandler.
 */
- (void)prepareRouteSelectionForPlaybackWithCompletionHandler:(void (^)(BOOL shouldStartPlayback, AVAudioSessionRouteSelection routeSelection))completionHandler;

@end

NS_ASSUME_NONNULL_END
