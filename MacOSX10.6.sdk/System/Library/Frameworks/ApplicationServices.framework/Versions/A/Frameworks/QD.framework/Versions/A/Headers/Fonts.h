/*
     File:       QD/Fonts.h
 
     Contains:   Public interface to the Font Manager.
 
     Version:    Quickdraw-264.3~1
 
     Copyright:  © 1985-2008 by Apple Inc. all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __FONTS__
#define __FONTS__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __ATSTYPES__
#include <ATS/ATSTypes.h>
#endif

#ifndef __QUICKDRAW__
#include <QD/Quickdraw.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 2)

#if !__LP64__
/*
 *  FMGetATSFontRefFromFont()
 *  
 *  Summary:
 *    Obtains the ATS font reference associated with a QuickDraw font
 *    reference.
 *  
 *  Parameters:
 *    
 *    iFont:
 *      A QuickDraw font reference.
 *    
 *    Result:
 *      The ATS font reference associated with the specified QuickDraw
 *      font reference.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework [32-bit only]
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern ATSFontRef 
FMGetATSFontRefFromFont(FMFont iFont)                         AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  FMGetFontFromATSFontRef()
 *  
 *  Summary:
 *    Obtains the QuickDraw font reference associated with an ATS font
 *    reference.
 *  
 *  Parameters:
 *    
 *    iFont:
 *      An ATS font reference.
 *    
 *    Result:
 *      The QuickDraw font reference associated with the specified ATS
 *      font reference.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework [32-bit only]
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern FMFont 
FMGetFontFromATSFontRef(ATSFontRef iFont)                     AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  FMFontGetCGFontRefFromFontFamilyInstance()
 *  
 *  Summary:
 *    Obtains the Quartz font reference associated with a typeface from
 *    a QuickDraw font family reference.
 *  
 *  Parameters:
 *    
 *    iFontFamily:
 *      A QuickDraw font family reference.
 *    
 *    iStyle:
 *      A QuickDraw font style.
 *    
 *    oFont:
 *      A pointer to a Quartz font reference. On output, points to the
 *      font reference for the specified font family and style. You are
 *      responsible for allocating the memory for the font reference.
 *    
 *    oStyle:
 *      On output, a pointer to an intrinsic font style. If a font
 *      reference isn’t found that matches the font family reference
 *      and font style you specify, the function returns the QuickDraw
 *      style that matches most closely.
 *    
 *    Result:
 *      A result code. If a font reference and intrinsic style are not
 *      found, the function returns a value of kFMInvalidFontErr.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework [32-bit only]
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
FMFontGetCGFontRefFromFontFamilyInstance(
  FMFontFamily   iFontFamily,
  FMFontStyle    iStyle,
  CGFontRef *    oFont,
  FMFontStyle *  oStyle)                                      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  The remaining functions in this file have all been deprecated on Mac OS X 10.4. There are other
 *  solutions that are recommended that provide better compatibility with the rest of the operating
 *  system.
 *  
 *  Instead of using the QuickDraw functions, you should consider the following:
 *
 *  1.  For drawing and measuring text, you can use the Appearance Manager API in HITheme.h or the
 *      ATSUI API in ATSUnicode.h to render text directly through a Quartz graphics context. Alternatively
 *      use CoreText on Mac OS X 10.5 or later.
 *
 *  2.  For accessing information on fonts tracked by the operating system, please refer to the
 *      functions described in ATSFont.h. Alternatively use CoreText on Mac OS X 10.5 or later.
 *  
 *  3.  For accessing and modifying information on fonts in a Quartz graphics context, please refer
 *      to the functions described in CoreGraphics.h.
 */
#endif  /* !__LP64__ */

enum {
  systemFont                    = 0,
  applFont                      = 1
};

enum {
  kFMDefaultOptions             = kNilOptions
};

/* Activation contexts */
enum {
  kFMDefaultActivationContext   = kFMDefaultOptions,
  kFMGlobalActivationContext    = 0x00000001,
  kFMLocalActivationContext     = kFMDefaultActivationContext
};

/* Iteration scopes */
enum {
  kFMDefaultIterationScope      = kFMDefaultOptions,
  kFMGlobalIterationScope       = 0x00000001,
  kFMLocalIterationScope        = kFMDefaultIterationScope
};

/* kPlatformDefaultGuiFontID is used in QuickTime 3.0. */
enum {
  kPlatformDefaultGuiFontID     = applFont
};

