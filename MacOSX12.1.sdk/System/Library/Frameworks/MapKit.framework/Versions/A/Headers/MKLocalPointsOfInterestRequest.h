//
//  MKLocalPointsOfInterestRequest.h
//  MapKit
//
//  Copyright (c) 2020, Apple Inc. All rights reserved.
//

#import <MapKit/MKGeometry.h>
#import <MapKit/MKPointOfInterestFilter.h>

MK_EXTERN const CLLocationDistance MKPointsOfInterestRequestMaxRadius API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0)) API_UNAVAILABLE(watchos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0)) API_UNAVAILABLE(watchos)
@interface MKLocalPointsOfInterestRequest : NSObject <NSCopying>

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithCenterCoordinate:(CLLocationCoordinate2D)coordinate radius:(CLLocationDistance)radius NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCoordinateRegion:(MKCoordinateRegion)region NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;
@property (nonatomic, readonly) CLLocationDistance radius;
@property (nonatomic, readonly) MKCoordinateRegion region;
@property (nonatomic, copy, nullable) MKPointOfInterestFilter *pointOfInterestFilter;

@end

NS_ASSUME_NONNULL_END

