//
//  VNGeneratePersonInstanceMaskRequest.h
//  Vision
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>
#import <Vision/VNObservation.h>



NS_ASSUME_NONNULL_BEGIN


/*!
    @brief A request that generates an instance mask of individual people found in the image.
*/
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0))
@interface VNGeneratePersonInstanceMaskRequest : VNImageBasedRequest

/*!
    @discussion VNObservation results.
*/
@property (readonly, copy, nullable) NSArray<VNInstanceMaskObservation*>* results;

@end


API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0))
static const NSUInteger VNGeneratePersonInstanceMaskRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
