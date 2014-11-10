//
//  MKTileOverlayRenderer.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKOverlayRenderer.h>
#import <MapKit/MKTileOverlay.h>

MK_CLASS_AVAILABLE(10_9, 7_0)
@interface MKTileOverlayRenderer : MKOverlayRenderer

- (instancetype)initWithTileOverlay:(MKTileOverlay *)overlay;

- (void)reloadData;

@end
