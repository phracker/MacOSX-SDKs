//
//  MKPolylineRenderer.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKOverlayPathRenderer.h>
#import <MapKit/MKPolyline.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_9, 7_0) __TVOS_AVAILABLE(9_2) API_UNAVAILABLE(watchos)
@interface MKPolylineRenderer : MKOverlayPathRenderer

- (instancetype)initWithPolyline:(MKPolyline *)polyline;

@property (nonatomic, readonly) MKPolyline *polyline;

/* These values define the subregion of the path used to draw the
 * polyline. The values must be in the range [0,1] with zero
 * representing the start of the polyline and one the end. Values in
 * between zero and one are interpolated linearly along the polyline
 * length. strokeStart defaults to 0 and strokeEnd to 1
 */
@property (nonatomic, assign) CGFloat strokeStart API_AVAILABLE(ios(14.0), tvos(14.0), macos(11.0)) API_UNAVAILABLE(watchos);
@property (nonatomic, assign) CGFloat strokeEnd API_AVAILABLE(ios(14.0), tvos(14.0), macos(11.0)) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END
