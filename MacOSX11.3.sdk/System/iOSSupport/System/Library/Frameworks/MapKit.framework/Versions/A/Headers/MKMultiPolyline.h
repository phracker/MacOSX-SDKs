//
//  MKMultiPolyline.h
//  MapKit
//
//  Copyright (c) 2019, Apple Inc. All rights reserved.
//

#import <MapKit/MKOverlay.h>
#import <MapKit/MKPolyline.h>
#import <MapKit/MKShape.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15)) API_UNAVAILABLE(watchos)
@interface MKMultiPolyline : MKShape <MKOverlay>

- (instancetype)initWithPolylines:(NSArray<MKPolyline *> *)polylines NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly, copy) NSArray<MKPolyline *> *polylines;

@end

NS_ASSUME_NONNULL_END
