/*
     File:       ATS/ATSFont.h
 
     Contains:   Public interface to the font access and data management functions of ATS.
 
     Version:    ATS
 
     Copyright:  © 2000-2011 by Apple Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __ATSFONT__
#define __ATSFONT__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __COREFOUNDATION__
#include <CoreFoundation/CoreFoundation.h>
#endif

#ifndef __ATSTYPES__
#include <ATS/ATSTypes.h>
#endif

#ifndef __SFNTTYPES__
#include <ATS/SFNTTypes.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 2)

#if PRAGMA_ENUM_ALWAYSINT
    #pragma enumsalwaysint on
#endif

enum {
  kATSOptionFlagsDefault        = kNilOptions,
  kATSOptionFlagsComposeFontPostScriptName = 1 << 0, /* ATSFontGetPostScriptName */
  kATSOptionFlagsUseDataForkAsResourceFork = 1 << 8, /* ATSFontActivateFromFileSpecification */
  kATSOptionFlagsUseResourceFork = 2 << 8,
  kATSOptionFlagsUseDataFork    = 3 << 8
};

enum {
  kATSIterationCompleted        = -980L,
  kATSInvalidFontFamilyAccess   = -981L,
  kATSInvalidFontAccess         = -982L,
  kATSIterationScopeModified    = -983L,
  kATSInvalidFontTableAccess    = -984L,
  kATSInvalidFontContainerAccess = -985L,
  kATSInvalidGlyphAccess        = -986L
};

/* Activation Option Flags */
typedef UInt32                          ATSFontContext;
enum {
  kATSFontContextUnspecified    = 0,
  kATSFontContextGlobal         = 1,
  kATSFontContextLocal          = 2
};

enum {
  kATSOptionFlagsActivateDisabled = 0x00000001 << 5, /* Used by activate to activate fonts in the disabled state */
  kATSOptionFlagsProcessSubdirectories = 0x00000001 << 6, /* Used by activation/deactivation & iteration */
  kATSOptionFlagsDoNotNotify    = 0x00000001 << 7, /* Do not notify after global activation/deactivation */
  kATSOptionFlagsRecordPersistently = 0x00000001 << 18 /* Used by activated/deactivation to record/remove font references in persistent store to be remembered at next login */
};

/* Iteration Option Flags */
enum {
  kATSOptionFlagsIterateByPrecedenceMask = 0x00000001 << 5, /* Fonts returned from highest to lowest precedece */
  kATSOptionFlagsIncludeDisabledMask = 0x00000001 << 7, /* Disabled Fonts will show up in iteration, also valid for ATSFontFindFromContainer */
  kATSOptionFlagsIterationScopeMask = 0x00000007 << 12, /* Mask option bits 12-14 for iteration scopes */
  kATSOptionFlagsDefaultScope   = 0x00000000 << 12,
  kATSOptionFlagsUnRestrictedScope = 0x00000001 << 12,
  kATSOptionFlagsRestrictedScope = 0x00000002 << 12
};

typedef CALLBACK_API_C( OSStatus , ATSFontFamilyApplierFunction )(ATSFontFamilyRef iFamily, void *iRefCon);
typedef CALLBACK_API_C( OSStatus , ATSFontApplierFunction )(ATSFontRef iFont, void *iRefCon);
typedef struct ATSFontFamilyIterator_*  ATSFontFamilyIterator;
typedef struct ATSFontIterator_*        ATSFontIterator;
enum {
  kATSFontFilterCurrentVersion  = 0
};

enum ATSFontFilterSelector {
  kATSFontFilterSelectorUnspecified = 0,
  kATSFontFilterSelectorGeneration = 3,
  kATSFontFilterSelectorFontFamily = 7,
  kATSFontFilterSelectorFontFamilyApplierFunction = 8,
  kATSFontFilterSelectorFontApplierFunction = 9,
  kATSFileReferenceFilterSelector = 10
};
typedef enum ATSFontFilterSelector ATSFontFilterSelector;

