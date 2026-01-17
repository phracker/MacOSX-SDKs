/*
 *  ABGlobalsC.h
 *  AddressBook Framework
 *
 *  Copyright (c) 2002-2003 Apple Computer. All rights reserved.
 *
 */

#ifndef __ABGLOBALSC__
#define __ABGLOBALSC__

#ifndef __OBJC__

#include <CoreFoundation/CoreFoundation.h>

// NOTE: This header is for C programmers. For Objective-C use ABGlobals.h

// ================================================================
//      Global Table properties
// ================================================================

// ----- Properties common to all Records

extern CFStringRef const kABUIDProperty;                   // The UID property - kABStringProperty
extern CFStringRef const kABCreationDateProperty;          // Creation Date (when first saved) - kABDateProperty
extern CFStringRef const kABModificationDateProperty;      // Last saved date - kABDateProperty

// ----- Person specific properties

extern CFStringRef const kABFirstNameProperty;             // First name - kABStringProperty
extern CFStringRef const kABLastNameProperty;              // Last name - kABStringProperty

extern CFStringRef const kABFirstNamePhoneticProperty;     // First name Phonetic - kABStringProperty
extern CFStringRef const kABLastNamePhoneticProperty;      // Last name Phonetic - kABStringProperty

extern CFStringRef const kABNicknameProperty;                // kABStringProperty
extern CFStringRef const kABMaidenNameProperty;              // kABStringProperty

extern CFStringRef const kABBirthdayProperty;              // Birth date - kABDateProperty

extern CFStringRef const kABOrganizationProperty;          // Company name - kABStringProperty

extern CFStringRef const kABJobTitleProperty;              // Job Title - kABStringProperty

// Deprecated in Mac OS 10.4. You should use kABURLsProperty.
extern CFStringRef const kABHomePageProperty;              // Home Web page - kABStringProperty

extern CFStringRef * const kABURLsProperty AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // URLs - kABMultiStringProperty
    extern CFStringRef * const kABHomePageLabel AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; // Homepage URL

extern CFStringRef const kABEmailProperty;                 // Email(s) - kABMultiStringProperty
        extern CFStringRef const kABEmailWorkLabel;        // Work email
        extern CFStringRef const kABEmailHomeLabel;        // Home email

extern CFStringRef const kABAddressProperty;                // Street Addresses - kABMultiDictionaryProperty
    extern CFStringRef const kABAddressStreetKey;           // Street
    extern CFStringRef const kABAddressCityKey;             // City
    extern CFStringRef const kABAddressStateKey;            // State
    extern CFStringRef const kABAddressZIPKey;              // Zip
    extern CFStringRef const kABAddressCountryKey;          // Country
    extern CFStringRef const kABAddressCountryCodeKey;      // Country Code
        extern CFStringRef const kABAddressHomeLabel;       // Home Address
        extern CFStringRef const kABAddressWorkLabel;       // Work Address

/*
 * kABAddressCountryCodeKey code must be one of the following:
 * iso country codes
 *
 *    ar = Argentina
 *    at = Austria
 *    au = Australia
 *    ba = Bosnia and Herzegovina
 *    be = Belgium
 *    bg = Bulgaria
 *    bh = Bahrain
 *    br = Brazil
 *    ca = Canada
 *    ch = Switzerland
 *    cn = China
 *    cs = Czech
 *    de = Germany
 *    dk = Denmark
 *    eg = Egypt
 *    es = Spain
 *    fi = Finland
 *    fr = France
 *    gr = Greece
 *    gl = Greenland
 *    hk = Hong Kong
 *    hr = Croatia
 *    hu = Hungary
 *    ie = Ireland
 *    il = Israel
 *    id = Indonesia
 *    in = India
 *    is = Iceland
 *    it = Italy
 *    ja = Japan
 *    jo = Jordan
 *    kr = South Korea
 *    kw = Kuwait
 *    lb = Lebanon
 *    lu = Luxembourg
 *    mk = Macedonia
 *    mx = Mexico
 *    nl = Netherlands
 *    no = Norway
 *    nz = New Zealand
 *    om = Oman
 *    pl = Poland
 *    pt = Portugal
 *    qa = Qatar
 *    ro = Romania
 *    ru = Russian Federation
 *    sa = Saudi Arabia
 *    se = Sweden
 *    sg = Singapore
 *    si = Slovenia
 *    sk = Slovakia
 *    sy = Syrian Arab Republic
 *    tw = Taiwan
 *    tr = Turkey
 *    ua = Ukraine
 *    uk = United Kingdom
 *    us = United States
 *    ye = Yemen
 *    za = South Africa
 *
 */

extern  CFStringRef const kABOtherDatesProperty      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;         // Dates associated with this person - kABMultiDateProperty - (Person)
    extern  CFStringRef const kABAnniversaryLabel    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

