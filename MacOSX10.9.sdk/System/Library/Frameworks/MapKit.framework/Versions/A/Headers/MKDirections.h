//
//  MKDirections.h
//  MapKit
//
//  Copyright (c) 2013, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

@class MKDirectionsRequest;
@class MKDirectionsResponse;
@class MKETAResponse;

typedef void (^MKDirectionsHandler)(MKDirectionsResponse *response, NSError *error);
typedef void (^MKETAHandler)(MKETAResponse *response, NSError *error);

MK_CLASS_AVAILABLE(10_9, 7_0)
@interface MKDirections : NSObject

// Designated initializer
//
// The request will be copied during initialization, so any changes made to the request
// after this method returns do not affect the request used in -calculateDirectionsWithCompletionHandler:
- (instancetype)initWithRequest:(MKDirectionsRequest *)request;

// Any calls to -calculateDirectionsWithCompletionHandler: or calculateETAWithCompletionHandler
// while -[MKDirections isCalculating] will fail. completionHandler will be called on the main queue
- (void)calculateDirectionsWithCompletionHandler:(MKDirectionsHandler)completionHandler;
- (void)calculateETAWithCompletionHandler:(MKETAHandler)completionHandler;
- (void)cancel;

@property (nonatomic, readonly, getter=isCalculating) BOOL calculating;

@end
