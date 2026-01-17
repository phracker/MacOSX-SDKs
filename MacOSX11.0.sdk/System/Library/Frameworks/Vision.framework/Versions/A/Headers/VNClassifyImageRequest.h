//
//  VNClassifyImageRequest.h
//  Vision
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>


NS_ASSUME_NONNULL_BEGIN


@class VNClassificationObservation;


/*!
	@brief A request for classifying an image.

	@discussion This request will produce a collection of VNClassificationObservation objects which describe an image.
*/
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@interface VNClassifyImageRequest : VNImageBasedRequest

/*!
	@brief Obtain the collection of classifications currently recognized by the Vision framework.
 
	@param	requestRevision		The revision of the request for which classifications should be reported.
 
	@param	error				The address of the variable that will be populated with the error when the call fails.

	@return the collection of classifications for the revision, or nil if an error was encountered.
*/
+ (nullable NSArray<VNClassificationObservation*>*) knownClassificationsForRevision:(NSUInteger)requestRevision error:(NSError**)error;


@end



API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
static const NSUInteger VNClassifyImageRequestRevision1 = 1;



NS_ASSUME_NONNULL_END
