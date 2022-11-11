//
//  MKGeometry.h
//  MapKit
//
//  Copyright (c) 2009-2014, Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <CoreLocation/CoreLocation.h>
#import <MapKit/MKFoundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef struct {
    CLLocationDegrees latitudeDelta;
    CLLocationDegrees longitudeDelta;
} MKCoordinateSpan;

typedef struct {
	CLLocationCoordinate2D center;
	MKCoordinateSpan span;
} MKCoordinateRegion;


NS_INLINE MKCoordinateSpan MKCoordinateSpanMake(CLLocationDegrees latitudeDelta, CLLocationDegrees longitudeDelta)
{
    MKCoordinateSpan span;
    span.latitudeDelta = latitudeDelta;
    span.longitudeDelta = longitudeDelta;
    return span;
}

NS_INLINE MKCoordinateRegion MKCoordinateRegionMake(CLLocationCoordinate2D centerCoordinate, MKCoordinateSpan span)
{
	MKCoordinateRegion region;
	region.center = centerCoordinate;
    region.span = span;
	return region;
}

MK_EXTERN MKCoordinateRegion MKCoordinateRegionMakeWithDistance(CLLocationCoordinate2D centerCoordinate, CLLocationDistance latitudinalMeters, CLLocationDistance longitudinalMeters) __TVOS_AVAILABLE(9_2);

// Projected geometry is available in iPhone OS 4.0 or later and Mac OS X 10.9 or later
#if (__IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED || __MAC_10_9 <= __MAC_OS_X_VERSION_MAX_ALLOWED)

// An MKMapPoint is a coordinate that has been projected for use on the
// two-dimensional map.  An MKMapPoint always refers to a place in the world
// and can be converted to a CLLocationCoordinate2D and back.
typedef struct {
    double x;
    double y;
} MKMapPoint;

typedef struct {
    double width;
    double height;
} MKMapSize;

typedef struct {
    MKMapPoint origin;
    MKMapSize size;
} MKMapRect;

// MKZoomScale provides a conversion factor between MKMapPoints and screen points.
// When MKZoomScale = 1, 1 screen point = 1 MKMapPoint.  When MKZoomScale is
// 0.5, 1 screen point = 2 MKMapPoints.
typedef CGFloat MKZoomScale;
#endif

MK_EXTERN const MKMapSize MKMapSizeWorld NS_AVAILABLE(10_9, 4_0) __TVOS_AVAILABLE(9_2);
// The rect that contains every map point in the world.
MK_EXTERN const MKMapRect MKMapRectWorld NS_AVAILABLE(10_9, 4_0) __TVOS_AVAILABLE(9_2);

// Conversion between unprojected and projected coordinates
MK_EXTERN MKMapPoint MKMapPointForCoordinate(CLLocationCoordinate2D coordinate) NS_AVAILABLE(10_9, 4_0) __TVOS_AVAILABLE(9_2);
MK_EXTERN CLLocationCoordinate2D MKCoordinateForMapPoint(MKMapPoint mapPoint) NS_AVAILABLE(10_9, 4_0) __TVOS_AVAILABLE(9_2);

// Conversion between distances and projected coordinates
MK_EXTERN CLLocationDistance MKMetersPerMapPointAtLatitude(CLLocationDegrees latitude) NS_AVAILABLE(10_9, 4_0) __TVOS_AVAILABLE(9_2);
MK_EXTERN double MKMapPointsPerMeterAtLatitude(CLLocationDegrees latitude) NS_AVAILABLE(10_9, 4_0) __TVOS_AVAILABLE(9_2);

MK_EXTERN CLLocationDistance MKMetersBetweenMapPoints(MKMapPoint a, MKMapPoint b) NS_AVAILABLE(10_9, 4_0) __TVOS_AVAILABLE(9_2);

MK_EXTERN const MKMapRect MKMapRectNull NS_AVAILABLE(10_9, 4_0) __TVOS_AVAILABLE(9_2);

#if (__IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED || __MAC_10_9 <= __MAC_OS_X_VERSION_MAX_ALLOWED)

// Geometric operations on MKMapPoint/Size/Rect.  See CGGeometry.h for 
// information on the CGFloat versions of these functions.
NS_INLINE MKMapPoint MKMapPointMake(double x, double y) {
    return (MKMapPoint){x, y};
}
NS_INLINE MKMapSize MKMapSizeMake(double width, double height) {
    return (MKMapSize){width, height};
}
NS_INLINE MKMapRect MKMapRectMake(double x, double y, double width, double height) {
    return (MKMapRect){ MKMapPointMake(x, y), MKMapSizeMake(width, height) };
}
NS_INLINE double MKMapRectGetMinX(MKMapRect rect) {
    return rect.origin.x;
}
NS_INLINE double MKMapRectGetMinY(MKMapRect rect) {
    return rect.origin.y;
}
NS_INLINE double MKMapRectGetMidX(MKMapRect rect) {
    return rect.origin.x + rect.size.width / 2.0;
}
NS_INLINE double MKMapRectGetMidY(MKMapRect rect) {
    return rect.origin.y + rect.size.height / 2.0;
}
NS_INLINE double MKMapRectGetMaxX(MKMapRect rect) {
    return rect.origin.x + rect.size.width;
}
NS_INLINE double MKMapRectGetMaxY(MKMapRect rect) {
    return rect.origin.y + rect.size.height;
}
NS_INLINE double MKMapRectGetWidth(MKMapRect rect) {
    return rect.size.width;
}
NS_INLINE double MKMapRectGetHeight(MKMapRect rect) {
    return rect.size.height;
}
NS_INLINE BOOL MKMapPointEqualToPoint(MKMapPoint point1, MKMapPoint point2) {
    return point1.x == point2.x && point1.y == point2.y;
}
NS_INLINE BOOL MKMapSizeEqualToSize(MKMapSize size1, MKMapSize size2) {
    return size1.width == size2.width && size1.height == size2.height;
}
NS_INLINE BOOL MKMapRectEqualToRect(MKMapRect rect1, MKMapRect rect2) {
    return 
    MKMapPointEqualToPoint(rect1.origin, rect2.origin) &&
    MKMapSizeEqualToSize(rect1.size, rect2.size);
}

