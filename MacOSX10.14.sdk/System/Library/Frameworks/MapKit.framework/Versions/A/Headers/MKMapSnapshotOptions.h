//
//  MKMapSnapshotOptions.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

#if __has_include(<UIKit/UIView.h>) || !TARGET_OS_IPHONE

#import <MapKit/MKGeometry.h>
#import <MapKit/MKTypes.h>
#import <MapKit/MKMapView.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_9, 7_0) __TVOS_AVAILABLE(9_2) __WATCHOS_PROHIBITED
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
@property (nonatomic, nullable, strong) NSAppearance *appearance API_AVAILABLE(macos(10.14)) API_UNAVAILABLE(ios, tvos, watchos);
#endif

#if TARGET_OS_IPHONE
// Defaults to the device's screen scale
@property (nonatomic, assign) CGFloat scale;
#endif

@end

NS_ASSUME_NONNULL_END

#endif
