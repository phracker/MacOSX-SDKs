//
//  MKMultiPolylineRenderer.h
//  MapKit
//
//  Copyright (c) 2019, Apple Inc. All rights reserved.
//

#import <MapKit/MKMultiPolyline.h>
#import <MapKit/MKOverlayPathRenderer.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15)) API_UNAVAILABLE(watchos)
@interface MKMultiPolylineRenderer : MKOverlayPathRenderer

- (instancetype)initWithMultiPolyline:(MKMultiPolyline *)multiPolyline;

@property (nonatomic, readonly) MKMultiPolyline *multiPolyline;

@end

NS_ASSUME_NONNULL_END
