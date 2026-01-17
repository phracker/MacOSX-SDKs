//
//  MKCompassButton.h
//  MapKit
//
//  Copyright © 2017 Apple, Inc. All rights reserved.
//

#import <UIKit/UIView.h>
#import <MapKit/MKTypes.h>

@class MKMapView;

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_IOS(11_0) __TVOS_UNAVAILABLE
@interface MKCompassButton : UIView

+ (instancetype)compassButtonWithMapView:(nullable MKMapView *)mapView;
@property (nonatomic, nullable, weak) MKMapView *mapView;
@property (nonatomic, assign) MKFeatureVisibility compassVisibility;

@end

NS_ASSUME_NONNULL_END
