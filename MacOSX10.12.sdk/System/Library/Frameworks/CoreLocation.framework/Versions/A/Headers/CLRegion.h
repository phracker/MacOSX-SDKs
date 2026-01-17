/*
 *  CLRegion.h
 *  CoreLocation
 *
 *  Copyright (c) 2009-2010 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreLocation/CLLocation.h>
#import <CoreLocation/CLAvailability.h>

NS_ASSUME_NONNULL_BEGIN

@class CLRegionInternal;

/*
 * CLRegionState
 *
 * Discussion:
 *    Represents the current state of the device with reference to a region.
 *
 */
typedef NS_ENUM(NSInteger, CLRegionState) {
	CLRegionStateUnknown,
	CLRegionStateInside,
	CLRegionStateOutside
} NS_ENUM_AVAILABLE(10_10, 7_0) __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

/*
 * CLProximity
 *
 * Discussion:
 *    Represents the current proximity of an entity.
 *
 */
typedef NS_ENUM(NSInteger, CLProximity) {
	CLProximityUnknown,
	CLProximityImmediate,
	CLProximityNear,
	CLProximityFar
} NS_ENUM_AVAILABLE(NA, 7_0) __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

/*
 *  CLRegion
 *  
 *  Discussion:
 *    A logical area.
 */
NS_CLASS_AVAILABLE(10_7, 4_0)
@interface CLRegion : NSObject <NSCopying, NSSecureCoding>
{
@protected
	CLRegionInternal *_internal;
}
/*
 *  initCircularRegionWithCenter:radius:identifier:
 *  
 *  Discussion:
 *    Initialize a region.  center gives the coordinates of center of the region, while radius gives
 *    the distance in meters between the center and the region's boundary. identifier is a description
 *    for the region that could be displayed to the user, and ideally should be chosen by the user.
 *
 *    This method has been deprecated, please see CLCircularRegion.
 */
- (instancetype)initCircularRegionWithCenter:(CLLocationCoordinate2D)center
									  radius:(CLLocationDistance)radius
								  identifier:(NSString *)identifier __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_7,__MAC_10_10,__IPHONE_4_0,__IPHONE_7_0) __TVOS_PROHIBITED;

/*
 *  center
 *  
 *  Discussion:
 *    Returns the coordinate of the center of the region.
 *
 *    This method has been deprecated, please see CLCircularRegion.
 */
@property (readonly, nonatomic) CLLocationCoordinate2D center __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_7,__MAC_10_10,__IPHONE_4_0,__IPHONE_7_0) __TVOS_PROHIBITED;

/*
 *  radius
 *  
 *  Discussion:
 *    Returns the radius of the region.
 *
 *    This method has been deprecated, please see CLCircularRegion.
 */
@property (readonly, nonatomic) CLLocationDistance radius __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_7,__MAC_10_10,__IPHONE_4_0,__IPHONE_7_0) __TVOS_PROHIBITED;

/*
 *  identifier
 *  
 *  Discussion:
 *    Returns the region's identifier.
 */
@property (readonly, nonatomic, copy) NSString *identifier __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*
 *  notifyOnEntry
 *
 *  Discussion:
 *    App will be launched and the delegate will be notified via locationManager:didEnterRegion:
 *    when the user enters the region. By default, this is YES.
 */
@property (nonatomic, assign) BOOL notifyOnEntry __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_7_0);

/*
 *  notifyOnExit
 *
 *  Discussion:
 *    App will be launched and the delegate will be notified via locationManager:didExitRegion:
 *    when the user exits the region. By default, this is YES.
 */
@property (nonatomic, assign) BOOL notifyOnExit __OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_7_0);

/*
 *  containsCoordinate:
 *
 *  Discussion:
 *    Returns YES if the coordinate lies inside the region, and NO otherwise.
 *
 *    This method has been deprecated, please see CLCircularRegion.
 */
- (BOOL)containsCoordinate:(CLLocationCoordinate2D)coordinate __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_7,__MAC_10_10,__IPHONE_4_0,__IPHONE_7_0) __TVOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
