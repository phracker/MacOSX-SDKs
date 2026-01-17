//
//  HMCameraStream.h
//  HomeKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>
#import <HomeKit/HMCameraSource.h>
#import <HomeKit/HMCameraDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @abstract Represents a camera stream.
 */
HM_EXTERN API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMCameraStream : HMCameraSource

/*!
 * @brief Represents the audio setting for the current stream.
 */
@property (assign, nonatomic, readonly) HMCameraAudioStreamSetting audioStreamSetting API_AVAILABLE(tvos(14.5));

/*!
 * @brief Sets the audio stream setting.
 *
 * @param audioStreamSetting New audio stream setting.
 *
 */
- (void)setAudioStreamSetting:(HMCameraAudioStreamSetting)audioStreamSetting  API_DEPRECATED_WITH_REPLACEMENT("updateAudioStreamSetting:completionHandler:", ios(10.0, 10.0), watchos(3.0, 3.0)) API_UNAVAILABLE(tvos);

/*!
 * @brief Updates the settings of the audio stream.
 *
 * @param audioStreamSetting New audio stream setting. Bidirectional audio is not allowed on TVOS.
 *
 * @param completion Block that is invoked once the request is processed.
 *                   The NSError provides more information on the status of the request, error
 *                   will be nil on success.
 */
- (void)updateAudioStreamSetting:(HMCameraAudioStreamSetting)audioStreamSetting completionHandler:(void (^)(NSError * __nullable error))completion API_AVAILABLE(tvos(14.5));

@end

NS_ASSUME_NONNULL_END
