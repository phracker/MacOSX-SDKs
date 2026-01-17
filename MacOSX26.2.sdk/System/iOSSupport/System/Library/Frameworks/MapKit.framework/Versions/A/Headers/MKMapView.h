//
//  MKMapView.h
//  MapKit
//
//  Copyright (c) 2009-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

#if MK_SUPPORTS_VIEW_CLASSES

#import <MapKit/MKAnnotationView.h>
#import <MapKit/MKGeometry.h>
#import <MapKit/MKTypes.h>
#import <MapKit/MKOverlay.h>
#import <MapKit/MKOverlayRenderer.h>
#if TARGET_OS_IPHONE
#import <MapKit/MKOverlayView.h>
#endif

#if TARGET_OS_IOS
#import <MapKit/MKMapFeatureAnnotation.h>
#endif

#if !TARGET_OS_WATCH
#import <MapKit/MKSelectionAccessory.h>
#endif

@class MKUserLocation;
@class MKMapCamera;
@class MKMapCameraZoomRange;
@class MKMapCameraBoundary;
@class MKClusterAnnotation;
@class MKPointOfInterestFilter;
@class MKMapConfiguration;

@protocol MKMapViewDelegate;

NS_ASSUME_NONNULL_BEGIN

#endif // MK_SUPPORTS_VIEW_CLASSES

typedef NS_ENUM(NSInteger, MKOverlayLevel) {
    MKOverlayLevelAboveRoads = 0, // note that labels include shields and point of interest icons.
    MKOverlayLevelAboveLabels
} API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.2), watchos(10.0));

#if MK_SUPPORTS_VIEW_CLASSES

typedef NS_ENUM(NSInteger, MKUserTrackingMode) {
	MKUserTrackingModeNone = 0, // the user's location is not followed
	MKUserTrackingModeFollow, // the map follows the user's location
    MKUserTrackingModeFollowWithHeading  // the map follows the user's location and heading
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_UNAVAILABLE(visionos)
#endif
API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos),
} API_AVAILABLE(ios(5.0), tvos(9.2), macos(11.0)) API_UNAVAILABLE(watchos);

#if TARGET_OS_IOS
typedef NS_OPTIONS(NSInteger, MKMapFeatureOptions) {
    MKMapFeatureOptionPointsOfInterest = 1 << MKMapFeatureTypePointOfInterest,
    MKMapFeatureOptionTerritories = 1 << MKMapFeatureTypeTerritory,
    MKMapFeatureOptionPhysicalFeatures = 1 << MKMapFeatureTypePhysicalFeature,
} API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, tvos, watchos);
#endif

MK_EXTERN NSString * const MKMapViewDefaultAnnotationViewReuseIdentifier API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);
MK_EXTERN NSString * const MKMapViewDefaultClusterAnnotationViewReuseIdentifier API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);

#if TARGET_OS_IPHONE
NS_CLASS_AVAILABLE(NA, 3_0) __TVOS_AVAILABLE(9_2) API_UNAVAILABLE(watchos)
@interface MKMapView : UIView <NSCoding>
#else
NS_CLASS_AVAILABLE(10_9, NA)
@interface MKMapView : NSView <NSCoding>
#endif

@property (nonatomic, weak, nullable) IBOutlet id <MKMapViewDelegate> delegate;

// Changing the map type or region can cause the map to start loading map content.
// The loading delegate methods will be called as map content is loaded.
@property (nonatomic) MKMapType mapType API_DEPRECATED("Use respective MKMapConfiguration", macos(10.9, API_TO_BE_DEPRECATED), ios(3.0, API_TO_BE_DEPRECATED), tvos(9.2, API_TO_BE_DEPRECATED));

@property (nonatomic, copy) MKMapConfiguration *preferredConfiguration API_AVAILABLE(ios(16.0), macos(13.0), tvos(16.0)) API_UNAVAILABLE(watchos);

#if TARGET_OS_IOS
@property (nonatomic) MKMapFeatureOptions selectableMapFeatures API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, tvos, watchos);
#endif

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

// Edge padding is the minumum padding on each side around the specified MKMapRect.
#if TARGET_OS_IPHONE
- (void)setVisibleMapRect:(MKMapRect)mapRect edgePadding:(UIEdgeInsets)insets animated:(BOOL)animate;
- (MKMapRect)mapRectThatFits:(MKMapRect)mapRect edgePadding:(UIEdgeInsets)insets;
#else
- (void)setVisibleMapRect:(MKMapRect)mapRect edgePadding:(NSEdgeInsets)insets animated:(BOOL)animate;
- (MKMapRect)mapRectThatFits:(MKMapRect)mapRect edgePadding:(NSEdgeInsets)insets;
#endif

