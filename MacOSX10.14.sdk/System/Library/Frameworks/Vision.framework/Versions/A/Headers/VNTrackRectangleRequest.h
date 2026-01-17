//
//  VNTrackRectangleRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Vision/VNTrackingRequest.h>


NS_ASSUME_NONNULL_BEGIN


@class VNRectangleObservation;


/*!
 @brief VNTrackRectangleRequest tracks a rectangle in a sequence of images.
 @discussion The VNTrackRectangleRequest is a special tracker to track rectangular shape objects. The VNTrackRectangleRequest is initialized with a VNRectangleObservation object that contains a rectangle bounding box and four corners locations. VNRectangleObservation can be obtained by running rectangle detector  (VNDetectRectanglesRequest). The VNTrackRectangleRequest is processed using one of the [VNSequenceRequestHandler performRequests:...] methods.
 @note The rectangular object doesn't have to look like a rectangle when projected into the plane of the image of interest. For example, it may look like trapezoid.
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNTrackRectangleRequest : VNTrackingRequest

/*!
 @property property inputObservation
 @abstract Rectangle observation, coming from rectangle detector (VNDetectRectanglesRequest), for initial tracker setup or returned from previous rectangle tracking iteration. The rectangle must be defined in normalized coordinates (size and origin between [0,1] with origin at lower left corner).
 */


/*!
 @brief Create a new rectangle tracking request with rectangle observation.
 
 @param    observation          Rectangle observation with bounding box and rectangle corners location info.
 */
- (instancetype) initWithRectangleObservation:(VNRectangleObservation *)observation;

/*!
 @brief Create a new rectangle tracking request with rectangle observation.
 
 @param    observation          Rectangle observation with bounding box and rectangle corners location info.
 @param    completionHandler    The block that is invoked when the request has been performed.
 */
- (instancetype) initWithRectangleObservation:(VNRectangleObservation *)observation completionHandler:(nullable VNRequestCompletionHandler)completionHandler  NS_DESIGNATED_INITIALIZER;

- (instancetype) init   NS_UNAVAILABLE;
- (instancetype) initWithCompletionHandler:(nullable VNRequestCompletionHandler)completionHandler   NS_UNAVAILABLE;

@end


API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
static const NSUInteger VNTrackRectangleRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
