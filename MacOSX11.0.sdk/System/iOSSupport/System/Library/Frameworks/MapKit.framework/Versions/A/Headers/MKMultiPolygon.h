//
//  MKMultiPolygon.h
//  MapKit
//
//  Copyright (c) 2019, Apple Inc. All rights reserved.
//

#import <MapKit/MKOverlay.h>
#import <MapKit/MKPolygon.h>
#import <MapKit/MKShape.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15)) API_UNAVAILABLE(watchos)
@interface MKMultiPolygon : MKShape <MKOverlay>

- (instancetype)initWithPolygons:(NSArray<MKPolygon *> *)polygons NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly, copy) NSArray<MKPolygon *> *polygons;

@end

NS_ASSUME_NONNULL_END