@property (nonatomic, copy) MKMapCamera *camera API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.2)) API_UNAVAILABLE(watchos);
- (void)setCamera:(MKMapCamera *)camera animated:(BOOL)animated API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.2)) API_UNAVAILABLE(watchos);

@property (nonatomic, copy, null_resettable) MKMapCameraZoomRange *cameraZoomRange API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0)) API_UNAVAILABLE(watchos);
- (void)setCameraZoomRange:(nullable MKMapCameraZoomRange *)cameraZoomRange animated:(BOOL)animated API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0)) API_UNAVAILABLE(watchos);

@property (nonatomic, copy, nullable) MKMapCameraBoundary *cameraBoundary API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0)) API_UNAVAILABLE(watchos);
- (void)setCameraBoundary:(nullable MKMapCameraBoundary *)cameraBoundary animated:(BOOL)animated API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0)) API_UNAVAILABLE(watchos);

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
@property (nonatomic, getter=isRotateEnabled) BOOL rotateEnabled API_AVAILABLE(macos(10.9), ios(7.0)) API_UNAVAILABLE(tvos, watchos);
@property (nonatomic, getter=isPitchEnabled) BOOL pitchEnabled API_AVAILABLE(macos(10.9), ios(7.0)) API_UNAVAILABLE(tvos, watchos);