struct ATSFontFilter {
  UInt32              version;
  ATSFontFilterSelector  filterSelector;
  union {
    ATSGeneration       generationFilter;
    ATSFontFamilyRef    fontFamilyFilter;
    ATSFontFamilyApplierFunction  fontFamilyApplierFunctionFilter;
    ATSFontApplierFunction  fontApplierFunctionFilter;
    const FSRef *       fontFileRefFilter;
  }                       filter;
};
typedef struct ATSFontFilter            ATSFontFilter;
/* Notification related */
typedef struct ATSFontNotificationRef_*  ATSFontNotificationRef;
typedef struct ATSFontNotificationInfoRef_*  ATSFontNotificationInfoRef;

/*
 *  ATSFontNotifyOption
 *  
 *  Discussion:
 *    Options used with ATSFontNotificationSubscribe.  Any of the
 *    options that follow may be used together in order to alter the
 *    default behavior of ATS notifications.
 */
enum ATSFontNotifyOption {

  /*
   * Default behavior of ATSFontNotificationSubscribe.
   */
  kATSFontNotifyOptionDefault   = 0,

  /*
   * Normally applications will only receive ATS notifications while in
   * the foreground.   If suspended, the notification will be delivered
   * when then application comes to the foreground.  This is the
   * default.  You should set this option if you are a server or tool
   * that performs font management functions and require immediate
   * notification when something changes.
   */
  kATSFontNotifyOptionReceiveWhileSuspended = 1L << 0
};
typedef enum ATSFontNotifyOption ATSFontNotifyOption;




/*
 *  ATSFontNotifyAction
 *  
 *  Discussion:
 *    Used with ATSFontNotify.   The following is a list of actions you
 *    might wish the ATS server to perform and notify clients if
 *    appropriate.
 */
enum ATSFontNotifyAction {

  /*
   * Used after a batch (de)activation of fonts occurs.   Typically the
   * caller has exercised multiple global (De)Activation calls with the
   * kATSOptionFlagsDoNotNotify set. Once all calls are completed, one
   * may use ATSFontNotify with this action to ask ATS to notify all
   * clients.
   */
  kATSFontNotifyActionFontsChanged = 1,

  /*
   * The ATS system with the help of the Finder keeps track of changes
   * to any of the font directories in the system domains ( System,
   * Local, Network, User, & Classic). However, one may wish to
   * add/remove fonts to these locations programmatically. This action
   * is used to let ATS server to rescan these directories and post
   * notifications if necessary.
   */
  kATSFontNotifyActionDirectoriesChanged = 2
};
typedef enum ATSFontNotifyAction ATSFontNotifyAction;



/*
 *  ATSNotificationCallback
 *  
 *  Discussion:
 *    Callback delivered for ATS notifications.
 *  
 *  Parameters:
 *    
 *    info:
 *      Parameter is placed here for future improvements.  Initially
 *      the contents of this parameter will be NULL.
 *    
 *    refCon:
 *      User data/state to be supplied to callback function
 */
typedef CALLBACK_API_C( void , ATSNotificationCallback )(ATSFontNotificationInfoRef info, void *refCon);
/* ----------------------------------------------------------------------------------------- */
/* Font container                                                                            */
/* ----------------------------------------------------------------------------------------- */
/*
 *  ATSGetGeneration()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern ATSGeneration 
ATSGetGeneration(void)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#if !__LP64__
/*
 *  ATSFontActivateFromFileSpecification()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use ATSFontActivateFromFileReference instead.
 *  
 *  Summary:
 *    Activates one or more fonts from a file specification.
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Parameters:
 *    
 *    iFile:
 *      A pointer to the file specification that specifies the name and
 *      location of a file or directory that contains the font data you
 *      want to activate.
 *    
 *    iContext:
 *      A value that specifies the context of the activated font.
 *    
 *    iFormat:
 *      A value that represents the format identifier of the font. Pass
 *      kATSFontFormatUnspecified as the system automatically
 *      determines the format of the font.
 *    
 *    iReserved:
 *      This parameter is currently reserved for future use, so you
 *      should pass NULL.
 *    
 *    iOptions:
 *      An options flag.  See developer documentation for appropriate
 *      flags.
 *    
 *    oContainer:
 *      On output, a reference to the font container that is activated
 *      from the file specification. You need this reference when you
 *      deactivate the font by calling the function ATSFontDeactivate.
 *  
 *  Result:
 *    noErr Activated successfully
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontActivateFromFileSpecification(
  const FSSpec *         iFile,
  ATSFontContext         iContext,
  ATSFontFormat          iFormat,
  void *                 iReserved,
  ATSOptionFlags         iOptions,
  ATSFontContainerRef *  oContainer)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


#endif  /* !__LP64__ */

