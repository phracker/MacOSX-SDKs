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

API_AVAILABLE(macos(10.9), ios(4.0), tvos(9.2), watchos(1.0))
@interface MKPolyline : MKMultiPoint <MKOverlay>

+ (instancetype)polylineWithPoints:(const MKMapPoint *)points count:(NSUInteger)count;
+ (instancetype)polylineWithCoordinates:(const CLLocationCoordinate2D *)coords count:(NSUInteger)count;

@end

NS_ASSUME_NONNULL_END
