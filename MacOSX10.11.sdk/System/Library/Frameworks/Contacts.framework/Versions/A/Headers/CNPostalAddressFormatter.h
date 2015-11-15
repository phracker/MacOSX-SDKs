//
//  CNPostalAddressFormatter.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/ContactsDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class CNPostalAddress;


/*!
 * @abstract The formatting styles for postal addresses.
 */
typedef NS_ENUM(NSInteger, CNPostalAddressFormatterStyle)
{
    /*! Combine the postal address components into a multi-line mailing address. */
    CNPostalAddressFormatterStyleMailingAddress,
} NS_ENUM_AVAILABLE(10_11, 9_0);


/*!
 * @abstract Formats a postal address.
 *
 * @discussion This formatter handles international formatting of a postal address.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNPostalAddressFormatter : NSFormatter

/*!
 * @abstract Formats the postal address.
 *
 * @param postalAddress The postal address to be formatted.
 * @param style The formatting style to be used for the postal address.
 * @return The formatted postal address.
 */
+ (NSString *)stringFromPostalAddress:(CNPostalAddress *)postalAddress style:(CNPostalAddressFormatterStyle)style;


/*!
 * @abstract Formats the postal address returning an attributed string.
 *
 * @discussion This behaves like +stringFromPostalAddress: except it returns an attributed string. Includes attribute keys CNPostalAddressPropertyAttribute and CNPostalAddressLocalizedPropertyNameAttribute.
 *
 * @param postalAddress The postal address to be formatted.
 * @param style The formatting style to be used for the postal address.
 * @param attributes The default attributes to use. See NSFormatter for details.
 * @return The formatted postal address as an attributed string.
 */
+ (NSAttributedString *)attributedStringFromPostalAddress:(CNPostalAddress *)postalAddress style:(CNPostalAddressFormatterStyle)style withDefaultAttributes:(NSDictionary *)attributes;

/*!
 * @abstract The style for a postal address formatter instance.
 *
 * @discussion The default value is CNPostalAddressFormatterStyleMailingAddress.
 */
@property (NS_NONATOMIC_IOSONLY) CNPostalAddressFormatterStyle style;

/*!
 * @abstract Formats the postal address.
 *
 * @param postalAddress The postal address to be formatted.
 * @return The formatted postal address.
 */
- (NSString *)stringFromPostalAddress:(CNPostalAddress *)postalAddress;

/*!
 * @abstract Formats the postal address returning an attributed string.
 *
 * @discussion This behaves like +stringFromPostalAddress: except it returns an attributed string. Includes attribute keys CNPostalAddressPropertyAttribute and CNPostalAddressLocalizedPropertyNameAttribute.
 *
 * @param postalAddress The postal address to be formatted.
 * @param attributes The default attributes to use. See NSFormatter for details.
 * @return The formatted postal address as an attributed string.
 */
- (NSAttributedString *)attributedStringFromPostalAddress:(CNPostalAddress *)postalAddress withDefaultAttributes:(NSDictionary *)attributes;

@end


// Attribute key whose value is a CNPostalAddress property key.
CONTACTS_EXTERN NSString * const CNPostalAddressPropertyAttribute;

// Attribute key whose value is a localized version of the CNPostalAddress property key.
CONTACTS_EXTERN NSString * const CNPostalAddressLocalizedPropertyNameAttribute;

NS_ASSUME_NONNULL_END