/*
 *  ATSFontActivateFromFileReference()
 *  
 *  Summary:
 *    Activates one or more fonts from a file reference.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.5
 *  
 *  Parameters:
 *    
 *    iFile:
 *      A pointer to the file specification that specifies the name and
 *      location of a file or directory that contains the font data you
 *      want to activate.
 *    
 *    iContext:
 *      A value that specifies the context of the activated font.
 *    
 *    iFormat:
 *      A value that represents the format identifier of the font. Pass
 *      kATSFontFormatUnspecified as the system automatically
 *      determines the format of the font.
 *    
 *    iRefCon:
 *      This parameter is currently reserved for future use, so you
 *      should pass NULL.
 *    
 *    iOptions:
 *      An options flag.  See developer documentation for appropriate
 *      flags.
 *    
 *    oContainer:
 *      On output, a reference to the font container that is activated
 *      from the file specification. You need this reference when you
 *      deactivate the font by calling the function ATSFontDeactivate.
 *  
 *  Result:
 *    noErr Activated successfully
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontActivateFromFileReference(
  const FSRef *          iFile,
  ATSFontContext         iContext,
  ATSFontFormat          iFormat,
  void *                 iRefCon,
  ATSOptionFlags         iOptions,
  ATSFontContainerRef *  oContainer)                          AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  ATSFontActivateFromMemory()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontActivateFromMemory(
  LogicalAddress         iData,
  ByteCount              iLength,
  ATSFontContext         iContext,
  ATSFontFormat          iFormat,
  void *                 iReserved,
  ATSOptionFlags         iOptions,
  ATSFontContainerRef *  oContainer)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSFontDeactivate()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontDeactivate(
  ATSFontContainerRef   iContainer,
  void *                iRefCon,
  ATSOptionFlags        iOptions)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSFontGetContainerFromFileReference()
 *  
 *  Summary:
 *    Get the font container reference associated with an activated
 *    file reference.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.5
 *  
 *  Parameters:
 *    
 *    iFile:
 *      A pointer to the valid file reference that specificies the
 *      activated font file for which to get the container.
 *    
 *    iContext:
 *      The context that the font file is accessible too. If
 *      kATSFontContextGlobal is specified this function will return
 *      only a valid font container reference that was activated in
 *      kATSFontContextGlobal. If kATSFontContextDefault or
 *      kATSFontContextLocal is used, the container returned will
 *      adhere to precedence rules. In which case a container activated
 *      in kATSFontContextLocal will be preferred over one activated in
 *      kATSFontContextGlobal.
 *    
 *    iOptions:
 *      An options flag.  See developer documentation for appropriate
 *      flags.
 *    
 *    oContainer:
 *      On output, a reference to the font container representing the
 *      file reference activated in the specified context. On error or
 *      for a file that is not activated, this will be set to
 *      kATSFontContainerRefUnspecified.
 *  
 *  Result:
 *    paramErr One or more parameters are invalid.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontGetContainerFromFileReference(
  const FSRef *          iFile,
  ATSFontContext         iContext,
  ATSOptionFlags         iOptions,
  ATSFontContainerRef *  oContainer)                          AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  ATSFontGetContainer()
 *  
 *  Summary:
 *    Gets the font container reference for the font.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.5
 *  
 *  Parameters:
 *    
 *    iFont:
 *      The font reference.
 *    
 *    iOptions:
 *      An options flag.  See developer documentation for appropriate
 *      flags.
 *    
 *    oContainer:
 *      On output, a reference to the font container that was used to
 *      activate the font reference. On error this will be set to
 *      kATSFontContainerRefUnspecified.
 *  
 *  Result:
 *    kATSInvalidFontContainerAccess The font container is invalid.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontGetContainer(
  ATSFontRef             iFont,
  ATSOptionFlags         iOptions,
  ATSFontContainerRef *  oContainer)                          AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  ATSFontSetEnabled()
 *  
 *  Summary:
 *    Sets a font's state to enabled or disabled.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.5
 *  
 *  Parameters:
 *    
 *    iFont:
 *      The font reference.
 *    
 *    iOptions:
 *      An options flag.  See developer documentation for appropriate
 *      flags.
 *    
 *    iEnabled:
 *      The state to set the font to. True for enabled, false for
 *      disabled.
 *  
 *  Result:
 *    kATSInvalidFontAccess The font reference is invalid in the
 *    current application context.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontSetEnabled(
  ATSFontRef       iFont,
  ATSOptionFlags   iOptions,
  Boolean          iEnabled)                                  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  ATSFontIsEnabled()
 *  
 *  Summary:
 *    Returns true if the font is enabled.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.5
 *  
 *  Parameters:
 *    
 *    iFont:
 *      The font reference
 *  
 *  Result:
 *    false The font is disabled.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
ATSFontIsEnabled(ATSFontRef iFont)                            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/* ----------------------------------------------------------------------------------------- */
/* Font family                                                                               */
/* ----------------------------------------------------------------------------------------- */
/*
 *  ATSFontFamilyApplyFunction()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontFamilyApplyFunction(
  ATSFontFamilyApplierFunction   iFunction,
  void *                         iRefCon)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSFontFamilyIteratorCreate()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontFamilyIteratorCreate(
  ATSFontContext           iContext,
  const ATSFontFilter *    iFilter,          /* can be NULL */
  void *                   iRefCon,
  ATSOptionFlags           iOptions,
  ATSFontFamilyIterator *  ioIterator)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSFontFamilyIteratorRelease()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontFamilyIteratorRelease(ATSFontFamilyIterator * ioIterator) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSFontFamilyIteratorReset()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontFamilyIteratorReset(
  ATSFontContext           iContext,
  const ATSFontFilter *    iFilter,          /* can be NULL */
  void *                   iRefCon,
  ATSOptionFlags           iOptions,
  ATSFontFamilyIterator *  ioIterator)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSFontFamilyIteratorNext()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontFamilyIteratorNext(
  ATSFontFamilyIterator   iIterator,
  ATSFontFamilyRef *      oFamily)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSFontFamilyFindFromName()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern ATSFontFamilyRef 
