//
//  VNDetectHumanBodyPoseRequest.h
//  Vision
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>
#import <Vision/VNObservation.h>


NS_ASSUME_NONNULL_BEGIN


VN_EXPORT VNRecognizedPointKey const VNBodyLandmarkKeyNose API_DEPRECATED_WITH_REPLACEMENT("VNHumanBodyPoseObservationJointNameNose", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));

VN_EXPORT VNRecognizedPointKey const VNBodyLandmarkKeyLeftEye API_DEPRECATED_WITH_REPLACEMENT("VNHumanBodyPoseObservationJointNameLeftEye", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointKey const VNBodyLandmarkKeyRightEye API_DEPRECATED_WITH_REPLACEMENT("VNHumanBodyPoseObservationJointNameRightEye", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));

VN_EXPORT VNRecognizedPointKey const VNBodyLandmarkKeyLeftEar API_DEPRECATED_WITH_REPLACEMENT("VNHumanBodyPoseObservationJointNameLeftEar", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointKey const VNBodyLandmarkKeyRightEar API_DEPRECATED_WITH_REPLACEMENT("VNHumanBodyPoseObservationJointNameRightEar", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));

VN_EXPORT VNRecognizedPointKey const VNBodyLandmarkKeyLeftShoulder API_DEPRECATED_WITH_REPLACEMENT("VNHumanBodyPoseObservationJointNameLeftShoulder", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointKey const VNBodyLandmarkKeyRightShoulder API_DEPRECATED_WITH_REPLACEMENT("VNHumanBodyPoseObservationJointNameRightShoulder", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointKey const VNBodyLandmarkKeyNeck API_DEPRECATED_WITH_REPLACEMENT("VNHumanBodyPoseObservationJointNameNeck", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));

VN_EXPORT VNRecognizedPointKey const VNBodyLandmarkKeyLeftElbow API_DEPRECATED_WITH_REPLACEMENT("VNHumanBodyPoseObservationJointNameLeftElbow", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointKey const VNBodyLandmarkKeyRightElbow API_DEPRECATED_WITH_REPLACEMENT("VNHumanBodyPoseObservationJointNameRightElbow", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));

VN_EXPORT VNRecognizedPointKey const VNBodyLandmarkKeyLeftWrist API_DEPRECATED_WITH_REPLACEMENT("VNHumanBodyPoseObservationJointNameLeftWrist", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointKey const VNBodyLandmarkKeyRightWrist API_DEPRECATED_WITH_REPLACEMENT("VNHumanBodyPoseObservationJointNameRightWrist", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));

VN_EXPORT VNRecognizedPointKey const VNBodyLandmarkKeyLeftHip API_DEPRECATED_WITH_REPLACEMENT("VNHumanBodyPoseObservationJointNameLeftHip", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointKey const VNBodyLandmarkKeyRightHip API_DEPRECATED_WITH_REPLACEMENT("VNHumanBodyPoseObservationJointNameRightHip", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointKey const VNBodyLandmarkKeyRoot API_DEPRECATED_WITH_REPLACEMENT("VNHumanBodyPoseObservationJointNameRoot", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));

VN_EXPORT VNRecognizedPointKey const VNBodyLandmarkKeyLeftKnee API_DEPRECATED_WITH_REPLACEMENT("VNHumanBodyPoseObservationJointNameLeftKnee", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointKey const VNBodyLandmarkKeyRightKnee API_DEPRECATED_WITH_REPLACEMENT("VNHumanBodyPoseObservationJointNameRightKnee", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));

VN_EXPORT VNRecognizedPointKey const VNBodyLandmarkKeyLeftAnkle API_DEPRECATED_WITH_REPLACEMENT("VNHumanBodyPoseObservationJointNameLeftAnkle", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointKey const VNBodyLandmarkKeyRightAnkle API_DEPRECATED_WITH_REPLACEMENT("VNHumanBodyPoseObservationJointNameRightAnkle", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));


VN_EXPORT VNRecognizedPointGroupKey const VNBodyLandmarkRegionKeyFace API_DEPRECATED_WITH_REPLACEMENT("VNHumanBodyPoseObservationJointsGroupNameFace", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointGroupKey const VNBodyLandmarkRegionKeyTorso API_DEPRECATED_WITH_REPLACEMENT("VNHumanBodyPoseObservationJointsGroupNameTorso", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointGroupKey const VNBodyLandmarkRegionKeyLeftArm API_DEPRECATED_WITH_REPLACEMENT("VNHumanBodyPoseObservationJointsGroupNameLeftArm", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointGroupKey const VNBodyLandmarkRegionKeyRightArm API_DEPRECATED_WITH_REPLACEMENT("VNHumanBodyPoseObservationJointsGroupNameRightArm", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointGroupKey const VNBodyLandmarkRegionKeyLeftLeg API_DEPRECATED_WITH_REPLACEMENT("VNHumanBodyPoseObservationJointsGroupNameLeftLeg", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointGroupKey const VNBodyLandmarkRegionKeyRightLeg API_DEPRECATED_WITH_REPLACEMENT("VNHumanBodyPoseObservationJointsGroupNameRightLeg", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));






typedef VNRecognizedPointKey VNHumanBodyPoseObservationJointName NS_TYPED_ENUM NS_SWIFT_NAME(VNHumanBodyPoseObservation.JointName) API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

VN_EXPORT VNHumanBodyPoseObservationJointName const VNHumanBodyPoseObservationJointNameNose API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

VN_EXPORT VNHumanBodyPoseObservationJointName const VNHumanBodyPoseObservationJointNameLeftEye API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanBodyPoseObservationJointName const VNHumanBodyPoseObservationJointNameRightEye API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

VN_EXPORT VNHumanBodyPoseObservationJointName const VNHumanBodyPoseObservationJointNameLeftEar API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanBodyPoseObservationJointName const VNHumanBodyPoseObservationJointNameRightEar API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

VN_EXPORT VNHumanBodyPoseObservationJointName const VNHumanBodyPoseObservationJointNameLeftShoulder API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanBodyPoseObservationJointName const VNHumanBodyPoseObservationJointNameRightShoulder API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanBodyPoseObservationJointName const VNHumanBodyPoseObservationJointNameNeck API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

VN_EXPORT VNHumanBodyPoseObservationJointName const VNHumanBodyPoseObservationJointNameLeftElbow API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanBodyPoseObservationJointName const VNHumanBodyPoseObservationJointNameRightElbow API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

VN_EXPORT VNHumanBodyPoseObservationJointName const VNHumanBodyPoseObservationJointNameLeftWrist API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanBodyPoseObservationJointName const VNHumanBodyPoseObservationJointNameRightWrist API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

VN_EXPORT VNHumanBodyPoseObservationJointName const VNHumanBodyPoseObservationJointNameLeftHip API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanBodyPoseObservationJointName const VNHumanBodyPoseObservationJointNameRightHip API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanBodyPoseObservationJointName const VNHumanBodyPoseObservationJointNameRoot API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

VN_EXPORT VNHumanBodyPoseObservationJointName const VNHumanBodyPoseObservationJointNameLeftKnee API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanBodyPoseObservationJointName const VNHumanBodyPoseObservationJointNameRightKnee API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

VN_EXPORT VNHumanBodyPoseObservationJointName const VNHumanBodyPoseObservationJointNameLeftAnkle API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanBodyPoseObservationJointName const VNHumanBodyPoseObservationJointNameRightAnkle API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));




typedef VNRecognizedPointGroupKey VNHumanBodyPoseObservationJointsGroupName NS_TYPED_ENUM NS_SWIFT_NAME(VNHumanBodyPoseObservation.JointsGroupName) API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

VN_EXPORT VNHumanBodyPoseObservationJointsGroupName const VNHumanBodyPoseObservationJointsGroupNameFace API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)); // nose, eyes, and ears
VN_EXPORT VNHumanBodyPoseObservationJointsGroupName const VNHumanBodyPoseObservationJointsGroupNameTorso API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)); // shoulders, neck and hips
VN_EXPORT VNHumanBodyPoseObservationJointsGroupName const VNHumanBodyPoseObservationJointsGroupNameLeftArm API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)); // left shoulder, left elbow, and left wrist
VN_EXPORT VNHumanBodyPoseObservationJointsGroupName const VNHumanBodyPoseObservationJointsGroupNameRightArm API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)); // right shoulder, right elbow, and right wrist
VN_EXPORT VNHumanBodyPoseObservationJointsGroupName const VNHumanBodyPoseObservationJointsGroupNameLeftLeg API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)); // left ankle, left knee, and left hip
VN_EXPORT VNHumanBodyPoseObservationJointsGroupName const VNHumanBodyPoseObservationJointsGroupNameRightLeg API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0)); // right ankle, right knee, and right hip
VN_EXPORT VNHumanBodyPoseObservationJointsGroupName const VNHumanBodyPoseObservationJointsGroupNameAll API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));




