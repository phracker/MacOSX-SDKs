//
//  VNGenerateAttentionBasedSaliencyImageRequest.h
//  Vision
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Vision/VNRequest.h>


NS_ASSUME_NONNULL_BEGIN


/*!
	@brief	Generates an image that identifies which part(s) of a given image is most interesting (i.e. something that a human is likely to look at - hence attention based).
			The resulting observation, VNSaliencyImageObservation, encodes this data as a heat map which can be used to highlight regions of interest.
*/
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@interface VNGenerateAttentionBasedSaliencyImageRequest : VNImageBasedRequest
@end


API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
static const NSUInteger VNGenerateAttentionBasedSaliencyImageRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
