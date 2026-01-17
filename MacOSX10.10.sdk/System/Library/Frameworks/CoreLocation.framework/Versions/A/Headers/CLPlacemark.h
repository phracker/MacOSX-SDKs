/*
 *  CLPlacemark.h
 *  CoreLocation
 *
 *  Copyright (c) 2010 Apple Inc. All rights reserved.
 */
#import <Foundation/Foundation.h>
#import <CoreLocation/CLAvailability.h>

@class CLLocation;
@class CLRegion;
@class CLPlacemarkInternal;

/*
 *  CLPlacemark
 *  
 *  Discussion:
 *    Represents placemark data for a geographic location. Placemark data can be
 *    information such as the country, state, city, and street address.
 */

NS_CLASS_AVAILABLE(10_8,5_0)
@interface CLPlacemark : NSObject <NSCopying, NSSecureCoding>
{
@private
    CLPlacemarkInternal *_internal;
}

/*
 * initWithPlacemark:
 *
 * Discussion:
 *   Initialize a newly allocated placemark from another placemark, copying its data.
 */
- (instancetype)initWithPlacemark:(CLPlacemark *)placemark;

/*
 *  location
 *  
 *  Discussion:
 *    Returns the geographic location associated with the placemark.
 */
@property (nonatomic, readonly, copy) CLLocation *location;

/*
 *  region
 *  
 *  Discussion:
 *    Returns the geographic region associated with the placemark.
 */
@property (nonatomic, readonly, copy) CLRegion *region;

/*
 *  addressDictionary
 *  
 *  Discussion:
 *    This dictionary can be formatted as an address using ABCreateStringWithAddressDictionary,
 *    defined in the AddressBookUI framework.
 */
@property (nonatomic, readonly, copy) NSDictionary *addressDictionary;

// address dictionary properties
@property (nonatomic, readonly, copy) NSString *name; // eg. Apple Inc.
@property (nonatomic, readonly, copy) NSString *thoroughfare; // street address, eg. 1 Infinite Loop
@property (nonatomic, readonly, copy) NSString *subThoroughfare; // eg. 1
@property (nonatomic, readonly, copy) NSString *locality; // city, eg. Cupertino
@property (nonatomic, readonly, copy) NSString *subLocality; // neighborhood, common name, eg. Mission District
@property (nonatomic, readonly, copy) NSString *administrativeArea; // state, eg. CA
@property (nonatomic, readonly, copy) NSString *subAdministrativeArea; // county, eg. Santa Clara
@property (nonatomic, readonly, copy) NSString *postalCode; // zip code, eg. 95014
@property (nonatomic, readonly, copy) NSString *ISOcountryCode; // eg. US
@property (nonatomic, readonly, copy) NSString *country; // eg. United States
@property (nonatomic, readonly, copy) NSString *inlandWater; // eg. Lake Tahoe
@property (nonatomic, readonly, copy) NSString *ocean; // eg. Pacific Ocean
@property (nonatomic, readonly, copy) NSArray *areasOfInterest; // eg. Golden Gate Park
@end
