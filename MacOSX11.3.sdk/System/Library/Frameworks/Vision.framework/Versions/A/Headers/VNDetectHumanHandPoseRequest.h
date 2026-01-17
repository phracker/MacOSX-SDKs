//
//  VNDetectHumanHandPoseRequest.h
//  Vision
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//


#import <Vision/VNRequest.h>
#import <Vision/VNObservation.h>



NS_ASSUME_NONNULL_BEGIN


/*
 *	Each finger has three phalanges, separated by two interphalangeal joints.
 *
 *	The Distal Interphalangeal (DIP) joint is the first knuckle from the top of the finger. It connects the two bones at the tip of the finger.
 *
 *	The Proximal Interphalangeal (PIP) joint is the first joint of the finger and is located between the first two bones of the finger
 *
 *	The Metacarpophalangeal (MCP) joint is where the hand bone called the metacarpal meets the finger bones called the phalanges.
 *
 *	The Carpometacarpal (CMC) joint forms where the ends of the metacarpal bone at the base of the thumb and the trapezium bone in the wrist meet.
 *
 *
 *                                      Middle
 *                                       _____
 *                               Index  |     |  Ring
 *                               _____  |     |  _____
 *                              |     | |     | |     |  Little
 *                              |     | |     | |     |  _____
 *                              |     | |_____| |     | |     |
 *                              |_____| |     | |_____| |     |
 *              Thumb           |     | |     | |     | |_____|  <-- DIP
 *              ______          |     | |     | |     | |     |
 *             |      \         |     | |     | |     | |     |
 *              \      \        |_____| |_____| |_____| |     |
 *               \      \       |     | |     | |     | |_____|  <-- PIP
 *        IP -->  \______\      |     | |     | |     | |     |
 *                 \      \     |     | |     | |     | |     |
 *                  \      \    |_____| |_____| |_____| |_____|  <-- MCP
 *                   \      \  /                               \
 *           MCP -->  \______\ |                               |
 *                     \      \|                               |
 *                      \      /                               |
 *                       \    /  <-- CMC                       |
 *                        \  /                                 |
 *                         \/                                  |
 *                          |                                  |
 *                           \                                 /
 *                            \ . . . . . . . . . . . . . . . /
 *                                          Wrist
 */


VN_EXPORT VNRecognizedPointKey const VNHandLandmarkKeyWrist API_DEPRECATED_WITH_REPLACEMENT("VNHumanHandPoseObservationJointNameWrist", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));

