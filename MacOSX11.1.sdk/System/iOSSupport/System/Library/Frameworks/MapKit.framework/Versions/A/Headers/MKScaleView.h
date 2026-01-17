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
} NS_AVAILABLE_IOS(11_0) __TVOS_AVAILABLE(11_0);

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE_IOS(11_0) __TVOS_AVAILABLE(11_0)
@interface MKScaleView : UIView

+ (instancetype)scaleViewWithMapView:(nullable MKMapView *)mapView;
@property (nonatomic, nullable, weak) MKMapView *mapView;

@property (nonatomic, assign) MKFeatureVisibility scaleVisibility;
@property (nonatomic, assign) MKScaleViewAlignment legendAlignment;

@end

NS_ASSUME_NONNULL_END

#endif // MK_SUPPORTS_VIEW_CLASSES
