//
//  VNFaceObservationAccepting.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN


@class VNFaceObservation;


/*!
	@brief A protocol that allows a user to provide an input collection of VNFaceObservations as part of a request. The protocol can be adopted by request objects that request additional information about detected faces, such as facial landmarks. 
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@protocol VNFaceObservationAccepting < NSObject >
@required

/*!
	@brief	The VNFaceObservation objects to be processed as part of the request.
*/
@property (readwrite, nonatomic, copy, nullable) NSArray<VNFaceObservation *> *inputFaceObservations;

@end


NS_ASSUME_NONNULL_END
