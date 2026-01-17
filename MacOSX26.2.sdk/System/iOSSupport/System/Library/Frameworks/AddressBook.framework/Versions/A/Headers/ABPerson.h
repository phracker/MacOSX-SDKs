/*
 *  ABPerson.h
 *  AddressBook
 *
 *  Copyright (c) 2010-2015 Apple Inc. All rights reserved.
 *
 *  An ABPerson corresponds to a contact such as a person or organization.
 *
 */

#ifndef __ABPerson__
#define __ABPerson__

#include <CoreFoundation/CoreFoundation.h>

#include <AddressBook/AddressBookDefines.h>
#include <AddressBook/ABAddressBook.h>
#include <AddressBook/ABRecord.h>
#include <AddressBook/ABSource.h>

#include <Availability.h>

// ABPersonCreate creates a new person in the default source
AB_EXTERN ABRecordRef ABPersonCreate(void) AB_DEPRECATED("use [[CNMutableContact alloc] init]");
AB_EXTERN ABRecordRef ABPersonCreateInSource(ABRecordRef source) AB_DEPRECATED("use [[CNMutableContact alloc] init] and [CNSaveRequest addContact:toContainerWithIdentifier:]");

AB_EXTERN ABRecordRef ABPersonCopySource(ABRecordRef person) AB_DEPRECATED("use [CNContactStore containersMatchingPredicate:[CNContainer predicateForContainerOfContactWithIdentifier:] error:]");

// Returns an array of all the linked people, including the person passed in. If the person is not linked, returns an array with the person passed in.
AB_EXTERN CFArrayRef ABPersonCopyArrayOfAllLinkedPeople(ABRecordRef person) AB_DEPRECATED("use CNContactFetchRequest with predicate = [CNContact predicateForContactsLinkedToContact:] and unifyResults = NO");

AB_EXTERN ABPropertyType ABPersonGetTypeOfProperty(ABPropertyID property) AB_DEPRECATED("");
AB_EXTERN CFStringRef ABPersonCopyLocalizedPropertyName(ABPropertyID property) AB_DEPRECATED("use [CNContact localizedStringForKey:]");

typedef uint32_t ABPersonSortOrdering AB_DEPRECATED("use CNContactSortOrder");
enum {
    kABPersonSortByFirstName = 0,   // deprecated, use CNContactSortOrderGivenName
    kABPersonSortByLastName  = 1    // deprecated, use CNContactSortOrderFamilyName"
};

AB_EXTERN ABPersonSortOrdering ABPersonGetSortOrdering(void) AB_DEPRECATED("use [[CNContactsUserDefaults sharedDefaults] sortOrder]");

typedef uint32_t ABPersonCompositeNameFormat AB_DEPRECATED("");
enum  {
    kABPersonCompositeNameFormatFirstNameFirst = 0, // deprecated
    kABPersonCompositeNameFormatLastNameFirst  = 1  // deprecated
};

// Composite Names
AB_EXTERN ABPersonCompositeNameFormat ABPersonGetCompositeNameFormat(void) AB_DEPRECATED("");
AB_EXTERN ABPersonCompositeNameFormat ABPersonGetCompositeNameFormatForRecord(ABRecordRef record) AB_DEPRECATED("");
AB_EXTERN CFStringRef ABPersonCopyCompositeNameDelimiterForRecord(ABRecordRef record) AB_DEPRECATED("");

// Images
typedef enum {
    kABPersonImageFormatThumbnail = 0,      // deprecated
    kABPersonImageFormatOriginalSize = 2    // deprecated
} ABPersonImageFormat AB_DEPRECATED("");

AB_EXTERN bool ABPersonSetImageData(ABRecordRef person, CFDataRef imageData, CFErrorRef* error) AB_DEPRECATED("use CNMutableContact.imageData");
AB_EXTERN CFDataRef ABPersonCopyImageData(ABRecordRef person) AB_DEPRECATED("use CNContact.imageData");
AB_EXTERN CFDataRef ABPersonCopyImageDataWithFormat(ABRecordRef person, ABPersonImageFormat format) AB_DEPRECATED("use CNContact.imageData or CNContact.thumbnailImageData");