enum {
  commandMark                   = 17,
  checkMark                     = 18,
  diamondMark                   = 19,
  appleMark                     = 20
};

enum {
  propFont                      = 36864,
  prpFntH                       = 36865,
  prpFntW                       = 36866,
  prpFntHW                      = 36867,
  fixedFont                     = 45056,
  fxdFntH                       = 45057,
  fxdFntW                       = 45058,
  fxdFntHW                      = 45059,
  fontWid                       = 44208
};

struct FMInput {
  short               family;
  short               size;
  Style               face;
  Boolean             needBits;
  short               device;
  Point               numer;
  Point               denom;
};
typedef struct FMInput                  FMInput;
struct FMOutput {
  short               errNum;
  Handle              fontHandle;
  UInt8               boldPixels;
  UInt8               italicPixels;
  UInt8               ulOffset;
  UInt8               ulShadow;
  UInt8               ulThick;
  UInt8               shadowPixels;
  SInt8               extra;
  UInt8               ascent;
  UInt8               descent;
  UInt8               widMax;
  SInt8               leading;
  SInt8               curStyle;
  Point               numer;
  Point               denom;
};
typedef struct FMOutput                 FMOutput;
typedef FMOutput *                      FMOutputPtr;
typedef FMOutputPtr                     FMOutPtr;
struct FMetricRec {
  Fixed               ascent;                 /*base line to top*/
  Fixed               descent;                /*base line to bottom*/
  Fixed               leading;                /*leading between lines*/
  Fixed               widMax;                 /*maximum character width*/
  Handle              wTabHandle;             /*handle to font width table*/
};
typedef struct FMetricRec               FMetricRec;
typedef FMetricRec *                    FMetricRecPtr;
typedef FMetricRecPtr *                 FMetricRecHandle;
#if !__LP64__
/*
 *  InitFonts()
 *  
 *  Availability:
 *    Mac OS X:         not available [32-bit only]
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  GetFontName()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetFontName(
  short    familyID,
  Str255   name)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  GetFNum()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetFNum(
  ConstStr255Param   name,
  short *            familyID)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  RealFont()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
RealFont(
  short   fontNum,
  short   size)                                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  SetFontLock()
 *  
 *  Availability:
 *    Mac OS X:         not available [32-bit only]
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  FMSwapFont()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern FMOutPtr 
FMSwapFont(const FMInput * inRec)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  SetFScaleDisable()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetFScaleDisable(Boolean fscaleDisable)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FontMetrics()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FontMetrics(FMetricRecPtr theMetrics)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  SetFractEnable()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetFractEnable(Boolean fractEnable)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  GetDefFontSize()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
GetDefFontSize(void)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  IsOutline()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
IsOutline(
  Point   numer,
  Point   denom)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  SetOutlinePreferred()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetOutlinePreferred(Boolean outlinePreferred)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  GetOutlinePreferred()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
GetOutlinePreferred(void)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  OutlineMetrics()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
OutlineMetrics(
  short         byteCount,
  const void *  textPtr,
  Point         numer,
  Point         denom,
  short *       yMax,
  short *       yMin,
  FixedPtr      awArray,
  FixedPtr      lsbArray,
  RectPtr       boundsArray)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  SetPreserveGlyph()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetPreserveGlyph(Boolean preserveGlyph)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  GetPreserveGlyph()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
GetPreserveGlyph(void)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


#endif  /* !__LP64__ */

/*
 *  FlushFonts()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


#if !__LP64__
/*
 *  getfnum()
 *  
 *  Availability:
 *    Mac OS X:         not available [32-bit only]
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  getfontname()
 *  
 *  Availability:
 *    Mac OS X:         not available [32-bit only]
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


#endif  /* !__LP64__ */

#if !__LP64__
/*
 *  GetSysFont()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
GetSysFont(void)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  GetAppFont()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
GetAppFont(void)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/* Extended font data functions (available only with Mac OS 8.5 or later). */
/*
 *  SetAntiAliasedTextEnabled()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.6 and later
 */
extern OSStatus 
SetAntiAliasedTextEnabled(
  Boolean   iEnable,
  SInt16    iMinFontSize)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  IsAntiAliasedTextEnabled()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.6 and later
 */
extern Boolean 
IsAntiAliasedTextEnabled(SInt16 * oMinFontSize)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  QDTextBounds()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.6 and later
 */
extern void 
QDTextBounds(
  short         byteCount,
  const void *  textAddr,
  Rect *        bounds)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FetchFontInfo()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.6 and later
 */
