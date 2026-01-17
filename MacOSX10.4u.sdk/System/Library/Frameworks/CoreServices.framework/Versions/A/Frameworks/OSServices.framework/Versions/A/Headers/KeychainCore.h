/*
     File:       SecurityCore/KeychainCore.h
 
     Contains:   Keychain low-level Interfaces
 
     Version:    SecurityCore-25606~262
 
     Copyright:  © 2000-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __KEYCHAINCORE__
#define __KEYCHAINCORE__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __FILES__
#include <CarbonCore/Files.h>
#endif

#ifndef __ALIASES__
#include <CarbonCore/Aliases.h>
#endif

#ifndef __CODEFRAGMENTS__
#include <CarbonCore/CodeFragments.h>
#endif

#ifndef __MACERRORS__
#include <CarbonCore/MacErrors.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

/* Data structures and types */
#ifndef __SEC_TYPES__
#define __SEC_TYPES__
typedef struct OpaqueSecKeychainRef*    SecKeychainRef;
typedef struct OpaqueSecKeychainItemRef*  SecKeychainItemRef;
typedef struct OpaqueSecKeychainSearchRef*  SecKeychainSearchRef;
typedef OSType                          SecKeychainAttrType;
typedef UInt32                          SecKeychainStatus;
struct SecKeychainAttribute {
  SecKeychainAttrType  tag;                   /* 4-byte attribute tag */
  UInt32              length;                 /* Length of attribute data */
  void *              data;                   /* Pointer to attribute data */
};
typedef struct SecKeychainAttribute     SecKeychainAttribute;
typedef SecKeychainAttribute *          SecKeychainAttributePtr;
struct SecKeychainAttributeList {
  UInt32              count;                  /* How many attributes in the array */
  SecKeychainAttribute * attr;                /* Pointer to first attribute in array */
};
typedef struct SecKeychainAttributeList SecKeychainAttributeList;
#endif

typedef SecKeychainRef                  KCRef;
typedef SecKeychainItemRef              KCItemRef;
typedef SecKeychainSearchRef            KCSearchRef;
typedef SecKeychainAttribute            KCAttribute;
typedef SecKeychainAttributeList        KCAttributeList;
typedef SecKeychainAttrType             KCAttrType;
typedef SecKeychainStatus               KCStatus;
typedef UInt16 KCEvent;
enum {
  kIdleKCEvent                  = 0,    /* null event */
  kLockKCEvent                  = 1,    /* a keychain was locked */
  kUnlockKCEvent                = 2,    /* a keychain was unlocked */
  kAddKCEvent                   = 3,    /* an item was added to a keychain */
  kDeleteKCEvent                = 4,    /* an item was deleted from a keychain */
  kUpdateKCEvent                = 5,    /* an item was updated */
  kPasswordChangedKCEvent       = 6,    /* the keychain identity was changed */
  kSystemKCEvent                = 8,    /* the keychain client can process events */
  kDefaultChangedKCEvent        = 9,    /* the default keychain was changed */
  kDataAccessKCEvent            = 10,   /* a process has accessed a keychain item's data */
  kKeychainListChangedKCEvent   = 11    /* the list of keychains has changed */
};

typedef UInt16 KCEventMask;
enum {
  kIdleKCEventMask              = 1 << kIdleKCEvent,
  kLockKCEventMask              = 1 << kLockKCEvent,
  kUnlockKCEventMask            = 1 << kUnlockKCEvent,
  kAddKCEventMask               = 1 << kAddKCEvent,
  kDeleteKCEventMask            = 1 << kDeleteKCEvent,
  kUpdateKCEventMask            = 1 << kUpdateKCEvent,
  kPasswordChangedKCEventMask   = 1 << kPasswordChangedKCEvent,
  kSystemEventKCEventMask       = 1 << kSystemKCEvent,
  kDefaultChangedKCEventMask    = 1 << kDefaultChangedKCEvent,
  kDataAccessKCEventMask        = 1 << kDataAccessKCEvent,
  kEveryKCEventMask             = 0xFFFF /* all of the above*/
};

