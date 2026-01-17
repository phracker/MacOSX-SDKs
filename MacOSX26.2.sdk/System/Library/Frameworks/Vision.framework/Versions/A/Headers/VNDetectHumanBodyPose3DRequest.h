//
//  VNDetectHumanBodyPose3DRequest.h
//  Vision
//
//	Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>
#import <Vision/VNObservation.h>
#import <Vision/VNTypes.h>
#import <Vision/VNStatefulRequest.h>



NS_ASSUME_NONNULL_BEGIN


/*!
 @brief A request that detects specific landmark points on human bodies in 3D space relative to the camera.
        When possible,`AVDepthData` depth information is used to produce more accurate results, but the request does not require it to run.
 @discussion This request generates a collection of VNHumanBodyPose3DObservation objects which describe the position of each detected body
*/
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0))
@interface VNDetectHumanBodyPose3DRequest : VNStatefulRequest


/*!
    @brief Creates a new VNDetectHumanBodyPose3DRequest with no completion handler.
*/
- (instancetype) init;


/*!
    @brief Creates a new VNDetectHumanBodyPose3DRequest with completion handler.
*/
- (instancetype) initWithCompletionHandler:(nullable VNRequestCompletionHandler)completionHandler;


/*!
 @brief Obtain the collection of human body joint names that are supported by a given request revision.
 @param error The address of a variable that will be populated with an error upon failure.  If the caller does not need this information, NULL can be passed.
 @return An array of VNHumanBodyPose3DObservationJointName symbols that are supported by the request revision, or nil if a failure occurs.
*/
- (nullable NSArray<VNHumanBodyPose3DObservationJointName>*) supportedJointNamesAndReturnError:(NSError **)error;


/*!
 @brief Obtain the collection of human body joints group names that are supported by a request object configured with a request revision.
 @param error The address of a variable that will be populated with an error upon failure.  If the caller does not need this information, NULL can be passed.
 @return An array of VNHumanBody3DPoseObservationJointsGroupName symbols that are supported by the request, or nil if a failure occurs.
*/
- (nullable NSArray<VNHumanBodyPose3DObservationJointsGroupName>*) supportedJointsGroupNamesAndReturnError:(NSError **)error;


/*!
	@discussion VNHumanBodyPose3DObservation results.
*/
@property (readonly, copy, nullable) NSArray<VNHumanBodyPose3DObservation*>* results;

@end


API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0))
static const NSUInteger VNDetectHumanBodyPose3DRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
