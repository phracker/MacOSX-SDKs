//
//  VNDetectFaceLandmarksRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>
#import <Vision/VNFaceObservationAccepting.h>


NS_ASSUME_NONNULL_BEGIN


/*!
	@brief A request that will produce face landmark information.

	@details This request will generate VNFaceObservation objects with the landmarks property populated with information describing face landmarks. If VNFaceObservations are provided via the VNFaceObservationAccepting protocol without the landmarks property populated, new observations will be created as copies of the input VNFaceObservations with the landmarks property populated. If the landmarks property has already been populated, the original VNFaceObservations will be returned. If no VNFaceObservations are provided, face detection will be run first. 
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNDetectFaceLandmarksRequest : VNImageBasedRequest <VNFaceObservationAccepting>
@end


API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
static const NSUInteger VNDetectFaceLandmarksRequestRevision1 = 1;

API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
static const NSUInteger VNDetectFaceLandmarksRequestRevision2 = 2;


NS_ASSUME_NONNULL_END
