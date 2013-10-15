
/*
 *  CLLocationManager.h
 *  CoreLocation
 *
 *  Copyright 2008 Apple Inc. All rights reserved.
 *
 */

#if ( !TARGET_OS_MAC || MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6 )

#import <Foundation/Foundation.h>

@class CLLocation;
@protocol CLLocationManagerDelegate;


/*
 *  CLLocationManager
 *  
 *  Discussion:
 *    The CLLocationManager object is your entry point to the location service.
 */
@interface CLLocationManager : NSObject
{
@private
	id _internal;
}

/*
 *  locationServicesEnabled
 *  
 *  Discussion:
 *      Determines whether the user has location services enabled on the device.
 *      If NO, and you proceed to call other CoreLocation API, user will be prompted with the warning
 *      dialog. You may want to check this value and use location services only when explicitly enabled by the user.
 */
+ (BOOL)locationServicesEnabled;

@property(assign, NS_NONATOMIC_IPHONEONLY) id<CLLocationManagerDelegate> delegate;

/*
 *  locationServicesEnabled
 *  
 *  Discussion:
 *      Deprecated. Use +locationServicesEnabled instead.
 */
@property(readonly, NS_NONATOMIC_IPHONEONLY) BOOL locationServicesEnabled __OSX_AVAILABLE_STARTING( __MAC_10_6, __IPHONE_2_0 );

/*
 *  distanceFilter
 *  
 *  Discussion:
 *      Specifies the minimum update distance in meters. Client will not be notified of movements of less 
 *      than the stated value, unless the accuracy has improved. Pass in kCLDistanceFilterNone to be 
 *      notified of all movements. By default, kCLDistanceFilterNone is used.
 */
@property(assign, NS_NONATOMIC_IPHONEONLY) CLLocationDistance distanceFilter;

/*
 *  desiredAccuracy
 *  
 *  Discussion:
 *      The desired location accuracy. The location service will try its best to achieve
 *      your desired accuracy. However, it is not guaranteed. To optimize
 *      power performence, be sure to specify an appropriate accuracy for your usage scenario (eg,
 *      use a large accuracy value when only a coarse location is needed). Use kCLLocationAccuracyBest to
 *      achieve the best possible accuracy. By default, kCLLocationAccuracyBest is used.
 */
@property(assign, NS_NONATOMIC_IPHONEONLY) CLLocationAccuracy desiredAccuracy;

/*
 *  location
 *  
 *  Discussion:
 *      The last location received. Will be nil until a location has been received.
 */
@property(readonly, NS_NONATOMIC_IPHONEONLY) CLLocation *location;

/*
 *  startUpdatingLocation
 *  
 *  Discussion:
 *      Start updating locations.
 */
- (void)startUpdatingLocation;

/*
 *  stopUpdatingLocation
 *  
 *  Discussion:
 *      Stop updating locations.
 */
- (void)stopUpdatingLocation;

@end

#endif
