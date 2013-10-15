/*
 *  ABGlobals.h
 *  AddressBook Framework
 *
 *  Copyright (c) 2002-2003 Apple Computer. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>

// ================================================================
//      Global Table properties
// ================================================================

// ----- Properties common to all Records

extern NSString * const kABUIDProperty;                   // The UID property - kABStringProperty
extern NSString * const kABCreationDateProperty;          // Creation Date (when first saved) - kABDateProperty
extern NSString * const kABModificationDateProperty;      // Last saved date - kABDateProperty

// ----- Person specific properties

extern NSString * const kABFirstNameProperty;             // First name - kABStringProperty
extern NSString * const kABLastNameProperty;              // Last name - kABStringProperty

extern NSString * const kABFirstNamePhoneticProperty;     // First name Phonetic - kABStringProperty
extern NSString * const kABLastNamePhoneticProperty;      // Last name Phonetic - kABStringProperty

extern NSString * const kABNicknameProperty;              // kABStringProperty
extern NSString * const kABMaidenNameProperty;            // kABStringProperty

extern NSString * const kABBirthdayProperty;              // Birth date - kABDateProperty

extern NSString * const kABOrganizationProperty;          // Company name - kABStringProperty

extern NSString * const kABJobTitleProperty;              // Job Title - kABStringProperty

// Deprecated in Mac OS 10.4. You should use kABURLsProperty.
extern NSString * const kABHomePageProperty;              // Home Web page - kABStringProperty

extern NSString * const kABURLsProperty AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;          // URLs - kABMultiStringProperty
        extern NSString * const kABHomePageLabel AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; // Homepage URL

extern NSString * const kABEmailProperty;                 // Email(s) - kABMultiStringProperty
        extern NSString * const kABEmailWorkLabel;        // Home email
        extern NSString * const kABEmailHomeLabel;        // Work email

extern NSString * const kABAddressProperty;                // Street Addresses - kABMultiDictionaryProperty
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
 *    ae = United Arab Emirates
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
 *    yu = Serbia and Montenegro
 *    za = South Africa
 *
 */

extern NSString* const kABOtherDatesProperty       AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;       // Dates associated with this person - kABMultiDateProperty - (Person)
       extern  NSString* const kABAnniversaryLabel AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

extern NSString* const kABRelatedNamesProperty     AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;       // names - kABMultiStringProperty
       extern  NSString* const kABFatherLabel      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
       extern  NSString* const kABMotherLabel      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
       extern  NSString* const kABParentLabel      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
       extern  NSString* const kABBrotherLabel     AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
       extern  NSString* const kABSisterLabel      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
       extern  NSString* const kABChildLabel       AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
       extern  NSString* const kABFriendLabel      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
       extern  NSString* const kABSpouseLabel      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
       extern  NSString* const kABPartnerLabel     AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
       extern  NSString* const kABAssistantLabel   AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
       extern  NSString* const kABManagerLabel     AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

extern NSString * const kABDepartmentProperty      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;     // Department name - (Person)

extern NSString * const kABPersonFlags             AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;     // Various flags - kABIntegerProperty
    #define kABShowAsMask                           000007
    #define kABShowAsPerson                         000000
    #define kABShowAsCompany                        000001

    #define kABNameOrderingMask                     000070
    #define kABDefaultNameOrdering                  000000
    #define kABFirstNameFirst                       000040
    #define kABLastNameFirst                        000020

extern NSString * const kABPhoneProperty;                  // Generic phone number - kABMultiStringProperty
        extern NSString * const kABPhoneWorkLabel;         // Work phone
        extern NSString * const kABPhoneHomeLabel;         // Home phone
        extern NSString * const kABPhoneMobileLabel;       // Cell phone
        extern NSString * const kABPhoneMainLabel;         // Main phone
        extern NSString * const kABPhoneHomeFAXLabel;      // FAX number
        extern NSString * const kABPhoneWorkFAXLabel;      // FAX number
        extern NSString * const kABPhonePagerLabel;        // Pager number

extern NSString * const kABAIMInstantProperty;             // AIM Instant Messaging - kABMultiStringProperty
        extern NSString * const kABAIMWorkLabel;
        extern NSString * const kABAIMHomeLabel;

extern NSString * const kABJabberInstantProperty;          // Jabber Instant Messaging - kABMultiStringProperty
        extern NSString * const kABJabberWorkLabel;
        extern NSString * const kABJabberHomeLabel;

extern NSString * const kABMSNInstantProperty;             // MSN Instant Messaging  - kABMultiStringProperty
        extern NSString * const kABMSNWorkLabel;
        extern NSString * const kABMSNHomeLabel;

extern NSString * const kABYahooInstantProperty;           // Yahoo Instant Messaging  - kABMultiStringProperty
        extern NSString * const kABYahooWorkLabel;
        extern NSString * const kABYahooHomeLabel;

extern NSString * const kABICQInstantProperty;             // ICQ Instant Messaging  - kABMultiStringProperty
        extern NSString * const kABICQWorkLabel;
        extern NSString * const kABICQHomeLabel;

extern NSString * const kABNoteProperty;                   // Note - kABStringProperty

extern NSString * const kABMiddleNameProperty;             // kABStringProperty
extern NSString * const kABMiddleNamePhoneticProperty;     // kABStringProperty
extern NSString * const kABTitleProperty;                  // kABStringProperty "Sir" "Duke" "General" "Lord"
extern NSString * const kABSuffixProperty;                 // kABStringProperty "Sr." "Jr." "III"

// ----- Group Specific Properties

extern NSString * const kABGroupNameProperty;              // Name of the group - kABStringProperty

// ================================================================
//      Generic Labels
// ================================================================

    // All kABXXXXWorkLabel are equivalent to this label
extern NSString * const kABWorkLabel;

    // All kABXXXXHomeLabel are equivalent to this label
extern NSString * const kABHomeLabel;

    // Can be used with any multi-value property
extern NSString * const kABOtherLabel;

// ================================================================
//      Notifications published when something changes
// ================================================================
// These notifications are not sent until [ABAddressBook sharedAddressBook]
// has been called somewhere

    // This process has changed the DB
extern NSString * const kABDatabaseChangedNotification;

    // Another process has changed the DB
extern NSString * const kABDatabaseChangedExternallyNotification;

    // The user info (dictionary) in the above notification will contain
    // the following 3 keys. Value for each keys is an array of
    // uniqueId of the Inserted/Updated/Deleted Records.
    // If all three values are nil assume that everything has changed (could be the case
    // when restoring from backup)
extern NSString * const kABInsertedRecords          AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
extern NSString * const kABUpdatedRecords           AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
extern NSString * const kABDeletedRecords           AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


// ================================================================
//      Localization of property or label
// ================================================================

    // Returns the localized version of built in properties, labels or keys
    // Returns propertyOrLabel if not found (e.g. if not built in)
NSString *ABLocalizedPropertyOrLabel(NSString *propertyOrLabel);