@property (nonatomic, assign) BOOL showsUserTrackingButton API_AVAILABLE(ios(17.0), tvos(17.0), macos(14.0), macCatalyst(17.0)) API_UNAVAILABLE(watchos);
@property (nonatomic, assign) MKFeatureVisibility pitchButtonVisibility API_AVAILABLE(ios(17.0), tvos(17.0), macos(14.0), macCatalyst(17.0)) API_UNAVAILABLE(watchos);
@property (nonatomic) BOOL showsPitchControl API_AVAILABLE(macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(ios, watchos, tvos);
@property (nonatomic) BOOL showsZoomControls API_AVAILABLE(macos(10.9), macCatalyst(13.0)) API_UNAVAILABLE(ios, watchos, tvos);
@property (nonatomic) BOOL showsCompass API_AVAILABLE(macos(10.9), ios(9.0)) API_UNAVAILABLE(tvos, watchos);
@property (nonatomic) BOOL showsScale API_AVAILABLE(macos(10.9), ios(9.0), tvos(9.2)) API_UNAVAILABLE(watchos);

@property (nonatomic, copy, nullable) MKPointOfInterestFilter *pointOfInterestFilter API_DEPRECATED("Use pointOfInterestFilter on respective MKMapConfiguration", macos(10.15, API_TO_BE_DEPRECATED), ios(13.0, API_TO_BE_DEPRECATED), tvos(13.0, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(watchos);
@property (nonatomic) BOOL showsPointsOfInterest
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_UNAVAILABLE(visionos);
#else
API_DEPRECATED("Use pointOfInterestFilter", macos(10.9, 10.15), ios(7.0, 13.0), tvos(9.2, 13.0)) API_UNAVAILABLE(watchos); // Affects MKMapTypeStandard and MKMapTypeHybrid
#endif
@property (nonatomic) BOOL showsBuildings API_DEPRECATED("None", macos(10.9, API_TO_BE_DEPRECATED), ios(7.0, API_TO_BE_DEPRECATED), tvos(9.2, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(watchos); // Affects MKMapTypeStandard
@property (nonatomic) BOOL showsTraffic API_DEPRECATED("Use showsTraffic on respective MKMapConfiguration", macos(10.11, API_TO_BE_DEPRECATED), ios(9.0, API_TO_BE_DEPRECATED), tvos(9.2, API_TO_BE_DEPRECATED)) API_UNAVAILABLE(watchos); // Affects MKMapTypeStandard and MKMapTypeHybrid

// Set to YES to add the user location annotation to the map and start updating its location
@property (nonatomic) BOOL showsUserLocation;

// The annotation representing the user's location
@property (nonatomic, readonly) MKUserLocation *userLocation;

@property (nonatomic) MKUserTrackingMode userTrackingMode API_AVAILABLE(ios(5.0), tvos(9.2), macos(11.0)) API_UNAVAILABLE(watchos);
- (void)setUserTrackingMode:(MKUserTrackingMode)mode animated:(BOOL)animated API_AVAILABLE(ios(5.0), tvos(9.2), macos(11.0)) API_UNAVAILABLE(watchos);

// Returns YES if the user's location is displayed within the currently visible map region.
@property (nonatomic, readonly, getter=isUserLocationVisible) BOOL userLocationVisible;

// Annotations are models used to annotate coordinates on the map. 
// Implement mapView:viewForAnnotation: on MKMapViewDelegate to return the annotation view for each annotation.
- (void)addAnnotation:(id <MKAnnotation>)annotation;
- (void)addAnnotations:(NSArray<id<MKAnnotation>> *)annotations;

- (void)removeAnnotation:(id <MKAnnotation>)annotation;
- (void)removeAnnotations:(NSArray<id<MKAnnotation>> *)annotations;

@property (nonatomic, readonly) NSArray<id<MKAnnotation>> *annotations;
- (NSSet<id<MKAnnotation>> *)annotationsInMapRect:(MKMapRect)mapRect API_AVAILABLE(macos(10.9), ios(4.2), tvos(9.2)) API_UNAVAILABLE(watchos);

// Currently displayed view for an annotation; returns nil if the view for the annotation isn't being displayed.
- (nullable MKAnnotationView *)viewForAnnotation:(id <MKAnnotation>)annotation;

// Used by the delegate to acquire a reusable annotation view, or create a new view for registered class, in lieu of allocating a new one.
- (nullable MKAnnotationView *)dequeueReusableAnnotationViewWithIdentifier:(NSString *)identifier;

// Used by the delegate to acquire a reusable annotation view, or create a new view for registered class, in lieu of allocating a new one. Throws an exception if view could not be aquired.
- (MKAnnotationView *)dequeueReusableAnnotationViewWithIdentifier:(NSString *)identifier forAnnotation:(id<MKAnnotation>)annotation API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);

// Register a MKAnnotationView subclass to be instantiated when dequeueReusableAnnotationViewWithIdentifier: does not have a view to reuse.
- (void)registerClass:(nullable Class)viewClass forAnnotationViewWithReuseIdentifier:(NSString *)identifier API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);

// Select or deselect a given annotation.  Asks the delegate for the corresponding annotation view if necessary.
- (void)selectAnnotation:(id <MKAnnotation>)annotation animated:(BOOL)animated;
- (void)deselectAnnotation:(nullable id <MKAnnotation>)annotation animated:(BOOL)animated;
@property (nonatomic, copy) NSArray<id<MKAnnotation>> *selectedAnnotations;

// annotationVisibleRect is the visible rect where the annotations views are currently displayed.
// The delegate can use annotationVisibleRect when animating the adding of the annotations views in mapView:didAddAnnotationViews:
@property (nonatomic, readonly) CGRect annotationVisibleRect;

// Position the map such that the provided array of annotations are all visible to the fullest extent possible.
- (void)showAnnotations:(NSArray<id<MKAnnotation>> *)annotations animated:(BOOL)animated API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.2)) API_UNAVAILABLE(watchos);

@end

@interface MKMapView (OverlaysAPI)

// Overlays are models used to represent areas to be drawn on top of the map.
// This is in contrast to annotations, which represent points on the map.
// Implement -mapView:rendererForOverlay: on MKMapViewDelegate to return the renderer for each overlay.
- (void)addOverlay:(id <MKOverlay>)overlay level:(MKOverlayLevel)level API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.2)) API_UNAVAILABLE(watchos);
- (void)addOverlays:(NSArray<id<MKOverlay>> *)overlays level:(MKOverlayLevel)level API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.2)) API_UNAVAILABLE(watchos);

- (void)removeOverlay:(id <MKOverlay>)overlay API_AVAILABLE(macos(10.9), ios(4.0), tvos(9.2)) API_UNAVAILABLE(watchos);
- (void)removeOverlays:(NSArray<id<MKOverlay>> *)overlays API_AVAILABLE(macos(10.9), ios(4.0), tvos(9.2)) API_UNAVAILABLE(watchos);

- (void)insertOverlay:(id <MKOverlay>)overlay atIndex:(NSUInteger)index level:(MKOverlayLevel)level  API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.2)) API_UNAVAILABLE(watchos);