NS_INLINE BOOL MKMapRectIsNull(MKMapRect rect) {
    return MKMapPointEqualToPoint(rect.origin, MKMapRectNull.origin);
}

NS_INLINE BOOL MKMapRectIsEmpty(MKMapRect rect) {
    return MKMapRectIsNull(rect) || (rect.size.width == 0.0 && rect.size.height == 0.0);
}

NS_INLINE NSString *MKStringFromMapPoint(MKMapPoint point) {
    return [NSString stringWithFormat:@"{%.1f, %.1f}", point.x, point.y];
}

NS_INLINE NSString *MKStringFromMapSize(MKMapSize size) {
    return [NSString stringWithFormat:@"{%.1f, %.1f}", size.width, size.height];
}

NS_INLINE NSString *MKStringFromMapRect(MKMapRect rect) {
    return [NSString stringWithFormat:@"{%@, %@}", MKStringFromMapPoint(rect.origin), MKStringFromMapSize(rect.size)];
}
#endif

MK_EXTERN MKMapRect MKMapRectUnion(MKMapRect rect1, MKMapRect rect2) NS_AVAILABLE(10_9, 4_0) __TVOS_AVAILABLE(9_2);
MK_EXTERN MKMapRect MKMapRectIntersection(MKMapRect rect1, MKMapRect rect2) NS_AVAILABLE(10_9, 4_0) __TVOS_AVAILABLE(9_2);
MK_EXTERN MKMapRect MKMapRectInset(MKMapRect rect, double dx, double dy) NS_AVAILABLE(10_9, 4_0) __TVOS_AVAILABLE(9_2);
MK_EXTERN MKMapRect MKMapRectOffset(MKMapRect rect, double dx, double dy) NS_AVAILABLE(10_9, 4_0) __TVOS_AVAILABLE(9_2);
MK_EXTERN void MKMapRectDivide(MKMapRect rect, MKMapRect *slice, MKMapRect *remainder, double amount, CGRectEdge edge) NS_AVAILABLE(10_9, 4_0) __TVOS_AVAILABLE(9_2);

MK_EXTERN BOOL MKMapRectContainsPoint(MKMapRect rect, MKMapPoint point) NS_AVAILABLE(10_9, 4_0) __TVOS_AVAILABLE(9_2);
MK_EXTERN BOOL MKMapRectContainsRect(MKMapRect rect1, MKMapRect rect2) NS_AVAILABLE(10_9, 4_0) __TVOS_AVAILABLE(9_2);
MK_EXTERN BOOL MKMapRectIntersectsRect(MKMapRect rect1, MKMapRect rect2) NS_AVAILABLE(10_9, 4_0) __TVOS_AVAILABLE(9_2);

MK_EXTERN MKCoordinateRegion MKCoordinateRegionForMapRect(MKMapRect rect) NS_AVAILABLE(10_9, 4_0) __TVOS_AVAILABLE(9_2);

MK_EXTERN BOOL MKMapRectSpans180thMeridian(MKMapRect rect) NS_AVAILABLE(10_9, 4_0) __TVOS_AVAILABLE(9_2);
// For map rects that span the 180th meridian, this returns the portion of the rect
// that lies outside of the world rect wrapped around to the other side of the
// world.  The portion of the rect that lies inside the world rect can be 
// determined with MKMapRectIntersection(rect, MKMapRectWorld).
MK_EXTERN MKMapRect MKMapRectRemainder(MKMapRect rect) NS_AVAILABLE(10_9, 4_0) __TVOS_AVAILABLE(9_2);


@interface NSValue (NSValueMapKitGeometryExtensions)

+ (NSValue *)valueWithMKCoordinate:(CLLocationCoordinate2D)coordinate __TVOS_AVAILABLE(9_2);
+ (NSValue *)valueWithMKCoordinateSpan:(MKCoordinateSpan)span __TVOS_AVAILABLE(9_2);

@property (atomic, readonly) CLLocationCoordinate2D MKCoordinateValue __TVOS_AVAILABLE(9_2);
@property (atomic, readonly) MKCoordinateSpan MKCoordinateSpanValue __TVOS_AVAILABLE(9_2);

@end

NS_ASSUME_NONNULL_END
