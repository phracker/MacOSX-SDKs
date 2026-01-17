//
//  MKDirectionsRequest.h
//  MapKit
//
//  Copyright (c) 2012-2014, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MapKit/MKMapItem.h>
#import <MapKit/MKDirectionsTypes.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(16.0), tvos(16.0), macos(13.0), watchos(9.0))
typedef NS_ENUM(NSInteger, MKDirectionsRoutePreference) {
    MKDirectionsRoutePreferenceAny = 0,
    MKDirectionsRoutePreferenceAvoid
};

API_AVAILABLE(macos(10.9), ios(6.0), tvos(9.2), watchos(1.0))
@interface MKDirectionsRequest : NSObject

@property (nonatomic, strong, nullable) MKMapItem *source;
- (void)setSource:(nullable MKMapItem *)source NS_AVAILABLE(10_9, 7_0);

@property (nonatomic, strong, nullable) MKMapItem *destination;
- (void)setDestination:(nullable MKMapItem *)destination NS_AVAILABLE(10_9, 7_0);

@end

@interface MKDirectionsRequest (MKRequestOptions)

@property (nonatomic) MKDirectionsTransportType transportType NS_AVAILABLE(10_9, 7_0); // Default is MKDirectionsTransportTypeAny

@property (nonatomic) BOOL requestsAlternateRoutes NS_AVAILABLE(10_9, 7_0); // if YES and there is more than one reasonable way to route from source to destination, allow the route server to return multiple routes. Default is NO.

// Set either departure or arrival date to hint to the route server when the trip will take place.
@property (nonatomic, copy, nullable) NSDate *departureDate NS_AVAILABLE(10_9, 7_0);
@property (nonatomic, copy, nullable) NSDate *arrivalDate NS_AVAILABLE(10_9, 7_0);

@property (nonatomic) MKDirectionsRoutePreference tollPreference API_AVAILABLE(ios(16.0), tvos(16.0), macos(13.0), watchos(9.0)); // Default is MKDirectionsRoutePreferenceAny
@property (nonatomic) MKDirectionsRoutePreference highwayPreference API_AVAILABLE(ios(16.0), tvos(16.0), macos(13.0), watchos(9.0)); // Default is MKDirectionsRoutePreferenceAny

@end

@interface MKDirectionsRequest (MKDirectionsURL)

- (instancetype)initWithContentsOfURL:(NSURL *)url NS_AVAILABLE(10_9, 6_0);
+ (BOOL)isDirectionsRequestURL:(NSURL *)url NS_AVAILABLE(10_9, 6_0);

@end

NS_ASSUME_NONNULL_END
