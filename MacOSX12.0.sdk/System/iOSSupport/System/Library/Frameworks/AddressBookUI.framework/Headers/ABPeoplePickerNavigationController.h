//
//  ABPeoplePickerNavigationController.h
//  AddressBookUI
//
//  Copyright (c) 2010-2014 Apple Inc. All rights reserved.
//

#import <UIKit/UINavigationController.h>
#import <AddressBook/ABAddressBook.h>
#import <AddressBook/ABMultiValue.h>
#import <AddressBook/ABRecord.h>

@protocol ABPeoplePickerNavigationControllerDelegate;

NS_ASSUME_NONNULL_BEGIN

AB_DEPRECATED("Use CNContactPickerViewController from ContactsUI.framework instead")
@interface ABPeoplePickerNavigationController : UINavigationController

// The ABPeoplePickerNavigationController allows the user to select a person or property by presenting the entire Address Book.
//
// In iOS 7.0 and later ABPeoplePickerNavigationController does not support subclassing. In the future, a nil instance will be returned.
//
// In iOS 8.0 and later the app does not need access to the user’s contacts and the user will not be prompted for access.
// If the app does not have access to the user's contacts a temporary copy of the selected person is returned to the app.
// If the app has access to the user's contacts the selected person is returned to the app from the ABPeoplePickerNavigationController.addressBook instance.

// Optional to get the selected contact, selected property or cancellation of the people picker.
//
@property(nonatomic,assign,nullable) id<ABPeoplePickerNavigationControllerDelegate> peoplePickerDelegate;

// An array of ABPropertyIDs listing the properties that should be visible when viewing a person.
// If you are interested in one particular type of data (for example a phone number), displayedProperties
// should be an array with a single NSNumber instance (representing kABPersonPhoneProperty).
// Note that name information will always be shown if available.
//
@property(nonatomic,copy,nullable) NSArray<NSNumber*> *displayedProperties;

// The Address Book to browse. Contacts will be returned from this ABAddressBook instance.
// If not set, a new ABAddressBook will be created the first time the property is accessed.
// Note this property is only used if the app has access to the user's contacts, otherwise it remains NULL.
//
@property(nonatomic,readwrite,nullable) ABAddressBookRef addressBook;

// Optionally determines if a person can be selected or not.
// If not set, all persons will be selectable.
//
@property(nonatomic,copy,nullable) NSPredicate *predicateForEnablingPerson NS_AVAILABLE_IOS(8_0);

// Optionally determines if a selected person should be returned to the app (predicate evaluates to TRUE),
// or if the selected person should be displayed (predicate evaluates to FALSE).
// If not set and -peoplePickerNavigationController:didSelectPerson: is implemented the selected person is returned to the app,
// or if not set and -peoplePickerNavigationController:didSelectPerson:identifier: is implemented the selected person is displayed.
//
@property(nonatomic,copy,nullable) NSPredicate *predicateForSelectionOfPerson NS_AVAILABLE_IOS(8_0);

// Optionally determines if a selected property should be returned to the app (predicate evaluates to TRUE),
// or if the default action for the property should be performed (predicate evaluates to FALSE).
// If not set and -peoplePickerNavigationController:didSelectPerson:identifier: is implemented the selected property is returned to the app.
//
@property(nonatomic,copy,nullable) NSPredicate *predicateForSelectionOfProperty NS_AVAILABLE_IOS(8_0);

@end


