//
//  MKMapItem.h
//  MapKit
//
//  Copyright 2011-2012, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKPlacemark.h>
#import <MapKit/MKPointOfInterestCategory.h>

#if TARGET_OS_IOS
@class UIScene;
#endif

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_9, 6_0) __TVOS_AVAILABLE(9_2)
@interface MKMapItem : NSObject

// If this MKMapItem represents your current location (isCurrentLocation == YES), then placemark will be nil.
@property (nonatomic, readonly) MKPlacemark *placemark;
@property (nonatomic, readonly) BOOL isCurrentLocation;

@property (nonatomic, copy, nullable) NSString *name;
@property (nonatomic, copy, nullable) NSString *phoneNumber;

@property (nonatomic, strong, nullable) NSURL *url;

@property (nonatomic, copy, nullable) NSTimeZone *timeZone NS_AVAILABLE(10_11, 9_0);

@property (nonatomic, copy, nullable) MKPointOfInterestCategory pointOfInterestCategory API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0)) API_UNAVAILABLE(watchos);

+ (MKMapItem *)mapItemForCurrentLocation;
- (instancetype)initWithPlacemark:(MKPlacemark *)placemark;

- (BOOL)openInMapsWithLaunchOptions:(nullable NSDictionary<NSString *, id> *)launchOptions API_UNAVAILABLE(tvos);
+ (BOOL)openMapsWithItems:(NSArray<MKMapItem *> *)mapItems launchOptions:(nullable NSDictionary<NSString *, id> *)launchOptions API_UNAVAILABLE(tvos);

#if TARGET_OS_IOS
// fromScene is used to indicate the UIScene where the user interaction took place.
- (void)openInMapsWithLaunchOptions:(nullable NSDictionary<NSString *, id> *)launchOptions fromScene:(nullable UIScene *)scene completionHandler:(void (^__nullable)(BOOL success))completion API_AVAILABLE(ios(13.2)) API_UNAVAILABLE(watchos, tvos, macos);
+ (void)openMapsWithItems:(NSArray<MKMapItem *> *)mapItems launchOptions:(nullable NSDictionary<NSString *, id> *)launchOptions fromScene:(nullable UIScene *)scene completionHandler:(void (^__nullable)(BOOL success))completion API_AVAILABLE(ios(13.2)) API_UNAVAILABLE(watchos, tvos, macos);
#endif

@end

MK_EXTERN NSString * const MKLaunchOptionsDirectionsModeKey     NS_AVAILABLE(10_9, 6_0) API_UNAVAILABLE(tvos); // Key to a directions mode
MK_EXTERN NSString * const MKLaunchOptionsMapTypeKey            NS_AVAILABLE(10_9, 6_0) API_UNAVAILABLE(tvos, watchos); // Key to an NSNumber corresponding to a MKMapType
MK_EXTERN NSString * const MKLaunchOptionsShowsTrafficKey       NS_AVAILABLE(10_9, 6_0) API_UNAVAILABLE(tvos, watchos); // Key to a boolean NSNumber

// Directions modes
MK_EXTERN NSString * const MKLaunchOptionsDirectionsModeDefault NS_AVAILABLE(10_12, 10_0) __WATCHOS_AVAILABLE(3_0) API_UNAVAILABLE(tvos); // Will pick the best directions mode, given the user's preferences
MK_EXTERN NSString * const MKLaunchOptionsDirectionsModeDriving NS_AVAILABLE(10_9, 6_0) API_UNAVAILABLE(tvos);
MK_EXTERN NSString * const MKLaunchOptionsDirectionsModeWalking NS_AVAILABLE(10_9, 6_0) API_UNAVAILABLE(tvos);
MK_EXTERN NSString * const MKLaunchOptionsDirectionsModeTransit NS_AVAILABLE(10_11, 9_0) API_UNAVAILABLE(tvos);

// If center and span are present, having a camera as well is undefined
MK_EXTERN NSString * const MKLaunchOptionsMapCenterKey          NS_AVAILABLE(10_9, 6_0) API_UNAVAILABLE(tvos); // Key to an NSValue-encoded CLLocationCoordinate2D
MK_EXTERN NSString * const MKLaunchOptionsMapSpanKey            NS_AVAILABLE(10_9, 6_0) API_UNAVAILABLE(tvos); // Key to an NSValue-encoded MKCoordinateSpan

MK_EXTERN NSString * const MKLaunchOptionsCameraKey             NS_AVAILABLE(10_10, 7_1) API_UNAVAILABLE(tvos); // Key to MKMapCamera object


@interface MKMapItem (MKMapItemSerialization) <NSSecureCoding>
@end

MK_EXTERN NSString * const MKMapItemTypeIdentifier NS_AVAILABLE(10_13, 11_0);


#if TARGET_OS_IOS
@interface MKMapItem (MKMapItemDragAndDropSupport) <NSItemProviderReading, NSItemProviderWriting>
@end
#endif

NS_ASSUME_NONNULL_END
