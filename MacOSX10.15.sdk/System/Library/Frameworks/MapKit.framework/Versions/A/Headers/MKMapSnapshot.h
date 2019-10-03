//
//  MKMapSnapshot.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKGeometry.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIImage.h>
#else
#import <AppKit/AppKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_9, 7_0) __TVOS_AVAILABLE(9_2) API_UNAVAILABLE(watchos)
@interface MKMapSnapshot : NSObject

#if TARGET_OS_IPHONE
@property (nonatomic, readonly) UIImage *image;
- (CGPoint)pointForCoordinate:(CLLocationCoordinate2D)coordinate;
@property (nonatomic, readonly) UITraitCollection *traitCollection API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(macos);
#else
@property (nonatomic, readonly) NSImage *image;
@property (nonatomic, readonly) NSAppearance *appearance API_AVAILABLE(macos(10.14)) API_UNAVAILABLE(ios, tvos, watchos);
- (NSPoint)pointForCoordinate:(CLLocationCoordinate2D)coordinate;
#endif

@end

NS_ASSUME_NONNULL_END
