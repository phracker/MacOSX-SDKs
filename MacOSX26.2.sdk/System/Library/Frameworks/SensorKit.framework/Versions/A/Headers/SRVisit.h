//
//  SRVisit.h
//  SensorKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <SensorKit/SRDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, SRLocationCategory) {
    SRLocationCategoryUnknown,
    SRLocationCategoryHome,
    SRLocationCategoryWork,
    SRLocationCategorySchool,
    SRLocationCategoryGym,
} API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, macos, visionos) API_UNAVAILABLE(tvos);

SR_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, visionos) API_UNAVAILABLE(tvos, macos)
@interface SRVisit : NSObject

/// The distance between the location of interest to home
@property (readonly) CLLocationDistance distanceFromHome;

/// The range of time the arrival to a location of interest occurred
@property (readonly, strong) NSDateInterval *arrivalDateInterval;

/// The range of time the departure from a location of interest occurred
@property (readonly, strong) NSDateInterval *departureDateInterval;

@property (readonly) SRLocationCategory locationCategory;

/// An identifier for the location of interest.
/// This can be used to identify the same location regardless of type
@property (readonly, strong) NSUUID *identifier;

@end

NS_ASSUME_NONNULL_END
