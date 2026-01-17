/*
 *  CLGeocoder.h
 *  CoreLocation
 *
 *  Copyright (c) 2010 Apple Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <CoreLocation/CLLocation.h>
#import <CoreLocation/CLAvailability.h>

NS_ASSUME_NONNULL_BEGIN

@class CLRegion;
@class CLPlacemark;
@class CLGeocoderInternal;
@class CNPostalAddress;

// geocoding handler, CLPlacemarks are provided in order of most confident to least confident
typedef void (^CLGeocodeCompletionHandler)(NSArray< CLPlacemark *> * __nullable placemarks, NSError * __nullable error);

CL_EXTERN
API_DEPRECATED("Use MapKit", ios(5.0, 26.0), macos(10.8, 26.0))
@interface CLGeocoder : NSObject
{
@private
    CLGeocoderInternal *_internal;
}

@property (nonatomic, readonly, getter=isGeocoding) BOOL geocoding;

// reverse geocode requests
- (void)reverseGeocodeLocation:(CLLocation *)location completionHandler:(CLGeocodeCompletionHandler)completionHandler API_DEPRECATED("Use MKReverseGeocodingRequest", ios(5.0, 26.0), macos(10.8, 26.0));
- (void)reverseGeocodeLocation:(CLLocation *)location preferredLocale:(nullable NSLocale *)locale completionHandler:(CLGeocodeCompletionHandler)completionHandler API_DEPRECATED("Use MKReverseGeocodingRequest", ios(11.0, 26.0), macos(10.13, 26.0), watchos(4.0, 26.0), tvos(11.0, 26.0));

// forward geocode requests
// geocodeAddressDictionary:completionHandler: takes an address dictionary as defined by the AddressBook framework.
// You can obtain an address dictionary from an ABPerson by retrieving the kABPersonAddressProperty property.
// Alternately, one can be constructed using the kABPersonAddress* keys defined in <AddressBook/ABPerson.h>.
- (void)geocodeAddressDictionary:(NSDictionary *)addressDictionary completionHandler:(CLGeocodeCompletionHandler)completionHandler API_DEPRECATED("Use MKReverseGeocodingRequest", macos(10.8, 10.13), ios(5.0, 11.0), watchos(1.0, 4.0)) API_UNAVAILABLE(visionos);
- (void)geocodeAddressString:(NSString *)addressString inRegion:(nullable CLRegion *)region completionHandler:(CLGeocodeCompletionHandler)completionHandler API_UNAVAILABLE(visionos);
- (void)geocodeAddressString:(NSString *)addressString inRegion:(nullable CLRegion *)region preferredLocale:(nullable NSLocale *)locale completionHandler:(CLGeocodeCompletionHandler)completionHandler API_DEPRECATED("Use MKGeocodingRequest", macos(10.13, 26.0), ios(11.0, 26.0), watchos(4.0, 26.0), tvos(11.0, 26.0)) API_UNAVAILABLE(visionos);
- (void)geocodeAddressString:(NSString *)addressString inRegionCenteredAt:(CLLocationCoordinate2D)centroid inRegionRadius:(CLLocationDistance)radius preferredLocale:(nullable NSLocale *)locale completionHandler:(CLGeocodeCompletionHandler)completionHandler API_DEPRECATED("Use MKGeocodingRequest", visionos(1.0, 26.0)) API_UNAVAILABLE(ios, macos, tvos, watchos);
- (void)geocodeAddressString:(NSString *)addressString completionHandler:(CLGeocodeCompletionHandler)completionHandler API_DEPRECATED("Use MKGeocodingRequest", ios(5.0, 26.0), macos(10.8, 26.0));

- (void)cancelGeocode API_DEPRECATED("Use MKGeocodingRequest", ios(5.0, 26.0), macos(10.8, 26.0));

@end

@interface CLGeocoder (ContactsAdditions)
- (void)geocodePostalAddress:(CNPostalAddress *)postalAddress completionHandler:(CLGeocodeCompletionHandler)completionHandler API_DEPRECATED("Use MKReverseGeocodingRequest", ios(11.0, 26.0), macos(10.13, 26.0), watchos(4.0, 26.0)) API_UNAVAILABLE(tvos);
- (void)geocodePostalAddress:(CNPostalAddress *)postalAddress preferredLocale:(nullable NSLocale *)locale completionHandler:(CLGeocodeCompletionHandler)completionHandler API_DEPRECATED("Use MKReverseGeocodingRequest", macos(10.13, 26.0), ios(11.0, 26.0), watchos(4.0, 26.0)) API_UNAVAILABLE(tvos);
@end

NS_ASSUME_NONNULL_END