ATSFontFamilyFindFromName(
  CFStringRef      iName,
  ATSOptionFlags   iOptions)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSFontFamilyGetGeneration()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern ATSGeneration 
ATSFontFamilyGetGeneration(ATSFontFamilyRef iFamily)          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSFontFamilyGetName()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontFamilyGetName(
  ATSFontFamilyRef   iFamily,
  ATSOptionFlags     iOptions,
  CFStringRef *      oName)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSFontFamilyGetEncoding()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern TextEncoding 
ATSFontFamilyGetEncoding(ATSFontFamilyRef iFamily)            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ----------------------------------------------------------------------------------------- */
/* Font                                                                                      */
/* ----------------------------------------------------------------------------------------- */
/*
 *  ATSFontApplyFunction()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontApplyFunction(
  ATSFontApplierFunction   iFunction,
  void *                   iRefCon)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSFontIteratorCreate()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontIteratorCreate(
  ATSFontContext         iContext,
  const ATSFontFilter *  iFilter,          /* can be NULL */
  void *                 iRefCon,
  ATSOptionFlags         iOptions,
  ATSFontIterator *      ioIterator)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSFontIteratorRelease()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontIteratorRelease(ATSFontIterator * ioIterator)          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSFontIteratorReset()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontIteratorReset(
  ATSFontContext         iContext,
  const ATSFontFilter *  iFilter,          /* can be NULL */
  void *                 iRefCon,
  ATSOptionFlags         iOptions,
  ATSFontIterator *      ioIterator)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSFontIteratorNext()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontIteratorNext(
  ATSFontIterator   iIterator,
  ATSFontRef *      oFont)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSFontFindFromName()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern ATSFontRef 
ATSFontFindFromName(
  CFStringRef      iName,
  ATSOptionFlags   iOptions)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSFontFindFromPostScriptName()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern ATSFontRef 