typedef UInt8                           AFPServerSignature[16];
typedef UInt8                           KCPublicKeyHash[20];
struct KCCallbackInfo {
  UInt32              version;
  KCItemRef           item;
  long                processID[2];           /* unavailable on Mac OS X*/
  long                event[4];               /* unavailable on Mac OS X*/
  KCRef               keychain;
};
typedef struct KCCallbackInfo           KCCallbackInfo;
enum {
  kUnlockStateKCStatus          = 1,
  kRdPermKCStatus               = 2,
  kWrPermKCStatus               = 4
};


enum {
  kCertificateKCItemClass       = 'cert', /* Certificate */
  kAppleSharePasswordKCItemClass = 'ashp', /* Appleshare password */
  kInternetPasswordKCItemClass  = 'inet', /* Internet password */
  kGenericPasswordKCItemClass   = 'genp' /* Generic password */
};


typedef FourCharCode                    KCItemClass;
enum {
                                        /* Common attributes */
  kClassKCItemAttr              = 'clas', /* Item class (KCItemClass) */
  kCreationDateKCItemAttr       = 'cdat', /* Date the item was created (UInt32) */
  kModDateKCItemAttr            = 'mdat', /* Last time the item was updated (UInt32) */
  kDescriptionKCItemAttr        = 'desc', /* User-visible description string (string) */
  kCommentKCItemAttr            = 'icmt', /* User's comment about the item (string) */
  kCreatorKCItemAttr            = 'crtr', /* Item's creator (OSType) */
  kTypeKCItemAttr               = 'type', /* Item's type (OSType) */
  kScriptCodeKCItemAttr         = 'scrp', /* Script code for all strings (ScriptCode) */
  kLabelKCItemAttr              = 'labl', /* Item label (string) */
  kInvisibleKCItemAttr          = 'invi', /* Invisible (boolean) */
  kNegativeKCItemAttr           = 'nega', /* Negative (boolean) */
  kCustomIconKCItemAttr         = 'cusi', /* Custom icon (boolean) */
  kAccountKCItemAttr            = 'acct', /* User account (string) */
                                        /* Unique Generic password attributes */
  kServiceKCItemAttr            = 'svce', /* Service (string) */
  kGenericKCItemAttr            = 'gena', /* User-defined attribute (untyped bytes) */
                                        /* Unique Internet password attributes */
  kSecurityDomainKCItemAttr     = 'sdmn', /* Security domain (string) */
  kServerKCItemAttr             = 'srvr', /* Server's domain name or IP address (string) */
  kAuthTypeKCItemAttr           = 'atyp', /* Authentication Type (KCAuthType) */
  kPortKCItemAttr               = 'port', /* Port (UInt16) */
  kPathKCItemAttr               = 'path', /* Path (string) */
                                        /* Unique Appleshare password attributes */
  kVolumeKCItemAttr             = 'vlme', /* Volume (string) */
  kAddressKCItemAttr            = 'addr', /* Server address (IP or domain name) or zone name (string) */
  kSignatureKCItemAttr          = 'ssig', /* Server signature block (AFPServerSignature) */
                                        /* Unique AppleShare and Internet attributes */
  kProtocolKCItemAttr           = 'ptcl', /* Protocol (KCProtocolType) */
                                        /* Certificate attributes */
  kSubjectKCItemAttr            = 'subj', /* Subject distinguished name (DER-encoded data) */
  kCommonNameKCItemAttr         = 'cn  ', /* Common Name (UTF8-encoded string) */
  kIssuerKCItemAttr             = 'issu', /* Issuer distinguished name (DER-encoded data) */
  kSerialNumberKCItemAttr       = 'snbr', /* Certificate serial number (DER-encoded data) */
  kEMailKCItemAttr              = 'mail', /* E-mail address (ASCII-encoded string) */
  kPublicKeyHashKCItemAttr      = 'hpky', /* Hash of public key (KCPublicKeyHash), 20 bytes max. */
  kIssuerURLKCItemAttr          = 'iurl', /* URL of the certificate issuer (ASCII-encoded string) */
                                        /* Shared by keys and certificates */
  kEncryptKCItemAttr            = 'encr', /* Encrypt (Boolean) */
  kDecryptKCItemAttr            = 'decr', /* Decrypt (Boolean) */
  kSignKCItemAttr               = 'sign', /* Sign (Boolean) */
  kVerifyKCItemAttr             = 'veri', /* Verify (Boolean) */
  kWrapKCItemAttr               = 'wrap', /* Wrap (Boolean) */
  kUnwrapKCItemAttr             = 'unwr', /* Unwrap (Boolean) */
  kStartDateKCItemAttr          = 'sdat', /* Start Date (UInt32) */
  kEndDateKCItemAttr            = 'edat' /* End Date (UInt32) */
};

