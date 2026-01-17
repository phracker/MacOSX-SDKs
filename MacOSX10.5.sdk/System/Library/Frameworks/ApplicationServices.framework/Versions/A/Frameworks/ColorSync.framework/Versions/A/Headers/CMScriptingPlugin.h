/*
     File:       ColorSync/CMScriptingPlugin.h
 
     Contains:   ColorSync Scripting Plugin API
 
     Copyright:  1998-2005 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult http://developer.apple.com/bugreporter/
 
*/
#ifndef __CMSCRIPTINGPLUGIN__
#define __CMSCRIPTINGPLUGIN__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __CMAPPLICATION__
#include <ColorSync/CMApplication.h>
#endif


#include <ColorSync/CMBase.h>

#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#if !__LP64__ && !TARGET_OS_WIN32

#ifdef __cplusplus
extern "C" {
#endif

enum {
                                        /* ColorSync Scripting Errors */
  cmspInvalidImageFile          = -4220, /* Plugin cannot handle this image file type */
  cmspInvalidImageSpace         = -4221, /* Plugin cannot create an image file of this colorspace */
  cmspInvalidProfileEmbed       = -4222, /* Specific invalid profile errors */
  cmspInvalidProfileSource      = -4223,
  cmspInvalidProfileDest        = -4224,
  cmspInvalidProfileProof       = -4225,
  cmspInvalidProfileLink        = -4226
};


/**** embedFlags field  ****/
/* reserved for future use: currently 0 */

/**** matchFlags field  ****/
enum {
  cmspFavorEmbeddedMask         = 0x00000001 /* if bit 0 is 0 then use srcProf profile, if 1 then use profile embedded in image if present*/
};


CSEXTERN CMError 
CMValidImage(const FSSpec * spec)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


CSEXTERN CMError 
CMGetImageSpace(
  const FSSpec *  spec,
  OSType *        space)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


CSEXTERN CMError 
CMEmbedImage(
  const FSSpec *  specFrom,
  const FSSpec *  specInto,
  Boolean         repl,
  CMProfileRef    embProf)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


CSEXTERN CMError 
CMUnembedImage(
  const FSSpec *  specFrom,
  const FSSpec *  specInto,
  Boolean         repl)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


CSEXTERN CMError 
CMMatchImage(
  const FSSpec *  specFrom,
  const FSSpec *  specInto,
  Boolean         repl,
  UInt32          qual,
  CMProfileRef    srcProf,
  UInt32          srcIntent,
  CMProfileRef    dstProf)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


CSEXTERN CMError 
CMProofImage(
  const FSSpec *  specFrom,
  const FSSpec *  specInto,
  Boolean         repl,
  UInt32          qual,
  CMProfileRef    srcProf,
  UInt32          srcIntent,
  CMProfileRef    dstProf,
  CMProfileRef    prfProf)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


CSEXTERN CMError 
CMLinkImage(
  const FSSpec *  specFrom,
  const FSSpec *  specInto,
  Boolean         repl,
  UInt32          qual,
  CMProfileRef    lnkProf,
  UInt32          lnkIntent)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


CSEXTERN CMError 
CMCountImageProfiles(
  const FSSpec *  spec,
  UInt32 *        count)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


CSEXTERN CMError 
CMGetIndImageProfile(
  const FSSpec *  spec,
  UInt32          index,
  CMProfileRef *  prof)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


CSEXTERN CMError 
CMSetIndImageProfile(
  const FSSpec *  specFrom,
  const FSSpec *  specInto,
  Boolean         repl,
  UInt32          index,
  CMProfileRef    prof)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;



#ifdef __cplusplus
}
#endif

#endif // !__LP64__ && !TARGET_OS_WIN32

#endif /* __CMSCRIPTINGPLUGIN__ */

