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

@class MKPointOfInterestFilter;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.2), watchos(1.0))
@interface MKMapSnapshotOptions : NSObject <NSCopying>

@property (nonatomic, copy) MKMapConfiguration *preferredConfiguration API_AVAILABLE(ios(17.0), macos(14.0), tvos(17.0), watchos(10.0));

@property (nonatomic, copy) MKMapCamera *camera;
@property (nonatomic, assign) MKMapRect mapRect;
@property (nonatomic, assign) MKCoordinateRegion region;
@property (nonatomic, assign) MKMapType mapType API_DEPRECATED("Use preferredConfiguration", macos(10.9, API_TO_BE_DEPRECATED), ios(7.0, API_TO_BE_DEPRECATED), tvos(9.2, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(watchos);

@property (nonatomic, copy, nullable) MKPointOfInterestFilter *pointOfInterestFilter API_DEPRECATED("Use preferredConfiguration", macos(10.15, API_TO_BE_DEPRECATED), ios(13.0, API_TO_BE_DEPRECATED), tvos(13.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(watchos);
@property (nonatomic) BOOL showsPointsOfInterest
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_UNAVAILABLE(visionos);
#else
API_DEPRECATED("Use preferredConfiguration", macos(10.9, 10.15), ios(7.0, 13.0), tvos(9.2, 13.0)) API_UNAVAILABLE(watchos); // Affects MKMapTypeStandard and MKMapTypeHybrid
#endif
@property (nonatomic) BOOL showsBuildings API_DEPRECATED("No longer supported.", macos(10.9, API_TO_BE_DEPRECATED), ios(7.0, API_TO_BE_DEPRECATED), tvos(9.2, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(watchos); // Affects MKMapTypeStandard

// The size of the image to create. Defaults to 256x256
#if TARGET_OS_IPHONE
@property (nonatomic, assign) CGSize size;
#else
@property (nonatomic, assign) NSSize size;
@property (nonatomic, nullable, strong) NSAppearance *appearance API_AVAILABLE(macos(10.14)) API_UNAVAILABLE(ios, tvos, watchos);
#endif

#if TARGET_OS_IPHONE
// Defaults to the device's screen scale
@property (nonatomic, assign) CGFloat scale API_DEPRECATED("Use traitCollection.displayScale", ios(7.0, API_TO_BE_DEPRECATED), tvos(9.2, API_TO_BE_DEPRECATED));
@property (nonatomic, copy) UITraitCollection *traitCollection API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(macos);
#endif

@end

NS_ASSUME_NONNULL_END

#endif