AB_EXTERN bool ABPersonHasImageData(ABRecordRef person) AB_DEPRECATED("");
AB_EXTERN bool ABPersonRemoveImageData(ABRecordRef person, CFErrorRef* error) AB_DEPRECATED("use CNMutableContact.imageData = nil");

// Sorting
AB_EXTERN CFComparisonResult ABPersonComparePeopleByName(ABRecordRef person1, ABRecordRef person2, ABPersonSortOrdering ordering) AB_DEPRECATED("use [CNContact comparatorForNameSortOrder:]");

// Finding people
AB_EXTERN CFIndex ABAddressBookGetPersonCount(ABAddressBookRef addressBook) AB_DEPRECATED("use count of fetch results for CNContactFetchRequest with predicate = nil");
AB_EXTERN ABRecordRef ABAddressBookGetPersonWithRecordID(ABAddressBookRef addressBook, ABRecordID recordID) AB_DEPRECATED("use [CNContactStore unifiedContactWithIdentifier:keysToFetch:error:]");

AB_EXTERN CFArrayRef ABAddressBookCopyArrayOfAllPeople(ABAddressBookRef addressBook) AB_DEPRECATED("use CNContactFetchRequest with predicate = nil");
AB_EXTERN CFArrayRef ABAddressBookCopyArrayOfAllPeopleInSource(ABAddressBookRef addressBook, ABRecordRef source) AB_DEPRECATED("use CNContactFetchRequest with predicate = [CNContact predicateForContactsInContainerWithIdentifier:] and unifyResults = NO");
AB_EXTERN CFArrayRef ABAddressBookCopyArrayOfAllPeopleInSourceWithSortOrdering(ABAddressBookRef addressBook, ABRecordRef source, ABPersonSortOrdering sortOrdering) AB_DEPRECATED("use CNContactFetchRequest with predicate = [CNContact predicateForContactsInContainerWithIdentifier:] and unifyResults = NO and sortOrder");

AB_EXTERN CFArrayRef ABAddressBookCopyPeopleWithName(ABAddressBookRef addressBook, CFStringRef name) AB_DEPRECATED("use [CNContactStore unifiedContactsMatchingPredicate:[CNContact predicateForContactsMatchingName:] keysToFetch: error:]");

// VCard
    // Creates an array of people from a vcard representation. Source is optional. The people
    // will be created in the source given as the first argument, or the default source if NULL.
AB_EXTERN CFArrayRef ABPersonCreatePeopleInSourceWithVCardRepresentation(ABRecordRef source, CFDataRef vCardData) AB_DEPRECATED("use [CNContactVCardSerialization contactsWithData:error:]");
    // Creates a vCard representation of the people passed in.
AB_EXTERN CFDataRef ABPersonCreateVCardRepresentationWithPeople(CFArrayRef people) AB_DEPRECATED("use [CNContactVCardSerialization dataWithContacts:error:]");

// Generic labels
AB_EXTERN const CFStringRef kABWorkLabel AB_DEPRECATED("use CNLabelWork");
AB_EXTERN const CFStringRef kABHomeLabel AB_DEPRECATED("use CNLabelHome");
AB_EXTERN const CFStringRef kABOtherLabel AB_DEPRECATED("use CNLabelOther");

