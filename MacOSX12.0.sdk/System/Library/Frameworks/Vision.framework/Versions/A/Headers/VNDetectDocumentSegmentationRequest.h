//
//  VNDetectDocumentSegmentationRequest.h
//  Vision
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>



NS_ASSUME_NONNULL_BEGIN

/*!
 @brief Performs document detection and segmentation in an image.
 */
API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0))
@interface VNDetectDocumentSegmentationRequest : VNImageBasedRequest

/*!
    @discussion VNRectangleObservation results.
*/
@property (readonly, copy, nullable) NSArray<VNRectangleObservation*>* results;

@end



API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0))
static const NSUInteger VNDetectDocumentSegmentationRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
