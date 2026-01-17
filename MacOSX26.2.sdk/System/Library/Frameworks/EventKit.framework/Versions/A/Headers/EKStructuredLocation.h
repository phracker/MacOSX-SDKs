//
//  EKStructuredLocation.h
//  EventKit
//
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <EventKit/EventKitDefines.h>
#import <EventKit/EKObject.h>
#import <CoreLocation/CLLocation.h>

NS_ASSUME_NONNULL_BEGIN

@class MKMapItem;

NS_CLASS_AVAILABLE(10_8, 6_0)
@interface EKStructuredLocation : EKObject <NSCopying>

+ (instancetype)locationWithTitle:(NSString *)title;
+ (instancetype)locationWithMapItem:(MKMapItem *)mapItem NS_AVAILABLE(10_11, 9_0);

@property(nullable, nonatomic, strong) NSString     *title;
@property(nonatomic, strong, nullable) CLLocation   *geoLocation;
@property(nonatomic) double                radius; // 0 = use default, unit is meters

@end

NS_ASSUME_NONNULL_END
