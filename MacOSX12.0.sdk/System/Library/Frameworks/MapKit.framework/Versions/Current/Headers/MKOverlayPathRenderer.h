//
//  MKOverlayPathRenderer.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKOverlayRenderer.h>
#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_9, 7_0) __TVOS_AVAILABLE(9_2) API_UNAVAILABLE(watchos)
@interface MKOverlayPathRenderer : MKOverlayRenderer

#if TARGET_OS_IPHONE
@property (strong, nullable) UIColor *fillColor;
@property (strong, nullable) UIColor *strokeColor;
#else
@property (strong, nullable) NSColor *fillColor;
@property (strong, nullable) NSColor *strokeColor;
#endif

@property CGFloat lineWidth; // defaults to 0, which is MKRoadWidthAtZoomScale(currentZoomScale)
@property CGLineJoin lineJoin; // defaults to kCGLineJoinRound
@property CGLineCap lineCap; // defaults to kCGLineCapRound
@property CGFloat miterLimit; // defaults to 10
@property CGFloat lineDashPhase; // defaults to 0
@property (copy, nullable) NSArray<NSNumber *> *lineDashPattern; // defaults to nil

/*
 For renderers which support vector drawing, controls whether the overlay is rendered
 as a bitmap when being composited with the map.

 When false (the default), the overlay will be rendered as vector geometry whenever possible.
 Note that certain geometry or configurations may force rasterization even when the value
 of this property is false.
 */
@property (nonatomic, assign) BOOL shouldRasterize API_AVAILABLE(ios(13.0), tvos(13.0), macos(10.15)) API_UNAVAILABLE(watchos);

// subclassers should override this to create a path and then set it on
// themselves with self.path = newPath;
- (void)createPath;
// returns cached path or calls createPath if path has not yet been created
@property (null_resettable) CGPathRef path; // path will be retained
- (void)invalidatePath;

// subclassers may override these
- (void)applyStrokePropertiesToContext:(CGContextRef)context
                           atZoomScale:(MKZoomScale)zoomScale;
- (void)applyFillPropertiesToContext:(CGContextRef)context
                         atZoomScale:(MKZoomScale)zoomScale;
- (void)strokePath:(CGPathRef)path inContext:(CGContextRef)context;
- (void)fillPath:(CGPathRef)path inContext:(CGContextRef)context;

@end

NS_ASSUME_NONNULL_END
