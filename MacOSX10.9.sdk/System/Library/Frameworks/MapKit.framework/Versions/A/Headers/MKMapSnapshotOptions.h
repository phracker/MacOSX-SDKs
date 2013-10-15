//
//  MKMapSnapshotOptions.h
//  MapKit
//
//  Copyright (c) 2013, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKGeometry.h>
#import <MapKit/MKTypes.h>
#import <MapKit/MKMapView.h>

MK_CLASS_AVAILABLE(10_9, 7_0)
@interface MKMapSnapshotOptions : NSObject <NSCopying>

@property (nonatomic, copy) MKMapCamera *camera;
@property (nonatomic, assign) MKMapRect mapRect;
@property (nonatomic, assign) MKCoordinateRegion region;
@property (nonatomic, assign) MKMapType mapType;

@property (nonatomic) BOOL showsPointsOfInterest; // Affects MKMapTypeStandard and MKMapTypeHybrid
@property (nonatomic) BOOL showsBuildings; // Affects MKMapTypeStandard

// The size of the image to create. Defaults to 256x256
#if TARGET_OS_IPHONE
@property (nonatomic, assign) CGSize size;
#else
@property (nonatomic, assign) NSSize size;
#endif

#if TARGET_OS_IPHONE
// Defaults to the device's screen scale
@property (nonatomic, assign) CGFloat scale;
#endif

@end
