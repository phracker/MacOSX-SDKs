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

/*!
	@brief The chirality of the hand.
*/
@property (readonly) VNChirality chirality API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));

@end



/*!
 @brief Detects specific landmark points on human hands.
 @discussion This request will produce a collection of VNRecognizedPointsObservation objects which describe the pose of each detected human hand.
 */
API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
@interface VNDetectHumanHandPoseRequest : VNImageBasedRequest

/*!
 @brief Obtain the collection of human hand joint names that are supported by a given request revision.
 @param revision The revision of VNDetectHumanHandPoseRequest being queried.
 @param error The address of a variable that will be populated with an error upon failure.  If the caller does not need this information, NULL can be passed.
 @return An array of VNHumanHandPoseObservationJointName symbols that are supported by the request revision, or nil if a failure occurs.
*/
+ (nullable NSArray<VNHumanHandPoseObservationJointName>*) supportedJointNamesForRevision:(NSUInteger)revision error:(NSError **)error API_DEPRECATED_WITH_REPLACEMENT("supportedJointNamesAndReturnError", macos(11.0, 14.0), ios(14.0, 17.0), tvos(14.0, 17.0));

/*!
 @brief Obtain the collection of human hand joint names that are supported by a given request object configured with a specific revision.
 @param error The address of a variable that will be populated with an error upon failure.  If the caller does not need this information, NULL can be passed.
 @return An array of VNHumanHandPoseObservationJointName symbols that are supported by the request revision, or nil if a failure occurs.
*/
- (nullable NSArray<VNHumanHandPoseObservationJointName>*) supportedJointNamesAndReturnError:(NSError **)error API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));

/*!
 @brief Obtain the collection of human hand joints group names that are supported by a given request revision.
 @param revision The revision of VNDetectHumanHandPoseRequest being queried.
 @param error The address of a variable that will be populated with an error upon failure.  If the caller does not need this information, NULL can be passed.
 @return An array of VNHumanHandPoseObservationJointsGroupName symbols that are supported by the request revision, or nil if a failure occurs.
*/
+ (nullable NSArray<VNHumanHandPoseObservationJointsGroupName>*) supportedJointsGroupNamesForRevision:(NSUInteger)revision error:(NSError **)error API_DEPRECATED_WITH_REPLACEMENT("supportedJointsGroupNamesAndReturnError", macos(11.0, 14.0), ios(14.0, 17.0), tvos(14.0, 17.0));

/*!
 @brief Obtain the collection of human hand joints group names that are supported by a given request object configured with a specific revision.
 @param error The address of a variable that will be populated with an error upon failure.  If the caller does not need this information, NULL can be passed.
 @return An array of VNHumanHandPoseObservationJointsGroupName symbols that are supported by the request revision, or nil if a failure occurs.
*/
- (nullable NSArray<VNHumanHandPoseObservationJointsGroupName>*) supportedJointsGroupNamesAndReturnError:(NSError **)error API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));

/*!
	@brief Defines an upper bounds to the maximum number of hands that will be processed for key points in an image.
	@discussion The complexity in key points determination is scalable by the number of hands to be processed.  All hands detected in an image will be ordered by relative size, with only the N largest ones having key points determined.  The default value for this property is 2. The maximum value for VNDetectHumanHandPoseRequestRevision1 is 6.
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
