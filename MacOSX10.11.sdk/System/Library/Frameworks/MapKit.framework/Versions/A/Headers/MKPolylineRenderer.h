//
//  MKPolylineRenderer.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKOverlayPathRenderer.h>
#import <MapKit/MKPolyline.h>

NS_ASSUME_NONNULL_BEGIN

MK_CLASS_AVAILABLE(10_9, 7_0) __WATCHOS_PROHIBITED
@interface MKPolylineRenderer : MKOverlayPathRenderer

- (instancetype)initWithPolyline:(MKPolyline *)polyline;

@property (nonatomic, readonly) MKPolyline *polyline;

@end

NS_ASSUME_NONNULL_END
