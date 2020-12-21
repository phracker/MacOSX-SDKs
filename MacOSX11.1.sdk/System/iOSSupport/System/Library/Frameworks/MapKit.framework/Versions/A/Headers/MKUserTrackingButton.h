//
//  MKUserTrackingButton.h
//  MapKit
//
//  Copyright © 2017 Apple, Inc. All rights reserved.
//

#import <UIKit/UIView.h>

@class MKMapView;

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_IOS(11_0) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos)
@interface MKUserTrackingButton : UIView

+ (instancetype)userTrackingButtonWithMapView:(nullable MKMapView *)mapView;
@property (nonatomic, nullable, weak) MKMapView *mapView;

@end

NS_ASSUME_NONNULL_END
