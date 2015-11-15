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

MK_CLASS_AVAILABLE(10_9, 4_0) __WATCHOS_PROHIBITED
@interface MKPolygon : MKMultiPoint <MKOverlay>

+ (instancetype)polygonWithPoints:(MKMapPoint *)points count:(NSUInteger)count;
+ (instancetype)polygonWithPoints:(MKMapPoint *)points count:(NSUInteger)count interiorPolygons:(nullable NSArray<MKPolygon *> *)interiorPolygons;

+ (instancetype)polygonWithCoordinates:(CLLocationCoordinate2D *)coords count:(NSUInteger)count;
+ (instancetype)polygonWithCoordinates:(CLLocationCoordinate2D *)coords count:(NSUInteger)count interiorPolygons:(nullable NSArray<MKPolygon *> *)interiorPolygons;

@property (readonly, nullable) NSArray<MKPolygon *> *interiorPolygons;

@end

NS_ASSUME_NONNULL_END
