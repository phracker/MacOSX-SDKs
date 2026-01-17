//
//  CNContactFormatter.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/ContactsDefines.h>
#import <Contacts/CNContact.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @abstract The formatting styles for contact names.
 */
typedef NS_ENUM(NSInteger, CNContactFormatterStyle)
{
    /*! Combine the contact name components into a displayable full name. */
    CNContactFormatterStyleFullName,
    /*! Combine the contact phonetic name components into a displayable phonetic full name.*/
    CNContactFormatterStylePhoneticFullName,
} NS_ENUM_AVAILABLE(10_11, 9_0);

/*!
 * @abstract The formatting order of the contact name components.
 */
typedef NS_ENUM(NSInteger, CNContactDisplayNameOrder)
{
    CNContactDisplayNameOrderUserDefault,
    CNContactDisplayNameOrderGivenNameFirst,
    CNContactDisplayNameOrderFamilyNameFirst,
} NS_ENUM_AVAILABLE(10_11, 9_0);


/*!
 * @abstract Formats a contact name.
 *
 * @discussion This formatter handles international ordering and delimiting of the contact name components. This includes applying the user defaults when appropriate.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNContactFormatter : NSFormatter <NSSecureCoding>

/*!
 * @abstract The contact key descriptor required for the formatter.
 *
 * @discussion Use to fetch all contact keys required for the formatter style. Can combine key descriptors for different formatter styles in the fetch.
 *
 * @param style The formatting style to be used for the contact name.
 * @return The contact key descriptor for the formatting style.
 */
+ (id<CNKeyDescriptor>)descriptorForRequiredKeysForStyle:(CNContactFormatterStyle)style;

/*!
 * @abstract The contact key descriptor required for the name order.
 *
 * @discussion Use to fetch all contact keys required for +nameOrderForContact:. Can combine key descriptors for different formatter styles in the fetch.
 *
 * @return The contact key descriptor for the name order.
 */
@property (class, readonly) id<CNKeyDescriptor> descriptorForRequiredKeysForNameOrder;

/*!
 * @abstract The contact key descriptor required for the name delimiter.
 *
 * @discussion Use to fetch all contact keys required for +delimiterForContact:. Can combine key descriptors for different formatter styles in the fetch.
 *
 * @return The contact key descriptor for the name delimiter.
 */
@property (class, readonly) id<CNKeyDescriptor> descriptorForRequiredKeysForDelimiter;


/*!
 * @abstract Formats the contact name.
 *
 * @param contact The contact whose name is to be formatted.
 * @param style The formatting style to be used for the contact name.
 * @return The formatted contact name.
 */
+ (nullable NSString *)stringFromContact:(CNContact *)contact style:(CNContactFormatterStyle)style;

/*!
 * @abstract Formats the contact name returning an attributed string.
 *
 * @discussion This behaves like +stringFromContact:style: except it returns an attributed string. Includes the attribute key CNContactPropertyAttribute.
 *
 * @param contact The contact whose name is to be formatted.
 * @param style The formatting style to be used for the contact name.
 * @param attributes The default attributes to use. See NSFormatter for details.
 * @return The formatted contact name as an attributed string.
 */
+ (nullable NSAttributedString *)attributedStringFromContact:(CNContact *)contact style:(CNContactFormatterStyle)style defaultAttributes:(nullable NSDictionary *)attributes;

/*!
 * @abstract The recommended name order for a given contact.
 */
+ (CNContactDisplayNameOrder)nameOrderForContact:(CNContact *)contact;

/*!
 * @abstract The recommended delimiter to use between name components for a given contact.
 */
+ (NSString *)delimiterForContact:(CNContact *)contact;

/*!
 * @abstract The style for a contact formatter instance.
 *
 * @discussion The default value is CNContactFormatterStyleFullName.
 */
@property (NS_NONATOMIC_IOSONLY) CNContactFormatterStyle style;

/*!
 * @abstract Formats the contact name.
 *
 * @param contact The contact whose name is to be formatted.
 * @return The formatted contact name.
 */
- (nullable NSString *)stringFromContact:(CNContact *)contact;

/*!
 * @abstract Formats the contact name returning an attributed string.
 *
 * @discussion This behaves like -stringFromContact:style: except it returns an attributed string. CNContactPropertyAttribute key has the value of a CNContact name property key.
 *
 * @param contact The contact whose name is to be formatted.
 * @param attributes The default attributes to use. See NSFormatter for details.
 * @return The formatted contact name as an attributed string.
 */
- (nullable NSAttributedString *)attributedStringFromContact:(CNContact *)contact defaultAttributes:(nullable NSDictionary *)attributes;

@end


// Attribute key whose value is a CNContact name component property key.
CONTACTS_EXTERN NSString * const CNContactPropertyAttribute;

NS_ASSUME_NONNULL_END
