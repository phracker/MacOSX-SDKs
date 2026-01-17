/*
 *  CLLocation.h
 *  CoreLocation
 *
 *  Copyright (c) 2008-2010 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreLocation/CLAvailability.h>

NS_ASSUME_NONNULL_BEGIN

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
 *    Type used to represent the direction in degrees from 0 to 359.9. A negative value indicates an
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
struct CLLocationCoordinate2D {
	CLLocationDegrees latitude;
	CLLocationDegrees longitude;
};
typedef struct CLLocationCoordinate2D CLLocationCoordinate2D;

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
extern const CLLocationAccuracy kCLLocationAccuracyBestForNavigation API_AVAILABLE(ios(4.0), macos(10.7));
extern const CLLocationAccuracy kCLLocationAccuracyBest;
extern const CLLocationAccuracy kCLLocationAccuracyNearestTenMeters;
extern const CLLocationAccuracy kCLLocationAccuracyHundredMeters;
extern const CLLocationAccuracy kCLLocationAccuracyKilometer;
extern const CLLocationAccuracy kCLLocationAccuracyThreeKilometers;

/*
 *  CLLocationDistanceMax
 *
 *  Discussion:
 *  	Used to specify the maximum CLLocationDistance
 */
extern const CLLocationDistance CLLocationDistanceMax API_AVAILABLE(ios(6.0), macos(10.14));

/*
 *  CLTimeIntervalMax
 *
 *  Discussion:
 *  	Used to specify the maximum NSTimeInterval
 */
extern const NSTimeInterval CLTimeIntervalMax API_AVAILABLE(ios(6.0), macos(10.14));

/*
 *  kCLLocationCoordinate2DInvalid
 *  
 *  Discussion:
 *    Used to specify an invalid CLLocationCoordinate2D.
 */
extern const CLLocationCoordinate2D kCLLocationCoordinate2DInvalid API_AVAILABLE(ios(4.0), macos(10.7));

#ifdef __cplusplus
extern "C" {
#endif    

/*
 *  CLLocationCoordinate2DIsValid
 *  
 *  Discussion:
 *    Returns YES if the specified coordinate is valid, NO otherwise.
 */
BOOL CLLocationCoordinate2DIsValid(CLLocationCoordinate2D coord) API_AVAILABLE(ios(4.0), macos(10.7));

/*
 *  CLLocationCoordinate2DMake:
 *
 *  Discussion:
 *    Returns a new CLLocationCoordinate2D at the given latitude and longitude
 */
CLLocationCoordinate2D CLLocationCoordinate2DMake(CLLocationDegrees latitude, CLLocationDegrees longitude) API_AVAILABLE(ios(4.0), macos(10.7));

#ifdef __cplusplus
}
#endif

/*
 *  CLFloor
 *
 *  Discussion:
 *    Encapsulates the information about a floor.
 */
API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos)
@interface CLFloor : NSObject <NSCopying, NSSecureCoding>

/*
 *  level
 *
 *  Discussion:
 *    This is a logical representation that will vary on definition from building-to-building.
 *    Floor 0 will always represent the floor designated as "ground".
 *    This number may be negative to designate floors below the ground floor
 *    and positive to indicate floors above the ground floor.
 *    It is not intended to match any numbering that might actually be used in the building.
 *    It is erroneous to use as an estimate of altitude.
 */
@property(readonly, nonatomic) NSInteger level;

@end

/*
 *  CLLocation
 *  
 *  Discussion:
 *    Represents a geographical coordinate along with accuracy and timestamp information.
 */
API_AVAILABLE(macos(10.6), ios(2.0))
@interface CLLocation : NSObject <NSCopying, NSSecureCoding>
{
@private
	id _internal;
}

/*
 *  initWithLatitude:longitude:
 *  
 *  Discussion:
 *    Initialize with the specified latitude and longitude.
 */
- (instancetype)initWithLatitude:(CLLocationDegrees)latitude
	longitude:(CLLocationDegrees)longitude;

