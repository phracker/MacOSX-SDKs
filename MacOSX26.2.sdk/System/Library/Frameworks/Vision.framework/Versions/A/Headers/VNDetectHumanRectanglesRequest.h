//
//  VNDetectHumanRectanglesRequest.h
//  Vision
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>
#import <Vision/VNObservation.h>


NS_ASSUME_NONNULL_BEGIN


@class VNHumanObservation;


/*!
 @brief A request that will detect human Torsos in an image.
 
 @details This request will generate VNHumanObservation objects with defined boundingBox and confidence score.
 */
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@interface VNDetectHumanRectanglesRequest : VNImageBasedRequest


/*!
 @brief Boolean property to specify whether the human upper body or full body needs to be detected. The default is YES, meaning the request is setup to detect upper body only
 */
@property(nonatomic) BOOL upperBodyOnly API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));

/*!
	@discussion VNHumanObservation results.
*/
@property (readonly, copy, nullable) NSArray<VNHumanObservation*>* results;

@end


/*!
    @brief    This request revsion can detect human upper body only
*/
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
static const NSUInteger VNDetectHumanRectanglesRequestRevision1 = 1;

/*!
    @brief    This request revsion can detect human full body in addition to upper body only in the previous revision. The choice is controlled by [VNDetectHumanRectanglesRequest -upperBodyOnly] property, which is by default set to YES
*/
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0))
static const NSUInteger VNDetectHumanRectanglesRequestRevision2 = 2;


NS_ASSUME_NONNULL_END
