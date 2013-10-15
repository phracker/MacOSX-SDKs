//
//  MKOverlay.h
//  MapKit
//
//  Copyright (c) 2010-2013, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKAnnotation.h>
#import <MapKit/MKTypes.h>
#import <MapKit/MKGeometry.h>

@protocol MKOverlay <MKAnnotation>
@required

// From MKAnnotation, for areas this should return the centroid of the area.
@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;

// boundingMapRect should be the smallest rectangle that completely contains the overlay.
// For overlays that span the 180th meridian, boundingMapRect should have either a negative MinX or a MaxX that is greater than MKMapSizeWorld.width.
@property (nonatomic, readonly) MKMapRect boundingMapRect;

@optional
// Implement intersectsMapRect to provide more precise control over when the view for the overlay should be shown.
// If omitted, MKMapRectIntersectsRect([overlay boundingRect], mapRect) will be used instead.
- (BOOL)intersectsMapRect:(MKMapRect)mapRect;

// If this method is implemented and returns YES, MKMapView may use it as a hint to skip loading or drawing the built in map content in the area covered by this overlay.
- (BOOL)canReplaceMapContent NS_AVAILABLE(10_9, 7_0);

@end
