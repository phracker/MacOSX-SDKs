/*
     File:       ColorSync/CMScriptingPlugin.h
 
     Contains:   ColorSync Scripting Plugin API
 
     Version:    ColorSync-81~8
 
     Copyright:  © 1998-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __CMSCRIPTINGPLUGIN__
#define __CMSCRIPTINGPLUGIN__

#ifndef __FILES__
#include <CarbonCore/Files.h>
#endif

#ifndef __CMAPPLICATION__
#include <ColorSync/CMApplication.h>
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

enum {
                                        /* ColorSync Scripting AppleEvent Errors */
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


/**** scripting plugin entry points  ****/
typedef CALLBACK_API_C( CMError , ValidateImageProcPtr )(const FSSpec * spec);
typedef CALLBACK_API_C( CMError , GetImageSpaceProcPtr )(const FSSpec *spec, OSType *space);
typedef CALLBACK_API_C( CMError , ValidateSpaceProcPtr )(const FSSpec *spec, OSType *space);
typedef CALLBACK_API_C( CMError , EmbedImageProcPtr )(const FSSpec *specFrom, const FSSpec *specInto, CMProfileRef embedProf, UInt32 embedFlags);
typedef CALLBACK_API_C( CMError , UnembedImageProcPtr )(const FSSpec *specFrom, const FSSpec *specInto);
typedef CALLBACK_API_C( CMError , MatchImageProcPtr )(const FSSpec *specFrom, const FSSpec *specInto, UInt32 qual, UInt32 srcIntent, CMProfileRef srcProf, CMProfileRef dstProf, CMProfileRef prfProf, UInt32 matchFlags);
typedef CALLBACK_API_C( CMError , CountImageProfilesProcPtr )(const FSSpec *spec, UInt32 *count);
typedef CALLBACK_API_C( CMError , GetIndImageProfileProcPtr )(const FSSpec *spec, UInt32 index, CMProfileRef *prof);
typedef CALLBACK_API_C( CMError , SetIndImageProfileProcPtr )(const FSSpec *specFrom, const FSSpec *specInto, UInt32 index, CMProfileRef prof, UInt32 embedFlags);
/**** CSScriptingLib entry points  ****/
typedef CALLBACK_API_C( CMError , CMValidImageProcPtr )(const FSSpec * spec);
typedef CALLBACK_API_C( CMError , CMGetImageSpaceProcPtr )(const FSSpec *spec, OSType *space);
typedef CALLBACK_API_C( CMError , CMEmbedImageProcPtr )(const FSSpec *specFrom, const FSSpec *specInto, Boolean repl, CMProfileRef embProf);
typedef CALLBACK_API_C( CMError , CMUnembedImageProcPtr )(const FSSpec *specFrom, const FSSpec *specInto, Boolean repl);
typedef CALLBACK_API_C( CMError , CMMatchImageProcPtr )(const FSSpec *specFrom, const FSSpec *specInto, Boolean repl, UInt32 qual, CMProfileRef srcProf, UInt32 srcIntent, CMProfileRef dstProf);
typedef CALLBACK_API_C( CMError , CMProofImageProcPtr )(const FSSpec *specFrom, const FSSpec *specInto, Boolean repl, UInt32 qual, CMProfileRef srcProf, UInt32 srcIntent, CMProfileRef dstProf, CMProfileRef prfProf);
typedef CALLBACK_API_C( CMError , CMLinkImageProcPtr )(const FSSpec *specFrom, const FSSpec *specInto, Boolean repl, UInt32 qual, CMProfileRef lnkProf, UInt32 lnkIntent);
typedef CALLBACK_API_C( CMError , CMCountImageProfilesProcPtr )(const FSSpec *spec, UInt32 *count);
typedef CALLBACK_API_C( CMError , CMGetIndImageProfileProcPtr )(const FSSpec *spec, UInt32 index, CMProfileRef *prof);
typedef CALLBACK_API_C( CMError , CMSetIndImageProfileProcPtr )(const FSSpec *specFrom, const FSSpec *specInto, Boolean repl, UInt32 index, CMProfileRef prof);
/**** CSScriptingLib API  ****/

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

#endif /* __CMSCRIPTINGPLUGIN__ */