extern OSErr 
FetchFontInfo(
  SInt16      fontID,
  SInt16      fontSize,
  SInt16      fontStyle,
  FontInfo *  info)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/* Font access and data management functions (available only with Mac OS 9.0 or later). */
/*
 *  FMCreateFontFamilyIterator()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated in Mac OS X 10.4 and not available in
 *    64-bit. Please see ATSFont.h for alternatives. Suggested
 *    replacement is ATSFontFamilyIteratorCreate.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMCreateFontFamilyIterator(
  const FMFilter *        iFilter,          /* can be NULL */
  void *                  iRefCon,
  OptionBits              iOptions,
  FMFontFamilyIterator *  ioIterator)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FMDisposeFontFamilyIterator()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated in Mac OS X 10.4 and not available in
 *    64-bit. Please see ATSFont.h for alternatives. Suggested
 *    replacement is ATSFontFamilyIteratorRelease.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMDisposeFontFamilyIterator(FMFontFamilyIterator * ioIterator) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FMResetFontFamilyIterator()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated in Mac OS X 10.4 and not available in
 *    64-bit. Please see ATSFont.h for alternatives. Suggested
 *    replacement is ATSFontFamilyIteratorReset.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMResetFontFamilyIterator(
  const FMFilter *        iFilter,          /* can be NULL */
  void *                  iRefCon,
  OptionBits              iOptions,
  FMFontFamilyIterator *  ioIterator)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FMGetNextFontFamily()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated in Mac OS X 10.4 and not available in
 *    64-bit. Please see ATSFont.h for alternatives. Suggested
 *    replacement is ATSFontFamilyIteratorNext.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMGetNextFontFamily(
  FMFontFamilyIterator *  ioIterator,
  FMFontFamily *          oFontFamily)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FMCreateFontIterator()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated in Mac OS X 10.4 and not available in
 *    64-bit. Please see ATSFont.h for alternatives. Suggested
 *    replacement is ATSFontIteratorCreate.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMCreateFontIterator(
  const FMFilter *  iFilter,          /* can be NULL */
  void *            iRefCon,
  OptionBits        iOptions,
  FMFontIterator *  ioIterator)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FMDisposeFontIterator()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated in Mac OS X 10.4 and not available in
 *    64-bit. Please see ATSFont.h for alternatives. Suggested
 *    replacement is ATSFontIteratorRelease.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMDisposeFontIterator(FMFontIterator * ioIterator)            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FMResetFontIterator()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated in Mac OS X 10.4 and not available in
 *    64-bit. Please see ATSFont.h for alternatives. Suggested
 *    replacement is ATSFontIteratorReset.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMResetFontIterator(
  const FMFilter *  iFilter,          /* can be NULL */
  void *            iRefCon,
  OptionBits        iOptions,
  FMFontIterator *  ioIterator)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FMGetNextFont()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated in Mac OS X 10.4 and not available in
 *    64-bit. Please see ATSFont.h for alternatives. Suggested
 *    replacement is ATSFontIteratorNext.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMGetNextFont(
  FMFontIterator *  ioIterator,
  FMFont *          oFont)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FMCreateFontFamilyInstanceIterator()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated in Mac OS X 10.4 and not available in
 *    64-bit. Please see ATSFont.h for alternatives.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMCreateFontFamilyInstanceIterator(
  FMFontFamily                    iFontFamily,
  FMFontFamilyInstanceIterator *  ioIterator)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FMDisposeFontFamilyInstanceIterator()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated in Mac OS X 10.4 and not available in
 *    64-bit. Please see ATSFont.h for alternatives.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMDisposeFontFamilyInstanceIterator(FMFontFamilyInstanceIterator * ioIterator) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FMResetFontFamilyInstanceIterator()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated in Mac OS X 10.4 and not available in
 *    64-bit. Please see ATSFont.h for alternatives.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMResetFontFamilyInstanceIterator(
  FMFontFamily                    iFontFamily,
  FMFontFamilyInstanceIterator *  ioIterator)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FMGetNextFontFamilyInstance()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated in Mac OS X 10.4 and not available in
 *    64-bit. Please see ATSFont.h for alternatives.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMGetNextFontFamilyInstance(
  FMFontFamilyInstanceIterator *  ioIterator,
  FMFont *                        oFont,
  FMFontStyle *                   oStyle,           /* can be NULL */
  FMFontSize *                    oSize)            /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FMGetFontFamilyFromName()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated in Mac OS X 10.4 and not available in
 *    64-bit. Please see ATSFont.h for alternatives. Suggested
 *    replacement is ATSFontFamilyFindFromName.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern FMFontFamily 