/*
 *  initWithCoordinate:altitude:horizontalAccuracy:verticalAccuracy:timestamp:
 *  
 *  Discussion:
 *    Initialize with the specified parameters.
 */
- (instancetype)initWithCoordinate:(CLLocationCoordinate2D)coordinate
	altitude:(CLLocationDistance)altitude
	horizontalAccuracy:(CLLocationAccuracy)hAccuracy
	verticalAccuracy:(CLLocationAccuracy)vAccuracy
	timestamp:(NSDate *)timestamp;

/*
 *  initWithCoordinate:altitude:horizontalAccuracy:verticalAccuracy:course:speed:timestamp:
 *  
 *  Discussion:
 *    Initialize with the specified parameters.
 */
- (instancetype)initWithCoordinate:(CLLocationCoordinate2D)coordinate
    altitude:(CLLocationDistance)altitude
    horizontalAccuracy:(CLLocationAccuracy)hAccuracy
    verticalAccuracy:(CLLocationAccuracy)vAccuracy
    course:(CLLocationDirection)course
    speed:(CLLocationSpeed)speed
    timestamp:(NSDate *)timestamp API_AVAILABLE(ios(4.2), macos(10.7));

/*
 *  coordinate
 *  
 *  Discussion:
 *    Returns the coordinate of the current location.
 */
@property(readonly, nonatomic) CLLocationCoordinate2D coordinate;

/*
 *  altitude
 *  
 *  Discussion:
 *    Returns the altitude of the location. Can be positive (above sea level) or negative (below sea level).
 */
@property(readonly, nonatomic) CLLocationDistance altitude;

/*
 *  horizontalAccuracy
 *  
 *  Discussion:
 *    Returns the horizontal accuracy of the location. Negative if the lateral location is invalid.
 */
@property(readonly, nonatomic) CLLocationAccuracy horizontalAccuracy;

/*
 *  verticalAccuracy
 *  
 *  Discussion:
 *    Returns the vertical accuracy of the location. Negative if the altitude is invalid.
 */
@property(readonly, nonatomic) CLLocationAccuracy verticalAccuracy;

/*
 *  course
 *  
 *  Discussion:
 *    Returns the course of the location in degrees true North. Negative if course is invalid.
 *
 *  Range:
 *    0.0 - 359.9 degrees, 0 being true North
 */
@property(readonly, nonatomic) CLLocationDirection course API_AVAILABLE(ios(2.2), macos(10.7)) API_UNAVAILABLE(tvos);

/*
 *  speed
 *  
 *  Discussion:
 *    Returns the speed of the location in m/s. Negative if speed is invalid.
 */
@property(readonly, nonatomic) CLLocationSpeed speed API_AVAILABLE(ios(2.2), macos(10.7)) API_UNAVAILABLE(tvos);

/*
 *  timestamp
 *  
 *  Discussion:
 *    Returns the timestamp when this location was determined.
 */
@property(readonly, nonatomic, copy) NSDate *timestamp;

/*
 *  floor
 *
 *  Discussion:
 *    Contains information about the logical floor that you are on
 *    in the current building if you are inside a supported venue.
 *    This will be nil if the floor is unavailable.
 */
@property(readonly, nonatomic, copy, nullable) CLFloor *floor API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos);

/*
 *  getDistanceFrom:
 *
 *  Discussion:
 *    Deprecated. Use -distanceFromLocation: instead.
 */
- (CLLocationDistance)getDistanceFrom:(const CLLocation *)location API_DEPRECATED_WITH_REPLACEMENT("-distanceFromLocation:", ios(2.0, 3.2)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos);

/*
 *  distanceFromLocation:
 *
 *  Discussion:
 *    Returns the lateral distance between two locations.
 */
- (CLLocationDistance)distanceFromLocation:(const CLLocation *)location API_AVAILABLE(ios(3.2), macos(10.6));

@end

NS_ASSUME_NONNULL_END
