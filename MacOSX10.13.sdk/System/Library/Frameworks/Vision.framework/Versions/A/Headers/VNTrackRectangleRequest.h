//
//  VNTrackRectangleRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Vision/VNTrackingRequest.h>


NS_ASSUME_NONNULL_BEGIN


@class VNRectangleObservation;


API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNTrackRectangleRequest : VNTrackingRequest

- (instancetype) initWithRectangleObservation:(VNRectangleObservation *)observation;
- (instancetype) initWithRectangleObservation:(VNRectangleObservation *)observation completionHandler:(nullable VNRequestCompletionHandler)completionHandler  NS_DESIGNATED_INITIALIZER;

- (instancetype) init   NS_UNAVAILABLE;
- (instancetype) initWithCompletionHandler:(nullable VNRequestCompletionHandler)completionHandler   NS_UNAVAILABLE;

@end


NS_ASSUME_NONNULL_END