ATSFontFindFromPostScriptName(
  CFStringRef      iName,
  ATSOptionFlags   iOptions)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSFontFindFromContainer()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontFindFromContainer(
  ATSFontContainerRef   iContainer,
  ATSOptionFlags        iOptions,
  ItemCount             iCount,
  ATSFontRef            ioArray[],
  ItemCount *           oCount)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSFontGetGeneration()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern ATSGeneration 
ATSFontGetGeneration(ATSFontRef iFont)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSFontGetName()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontGetName(
  ATSFontRef       iFont,
  ATSOptionFlags   iOptions,
  CFStringRef *    oName)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSFontGetPostScriptName()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontGetPostScriptName(
  ATSFontRef       iFont,
  ATSOptionFlags   iOptions,
  CFStringRef *    oName)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSFontGetTableDirectory()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontGetTableDirectory(
  ATSFontRef   iFont,
  ByteCount    iBufferSize,
  void *       ioBuffer,
  ByteCount *  oSize)             /* can be NULL */           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSFontGetTable()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontGetTable(
  ATSFontRef     iFont,
  FourCharCode   iTag,
  ByteOffset     iOffset,
  ByteCount      iBufferSize,
  void *         ioBuffer,
  ByteCount *    oSize)             /* can be NULL */         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSFontGetHorizontalMetrics()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontGetHorizontalMetrics(
  ATSFontRef        iFont,
  ATSOptionFlags    iOptions,
  ATSFontMetrics *  oMetrics)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSFontGetVerticalMetrics()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontGetVerticalMetrics(
  ATSFontRef        iFont,
  ATSOptionFlags    iOptions,
  ATSFontMetrics *  oMetrics)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ----------------------------------------------------------------------------------------- */
/* Compatibility                                                                             */
/* ----------------------------------------------------------------------------------------- */
/*
 *  ATSFontFamilyFindFromQuickDrawName()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern ATSFontFamilyRef 
ATSFontFamilyFindFromQuickDrawName(ConstStr255Param iName)    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSFontFamilyGetQuickDrawName()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontFamilyGetQuickDrawName(
  ATSFontFamilyRef   iFamily,
  Str255             oName)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#if !__LP64__
/*
 *  ATSFontGetFileSpecification()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use ATSFontGetFileReference instead.
 *  
 *  Summary:
 *    Obtains the file specification for a font.
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Parameters:
 *    
 *    iFont:
 *      A reference to the font whose file specification you want to
 *      obtain.
 *    
 *    oFile:
 *      On output, points to the file specification that specifies the
 *      name and location of a file or directory that contains the font
 *      data specified by the iFont parameter.
 *  
 *  Result:
 *    noErr File specification obtained successfully.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontGetFileSpecification(
  ATSFontRef   iFont,
  ATSFSSpec *  oFile)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


#endif  /* !__LP64__ */

/*
 *  ATSFontGetFileReference()
 *  
 *  Summary:
 *    Obtains the file reference for a font.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.5
 *  
 *  Parameters:
 *    
 *    iFont:
 *      A reference to the font whose file specification you want to
 *      obtain.
 *    
 *    oFile:
 *      On output, points to the file reference that specifies the name
 *      and location of a file or directory that contains the font data
 *      specified by the iFont parameter.
 *  
 *  Result:
 *    noErr File specification obtained successfully.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontGetFileReference(
  ATSFontRef   iFont,
  FSRef *      oFile)                                         AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;



/*
 *  ATSFontGetFontFamilyResource()
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontGetFontFamilyResource(
  ATSFontRef   iFont,
  ByteCount    iBufferSize,
  void *       ioBuffer,
  ByteCount *  oSize)             /* can be NULL */           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/* ----------------------------------------------------------------------------------------- */
