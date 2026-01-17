//
//  MKOverlayPathView.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

#if MK_SUPPORTS_VIEW_CLASSES

#import <UIKit/UIKit.h>

#import <MapKit/MKOverlayView.h>

// Prefer MKOverlayPathRenderer
API_DEPRECATED_WITH_REPLACEMENT("MKOverlayPathRenderer", ios(4.0, 13.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MKOverlayPathView : MKOverlayView

@property (strong) UIColor *fillColor NS_DEPRECATED_IOS(4_0, 7_0);
@property (strong) UIColor *strokeColor NS_DEPRECATED_IOS(4_0, 7_0);

@property CGFloat lineWidth NS_DEPRECATED_IOS(4_0, 7_0); // defaults to 0, which is MKRoadWidthAtZoomScale(currentZoomScale)
@property CGLineJoin lineJoin NS_DEPRECATED_IOS(4_0, 7_0); // defaults to kCGLineJoinRound
@property CGLineCap lineCap NS_DEPRECATED_IOS(4_0, 7_0); // defaults to kCGLineCapRound
@property CGFloat miterLimit NS_DEPRECATED_IOS(4_0, 7_0); // defaults to 10
@property CGFloat lineDashPhase NS_DEPRECATED_IOS(4_0, 7_0); // defaults to 0
@property (copy) NSArray *lineDashPattern NS_DEPRECATED_IOS(4_0, 7_0); // an array of NSNumbers, defaults to nil

// subclassers should override this to create a path and then set it on
// themselves with self.path = newPath;
- (void)createPath NS_DEPRECATED_IOS(4_0, 7_0);
// returns cached path or calls createPath if path has not yet been created
@property CGPathRef path NS_DEPRECATED_IOS(4_0, 7_0); // path will be retained
- (void)invalidatePath NS_DEPRECATED_IOS(4_0, 7_0);

// subclassers may override these
- (void)applyStrokePropertiesToContext:(CGContextRef)context
                           atZoomScale:(MKZoomScale)zoomScale NS_DEPRECATED_IOS(4_0, 7_0);
- (void)applyFillPropertiesToContext:(CGContextRef)context
                         atZoomScale:(MKZoomScale)zoomScale NS_DEPRECATED_IOS(4_0, 7_0);
- (void)strokePath:(CGPathRef)path inContext:(CGContextRef)context NS_DEPRECATED_IOS(4_0, 7_0);
- (void)fillPath:(CGPathRef)path inContext:(CGContextRef)context NS_DEPRECATED_IOS(4_0, 7_0);

@end

#endif // MK_SUPPORTS_VIEW_CLASSES
