//
//  CSSearchableItemAttributeSet_Places.h
//  CoreSpotlight
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <CoreSpotlight/CSSearchableItemAttributeSet.h>

@interface CSSearchableItemAttributeSet (CSPlaces)

//A publishable entry providing a synopsis of the contents of the item.
@property(nullable, copy) NSString *headline;

//Other editorial instructions concerning the use of the item, such as embargoes and warnings.
@property(nullable, copy) NSString *instructions;

//The location (e.g., street name) for the item according to guidelines established by the provider.
@property(nullable, copy) NSString *thoroughfare;

//The sub-location (e.g., street number) for the item according to guidelines established by the provider.
@property(nullable, copy) NSString *subThoroughfare;

//The postal code for the item according to guidelines established by the provider.
@property(nullable, copy) NSString *postalCode;

//Identifies city of item origin according to guidelines established by the provider.
@property(nullable, copy) NSString *city;

//Identifies Province/State of origin according to guidelines established by the provider.
@property(nullable, copy) NSString *stateOrProvince;

//Provides full, publishable, name of the country/primary location where the
//intellectual property of the item was created,according to guidelines of the provider.
@property(nullable, copy) NSString *country;

// The fully formatted address of the item (obtained from MapKit)
@property(nullable, copy) NSString *fullyFormattedAddress;

//The altitude of the item in meters above sea level, expressed
//using the WGS84 datum.  Negative values lie below sea level.
@property(nullable, strong) NSNumber *altitude;

//The latitude of the item in degrees north of the equator, expressed
//using the WGS84 datum.  Negative values lie south of the equator.
@property(nullable, strong) NSNumber *latitude;

//The longitude of the item in degrees east of the prime meridian,
//expressed using the WGS84 datum.  Negative values lie west of the prime meridian.
@property(nullable, strong) NSNumber *longitude;

//The speed of the item, in kilometers per hour.
@property(nullable, strong) NSNumber *speed;

//The timestamp on the item.  This generally is used to indicate the time at
//which the event captured by the item took place.
@property(nullable, strong) NSDate *timestamp;

//The direction of the item's image, in degrees from true north.
@property(nullable, strong) NSNumber *imageDirection;

//The name of the location or point of interest associated with the item. The name may be user provided.
@property(nullable, copy) NSString *namedLocation;

//The direction of travel of the item, in degrees from true north.
@property(nullable, strong) NSNumber *GPSTrack;

@property(nullable, copy) NSString *GPSStatus;

@property(nullable, copy) NSString *GPSMeasureMode;

@property(nullable, strong) NSNumber *GPSDOP;

@property(nullable, copy) NSString *GPSMapDatum;

@property(nullable, strong) NSNumber *GPSDestLatitude;

@property(nullable, strong) NSNumber *GPSDestLongitude;

@property(nullable, strong) NSNumber *GPSDestBearing;

@property(nullable, strong) NSNumber *GPSDestDistance;

@property(nullable, copy) NSString *GPSProcessingMethod;

@property(nullable, copy) NSString *GPSAreaInformation;

@property(nullable, strong) NSDate *GPSDateStamp;

@property(nullable, strong) NSNumber *GPSDifferental;

@end
