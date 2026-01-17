/*
 *  ABGlobals.h
 *  AddressBook Framework
 *
 *  Copyright (c) 2003-2010 Apple Inc.  All rights reserved.
 *
 */

#ifndef __ABGLOBALS__
#define __ABGLOBALS__

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
extern NSString * const kABBirthdayComponentsProperty AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;  // Birth date - kABDateComponentsProperty
extern NSString * const kABAlternateBirthdayComponentsProperty; //Alternate non-Gregorian birth date - kABDateComponentsProperty

extern NSString * const kABOrganizationProperty;          // Company name - kABStringProperty
extern NSString * const kABOrganizationPhoneticProperty;   // Company name phonetic - kABStringProperty


extern NSString * const kABJobTitleProperty;              // Job Title - kABStringProperty

// Deprecated in Mac OS 10.4. You should use kABURLsProperty.
extern NSString * const kABHomePageProperty;              // Home Web page - kABStringProperty

extern NSString * const kABURLsProperty AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;          // URLs - kABMultiStringProperty
        extern NSString * const kABHomePageLabel AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; // Homepage URL
		
extern NSString * const kABCalendarURIsProperty AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER; // Calendar URIs - kABMultiStringProperty

extern NSString * const kABEmailProperty;                 // Email(s) - kABMultiStringProperty
        extern NSString * const kABEmailWorkLabel;        // Work email
        extern NSString * const kABEmailHomeLabel;        // Home email
        extern NSString * const kABEmailMobileMeLabel;    // MobileMe email

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
extern NSString* const kABOtherDateComponentsProperty AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;    // Dates associated with this person - kABMultiDateComponentsProperty - (Person)
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
	#define kABShowAsResource                       000002
	#define kABShowAsRoom                           000003

    #define kABNameOrderingMask                     000070
    #define kABDefaultNameOrdering                  000000
    #define kABFirstNameFirst                       000040
    #define kABLastNameFirst                        000020

extern NSString * const kABPhoneProperty;                  // Generic phone number - kABMultiStringProperty
		extern NSString * const kABPhoneWorkLabel;         // Work phone
		extern NSString * const kABPhoneHomeLabel;         // Home phone
		extern NSString * const kABPhoneiPhoneLabel;       // iPhone
		extern NSString * const kABPhoneMobileLabel;       // Cell phone
		extern NSString * const kABPhoneMainLabel;         // Main phone
		extern NSString * const kABPhoneHomeFAXLabel;      // FAX number
		extern NSString * const kABPhoneWorkFAXLabel;      // FAX number
		extern NSString * const kABPhonePagerLabel;        // Pager number

// Deprecated in Mac OS 10.7. You should use kABInstantMessageProperty.
extern NSString * const kABAIMInstantProperty						DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;	// AIM Instant Messaging - kABMultiStringProperty
		extern NSString * const kABAIMWorkLabel						DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;
		extern NSString * const kABAIMHomeLabel						DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;
		extern NSString * const kABAIMMobileMeLabel					DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

// Deprecated in Mac OS 10.7. You should use kABInstantMessageProperty.
extern NSString * const kABJabberInstantProperty					DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;	// Jabber Instant Messaging - kABMultiStringProperty
		extern NSString * const kABJabberWorkLabel					DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;
		extern NSString * const kABJabberHomeLabel					DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

// Deprecated in Mac OS 10.7. You should use kABInstantMessageProperty.
extern NSString * const kABMSNInstantProperty						DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;	// MSN Instant Messaging  - kABMultiStringProperty
		extern NSString * const kABMSNWorkLabel						DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;
		extern NSString * const kABMSNHomeLabel						DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

// Deprecated in Mac OS 10.7. You should use kABInstantMessageProperty.
extern NSString * const kABYahooInstantProperty						DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;	// Yahoo Instant Messaging  - kABMultiStringProperty
		extern NSString * const kABYahooWorkLabel						DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;
		extern NSString * const kABYahooHomeLabel						DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

// Deprecated in Mac OS 10.7. You should use kABInstantMessageProperty.
extern NSString * const kABICQInstantProperty						DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;	// ICQ Instant Messaging  - kABMultiStringProperty
		extern NSString * const kABICQWorkLabel						DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;
		extern NSString * const kABICQHomeLabel						DEPRECATED_IN_MAC_OS_X_VERSION_10_7_AND_LATER;

extern NSString * const kABInstantMessageProperty					AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER; // Instant Messaging - kABMultiDictionaryProperty
	extern NSString * const kABInstantMessageUsernameKey			AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;		// dictionary key for the instant messaging handle/username
	extern NSString * const kABInstantMessageServiceKey				AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;		// dictionary key for the service type, not guaranteed to be present; possible values follow
		extern NSString * const kABInstantMessageServiceAIM			AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;		// AIM
		extern NSString * const kABInstantMessageServiceFacebook	AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;		// Facebook
		extern NSString * const kABInstantMessageServiceGaduGadu	AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;		// Gadu-Gadu
		extern NSString * const kABInstantMessageServiceGoogleTalk	AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;		// Google Talk
		extern NSString * const kABInstantMessageServiceICQ			AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;		// ICQ
		extern NSString * const kABInstantMessageServiceJabber		AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;		// Jabber
		extern NSString * const kABInstantMessageServiceMSN			AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;		// MSN
		extern NSString * const kABInstantMessageServiceQQ			AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;		// QQ
		extern NSString * const kABInstantMessageServiceSkype		AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;		// Skype
		extern NSString * const kABInstantMessageServiceYahoo		AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;		// Yahoo!

extern NSString * const kABSocialProfileProperty                    AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;  // Social Profiles - kABMultiDictionaryProperty
    extern NSString * const kABSocialProfileURLKey                  AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;  // String representation of the profile URL
    extern NSString * const kABSocialProfileUsernameKey             AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;  // User-visible profile name
    extern NSString * const kABSocialProfileUserIdentifierKey       AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;  // Service-specific identifier
    extern NSString * const kABSocialProfileServiceKey              AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;  // Service name. Possible values follow.
        extern NSString * const kABSocialProfileServiceTwitter      AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;
        extern NSString * const kABSocialProfileServiceFacebook     AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;
        extern NSString * const kABSocialProfileServiceLinkedIn     AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;
        extern NSString * const kABSocialProfileServiceFlickr       AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;
        extern NSString * const kABSocialProfileServiceMySpace      AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;
        extern NSString * const kABSocialProfileServiceSinaWeibo    AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER;
        extern NSString * const kABSocialProfileServiceTencentWeibo AVAILABLE_MAC_OS_X_VERSION_10_9_AND_LATER;
        extern NSString * const kABSocialProfileServiceYelp         AVAILABLE_MAC_OS_X_VERSION_10_9_AND_LATER;

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

    // MobileMe - for AIM or email values
extern NSString * const kABMobileMeLabel AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;


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

#endif // __ABGLOBALS__

