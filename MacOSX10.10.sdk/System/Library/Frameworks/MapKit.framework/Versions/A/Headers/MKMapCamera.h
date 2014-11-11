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

MK_CLASS_AVAILABLE(10_9, 7_0)
@interface MKMapCamera : NSObject <NSSecureCoding, NSCopying>

@property (nonatomic) CLLocationCoordinate2D centerCoordinate;
@property (nonatomic) CLLocationDirection heading;
@property (nonatomic) CGFloat pitch; // In degrees where 0 is looking straight down. Pitch may be clamped to an appropriate value.
@property (nonatomic) CLLocationDistance altitude;

+ (instancetype)camera;

+ (instancetype)cameraLookingAtCenterCoordinate:(CLLocationCoordinate2D)centerCoordinate
                              fromEyeCoordinate:(CLLocationCoordinate2D)eyeCoordinate
                                    eyeAltitude:(CLLocationDistance)eyeAltitude;

@end
