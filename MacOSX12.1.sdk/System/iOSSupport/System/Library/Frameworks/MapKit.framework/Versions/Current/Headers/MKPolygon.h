//
//  MKPolygon.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKMultiPoint.h>
#import <MapKit/MKOverlay.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_9, 4_0) __TVOS_AVAILABLE(9_2) API_UNAVAILABLE(watchos)
@interface MKPolygon : MKMultiPoint <MKOverlay>

+ (instancetype)polygonWithPoints:(const MKMapPoint *)points count:(NSUInteger)count;
+ (instancetype)polygonWithPoints:(const MKMapPoint *)points count:(NSUInteger)count interiorPolygons:(nullable NSArray<MKPolygon *> *)interiorPolygons;

+ (instancetype)polygonWithCoordinates:(const CLLocationCoordinate2D *)coords count:(NSUInteger)count;
+ (instancetype)polygonWithCoordinates:(const CLLocationCoordinate2D *)coords count:(NSUInteger)count interiorPolygons:(nullable NSArray<MKPolygon *> *)interiorPolygons;

@property (atomic, readonly, nullable) NSArray<MKPolygon *> *interiorPolygons;

@end

NS_ASSUME_NONNULL_END
