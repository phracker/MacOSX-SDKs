//
//  VNDetectFaceCaptureQualityRequest.h
//  Vision
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>
#import <Vision/VNFaceObservationAccepting.h>
#import <Vision/VNObservation.h>


NS_ASSUME_NONNULL_BEGIN


/*!
 @brief A request that will produce or update a VNFaceObservation's property faceCaptureQuality with a float value.
 faceCaptureQuality is a float (wrapped by a NSNumber) that represents the capture quality of a given face in a photo.
 The float will be a value between 0 and 1, with 1 being the highest face capture quality and 0 being the lowest.
 If the request fails or the face observation has never been processed, the property faceCaptureQuality will be nil.
 
 @details This request will generate VNFaceObservation objects with the face quality variable populated with information .
 */
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@interface VNDetectFaceCaptureQualityRequest : VNImageBasedRequest <VNFaceObservationAccepting>

/*!
	@discussion VNFaceObservation with populated faceCaptureQuality property results.
*/
@property (readonly, copy, nullable) NSArray<VNFaceObservation*>* results;

@end

API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
static const NSUInteger VNDetectFaceCaptureQualityRequestRevision1 = 1;

API_AVAILABLE(macos(11.0), ios(14.0), tvos(14.0))
static const NSUInteger VNDetectFaceCaptureQualityRequestRevision2 = 2;

NS_ASSUME_NONNULL_END
