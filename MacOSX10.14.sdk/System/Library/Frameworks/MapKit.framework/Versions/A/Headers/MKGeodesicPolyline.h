//
//  MKGeodesicPolyline.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKPolyline.h>

NS_ASSUME_NONNULL_BEGIN

/*
 An MKGeodesicPolyline follows the shortest path along the surface of the earth,
 which may appear as a curved line when drawn on the projected MKMapView.
 */
NS_CLASS_AVAILABLE(10_9, 7_0) __TVOS_AVAILABLE(9_2) __WATCHOS_PROHIBITED
@interface MKGeodesicPolyline : MKPolyline

+ (instancetype)polylineWithPoints:(const MKMapPoint *)points count:(NSUInteger)count;
+ (instancetype)polylineWithCoordinates:(const CLLocationCoordinate2D *)coords count:(NSUInteger)count;

@end

NS_ASSUME_NONNULL_END
