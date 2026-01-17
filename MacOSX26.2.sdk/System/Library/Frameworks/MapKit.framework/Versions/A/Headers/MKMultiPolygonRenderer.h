//
//  MKMultiPolygonRenderer.h
//  MapKit
//
//  Copyright (c) 2019, Apple Inc. All rights reserved.
//

#import <MapKit/MKMultiPolygon.h>
#import <MapKit/MKOverlayPathRenderer.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15)) API_UNAVAILABLE(watchos)
@interface MKMultiPolygonRenderer : MKOverlayPathRenderer

- (instancetype)initWithMultiPolygon:(MKMultiPolygon *)multiPolygon;

@property (nonatomic, readonly) MKMultiPolygon *multiPolygon;

@end

NS_ASSUME_NONNULL_END
