//
//  MKDirectionsResponse.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKDirectionsTypes.h>
#import <CoreLocation/CoreLocation.h>

@class MKMapItem;
@class MKPolyline;
@class MKRoute;
@class MKRouteStep;

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_9, 7_0) __TVOS_AVAILABLE(9_2) API_UNAVAILABLE(watchos)
@interface MKDirectionsResponse : NSObject

// Source and destination may be filled with additional details compared to the request object.
@property (nonatomic, readonly) MKMapItem *source;
@property (nonatomic, readonly) MKMapItem *destination;

@property (nonatomic, readonly) NSArray<MKRoute *> *routes;

@end

NS_CLASS_AVAILABLE(10_9, 7_0) __TVOS_AVAILABLE(9_2) API_UNAVAILABLE(watchos)
@interface MKRoute : NSObject

@property (nonatomic, readonly) NSString *name; // localized description of the route's significant feature, e.g. "US-101"

@property (nonatomic, readonly) NSArray<NSString *> *advisoryNotices; // localized notices of route conditions. e.g. "Avoid during winter storms"

@property (nonatomic, readonly) CLLocationDistance distance; // overall route distance in meters
@property (nonatomic, readonly) NSTimeInterval expectedTravelTime;

@property (nonatomic, readonly) MKDirectionsTransportType transportType; // overall route transport type

@property (nonatomic, readonly) MKPolyline *polyline; // detailed route geometry

@property (nonatomic, readonly) NSArray<MKRouteStep *> *steps;

@end

NS_CLASS_AVAILABLE(10_9, 7_0) __TVOS_AVAILABLE(9_2) API_UNAVAILABLE(watchos)
@interface MKRouteStep : NSObject

@property (nonatomic, readonly) NSString *instructions; // localized written instructions
@property (nonatomic, readonly, nullable) NSString *notice; // additional localized legal or warning notice related to this step (e.g. "Do not cross tracks when lights flash")

@property (nonatomic, readonly) MKPolyline *polyline; // detailed step geometry

@property (nonatomic, readonly) CLLocationDistance distance; // step distance in meters

@property (nonatomic, readonly) MKDirectionsTransportType transportType; // step transport type (may differ from overall route transport type)

@end

NS_CLASS_AVAILABLE(10_9, 7_0) __TVOS_AVAILABLE(9_2) API_UNAVAILABLE(watchos)
@interface MKETAResponse : NSObject

// Source and destination may be filled with additional details compared to the request object.
@property (nonatomic, readonly) MKMapItem *source;
@property (nonatomic, readonly) MKMapItem *destination;
@property (nonatomic, readonly) NSTimeInterval expectedTravelTime;
@property (nonatomic, readonly) CLLocationDistance distance NS_AVAILABLE(10_11, 9_0); // overall route distance in meters
@property (nonatomic, readonly) NSDate *expectedArrivalDate NS_AVAILABLE(10_11, 9_0);
@property (nonatomic, readonly) NSDate *expectedDepartureDate NS_AVAILABLE(10_11, 9_0);
@property (nonatomic, readonly) MKDirectionsTransportType transportType NS_AVAILABLE(10_11, 9_0);
@end

NS_ASSUME_NONNULL_END