// Property keys
AB_EXTERN const ABPropertyID kABPersonFirstNameProperty AB_DEPRECATED("use CNContact.givenName");                               // First name - kABStringPropertyType
AB_EXTERN const ABPropertyID kABPersonLastNameProperty AB_DEPRECATED("use CNContact.familyName");                               // Last name - kABStringPropertyType
AB_EXTERN const ABPropertyID kABPersonMiddleNameProperty AB_DEPRECATED("use CNContact.middleName");                             // Middle name - kABStringPropertyType
AB_EXTERN const ABPropertyID kABPersonPrefixProperty AB_DEPRECATED("use CNContact.namePrefix");                                 // Prefix ("Sir" "Duke" "General") - kABStringPropertyType
AB_EXTERN const ABPropertyID kABPersonSuffixProperty AB_DEPRECATED("use CNContact.nameSuffix");                                 // Suffix ("Jr." "Sr." "III") - kABStringPropertyType
AB_EXTERN const ABPropertyID kABPersonNicknameProperty AB_DEPRECATED("use CNContact.nickname");                                 // Nickname - kABStringPropertyType
AB_EXTERN const ABPropertyID kABPersonFirstNamePhoneticProperty AB_DEPRECATED("use CNContact.phoneticGivenName");               // First name Phonetic - kABStringPropertyType
AB_EXTERN const ABPropertyID kABPersonLastNamePhoneticProperty AB_DEPRECATED("use CNContact.phoneticFamilyName");               // Last name Phonetic - kABStringPropertyType
AB_EXTERN const ABPropertyID kABPersonMiddleNamePhoneticProperty AB_DEPRECATED("use CNContact.phoneticMiddleName");             // Middle name Phonetic - kABStringPropertyType
AB_EXTERN const ABPropertyID kABPersonOrganizationProperty AB_DEPRECATED("use CNContact.organizationName");                     // Company name - kABStringPropertyType
AB_EXTERN const ABPropertyID kABPersonDepartmentProperty AB_DEPRECATED("use CNContact.departmentName");                         // Department name - kABStringPropertyType
AB_EXTERN const ABPropertyID kABPersonJobTitleProperty AB_DEPRECATED("use CNContact.jobTitle");                                 // Job Title - kABStringPropertyType
AB_EXTERN const ABPropertyID kABPersonEmailProperty AB_DEPRECATED("use CNContact.emailAddresses");                              // Email(s) - kABMultiStringPropertyType
AB_EXTERN const ABPropertyID kABPersonBirthdayProperty AB_DEPRECATED("use CNContact.birthday");                                 // Birthday associated with this person - kABDateTimePropertyType
AB_EXTERN const ABPropertyID kABPersonNoteProperty AB_DEPRECATED("use CNContact.note");                                         // Note - kABStringPropertyType
AB_EXTERN const ABPropertyID kABPersonCreationDateProperty AB_DEPRECATED("");                                                   // Creation Date (when first saved)
AB_EXTERN const ABPropertyID kABPersonModificationDateProperty AB_DEPRECATED("");                                               // Last saved date

// Addresses
AB_EXTERN const ABPropertyID kABPersonAddressProperty AB_DEPRECATED("use CNContact.postalAddresses");                           // Street address - kABMultiDictionaryPropertyType
AB_EXTERN const CFStringRef kABPersonAddressStreetKey AB_DEPRECATED("use CNPostalAddress.street");
AB_EXTERN const CFStringRef kABPersonAddressCityKey AB_DEPRECATED("use CNPostalAddress.city");
AB_EXTERN const CFStringRef kABPersonAddressStateKey AB_DEPRECATED("use CNPostalAddress.state");
AB_EXTERN const CFStringRef kABPersonAddressZIPKey AB_DEPRECATED("use CNPostalAddress.postalCode");
AB_EXTERN const CFStringRef kABPersonAddressCountryKey AB_DEPRECATED("use CNPostalAddress.country");
AB_EXTERN const CFStringRef kABPersonAddressCountryCodeKey AB_DEPRECATED("use CNPostalAddress.ISOCountryCode");

/*
 * kABPersonAddressCountryCodeKey code must be in the form of 2 character iso 3166 country codes
 *
 * eg:
 *    fr = France
 *    us = United States
 * etc.
 *
 */

// Dates
AB_EXTERN const ABPropertyID kABPersonDateProperty AB_DEPRECATED("use CNContact.dates");                                        // Dates associated with this person - kABMultiDatePropertyType
AB_EXTERN const CFStringRef kABPersonAnniversaryLabel AB_DEPRECATED("use CNLabelDateAnniversary");

// Kind
AB_EXTERN const ABPropertyID kABPersonKindProperty AB_DEPRECATED("use CNContact.contactType");                                  // Person/Organization - kABIntegerPropertyType
AB_EXTERN const CFNumberRef kABPersonKindPerson AB_DEPRECATED("use CNContactTypePerson");
AB_EXTERN const CFNumberRef kABPersonKindOrganization AB_DEPRECATED("use CNContactTypeOrganization");