/* Notification                                                                              */
/* ----------------------------------------------------------------------------------------- */
/*
 *  ATSFontNotify()
 *  
 *  Summary:
 *    Used to alert ATS that an action which may require notification
 *    to clients has occurred.
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Parameters:
 *    
 *    action:
 *      Action that should be taken by the ATS Server
 *    
 *    info:
 *      Any required or optional information that may be required by
 *      the action taken.
 *  
 *  Result:
 *    noErr Action successfully reported paramErr Invalid action passed
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontNotify(
  ATSFontNotifyAction   action,
  void *                info)         /* can be NULL */       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*
 *  ATSFontNotificationSubscribe()
 *  
 *  Summary:
 *    Ask the ATS System to notify caller when certain events have
 *    occurred.  Note that your application must have a CFRunLoop in
 *    order to receive notifications. Any Appkit or Carbon event loop
 *    based application will have one by default.
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Parameters:
 *    
 *    callback:
 *      Function that will be called by the ATS system whenever an
 *      event of interest takes place.
 *    
 *    options:
 *      Set the wanted ATSFontNotificationOptions to modify the default
 *      behavior of ATS Notifications.
 *    
 *    iRefcon:
 *      User data/state which will be passed to the callback funtion
 *    
 *    oNotificationRef:
 *      You may use this reference to un-subscribe to this notification.
 *  
 *  Result:
 *    noErr Subscribed successfully paramErr NULL callback was passed.
 *    memFullErr Could not allocate enough memory for internal data
 *    structures.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontNotificationSubscribe(
  ATSNotificationCallback   callback,
  ATSFontNotifyOption       options,
  void *                    iRefcon,                /* can be NULL */
  ATSFontNotificationRef *  oNotificationRef)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*
 *  ATSFontNotificationUnsubscribe()
 *  
 *  Summary:
 *    Release subscription and stop receiving notifications for a given
 *    reference.
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Parameters:
 *    
 *    notificationRef:
 *      Notification reference for which you want to stop receiving
 *      notifications. Note, if more than one notification has been
 *      requested of ATS, you will still receive notifications on those
 *      requests.
 *  
 *  Result:
 *    noErr Unsubscribed successfully paramErr NULL/invalid
 *    notificationRef passed
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontNotificationUnsubscribe(ATSFontNotificationRef notificationRef) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/* ----------------------------------------------------------------------------------------- */
/* Font query message hooks                                                                  */
/* ----------------------------------------------------------------------------------------- */

/*
 *  ATSFontQuerySourceContext
 *  
 *  Summary:
 *    A parameter block for client information to be retained by ATS
 *    and passed back to an ATSFontQueryCallback function.
 */
struct ATSFontQuerySourceContext {

  /*
   * A 32-bit unsigned integer that indicates the version of this
   * structure. This should be set to 0.
   */
  UInt32              version;

  /*
   * A pointer-sized client datum that should be passed back to an
   * ATSFontQueryCallback function.
   */
  void *              refCon;

  /*
   * The callback used to add a retain to the refCon.
   */
  CFAllocatorRetainCallBack  retain;

  /*
   * The callback used to remove a retain to the refCon.
   */
  CFAllocatorReleaseCallBack  release;
};
typedef struct ATSFontQuerySourceContext ATSFontQuerySourceContext;

/*
 *  ATSFontQueryMessageID
 *  
 *  Discussion:
 *    Constants for ATS font query message types.
 */
enum ATSFontQueryMessageID {

  /*
   * The message ID for a font request query. The data for a message
   * with this ID is a flattened CFDictionaryRef with keys and values
   * as decribed below. A query dictionary may have any or all of these
   * entries.
   */
  kATSQueryActivateFontMessage  = 'atsa'
};
typedef enum ATSFontQueryMessageID ATSFontQueryMessageID;


/*
 *  ATSFontQueryCallback
 *  
 *  Summary:
 *    Callback for receiving font-related queries from ATS.
 *  
 *  Parameters:
 *    
 *    msgid:
 *      An ATSFontQueryMessageID that identifies the message type.
 *    
 *    data:
 *      A CFPropertyListRef that represents the query. The content is
 *      message type-specific.
 *    
 *    refCon:
 *      A pointer-sized client datum that was optionally provided to
 *      ATSCreateFontQueryRunLoopSource.
 *  
 *  Result:
 *    A CFPropertyListRef that represents the message type-specific
 *    response to the query. May be NULL.
 */
