//
//  VNRecognizeAnimalsRequest.h
//  Vision
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>
#import <Vision/VNDefines.h>


NS_ASSUME_NONNULL_BEGIN


typedef NSString *VNAnimalIdentifier NS_STRING_ENUM;

VN_EXPORT VNAnimalIdentifier const VNAnimalIdentifierDog API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));
VN_EXPORT VNAnimalIdentifier const VNAnimalIdentifierCat API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));


/*!
	@brief A request that will recognize various animals in an image. The list of animals supported by the recognition algorithm can be queried by +(NSArray *)knownAnimalIdentifiersForRevision

	@details This request will generate VNRecognizedObjectObservation objects with a defined boundingBox, label and confidence level.
*/
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@interface VNRecognizeAnimalsRequest : VNImageBasedRequest

/*!
 @brief This class method returns a list of all animals supported by the recognition algorithm
 
 @details This request will generate a collection of names for supported animals by current recognition algorithm.
 */
+ (nullable NSArray<VNAnimalIdentifier> *)knownAnimalIdentifiersForRevision:(NSUInteger)requestRevision error:(NSError **)error;

@end


API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
static const NSUInteger VNRecognizeAnimalsRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
