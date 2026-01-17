//
//  MKUserTrackingBarButtonItem.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

#if MK_SUPPORTS_VIEW_CLASSES

#import <UIKit/UIBarButtonItem.h>

@class MKMapView;

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(NA, 5_0) API_UNAVAILABLE(tvos, watchos)
@interface MKUserTrackingBarButtonItem : UIBarButtonItem

- (instancetype)initWithMapView:(nullable MKMapView *)mapView NS_DESIGNATED_INITIALIZER;
@property (nonatomic, strong, nullable) MKMapView *mapView;

@end

NS_ASSUME_NONNULL_END

#endif // MK_SUPPORTS_VIEW_CLASSES