FMGetFontFamilyFromName(ConstStr255Param iName)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FMGetFontFamilyName()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated in Mac OS X 10.4 and not available in
 *    64-bit. Please see ATSFont.h for alternatives. Suggested
 *    replacement is ATSFontFamilyGetName.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMGetFontFamilyName(
  FMFontFamily   iFontFamily,
  Str255         oName)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FMGetFontFamilyTextEncoding()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated in Mac OS X 10.4 and not available in
 *    64-bit. Please see ATSFont.h for alternatives. Suggested
 *    replacement is ATSFontFamilyGetEncoding.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMGetFontFamilyTextEncoding(
  FMFontFamily    iFontFamily,
  TextEncoding *  oTextEncoding)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FMGetFontFamilyGeneration()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated in Mac OS X 10.4 and not available in
 *    64-bit. Please see ATSFont.h for alternatives. Suggested
 *    replacement is ATSFontFamilyGetGeneration.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMGetFontFamilyGeneration(
  FMFontFamily    iFontFamily,
  FMGeneration *  oGeneration)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FMGetFontFormat()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated in Mac OS X 10.4 and not available in
 *    64-bit. Please see ATSFont.h for alternatives.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMGetFontFormat(
  FMFont          iFont,
  FourCharCode *  oFormat)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FMGetFontTableDirectory()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMGetFontTableDirectory(
  FMFont       iFont,
  ByteCount    iLength,
  void *       iBuffer,
  ByteCount *  oActualLength)       /* can be NULL */         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FMGetFontTable()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated in Mac OS X 10.4 and not available in
 *    64-bit. Please see ATSFont.h for alternatives. Suggested
 *    replacement is ATSFontGetTable or CTFontCopyTable from
 *    CoreText/CTFont.h.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMGetFontTable(
  FMFont         iFont,
  FourCharCode   iTag,
  ByteOffset     iOffset,
  ByteCount      iLength,
  void *         iBuffer,
  ByteCount *    oActualLength)       /* can be NULL */       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FMGetFontGeneration()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated in Mac OS X 10.4 and not available in
 *    64-bit. Please see ATSFont.h for alternatives. Suggested
 *    replacement is ATSFontGetGeneration.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMGetFontGeneration(
  FMFont          iFont,
  FMGeneration *  oGeneration)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FMGetFontContainer()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated in Mac OS X 10.4 and not available in
 *    64-bit. Please see ATSFont.h for alternatives. Suggested
 *    replacement is ATSFontGetContainer.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMGetFontContainer(
  FMFont    iFont,
  FSSpec *  oFontContainer)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FMGetFontFromFontFamilyInstance()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated in Mac OS X 10.4 and not available in
 *    64-bit. Please see ATSFont.h for alternatives. Suggested
 *    replacement is CTFontCreateFromQuickdrawInstance in
 *    CoreText/CTFont.h.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMGetFontFromFontFamilyInstance(
  FMFontFamily   iFontFamily,
  FMFontStyle    iStyle,
  FMFont *       oFont,
  FMFontStyle *  oIntrinsicStyle)       /* can be NULL */     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FMGetFontFamilyInstanceFromFont()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated in Mac OS X 10.4 and not available in
 *    64-bit. Please see ATSFont.h for alternatives.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMGetFontFamilyInstanceFromFont(
  FMFont          iFont,
  FMFontFamily *  oFontFamily,
  FMFontStyle *   oStyle)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FMGetATSFontFamilyRefFromFontFamily()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated in Mac OS X 10.4 and not available in
 *    64-bit. Please see ATSFont.h for alternatives.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern ATSFontFamilyRef 
FMGetATSFontFamilyRefFromFontFamily(FMFontFamily iFamily)     AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FMGetFontFamilyFromATSFontFamilyRef()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated in Mac OS X 10.4 and not available in
 *    64-bit. Please see ATSFont.h for alternatives.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern FMFontFamily 
