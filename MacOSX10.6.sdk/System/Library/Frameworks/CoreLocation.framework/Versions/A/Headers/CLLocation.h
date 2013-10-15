
/*
 *  CLLocation.h
 *  CoreLocation
 *
 *  Copyright 2008 Apple Inc. All rights reserved.
 *
 */

#if ( !TARGET_OS_MAC || MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6 )

#import <Availability.h>
#import <Foundation/Foundation.h>

/*
 *  CLLocationDegrees
 *  
 *  Discussion:
 *    Type used to represent a latitude or longitude coordinate in degrees under the WGS 84 reference
 *    frame. The degree can be positive (North and East) or negative (South and West).  
 */
typedef double CLLocationDegrees;

/*
 *  CLLocationAccuracy
 *  
 *  Discussion:
 *    Type used to represent a location accuracy level in meters. The lower the value in meters, the
 *    more physically precise the location is. A negative accuracy value indicates an invalid location.
 */
typedef double CLLocationAccuracy;

/*
 *  CLLocationSpeed
 *  
 *  Discussion:
 *    Type used to represent the speed in meters per second.
 */
typedef double CLLocationSpeed;

/*
 *  CLLocationDirection
 *  
 *  Discussion:
 *    Type used to represent the direction in degrees, where 0 degrees is true North. A negative value indicates an
 *    invalid direction.
 */
typedef double CLLocationDirection;


/*
 *  CLLocationCoordinate2D
 *  
 *  Discussion:
 *    A structure that contains a geographical coordinate.
 *
 *  Fields:
 *    latitude:
 *      The latitude in degrees.
 *    longitude:
 *      The longitude in degrees.
 */
typedef struct {
	CLLocationDegrees latitude;
	CLLocationDegrees longitude;
} CLLocationCoordinate2D;

/*
 *  CLLocationDistance
 *  
 *  Discussion:
 *    Type used to represent a distance in meters.
 */
typedef double CLLocationDistance;

/*
 *  kCLDistanceFilterNone
 *  
 *  Discussion:
 *    Use as the distanceFilter property for CLLocationManager. This indicates 
 *    to the location service that no minimum movement filter is desired - ie, client will be informed
 *    of any movement.
 */
extern const CLLocationDistance kCLDistanceFilterNone;

/*
 *  kCLLocationAccuracy<x>
 *  
 *  Discussion:
 *    Used to specify the accuracy level desired. The location service will try its best to achieve
 *    your desired accuracy. However, it is not guaranteed. To optimize
 *    power performance, be sure to specify an appropriate accuracy for your usage scenario (eg,
 *    use a large accuracy value when only a coarse location is needed).
 */
extern const CLLocationAccuracy kCLLocationAccuracyBest;
extern const CLLocationAccuracy kCLLocationAccuracyNearestTenMeters;
extern const CLLocationAccuracy kCLLocationAccuracyHundredMeters;
extern const CLLocationAccuracy kCLLocationAccuracyKilometer;
extern const CLLocationAccuracy kCLLocationAccuracyThreeKilometers;


/*
 *  CLLocation
 *  
 *  Discussion:
 *    Represents a geographical coordinate along with accuracy and timestamp information.
 */
@interface CLLocation : NSObject <NSCopying, NSCoding>
{
@private
	id _internal;
}

/*
 *  coordinate
 *  
 *  Discussion:
 *    Returns the coordinate of the current location.
 */
@property(readonly, NS_NONATOMIC_IPHONEONLY) CLLocationCoordinate2D coordinate;

/*
 *  altitude
 *  
 *  Discussion:
 *    Returns the altitude of the location. Can be positive (above sea level) or negative (below sea level).
 */
@property(readonly, NS_NONATOMIC_IPHONEONLY) CLLocationDistance altitude;

/*
 *  horizontalAccuracy
 *  
 *  Discussion:
 *    Returns the horizontal accuracy of the location. Negative if the lateral location is invalid.
 */
@property(readonly, NS_NONATOMIC_IPHONEONLY) CLLocationAccuracy horizontalAccuracy;

/*
 *  verticalAccuracy
 *  
 *  Discussion:
 *    Returns the vertical accuracy of the location. Negative if the altitude is invalid.
 */
@property(readonly, NS_NONATOMIC_IPHONEONLY) CLLocationAccuracy verticalAccuracy;

/*
 *  course
 *  
 *  Discussion:
 *    Returns the course of the location in degrees true North. Negative if course is invalid.
 */
@property(readonly, NS_NONATOMIC_IPHONEONLY) CLLocationDirection course __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_2);

/*
 *  speed
 *  
 *  Discussion:
 *    Returns the speed of the location in m/s. Negative if speed is invalid.
 */
@property(readonly, NS_NONATOMIC_IPHONEONLY) CLLocationSpeed speed __OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_2);

/*
 *  timestamp
 *  
 *  Discussion:
 *    Returns the timestamp when this location was determined.
 */
@property(readonly, NS_NONATOMIC_IPHONEONLY) NSDate *timestamp;

/*
 *  initWithLatitude:longitude:
 *  
 *  Discussion:
 *    Initialize with the specified latitude and longitude.
 */
- (id)initWithLatitude:(CLLocationDegrees)latitude
	longitude:(CLLocationDegrees)longitude;

/*
 *  initWithCoordinate:altitude:horizontalAccuracy:verticalAccuracy:timestamp:
 *  
 *  Discussion:
 *    Initialize with the specified parameters.
 */
- (id)initWithCoordinate:(CLLocationCoordinate2D)coordinate
	altitude:(CLLocationDistance)altitude
	horizontalAccuracy:(CLLocationAccuracy)hAccuracy
	verticalAccuracy:(CLLocationAccuracy)vAccuracy
	timestamp:(NSDate *)timestamp;

/*
 *  description
 *  
 *  Discussion:
 *    Returns a string representation of the location.
 */
- (NSString *)description;

/*
 *  distanceFromLocation:
 *
 *  Discussion:
 *    Returns the lateral distance between two locations.
 */
- (CLLocationDistance)distanceFromLocation:(const CLLocation *)location __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_3_0 );

/*
 *  getDistanceFrom:
 *
 *  Discussion:
 *    Not available on Mac OS X. See -distanceFromLocation:.
 */
- (CLLocationDistance)getDistanceFrom:(const CLLocation *)location __OSX_AVAILABLE_STARTING( __MAC_NA, __IPHONE_2_0 );

@end

#endif
