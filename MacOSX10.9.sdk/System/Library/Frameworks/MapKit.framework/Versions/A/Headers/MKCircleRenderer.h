//
//  MKCircleRenderer.h
//  MapKit
//
//  Copyright (c) 2010-2013, Apple Inc. All rights reserved.
//

#import <MapKit/MKOverlayPathRenderer.h>
#import <MapKit/MKCircle.h>

MK_CLASS_AVAILABLE(10_9, 7_0)
@interface MKCircleRenderer : MKOverlayPathRenderer

- (id)initWithCircle:(MKCircle *)circle;

@property (nonatomic, readonly) MKCircle *circle;

@end
