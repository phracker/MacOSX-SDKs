//
//  VNHumanBodyRecognizedPoint3D.h
//  Vision
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Vision/VNRecognizedPoint3D.h>
#import <Vision/VNTypes.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0))
/*!
 @brief
 */
@interface VNHumanBodyRecognizedPoint3D : VNRecognizedPoint3D

@property (readonly) simd_float4x4 localPosition;
@property (readonly) VNHumanBodyPose3DObservationJointName parentJoint;

+ (instancetype) new NS_UNAVAILABLE;
- (instancetype) init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
