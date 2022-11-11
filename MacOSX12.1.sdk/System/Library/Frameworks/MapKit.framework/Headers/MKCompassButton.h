//
//  MKCompassButton.h
//  MapKit
//
//  Copyright © 2017 Apple, Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKTypes.h>

#if MK_SUPPORTS_VIEW_CLASSES

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif

@class MKMapView;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11), macos(11.0), macCatalyst(13.0)) API_UNAVAILABLE(watchos, tvos)
#if TARGET_OS_IPHONE
@interface MKCompassButton : UIView
#else
@interface MKCompassButton : NSView
#endif

+ (instancetype)compassButtonWithMapView:(nullable MKMapView *)mapView;
@property (nonatomic, nullable, weak) MKMapView *mapView;
@property (nonatomic, assign) MKFeatureVisibility compassVisibility;

@end

NS_ASSUME_NONNULL_END

#endif
