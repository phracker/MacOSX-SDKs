//
//  ABAddressBookC.h
//  AddressBook Framework
//
//  Copyright (c) 2002-2003 Apple Computer. All rights reserved.
//

#ifndef __ADDRESSBOOKC__
#define __ADDRESSBOOKC__

#if defined(__cplusplus)
extern "C" {
#endif

#include <CoreFoundation/CoreFoundation.h>
#include <AddressBook/ABTypedefs.h>
#include <AddressBook/ABGlobalsC.h>

typedef void                            *ABRecordRef;
typedef struct __ABPerson               *ABPersonRef;
typedef struct __ABGroup                *ABGroupRef;
typedef struct __ABSearchElementRef     *ABSearchElementRef;
typedef struct __ABAddressBookRef       *ABAddressBookRef;
typedef const struct __ABMultiValue     *ABMultiValueRef;
typedef struct __ABMultiValue           *ABMutableMultiValueRef;

// --------------------------------------------------------------------------------
//	LSOpenCFURLRef support
// --------------------------------------------------------------------------------
// An application can open the AddressBook app and select (and edit) a specific
// person by using the LSOpenCFURLRef API.
//
// To launch (or bring to front) the Address Book app and select a given person
//
// CFStringRef uniqueId = ABRecordCopyUniqueId(aPerson);
// CFStringRef urlString = CFStringCreateWithFormat(NULL, CFSTR(addressbook://%@), uniqueId);
// CFURLRef urlRef = CFURLCreateWithString(NULL, urlString, NULL);
// LSOpenCFURLRef(urlRef, NULL);
// CFRelease(uniqueId);
// CFRelease(urlRef);
// CFRelease(urlString);
//
// To launch (or bring to front) the Address Book app and edit a given person
//
// CFStringRef uniqueId = ABRecordCopyUniqueId(aPerson);
// CFStringRef urlString = CFStringCreateWithFormat(NULL, CFSTR(addressbook://%@?edit), uniqueId);
// CFURLRef urlRef = CFURLCreateWithString(NULL, urlString, NULL);
// LSOpenCFURLRef(urlRef, NULL);
// CFRelease(uniqueId);
// CFRelease(urlRef);
// CFRelease(urlString);

// --------------------------------------------------------------------------------
//      AddressBook
// --------------------------------------------------------------------------------

    // --- There is only one Address Book
extern ABAddressBookRef ABGetSharedAddressBook(void);

    // --- Searching
extern CFArrayRef ABCopyArrayOfMatchingRecords(ABAddressBookRef addressBook, ABSearchElementRef search);

    // --- Saving
extern bool ABSave(ABAddressBookRef addressBook);
extern bool ABHasUnsavedChanges(ABAddressBookRef addressBook);

    // --- Me
extern ABPersonRef ABGetMe(ABAddressBookRef addressBook); // Not retain???
extern void ABSetMe(ABAddressBookRef addressBook, ABPersonRef moi);

    // Returns the record class Name for a particular uniqueId
extern CFStringRef ABCopyRecordTypeFromUniqueId(ABAddressBookRef addressBook, CFStringRef uniqueId) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

    // --- Properties
    // Property names must be unique for a record type
extern int ABAddPropertiesAndTypes(ABAddressBookRef addressBook, CFStringRef recordType, CFDictionaryRef propertiesAnTypes);
extern int ABRemoveProperties(ABAddressBookRef addressBook, CFStringRef recordType, CFArrayRef properties);
extern CFArrayRef ABCopyArrayOfPropertiesForRecordType(ABAddressBookRef addressBook, CFStringRef recordType);
extern ABPropertyType ABTypeOfProperty(ABAddressBookRef addressBook, CFStringRef recordType, CFStringRef property);

    // --- Records (Person, Group)
extern ABRecordRef ABCopyRecordForUniqueId(ABAddressBookRef addressBook, CFStringRef uniqueId);
extern bool ABAddRecord(ABAddressBookRef addressBook, ABRecordRef record);
extern bool ABRemoveRecord(ABAddressBookRef addressBook, ABRecordRef record);

    // --- People
extern CFArrayRef ABCopyArrayOfAllPeople(ABAddressBookRef addressBook);                  // Array of ABPerson

    // --- Groups
extern CFArrayRef ABCopyArrayOfAllGroups(ABAddressBookRef addressBook);                  // Array of ABGroup

// --------------------------------------------------------------------------------
//      ABRecord
// --------------------------------------------------------------------------------

extern ABRecordRef ABRecordCreateCopy(ABRecordRef record) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

extern CFStringRef ABRecordCopyRecordType(ABRecordRef record);

    // --- Property value
extern CFTypeRef ABRecordCopyValue(ABRecordRef record, CFStringRef property);
    // returns a CFDictionary for multi-value properties
extern bool ABRecordSetValue(ABRecordRef record, CFStringRef property, CFTypeRef value);
    // takes a CFDictionary for multi-value properties
extern bool ABRecordRemoveValue(ABRecordRef record, CFStringRef property);
   // is the record read only
extern bool ABRecordIsReadOnly(ABRecordRef record) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

    // ---- Unique ID access convenience
extern CFStringRef ABRecordCopyUniqueId(ABRecordRef record);

// --------------------------------------------------------------------------------
//      ABPerson
// --------------------------------------------------------------------------------

extern ABPersonRef ABPersonCreate(void);

extern ABPersonRef ABPersonCreateWithVCardRepresentation(CFDataRef vCard);
extern CFDataRef ABPersonCopyVCardRepresentation(ABPersonRef person);

extern CFArrayRef ABPersonCopyParentGroups(ABPersonRef person); // Groups this person belongs to

    // --- Search elements
extern ABSearchElementRef ABPersonCreateSearchElement(CFStringRef property, CFStringRef label, CFStringRef key, CFTypeRef value, ABSearchComparison comparison);

// --------------------------------------------------------------------------------
//      ABGroups
// --------------------------------------------------------------------------------

extern ABGroupRef ABGroupCreate(void);

    // --- Dealing with Persons
extern CFArrayRef ABGroupCopyArrayOfAllMembers(ABGroupRef group);
extern bool ABGroupAddMember(ABGroupRef group, ABPersonRef personToAdd);
extern bool ABGroupRemoveMember(ABGroupRef group, ABPersonRef personToRemove);

    // --- Dealing with Groups
extern CFArrayRef ABGroupCopyArrayOfAllSubgroups(ABGroupRef group);
extern bool ABGroupAddGroup(ABGroupRef group, ABGroupRef groupToAdd);
extern bool ABGroupRemoveGroup(ABGroupRef group, ABGroupRef groupToRemove);

    // --- Dealing with Parents
extern CFArrayRef ABGroupCopyParentGroups(ABGroupRef group);

    // --- Distribution list
extern bool ABGroupSetDistributionIdentifier(ABGroupRef group, ABPersonRef person, CFStringRef property, CFStringRef identifier);
extern CFStringRef ABGroupCopyDistributionIdentifier(ABGroupRef group, ABPersonRef person, CFStringRef property);

    // --- Search elements
extern ABSearchElementRef ABGroupCreateSearchElement(CFStringRef property, CFStringRef label, CFStringRef key, CFTypeRef value, ABSearchComparison comparison);

// --------------------------------------------------------------------------------
//      ABSearchElement
// --------------------------------------------------------------------------------

extern ABSearchElementRef ABSearchElementCreateWithConjunction(ABSearchConjunction conjunction, CFArrayRef childrenSearchElement);

extern bool ABSearchElementMatchesRecord(ABSearchElementRef searchElement, ABRecordRef record);

// --------------------------------------------------------------------------------
//      ABMultiValue
// --------------------------------------------------------------------------------

extern ABMultiValueRef ABMultiValueCreate(void);
extern unsigned ABMultiValueCount(ABMultiValueRef multiValue);
extern CFTypeRef ABMultiValueCopyValueAtIndex(ABMultiValueRef multiValue, int index);
extern CFStringRef ABMultiValueCopyLabelAtIndex(ABMultiValueRef multiValue, int index);
extern CFStringRef ABMultiValueCopyPrimaryIdentifier(ABMultiValueRef multiValue);
extern int ABMultiValueIndexForIdentifier(ABMultiValueRef multiValue, CFStringRef identifier);
extern CFStringRef ABMultiValueCopyIdentifierAtIndex(ABMultiValueRef multiValue, int index);
extern ABPropertyType ABMultiValuePropertyType(ABMultiValueRef multiValue);
extern ABMultiValueRef ABMultiValueCreateCopy(ABMultiValueRef multiValue);

// --------------------------------------------------------------------------------
//      ABMutableMultiValue
// --------------------------------------------------------------------------------

extern ABMutableMultiValueRef ABMultiValueCreateMutable(void);
extern bool ABMultiValueAdd(ABMutableMultiValueRef multiValue, CFTypeRef value, CFStringRef label, CFStringRef *outIdentifier);
extern bool ABMultiValueInsert(ABMutableMultiValueRef multiValue, CFTypeRef value, CFStringRef label, int index, CFStringRef *outIdentifier);
extern bool ABMultiValueRemove(ABMutableMultiValueRef multiValue, int index);
extern bool ABMultiValueReplaceValue(ABMutableMultiValueRef multiValue, CFTypeRef value, int index);
extern bool ABMultiValueReplaceLabel(ABMutableMultiValueRef multiValue, CFStringRef label, int index);
extern bool ABMultiValueSetPrimaryIdentifier(ABMutableMultiValueRef multiValue, CFStringRef identifier);
extern ABMutableMultiValueRef ABMultiValueCreateMutableCopy(ABMultiValueRef multiValue);

// --------------------------------------------------------------------------------
//      Localization of properties or labels
// --------------------------------------------------------------------------------

extern CFStringRef ABCopyLocalizedPropertyOrLabel(CFStringRef labelOrProperty);

// --- Address formatting
extern CFStringRef ABCreateFormattedAddressFromDictionary(ABAddressBookRef addressBook, CFDictionaryRef address) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
extern CFStringRef ABCopyDefaultCountryCode(ABAddressBookRef addressBook) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

// --------------------------------------------------------------------------------
//      Person Image Loading
// --------------------------------------------------------------------------------

extern bool ABPersonSetImageData(ABPersonRef person, CFDataRef imageData);
extern CFDataRef ABPersonCopyImageData(ABPersonRef person);

typedef void (*ABImageClientCallback) (CFDataRef imageData, int tag, void* refcon);

extern int ABBeginLoadingImageDataForClient(ABPersonRef person, ABImageClientCallback callback, void* refcon);
extern void ABCancelLoadingImageDataForTag(int tag);

#if defined(__cplusplus)
}
#endif

#endif
