//
//  VNTrackObjectRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Vision/VNTrackingRequest.h>


NS_ASSUME_NONNULL_BEGIN


@class VNDetectedObjectObservation;


/*!
 @brief VNTrackObjectRequest tracks an object in a sequence of images.
 @discussion The VNTrackObjectRequest is a general purpose object tracker. This tracker is used when the tracked entity does not have a special tracker, like VNTrackRectangleRequest. The VNTrackObjectRequest is initialized with VNDetectedObjectObservation that contains bounding box for the object of interest. This tracker is processed using one of the [VNSequenceRequestHandler performRequests:...] methods.
 */
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNTrackObjectRequest : VNTrackingRequest

/*!
 @brief Create a new request with detected object observation.
 
 @param    observation          Detected object observation with bounding box info.
 */
- (instancetype) initWithDetectedObjectObservation:(VNDetectedObjectObservation *)observation;


/*!
 @brief Create a new request with detected object observation.
 
 @param    observation          Detected object observation with bounding box info.
 @param    completionHandler    The block that is invoked when the request has been performed.
 */
- (instancetype) initWithDetectedObjectObservation:(VNDetectedObjectObservation *)observation completionHandler:(nullable VNRequestCompletionHandler)completionHandler;

- (instancetype) init NS_UNAVAILABLE;
- (instancetype) initWithCompletionHandler:(nullable VNRequestCompletionHandler)completionHandler NS_UNAVAILABLE;

@end


API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
static const NSUInteger VNTrackObjectRequestRevision1 = 1;

API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
static const NSUInteger VNTrackObjectRequestRevision2 = 2;


NS_ASSUME_NONNULL_END
