//
//  MKUserTrackingButton.h
//  MapKit
//
//  Copyright © 2017 Apple, Inc. All rights reserved.
//

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif

@class MKMapView;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, macos, watchos)
#if TARGET_OS_IPHONE
@interface MKUserTrackingButton : UIView
#else
@interface MKUserTrackingButton : NSView
#endif

+ (instancetype)userTrackingButtonWithMapView:(nullable MKMapView *)mapView;
@property (nonatomic, nullable, weak) MKMapView *mapView;

@end

NS_ASSUME_NONNULL_END