// Phone numbers
AB_EXTERN const ABPropertyID kABPersonPhoneProperty AB_DEPRECATED("use CNContact.phoneNumbers");                                // Generic phone number - kABMultiStringPropertyType
AB_EXTERN const CFStringRef kABPersonPhoneMobileLabel AB_DEPRECATED("use CNLabelPhoneNumberMobile");
AB_EXTERN const CFStringRef kABPersonPhoneIPhoneLabel AB_DEPRECATED("use CNLabelPhoneNumberiPhone");
AB_EXTERN const CFStringRef kABPersonPhoneMainLabel AB_DEPRECATED("use CNLabelPhoneNumberMain");
AB_EXTERN const CFStringRef kABPersonPhoneHomeFAXLabel AB_DEPRECATED("use CNLabelPhoneNumberHomeFax");
AB_EXTERN const CFStringRef kABPersonPhoneWorkFAXLabel AB_DEPRECATED("use CNLabelPhoneNumberWorkFax");
AB_EXTERN const CFStringRef kABPersonPhoneOtherFAXLabel AB_DEPRECATED("use CNLabelPhoneNumberOtherFax");
AB_EXTERN const CFStringRef kABPersonPhonePagerLabel AB_DEPRECATED("use CNLabelPhoneNumberPager");

// IM
AB_EXTERN const ABPropertyID kABPersonInstantMessageProperty AB_DEPRECATED("use CNContact.instantMessageAddresses");            // Instant Messaging - kABMultiDictionaryPropertyType
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceKey AB_DEPRECATED("use CNInstantMessageAddress.service");             // Service ("Yahoo", "Jabber", etc.)
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceYahoo AB_DEPRECATED("use CNInstantMessageServiceYahoo");
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceJabber AB_DEPRECATED("use CNInstantMessageServiceJabber");
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceMSN AB_DEPRECATED("use CNInstantMessageServiceMSN");
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceICQ AB_DEPRECATED("use CNInstantMessageServiceICQ");
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceAIM AB_DEPRECATED("use CNInstantMessageServiceAIM");
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceQQ AB_DEPRECATED("use CNInstantMessageServiceQQ");
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceGoogleTalk AB_DEPRECATED("use CNInstantMessageServiceGoogleTalk");
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceSkype AB_DEPRECATED("use CNInstantMessageServiceSkype");
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceFacebook AB_DEPRECATED("use CNInstantMessageServiceFacebook");
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceGaduGadu AB_DEPRECATED("use CNInstantMessageServiceGaduGadu");

AB_EXTERN const CFStringRef kABPersonInstantMessageUsernameKey AB_DEPRECATED("use CNInstantMessageAddress.username");           // Username

// URLs
AB_EXTERN const ABPropertyID kABPersonURLProperty AB_DEPRECATED("use CNContact.urlAddresses");                                  // URL - kABMultiStringPropertyType
AB_EXTERN const CFStringRef kABPersonHomePageLabel AB_DEPRECATED("use CNLabelURLAddressHomePage");                              // Home Page

// Related names
AB_EXTERN const ABPropertyID kABPersonRelatedNamesProperty AB_DEPRECATED("use CNContact.contactRelations");                     // Names - kABMultiStringPropertyType
AB_EXTERN const CFStringRef kABPersonFatherLabel AB_DEPRECATED("use CNLabelContactRelationFather");                             // Father
AB_EXTERN const CFStringRef kABPersonMotherLabel AB_DEPRECATED("use CNLabelContactRelationMother");                             // Mother
AB_EXTERN const CFStringRef kABPersonParentLabel AB_DEPRECATED("use CNLabelContactRelationParent");                             // Parent
AB_EXTERN const CFStringRef kABPersonBrotherLabel AB_DEPRECATED("use CNLabelContactRelationBrother");                           // Brother
AB_EXTERN const CFStringRef kABPersonSisterLabel AB_DEPRECATED("use CNLabelContactRelationSister");                             // Sister
AB_EXTERN const CFStringRef kABPersonChildLabel AB_DEPRECATED("use CNLabelContactRelationChild");                               // Child
AB_EXTERN const CFStringRef kABPersonFriendLabel AB_DEPRECATED("use CNLabelContactRelationFriend");                             // Friend
AB_EXTERN const CFStringRef kABPersonSpouseLabel AB_DEPRECATED("use CNLabelContactRelationSpouse");                             // Spouse
AB_EXTERN const CFStringRef kABPersonPartnerLabel AB_DEPRECATED("use CNLabelContactRelationPartner");                           // Partner
AB_EXTERN const CFStringRef kABPersonAssistantLabel AB_DEPRECATED("use CNLabelContactRelationAssistant");                       // Assistant
AB_EXTERN const CFStringRef kABPersonManagerLabel AB_DEPRECATED("use CNLabelContactRelationManager");                           // Manager
    