FMGetFontFamilyFromATSFontFamilyRef(ATSFontFamilyRef iFamily) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FMActivateFonts()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated in Mac OS X 10.4 and not available in
 *    64-bit. Please see ATSFont.h for alternatives. Suggested
 *    replacement is ATSFontActivateFromFileReference.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMActivateFonts(
  const FSSpec *    iFontContainer,
  const FMFilter *  iFilter,              /* can be NULL */
  void *            iRefCon,
  OptionBits        iOptions)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FMDeactivateFonts()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated in Mac OS X 10.4 and not available in
 *    64-bit. Please see ATSFont.h for alternatives. Suggested
 *    replacement is ATSFontDeactivate.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMDeactivateFonts(
  const FSSpec *    iFontContainer,
  const FMFilter *  iFilter,              /* can be NULL */
  void *            iRefCon,
  OptionBits        iOptions)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/* Use ATSGetGeneration instead of FMGetGeneration */
/*
 *  FMGetGeneration()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated in Mac OS X 10.4 and not available in
 *    64-bit. Please see ATSFont.h for alternatives. Suggested
 *    replacement is ATSGetGeneration.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern FMGeneration 
FMGetGeneration(void)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  FMGetFontContainerFromFontFamilyInstance()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated in Mac OS X 10.4 and not available in
 *    64-bit. Please see ATSFont.h for alternatives. Suggested
 *    replacement is ATSFontGetContainer.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
FMGetFontContainerFromFontFamilyInstance(
  FMFontFamily   iFontFamily,
  FMFontStyle    iStyle,
  FMFontSize     iFontSize,
  FSSpec *       oFontContainer)                              AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FMGetFontFamilyResource()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated in Mac OS X 10.4 and not available in
 *    64-bit. Please see ATSFont.h for alternatives. Suggested
 *    replacement is ATSFontGetFontFamilyResource.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
FMGetFontFamilyResource(
  FMFontFamily   iFontFamily,
  FMFontStyle    iFontStyle,
  FMFontSize     iFontSize,
  ByteCount      iBufferSize,
  void *         ioBuffer,
  ByteCount *    oSize)             /* can be NULL */         AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


#endif  /* !__LP64__ */

typedef FMFontFamily                    FontFamilyID;
typedef FMFontSize                      FontPointSize;
enum {
  kFMUseGlobalScopeOption       = 0x00000001
};

/*
 *  The font identifier constants are deprecated; use ATSFontFamilyFindFromQuickDrawName in ATSFont.h
 *  to find a font family from a standard QuickDraw name.
 */
enum {
  kFontIDNewYork                = 2,
  kFontIDGeneva                 = 3,
  kFontIDMonaco                 = 4,
  kFontIDVenice                 = 5,
  kFontIDLondon                 = 6,
  kFontIDAthens                 = 7,
  kFontIDSanFrancisco           = 8,
  kFontIDToronto                = 9,
  kFontIDCairo                  = 11,
  kFontIDLosAngeles             = 12,
  kFontIDTimes                  = 20,
  kFontIDHelvetica              = 21,
  kFontIDCourier                = 22,
  kFontIDSymbol                 = 23,
  kFontIDMobile                 = 24
};

/*
 *  The following data structures referenced by the low memory global variables of QuickDraw are
 *  deprecated on Mac OS X and CarbonLib 1.1. The low memory global variables are not shared between
 *  processes and may result in inconsistencies compared to previous releases of the system software.
 *  Changes made to the information contained in the low memory global variables, including any
 *  indirectly referenced width tables, font family records, and font records, are not reflected in
 *  the global state for QuickDraw and should only be accessed through the font access and data
 *  management functions of ATS.
 */