API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
@interface VNHumanBodyPoseObservation : VNRecognizedPointsObservation

/*!
 @brief All of the joint names available in the observation.
 */
@property (readonly, copy) NSArray<VNHumanBodyPoseObservationJointName>* availableJointNames;



/*!
 @brief All of the joints group names available in the observation.
 */
@property (readonly, copy) NSArray<VNHumanBodyPoseObservationJointsGroupName>* availableJointsGroupNames;


/*!
 @brief Obtain a specific normalized point for a named human body joint.
 
 @param jointName The name of the human body joint.
 @param error The address of a variable that will be populated with the error that describes the failure.  If the caller does not require this information, NULL can be passed.
 @return the recognized point, or nil if the point could not be obtained.
*/
- (nullable VNRecognizedPoint*) recognizedPointForJointName:(VNHumanBodyPoseObservationJointName)jointName error:(NSError**)error NS_SWIFT_NAME(recognizedPoint(_:));

/*!
 @brief Obtains the collection of points associated with a named human body joints group.
 
 @discussion The obtained collection is a dictionary that provides the mapping of human body join names to the recognized point.
 
 @param jointsGroupName The name of the human body joints group.
 @param error The address of a variable that will be populated with the error that describes the failure.  If the caller does not require this information, NULL can be passed.
 @return a dictionary of recognized points in the group, or nil if an error was encountered.
*/
- (nullable NSDictionary<VNHumanBodyPoseObservationJointName, VNRecognizedPoint*>*) recognizedPointsForJointsGroupName:(VNHumanBodyPoseObservationJointsGroupName)jointsGroupName error:(NSError**)error NS_SWIFT_NAME(recognizedPoints(_:));