typedef CALLBACK_API_C( CFPropertyListRef , ATSFontQueryCallback )(ATSFontQueryMessageID msgid, CFPropertyListRef data, void *refCon);
/*
 *  ATSCreateFontQueryRunLoopSource()
 *  
 *  Summary:
 *    Creates a CFRunLoopSourceRef that will be used to convey font
 *    queries from ATS.
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jaguar
 *  
 *  Parameters:
 *    
 *    queryOrder:
 *      A CFIndex that specifies the priority of this query receiver
 *      relative to others. When ATS makes a font query, it will send
 *      the query to each receiver in priority order, from highest to
 *      lowest. "Normal" priority is 0.
 *    
 *    sourceOrder:
 *      The order of the created run loop source.
 *    
 *    callout:
 *      A function pointer of type ATSFontQueryCallback that will be
 *      called to process a font query.
 *    
 *    context:
 *      An ATSFontQuerySourceContext parameter block that provides a
 *      pointer-sized client datum which will be retained by ATS and
 *      passed to the callout function. May be NULL.
 *  
 *  Result:
 *    A CFRunLoopSourceRef. To stop receiving queries, invalidate this
 *    run loop source.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFRunLoopSourceRef 
ATSCreateFontQueryRunLoopSource(
  CFIndex                            queryOrder,
  CFIndex                            sourceOrder,
  ATSFontQueryCallback               callout,
  const ATSFontQuerySourceContext *  context)           /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* ----------------------------------------------------------------------------------------- */
/* Font request query message content                                                        */
/* ----------------------------------------------------------------------------------------- */
/* Keys in a font request query dictionary. */
/* These keys appear in the dictionary for a kATSQueryActivateFontMessage query. */

/*
 *  kATSQueryClientPID
 *  
 *  Discussion:
 *    The process ID of the application making the query. The
 *    corresponding value is a CFNumberRef that contains a pid_t.
 */
#define kATSQueryClientPID              CFSTR("ATS client pid")

/*
 *  kATSQueryQDFamilyName
 *  
 *  Discussion:
 *    The Quickdraw-style family name of the font being requested, e.g.
 *    the name passed to GetFNum. The corresponding value is a
 *    CFStringRef.
 */
#define kATSQueryQDFamilyName           CFSTR("font family name")

/*
 *  kATSQueryFontName
 *  
 *  Discussion:
 *    The name of the font being requested. The corresponding value is
 *    a CFStringRef suitable as an argument to ATSFontFindFromName().
 *    This should match a candidate font's unique or full name.
 */
#define kATSQueryFontName               CFSTR("font name")

/*
 *  kATSQueryFontPostScriptName
 *  
 *  Discussion:
 *    The PostScript name of the font being requested. The
 *    corresponding value is a CFStringRef suitable as an argument to
 *    ATSFontFindFromPostScriptName(). This should match either the
 *    PostScript name derived from the font's FOND resource or its sfnt
 *    name table, with preference given to the FOND PostScript name.
 */
#define kATSQueryFontPostScriptName     CFSTR("font PS name")

/*
 *  kATSQueryFontNameTableEntries
 *  
 *  Discussion:
 *    A descriptor for sfnt name table entries that the requested font
 *    must have. The corresponding value is a CFArrayRef of
 *    CFDictionaryRefs that describe name table entries. A font must
 *    have all of the specified entries to be considered a match.
 */
#define kATSQueryFontNameTableEntries   CFSTR("font name table entries")
/* Keys in a font raw name descriptor dictionary. */

/*
 *  kATSFontNameTableCode
 *  
 *  Discussion:
 *    The font name's name code. The corresponding value is a
 *    CFNumberRef. If missing, assume kFontNoNameCode.
 */
#define kATSFontNameTableCode           CFSTR("font name code")

/*
 *  kATSFontNameTablePlatform
 *  
 *  Discussion:
 *    The font name's platform code. The corresponding value is a
 *    CFNumberRef. If missing, assume kFontNoPlatformCode.
 */
#define kATSFontNameTablePlatform       CFSTR("font platform code")

/*
 *  kATSFontNameTableScript
 *  
 *  Discussion:
 *    The font name's script code. The corresponding value is a
 *    CFNumberRef. If missing, assume kFontNoScriptCode.
 */
#define kATSFontNameTableScript         CFSTR("font script code")

/*
 *  kATSFontNameTableLanguage
 *  
 *  Discussion:
 *    The font name's language code. The corresponding value is a
 *    CFNumberRef. If missing, assume kFontNoLanguageCode.
 */
#define kATSFontNameTableLanguage       CFSTR("font language code")

