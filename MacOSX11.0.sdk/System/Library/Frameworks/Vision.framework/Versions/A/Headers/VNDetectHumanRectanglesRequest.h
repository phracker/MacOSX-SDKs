//
//  VNDetectHumanRectanglesRequest.h
//  Vision
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>


NS_ASSUME_NONNULL_BEGIN


/*!
 @brief A request that will detect human Torsos in an image.
 
 @details This request will generate VNDetectedObjectObservation objects with a defined boundingBox and confidence score.
 */
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@interface VNDetectHumanRectanglesRequest : VNImageBasedRequest
@end


API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
static const NSUInteger VNDetectHumanRectanglesRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
