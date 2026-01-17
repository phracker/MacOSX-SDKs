//
//  MKOverlayRenderer.h
//  MapKit
//
//  Copyright (c) 2010-2013, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKGeometry.h>
#import <MapKit/MKOverlay.h>

MK_CLASS_AVAILABLE(10_9, 7_0)
@interface MKOverlayRenderer : NSObject

- (id)initWithOverlay:(id <MKOverlay>)overlay;

@property (nonatomic, readonly) id <MKOverlay> overlay;

// Convert points relative to this view to absolute MKMapPoints
- (CGPoint)pointForMapPoint:(MKMapPoint)mapPoint;
- (MKMapPoint)mapPointForPoint:(CGPoint)point;

- (CGRect)rectForMapRect:(MKMapRect)mapRect;
- (MKMapRect)mapRectForRect:(CGRect)rect;

// Return YES if the renderer is currently ready to draw in the specified rect.
// Return NO if the renderer will not draw in the specified rect or if the
// data necessary to draw in the specified rect is not available.  In the 
// case where the renderer may want to draw in the specified rect but the data is
// not available, use setNeedsDisplayInMapRect:zoomLevel: to signal when the
// data does become available.
- (BOOL)canDrawMapRect:(MKMapRect)mapRect
             zoomScale:(MKZoomScale)zoomScale;

- (void)drawMapRect:(MKMapRect)mapRect
          zoomScale:(MKZoomScale)zoomScale
          inContext:(CGContextRef)context;

- (void)setNeedsDisplay;

- (void)setNeedsDisplayInMapRect:(MKMapRect)mapRect;     

- (void)setNeedsDisplayInMapRect:(MKMapRect)mapRect
                       zoomScale:(MKZoomScale)zoomScale;

@property CGFloat alpha;

@property (readonly) CGFloat contentScaleFactor;

@end

// Road widths are typically not drawn to scale on the map.  This function
// returns the approximate width in points of roads at the specified zoomScale.
// The result of this function is suitable for use with CGContextSetLineWidth.
MK_EXTERN CGFloat MKRoadWidthAtZoomScale(MKZoomScale zoomScale) NS_AVAILABLE(10_9, 4_0);
