/*
 *  ABGlobals.h
 *  AddressBook Framework
 *
 *  Copyright (c) 2002 Apple Computer. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>

// ================================================================
//      Global Table properties
// ================================================================

// ----- Properties common to all Records

extern NSString * const kABUIDProperty;                   // The UID property
extern NSString * const kABCreationDateProperty;          // Creation Date (when first saved) (date)
extern NSString * const kABModificationDateProperty;      // Last saved date (date)

// ----- Person specific properties

extern NSString * const kABFirstNameProperty;             // First name (string)
extern NSString * const kABLastNameProperty;              // Last name  (string)

extern NSString * const kABFirstNamePhoneticProperty;     // First name Phonetic (string)
extern NSString * const kABLastNamePhoneticProperty;      // Last name Phonetic (string)

extern NSString * const kABBirthdayProperty;              // Birth date  (date)

extern NSString * const kABOrganizationProperty;          // Company name  (string)

extern NSString * const kABJobTitleProperty;              // Job Title  (string)

extern NSString * const kABHomePageProperty;              // Home Web page  (string)

extern NSString * const kABEmailProperty;                 // Email(s) (multi-string)
        extern NSString * const kABEmailWorkLabel;        // Home email
        extern NSString * const kABEmailHomeLabel;        // Work email

extern NSString * const kABAddressProperty;                // Street Addresses (multi-dictionary)
    extern NSString * const kABAddressStreetKey;           // Street
    extern NSString * const kABAddressCityKey;             // City
    extern NSString * const kABAddressStateKey;            // State
    extern NSString * const kABAddressZIPKey;              // Zip
    extern NSString * const kABAddressCountryKey;          // Country
    extern NSString * const kABAddressCountryCodeKey;      // Country Code
        extern NSString * const kABAddressHomeLabel;       // Home Address
        extern NSString * const kABAddressWorkLabel;       // Work Address

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

extern NSString * const kABPhoneProperty;                  // Generic phone number (multi-string)
        extern NSString * const kABPhoneWorkLabel;         // Work phone
        extern NSString * const kABPhoneHomeLabel;         // Home phone
        extern NSString * const kABPhoneMobileLabel;       // Cell phone
        extern NSString * const kABPhoneMainLabel;         // Main phone
        extern NSString * const kABPhoneHomeFAXLabel;      // FAX number
        extern NSString * const kABPhoneWorkFAXLabel;      // FAX number
        extern NSString * const kABPhonePagerLabel;        // Pager number

extern NSString * const kABAIMInstantProperty;             // AIM Instant Messaging (multi-string)
        extern NSString * const kABAIMWorkLabel;
        extern NSString * const kABAIMHomeLabel;

extern NSString * const kABJabberInstantProperty;          // Jabber Instant Messaging (multi-string)
        extern NSString * const kABJabberWorkLabel;
        extern NSString * const kABJabberHomeLabel;

extern NSString * const kABMSNInstantProperty;             // MSN Instant Messaging  (multi-string)
        extern NSString * const kABMSNWorkLabel;
        extern NSString * const kABMSNHomeLabel;

extern NSString * const kABYahooInstantProperty;           // Yahoo Instant Messaging  (multi-string)
        extern NSString * const kABYahooWorkLabel;
        extern NSString * const kABYahooHomeLabel;

extern NSString * const kABICQInstantProperty;             // ICQ Instant Messaging  (multi-string)
        extern NSString * const kABICQWorkLabel;
        extern NSString * const kABICQHomeLabel;

extern NSString * const kABNoteProperty;                   // Note (string)

// ----- Person Properties not Currently supported in the AddressBook UI
extern NSString * const kABMiddleNameProperty;			// string
extern NSString * const kABMiddleNamePhoneticProperty;		// string
extern NSString * const kABTitleProperty;			// string "Sir" "Duke" "General" "Lord"
extern NSString * const kABSuffixProperty;                	// string "Sr." "Jr." "III"
extern NSString * const kABNicknameProperty;                	// string
extern NSString * const kABMaidenNameProperty;                	// string

// ----- Group Specific Properties

extern NSString * const kABGroupNameProperty;              // Name of the group

// ================================================================
//      Generic Labels
// ================================================================

    // All kABXXXXWorkLabel are equivalent to this label
extern NSString * const kABWorkLabel;

    // All kABXXXXHomeLabel are equivalent to this label
extern NSString * const kABHomeLabel;

    // Can be use with any Mutli-value property
extern NSString * const kABOtherLabel;

// ================================================================
//      Notifications published when something changes
// ================================================================

    // This process has changed the DB
extern NSString * const kABDatabaseChangedNotification;

    // Another process has changed the DB
extern NSString * const kABDatabaseChangedExternallyNotification;

// ================================================================
//      Localization of property or label
// ================================================================

    // Returns the localized version of built in properties, labels or keys
    // Returns propertyOrLabel if not found (e.g. if not built in)
NSString *ABLocalizedPropertyOrLabel(NSString *propertyOrLabel);

