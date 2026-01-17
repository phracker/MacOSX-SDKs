//
//  MKOverlayView.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

#if MK_SUPPORTS_VIEW_CLASSES

#import <UIKit/UIKit.h>
#import <MapKit/MKGeometry.h>
#import <MapKit/MKOverlay.h>


// Prefer MKOverlayRenderer
API_DEPRECATED_WITH_REPLACEMENT("MKOverlayRenderer", ios(4.0, 13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MKOverlayView : UIView

- (instancetype)initWithOverlay:(id <MKOverlay>)overlay NS_DESIGNATED_INITIALIZER NS_DEPRECATED_IOS(4_0, 7_0);

@property (nonatomic, readonly) id <MKOverlay> overlay NS_DEPRECATED_IOS(4_0, 7_0);

// Convert screen points relative to this view to absolute MKMapPoints
- (CGPoint)pointForMapPoint:(MKMapPoint)mapPoint NS_DEPRECATED_IOS(4_0, 7_0);
- (MKMapPoint)mapPointForPoint:(CGPoint)point NS_DEPRECATED_IOS(4_0, 7_0);

- (CGRect)rectForMapRect:(MKMapRect)mapRect NS_DEPRECATED_IOS(4_0, 7_0);
- (MKMapRect)mapRectForRect:(CGRect)rect NS_DEPRECATED_IOS(4_0, 7_0);

// Return YES if the view is currently ready to draw in the specified rect.
// Return NO if the view will not draw in the specified rect or if the
// data necessary to draw in the specified rect is not available.  In the 
// case where the view may want to draw in the specified rect but the data is
// not available, use setNeedsDisplayInMapRect:zoomLevel: to signal when the
// data does become available.
- (BOOL)canDrawMapRect:(MKMapRect)mapRect
             zoomScale:(MKZoomScale)zoomScale NS_DEPRECATED_IOS(4_0, 7_0);

- (void)drawMapRect:(MKMapRect)mapRect
          zoomScale:(MKZoomScale)zoomScale
          inContext:(CGContextRef)context NS_DEPRECATED_IOS(4_0, 7_0);

- (void)setNeedsDisplayInMapRect:(MKMapRect)mapRect NS_DEPRECATED_IOS(4_0, 7_0);

- (void)setNeedsDisplayInMapRect:(MKMapRect)mapRect
                       zoomScale:(MKZoomScale)zoomScale NS_DEPRECATED_IOS(4_0, 7_0);

@end

// Road widths are typically not drawn to scale on the map.  This function
// returns the approximate width in points of roads at the specified zoomScale.
// The result of this function is suitable for use with CGContextSetLineWidth.
MK_EXTERN CGFloat MKRoadWidthAtZoomScale(MKZoomScale zoomScale) NS_AVAILABLE(10_9, 4_0) API_UNAVAILABLE(watchos);

#endif // MK_SUPPORTS_VIEW_CLASSES
