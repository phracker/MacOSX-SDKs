//
//  EKStructuredLocation.h
//  EventKit
//
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <EventKit/EventKitDefines.h>
#import <EventKit/EKObject.h>
#import <CoreLocation/CLLocation.h>

EVENTKIT_CLASS_AVAILABLE(10_8, 6_0)
@interface EKStructuredLocation : EKObject <NSCopying> {
}

+ (EKStructuredLocation *)locationWithTitle:(NSString *)title;

@property(nonatomic, retain) NSString     *title;
@property(nonatomic, retain) CLLocation   *geoLocation;
@property(nonatomic) double                radius; // 0 = use default, unit is meters

@end