- (void)insertOverlay:(id <MKOverlay>)overlay aboveOverlay:(id <MKOverlay>)sibling API_AVAILABLE(macos(10.9), ios(4.0), tvos(9.2)) API_UNAVAILABLE(watchos);
- (void)insertOverlay:(id <MKOverlay>)overlay belowOverlay:(id <MKOverlay>)sibling API_AVAILABLE(macos(10.9), ios(4.0), tvos(9.2)) API_UNAVAILABLE(watchos);

- (void)exchangeOverlay:(id <MKOverlay>)overlay1 withOverlay:(id <MKOverlay>)overlay2  API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.2)) API_UNAVAILABLE(watchos);

@property (nonatomic, readonly) NSArray<id<MKOverlay>> *overlays API_AVAILABLE(macos(10.9), ios(4.0), tvos(9.2)) API_UNAVAILABLE(watchos);
- (NSArray<id<MKOverlay>> *)overlaysInLevel:(MKOverlayLevel)level  API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.2)) API_UNAVAILABLE(watchos);

// Current renderer for overlay; returns nil if the overlay is not shown.
- (nullable MKOverlayRenderer *)rendererForOverlay:(id <MKOverlay>)overlay  API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.2)) API_UNAVAILABLE(watchos);

#if TARGET_OS_IPHONE
// Currently displayed view for overlay; returns nil if the view has not been created yet.
// Prefer using MKOverlayRenderer and -rendererForOverlay.
- (MKOverlayView *)viewForOverlay:(id <MKOverlay>)overlay
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_UNAVAILABLE(visionos);
#else
API_DEPRECATED("Use -rendererForOverlay:", ios(4.0, 13.0)) API_UNAVAILABLE(macos, tvos, watchos);
#endif
#endif

// These methods operate implicitly on overlays in MKOverlayLevelAboveRoads and may be deprecated in a future release in favor of the methods that specify the level.
- (void)addOverlay:(id <MKOverlay>)overlay API_AVAILABLE(macos(10.9), ios(4.0), tvos(9.2)) API_UNAVAILABLE(watchos);
- (void)addOverlays:(NSArray<id<MKOverlay>> *)overlays API_AVAILABLE(macos(10.9), ios(4.0), tvos(9.2)) API_UNAVAILABLE(watchos);

- (void)insertOverlay:(id <MKOverlay>)overlay atIndex:(NSUInteger)index API_AVAILABLE(macos(10.9), ios(4.0), tvos(9.2)) API_UNAVAILABLE(watchos);
- (void)exchangeOverlayAtIndex:(NSUInteger)index1 withOverlayAtIndex:(NSUInteger)index2 API_AVAILABLE(macos(10.9), ios(4.0), tvos(9.2)) API_UNAVAILABLE(watchos);

@end

API_UNAVAILABLE(watchos)
NS_SWIFT_UI_ACTOR
@protocol MKMapViewDelegate <NSObject>
@optional

- (void)mapView:(MKMapView *)mapView regionWillChangeAnimated:(BOOL)animated;
- (void)mapView:(MKMapView *)mapView regionDidChangeAnimated:(BOOL)animated;

- (void)mapViewDidChangeVisibleRegion:(MKMapView *)mapView API_AVAILABLE(ios(11), tvos(11), macos(10.13)) API_UNAVAILABLE(watchos);

- (void)mapViewWillStartLoadingMap:(MKMapView *)mapView;
- (void)mapViewDidFinishLoadingMap:(MKMapView *)mapView;
- (void)mapViewDidFailLoadingMap:(MKMapView *)mapView withError:(NSError *)error;

- (void)mapViewWillStartRenderingMap:(MKMapView *)mapView API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.2)) API_UNAVAILABLE(watchos);
- (void)mapViewDidFinishRenderingMap:(MKMapView *)mapView fullyRendered:(BOOL)fullyRendered API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.2)) API_UNAVAILABLE(watchos);

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
- (void)mapView:(MKMapView *)mapView annotationView:(MKAnnotationView *)view calloutAccessoryControlTapped:(UIControl *)control API_UNAVAILABLE(tvos, watchos);
#endif

- (void)mapView:(MKMapView *)mapView didSelectAnnotationView:(MKAnnotationView *)view API_AVAILABLE(macos(10.9), ios(4.0), tvos(9.2)) API_UNAVAILABLE(watchos);
- (void)mapView:(MKMapView *)mapView didDeselectAnnotationView:(MKAnnotationView *)view API_AVAILABLE(macos(10.9), ios(4.0), tvos(9.2)) API_UNAVAILABLE(watchos);

