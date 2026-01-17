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
@interface CLPlacemark : NSObject <NSCopying, NSCoding>
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
- (id)initWithPlacemark:(CLPlacemark *)placemark;

/*
 *  location
 *  
 *  Discussion:
 *    Returns the geographic location associated with the placemark.
 */
@property (nonatomic, readonly) CLLocation *location;

/*
 *  region
 *  
 *  Discussion:
 *    Returns the geographic region associated with the placemark.
 */
@property (nonatomic, readonly) CLRegion *region;

/*
 *  addressDictionary
 *  
 *  Discussion:
 *    This dictionary can be formatted as an address using ABCreateStringWithAddressDictionary,
 *    defined in the AddressBookUI framework.
 */
@property (nonatomic, readonly) NSDictionary *addressDictionary;

// address dictionary properties
@property (nonatomic, readonly) NSString *name; // eg. Apple Inc.
@property (nonatomic, readonly) NSString *thoroughfare; // street address, eg. 1 Infinite Loop
@property (nonatomic, readonly) NSString *subThoroughfare; // eg. 1
@property (nonatomic, readonly) NSString *locality; // city, eg. Cupertino
@property (nonatomic, readonly) NSString *subLocality; // neighborhood, common name, eg. Mission District
@property (nonatomic, readonly) NSString *administrativeArea; // state, eg. CA
@property (nonatomic, readonly) NSString *subAdministrativeArea; // county, eg. Santa Clara
@property (nonatomic, readonly) NSString *postalCode; // zip code, eg. 95014
@property (nonatomic, readonly) NSString *ISOcountryCode; // eg. US
@property (nonatomic, readonly) NSString *country; // eg. United States
@property (nonatomic, readonly) NSString *inlandWater; // eg. Lake Tahoe
@property (nonatomic, readonly) NSString *ocean; // eg. Pacific Ocean
@property (nonatomic, readonly) NSArray *areasOfInterest; // eg. Golden Gate Park
@end