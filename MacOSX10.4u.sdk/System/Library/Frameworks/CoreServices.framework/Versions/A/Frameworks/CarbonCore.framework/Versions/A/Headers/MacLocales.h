/*
     File:       CarbonCore/MacLocales.h
 
     Contains:   Types & prototypes for locale functions
 
     Version:    CarbonCore-682.26~1
 
     Copyright:  © 1998-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __MACLOCALES__
#define __MACLOCALES__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
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


/*
   -------------------------------------------------------------------------------------------------
   TYPES & CONSTANTS
   -------------------------------------------------------------------------------------------------
*/

typedef struct OpaqueLocaleRef*         LocaleRef;
typedef UInt32                          LocalePartMask;
enum {
                                        /* bit set requests the following:*/
  kLocaleLanguageMask           = 1L << 0, /* ISO 639-1 or -2 language code (2 or 3 letters)*/
  kLocaleLanguageVariantMask    = 1L << 1, /* custom string for language variant*/
  kLocaleScriptMask             = 1L << 2, /* ISO 15924 script code (2 letters)*/
  kLocaleScriptVariantMask      = 1L << 3, /* custom string for script variant*/
  kLocaleRegionMask             = 1L << 4, /* ISO 3166 country/region code (2 letters)*/
  kLocaleRegionVariantMask      = 1L << 5, /* custom string for region variant*/
  kLocaleAllPartsMask           = 0x0000003F /* all of the above*/
};

typedef FourCharCode                    LocaleOperationClass;
/* constants for LocaleOperationClass are in UnicodeUtilities interfaces*/
typedef FourCharCode                    LocaleOperationVariant;
struct LocaleAndVariant {
  LocaleRef           locale;
  LocaleOperationVariant  opVariant;
};
typedef struct LocaleAndVariant         LocaleAndVariant;

typedef UInt32                          LocaleNameMask;
enum {
                                        /* bit set requests the following:*/
  kLocaleNameMask               = 1L << 0, /* name of locale*/
  kLocaleOperationVariantNameMask = 1L << 1, /* name of LocaleOperationVariant*/
  kLocaleAndVariantNameMask     = 0x00000003 /* all of the above*/
};

/*
   -------------------------------------------------------------------------------------------------
   FUNCTION PROTOTYPES
   -------------------------------------------------------------------------------------------------
*/

/* Convert to or from LocaleRefs (and related utilities)*/

/*
 *  LocaleRefFromLangOrRegionCode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LocalesLib 8.6 and later
 */
extern OSStatus 
LocaleRefFromLangOrRegionCode(
  LangCode     lang,
  RegionCode   region,
  LocaleRef *  locale)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LocaleRefFromLocaleString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LocalesLib 8.6 and later
 */
extern OSStatus 
LocaleRefFromLocaleString(
  const char   localeString[],
  LocaleRef *  locale)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LocaleRefGetPartString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LocalesLib 8.6 and later
 */
extern OSStatus 
LocaleRefGetPartString(
  LocaleRef        locale,
  LocalePartMask   partMask,
  ByteCount        maxStringLen,
  char             partString[])                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  LocaleStringToLangAndRegionCodes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LocalesLib 9.0 and later
 */
extern OSStatus 
LocaleStringToLangAndRegionCodes(
  const char    localeString[],
  LangCode *    lang,
  RegionCode *  region)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* Enumerate locales for a LocaleOperationClass */

/*
 *  LocaleOperationCountLocales()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LocalesLib 8.6 and later
 */
extern OSStatus 
LocaleOperationCountLocales(
  LocaleOperationClass   opClass,
  ItemCount *            localeCount)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LocaleOperationGetLocales()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LocalesLib 8.6 and later
 */
extern OSStatus 
LocaleOperationGetLocales(
  LocaleOperationClass   opClass,
  ItemCount              maxLocaleCount,
  ItemCount *            actualLocaleCount,
  LocaleAndVariant       localeVariantList[])                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Get names for a locale (or a region's language)*/

/*
 *  LocaleGetName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LocalesLib 8.6 and later
 */
extern OSStatus 
LocaleGetName(
  LocaleRef                locale,
  LocaleOperationVariant   opVariant,
  LocaleNameMask           nameMask,
  LocaleRef                displayLocale,
  UniCharCount             maxNameLen,
  UniCharCount *           actualNameLen,
  UniChar                  displayName[])                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LocaleCountNames()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LocalesLib 8.6 and later
 */
extern OSStatus 
LocaleCountNames(
  LocaleRef                locale,
  LocaleOperationVariant   opVariant,
  LocaleNameMask           nameMask,
  ItemCount *              nameCount)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LocaleGetIndName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LocalesLib 8.6 and later
 */
extern OSStatus 
LocaleGetIndName(
  LocaleRef                locale,
  LocaleOperationVariant   opVariant,
  LocaleNameMask           nameMask,
  ItemCount                nameIndex,
  UniCharCount             maxNameLen,
  UniCharCount *           actualNameLen,
  UniChar                  displayName[],
  LocaleRef *              displayLocale)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  LocaleGetRegionLanguageName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LocalesLib 9.0 and later
 */
extern OSStatus 
LocaleGetRegionLanguageName(
  RegionCode   region,
  Str255       languageName)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* Get names for a LocaleOperationClass*/

/*
 *  LocaleOperationGetName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LocalesLib 8.6 and later
 */
extern OSStatus 
LocaleOperationGetName(
  LocaleOperationClass   opClass,
  LocaleRef              displayLocale,
  UniCharCount           maxNameLen,
  UniCharCount *         actualNameLen,
  UniChar                displayName[])                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LocaleOperationCountNames()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LocalesLib 8.6 and later
 */
extern OSStatus 
LocaleOperationCountNames(
  LocaleOperationClass   opClass,
  ItemCount *            nameCount)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LocaleOperationGetIndName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LocalesLib 8.6 and later
 */
extern OSStatus 
LocaleOperationGetIndName(
  LocaleOperationClass   opClass,
  ItemCount              nameIndex,
  UniCharCount           maxNameLen,
  UniCharCount *         actualNameLen,
  UniChar                displayName[],
  LocaleRef *            displayLocale)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __MACLOCALES__ */