// Constants to use in predicates:
// A LabeledValue has a 'label' property and a 'value' property.
// A PhoneNumber has a 'stringValue' property, a 'countryCode' property, a 'formattedStringValue' property and a 'normalizedStringValue' property
// A InstantMessageAddress has a 'username' property and a 'service' property
// A SocialProfile has a 'username' property and a 'service' property
// A PostalAddress has a 'street' property, a 'subLocality' property, a 'city' property, a 'subAdministrativeArea' property, a 'state' property, a 'postalCode' property, a 'country' property and a 'ISOCountryCode' property
//
extern NSString * const ABPersonNamePrefixProperty NS_AVAILABLE_IOS(8_0);               // "namePrefix"                 NSString
extern NSString * const ABPersonGivenNameProperty NS_AVAILABLE_IOS(8_0);                // "givenName"                  NSString
extern NSString * const ABPersonMiddleNameProperty NS_AVAILABLE_IOS(8_0);               // "middleName"                 NSString
extern NSString * const ABPersonFamilyNameProperty NS_AVAILABLE_IOS(8_0);               // "familyName"                 NSString
extern NSString * const ABPersonNameSuffixProperty NS_AVAILABLE_IOS(8_0);               // "nameSuffix"                 NSString
extern NSString * const ABPersonPreviousFamilyNameProperty NS_AVAILABLE_IOS(8_0);       // "previousFamilyName"         NSString
extern NSString * const ABPersonNicknameProperty NS_AVAILABLE_IOS(8_0);                 // "nickname"                   NSString
extern NSString * const ABPersonPhoneticGivenNameProperty NS_AVAILABLE_IOS(8_0);        // "phoneticGivenName"          NSString
extern NSString * const ABPersonPhoneticMiddleNameProperty NS_AVAILABLE_IOS(8_0);       // "phoneticMiddleName"         NSString
extern NSString * const ABPersonPhoneticFamilyNameProperty NS_AVAILABLE_IOS(8_0);       // "phoneticFamilyName"         NSString
extern NSString * const ABPersonOrganizationNameProperty NS_AVAILABLE_IOS(8_0);         // "organizationName"           NSString
extern NSString * const ABPersonDepartmentNameProperty NS_AVAILABLE_IOS(8_0);           // "departmentName"             NSString
extern NSString * const ABPersonJobTitleProperty NS_AVAILABLE_IOS(8_0);                 // "jobTitle"                   NSString
extern NSString * const ABPersonBirthdayProperty NS_AVAILABLE_IOS(8_0);                 // "birthday"                   NSDateComponents
extern NSString * const ABPersonNoteProperty NS_AVAILABLE_IOS(8_0);                     // "note"                       NSString
extern NSString * const ABPersonPhoneNumbersProperty NS_AVAILABLE_IOS(8_0);             // "phoneNumbers"               array of LabeledValue with PhoneNumber values
extern NSString * const ABPersonEmailAddressesProperty NS_AVAILABLE_IOS(8_0);           // "emailAddresses"             array of LabeledValue with NSString values
extern NSString * const ABPersonUrlAddressesProperty NS_AVAILABLE_IOS(8_0);             // "urlAddresses"               array of LabeledValue with NSString values
extern NSString * const ABPersonDatesProperty NS_AVAILABLE_IOS(8_0);                    // "dates"                      array of LabeledValue with NSDateComponents values
extern NSString * const ABPersonInstantMessageAddressesProperty NS_AVAILABLE_IOS(8_0);  // "instantMessageAddresses"    array of LabeledValue with InstantMessageAddress values
extern NSString * const ABPersonRelatedNamesProperty NS_AVAILABLE_IOS(8_0);             // "relatedNames"               array of LabeledValue with NSString values
extern NSString * const ABPersonSocialProfilesProperty NS_AVAILABLE_IOS(8_0);           // "socialProfiles"             array of LabeledValue with SocialProfile values
extern NSString * const ABPersonPostalAddressesProperty NS_AVAILABLE_IOS(8_0);          // "postalAddresses"            array of LabeledValue with PostalAddress values


@protocol ABPeoplePickerNavigationControllerDelegate <NSObject>

@optional

// Called after a person has been selected by the user.
- (void)peoplePickerNavigationController:(ABPeoplePickerNavigationController*)peoplePicker didSelectPerson:(ABRecordRef)person NS_AVAILABLE_IOS(8_0);

// Called after a property has been selected by the user.
- (void)peoplePickerNavigationController:(ABPeoplePickerNavigationController*)peoplePicker didSelectPerson:(ABRecordRef)person property:(ABPropertyID)property identifier:(ABMultiValueIdentifier)identifier NS_AVAILABLE_IOS(8_0);

// Called after the user has pressed cancel.
- (void)peoplePickerNavigationControllerDidCancel:(ABPeoplePickerNavigationController *)peoplePicker;


// Deprecated, use predicateForSelectionOfPerson and/or -peoplePickerNavigationController:didSelectPerson: instead.
- (BOOL)peoplePickerNavigationController:(ABPeoplePickerNavigationController *)peoplePicker shouldContinueAfterSelectingPerson:(ABRecordRef)person NS_DEPRECATED_IOS(2_0, 8_0);

// Deprecated, use predicateForSelectionOfProperty and/or -peoplePickerNavigationController:didSelectPerson:property:identifier: instead.
- (BOOL)peoplePickerNavigationController:(ABPeoplePickerNavigationController *)peoplePicker shouldContinueAfterSelectingPerson:(ABRecordRef)person property:(ABPropertyID)property identifier:(ABMultiValueIdentifier)identifier NS_DEPRECATED_IOS(2_0, 8_0);

@end

NS_ASSUME_NONNULL_END
