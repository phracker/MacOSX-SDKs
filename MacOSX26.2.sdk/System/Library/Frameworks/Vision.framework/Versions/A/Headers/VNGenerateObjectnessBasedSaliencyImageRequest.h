//
//  VNGenerateObjectnessBasedSaliencyImageRequest.h
//  Vision
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>
#import <Vision/VNObservation.h>


NS_ASSUME_NONNULL_BEGIN

/*!
 @brief    Generates an image that identifies which part(s) of a given image are most likely to be objects (i.e. something that a human is likely to see as an object).
 The resulting observation, VNSaliencyImageObservation, encodes this data as a heat map which can be used highlight regions of interest.
 */
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@interface VNGenerateObjectnessBasedSaliencyImageRequest : VNImageBasedRequest

/*!
	@discussion VNSaliencyImageObservation results.
*/
@property (readonly, copy, nullable) NSArray<VNSaliencyImageObservation*>* results;

@end



API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
static const NSUInteger VNGenerateObjectnessBasedSaliencyImageRequestRevision1 = 1;


/*!
	@brief Improved accuracy, reduced latency and memory utilization.
*/
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0))
static const NSUInteger VNGenerateObjectnessBasedSaliencyImageRequestRevision2 = 2;


NS_ASSUME_NONNULL_END
