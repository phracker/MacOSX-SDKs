//
//  MKCircleRenderer.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKOverlayPathRenderer.h>
#import <MapKit/MKCircle.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_9, 7_0) __TVOS_AVAILABLE(9_2) API_UNAVAILABLE(watchos)
@interface MKCircleRenderer : MKOverlayPathRenderer

- (instancetype)initWithCircle:(MKCircle *)circle;

@property (nonatomic, readonly) MKCircle *circle;

/* These values define the subregion of the path used to draw the
 * stroke. The values must be in the range [0,1] with zero
 * representing North, and positive values increasing in the clockwise direction.
 * strokeStart defaults to 0 and strokeEnd to 1
 */
@property (nonatomic, assign) CGFloat strokeStart API_AVAILABLE(ios(14.0), tvos(14.0), macos(11.0)) API_UNAVAILABLE(watchos);
@property (nonatomic, assign) CGFloat strokeEnd API_AVAILABLE(ios(14.0), tvos(14.0), macos(11.0)) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END
