/*
 *  CLLocationManager+CLVisitExtensions.h
 *  CoreLocation
 *
 *  Copyright (c) 2014 Apple Inc. All rights reserved.
 *
 */

#import <CoreLocation/CLLocationManager.h>

#import <CoreLocation/CLAvailability.h>

NS_ASSUME_NONNULL_BEGIN

@interface CLLocationManager (CLVisitExtensions)

/*
 *  startMonitoringVisits
 *
 *  Discussion:
 *    Begin monitoring for visits.  All CLLLocationManagers allocated by your
 *    application, both current and future, will deliver detected visits to
 *    their delegates.  This will continue until -stopMonitoringVisits is sent
 *    to any such CLLocationManager, even across application relaunch events.
 *
 *    Detected visits are sent to the delegate's -locationManager:didVisit:
 *    method.
 */
- (void)startMonitoringVisits NS_AVAILABLE(NA, 8_0) __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

/*
 *  stopMonitoringVisits
 *
 *  Discussion:
 *    Stop monitoring for visits.  To resume visit monitoring, send
 *    -startMonitoringVisits.
 *
 *    Note that stopping and starting are asynchronous operations and may not
 *    immediately reflect in delegate callback patterns.
 */
- (void)stopMonitoringVisits NS_AVAILABLE(NA, 8_0) __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
