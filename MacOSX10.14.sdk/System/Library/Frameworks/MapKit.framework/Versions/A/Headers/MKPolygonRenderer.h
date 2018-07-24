//
//  MKPolygonRenderer.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKOverlayPathRenderer.h>
#import <MapKit/MKPolygon.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_9, 7_0) __TVOS_AVAILABLE(9_2) __WATCHOS_PROHIBITED
@interface MKPolygonRenderer : MKOverlayPathRenderer

- (instancetype)initWithPolygon:(MKPolygon *)polygon;
@property (nonatomic, readonly) MKPolygon *polygon;

@end

NS_ASSUME_NONNULL_END
