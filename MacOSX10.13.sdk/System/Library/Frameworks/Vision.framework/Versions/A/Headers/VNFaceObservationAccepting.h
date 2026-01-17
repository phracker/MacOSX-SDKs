//
//  VNFaceObservationAccepting.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

@class VNFaceObservation;


NS_ASSUME_NONNULL_BEGIN


/*!
	@brief A protocol that can provide a collection of VNFaceObservations.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@protocol VNFaceObservationAccepting < NSObject >
@required

/*!
	@brief	The VNFaceObservation objects to be processed by the request.
*/
@property (readwrite, nonatomic, copy, nullable) NSArray<VNFaceObservation *> *inputFaceObservations;

@end


NS_ASSUME_NONNULL_END
