//
//  MKPolylineRenderer.h
//  MapKit
//
//  Copyright (c) 2013, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKOverlayPathRenderer.h>
#import <MapKit/MKPolyline.h>

MK_CLASS_AVAILABLE(10_9, 7_0)
@interface MKPolylineRenderer : MKOverlayPathRenderer

- (id)initWithPolyline:(MKPolyline *)polyline;

@property (nonatomic, readonly) MKPolyline *polyline;

@end
