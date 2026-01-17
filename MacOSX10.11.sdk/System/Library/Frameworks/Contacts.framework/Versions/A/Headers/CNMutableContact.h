//
//  CNMutableContact.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Contacts/CNContact.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract A mutable value object representing a contact.
 *
 * @discussion CNMutableContact is not thread safe. If this is a mutable copy of CNContact then it will throw CNContactPropertyNotFetchedExceptionName when accessing a property that was not fetched for the CNContact.
 *
 * @note To remove properties when saving a mutable contact, set string properties and array properties to empty values. Set other properties to nil.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNMutableContact : CNContact

@property (NS_NONATOMIC_IOSONLY) CNContactType contactType;

@property (copy, NS_NONATOMIC_IOSONLY) NSString *namePrefix;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *givenName;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *middleName;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *familyName;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *previousFamilyName;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *nameSuffix;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *nickname;

@property (copy, NS_NONATOMIC_IOSONLY) NSString *phoneticGivenName;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *phoneticMiddleName;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *phoneticFamilyName;

@property (copy, NS_NONATOMIC_IOSONLY) NSString *organizationName;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *departmentName;
@property (copy, NS_NONATOMIC_IOSONLY) NSString *jobTitle;

@property (copy, NS_NONATOMIC_IOSONLY) NSString *note;

@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSData *imageData;

@property (copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<CNPhoneNumber*>*>               *phoneNumbers;
@property (copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<NSString*>*>                    *emailAddresses;
@property (copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<CNPostalAddress*>*>             *postalAddresses;
@property (copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<NSString*>*>                    *urlAddresses;
@property (copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<CNContactRelation*>*>           *contactRelations;
@property (copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<CNSocialProfile*>*>             *socialProfiles;
@property (copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<CNInstantMessageAddress*>*>     *instantMessageAddresses;

/*! @abstract The Gregorian birthday.
 *
 *  @description Only uses day, month and year components. Needs to have at least a day and a month.
 */
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *birthday;

/*! @abstract The alternate birthday (Lunisolar).
 *
 *  @description Only uses day, month, year and calendar components. Needs to have at least a day and a month. Calendar must be Chinese, Hebrew or Islamic.
 */
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *nonGregorianBirthday;

/*! @abstract Other Gregorian dates (anniversaries, etc).
 *
 *  @description Only uses day, month and year components. Needs to have at least a day and a month.
 */
@property (copy, NS_NONATOMIC_IOSONLY) NSArray<CNLabeledValue<NSDateComponents*>*> *dates;

@end

NS_ASSUME_NONNULL_END