typedef FourCharCode                    KCItemAttr;
enum {
  kKCAuthTypeNTLM               = 'ntlm',
  kKCAuthTypeMSN                = 'msna',
  kKCAuthTypeDPA                = 'dpaa',
  kKCAuthTypeRPA                = 'rpaa',
  kKCAuthTypeHTTPDigest         = 'httd',
  kKCAuthTypeDefault            = 'dflt'
};

typedef FourCharCode                    KCAuthType;
enum {
  kKCProtocolTypeFTP            = 'ftp ',
  kKCProtocolTypeFTPAccount     = 'ftpa',
  kKCProtocolTypeHTTP           = 'http',
  kKCProtocolTypeIRC            = 'irc ',
  kKCProtocolTypeNNTP           = 'nntp',
  kKCProtocolTypePOP3           = 'pop3',
  kKCProtocolTypeSMTP           = 'smtp',
  kKCProtocolTypeSOCKS          = 'sox ',
  kKCProtocolTypeIMAP           = 'imap',
  kKCProtocolTypeLDAP           = 'ldap',
  kKCProtocolTypeAppleTalk      = 'atlk',
  kKCProtocolTypeAFP            = 'afp ',
  kKCProtocolTypeTelnet         = 'teln'
};

typedef FourCharCode                    KCProtocolType;
typedef UInt32 KCCertAddOptions;
enum {
  kSecOptionReserved            = 0x000000FF, /* First byte reserved for SecOptions flags */
  kCertUsageShift               = 8,    /* start at bit 8 */
  kCertUsageSigningAdd          = 1 << (kCertUsageShift + 0),
  kCertUsageSigningAskAndAdd    = 1 << (kCertUsageShift + 1),
  kCertUsageVerifyAdd           = 1 << (kCertUsageShift + 2),
  kCertUsageVerifyAskAndAdd     = 1 << (kCertUsageShift + 3),
  kCertUsageEncryptAdd          = 1 << (kCertUsageShift + 4),
  kCertUsageEncryptAskAndAdd    = 1 << (kCertUsageShift + 5),
  kCertUsageDecryptAdd          = 1 << (kCertUsageShift + 6),
  kCertUsageDecryptAskAndAdd    = 1 << (kCertUsageShift + 7),
  kCertUsageKeyExchAdd          = 1 << (kCertUsageShift + 8),
  kCertUsageKeyExchAskAndAdd    = 1 << (kCertUsageShift + 9),
  kCertUsageRootAdd             = 1 << (kCertUsageShift + 10),
  kCertUsageRootAskAndAdd       = 1 << (kCertUsageShift + 11),
  kCertUsageSSLAdd              = 1 << (kCertUsageShift + 12),
  kCertUsageSSLAskAndAdd        = 1 << (kCertUsageShift + 13),
  kCertUsageAllAdd              = 0x7FFFFF00
};

typedef UInt16 KCVerifyStopOn;
enum {
  kPolicyKCStopOn               = 0,
  kNoneKCStopOn                 = 1,
  kFirstPassKCStopOn            = 2,
  kFirstFailKCStopOn            = 3
};

