//
//  MKCircle.h
//  MapKit
//
//  Copyright (c) 2010-2013, Apple Inc. All rights reserved.
//

#import <MapKit/MKShape.h>
#import <MapKit/MKOverlay.h>
#import <MapKit/MKGeometry.h>
#import <MapKit/MKFoundation.h>

MK_CLASS_AVAILABLE(10_9, 4_0)
@interface MKCircle : MKShape <MKOverlay>

+ (MKCircle *)circleWithCenterCoordinate:(CLLocationCoordinate2D)coord
                                  radius:(CLLocationDistance)radius;

+ (MKCircle *)circleWithMapRect:(MKMapRect)mapRect; // radius will be determined from MAX(width, height)

@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;
@property (nonatomic, readonly) CLLocationDistance radius;

@property (nonatomic, readonly) MKMapRect boundingMapRect; 

@end
