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

API_AVAILABLE(macos(10.9), ios(4.0), tvos(9.2), watchos(1.0))
@interface MKPointAnnotation : MKShape

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCoordinate:(CLLocationCoordinate2D)coordinate API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15), watchos(6.0));
- (instancetype)initWithCoordinate:(CLLocationCoordinate2D)coordinate title:(nullable NSString *)title subtitle:(nullable NSString *)subtitle API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15), watchos(6.0));

@property (nonatomic, assign) CLLocationCoordinate2D coordinate;

@end

NS_ASSUME_NONNULL_END