typedef UInt32 KCCertSearchOptions;
enum {
  kCertSearchShift              = 0,    /* start at bit 0 */
  kCertSearchSigningIgnored     = 0,
  kCertSearchSigningAllowed     = 1 << (kCertSearchShift + 0),
  kCertSearchSigningDisallowed  = 1 << (kCertSearchShift + 1),
  kCertSearchSigningMask        = ((kCertSearchSigningAllowed) | (kCertSearchSigningDisallowed)),
  kCertSearchVerifyIgnored      = 0,
  kCertSearchVerifyAllowed      = 1 << (kCertSearchShift + 2),
  kCertSearchVerifyDisallowed   = 1 << (kCertSearchShift + 3),
  kCertSearchVerifyMask         = ((kCertSearchVerifyAllowed) | (kCertSearchVerifyDisallowed)),
  kCertSearchEncryptIgnored     = 0,
  kCertSearchEncryptAllowed     = 1 << (kCertSearchShift + 4),
  kCertSearchEncryptDisallowed  = 1 << (kCertSearchShift + 5),
  kCertSearchEncryptMask        = ((kCertSearchEncryptAllowed) | (kCertSearchEncryptDisallowed)),
  kCertSearchDecryptIgnored     = 0,
  kCertSearchDecryptAllowed     = 1 << (kCertSearchShift + 6),
  kCertSearchDecryptDisallowed  = 1 << (kCertSearchShift + 7),
  kCertSearchDecryptMask        = ((kCertSearchDecryptAllowed) | (kCertSearchDecryptDisallowed)),
  kCertSearchWrapIgnored        = 0,
  kCertSearchWrapAllowed        = 1 << (kCertSearchShift + 8),
  kCertSearchWrapDisallowed     = 1 << (kCertSearchShift + 9),
  kCertSearchWrapMask           = ((kCertSearchWrapAllowed) | (kCertSearchWrapDisallowed)),
  kCertSearchUnwrapIgnored      = 0,
  kCertSearchUnwrapAllowed      = 1 << (kCertSearchShift + 10),
  kCertSearchUnwrapDisallowed   = 1 << (kCertSearchShift + 11),
  kCertSearchUnwrapMask         = ((kCertSearchUnwrapAllowed) | (kCertSearchUnwrapDisallowed)),
  kCertSearchPrivKeyRequired    = 1 << (kCertSearchShift + 12),
  kCertSearchAny                = 0
};

/* Other constants */
enum {
  kAnyPort                      = 0
};

enum {
  kAnyProtocol                  = 0,
  kAnyAuthType                  = 0
};

/* Opening and getting information about the Keychain Manager */
/*
 *  KCGetKeychainManagerVersion()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
KCGetKeychainManagerVersion(UInt32 * returnVers);


#if TARGET_RT_MAC_CFM
#ifdef __cplusplus
    inline pascal Boolean KeychainManagerAvailable() { return ((KCGetKeychainManagerVersion != (void*)kUnresolvedCFragSymbolAddress) && (KCGetKeychainManagerVersion(nil) != cfragNoSymbolErr)); }
#else
    #define KeychainManagerAvailable()  ((KCGetKeychainManagerVersion != (void*)kUnresolvedCFragSymbolAddress) && (KCGetKeychainManagerVersion(nil) != cfragNoSymbolErr))
#endif
#elif TARGET_RT_MAC_MACHO
/* Keychain is always available on OS X */
#ifdef __cplusplus
    inline pascal Boolean KeychainManagerAvailable() { return true; }
#else
    #define KeychainManagerAvailable()  (true)
#endif
#endif  /*  */

/* Managing the Human Interface */
/*
 *  KCSetInteractionAllowed()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 2.0 and later
 */
extern OSStatus 
KCSetInteractionAllowed(Boolean state)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  KCIsInteractionAllowed()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 2.0 and later
 */
extern Boolean 
KCIsInteractionAllowed(void)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Creating references to keychains */
/*
 *  KCMakeKCRefFromFSSpec()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 2.0 and later
 */
extern OSStatus 
KCMakeKCRefFromFSSpec(
  FSSpec *  keychainFSSpec,
  KCRef *   keychain)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  KCMakeKCRefFromAlias()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 2.0 and later
 */
extern OSStatus 
KCMakeKCRefFromAlias(
  AliasHandle   keychainAlias,
  KCRef *       keychain)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  KCMakeAliasFromKCRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 2.0 and later
 */
