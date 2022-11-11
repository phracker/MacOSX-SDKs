//
//  MKMapCameraBoundary.h
//  MapKit
//
//  Copyright © 2018 Apple, Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKGeometry.h>

#if MK_SUPPORTS_VIEW_CLASSES

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0)) API_UNAVAILABLE(watchos)
@interface MKMapCameraBoundary : NSObject <NSSecureCoding, NSCopying>

- (nullable instancetype)initWithMapRect:(MKMapRect)mapRect NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoordinateRegion:(MKCoordinateRegion)region NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(nonnull NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly) MKMapRect mapRect;
@property (nonatomic, readonly) MKCoordinateRegion region;

@end

NS_ASSUME_NONNULL_END

#endif