@end






/*!
 @brief Detects specific landmark points on human bodies.
 @discussion This request will produce a collection of VNHumanBodyPoseObservation objects which describe the pose of each detected human body.
*/
API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
@interface VNDetectHumanBodyPoseRequest : VNImageBasedRequest

/*!
 @brief Obtain the collection of human body joint names that are supported by a given request revision.
 @param revision The revision of VNDetectHumanBodyPoseRequest being queried.
 @param error The address of a variable that will be populated with an error upon failure.  If the caller does not need this information, NULL can be passed.
 @return An array of VNHumanBodyPoseObservationJointName symbols that are supported by the request revision, or nil if a failure occurs.
*/
+ (nullable NSArray<VNHumanBodyPoseObservationJointName>*) supportedJointNamesForRevision:(NSUInteger)revision error:(NSError **)error;


/*!
 @brief Obtain the collection of human body joints group names that are supported by a given request revision.
 @param revision The revision of VNDetectHumanBodyPoseRequest being queried.
 @param error The address of a variable that will be populated with an error upon failure.  If the caller does not need this information, NULL can be passed.
 @return An array of VNHumanBodyPoseObservationJointsGroupName symbols that are supported by the request revision, or nil if a failure occurs.
*/
+ (nullable NSArray<VNHumanBodyPoseObservationJointsGroupName>*) supportedJointsGroupNamesForRevision:(NSUInteger)revision error:(NSError **)error;


/*!
 @discussion VNHumanBodyPoseObservation results.
*/
@property (readonly, copy, nullable) NSArray<VNHumanBodyPoseObservation*>* results;

@end


API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
static const NSUInteger VNDetectHumanBodyPoseRequestRevision1 = 1;




NS_ASSUME_NONNULL_END
