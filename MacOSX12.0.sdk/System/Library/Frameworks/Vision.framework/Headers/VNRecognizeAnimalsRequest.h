//
//  VNRecognizeAnimalsRequest.h
//  Vision
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>
#import <Vision/VNObservation.h>


NS_ASSUME_NONNULL_BEGIN


typedef NSString *VNAnimalIdentifier NS_STRING_ENUM;

VN_EXPORT VNAnimalIdentifier const VNAnimalIdentifierDog API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));
VN_EXPORT VNAnimalIdentifier const VNAnimalIdentifierCat API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0));


/*!
	@brief A request that will recognize various animals in an image. The list of animals supported by the recognition algorithm can be queried by  -supportedIdentifiersAndReturnError:

	@details This request will generate VNRecognizedObjectObservation objects with a defined boundingBox, label and confidence level.
*/
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@interface VNRecognizeAnimalsRequest : VNImageBasedRequest

/*!
 @brief This class method returns a list of all animals supported by the recognition algorithm
 
 @details This request will generate a collection of names for supported animals by current recognition algorithm.
 */
+ (nullable NSArray<VNAnimalIdentifier> *)knownAnimalIdentifiersForRevision:(NSUInteger)requestRevision error:(NSError **)error API_DEPRECATED_WITH_REPLACEMENT("-supportedIdentifiersAndReturnError:", macos(10.15, 12.0), ios(13.0, 15.0), tvos(13.0, 15.0));

/*!
    @brief Obtain the collection of identifiers supported by the target request.
    @discussion This method will return the collection of all possible classification identifiers that are produced by the target request based on its current state of configuration at the time of the call.

    @param error The address of the variable that will be populated with the error if the call fails.
    
    @return The collection of classification identifiers, or nil if a failure occurs.
*/
- (nullable NSArray<VNAnimalIdentifier>*) supportedIdentifiersAndReturnError:(NSError**)error API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));

/*!
	@discussion VNRecognizedObjectObservation results.
*/
@property (readonly, copy, nullable) NSArray<VNRecognizedObjectObservation*>* results;

@end


API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
static const NSUInteger VNRecognizeAnimalsRequestRevision1 = 1;

API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0))
static const NSUInteger VNRecognizeAnimalsRequestRevision2 = 2;


NS_ASSUME_NONNULL_END
