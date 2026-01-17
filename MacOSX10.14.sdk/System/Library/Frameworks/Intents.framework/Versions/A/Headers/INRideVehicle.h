//
//  INRideVehicle.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CLLocation;
@class INImage;

API_AVAILABLE(ios(10.0), watchos(3.0))
API_UNAVAILABLE(macosx)
@interface INRideVehicle : NSObject <NSCopying, NSSecureCoding>

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) CLLocation *location; // The course of this location is significant; see below.

@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *registrationPlate;
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *manufacturer;
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *model;
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INImage *mapAnnotationImage; // An image suitable for display as a map annotation. Will be centered at the coordinate provided through the .vehicleLocation property, and rotated to match that location's course.

@end