// Social Profile
AB_EXTERN const ABPropertyID kABPersonSocialProfileProperty AB_DEPRECATED("use CNContact.socialProfiles");                      // kABMultiDictionaryPropertyType
AB_EXTERN const CFStringRef kABPersonSocialProfileURLKey AB_DEPRECATED("use CNSocialProfile.urlString");                        // string representation of a url for the social profile
    // the following properties are optional
    AB_EXTERN const CFStringRef kABPersonSocialProfileServiceKey AB_DEPRECATED("use CNSocialProfile.service");                  // string representing the name of the service (Twitter, Facebook, LinkedIn, etc.)
    AB_EXTERN const CFStringRef kABPersonSocialProfileUsernameKey AB_DEPRECATED("use CNSocialProfile.username");                // string representing the user visible name
    AB_EXTERN const CFStringRef kABPersonSocialProfileUserIdentifierKey AB_DEPRECATED("use CNSocialProfile.userIdentifier");    // string representing the service specific identifier (optional)

AB_EXTERN const CFStringRef kABPersonSocialProfileServiceTwitter AB_DEPRECATED("use CNSocialProfileServiceTwitter");
AB_EXTERN const CFStringRef kABPersonSocialProfileServiceSinaWeibo AB_DEPRECATED("use CNSocialProfileServiceSinaWeibo");
AB_EXTERN const CFStringRef kABPersonSocialProfileServiceGameCenter AB_DEPRECATED("use CNSocialProfileServiceGameCenter");
AB_EXTERN const CFStringRef kABPersonSocialProfileServiceFacebook AB_DEPRECATED("use CNSocialProfileServiceFacebook");
AB_EXTERN const CFStringRef kABPersonSocialProfileServiceMyspace AB_DEPRECATED("use CNSocialProfileServiceMySpace");
AB_EXTERN const CFStringRef kABPersonSocialProfileServiceLinkedIn AB_DEPRECATED("use CNSocialProfileServiceLinkedIn");
AB_EXTERN const CFStringRef kABPersonSocialProfileServiceFlickr AB_DEPRECATED("use CNSocialProfileServiceFlickr");

// Alternate birthday
AB_EXTERN const ABPropertyID kABPersonAlternateBirthdayProperty AB_DEPRECATED("use CNContact.nonGregorianBirthday");            // kABDictionaryPropertyType
AB_EXTERN const CFStringRef kABPersonAlternateBirthdayCalendarIdentifierKey AB_DEPRECATED("use NSDateComponents.calendar");     // string representing the calendar identifier for CFCalendarRef
AB_EXTERN const CFStringRef kABPersonAlternateBirthdayEraKey AB_DEPRECATED("use NSDateComponents.era");                         // CFNumberRef - kCFNumberNSIntegerType
AB_EXTERN const CFStringRef kABPersonAlternateBirthdayYearKey AB_DEPRECATED("use NSDateComponents.year");                       // CFNumberRef - kCFNumberNSIntegerType
AB_EXTERN const CFStringRef kABPersonAlternateBirthdayMonthKey AB_DEPRECATED("use NSDateComponents.month");                     // CFNumberRef - kCFNumberNSIntegerType
AB_EXTERN const CFStringRef kABPersonAlternateBirthdayIsLeapMonthKey AB_DEPRECATED("use NSDateComponents.isLeapMonth");         // CFNumberRef - kCFNumberCharType (aka NSNumber Bool type)
AB_EXTERN const CFStringRef kABPersonAlternateBirthdayDayKey AB_DEPRECATED("use NSDateComponents.day");                         // CFNumberRef - kCFNumberNSIntegerType

#endif