extern OSStatus 
KCMakeAliasFromKCRef(
  KCRef          keychain,
  AliasHandle *  keychainAlias)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  KCReleaseKeychain()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 2.0 and later
 */
extern OSStatus 
KCReleaseKeychain(KCRef * keychain)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Specifying the default keychain */
/*
 *  KCGetDefaultKeychain()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 2.0 and later
 */
extern OSStatus 
KCGetDefaultKeychain(KCRef * keychain)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  KCSetDefaultKeychain()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 2.0 and later
 */
extern OSStatus 
KCSetDefaultKeychain(KCRef keychain)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Getting information about a keychain */
/*
 *  KCGetStatus()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
KCGetStatus(
  KCRef     keychain,             /* can be NULL */
  UInt32 *  keychainStatus)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  KCGetKeychain()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
KCGetKeychain(
  KCItemRef   item,
  KCRef *     keychain)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  KCGetKeychainName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 2.0 and later
 */
extern OSStatus 
KCGetKeychainName(
  KCRef       keychain,
  StringPtr   keychainName)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Enumerating available keychains */
/*
 *  KCCountKeychains()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern UInt16 
KCCountKeychains(void)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  KCGetIndKeychain()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
KCGetIndKeychain(
  UInt16   index,
  KCRef *  keychain)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


typedef CALLBACK_API( OSStatus , KCCallbackProcPtr )(KCEvent keychainEvent, KCCallbackInfo *info, void *userContext);
typedef STACK_UPP_TYPE(KCCallbackProcPtr)                       KCCallbackUPP;
/*
 *  NewKCCallbackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern KCCallbackUPP
NewKCCallbackUPP(KCCallbackProcPtr userRoutine)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeKCCallbackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeKCCallbackUPP(KCCallbackUPP userUPP)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeKCCallbackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeKCCallbackUPP(
  KCEvent           keychainEvent,
  KCCallbackInfo *  info,
  void *            userContext,
  KCCallbackUPP     userUPP)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/* High-level interface for retrieving passwords */
/*
 *  KCFindAppleSharePassword()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
KCFindAppleSharePassword(
  AFPServerSignature *  serverSignature,       /* can be NULL */
  ConstStringPtr        serverAddress,         /* can be NULL */
  ConstStringPtr        serverName,            /* can be NULL */
  ConstStringPtr        volumeName,            /* can be NULL */
  ConstStringPtr        accountName,           /* can be NULL */
  UInt32                maxLength,
  void *                passwordData,
  UInt32 *              actualLength,
  KCItemRef *           item)                  /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  KCFindInternetPassword()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
KCFindInternetPassword(
  ConstStringPtr   serverName,           /* can be NULL */
  ConstStringPtr   securityDomain,       /* can be NULL */
  ConstStringPtr   accountName,          /* can be NULL */
  UInt16           port,
  OSType           protocol,
  OSType           authType,
  UInt32           maxLength,
  void *           passwordData,
  UInt32 *         actualLength,
  KCItemRef *      item)                 /* can be NULL */    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  KCFindInternetPasswordWithPath()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 2.0 and later
 */
extern OSStatus 
KCFindInternetPasswordWithPath(
  ConstStringPtr   serverName,           /* can be NULL */
  ConstStringPtr   securityDomain,       /* can be NULL */
  ConstStringPtr   accountName,          /* can be NULL */
  ConstStringPtr   path,                 /* can be NULL */
  UInt16           port,
  OSType           protocol,
  OSType           authType,
  UInt32           maxLength,
  void *           passwordData,
  UInt32 *         actualLength,
  KCItemRef *      item)                 /* can be NULL */    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  KCFindGenericPassword()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
KCFindGenericPassword(
  ConstStringPtr   serviceName,        /* can be NULL */
  ConstStringPtr   accountName,        /* can be NULL */
  UInt32           maxLength,
  void *           passwordData,
  UInt32 *         actualLength,
  KCItemRef *      item)               /* can be NULL */      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Keychain Manager callbacks */