- (void)mapView:(MKMapView *)mapView didSelectAnnotation:(id<MKAnnotation>)annotation API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, tvos, watchos);
- (void)mapView:(MKMapView *)mapView didDeselectAnnotation:(id<MKAnnotation>)annotation API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, tvos, watchos);

#if !TARGET_OS_WATCH && !TARGET_OS_TV
// Specifies the accessory to display for a selected annotation
//
// Called for all selected annotations. Not all types of annotations
// currently support displaying selection accessories. Please return `nil`
// for annotations where a selection accessory is not desired.
//
// No accessory will be displayed if...
// - `nil` is returned
// - `- mapView:selectionAccessoryForAnnotation:` is not implemented
// - the accessory returned is not supported for `annotation`
- (nullable MKSelectionAccessory *)mapView:(MKMapView *)mapView
           selectionAccessoryForAnnotation:(id<MKAnnotation>)annotation
API_AVAILABLE(ios(18.0), macos(15.0), visionos(2.0))
API_UNAVAILABLE(watchos, tvos);
#endif

- (void)mapViewWillStartLocatingUser:(MKMapView *)mapView API_AVAILABLE(macos(10.9), ios(4.0), tvos(9.2)) API_UNAVAILABLE(watchos);
- (void)mapViewDidStopLocatingUser:(MKMapView *)mapView API_AVAILABLE(macos(10.9), ios(4.0), tvos(9.2)) API_UNAVAILABLE(watchos);
- (void)mapView:(MKMapView *)mapView didUpdateUserLocation:(MKUserLocation *)userLocation API_AVAILABLE(macos(10.9), ios(4.0), tvos(9.2)) API_UNAVAILABLE(watchos);
- (void)mapView:(MKMapView *)mapView didFailToLocateUserWithError:(NSError *)error API_AVAILABLE(macos(10.9), ios(4.0), tvos(9.2)) API_UNAVAILABLE(watchos);

- (void)mapView:(MKMapView *)mapView annotationView:(MKAnnotationView *)view didChangeDragState:(MKAnnotationViewDragState)newState 
   fromOldState:(MKAnnotationViewDragState)oldState API_AVAILABLE(macos(10.9), ios(4.0)) API_UNAVAILABLE(tvos, watchos);

- (void)mapView:(MKMapView *)mapView didChangeUserTrackingMode:(MKUserTrackingMode)mode animated:(BOOL)animated API_AVAILABLE(ios(5.0), tvos(9.2), macos(11.0)) API_UNAVAILABLE(watchos);

- (MKOverlayRenderer *)mapView:(MKMapView *)mapView rendererForOverlay:(id <MKOverlay>)overlay API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.2)) API_UNAVAILABLE(watchos);
- (void)mapView:(MKMapView *)mapView didAddOverlayRenderers:(NSArray<MKOverlayRenderer *> *)renderers API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.2)) API_UNAVAILABLE(watchos);

#if TARGET_OS_IPHONE
// Prefer -mapView:rendererForOverlay:
- (MKOverlayView *)mapView:(MKMapView *)mapView viewForOverlay:(id <MKOverlay>)overlay API_DEPRECATED("Use -mapView:rendererForOverlay:", ios(4.0, 13.0))
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_UNAVAILABLE(visionos);
#else
API_UNAVAILABLE(macos, tvos, watchos);
#endif
// Called after the provided overlay views have been added and positioned in the map.
// Prefer -mapView:didAddOverlayRenderers:
- (void)mapView:(MKMapView *)mapView didAddOverlayViews:(NSArray *)overlayViews
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_UNAVAILABLE(visionos);
#else
API_DEPRECATED("Use -mapView:didAddOverlayRenderers:", ios(4.0, 13.0)) API_UNAVAILABLE(macos, tvos, watchos);
#endif
#endif

// Return nil for default MKClusterAnnotation, it is illegal to return a cluster annotation not containing the identical array of member annotations given.
- (MKClusterAnnotation *)mapView:(MKMapView *)mapView clusterAnnotationForMemberAnnotations:(NSArray<id<MKAnnotation>>*)memberAnnotations NS_AVAILABLE(10_13, 11_0) __TVOS_AVAILABLE(11_0) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END

#endif // MK_SUPPORTS_VIEW_CLASSES
