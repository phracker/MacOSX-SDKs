//
//  MKMapView.h
//  MapKit
//
//  Copyright (c) 2009-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKAnnotationView.h>
#import <MapKit/MKFoundation.h>
#import <MapKit/MKGeometry.h>
#import <MapKit/MKTypes.h>
#import <MapKit/MKOverlay.h>
#import <MapKit/MKOverlayRenderer.h>
#if TARGET_OS_IPHONE
#import <MapKit/MKOverlayView.h>
#endif

@class MKUserLocation;
@class MKMapCamera;

@protocol MKMapViewDelegate;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, MKUserTrackingMode) {
	MKUserTrackingModeNone = 0, // the user's location is not followed
	MKUserTrackingModeFollow, // the map follows the user's location
	MKUserTrackingModeFollowWithHeading, // the map follows the user's location and heading
} NS_ENUM_AVAILABLE(NA, 5_0) __WATCHOS_PROHIBITED;

#if TARGET_OS_IPHONE
MK_CLASS_AVAILABLE(NA, 3_0) __WATCHOS_PROHIBITED
@interface MKMapView : UIView <NSCoding>
#else
MK_CLASS_AVAILABLE(10_9, NA)
@interface MKMapView : NSView <NSCoding>
#endif

@property (nonatomic, weak, nullable) id <MKMapViewDelegate> delegate;

// Changing the map type or region can cause the map to start loading map content.
// The loading delegate methods will be called as map content is loaded.
@property (nonatomic) MKMapType mapType;

// Region is the coordinate and span of the map.
// Region may be modified to fit the aspect ratio of the view using regionThatFits:.
@property (nonatomic) MKCoordinateRegion region;
- (void)setRegion:(MKCoordinateRegion)region animated:(BOOL)animated;

// centerCoordinate allows the coordinate of the region to be changed without changing the zoom level.
@property (nonatomic) CLLocationCoordinate2D centerCoordinate;
- (void)setCenterCoordinate:(CLLocationCoordinate2D)coordinate animated:(BOOL)animated;

// Returns a region of the aspect ratio of the map view that contains the given region, with the same center point.
- (MKCoordinateRegion)regionThatFits:(MKCoordinateRegion)region;

// Access the visible region of the map in projected coordinates.
@property (nonatomic) MKMapRect visibleMapRect;
- (void)setVisibleMapRect:(MKMapRect)mapRect animated:(BOOL)animate;

// Returns an MKMapRect modified to fit the aspect ratio of the map.
- (MKMapRect)mapRectThatFits:(MKMapRect)mapRect;

// To be used in testing only
- (void)_handleSelectionAtPoint:(CGPoint)locationInView;

// Edge padding is the minumum padding on each side around the specified MKMapRect.
#if TARGET_OS_IPHONE
- (void)setVisibleMapRect:(MKMapRect)mapRect edgePadding:(UIEdgeInsets)insets animated:(BOOL)animate;
- (MKMapRect)mapRectThatFits:(MKMapRect)mapRect edgePadding:(UIEdgeInsets)insets;
#else
- (void)setVisibleMapRect:(MKMapRect)mapRect edgePadding:(NSEdgeInsets)insets animated:(BOOL)animate;
- (MKMapRect)mapRectThatFits:(MKMapRect)mapRect edgePadding:(NSEdgeInsets)insets;
#endif

@property (nonatomic, copy) MKMapCamera *camera NS_AVAILABLE(10_9, 7_0);
- (void)setCamera:(MKMapCamera *)camera animated:(BOOL)animated NS_AVAILABLE(10_9, 7_0);

#if TARGET_OS_IPHONE
- (CGPoint)convertCoordinate:(CLLocationCoordinate2D)coordinate toPointToView:(nullable UIView *)view;
- (CLLocationCoordinate2D)convertPoint:(CGPoint)point toCoordinateFromView:(nullable UIView *)view;
- (CGRect)convertRegion:(MKCoordinateRegion)region toRectToView:(nullable UIView *)view;
- (MKCoordinateRegion)convertRect:(CGRect)rect toRegionFromView:(nullable UIView *)view;
#else
- (CGPoint)convertCoordinate:(CLLocationCoordinate2D)coordinate toPointToView:(nullable NSView *)view;
- (CLLocationCoordinate2D)convertPoint:(CGPoint)point toCoordinateFromView:(nullable NSView *)view;
- (CGRect)convertRegion:(MKCoordinateRegion)region toRectToView:(nullable NSView *)view;
- (MKCoordinateRegion)convertRect:(CGRect)rect toRegionFromView:(nullable NSView *)view;
#endif

