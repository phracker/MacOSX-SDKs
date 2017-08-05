//
//  MKPolyline.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKMultiPoint.h>
#import <MapKit/MKOverlay.h>
#import <MapKit/MKFoundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_9, 4_0) __TVOS_AVAILABLE(9_2) __WATCHOS_PROHIBITED
@interface MKPolyline : MKMultiPoint <MKOverlay>

+ (instancetype)polylineWithPoints:(const MKMapPoint *)points count:(NSUInteger)count;
+ (instancetype)polylineWithCoordinates:(const CLLocationCoordinate2D *)coords count:(NSUInteger)count;

@end

NS_ASSUME_NONNULL_END
