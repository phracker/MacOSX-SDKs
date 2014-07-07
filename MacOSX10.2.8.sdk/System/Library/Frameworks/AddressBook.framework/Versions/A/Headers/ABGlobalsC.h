/*
 *  ABGlobalsC.h
 *  AddressBook Framework
 *
 *  Copyright (c) 2001 Apple Computer. All rights reserved.
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

extern CFStringRef kABUIDProperty;                   // The UID property
extern CFStringRef kABCreationDateProperty;          // Creation Date (when first saved) (date)
extern CFStringRef kABModificationDateProperty;      // Last saved date (date)

// ----- Person specific properties

extern CFStringRef kABFirstNameProperty;             // First name (string)
extern CFStringRef kABLastNameProperty;              // Last name  (string)

extern CFStringRef kABFirstNamePhoneticProperty;     // First name Phonetic (string)
extern CFStringRef kABLastNamePhoneticProperty;      // Last name Phonetic (string)

extern CFStringRef kABBirthdayProperty;              // Birth date  (date)

extern CFStringRef kABOrganizationProperty;          // Company name  (string)

extern CFStringRef kABJobTitleProperty;              // Job Title  (string)

extern CFStringRef kABHomePageProperty;              // Home Web page  (string)

extern CFStringRef kABEmailProperty;                 // Email(s) (multi-string)
        extern CFStringRef kABEmailWorkLabel;        // Work email
        extern CFStringRef kABEmailHomeLabel;        // Home email

extern CFStringRef kABAddressProperty;                // Street Addresses (multi-dictionary)
    extern CFStringRef kABAddressStreetKey;           // Street
    extern CFStringRef kABAddressCityKey;             // City
    extern CFStringRef kABAddressStateKey;            // State
    extern CFStringRef kABAddressZIPKey;              // Zip
    extern CFStringRef kABAddressCountryKey;          // Country
    extern CFStringRef kABAddressCountryCodeKey;      // Country Code
        extern CFStringRef kABAddressHomeLabel;       // Home Address
        extern CFStringRef kABAddressWorkLabel;       // Work Address

/*
 * kABAddressCountryCodeKey code must be one of the following:
 * iso country codes
 *
 *    at = Austria
 *    au = Australia
 *    be = Belgium
 *    ca = Canada
 *    ch = Switzerland
 *    cn = China
 *    de = Germany
 *    dk = Denmark
 *    es = Spain
 *    fi = Finland
 *    fr = France
 *    gl = Greenland
 *    ie = Ireland
 *    il = Israel
 *    id = Indonesia
 *    is = Iceland
 *    it = Italy
 *    ja = Japan
 *    kr = South Korea
 *    lu = Luxembourg
 *    mx = Mexico
 *    nl = Netherlands
 *    no = Norway
 *    nz = New Zealand
 *    pl = Poland
 *    pt = Portugal
 *    se = Sweden
 *    sg = Singapore
 *    tr = Turkey
 *    tw = Taiwan
 *    uk = United Kingdom
 *    us = United States
 *    za = South Africa
 *
 */

extern CFStringRef kABPhoneProperty;                  // Generic phone number (multi-string)
        extern CFStringRef kABPhoneWorkLabel;         // Work phone
        extern CFStringRef kABPhoneHomeLabel;         // Home phone
        extern CFStringRef kABPhoneMobileLabel;       // Cell phone
        extern CFStringRef kABPhoneMainLabel;         // Main phone
        extern CFStringRef kABPhoneHomeFAXLabel;      // FAX number
        extern CFStringRef kABPhoneWorkFAXLabel;      // FAX number
        extern CFStringRef kABPhonePagerLabel;        // Pager number

extern CFStringRef kABAIMInstantProperty;             // AIM Instant Messaging (multi-string)
        extern CFStringRef kABAIMWorkLabel;
        extern CFStringRef kABAIMHomeLabel;

extern CFStringRef kABJabberInstantProperty;          // Jabber Instant Messaging (multi-string)
        extern CFStringRef kABJabberWorkLabel;
        extern CFStringRef kABJabberHomeLabel;

extern CFStringRef kABMSNInstantProperty;             // MSN Instant Messaging  (multi-string)
        extern CFStringRef kABMSNWorkLabel;
        extern CFStringRef kABMSNHomeLabel;

extern CFStringRef kABYahooInstantProperty;           // Yahoo Instant Messaging  (multi-string)
        extern CFStringRef kABYahooWorkLabel;
        extern CFStringRef kABYahooHomeLabel;

extern CFStringRef kABICQInstantProperty;             // ICQ Instant Messaging  (multi-string)
        extern CFStringRef kABICQWorkLabel;
        extern CFStringRef kABICQHomeLabel;

extern CFStringRef kABNoteProperty;                   // Note (string)

// ----- Person Properties not Currently supported in the AddressBook UI
extern CFStringRef kABMiddleNameProperty;		// string
extern CFStringRef kABMiddleNamePhoneticProperty;	// string
extern CFStringRef kABTitleProperty;			// string "Sir" "Duke" "General" "Lord"
extern CFStringRef kABSuffixProperty;                	// string "Sr." "Jr." "III"
extern CFStringRef kABNicknameProperty;                	// string
extern CFStringRef kABMaidenNameProperty;		// string

// ----- Group Specific Properties

extern CFStringRef kABGroupNameProperty;              // Name of the group

// ================================================================
//      Generic Labels
// ================================================================

    // All kABXXXXWorkLabel are equivalent to this label
extern CFStringRef kABWorkLabel;

    // All kABXXXXHomeLabel are equivalent to this label
extern CFStringRef kABHomeLabel;

    // Can be use with any Mutli-value property
extern CFStringRef kABOtherLabel;

// ================================================================
//      RecordTypes
// ================================================================

    // Type of a ABPersonRef
extern CFStringRef kABPersonRecordType;

    // Type of a ABGroupRef
extern CFStringRef kABGroupRecordType;

// ================================================================
//      Notifications published when something changes
// ================================================================

    // This process has changed the DB
extern CFStringRef kABDatabaseChangedNotification;

    // Another process has changed the DB
extern CFStringRef kABDatabaseChangedExternallyNotification;


#endif

#endif
