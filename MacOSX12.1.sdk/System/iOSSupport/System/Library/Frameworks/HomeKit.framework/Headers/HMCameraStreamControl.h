//
//  HMCameraStreamControl.h
//  HomeKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <HomeKit/HMCameraControl.h>
#import <HomeKit/HMCameraDefines.h>
#import <HomeKit/HMDefines.h>

#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

@protocol HMCameraStreamControlDelegate;
@class HMCameraStream;

/*!
 * @abstract This class can be used to control the stream from a camera.
 */
HM_EXTERN API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMCameraStreamControl : HMCameraControl

/*!
 * @brief Delegate that receives updates on the camera stream changes.
 */
@property(weak, nonatomic) id<HMCameraStreamControlDelegate> delegate;

/*!
 * @brief Represents the current streaming state.
 */
@property(readonly, assign, nonatomic) HMCameraStreamState streamState;

/*!
 * @brief Represents the current camera stream.
 */
@property(readonly, strong, nonatomic, nullable) HMCameraStream *cameraStream;

/*!
 * @brief Starts the camera stream. 'currentCameraStream' will be updated upon 
 *        successfully starting the stream.
 */
- (void)startStream;

/*!
 * @brief Stops the camera stream.
 * */
- (void)stopStream;

@end

/*!
 * @brief This delegate receives updates on the camera stream.
 */
API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@protocol HMCameraStreamControlDelegate <NSObject>

@optional

/*!
 * @brief Informs the delegate that the stream has started.
 *
 * @param cameraStreamControl Sender of this message.
 */
- (void)cameraStreamControlDidStartStream:(HMCameraStreamControl *)cameraStreamControl;

/*!
 * @brief Informs the delegate that the stream has stopped.
 *
 * @param cameraStreamControl Sender of this message.
 *
 * @param error When stream stops because of an error, 'error' will be populated.
 */
- (void)cameraStreamControl:(HMCameraStreamControl *)cameraStreamControl didStopStreamWithError:(NSError *__nullable)error;

@end

NS_ASSUME_NONNULL_END

