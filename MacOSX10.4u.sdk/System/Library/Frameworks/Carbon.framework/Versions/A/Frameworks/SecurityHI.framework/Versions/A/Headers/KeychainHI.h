/*
     File:       SecurityHI/KeychainHI.h
 
     Contains:   Keychain API's with Human Interfaces
 
     Version:    SecurityHI-24742~1491
 
     Copyright:  © 2000-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __KEYCHAINHI__
#define __KEYCHAINHI__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif


#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* High-level interface for storing passwords */
/*
 *  KCAddAppleSharePassword()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
KCAddAppleSharePassword(
  AFPServerSignature *  serverSignature,
  StringPtr             serverAddress,
  StringPtr             serverName,
  StringPtr             volumeName,
  StringPtr             accountName,
  UInt32                passwordLength,
  const void *          passwordData,
  KCItemRef *           item)                  /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  KCAddInternetPassword()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
KCAddInternetPassword(
  StringPtr     serverName,
  StringPtr     securityDomain,
  StringPtr     accountName,
  UInt16        port,
  OSType        protocol,
  OSType        authType,
  UInt32        passwordLength,
  const void *  passwordData,
  KCItemRef *   item)                 /* can be NULL */       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  KCAddInternetPasswordWithPath()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 2.0 and later
 */
extern OSStatus 
KCAddInternetPasswordWithPath(
  StringPtr     serverName,
  StringPtr     securityDomain,
  StringPtr     accountName,
  StringPtr     path,
  UInt16        port,
  OSType        protocol,
  OSType        authType,
  UInt32        passwordLength,
  const void *  passwordData,
  KCItemRef *   item)                 /* can be NULL */       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  KCAddGenericPassword()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
KCAddGenericPassword(
  StringPtr     serviceName,
  StringPtr     accountName,
  UInt32        passwordLength,
  const void *  passwordData,
  KCItemRef *   item)                 /* can be NULL */       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Low-level interface for storing keychain items */
/*
 *  KCAddItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
KCAddItem(KCItemRef item)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Managing keychains */
/*
 *  KCUnlock()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
KCUnlock(
  KCRef       keychain,       /* can be NULL */
  StringPtr   password)       /* can be NULL */               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  KCCreateKeychain()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
KCCreateKeychain(
  StringPtr   password,       /* can be NULL */
  KCRef *     keychain)       /* can be NULL */               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  KCChangeSettings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 2.0 and later
 */
extern OSStatus 
KCChangeSettings(KCRef keychain)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  kcunlock()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
kcunlock(
  KCRef         keychain,       /* can be NULL */
  const char *  password)       /* can be NULL */             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  kccreatekeychain()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
kccreatekeychain(
  const char *  password,       /* can be NULL */
  KCRef *       keychain)       /* can be NULL */             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  kcaddapplesharepassword()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
kcaddapplesharepassword(
  AFPServerSignature *  serverSignature,
  const char *          serverAddress,
  const char *          serverName,
  const char *          volumeName,
  const char *          accountName,
  UInt32                passwordLength,
  const void *          passwordData,
  KCItemRef *           item)                  /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  kcaddinternetpassword()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
kcaddinternetpassword(
  const char *  serverName,
  const char *  securityDomain,
  const char *  accountName,
  UInt16        port,
  OSType        protocol,
  OSType        authType,
  UInt32        passwordLength,
  const void *  passwordData,
  KCItemRef *   item)                 /* can be NULL */       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  kcaddinternetpasswordwithpath()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 2.0 and later
 */
extern OSStatus 
kcaddinternetpasswordwithpath(
  const char *  serverName,
  const char *  securityDomain,
  const char *  accountName,
  const char *  path,
  UInt16        port,
  OSType        protocol,
  OSType        authType,
  UInt32        passwordLength,
  const void *  passwordData,
  KCItemRef *   item)                 /* can be NULL */       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  kcaddgenericpassword()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 1.0 and later
 */
extern OSStatus 
kcaddgenericpassword(
  const char *  serviceName,
  const char *  accountName,
  UInt32        passwordLength,
  const void *  passwordData,
  KCItemRef *   item)                 /* can be NULL */       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Working with certificates */
/*
 *  KCFindX509Certificates()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in KeychainLib 2.0 and later
 */


/*
 *  KCChooseCertificate()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in KeychainLib 2.0 and later
 */




#ifdef __cplusplus
}
#endif

#endif /* __KEYCHAINHI__ */

