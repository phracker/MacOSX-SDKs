//
//  MKMapCameraZoomRange.h
//  MapKit
//
//  Copyright © 2018 Apple, Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

#if MK_SUPPORTS_VIEW_CLASSES

#import <CoreLocation/CoreLocation.h>

MK_EXTERN const CLLocationDistance MKMapCameraZoomDefault API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0)) API_UNAVAILABLE(watchos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0)) API_UNAVAILABLE(watchos)
@interface MKMapCameraZoomRange : NSObject <NSSecureCoding, NSCopying>

- (nullable instancetype)initWithMinCenterCoordinateDistance:(CLLocationDistance)minDistance maxCenterCoordinateDistance:(CLLocationDistance)maxDistance NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithMinCenterCoordinateDistance:(CLLocationDistance)minDistance;
- (nullable instancetype)initWithMaxCenterCoordinateDistance:(CLLocationDistance)maxDistance;

@property (nonatomic, readonly) CLLocationDistance minCenterCoordinateDistance;
@property (nonatomic, readonly) CLLocationDistance maxCenterCoordinateDistance;

@end

NS_ASSUME_NONNULL_END

#endif