/*
 *  KCAddCallback()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
KCAddCallback(
  KCCallbackUPP   callbackProc,
  KCEventMask     eventMask,
  void *          userContext)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  KCRemoveCallback()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
KCRemoveCallback(KCCallbackUPP callbackProc)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Creating and editing a keychain item */
/*
 *  KCNewItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
KCNewItem(
  KCItemClass   itemClass,
  OSType        itemCreator,
  UInt32        length,
  const void *  data,
  KCItemRef *   item)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  KCSetAttribute()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
KCSetAttribute(
  KCItemRef      item,
  KCAttribute *  attr)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  KCGetAttribute()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
KCGetAttribute(
  KCItemRef      item,
  KCAttribute *  attr,
  UInt32 *       actualLength)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  KCSetData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
KCSetData(
  KCItemRef     item,
  UInt32        length,
  const void *  data)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Managing keychain items */
/*
 *  KCUpdateItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
KCUpdateItem(KCItemRef item)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  KCReleaseItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
KCReleaseItem(KCItemRef * item)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  KCCopyItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 2.0 and later
 */
extern OSStatus 
KCCopyItem(
  KCItemRef    item,
  KCRef        destKeychain,
  KCItemRef *  copy)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Searching and enumerating keychain items */
/*
 *  KCFindFirstItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
KCFindFirstItem(
  KCRef                    keychain,       /* can be NULL */
  const KCAttributeList *  attrList,       /* can be NULL */
  KCSearchRef *            search,
  KCItemRef *              item)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  KCFindNextItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
KCFindNextItem(
  KCSearchRef   search,
  KCItemRef *   item)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  KCReleaseSearch()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
KCReleaseSearch(KCSearchRef * search)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Managing keychain items */
/*
 *  KCDeleteItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
KCDeleteItem(KCItemRef item)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  KCGetData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
KCGetData(
  KCItemRef   item,
  UInt32      maxLength,
  void *      data,
  UInt32 *    actualLength)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Locking a keychain */
/*
 *  KCLock()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
KCLock(KCRef keychain)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Routines that use "C" strings */
/*
 *  kcgetkeychainname()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 2.0 and later
 */
extern OSStatus 
kcgetkeychainname(
  KCRef   keychain,
  char *  keychainName)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  kcfindapplesharepassword()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
kcfindapplesharepassword(
  AFPServerSignature *  serverSignature,       /* can be NULL */
  const char *          serverAddress,         /* can be NULL */
  const char *          serverName,            /* can be NULL */
  const char *          volumeName,            /* can be NULL */
  const char *          accountName,           /* can be NULL */
  UInt32                maxLength,
  void *                passwordData,
  UInt32 *              actualLength,
  KCItemRef *           item)                  /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  kcfindinternetpassword()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
kcfindinternetpassword(
  const char *  serverName,           /* can be NULL */
  const char *  securityDomain,       /* can be NULL */
  const char *  accountName,          /* can be NULL */
  UInt16        port,
  OSType        protocol,
  OSType        authType,
  UInt32        maxLength,
  void *        passwordData,
  UInt32 *      actualLength,
  KCItemRef *   item)                 /* can be NULL */       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  kcfindinternetpasswordwithpath()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 2.0 and later
 */
extern OSStatus 
kcfindinternetpasswordwithpath(
  const char *  serverName,           /* can be NULL */
  const char *  securityDomain,       /* can be NULL */
  const char *  accountName,          /* can be NULL */
  const char *  path,                 /* can be NULL */
  UInt16        port,
  OSType        protocol,
  OSType        authType,
  UInt32        maxLength,
  void *        passwordData,
  UInt32 *      actualLength,
  KCItemRef *   item)                 /* can be NULL */       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  kcfindgenericpassword()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
kcfindgenericpassword(
  const char *  serviceName,        /* can be NULL */
  const char *  accountName,        /* can be NULL */
  UInt32        maxLength,
  void *        passwordData,
  UInt32 *      actualLength,
  KCItemRef *   item)               /* can be NULL */         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __KEYCHAINCORE__ */

