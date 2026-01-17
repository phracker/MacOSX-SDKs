#if (defined(USE_AVFAUDIO_PUBLIC_HEADERS) && USE_AVFAUDIO_PUBLIC_HEADERS) || !__has_include(<AudioSession/AVAudioRoutingArbiter.h>)
/*!
    @file       AVAudioRoutingArbiter.h
    @framework  AudioSession.framework
    @copyright  (c) 2020 by Apple Inc. All rights reserved.
    @abstract   API's to allow macOS apps to participate in audio routing arbitration.

    @discussion
        Audio routing arbitration is a feature of Apple operating systems for automatically connecting wireless headphones
        to the best audio source device in a multi-product environment. The supported Apple products are iOS devices,
        iPadOS devices, watchOS devices, and Mac computers. The best audio source is the device from which the user is
        most likely to want  audio playing. The operating system tries to determine that device intelligently. For example, if a
        user was playing a movie with their iPad, then locked the iPad, and started using their iPhone to play music, the iPad
        would stop being the source audio device and the iPhone would become the source audio. This feature is limited
        to select Apple and Beats wireless headsets.

        The intention of the API is to give a hint to the operating system that the app is about to start audio and
        to provide context about what type of audio is to be used. To be a participant of the routing arbitration the app has
        to begin the arbitration. Once arbitration completes, the application is free to start running audio I/O.  The result of
        arbitration may change the system default input and/or output audio devices, so the use of this API will affect any applications
        that are impacted when system default devices change. When the app is no longer interested in using audio I/O it should
        leave audio routing arbitration.

        Applications that use the AVAudioRoutingArbiter API are encouraged to also use MPRemoteCommandCenter and
        MPNowPlayingInfoCenter classes provided by Media Player framework. The use of those classes provides the operating system
        additional context about the content being played and allow the application to respond to remote command events.
*/
#ifndef AudioSession_AVAudioRoutingArbiter_h
#define AudioSession_AVAudioRoutingArbiter_h

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
    @typedef    AVAudioRoutingArbitrationCategory
    @abstract   The category describes the general type of audio that the app plans to use.
    @discussion
        Provides context to the operating system about the type of audio an application intends to use. The system uses this information
        when arbitrating between Apple products that want to take ownership of Bluetooth audio routes.
    @constant   AVAudioRoutingArbitrationCategoryPlayback
        Used for Audio playback.
    @constant   AVAudioRoutingArbitrationCategoryPlayAndRecord
        Used for recording and playing back audio.
    @constant   AVAudioRoutingArbitrationCategoryPlayAndRecordVoice
        Appropriate for Voice over IP(VoIP) applications.
*/
API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios, watchos, tvos, visionos)
typedef NS_ENUM(NSInteger, AVAudioRoutingArbitrationCategory) {
    AVAudioRoutingArbitrationCategoryPlayback           = 0,
    AVAudioRoutingArbitrationCategoryPlayAndRecord      = 1,
    AVAudioRoutingArbitrationCategoryPlayAndRecordVoice = 2,
} NS_SWIFT_NAME(AVAudioRoutingArbiter.Category);

/*!
    @class      AVAudioRoutingArbiter
    @brief      The interface to participate in audio routing arbitration.
*/
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios, watchos, tvos, visionos)
@interface AVAudioRoutingArbiter : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @property sharedRoutingArbiter
    @abstract Returns the singleton AVAudioRoutingArbiter instance.
*/
@property (class, readonly, nonatomic) AVAudioRoutingArbiter *sharedRoutingArbiter;

/*!
    @method        beginArbitrationWithCategory:completionHandler:
    @abstract      Begin routing arbitration to take ownership of nearby Bluetooth audio routes.
    @discussion
       When an app wants to participate in automatic audio arbitration for the wireless headphones route, it has to begin arbitration
       specifying its arbitration session category. It provides the operating system time to arbitrate with other nearby Apple
       devices to obtain ownership of supported Bluetooth audio devices. Then upon completion of arbitration, the operating system
       will automatically determine  whether to route audio to the nearby Bluetooth device. Once arbitration completes, the application
       is free to start running audio I/O. I/O will be started upon the app request even if the -beginArbitrationWithCategory:completionHandler: fails.
       This method should also be used whenever restarting audio I/O in order to allow the system to arbitrate for ownership of a Bluetooth
       device that may have been taken by another nearby Apple device during the time that I/O was stopped.
    @param         category
       The category describes the general type of audio that the app plans to use.
    @param         handler
        A client-supplied block called asynchronously when audio routing arbitration is completed.
        This completion handler takes the following parameters:
        defaultDeviceChanged
            Indicating that the system default audio device has been changed as a result of the arbitration operation.
        error
            An error object that indicates why the request failed, or nil if the request was successful.
*/
- (void)beginArbitrationWithCategory:(AVAudioRoutingArbitrationCategory)category completionHandler:(void(^)(BOOL defaultDeviceChanged, NSError * _Nullable error))handler
NS_SWIFT_NAME(begin(category:completionHandler:));

/*!
    @method   leaveArbitration
    @abstract   Stop participating in audio routing arbitration.
    @discussion
        When an application has stopped using audio for the foreseeable future, it should notify the system. For example,
        in Voice over IP (VoIP)  use cases, the application should call -leaveArbitration when the VoIP call has ended.
        This allows the system to make a better decision when other participating Apple devices would like to take ownership
        of a nearby Bluetooth device. Applications should not call this API in cases where audio is only momentarily paused.
*/
- (void)leaveArbitration NS_SWIFT_NAME(leave());

@end

NS_ASSUME_NONNULL_END

#endif /* AudioSession_AVAudioRoutingArbiter_h */
#else
#include <AudioSession/AVAudioRoutingArbiter.h>
#endif
