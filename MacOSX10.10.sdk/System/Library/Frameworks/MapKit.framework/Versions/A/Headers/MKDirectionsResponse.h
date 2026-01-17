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

MK_CLASS_AVAILABLE(10_9, 7_0)
@interface MKDirectionsResponse : NSObject

// Source and destination may be filled with additional details compared to the request object.
@property (nonatomic, readonly) MKMapItem *source;
@property (nonatomic, readonly) MKMapItem *destination;

@property (nonatomic, readonly) NSArray *routes; // array of MKRoute objects

@end

MK_CLASS_AVAILABLE(10_9, 7_0)
@interface MKRoute : NSObject

@property (nonatomic, readonly) NSString *name; // localized description of the route's significant feature, e.g. "US-101"

@property (nonatomic, readonly) NSArray *advisoryNotices; // localized notices of route conditions as NSStrings. e.g. "Avoid during winter storms"

@property (nonatomic, readonly) CLLocationDistance distance; // overall route distance in meters
@property (nonatomic, readonly) NSTimeInterval expectedTravelTime;

@property (nonatomic, readonly) MKDirectionsTransportType transportType; // overall route transport type

@property (nonatomic, readonly) MKPolyline *polyline; // detailed route geometry

@property (nonatomic, readonly) NSArray *steps; // array of MKRouteStep objects

@end

MK_CLASS_AVAILABLE(10_9, 7_0)
@interface MKRouteStep : NSObject

@property (nonatomic, readonly) NSString *instructions; // localized written instructions
@property (nonatomic, readonly) NSString *notice; // additional localized legal or warning notice related to this step (e.g. "Do not cross tracks when lights flash")

@property (nonatomic, readonly) MKPolyline *polyline; // detailed step geometry

@property (nonatomic, readonly) CLLocationDistance distance; // step distance in meters

@property (nonatomic, readonly) MKDirectionsTransportType transportType; // step transport type (may differ from overall route transport type)

@end

MK_CLASS_AVAILABLE(10_9, 7_0)
@interface MKETAResponse : NSObject

// Source and destination may be filled with additional details compared to the request object.
@property (nonatomic, readonly) MKMapItem *source;
@property (nonatomic, readonly) MKMapItem *destination;

@property (nonatomic, readonly) NSTimeInterval expectedTravelTime;

@end
