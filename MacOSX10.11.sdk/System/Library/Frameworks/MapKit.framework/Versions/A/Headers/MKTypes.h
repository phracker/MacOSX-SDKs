//
//  MKTypes.h
//  MapKit
//
//  Copyright (c) 2009-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, MKMapType) {
    MKMapTypeStandard = 0,
    MKMapTypeSatellite,
    MKMapTypeHybrid,
    MKMapTypeSatelliteFlyover NS_ENUM_AVAILABLE(10_11, 9_0),
    MKMapTypeHybridFlyover NS_ENUM_AVAILABLE(10_11, 9_0),
} NS_ENUM_AVAILABLE(10_9, 3_0) __WATCHOS_PROHIBITED;

MK_EXTERN NSString *MKErrorDomain;

typedef NS_ENUM(NSUInteger, MKErrorCode) {
    MKErrorUnknown = 1,
    MKErrorServerFailure,
    MKErrorLoadingThrottled,
    MKErrorPlacemarkNotFound,
    MKErrorDirectionsNotFound NS_ENUM_AVAILABLE(10_9, 7_0)
} NS_ENUM_AVAILABLE(10_9, 3_0) __WATCHOS_PROHIBITED;

NS_ASSUME_NONNULL_END
