//
//  MKTypes.h
//  MapKit
//
//  Copyright (c) 2009-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

typedef NS_ENUM(NSUInteger, MKMapType) {
    MKMapTypeStandard = 0,
    MKMapTypeSatellite,
    MKMapTypeHybrid
} NS_ENUM_AVAILABLE(10_9, 3_0);

MK_EXTERN NSString *MKErrorDomain;

typedef NS_ENUM(NSUInteger, MKErrorCode) {
    MKErrorUnknown = 1,
    MKErrorServerFailure,
    MKErrorLoadingThrottled,
    MKErrorPlacemarkNotFound,
    MKErrorDirectionsNotFound NS_ENUM_AVAILABLE(10_9, 7_0)
} NS_ENUM_AVAILABLE(10_9, 3_0);

