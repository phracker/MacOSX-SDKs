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
    MKMapTypeMutedStandard NS_ENUM_AVAILABLE(10_13, 11_0) __TVOS_AVAILABLE(11_0),
} NS_ENUM_AVAILABLE(10_9, 3_0) __TVOS_AVAILABLE(9_2) API_UNAVAILABLE(watchos);

MK_EXTERN NSString *MKErrorDomain __TVOS_AVAILABLE(9_2);

typedef NS_ENUM(NSUInteger, MKErrorCode) {
    MKErrorUnknown = 1,
    MKErrorServerFailure,
    MKErrorLoadingThrottled,
    MKErrorPlacemarkNotFound,
    MKErrorDirectionsNotFound NS_ENUM_AVAILABLE(10_9, 7_0),
    MKErrorDecodingFailed API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15)) API_UNAVAILABLE(watchos),
} NS_ENUM_AVAILABLE(10_9, 3_0) __TVOS_AVAILABLE(9_2) API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, MKFeatureVisibility) {
    MKFeatureVisibilityAdaptive,
    MKFeatureVisibilityHidden,
    MKFeatureVisibilityVisible
} API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(macos, watchos);

NS_ASSUME_NONNULL_END
