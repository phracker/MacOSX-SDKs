/*
     File:       SecurityHI/KeychainHI.h
 
     Contains:   Keychain API's with Human Interfaces
 
     Version:    SecurityHI-56.2~77
 
     Copyright:  © 2000-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __KEYCHAINHI__
#define __KEYCHAINHI__

#ifndef __KEYCHAINCORE__
#include <SecurityCore/KeychainCore.h>
#endif

#ifndef __CFSTRING__
#include <CoreFoundation/CFString.h>
#endif

#ifndef __CFARRAY__
#include <CoreFoundation/CFArray.h>
#endif

#ifndef __CFDATE__
#include <CoreFoundation/CFDate.h>
#endif




#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if PRAGMA_STRUCT_ALIGN
    #pragma options align=mac68k
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif PRAGMA_STRUCT_PACK
    #pragma pack(2)
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
  KCItemRef *           item);                 /* can be NULL */


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
  KCItemRef *   item);                /* can be NULL */


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
  KCItemRef *   item);                /* can be NULL */


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
  KCItemRef *   item);                /* can be NULL */


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
KCAddItem(KCItemRef item);


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
  StringPtr   password);      /* can be NULL */


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
  KCRef *     keychain);      /* can be NULL */


/*
 *  KCChangeSettings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in KeychainLib 2.0 and later
 */
extern OSStatus 
KCChangeSettings(KCRef keychain);


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
  const char *  password);      /* can be NULL */


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
  KCRef *       keychain);      /* can be NULL */


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
  KCItemRef *           item);                 /* can be NULL */


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
  KCItemRef *   item);                /* can be NULL */


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
  KCItemRef *   item);                /* can be NULL */


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
  KCItemRef *   item);                /* can be NULL */


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




#if PRAGMA_STRUCT_ALIGN
    #pragma options align=reset
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

#ifdef __cplusplus
}
#endif

#endif /* __KEYCHAINHI__ */

