//
//  CNPostalAddress.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/ContactsDefines.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract An immutable value object representing a postal address.
 *
 * @discussion CNPostalAddress is thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNPostalAddress : NSObject <NSCopying, NSMutableCopying, NSSecureCoding>

/*! multi-street address is delimited with carriage returns “\n” */
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *street;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *subLocality              NS_AVAILABLE(10_12_4, 10_3);
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *city;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *subAdministrativeArea    NS_AVAILABLE(10_12_4, 10_3);
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *state;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *postalCode;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *country;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *ISOCountryCode;

/*! Returns a user displayable property name. */
+ (NSString *)localizedStringForKey:(NSString *)key;

@end


// Properties that are always fetched. Can be used with key value coding and observing.
CONTACTS_EXTERN NSString * const CNPostalAddressStreetKey                            NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNPostalAddressSubLocalityKey                       NS_AVAILABLE(10_12_4, 10_3);
CONTACTS_EXTERN NSString * const CNPostalAddressCityKey                              NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNPostalAddressSubAdministrativeAreaKey             NS_AVAILABLE(10_12_4, 10_3);
CONTACTS_EXTERN NSString * const CNPostalAddressStateKey                             NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNPostalAddressPostalCodeKey                        NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNPostalAddressCountryKey                           NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNPostalAddressISOCountryCodeKey                    NS_AVAILABLE(10_11, 9_0);


NS_ASSUME_NONNULL_END
