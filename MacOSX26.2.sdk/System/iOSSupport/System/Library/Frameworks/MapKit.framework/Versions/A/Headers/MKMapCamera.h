//
//  MKMapCamera.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MapKit/MKFoundation.h>
#import <CoreLocation/CoreLocation.h>
#import <CoreGraphics/CoreGraphics.h>

@class MKMapItem;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.2), watchos(1.0))
@interface MKMapCamera : NSObject <NSSecureCoding, NSCopying>

@property (nonatomic) CLLocationCoordinate2D centerCoordinate;
@property (nonatomic) CLLocationDistance centerCoordinateDistance API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));
@property (nonatomic) CLLocationDirection heading;
@property (nonatomic) CGFloat pitch; // In degrees where 0 is looking straight down. Pitch may be clamped to an appropriate value.
@property (nonatomic) CLLocationDistance altitude API_DEPRECATED("Use centerCoordinateDistance", ios(7.0, API_TO_BE_DEPRECATED), macos(10.9, API_TO_BE_DEPRECATED), tvos(9.2, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(watchos);

+ (instancetype)camera;

+ (instancetype)cameraLookingAtCenterCoordinate:(CLLocationCoordinate2D)centerCoordinate
                              fromEyeCoordinate:(CLLocationCoordinate2D)eyeCoordinate
                                    eyeAltitude:(CLLocationDistance)eyeAltitude;

+ (instancetype)cameraLookingAtCenterCoordinate:(CLLocationCoordinate2D)centerCoordinate
                                   fromDistance:(CLLocationDistance)distance
                                          pitch:(CGFloat)pitch
                                        heading:(CLLocationDirection)heading NS_AVAILABLE(10_11, 9_0);

+ (instancetype)cameraLookingAtMapItem:(MKMapItem *)mapItem
                           forViewSize:(CGSize)viewSize
                            allowPitch:(BOOL)allowPitch API_AVAILABLE(ios(16.0), macos(13.0), tvos(16.0), watchos(9.0));

@end

NS_ASSUME_NONNULL_END
