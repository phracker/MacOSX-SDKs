//
//  MapKit.h
//  MapKit
//
//  Copyright (c) 2009-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

#import <MapKit/MKAddress.h>
#import <MapKit/MKAddressRepresentations.h>
#import <MapKit/MKAddressFilter.h>
#import <MapKit/MKAnnotation.h>
#import <MapKit/MKCircle.h>
#import <MapKit/MKDirections.h>
#import <MapKit/MKDirectionsRequest.h>
#import <MapKit/MKDirectionsResponse.h>
#import <MapKit/MKDistanceFormatter.h>
#import <MapKit/MKGeocodingRequest.h>
#import <MapKit/MKGeoJSONSerialization.h>
#import <MapKit/MKGeodesicPolyline.h>
#import <MapKit/MKGeometry.h>
#import <MapKit/MKLocalPointsOfInterestRequest.h>
#import <MapKit/MKLocalSearch.h>
#import <MapKit/MKLocalSearchCompleter.h>
#import <MapKit/MKLocalSearchRequest.h>
#import <MapKit/MKLocalSearchResponse.h>
#import <MapKit/MKMapCamera.h>
#import <MapKit/MKMapConfiguration.h>
#import <MapKit/MKMapItemIdentifier.h>
#import <MapKit/MKMapItem.h>
#import <MapKit/MKMapItemRequest.h>
#import <MapKit/MKMapSnapshot.h>
#import <MapKit/MKMapSnapshotOptions.h>
#import <MapKit/MKMapSnapshotter.h>
#import <MapKit/MKMultiPoint.h>
#import <MapKit/MKMultiPolygon.h>
#import <MapKit/MKMultiPolyline.h>
#import <MapKit/MKOverlay.h>
#import <MapKit/MKPlacemark.h>
#import <MapKit/MKPointAnnotation.h>
#import <MapKit/MKPointOfInterestCategory.h>
#import <MapKit/MKPointOfInterestFilter.h>
#import <MapKit/MKPolygon.h>
#import <MapKit/MKPolyline.h>
#import <MapKit/MKReverseGeocodingRequest.h>
#import <MapKit/MKShape.h>
#import <MapKit/MKStandardMapConfiguration.h>
#import <MapKit/MKTypes.h>
#import <MapKit/NSUserActivity+MKMapItem.h>

#if __has_include(<MapKit/MKMapView.h>)
#import <MapKit/MKAnnotationView.h>
#import <MapKit/MKMapView.h>
#import <MapKit/MKMarkerAnnotationView.h>
#import <MapKit/MKPinAnnotationView.h>
#import <MapKit/MKUserLocation.h>
#import <MapKit/MKUserLocationView.h>
#import <MapKit/MKClusterAnnotation.h>
#import <MapKit/MKCompassButton.h>
#import <MapKit/MKMapItemAnnotation.h>
#import <MapKit/MKMultiPolygonRenderer.h>
#import <MapKit/MKMultiPolylineRenderer.h>
#import <MapKit/MKGradientPolylineRenderer.h>
#import <MapKit/MKOverlayRenderer.h>
#import <MapKit/MKOverlayPathRenderer.h>
#import <MapKit/MKPolygonRenderer.h>
#import <MapKit/MKPolylineRenderer.h>
#import <MapKit/MKCircleRenderer.h>
#import <MapKit/MKTileOverlay.h>
#import <MapKit/MKTileOverlayRenderer.h>
#import <MapKit/MKMapCameraZoomRange.h>
#import <MapKit/MKMapCameraBoundary.h>
#import <MapKit/MKPitchControl.h>
#import <MapKit/MKZoomControl.h>
#import <MapKit/MKHybridMapConfiguration.h>
#import <MapKit/MKImageryMapConfiguration.h>

#if TARGET_OS_IPHONE
#import <MapKit/MKReverseGeocoder.h>
#import <MapKit/MKOverlayView.h>
#import <MapKit/MKOverlayPathView.h>
#import <MapKit/MKPolygonView.h>
#import <MapKit/MKPolylineView.h>
#import <MapKit/MKCircleView.h>
#import <MapKit/MKScaleView.h>
#import <MapKit/MKUserTrackingBarButtonItem.h>
#endif // TARGET_OS_IPHONE

#if TARGET_OS_IOS || TARGET_OS_MACCATALYST || TARGET_OS_TV
#import <MapKit/MKUserTrackingButton.h>
#import <MapKit/MKIconStyle.h>
#import <MapKit/MKMapFeatureAnnotation.h>

#endif // TARGET_OS_IOS || TARGET_OS_MACCATALYST || TARGET_OS_TV

#if (TARGET_OS_IOS || TARGET_OS_MACCATALYST || TARGET_OS_OSX || TARGET_OS_TV)

#import <MapKit/MKLookAroundScene.h>
#import <MapKit/MKLookAroundSceneRequest.h>
#import <MapKit/MKLookAroundSnapshot.h>
#import <MapKit/MKLookAroundSnapshotOptions.h>
#import <MapKit/MKLookAroundSnapshotter.h>
#import <MapKit/MKLookAroundViewController.h>

#endif // (TARGET_OS_IOS || TARGET_OS_MACCATALYST || TARGET_OS_OSX || TARGET_OS_TV)

#if (!TARGET_OS_WATCH)

#import <MapKit/MKMapItemDetailViewController.h>
#import <MapKit/MKSelectionAccessory.h>

#endif // (!TARGET_OS_WATCH)


#endif // __has_include(<MapKit/MKMapView.h>)
