//
//  VNDetectAnimalBodyPoseRequest.h
//  Vision
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>
#import <Vision/VNTypes.h>


NS_ASSUME_NONNULL_BEGIN

/*!
 @brief Detects specific landmark points on animal bodies.
 @discussion This request will produce a collection of VNAnimalBodyPoseObservation objects which describe the pose of each detected animal body.
*/
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0))
@interface VNDetectAnimalBodyPoseRequest : VNImageBasedRequest

/*!
 @brief Obtain the collection of animal body joint names that are supported by a request object configured with a request revision.
 @param error The address of a variable that will be populated with an error upon failure.  If the caller does not need this information, NULL can be passed.
 @return An array of VNAnimalBodyPoseObservationJointName symbols that are supported by the request, or nil if a failure occurs.
*/
- (nullable NSArray<VNAnimalBodyPoseObservationJointName>*) supportedJointNamesAndReturnError:(NSError **)error;


/*!
 @brief Obtain the collection of animal body joints group names that are supported by a request object configured with a request revision.
 @param error The address of a variable that will be populated with an error upon failure.  If the caller does not need this information, NULL can be passed.
 @return An array of VNAnimalBodyPoseObservationJointsGroupName symbols that are supported by the request, or nil if a failure occurs.
*/
- (nullable NSArray<VNAnimalBodyPoseObservationJointsGroupName>*) supportedJointsGroupNamesAndReturnError:(NSError **)error;


/*!
 @discussion VNAnimalBodyPoseObservation results.
*/
@property (readonly, copy, nullable) NSArray<VNAnimalBodyPoseObservation*>* results;

@end


API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0))
static const NSUInteger VNDetectAnimalBodyPoseRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
