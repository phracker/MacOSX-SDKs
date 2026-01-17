//
//  HMCameraDefines.h
//  HomeKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

/*!
 * @abstract This enumeration describes the different states of a camera stream.
 */
API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
typedef NS_ENUM(NSUInteger, HMCameraStreamState)
{
    /*!
     * Start stream request is in progress.
     */
    HMCameraStreamStateStarting = 1,

    /*!
     * Streaming is in progress.
     */
    HMCameraStreamStateStreaming = 2,

    /*!
     * Stop stream request is in progress.
     */
    HMCameraStreamStateStopping = 3,

    /*!
     * No streaming is in progress.
     */
    HMCameraStreamStateNotStreaming = 4
};

/*!
 * @abstract This enumeration describes the setting for audio on the recipient of the camera stream.
 */
API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
typedef NS_ENUM(NSUInteger, HMCameraAudioStreamSetting)
{
    /*!
     * Muted for incoming and outgoing audio.
     */
    HMCameraAudioStreamSettingMuted = 1,

    /*!
     * Only incoming audio is allowed.
     */
    HMCameraAudioStreamSettingIncomingAudioAllowed = 2,

    /*!
     * Bidirectional audio is allowed.
     */
    HMCameraAudioStreamSettingBidirectionalAudioAllowed = 3,
};


