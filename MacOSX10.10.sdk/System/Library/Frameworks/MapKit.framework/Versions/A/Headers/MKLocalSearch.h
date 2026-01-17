//
//  MKLocalSearch.h
//  MapKit
//
//  Copyright (c) 2012-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

@class MKLocalSearchRequest;
@class MKLocalSearchResponse;

typedef void (^MKLocalSearchCompletionHandler)(MKLocalSearchResponse *response, NSError *error);

MK_CLASS_AVAILABLE(10_9, 6_1)
@interface MKLocalSearch : NSObject

// The request will be copied during initialization, so any changes made to the request
// after this method returns do not affect the request used in -startWithCompletionHandler:
- (instancetype)initWithRequest:(MKLocalSearchRequest *)request NS_DESIGNATED_INITIALIZER;

// Any calls to -startWithCompletionHandler: while -[MKLocalSearch isSearching] will fail.
// completionHandler will be called on the main queue
- (void)startWithCompletionHandler:(MKLocalSearchCompletionHandler)completionHandler;
- (void)cancel;

@property (nonatomic, readonly, getter=isSearching) BOOL searching;

@end
