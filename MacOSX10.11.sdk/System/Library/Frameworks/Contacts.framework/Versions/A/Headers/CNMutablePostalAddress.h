//
//  CNMutablePostalAddress.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Contacts/CNPostalAddress.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract A mutable value object representing a postal address.
 *
 * @discussion CNMutablePostalAddress is not thread safe.
 *
 * @note To remove properties when saving a mutable postal address, set string properties to empty values.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNMutablePostalAddress : CNPostalAddress

/*! multi-street address is delimited with carriage returns “\n” */
@property (copy, NS_NONATOMIC_IOSONLY) NSString *street;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *city;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *state;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *postalCode;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *country;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *ISOCountryCode;

@end

NS_ASSUME_NONNULL_END
