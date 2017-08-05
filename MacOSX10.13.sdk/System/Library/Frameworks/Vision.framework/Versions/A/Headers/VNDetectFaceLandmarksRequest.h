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

	@details This request will generate VNFaceObservation objects with the landmarks property populated with information describing face landmarks.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNDetectFaceLandmarksRequest : VNImageBasedRequest <VNFaceObservationAccepting>
@end


NS_ASSUME_NONNULL_END
