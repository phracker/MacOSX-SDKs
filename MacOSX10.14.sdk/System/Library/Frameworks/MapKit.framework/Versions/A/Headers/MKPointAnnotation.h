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

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_9, 4_0) __TVOS_AVAILABLE(9_2) __WATCHOS_PROHIBITED
@interface MKPointAnnotation : MKShape

@property (nonatomic, assign) CLLocationCoordinate2D coordinate;

@end

NS_ASSUME_NONNULL_END
