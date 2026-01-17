//
//  MKTileOverlayRenderer.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKOverlayRenderer.h>
#import <MapKit/MKTileOverlay.h>

NS_ASSUME_NONNULL_BEGIN

MK_CLASS_AVAILABLE(10_9, 7_0) __WATCHOS_PROHIBITED
@interface MKTileOverlayRenderer : MKOverlayRenderer

- (instancetype)initWithTileOverlay:(MKTileOverlay *)overlay;

- (void)reloadData;

@end

NS_ASSUME_NONNULL_END
