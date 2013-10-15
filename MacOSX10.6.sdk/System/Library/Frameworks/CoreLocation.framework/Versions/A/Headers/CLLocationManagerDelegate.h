
/*
 *  CLLocationManagerDelegate.h
 *  CoreLocation
 *
 *  Copyright 2008 Apple Inc. All rights reserved.
 *
 */

#if ( !TARGET_OS_MAC || MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6 )

#import <Foundation/Foundation.h>

@class CLLocation;
@class CLLocationManager;


/*
 *  CLLocationManagerDelegate
 *  
 *  Discussion:
 *    Delegate for CLLocationManager.
 */
@protocol CLLocationManagerDelegate<NSObject>

@optional

/*
 *  locationManager:didUpdateToLocation:fromLocation:
 *  
 *  Discussion:
 *    Invoked when a new location is available. oldLocation may be nil if there is no previous location
 *    available.
 */
- (void)locationManager:(CLLocationManager *)manager
	didUpdateToLocation:(CLLocation *)newLocation
	fromLocation:(CLLocation *)oldLocation;

/*
 *  locationManager:didFailWithError:
 *  
 *  Discussion:
 *    Invoked when an error has occurred.
 */
- (void)locationManager:(CLLocationManager *)manager
	didFailWithError:(NSError *)error;

@end

#endif