extern  CFStringRef const kABRelatedNamesProperty    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;         // names - kABMultiStringProperty
    extern  CFStringRef const kABFatherLabel         AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
    extern  CFStringRef const kABMotherLabel         AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
    extern  CFStringRef const kABParentLabel         AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
    extern  CFStringRef const kABBrotherLabel        AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
    extern  CFStringRef const kABSisterLabel         AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
    extern  CFStringRef const kABChildLabel          AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
    extern  CFStringRef const kABFriendLabel         AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
    extern  CFStringRef const kABSpouseLabel         AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
    extern  CFStringRef const kABPartnerLabel        AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
    extern  CFStringRef const kABAssistantLabel      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
    extern  CFStringRef const kABManagerLabel        AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

extern CFStringRef const kABDepartmentProperty       AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;         // Department name - kABStringProperty - (Person)

extern CFStringRef const kABPersonFlags              AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;         // Various flags - kABIntegerProperty - (Person)
#define kABShowAsMask                           000007
#define kABShowAsPerson                         000000
#define kABShowAsCompany                        000001

#define kABNameOrderingMask                     000070
#define kABDefaultNameOrdering                  000000
#define kABFirstNameFirst                       000040
#define kABLastNameFirst                        000020

extern CFStringRef const kABPhoneProperty;                   // Generic phone number - kABMultiStringProperty
        extern CFStringRef const kABPhoneWorkLabel;          // Work phone
        extern CFStringRef const kABPhoneHomeLabel;          // Home phone
        extern CFStringRef const kABPhoneMobileLabel;        // Cell phone
        extern CFStringRef const kABPhoneMainLabel;          // Main phone
        extern CFStringRef const kABPhoneHomeFAXLabel;       // FAX number
        extern CFStringRef const kABPhoneWorkFAXLabel;       // FAX number
        extern CFStringRef const kABPhonePagerLabel;         // Pager number

extern CFStringRef const kABAIMInstantProperty;              // AIM Instant Messaging - kABMultiStringProperty
        extern CFStringRef const kABAIMWorkLabel;
        extern CFStringRef const kABAIMHomeLabel;

extern CFStringRef const kABJabberInstantProperty;           // Jabber Instant Messaging - kABMultiStringProperty
        extern CFStringRef const kABJabberWorkLabel;
        extern CFStringRef const kABJabberHomeLabel;

extern CFStringRef const kABMSNInstantProperty;              // MSN Instant Messaging - kABMultiStringProperty
        extern CFStringRef const kABMSNWorkLabel;
        extern CFStringRef const kABMSNHomeLabel;

extern CFStringRef const kABYahooInstantProperty;            // Yahoo Instant Messaging - kABMultiStringProperty
        extern CFStringRef const kABYahooWorkLabel;
        extern CFStringRef const kABYahooHomeLabel;

extern CFStringRef const kABICQInstantProperty;              // ICQ Instant Messaging - kABMultiStringProperty
        extern CFStringRef const kABICQWorkLabel;
        extern CFStringRef const kABICQHomeLabel;

extern CFStringRef const kABNoteProperty;                    // Note (string)

extern CFStringRef const kABMiddleNameProperty;              // kABStringProperty
extern CFStringRef const kABMiddleNamePhoneticProperty;      // kABStringProperty
extern CFStringRef const kABTitleProperty;                   // kABStringProperty "Sir" "Duke" "General" "Lord"
extern CFStringRef const kABSuffixProperty;                  // kABStringProperty "Sr." "Jr." "III"

// ----- Group Specific Properties

extern CFStringRef const kABGroupNameProperty;               // Name of the group - kABStringProperty

// ================================================================
//      Generic Labels
// ================================================================

    // All kABXXXXWorkLabel are equivalent to this label
extern CFStringRef const kABWorkLabel;

    // All kABXXXXHomeLabel are equivalent to this label
extern CFStringRef const kABHomeLabel;

    // Can be used with any multi-value property
extern CFStringRef const kABOtherLabel;

// ================================================================
//      RecordTypes
// ================================================================

    // Type of a ABPersonRef
extern CFStringRef const kABPersonRecordType;

    // Type of a ABGroupRef
extern CFStringRef const kABGroupRecordType;

// ================================================================
//      Notifications published when something changes
// ================================================================
// These notifications are not sent until ABGetSharedAddressBook()
// has been called somewhere

    // This process has changed the DB
extern CFStringRef const kABDatabaseChangedNotification;

    // Another process has changed the DB
extern CFStringRef const kABDatabaseChangedExternallyNotification;

    // The user info in the above notifications will contain
    // the following 3 keys, the values of the keys in the dictionary
    // will be the uniqueIds of the Inserted/Updated/Deleted Records
extern CFStringRef const kABInsertedRecords         AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
extern CFStringRef const kABUpdatedRecords          AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
extern CFStringRef const kABDeletedRecords          AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

#endif
#endif