VN_EXPORT VNRecognizedPointKey const VNHandLandmarkKeyThumbCMC API_DEPRECATED_WITH_REPLACEMENT("VNHumanHandPoseObservationJointNameThumbCMC", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointKey const VNHandLandmarkKeyThumbMP API_DEPRECATED_WITH_REPLACEMENT("VNHumanHandPoseObservationJointNameThumbMP", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointKey const VNHandLandmarkKeyThumbIP API_DEPRECATED_WITH_REPLACEMENT("VNHumanHandPoseObservationJointNameThumbIP", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointKey const VNHandLandmarkKeyThumbTIP API_DEPRECATED_WITH_REPLACEMENT("VNHumanHandPoseObservationJointNameThumbTip", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));

VN_EXPORT VNRecognizedPointKey const VNHandLandmarkKeyIndexMCP API_DEPRECATED_WITH_REPLACEMENT("VNHumanHandPoseObservationJointNameIndexMCP", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointKey const VNHandLandmarkKeyIndexPIP API_DEPRECATED_WITH_REPLACEMENT("VNHumanHandPoseObservationJointNameIndexPIP", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointKey const VNHandLandmarkKeyIndexDIP API_DEPRECATED_WITH_REPLACEMENT("VNHumanHandPoseObservationJointNameIndexDIP", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointKey const VNHandLandmarkKeyIndexTIP API_DEPRECATED_WITH_REPLACEMENT("VNHumanHandPoseObservationJointNameIndexTip", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));

VN_EXPORT VNRecognizedPointKey const VNHandLandmarkKeyMiddleMCP API_DEPRECATED_WITH_REPLACEMENT("VNHumanHandPoseObservationJointNameMiddleMCP", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointKey const VNHandLandmarkKeyMiddlePIP API_DEPRECATED_WITH_REPLACEMENT("VNHumanHandPoseObservationJointNameMiddlePIP", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointKey const VNHandLandmarkKeyMiddleDIP API_DEPRECATED_WITH_REPLACEMENT("VNHumanHandPoseObservationJointNameMiddleDIP", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointKey const VNHandLandmarkKeyMiddleTIP API_DEPRECATED_WITH_REPLACEMENT("VNHumanHandPoseObservationJointNameMiddleTip", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));

VN_EXPORT VNRecognizedPointKey const VNHandLandmarkKeyRingMCP API_DEPRECATED_WITH_REPLACEMENT("VNHumanHandPoseObservationJointNameRingMCP", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointKey const VNHandLandmarkKeyRingPIP API_DEPRECATED_WITH_REPLACEMENT("VNHumanHandPoseObservationJointNameRingPIP", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointKey const VNHandLandmarkKeyRingDIP API_DEPRECATED_WITH_REPLACEMENT("VNHumanHandPoseObservationJointNameRingDIP", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointKey const VNHandLandmarkKeyRingTIP API_DEPRECATED_WITH_REPLACEMENT("VNHumanHandPoseObservationJointNameRingTip", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));

VN_EXPORT VNRecognizedPointKey const VNHandLandmarkKeyLittleMCP API_DEPRECATED_WITH_REPLACEMENT("VNHumanHandPoseObservationJointNameLittleMCP", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointKey const VNHandLandmarkKeyLittlePIP API_DEPRECATED_WITH_REPLACEMENT("VNHumanHandPoseObservationJointNameLittlePIP", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointKey const VNHandLandmarkKeyLittleDIP API_DEPRECATED_WITH_REPLACEMENT("VNHumanHandPoseObservationJointNameLittleDIP", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointKey const VNHandLandmarkKeyLittleTIP API_DEPRECATED_WITH_REPLACEMENT("VNHumanHandPoseObservationJointNameLittleTip", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));


VN_EXPORT VNRecognizedPointGroupKey const VNHandLandmarkRegionKeyThumb API_DEPRECATED_WITH_REPLACEMENT("VNHumanHandPoseObservationJointsGroupNameThumb", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointGroupKey const VNHandLandmarkRegionKeyIndexFinger API_DEPRECATED_WITH_REPLACEMENT("VNHumanHandPoseObservationJointsGroupNameIndexFinger", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointGroupKey const VNHandLandmarkRegionKeyMiddleFinger API_DEPRECATED_WITH_REPLACEMENT("VNHumanHandPoseObservationJointsGroupNameMiddleFinger", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointGroupKey const VNHandLandmarkRegionKeyRingFinger API_DEPRECATED_WITH_REPLACEMENT("VNHumanHandPoseObservationJointsGroupNameRingFinger", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNRecognizedPointGroupKey const VNHandLandmarkRegionKeyLittleFinger API_DEPRECATED_WITH_REPLACEMENT("VNHumanHandPoseObservationJointsGroupNameLittleFinger", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));





typedef VNRecognizedPointKey VNHumanHandPoseObservationJointName NS_TYPED_ENUM NS_SWIFT_NAME(VNHumanHandPoseObservation.JointName) API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

VN_EXPORT VNHumanHandPoseObservationJointName const VNHumanHandPoseObservationJointNameWrist API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

VN_EXPORT VNHumanHandPoseObservationJointName const VNHumanHandPoseObservationJointNameThumbCMC API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanHandPoseObservationJointName const VNHumanHandPoseObservationJointNameThumbMP API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanHandPoseObservationJointName const VNHumanHandPoseObservationJointNameThumbIP API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanHandPoseObservationJointName const VNHumanHandPoseObservationJointNameThumbTip API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

VN_EXPORT VNHumanHandPoseObservationJointName const VNHumanHandPoseObservationJointNameIndexMCP API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanHandPoseObservationJointName const VNHumanHandPoseObservationJointNameIndexPIP API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanHandPoseObservationJointName const VNHumanHandPoseObservationJointNameIndexDIP API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanHandPoseObservationJointName const VNHumanHandPoseObservationJointNameIndexTip API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

VN_EXPORT VNHumanHandPoseObservationJointName const VNHumanHandPoseObservationJointNameMiddleMCP API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanHandPoseObservationJointName const VNHumanHandPoseObservationJointNameMiddlePIP API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanHandPoseObservationJointName const VNHumanHandPoseObservationJointNameMiddleDIP API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanHandPoseObservationJointName const VNHumanHandPoseObservationJointNameMiddleTip API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

VN_EXPORT VNHumanHandPoseObservationJointName const VNHumanHandPoseObservationJointNameRingMCP API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanHandPoseObservationJointName const VNHumanHandPoseObservationJointNameRingPIP API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanHandPoseObservationJointName const VNHumanHandPoseObservationJointNameRingDIP API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanHandPoseObservationJointName const VNHumanHandPoseObservationJointNameRingTip API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

VN_EXPORT VNHumanHandPoseObservationJointName const VNHumanHandPoseObservationJointNameLittleMCP API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanHandPoseObservationJointName const VNHumanHandPoseObservationJointNameLittlePIP API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanHandPoseObservationJointName const VNHumanHandPoseObservationJointNameLittleDIP API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanHandPoseObservationJointName const VNHumanHandPoseObservationJointNameLittleTip API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));



typedef VNRecognizedPointGroupKey VNHumanHandPoseObservationJointsGroupName NS_TYPED_ENUM NS_SWIFT_NAME(VNHumanHandPoseObservation.JointsGroupName) API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));

VN_EXPORT VNHumanHandPoseObservationJointsGroupName const VNHumanHandPoseObservationJointsGroupNameThumb API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanHandPoseObservationJointsGroupName const VNHumanHandPoseObservationJointsGroupNameIndexFinger API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanHandPoseObservationJointsGroupName const VNHumanHandPoseObservationJointsGroupNameMiddleFinger API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanHandPoseObservationJointsGroupName const VNHumanHandPoseObservationJointsGroupNameRingFinger API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanHandPoseObservationJointsGroupName const VNHumanHandPoseObservationJointsGroupNameLittleFinger API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));
VN_EXPORT VNHumanHandPoseObservationJointsGroupName const VNHumanHandPoseObservationJointsGroupNameAll API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0));



API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
@interface VNHumanHandPoseObservation : VNRecognizedPointsObservation

/*!
 @brief All of the joint names available in the observation.
 */
@property (readonly, copy) NSArray<VNHumanHandPoseObservationJointName>* availableJointNames;


/*!
 @brief All of the joints group names available in the observation.
 */
@property (readonly, copy) NSArray<VNHumanHandPoseObservationJointsGroupName>* availableJointsGroupNames;


/*!
 @brief Obtain a specific normalized point for a named human hand joint.
 
 @param jointName The name of the human hand joint.
 @param error The address of a variable that will be populated with the error that describes the failure.  If the caller does not require this information, NULL can be passed.
 @return the recognized point, or nil if the point could not be obtained.
*/
- (nullable VNRecognizedPoint*) recognizedPointForJointName:(VNHumanHandPoseObservationJointName)jointName error:(NSError**)error NS_SWIFT_NAME(recognizedPoint(_:));

/*!
 @brief Obtains the collection of points associated with a named human hand joints group.
 
 @discussion The obtained collection is a dictionary that provides the mapping of human hand join names to the recognized point.
 
 @param jointsGroupName The name of the human hand joints group.
 @param error The address of a variable that will be populated with the error that describes the failure.  If the caller does not require this information, NULL can be passed.
 @return a dictionary of recognized points in the group, or nil if an error was encountered.
*/
- (nullable NSDictionary<VNHumanHandPoseObservationJointName, VNRecognizedPoint*>*) recognizedPointsForJointsGroupName:(VNHumanHandPoseObservationJointsGroupName)jointsGroupName error:(NSError**)error NS_SWIFT_NAME(recognizedPoints(_:));

@end




/*!
 @brief Detects specific landmark points on human hands.
 @discussion This request will produce a collection of VNRecognizedPointsObservation objects which describe the pose of each detected human hand.
 */
API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
@interface VNDetectHumanHandPoseRequest : VNImageBasedRequest

+ (nullable NSArray<VNRecognizedPointKey>*) supportedRecognizedPointKeysForRevision:(NSUInteger)revision error:(NSError **)error
	API_DEPRECATED_WITH_REPLACEMENT("Use +supportedJointNamesForRevision:error:] instead", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));

+ (nullable NSArray<VNRecognizedPointGroupKey>*) supportedRecognizedPointGroupKeysForRevision:(NSUInteger)revision error:(NSError **)error
	API_DEPRECATED_WITH_REPLACEMENT("Use +supportedJointsGroupNamesForRevision:error:] instead", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));


+ (nullable NSArray<VNRecognizedPointKey>*) supportedIdentifiedPointKeysForRevision:(NSUInteger)revision error:(NSError **)error
	API_DEPRECATED_WITH_REPLACEMENT("Use +supportedJointNamesForRevision:error:] instead", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));

+ (nullable NSArray<VNRecognizedPointGroupKey>*) supportedIdentifiedPointGroupKeysForRevision:(NSUInteger)revision error:(NSError **)error
	API_DEPRECATED_WITH_REPLACEMENT("Use +supportedJointsGroupNamesForRevision:error:] instead", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));





/*!
 @brief Obtain the collection of human hand joint names that are supported by a given request revision.
 @param revision The revision of VNDetectHumanHandPoseRequest being queried.
 @param error The address of a variable that will be populated with an error upon failure.  If the caller does not need this information, NULL can be passed.
 @return An array of VNHumanHandPoseObservationJointName symbols that are supported by the request revision, or nil if a failure occurs.
*/
+ (nullable NSArray<VNHumanHandPoseObservationJointName>*) supportedJointNamesForRevision:(NSUInteger)revision error:(NSError **)error;


/*!
 @brief Obtain the collection of human hand joints group names that are supported by a given request revision.
 @param revision The revision of VNDetectHumanHandPoseRequest being queried.
 @param error The address of a variable that will be populated with an error upon failure.  If the caller does not need this information, NULL can be passed.
 @return An array of VNHumanHandPoseObservationJointsGroupName symbols that are supported by the request revision, or nil if a failure occurs.
*/
+ (nullable NSArray<VNHumanHandPoseObservationJointsGroupName>*) supportedJointsGroupNamesForRevision:(NSUInteger)revision error:(NSError **)error;

/*!
	@brief Defines an upper bounds to the maximum number of hands that will be processed for key points in an image.
	@discussion The complexity in key points determination is scalable by the number of hands to be processed.  All hands detected in an image will be ordered by relative size, with only the N largest ones having key points determined.  The default value for this property is 2.
*/
@property (readwrite, assign) NSUInteger maximumHandCount;

/*!
	@discussion VNHumanHandPoseObservation results.
*/
@property (readonly, copy, nullable) NSArray<VNHumanHandPoseObservation*>* results;

@end


API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
static const NSUInteger VNDetectHumanHandPoseRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
