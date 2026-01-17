//
//  HMCameraSnapshotControl.h
//  HomeKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMCameraControl.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HMCameraSnapshot;
@protocol HMCameraSnapshotControlDelegate;

/*!
 * @abstract This class can be used to take an image snapshot from a camera.
 */
HM_EXTERN API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMCameraSnapshotControl : HMCameraControl

/*!
 * @brief Delegate that receives updates on the camera snapshot changes.
 */
@property(weak, nonatomic) id<HMCameraSnapshotControlDelegate> delegate;

/*!
 * @brief Represents the most recent snapshot taken from the camera.
 */
@property(readonly, strong, nonatomic, nullable) HMCameraSnapshot *mostRecentSnapshot;

/*!
 * @brief Takes an image snapshot.
 */
- (void)takeSnapshot;

@end


/*!
 * @brief This delegate receives updates on the camera snapshot.
 */
API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@protocol HMCameraSnapshotControlDelegate <NSObject>

@optional

/*!
 * @brief Informs the delegate that the snapshot was taken.
 *
 * @param cameraSnapshotControl Sender of this message.
 *
 * @param snapshot Snapshot will be valid if snapshot was successfully taken.
 *
 * @param error Error will be populated if the snapshot could not be taken.
 */
- (void)cameraSnapshotControl:(HMCameraSnapshotControl *)cameraSnapshotControl
              didTakeSnapshot:(HMCameraSnapshot *__nullable)snapshot
                        error:(NSError *__nullable)error;

/*!
 * @brief Informs the delegate that the mostRecentSnapshot was updated.
 *
 * @param cameraSnapshotControl Sender of this message.
 */
- (void)cameraSnapshotControlDidUpdateMostRecentSnapshot:(HMCameraSnapshotControl *)cameraSnapshotControl;

@end

NS_ASSUME_NONNULL_END

