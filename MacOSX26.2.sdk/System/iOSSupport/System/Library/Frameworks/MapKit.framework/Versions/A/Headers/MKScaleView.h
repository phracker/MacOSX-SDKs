//
//  MKScaleView.h
//  Maps
//
//  Copyright 2017, Apple. All rights reserved.
//

#import <MapKit/MKFoundation.h>

#if MK_SUPPORTS_VIEW_CLASSES

// System
#import <UIKit/UIKit.h>
#import <MapKit/MKTypes.h>

@class MKMapView;

typedef NS_ENUM(NSInteger, MKScaleViewAlignment) {
    MKScaleViewAlignmentLeading,
    MKScaleViewAlignmentTrailing,
    MKScaleViewAlignmentCenter API_AVAILABLE(ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos)
} API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos)
@interface MKScaleView : UIView

+ (instancetype)scaleViewWithMapView:(nullable MKMapView *)mapView;
@property (nonatomic, nullable, weak) MKMapView *mapView;

@property (nonatomic, assign) MKFeatureVisibility scaleVisibility;
@property (nonatomic, assign) MKScaleViewAlignment legendAlignment;

@end

NS_ASSUME_NONNULL_END

#endif // MK_SUPPORTS_VIEW_CLASSES
