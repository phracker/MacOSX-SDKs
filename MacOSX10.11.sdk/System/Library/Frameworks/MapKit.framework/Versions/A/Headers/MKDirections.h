//
//  MKDirections.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

@class MKDirectionsRequest;
@class MKDirectionsResponse;
@class MKETAResponse;

NS_ASSUME_NONNULL_BEGIN

typedef void (^MKDirectionsHandler)(MKDirectionsResponse * __nullable response, NSError * __nullable error);
typedef void (^MKETAHandler)(MKETAResponse * __nullable response, NSError * __nullable error);

MK_CLASS_AVAILABLE(10_9, 7_0) __WATCHOS_PROHIBITED
@interface MKDirections : NSObject

// The request will be copied during initialization, so any changes made to the request
// after this method returns do not affect the request used in -calculateDirectionsWithCompletionHandler:
- (instancetype)initWithRequest:(MKDirectionsRequest *)request NS_DESIGNATED_INITIALIZER;

// Any calls to -calculateDirectionsWithCompletionHandler: or calculateETAWithCompletionHandler
// while -[MKDirections isCalculating] will fail. completionHandler will be called on the main queue
- (void)calculateDirectionsWithCompletionHandler:(MKDirectionsHandler)completionHandler;
- (void)calculateETAWithCompletionHandler:(MKETAHandler)completionHandler;
- (void)cancel;

@property (nonatomic, readonly, getter=isCalculating) BOOL calculating;

@end

NS_ASSUME_NONNULL_END
