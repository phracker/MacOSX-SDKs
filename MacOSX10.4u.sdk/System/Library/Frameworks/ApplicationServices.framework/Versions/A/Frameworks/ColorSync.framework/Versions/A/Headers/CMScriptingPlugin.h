/*
     File:       ColorSync/CMScriptingPlugin.h
 
     Contains:   ColorSync Scripting Plugin API
 
     Version:    ColorSync-174.3.3~45
 
     Copyright:  © 1998-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __CMSCRIPTINGPLUGIN__
#define __CMSCRIPTINGPLUGIN__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __CMAPPLICATION__
#include <ColorSync/CMApplication.h>
#endif




#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

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


/*
 *  CMValidImage()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CSScriptingLib 2.6 and later
 */
extern CMError 
CMValidImage(const FSSpec * spec);


/*
 *  CMGetImageSpace()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CSScriptingLib 2.6 and later
 */
extern CMError 
CMGetImageSpace(
  const FSSpec *  spec,
  OSType *        space);


/*
 *  CMEmbedImage()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CSScriptingLib 2.6 and later
 */
extern CMError 
CMEmbedImage(
  const FSSpec *  specFrom,
  const FSSpec *  specInto,
  Boolean         repl,
  CMProfileRef    embProf);


/*
 *  CMUnembedImage()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CSScriptingLib 2.6 and later
 */
extern CMError 
CMUnembedImage(
  const FSSpec *  specFrom,
  const FSSpec *  specInto,
  Boolean         repl);


/*
 *  CMMatchImage()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CSScriptingLib 2.6 and later
 */
extern CMError 
CMMatchImage(
  const FSSpec *  specFrom,
  const FSSpec *  specInto,
  Boolean         repl,
  UInt32          qual,
  CMProfileRef    srcProf,
  UInt32          srcIntent,
  CMProfileRef    dstProf);


/*
 *  CMProofImage()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CSScriptingLib 2.6 and later
 */
extern CMError 
CMProofImage(
  const FSSpec *  specFrom,
  const FSSpec *  specInto,
  Boolean         repl,
  UInt32          qual,
  CMProfileRef    srcProf,
  UInt32          srcIntent,
  CMProfileRef    dstProf,
  CMProfileRef    prfProf);


/*
 *  CMLinkImage()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CSScriptingLib 2.6 and later
 */
extern CMError 
CMLinkImage(
  const FSSpec *  specFrom,
  const FSSpec *  specInto,
  Boolean         repl,
  UInt32          qual,
  CMProfileRef    lnkProf,
  UInt32          lnkIntent);


/*
 *  CMCountImageProfiles()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CSScriptingLib 2.6 and later
 */
extern CMError 
CMCountImageProfiles(
  const FSSpec *  spec,
  UInt32 *        count);


/*
 *  CMGetIndImageProfile()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CSScriptingLib 2.6 and later
 */
extern CMError 
CMGetIndImageProfile(
  const FSSpec *  spec,
  UInt32          index,
  CMProfileRef *  prof);


/*
 *  CMSetIndImageProfile()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CSScriptingLib 2.6 and later
 */
extern CMError 
CMSetIndImageProfile(
  const FSSpec *  specFrom,
  const FSSpec *  specInto,
  Boolean         repl,
  UInt32          index,
  CMProfileRef    prof);



#ifdef __cplusplus
}
#endif

#endif /* __CMSCRIPTINGPLUGIN__ */

