//
//  MKMapItem.h
//  MapKit
//
//  Copyright 2011-2012, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKMapItemIdentifier.h>
#import <MapKit/MKPlacemark.h>
#import <MapKit/MKPointOfInterestCategory.h>
#import <MapKit/MKAddress.h>
#import <MapKit/MKAddressRepresentations.h>

#if TARGET_OS_IOS
@class UIScene;
#endif

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_9, 6_0) __TVOS_AVAILABLE(9_2)
@interface MKMapItem : NSObject

@property (nonatomic, nullable, readonly) MKMapItemIdentifier *identifier API_AVAILABLE(ios(18.0), visionos(2.0), tvos(18.0), macos(15.0), watchos(11.0));
@property (nonatomic, readonly) NSSet<MKMapItemIdentifier *> *alternateIdentifiers API_AVAILABLE(ios(18.0), visionos(2.0), tvos(18.0), macos(15.0), watchos(11.0));

// If this MKMapItem represents your current location (isCurrentLocation == YES), then placemark will be nil.
@property (nonatomic, readonly) MKPlacemark *placemark API_DEPRECATED("Use location, address and addressRepresentations instead", ios(6.0, 26.0), visionos(1.0, 26.0), tvos(9.2, 26.0), macos(10.9, 26.0), watchos(2.0, 26.0));

@property (nonatomic, readonly) BOOL isCurrentLocation;

@property (nonatomic, readonly) CLLocation *location API_AVAILABLE(ios(26.0), visionos(26.0), tvos(26.0), macos(26.0), watchos(26.0));
@property (nonatomic, readonly, nullable) MKAddress *address API_AVAILABLE(ios(26.0), visionos(26.0), tvos(26.0), macos(26.0), watchos(26.0));
@property (nonatomic, readonly, nullable) MKAddressRepresentations *addressRepresentations API_AVAILABLE(ios(26.0), visionos(26.0), tvos(26.0), macos(26.0), watchos(26.0));

@property (nonatomic, copy, nullable) NSString *name;
@property (nonatomic, copy, nullable) NSString *phoneNumber;

@property (nonatomic, strong, nullable) NSURL *url;

@property (nonatomic, copy, nullable) NSTimeZone *timeZone NS_AVAILABLE(10_11, 9_0);

@property (nonatomic, copy, nullable) MKPointOfInterestCategory pointOfInterestCategory API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0), watchos(6.0));

+ (MKMapItem *)mapItemForCurrentLocation;
- (instancetype)initWithPlacemark:(MKPlacemark *)placemark API_DEPRECATED("Use init(location:address:)", ios(6.0, 26.0), visionos(1.0, 26.0), tvos(9.2, 26.0), macos(10.9, 26.0), watchos(2.0, 26.0));



- (instancetype)initWithLocation:(CLLocation *)location address:(nullable MKAddress *)address API_AVAILABLE(ios(26.0), visionos(26.0), tvos(26.0), macos(26.0), watchos(26.0));

- (BOOL)openInMapsWithLaunchOptions:(nullable NSDictionary<NSString *, id> *)launchOptions API_UNAVAILABLE(tvos);
+ (BOOL)openMapsWithItems:(NSArray<MKMapItem *> *)mapItems launchOptions:(nullable NSDictionary<NSString *, id> *)launchOptions API_UNAVAILABLE(tvos);

#if TARGET_OS_IOS
// fromScene is used to indicate the UIScene where the user interaction took place.
- (void)openInMapsWithLaunchOptions:(nullable NSDictionary<NSString *, id> *)launchOptions fromScene:(nullable UIScene *)scene completionHandler:(void (^__nullable)(BOOL success))completion API_AVAILABLE(ios(13.2)) API_UNAVAILABLE(watchos, tvos, macos);
+ (void)openMapsWithItems:(NSArray<MKMapItem *> *)mapItems launchOptions:(nullable NSDictionary<NSString *, id> *)launchOptions fromScene:(nullable UIScene *)scene completionHandler:(void (^__nullable)(BOOL success))completion API_AVAILABLE(ios(13.2)) API_UNAVAILABLE(watchos, tvos, macos);
#elif TARGET_OS_OSX
- (void)openInMapsWithLaunchOptions:(nullable NSDictionary<NSString *, id> *)launchOptions completionHandler:(void (^__nullable)(BOOL success))completion API_AVAILABLE(macos(14.4)) API_UNAVAILABLE(ios, watchos, tvos);
+ (void)openMapsWithItems:(NSArray<MKMapItem *> *)mapItems launchOptions:(nullable NSDictionary<NSString *, id> *)launchOptions completionHandler:( void (^__nullable)(BOOL success))completion API_AVAILABLE(macos(14.4)) API_UNAVAILABLE(ios, watchos, tvos);
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
MK_EXTERN NSString * const MKLaunchOptionsDirectionsModeCycling API_AVAILABLE(ios(14.0), macos(11.0), watchos(7.0), visionos(1.0)) API_UNAVAILABLE(tvos);

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
