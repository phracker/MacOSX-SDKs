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

NS_CLASS_AVAILABLE(10_9, 4_0) __TVOS_AVAILABLE(9_2) API_UNAVAILABLE(watchos)
@interface MKPointAnnotation : MKShape

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCoordinate:(CLLocationCoordinate2D)coordinate NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15)) API_UNAVAILABLE(watchos);
- (instancetype)initWithCoordinate:(CLLocationCoordinate2D)coordinate title:(nullable NSString *)title subtitle:(nullable NSString *)subtitle NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15)) API_UNAVAILABLE(watchos);

@property (nonatomic, assign) CLLocationCoordinate2D coordinate;

@end

NS_ASSUME_NONNULL_END
