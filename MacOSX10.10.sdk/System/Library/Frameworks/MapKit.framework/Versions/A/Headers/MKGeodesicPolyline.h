//
//  MKGeodesicPolyline.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKPolyline.h>

/*
 An MKGeodesicPolyline follows the shortest path along the surface of the earth,
 which may appear as a curved line when drawn on the projected MKMapView.
 */
MK_CLASS_AVAILABLE(10_9, 7_0)
@interface MKGeodesicPolyline : MKPolyline

+ (instancetype)polylineWithPoints:(MKMapPoint *)points count:(NSUInteger)count;
+ (instancetype)polylineWithCoordinates:(CLLocationCoordinate2D *)coords count:(NSUInteger)count;

@end
