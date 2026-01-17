//
//  VNCalculateImageAestheticsScoresRequest.h
//  Vision
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>
#import <Vision/VNObservation.h>


NS_ASSUME_NONNULL_BEGIN

/*!
     @brief    Analyzes an image for aesthetically pleasing attributes and returns a VNImageAestheticsScoresObservation.
             This observation calculates an overall aeshetically pleasing score for the image and checks for utility images.
*/
API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), visionos(2.0))
@interface VNCalculateImageAestheticsScoresRequest : VNImageBasedRequest

/*!
    @discussion VNObservation results.
*/

@property (readonly, copy, nullable) NSArray<VNImageAestheticsScoresObservation*>* results;

@end

API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), visionos(2.0))
static const NSUInteger VNCalculateImageAestheticsScoresRequestRevision1 = 1;

NS_ASSUME_NONNULL_END
