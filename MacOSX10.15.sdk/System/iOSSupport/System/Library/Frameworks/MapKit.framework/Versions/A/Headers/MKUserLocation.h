//
//  MKUserLocation.h
//  MapKit
//
//  Copyright (c) 2009-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKAnnotation.h>

@class CLLocation;
@class MKUserLocationInternal;

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_9, 3_0) __TVOS_AVAILABLE(9_2) API_UNAVAILABLE(watchos)
@interface MKUserLocation : NSObject <MKAnnotation>

// Returns YES if the user's location is being updated.
@property (readonly, nonatomic, getter=isUpdating) BOOL updating;

// Returns nil if the owning MKMapView's showsUserLocation is NO or the user's location has yet to be determined.
@property (readonly, nonatomic, nullable) CLLocation *location;

// Returns nil if not in MKUserTrackingModeFollowWithHeading
@property (readonly, nonatomic, nullable) CLHeading *heading NS_AVAILABLE(10_9, 5_0) API_UNAVAILABLE(tvos);

// The title to be displayed for the user location annotation.
@property (nonatomic, copy, nullable) NSString *title;

// The subtitle to be displayed for the user location annotation.
@property (nonatomic, copy, nullable) NSString *subtitle;

@end

NS_ASSUME_NONNULL_END
