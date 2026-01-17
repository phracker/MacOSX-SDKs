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

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@protocol HMCameraStreamControlDelegate;
@class HMCameraStream;

/*!
 * @abstract This class can be used to control the stream from a camera.
 */
HM_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0), macCatalyst(14.0))
API_UNAVAILABLE(macos)
@interface HMCameraStreamControl : HMCameraControl

/*!
 * @brief Delegate that receives updates on the camera stream changes.
 */
@property (nonatomic, weak) id<HMCameraStreamControlDelegate> delegate;

/*!
 * @brief Represents the current streaming state.
 */
@property (nonatomic, readonly, assign) HMCameraStreamState streamState;

/*!
 * @brief Represents the current camera stream.
 */
@property (nullable, nonatomic, readonly, strong) HMCameraStream *cameraStream;

/*!
 * @brief Starts the camera stream. 'currentCameraStream' will be updated upon 
 *        successfully starting the stream.
 */
- (void)startStream;

/*!
 * @brief Stops the camera stream.
 * */
- (void)stopStream;

- (instancetype)init API_DEPRECATED("HMCameraStreamControl objects are created by their parent container objects. Directly creating them is not supported.", ios(10.0, 10.0), watchos(3.0, 3.0), tvos(10.0, 10.0), macCatalyst(14.0, 14.0));

@end

/*!
 * @brief This delegate receives updates on the camera stream.
 */
API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0), macCatalyst(14.0))
API_UNAVAILABLE(macos)
@protocol HMCameraStreamControlDelegate<NSObject>

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

NS_HEADER_AUDIT_END(nullability, sendability)
