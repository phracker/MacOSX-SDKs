//
//  MKPointAnnotation.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKShape.h>
#import <MapKit/MKFoundation.h>
#import <CoreLocation/CLLocation.h>

MK_CLASS_AVAILABLE(10_9, 4_0)
@interface MKPointAnnotation : MKShape

@property (nonatomic, assign) CLLocationCoordinate2D coordinate;

@end