// Control the types of user interaction available
// Zoom and scroll are enabled by default.
@property (nonatomic, getter=isZoomEnabled) BOOL zoomEnabled;
@property (nonatomic, getter=isScrollEnabled) BOOL scrollEnabled;
// Rotate and pitch are enabled by default on Mac OS X and on iOS 7.0 and later.
@property (nonatomic, getter=isRotateEnabled) BOOL rotateEnabled NS_AVAILABLE(10_9, 7_0);
@property (nonatomic, getter=isPitchEnabled) BOOL pitchEnabled NS_AVAILABLE(10_9, 7_0);

#if !TARGET_OS_IPHONE
@property (nonatomic) BOOL showsZoomControls NS_AVAILABLE(10_9, NA);
#endif


@property (nonatomic) BOOL showsCompass NS_AVAILABLE(10_9, 9_0);
@property (nonatomic) BOOL showsScale NS_AVAILABLE(10_10, 9_0);

@property (nonatomic) BOOL showsPointsOfInterest NS_AVAILABLE(10_9, 7_0); // Affects MKMapTypeStandard and MKMapTypeHybrid
@property (nonatomic) BOOL showsBuildings NS_AVAILABLE(10_9, 7_0); // Affects MKMapTypeStandard
@property (nonatomic) BOOL showsTraffic NS_AVAILABLE(10_11, 9_0); // Affects MKMapTypeStandard and MKMapTypeHybrid

// Set to YES to add the user location annotation to the map and start updating its location
@property (nonatomic) BOOL showsUserLocation;

// The annotation representing the user's location
@property (nonatomic, readonly) MKUserLocation *userLocation;

#if TARGET_OS_IPHONE
@property (nonatomic) MKUserTrackingMode userTrackingMode NS_AVAILABLE(NA, 5_0);
- (void)setUserTrackingMode:(MKUserTrackingMode)mode animated:(BOOL)animated NS_AVAILABLE(NA, 5_0);
#endif

// Returns YES if the user's location is displayed within the currently visible map region.
@property (nonatomic, readonly, getter=isUserLocationVisible) BOOL userLocationVisible;

// Annotations are models used to annotate coordinates on the map. 
// Implement mapView:viewForAnnotation: on MKMapViewDelegate to return the annotation view for each annotation.
- (void)addAnnotation:(id <MKAnnotation>)annotation;
- (void)addAnnotations:(NSArray<id<MKAnnotation>> *)annotations;

- (void)removeAnnotation:(id <MKAnnotation>)annotation;
- (void)removeAnnotations:(NSArray<id<MKAnnotation>> *)annotations;

@property (nonatomic, readonly) NSArray<id<MKAnnotation>> *annotations;
- (NSSet<id<MKAnnotation>> *)annotationsInMapRect:(MKMapRect)mapRect NS_AVAILABLE(10_9, 4_2);

// Currently displayed view for an annotation; returns nil if the view for the annotation isn't being displayed.
- (nullable MKAnnotationView *)viewForAnnotation:(id <MKAnnotation>)annotation;

// Used by the delegate to acquire an already allocated annotation view, in lieu of allocating a new one.
- (nullable MKAnnotationView *)dequeueReusableAnnotationViewWithIdentifier:(NSString *)identifier;

// Select or deselect a given annotation.  Asks the delegate for the corresponding annotation view if necessary.
- (void)selectAnnotation:(id <MKAnnotation>)annotation animated:(BOOL)animated;
- (void)deselectAnnotation:(nullable id <MKAnnotation>)annotation animated:(BOOL)animated;
@property (nonatomic, copy) NSArray<id<MKAnnotation>> *selectedAnnotations;