/*
 *  kATSFontNameTableBytes
 *  
 *  Discussion:
 *    The raw bytes of the font name. The corresponding value is a
 *    CFDataRef that contains the raw name bytes.
 */
#define kATSFontNameTableBytes          CFSTR("font name table bytes")
/* ----------------------------------------------------------------------------------------- */
/* Auto activation settings                                                                  */
/* ----------------------------------------------------------------------------------------- */

/*
 *  ATSAutoActivationSetting
 *  
 *  Summary:
 *    Values for auto activation settings.
 */
enum {

  /*
   * Resets the setting the the default state. For application settings
   * this clears the setting. For the global setting it will revert to
   * the initial system setting, kATSFontAutoActivationEnabled.
   */
  kATSFontAutoActivationDefault = 0,
  kATSFontAutoActivationDisabled = 1,
  kATSFontAutoActivationEnabled = 2,

  /*
   * Asks the user before auto-activating fonts requested by the
   * application.
   */
  kATSFontAutoActivationAsk     = 4
};


typedef UInt32                          ATSFontAutoActivationSetting;
/*
 *  ATSFontSetGlobalAutoActivationSetting()
 *  
 *  Summary:
 *    Sets the user's global auto-activation setting.
 *  
 *  Discussion:
 *    This function can be used to set the user's global
 *    auto-activation setting.
 *  
 *  Mac OS X threading:
 *    Thread safe since version Leopard
 *  
 *  Parameters:
 *    
 *    iSetting:
 *      One of the enumerated constants above specifying the setting
 *      for font auto-activation. Will return paramErr on invalid input.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontSetGlobalAutoActivationSetting(ATSFontAutoActivationSetting iSetting) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  ATSFontGetGlobalAutoActivationSetting()
 *  
 *  Summary:
 *    Gets the user's global auto-activation setting.
 *  
 *  Discussion:
 *    This function can be used to get the user's global
 *    auto-activation setting.
 *  
 *  Mac OS X threading:
 *    Thread safe since version Leopard
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ATSFontAutoActivationSetting 
ATSFontGetGlobalAutoActivationSetting(void)                   AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  ATSFontSetAutoActivationSettingForApplication()
 *  
 *  Summary:
 *    Sets the auto-activation setting for the specified application
 *    bundle.
 *  
 *  Discussion:
 *    This function can be used to set the auto-activation setting for
 *    the specified application. The per-application setting overrides
 *    the global setting.
 *  
 *  Mac OS X threading:
 *    Thread safe since version Leopard
 *  
 *  Parameters:
 *    
 *    iSetting:
 *      One of the enumerated constants above specifying the setting
 *      for font auto-activation. Specifying
 *      kATSFontAutoActivationDefault will clear the application
 *      specific setting and the global setting will be used.
 *    
 *    iApplicationFileURL:
 *      A valid file URL for an application. Passing NULL for this
 *      parameter indicates the current process.
 *  
 *  Result:
 *    An OSStatus code. Will return noErr on success, and paramErr on
 *    any invalid input. May return memFullErr if unable to allocate
 *    temporary structures.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontSetAutoActivationSettingForApplication(
  ATSFontAutoActivationSetting   iSetting,
  CFURLRef                       iApplicationFileURL)         AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  ATSFontGetAutoActivationSettingForApplication()
 *  
 *  Summary:
 *    Query the activation setting for the specified application.
 *  
 *  Discussion:
 *    This function can be used to query the auto-activation setting
 *    for the specified application. The setting is the app-specific
 *    setting if available, otherwise it is
 *    kATSFontAutoActivationDefault.
 *  
 *  Mac OS X threading:
 *    Thread safe since version Leopard
 *  
 *  Parameters:
 *    
 *    iApplicationFileURL:
 *      A valid file URL for an application. Passing NULL for this
 *      parameter indicates the current process.
 *  
 *  Result:
 *    Returns the setting that will be used for the specified
 *    application. If this returns kATSFontAutoActivationDefault the
 *    global setting will be used.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern ATSFontAutoActivationSetting 
ATSFontGetAutoActivationSettingForApplication(CFURLRef iApplicationFileURL) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;



#if PRAGMA_ENUM_ALWAYSINT
    #pragma enumsalwaysint reset
#endif

#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif /* __ATSFONT__ */

