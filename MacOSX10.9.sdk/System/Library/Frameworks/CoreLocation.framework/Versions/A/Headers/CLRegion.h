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

/*
 *  CLRegion
 *  
 *  Discussion:
 *    A geographic area.
 */
NS_CLASS_AVAILABLE(10_7, 4_0)
@interface CLRegion : NSObject <NSCopying, NSCoding>
{
@private
	id _internal;
}


/*
 *  initCircularRegionWithCenter:radius:identifier:
 *  
 *  Discussion:
 *    Initialize a region.  center gives the coordinates of center of the region, while radius gives
 *    the distance in meters between the center and the region's boundary. identifier is a description
 *    for the region that could be displayed to the user, and ideally should be chosen by the user.
 */
- (id)initCircularRegionWithCenter:(CLLocationCoordinate2D)center
                            radius:(CLLocationDistance)radius
                        identifier:(NSString *)identifier __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*
 *  center
 *  
 *  Discussion:
 *    Returns the coordinate of the center of the region.
 */
@property (readonly, nonatomic) CLLocationCoordinate2D center __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*
 *  radius
 *  
 *  Discussion:
 *    Returns the radius of the region.
 */
@property (readonly, nonatomic) CLLocationDistance radius __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*
 *  identifier
 *  
 *  Discussion:
 *    Returns the region's identifier.
 */
@property (readonly, nonatomic) NSString *identifier __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*
 *  containsCoordinate:
 *
 *  Discussion:
 *    Returns YES if the coordinate lies inside the region, and NO otherwise.
 */
- (BOOL)containsCoordinate:(CLLocationCoordinate2D)coordinate __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

@end
