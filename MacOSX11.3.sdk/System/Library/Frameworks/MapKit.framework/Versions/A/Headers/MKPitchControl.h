//
//  MKPitchControl.h
//  MapKit
//
//  Created by Sean Meiners on 2/24/20.
//  Copyright © 2020 Apple, Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

#if MK_SUPPORTS_VIEW_CLASSES

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif

@class MKMapView;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(ios, watchos, tvos)
#if TARGET_OS_IPHONE
@interface MKPitchControl : UIView
#else
@interface MKPitchControl : NSView
#endif

+ (instancetype)pitchControlWithMapView:(nullable MKMapView *)mapView;
@property (nonatomic, nullable, weak) MKMapView *mapView;

@end

NS_ASSUME_NONNULL_END

#endif // MK_SUPPORTS_VIEW_CLASSES
