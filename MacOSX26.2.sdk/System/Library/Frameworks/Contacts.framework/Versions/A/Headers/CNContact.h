//
//  CNContact.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/ContactsDefines.h>
#import <Contacts/CNLabeledValue.h>
#import <Contacts/CNPhoneNumber.h>
#import <Contacts/CNPostalAddress.h>
#import <Contacts/CNContactRelation.h>
#import <Contacts/CNSocialProfile.h>
#import <Contacts/CNInstantMessageAddress.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, CNContactType)
{
    CNContactTypePerson,
    CNContactTypeOrganization,
} NS_ENUM_AVAILABLE(10_11, 9_0);

/*!
 * @abstract Sort order for contacts.
 *
 * @discussion CNContactSortOrderUserDefault is the user's preferred sort order.
 */
typedef NS_ENUM(NSInteger, CNContactSortOrder)
{
    CNContactSortOrderNone,
    CNContactSortOrderUserDefault,
    CNContactSortOrderGivenName,
    CNContactSortOrderFamilyName,
} NS_ENUM_AVAILABLE(10_11, 9_0);

/*! This protocol is reserved for Contacts framework usage. */
@protocol CNKeyDescriptor <NSObject, NSSecureCoding, NSCopying>
@end

/*! Allows contact property keys to be used with keysToFetch. */
@interface NSString (Contacts) <CNKeyDescriptor>
@end


/*!
 * @abstract An immutable value object representing a contact.
 *
 * @discussion CNContact is thread safe. 
 *
 * If using a CNContact instance where you are not certain of the keys that were fetched, use isKeyAvailable: or areKeysAvailable:. If these return NO you need to refetch the contact by the contact identifier with the keys you want to fetch. Accessing a property that was not fetched will throw CNContactPropertyNotFetchedExceptionName.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNContact : NSObject <NSCopying, NSMutableCopying, NSSecureCoding>

/*! The identifier is unique among contacts on the device. It can be saved and used for fetching contacts next application launch. */
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *identifier;

@property (readonly, NS_NONATOMIC_IOSONLY) CNContactType contactType;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *namePrefix;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *givenName;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *middleName;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *familyName;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *previousFamilyName;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *nameSuffix;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *nickname;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *organizationName;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *departmentName;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *jobTitle;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *phoneticGivenName;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *phoneticMiddleName;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *phoneticFamilyName;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *phoneticOrganizationName NS_AVAILABLE(10_12, 10_0);

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *note;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSData *imageData;
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSData *thumbnailImageData;
@property (readonly, NS_NONATOMIC_IOSONLY) BOOL imageDataAvailable NS_AVAILABLE(10_12, 9_0);

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<CNPhoneNumber*>*>             *phoneNumbers;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<NSString*>*>                  *emailAddresses;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<CNPostalAddress*>*>           *postalAddresses;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<NSString*>*>                  *urlAddresses;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<CNContactRelation*>*>         *contactRelations;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<CNSocialProfile*>*>           *socialProfiles;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<CNInstantMessageAddress*>*>   *instantMessageAddresses;

/*! The Gregorian birthday. */
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *birthday;

/*! The alternate birthday (Lunisolar). */
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *nonGregorianBirthday;

/*! Other Gregorian dates (anniversaries, etc). */
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<NSDateComponents*>*> *dates;


// Key Availability

/*! Returns YES if the value for the specified key was fetched. */
- (BOOL)isKeyAvailable:(NSString *)key;

/*! Returns YES if the values for the keys specified by all the descriptors were fetched. */
- (BOOL)areKeysAvailable:(NSArray <id<CNKeyDescriptor>>*)keyDescriptors;


// Key Localization

/*! Returns a user displayable property name. */
+ (NSString *)localizedStringForKey:(NSString *)key;


// Contact Sort Comparator

/*! The contact comparator for a given sort order. */
+ (NSComparator)comparatorForNameSortOrder:(CNContactSortOrder)sortOrder;

/*! Use to fetch all contact keys required for the contact sort comparator. */
+ (id<CNKeyDescriptor>)descriptorForAllComparatorKeys;


// Unification
/*! Returns YES if the receiver was fetched as a unified contact and includes the contact having contactIdentifier in its unification */
- (BOOL)isUnifiedWithContactWithIdentifier:(NSString*)contactIdentifier;

@end

CONTACTS_EXTERN NSString * const CNContactPropertyNotFetchedExceptionName;

// Properties that are always fetched. Can be used with key value coding and observing.
CONTACTS_EXTERN NSString * const CNContactIdentifierKey                      NS_AVAILABLE(10_11, 9_0);

// Optional properties that can be fetched. Can be used with key value coding and observing.
CONTACTS_EXTERN NSString * const CNContactNamePrefixKey                      NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactGivenNameKey                       NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactMiddleNameKey                      NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactFamilyNameKey                      NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactPreviousFamilyNameKey              NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactNameSuffixKey                      NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactNicknameKey                        NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactOrganizationNameKey                NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactDepartmentNameKey                  NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactJobTitleKey                        NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactPhoneticGivenNameKey               NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactPhoneticMiddleNameKey              NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactPhoneticFamilyNameKey              NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactPhoneticOrganizationNameKey        NS_AVAILABLE(10_12, 10_0);
CONTACTS_EXTERN NSString * const CNContactBirthdayKey                        NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactNonGregorianBirthdayKey            NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactNoteKey                            NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactImageDataKey                       NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactThumbnailImageDataKey              NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactImageDataAvailableKey              NS_AVAILABLE(10_12, 9_0);
CONTACTS_EXTERN NSString * const CNContactTypeKey                            NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactPhoneNumbersKey                    NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactEmailAddressesKey                  NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactPostalAddressesKey                 NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactDatesKey                           NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactUrlAddressesKey                    NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactRelationsKey                       NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactSocialProfilesKey                  NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNContactInstantMessageAddressesKey         NS_AVAILABLE(10_11, 9_0);

NS_ASSUME_NONNULL_END
