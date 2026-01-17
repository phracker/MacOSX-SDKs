//
//  MKMultiPoint.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKShape.h>
#import <MapKit/MKGeometry.h>
#import <MapKit/MKTypes.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.9), ios(4.0), tvos(9.2), watchos(1.0))
@interface MKMultiPoint : MKShape

- (MKMapPoint *)points NS_RETURNS_INNER_POINTER;
@property (nonatomic, readonly) NSUInteger pointCount;

// Unproject and copy points into the provided array of coordinates that
// must be large enough to hold range.length coordinates.
- (void)getCoordinates:(CLLocationCoordinate2D *)coords range:(NSRange)range;

// Conveniences for determining the location/fraction (0.0 -> 1.0) distance-wise
// at which a point or set of points exists on the shape
- (CGFloat)locationAtPointIndex:(NSUInteger)index API_AVAILABLE(ios(14.0), tvos(14.0), macos(11.0), watchos(7.0));
- (NSArray<NSNumber *> *)locationsAtPointIndexes:(NSIndexSet *)indexes NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(14.0), tvos(14.0), macos(11.0), watchos(7.0));

@end

NS_ASSUME_NONNULL_END
