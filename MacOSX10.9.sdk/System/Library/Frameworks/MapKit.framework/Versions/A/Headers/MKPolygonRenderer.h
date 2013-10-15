//
//  MKPolygonRenderer.h
//  MapKit
//
//  Copyright (c) 2013, Apple Inc. All rights reserved.
//

#import <MapKit/MKOverlayPathRenderer.h>
#import <MapKit/MKPolygon.h>

MK_CLASS_AVAILABLE(10_9, 7_0)
@interface MKPolygonRenderer : MKOverlayPathRenderer

- (id)initWithPolygon:(MKPolygon *)polygon;
@property (nonatomic, readonly) MKPolygon *polygon;

@end
