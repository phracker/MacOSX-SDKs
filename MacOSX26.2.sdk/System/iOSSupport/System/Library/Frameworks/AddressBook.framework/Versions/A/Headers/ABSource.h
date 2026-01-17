/*
 *  ABSource.h
 *  AddressBook
 *
 *  Copyright (c) 2010-2015 Apple Inc. All rights reserved.
 *
 */


#ifndef __ABSource__
#define __ABSource__

#include <AddressBook/AddressBookDefines.h>
#include <AddressBook/ABAddressBook.h>
#include <AddressBook/ABRecord.h>
#include <AddressBook/ABPerson.h>

#include <Availability.h>

#if __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED

#define kABSourceTypeSearchableMask  0x01000000 // deprecated

enum {
    kABSourceTypeLocal       = 0x0,                                                     // deprecated, use CNContainerTypeLocal
    kABSourceTypeExchange    = 0x1,                                                     // deprecated, used CNContainerTypeExchange
    kABSourceTypeExchangeGAL = kABSourceTypeExchange | kABSourceTypeSearchableMask,     // deprecated

    kABSourceTypeMobileMe    = 0x2,                                                     // deprecated

    kABSourceTypeLDAP        = 0x3 | kABSourceTypeSearchableMask,                       // deprecated
    
    kABSourceTypeCardDAV     = 0x4,                                                     // deprecated, use CNContainerTypeCardDAV
    kABSourceTypeCardDAVSearch = kABSourceTypeCardDAV | kABSourceTypeSearchableMask,    // deprecated
};
typedef int ABSourceType AB_DEPRECATED("");

#endif

AB_EXTERN const ABPropertyID kABSourceNameProperty AB_DEPRECATED("use CNContainer.name"); // string
AB_EXTERN const ABPropertyID kABSourceTypeProperty AB_DEPRECATED("use CNContainer.type"); // CFNumberRef of ABSourceType (int)

AB_EXTERN ABRecordRef ABAddressBookCopyDefaultSource(ABAddressBookRef addressBook) AB_DEPRECATED("use [CNContactStore containersMatchingPredicate:[CNContainer predicateForContainersWithIdentifiers: @[CNContactStore.defaultContainerIdentifier]] error:]");

AB_EXTERN ABRecordRef ABAddressBookGetSourceWithRecordID(ABAddressBookRef addressBook, ABRecordID sourceID) AB_DEPRECATED("use [CNContactStore containersMatchingPredicate:[CNContainer predicateForContainersWithIdentifiers:] error:]");

AB_EXTERN CFArrayRef ABAddressBookCopyArrayOfAllSources(ABAddressBookRef addressBook) AB_DEPRECATED("use [CNContactStore containersMatchingPredicate:nil error:]");

#endif