// annotationVisibleRect is the visible rect where the annotations views are currently displayed.
// The delegate can use annotationVisibleRect when animating the adding of the annotations views in mapView:didAddAnnotationViews:
@property (nonatomic, readonly) CGRect annotationVisibleRect;

// Position the map such that the provided array of annotations are all visible to the fullest extent possible.
- (void)showAnnotations:(NSArray<id<MKAnnotation>> *)annotations animated:(BOOL)animated NS_AVAILABLE(10_9, 7_0);

@end

typedef NS_ENUM(NSInteger, MKOverlayLevel) {
    MKOverlayLevelAboveRoads = 0, // note that labels include shields and point of interest icons.
    MKOverlayLevelAboveLabels
} NS_ENUM_AVAILABLE(10_9, 7_0) __WATCHOS_PROHIBITED;

@interface MKMapView (OverlaysAPI)

// Overlays are models used to represent areas to be drawn on top of the map.
// This is in contrast to annotations, which represent points on the map.
// Implement -mapView:rendererForOverlay: on MKMapViewDelegate to return the renderer for each overlay.
- (void)addOverlay:(id <MKOverlay>)overlay level:(MKOverlayLevel)level NS_AVAILABLE(10_9, 7_0);
- (void)addOverlays:(NSArray<id<MKOverlay>> *)overlays level:(MKOverlayLevel)level NS_AVAILABLE(10_9, 7_0);

- (void)removeOverlay:(id <MKOverlay>)overlay NS_AVAILABLE(10_9, 4_0);
- (void)removeOverlays:(NSArray<id<MKOverlay>> *)overlays NS_AVAILABLE(10_9, 4_0);

- (void)insertOverlay:(id <MKOverlay>)overlay atIndex:(NSUInteger)index level:(MKOverlayLevel)level NS_AVAILABLE(10_9, 7_0);

- (void)insertOverlay:(id <MKOverlay>)overlay aboveOverlay:(id <MKOverlay>)sibling NS_AVAILABLE(10_9, 4_0);
- (void)insertOverlay:(id <MKOverlay>)overlay belowOverlay:(id <MKOverlay>)sibling NS_AVAILABLE(10_9, 4_0);

- (void)exchangeOverlay:(id <MKOverlay>)overlay1 withOverlay:(id <MKOverlay>)overlay2 NS_AVAILABLE(10_9, 7_0);

@property (nonatomic, readonly) NSArray<id<MKOverlay>> *overlays NS_AVAILABLE(10_9, 4_0);
- (NSArray<id<MKOverlay>> *)overlaysInLevel:(MKOverlayLevel)level NS_AVAILABLE(10_9, 7_0);

// Current renderer for overlay; returns nil if the overlay is not shown.
- (nullable MKOverlayRenderer *)rendererForOverlay:(id <MKOverlay>)overlay NS_AVAILABLE(10_9, 7_0);

#if TARGET_OS_IPHONE
// Currently displayed view for overlay; returns nil if the view has not been created yet.
// Prefer using MKOverlayRenderer and -rendererForOverlay.
- (MKOverlayView *)viewForOverlay:(id <MKOverlay>)overlay NS_DEPRECATED_IOS(4_0, 7_0);
#endif

// These methods operate implicitly on overlays in MKOverlayLevelAboveLabels and may be deprecated in a future release in favor of the methods that specify the level.
- (void)addOverlay:(id <MKOverlay>)overlay NS_AVAILABLE(10_9, 4_0);
- (void)addOverlays:(NSArray<id<MKOverlay>> *)overlays NS_AVAILABLE(10_9, 4_0);

- (void)insertOverlay:(id <MKOverlay>)overlay atIndex:(NSUInteger)index NS_AVAILABLE(10_9, 4_0);
- (void)exchangeOverlayAtIndex:(NSUInteger)index1 withOverlayAtIndex:(NSUInteger)index2 NS_AVAILABLE(10_9, 4_0);

@end

__WATCHOS_PROHIBITED
@protocol MKMapViewDelegate <NSObject>
@optional

