//
//  VNTrackObjectRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Vision/VNTrackingRequest.h>


NS_ASSUME_NONNULL_BEGIN


@class VNDetectedObjectObservation;


API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNTrackObjectRequest : VNTrackingRequest

- (instancetype) initWithDetectedObjectObservation:(VNDetectedObjectObservation *)observation;
- (instancetype) initWithDetectedObjectObservation:(VNDetectedObjectObservation *)observation completionHandler:(nullable VNRequestCompletionHandler)completionHandler;

- (instancetype) init   NS_UNAVAILABLE;
- (instancetype) initWithCompletionHandler:(nullable VNRequestCompletionHandler)completionHandler   NS_UNAVAILABLE;

@end


NS_ASSUME_NONNULL_END
