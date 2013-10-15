//
//  MKDirectionsRequest.h
//  MapKit
//
//  Copyright (c) 2012-2013, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MapKit/MKMapItem.h>
#import <MapKit/MKDirectionsTypes.h>

MK_CLASS_AVAILABLE(10_9, 6_0)
@interface MKDirectionsRequest : NSObject

- (MKMapItem *)source NS_AVAILABLE(10_9, 6_0);
- (void)setSource:(MKMapItem *)source NS_AVAILABLE(10_9, 7_0);

- (MKMapItem *)destination NS_AVAILABLE(10_9, 6_0);
- (void)setDestination:(MKMapItem *)destination NS_AVAILABLE(10_9, 7_0);

@end

@interface MKDirectionsRequest (MKRequestOptions)

@property (nonatomic) MKDirectionsTransportType transportType NS_AVAILABLE(10_9, 7_0); // Default is MKDirectionsTransportTypeAny

@property (nonatomic) BOOL requestsAlternateRoutes NS_AVAILABLE(10_9, 7_0); // if YES and there is more than one reasonable way to route from source to destination, allow the route server to return multiple routes. Default is NO.

// Set either departure or arrival date to hint to the route server when the trip will take place.
@property (nonatomic, copy) NSDate *departureDate NS_AVAILABLE(10_9, 7_0);
@property (nonatomic, copy) NSDate *arrivalDate NS_AVAILABLE(10_9, 7_0);

@end

@interface MKDirectionsRequest (MKDirectionsURL)

- (id)initWithContentsOfURL:(NSURL *)url NS_AVAILABLE(10_9, 6_0);
+ (BOOL)isDirectionsRequestURL:(NSURL *)url NS_AVAILABLE(10_9, 6_0);

@end