- (void)mapView:(MKMapView *)mapView regionWillChangeAnimated:(BOOL)animated;
- (void)mapView:(MKMapView *)mapView regionDidChangeAnimated:(BOOL)animated;

- (void)mapViewWillStartLoadingMap:(MKMapView *)mapView;
- (void)mapViewDidFinishLoadingMap:(MKMapView *)mapView;
- (void)mapViewDidFailLoadingMap:(MKMapView *)mapView withError:(NSError *)error;

- (void)mapViewWillStartRenderingMap:(MKMapView *)mapView NS_AVAILABLE(10_9, 7_0);
- (void)mapViewDidFinishRenderingMap:(MKMapView *)mapView fullyRendered:(BOOL)fullyRendered NS_AVAILABLE(10_9, 7_0);

// mapView:viewForAnnotation: provides the view for each annotation.
// This method may be called for all or some of the added annotations.
// For MapKit provided annotations (eg. MKUserLocation) return nil to use the MapKit provided annotation view.
- (nullable MKAnnotationView *)mapView:(MKMapView *)mapView viewForAnnotation:(id <MKAnnotation>)annotation;

// mapView:didAddAnnotationViews: is called after the annotation views have been added and positioned in the map.
// The delegate can implement this method to animate the adding of the annotations views.
// Use the current positions of the annotation views as the destinations of the animation.
- (void)mapView:(MKMapView *)mapView didAddAnnotationViews:(NSArray<MKAnnotationView *> *)views;

#if TARGET_OS_IPHONE
// mapView:annotationView:calloutAccessoryControlTapped: is called when the user taps on left & right callout accessory UIControls.
- (void)mapView:(MKMapView *)mapView annotationView:(MKAnnotationView *)view calloutAccessoryControlTapped:(UIControl *)control;
#endif

- (void)mapView:(MKMapView *)mapView didSelectAnnotationView:(MKAnnotationView *)view NS_AVAILABLE(10_9, 4_0);
- (void)mapView:(MKMapView *)mapView didDeselectAnnotationView:(MKAnnotationView *)view NS_AVAILABLE(10_9, 4_0);

- (void)mapViewWillStartLocatingUser:(MKMapView *)mapView NS_AVAILABLE(10_9, 4_0);
- (void)mapViewDidStopLocatingUser:(MKMapView *)mapView NS_AVAILABLE(10_9, 4_0);
- (void)mapView:(MKMapView *)mapView didUpdateUserLocation:(MKUserLocation *)userLocation NS_AVAILABLE(10_9, 4_0);
- (void)mapView:(MKMapView *)mapView didFailToLocateUserWithError:(NSError *)error NS_AVAILABLE(10_9, 4_0);

- (void)mapView:(MKMapView *)mapView annotationView:(MKAnnotationView *)view didChangeDragState:(MKAnnotationViewDragState)newState 
   fromOldState:(MKAnnotationViewDragState)oldState NS_AVAILABLE(10_9, 4_0);

#if TARGET_OS_IPHONE
- (void)mapView:(MKMapView *)mapView didChangeUserTrackingMode:(MKUserTrackingMode)mode animated:(BOOL)animated NS_AVAILABLE(NA, 5_0);
#endif

- (MKOverlayRenderer *)mapView:(MKMapView *)mapView rendererForOverlay:(id <MKOverlay>)overlay NS_AVAILABLE(10_9, 7_0);
- (void)mapView:(MKMapView *)mapView didAddOverlayRenderers:(NSArray<MKOverlayRenderer *> *)renderers NS_AVAILABLE(10_9, 7_0);

#if TARGET_OS_IPHONE
// Prefer -mapView:rendererForOverlay:
- (MKOverlayView *)mapView:(MKMapView *)mapView viewForOverlay:(id <MKOverlay>)overlay NS_DEPRECATED_IOS(4_0, 7_0);
// Called after the provided overlay views have been added and positioned in the map.
// Prefer -mapView:didAddOverlayRenderers:
- (void)mapView:(MKMapView *)mapView didAddOverlayViews:(NSArray *)overlayViews NS_DEPRECATED_IOS(4_0, 7_0);
#endif

@end

NS_ASSUME_NONNULL_END