struct WidEntry {
  SInt16              widStyle;               /*style entry applies to*/
};
typedef struct WidEntry                 WidEntry;
struct WidTable {
  SInt16              numWidths;              /*number of entries - 1*/
};
typedef struct WidTable                 WidTable;
struct AsscEntry {
  SInt16              fontSize;
  SInt16              fontStyle;
  SInt16              fontID;                 /*font resource ID*/
};
typedef struct AsscEntry                AsscEntry;
struct FontAssoc {
  SInt16              numAssoc;               /*number of entries - 1*/
};
typedef struct FontAssoc                FontAssoc;
struct StyleTable {
  SInt16              fontClass;
  SInt32              offset;
  SInt32              reserved;
  char                indexes[48];
};
typedef struct StyleTable               StyleTable;
struct NameTable {
  SInt16              stringCount;
  Str255              baseFontName;
};
typedef struct NameTable                NameTable;
struct KernPair {
  char                kernFirst;              /*1st character of kerned pair*/
  char                kernSecond;             /*2nd character of kerned pair*/
  SInt16              kernWidth;              /*kerning in 1pt fixed format*/
};
typedef struct KernPair                 KernPair;
struct KernEntry {
  SInt16              kernStyle;              /*style the entry applies to*/
  SInt16              kernLength;             /*length of this entry*/
};
typedef struct KernEntry                KernEntry;
struct KernTable {
  SInt16              numKerns;               /*number of kerning entries*/
};
typedef struct KernTable                KernTable;
struct WidthTable {
  Fixed               tabData[256];           /*character widths*/
  Handle              tabFont;                /*font record used to build table*/
  long                sExtra;                 /*space extra used for table*/
  long                style;                  /*extra due to style*/
  short               fID;                    /*font family ID*/
  short               fSize;                  /*font size request*/
  short               face;                   /*style (face) request*/
  short               device;                 /*device requested*/
  Point               inNumer;                /*scale factors requested*/
  Point               inDenom;                /*scale factors requested*/
  short               aFID;                   /*actual font family ID for table*/
  Handle              fHand;                  /*family record used to build up table*/
  Boolean             usedFam;                /*used fixed point family widths*/
  UInt8               aFace;                  /*actual face produced*/
  short               vOutput;                /*vertical scale output value*/
  short               hOutput;                /*horizontal scale output value*/
  short               vFactor;                /*vertical scale output value*/
  short               hFactor;                /*horizontal scale output value*/
  short               aSize;                  /*actual size of actual font used*/
  short               tabSize;                /*total size of table*/
};
typedef struct WidthTable               WidthTable;
typedef WidthTable *                    WidthTablePtr;
typedef WidthTablePtr *                 WidthTableHdl;
struct FamRec {
  SInt16              ffFlags;                /*flags for family*/
  SInt16              ffFamID;                /*family ID number*/
  SInt16              ffFirstChar;            /*ASCII code of 1st character*/
  SInt16              ffLastChar;             /*ASCII code of last character*/
  SInt16              ffAscent;               /*maximum ascent for 1pt font*/
  SInt16              ffDescent;              /*maximum descent for 1pt font*/
  SInt16              ffLeading;              /*maximum leading for 1pt font*/
  SInt16              ffWidMax;               /*maximum widMax for 1pt font*/
  SInt32              ffWTabOff;              /*offset to width table*/
  SInt32              ffKernOff;              /*offset to kerning table*/
  SInt32              ffStylOff;              /*offset to style mapping table*/
  SInt16              ffProperty[9];          /*style property info*/
  SInt16              ffIntl[2];              /*for international use*/
  SInt16              ffVersion;              /*version number*/
};
typedef struct FamRec                   FamRec;
struct FontRec {
  SInt16              fontType;               /*font type*/
  SInt16              firstChar;              /*ASCII code of first character*/
  SInt16              lastChar;               /*ASCII code of last character*/
  SInt16              widMax;                 /*maximum character width*/
  SInt16              kernMax;                /*negative of maximum character kern*/
  SInt16              nDescent;               /*negative of descent*/
  SInt16              fRectWidth;             /*width of font rectangle*/
  SInt16              fRectHeight;            /*height of font rectangle*/
  UInt16              owTLoc;                 /*offset to offset/width table*/
  SInt16              ascent;                 /*ascent*/
  SInt16              descent;                /*descent*/
  SInt16              leading;                /*leading*/
  SInt16              rowWords;               /*row width of bit image / 2 */
};
typedef struct FontRec                  FontRec;
typedef FontRec *                       FontRecPtr;
typedef FontRecPtr *                    FontRecHdl;
#if OLDROUTINENAMES
enum {
  newYork                       = kFontIDNewYork,
  geneva                        = kFontIDGeneva,
  monaco                        = kFontIDMonaco,
  venice                        = kFontIDVenice,
  london                        = kFontIDLondon,
  athens                        = kFontIDAthens,
  sanFran                       = kFontIDSanFrancisco,
  toronto                       = kFontIDToronto,
  cairo                         = kFontIDCairo,
  losAngeles                    = kFontIDLosAngeles,
  times                         = kFontIDTimes,
  helvetica                     = kFontIDHelvetica,
  courier                       = kFontIDCourier,
  symbol                        = kFontIDSymbol,
  mobile                        = kFontIDMobile
};

#endif  /* OLDROUTINENAMES */


#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif /* __FONTS__ */

