//
//  MKMapItem.h
//  MapKit
//
//  Copyright 2011-2012, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKPlacemark.h>

NS_ASSUME_NONNULL_BEGIN

MK_CLASS_AVAILABLE(10_9, 6_0)
@interface MKMapItem : NSObject

// If this MKMapItem represents your current location (isCurrentLocation == YES), then placemark will be nil.
@property (nonatomic, readonly) MKPlacemark *placemark;
@property (nonatomic, readonly) BOOL isCurrentLocation;

@property (nonatomic, copy, nullable) NSString *name;
@property (nonatomic, copy, nullable) NSString *phoneNumber;

@property (nonatomic, strong, nullable) NSURL *url;

@property (nonatomic, copy, nullable) NSTimeZone *timeZone NS_AVAILABLE(10_11, 9_0);

+ (MKMapItem *)mapItemForCurrentLocation;
- (instancetype)initWithPlacemark:(MKPlacemark *)placemark;

- (BOOL)openInMapsWithLaunchOptions:(nullable NSDictionary<NSString *, id> *)launchOptions;
+ (BOOL)openMapsWithItems:(NSArray<MKMapItem *> *)mapItems launchOptions:(nullable NSDictionary<NSString *, id> *)launchOptions;

@end

MK_EXTERN NSString * const MKLaunchOptionsDirectionsModeKey     NS_AVAILABLE(10_9, 6_0); // Key to a directions mode
MK_EXTERN NSString * const MKLaunchOptionsMapTypeKey            NS_AVAILABLE(10_9, 6_0) __WATCHOS_PROHIBITED; // Key to an NSNumber corresponding to a MKMapType
MK_EXTERN NSString * const MKLaunchOptionsShowsTrafficKey       NS_AVAILABLE(10_9, 6_0) __WATCHOS_PROHIBITED; // Key to a boolean NSNumber

// Directions modes
MK_EXTERN NSString * const MKLaunchOptionsDirectionsModeDriving NS_AVAILABLE(10_9, 6_0);
MK_EXTERN NSString * const MKLaunchOptionsDirectionsModeWalking NS_AVAILABLE(10_9, 6_0);
MK_EXTERN NSString * const MKLaunchOptionsDirectionsModeTransit NS_AVAILABLE(10_11, 9_0);

// If center and span are present, having a camera as well is undefined
MK_EXTERN NSString * const MKLaunchOptionsMapCenterKey          NS_AVAILABLE(10_9, 6_0); // Key to an NSValue-encoded CLLocationCoordinate2D
MK_EXTERN NSString * const MKLaunchOptionsMapSpanKey            NS_AVAILABLE(10_9, 6_0); // Key to an NSValue-encoded MKCoordinateSpan

MK_EXTERN NSString * const MKLaunchOptionsCameraKey             NS_AVAILABLE(10_10, 7_1); // Key to MKMapCamera object

NS_ASSUME_NONNULL_END
