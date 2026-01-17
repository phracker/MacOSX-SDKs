//
//  MKPolygon.h
//  MapKit
//
//  Copyright (c) 2010-2013, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKMultiPoint.h>
#import <MapKit/MKOverlay.h>

MK_CLASS_AVAILABLE(10_9, 4_0)
@interface MKPolygon : MKMultiPoint <MKOverlay>

+ (MKPolygon *)polygonWithPoints:(MKMapPoint *)points count:(NSUInteger)count;
+ (MKPolygon *)polygonWithPoints:(MKMapPoint *)points count:(NSUInteger)count interiorPolygons:(NSArray *)interiorPolygons;

+ (MKPolygon *)polygonWithCoordinates:(CLLocationCoordinate2D *)coords count:(NSUInteger)count;
+ (MKPolygon *)polygonWithCoordinates:(CLLocationCoordinate2D *)coords count:(NSUInteger)count interiorPolygons:(NSArray *)interiorPolygons;

@property (readonly) NSArray *interiorPolygons;

@end
