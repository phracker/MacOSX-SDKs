/*
     File:       QD/Fonts.h
 
     Contains:   Public interface to the Font Manager.
 
     Version:    Quickdraw-96.21~1
 
     Copyright:  © 1985-2002 by Apple Computer, Inc., all rights reserved
 
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

#pragma options align=mac68k

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
  propFont                      = 36864L,
  prpFntH                       = 36865L,
  prpFntW                       = 36866L,
  prpFntHW                      = 36867L,
  fixedFont                     = 45056L,
  fxdFntH                       = 45057L,
  fxdFntW                       = 45058L,
  fxdFntHW                      = 45059L,
  fontWid                       = 44208L
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
/*
 *  InitFonts()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  GetFontName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetFontName(
  short    familyID,
  Str255   name)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetFNum()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetFNum(
  ConstStr255Param   name,
  short *            familyID)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RealFont()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
RealFont(
  short   fontNum,
  short   size)                                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetFontLock()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  FMSwapFont()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern FMOutPtr 
FMSwapFont(const FMInput * inRec)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetFScaleDisable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetFScaleDisable(Boolean fscaleDisable)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FontMetrics()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FontMetrics(FMetricRecPtr theMetrics)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetFractEnable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetFractEnable(Boolean fractEnable)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDefFontSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
GetDefFontSize(void)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  IsOutline()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
IsOutline(
  Point   numer,
  Point   denom)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetOutlinePreferred()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetOutlinePreferred(Boolean outlinePreferred)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetOutlinePreferred()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
GetOutlinePreferred(void)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  OutlineMetrics()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
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
  RectPtr       boundsArray)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetPreserveGlyph()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetPreserveGlyph(Boolean preserveGlyph)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPreserveGlyph()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
GetPreserveGlyph(void)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FlushFonts()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  getfnum()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  getfontname()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  GetSysFont()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
GetSysFont(void)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetAppFont()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
GetAppFont(void)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*--------------------------------------------------------------------------------------*/
/*  Extended font data functions (available only with Mac OS 8.5 or later)              */
/*--------------------------------------------------------------------------------------*/
/*
 *  SetAntiAliasedTextEnabled()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.6 and later
 */
extern OSStatus 
SetAntiAliasedTextEnabled(
  Boolean   iEnable,
  SInt16    iMinFontSize)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  IsAntiAliasedTextEnabled()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.6 and later
 */
extern Boolean 
IsAntiAliasedTextEnabled(SInt16 * oMinFontSize)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QDTextBounds()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.6 and later
 */
extern void 
QDTextBounds(
  short         byteCount,
  const void *  textAddr,
  Rect *        bounds)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FetchFontInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.6 and later
 */
extern OSErr 
FetchFontInfo(
  SInt16      fontID,
  SInt16      fontSize,
  SInt16      fontStyle,
  FontInfo *  info)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*--------------------------------------------------------------------------------------*/
/*  Font access and data management functions (available only with Mac OS 9.0 or later) */
/*--------------------------------------------------------------------------------------*/
/* Enumeration */
/*
 *  FMCreateFontFamilyIterator()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMCreateFontFamilyIterator(
  const FMFilter *        iFilter,          /* can be NULL */
  void *                  iRefCon,
  OptionBits              iOptions,
  FMFontFamilyIterator *  ioIterator)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FMDisposeFontFamilyIterator()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMDisposeFontFamilyIterator(FMFontFamilyIterator * ioIterator) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FMResetFontFamilyIterator()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMResetFontFamilyIterator(
  const FMFilter *        iFilter,          /* can be NULL */
  void *                  iRefCon,
  OptionBits              iOptions,
  FMFontFamilyIterator *  ioIterator)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FMGetNextFontFamily()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMGetNextFontFamily(
  FMFontFamilyIterator *  ioIterator,
  FMFontFamily *          oFontFamily)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FMCreateFontIterator()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMCreateFontIterator(
  const FMFilter *  iFilter,          /* can be NULL */
  void *            iRefCon,
  OptionBits        iOptions,
  FMFontIterator *  ioIterator)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FMDisposeFontIterator()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMDisposeFontIterator(FMFontIterator * ioIterator)            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FMResetFontIterator()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMResetFontIterator(
  const FMFilter *  iFilter,          /* can be NULL */
  void *            iRefCon,
  OptionBits        iOptions,
  FMFontIterator *  ioIterator)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FMGetNextFont()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMGetNextFont(
  FMFontIterator *  ioIterator,
  FMFont *          oFont)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Font families */
/*
 *  FMCreateFontFamilyInstanceIterator()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMCreateFontFamilyInstanceIterator(
  FMFontFamily                    iFontFamily,
  FMFontFamilyInstanceIterator *  ioIterator)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FMDisposeFontFamilyInstanceIterator()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMDisposeFontFamilyInstanceIterator(FMFontFamilyInstanceIterator * ioIterator) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FMResetFontFamilyInstanceIterator()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMResetFontFamilyInstanceIterator(
  FMFontFamily                    iFontFamily,
  FMFontFamilyInstanceIterator *  ioIterator)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FMGetNextFontFamilyInstance()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMGetNextFontFamilyInstance(
  FMFontFamilyInstanceIterator *  ioIterator,
  FMFont *                        oFont,
  FMFontStyle *                   oStyle,           /* can be NULL */
  FMFontSize *                    oSize)            /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FMGetFontFamilyFromName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern FMFontFamily 
FMGetFontFamilyFromName(ConstStr255Param iName)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FMGetFontFamilyName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMGetFontFamilyName(
  FMFontFamily   iFontFamily,
  Str255         oName)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FMGetFontFamilyTextEncoding()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMGetFontFamilyTextEncoding(
  FMFontFamily    iFontFamily,
  TextEncoding *  oTextEncoding)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FMGetFontFamilyGeneration()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMGetFontFamilyGeneration(
  FMFontFamily    iFontFamily,
  FMGeneration *  oGeneration)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Fonts */
/*
 *  FMGetFontFormat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMGetFontFormat(
  FMFont          iFont,
  FourCharCode *  oFormat)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FMGetFontTableDirectory()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMGetFontTableDirectory(
  FMFont       iFont,
  ByteCount    iLength,
  void *       iBuffer,
  ByteCount *  oActualLength)       /* can be NULL */         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FMGetFontTable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
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
  ByteCount *    oActualLength)       /* can be NULL */       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FMGetFontGeneration()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMGetFontGeneration(
  FMFont          iFont,
  FMGeneration *  oGeneration)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FMGetFontContainer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMGetFontContainer(
  FMFont    iFont,
  FSSpec *  oFontContainer)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Conversion */
/*
 *  FMGetFontFromFontFamilyInstance()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMGetFontFromFontFamilyInstance(
  FMFontFamily   iFontFamily,
  FMFontStyle    iStyle,
  FMFont *       oFont,
  FMFontStyle *  oIntrinsicStyle)       /* can be NULL */     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FMGetFontFamilyInstanceFromFont()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMGetFontFamilyInstanceFromFont(
  FMFont          iFont,
  FMFontFamily *  oFontFamily,
  FMFontStyle *   oStyle)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FMGetATSFontRefFromFont()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern ATSFontRef 
FMGetATSFontRefFromFont(FMFont iFont)                         AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  FMGetATSFontFamilyRefFromFontFamily()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern ATSFontFamilyRef 
FMGetATSFontFamilyRefFromFontFamily(FMFontFamily iFamily)     AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  FMGetFontFromATSFontRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern FMFont 
FMGetFontFromATSFontRef(ATSFontRef iFont)                     AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  FMGetFontFamilyFromATSFontFamilyRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern FMFontFamily 
FMGetFontFamilyFromATSFontFamilyRef(ATSFontFamilyRef iFamily) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/* Activation */
/*
 *  FMActivateFonts()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMActivateFonts(
  const FSSpec *    iFontContainer,
  const FMFilter *  iFilter,              /* can be NULL */
  void *            iRefCon,
  OptionBits        iOptions)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FMDeactivateFonts()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern OSStatus 
FMDeactivateFonts(
  const FSSpec *    iFontContainer,
  const FMFilter *  iFilter,              /* can be NULL */
  void *            iRefCon,
  OptionBits        iOptions)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FMGetGeneration()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontManager 9.0 and later
 */
extern FMGeneration 
FMGetGeneration(void)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Container Access */
/*
 *  FMGetFontContainerFromFontFamilyInstance()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
FMGetFontContainerFromFontFamilyInstance(
  FMFontFamily   iFontFamily,
  FMFontStyle    iStyle,
  FMFontSize     iFontSize,
  FSSpec *       oFontContainer)                              AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  FMGetFontFamilyResource()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
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
  ByteCount *    oSize)             /* can be NULL */         AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;



typedef FMFontFamily                    FontFamilyID;
typedef FMFontSize                      FontPointSize;
/*--------------------------------------------------------------------------------------*/
/* Deprecated constant and type definitions                                             */
/*--------------------------------------------------------------------------------------*/
/* The font identifier constants are deprecated; use GetFNum or FMGetFontFamilyFromName
   to find a font family from a standard QuickDraw name.
*/
enum {
  kFMUseGlobalScopeOption       = 0x00000001
};

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

/* The following data structures referenced by the low memory global variables of the
   Font Manager are deprecated on Mac OS X and CarbonLib 1.1. The low memory global
   variables are not shared between processes and may result in inconsistencies
   compared to previous releases of the system software. Changes made to the
   information contained in the low memory global variables, including any
   indirectly referenced width tables, font family records, and font records, are
   not reflected in the global state of the Font Manager and may only be accessed
   through the font access and data management functions of the Font Manager or ATS.
*/
struct WidEntry {
  short               widStyle;               /*style entry applies to*/
};
typedef struct WidEntry                 WidEntry;
struct WidTable {
  short               numWidths;              /*number of entries - 1*/
};
typedef struct WidTable                 WidTable;
struct AsscEntry {
  short               fontSize;
  short               fontStyle;
  short               fontID;                 /*font resource ID*/
};
typedef struct AsscEntry                AsscEntry;
struct FontAssoc {
  short               numAssoc;               /*number of entries - 1*/
};
typedef struct FontAssoc                FontAssoc;
struct StyleTable {
  short               fontClass;
  long                offset;
  long                reserved;
  char                indexes[48];
};
typedef struct StyleTable               StyleTable;
struct NameTable {
  short               stringCount;
  Str255              baseFontName;
};
typedef struct NameTable                NameTable;
struct KernPair {
  char                kernFirst;              /*1st character of kerned pair*/
  char                kernSecond;             /*2nd character of kerned pair*/
  short               kernWidth;              /*kerning in 1pt fixed format*/
};
typedef struct KernPair                 KernPair;
struct KernEntry {
  short               kernStyle;              /*style the entry applies to*/
  short               kernLength;             /*length of this entry*/
};
typedef struct KernEntry                KernEntry;
struct KernTable {
  short               numKerns;               /*number of kerning entries*/
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
  short               ffFlags;                /*flags for family*/
  short               ffFamID;                /*family ID number*/
  short               ffFirstChar;            /*ASCII code of 1st character*/
  short               ffLastChar;             /*ASCII code of last character*/
  short               ffAscent;               /*maximum ascent for 1pt font*/
  short               ffDescent;              /*maximum descent for 1pt font*/
  short               ffLeading;              /*maximum leading for 1pt font*/
  short               ffWidMax;               /*maximum widMax for 1pt font*/
  long                ffWTabOff;              /*offset to width table*/
  long                ffKernOff;              /*offset to kerning table*/
  long                ffStylOff;              /*offset to style mapping table*/
  short               ffProperty[9];          /*style property info*/
  short               ffIntl[2];              /*for international use*/
  short               ffVersion;              /*version number*/
};
typedef struct FamRec                   FamRec;
struct FontRec {
  short               fontType;               /*font type*/
  short               firstChar;              /*ASCII code of first character*/
  short               lastChar;               /*ASCII code of last character*/
  short               widMax;                 /*maximum character width*/
  short               kernMax;                /*negative of maximum character kern*/
  short               nDescent;               /*negative of descent*/
  short               fRectWidth;             /*width of font rectangle*/
  short               fRectHeight;            /*height of font rectangle*/
  unsigned short      owTLoc;                 /*offset to offset/width table*/
  short               ascent;                 /*ascent*/
  short               descent;                /*descent*/
  short               leading;                /*leading*/
  short               rowWords;               /*row width of bit image / 2 */
};
typedef struct FontRec                  FontRec;
typedef FontRec *                       FontRecPtr;
typedef FontRecPtr *                    FontRecHdl;
/*--------------------------------------------------------------------------------------*/
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

/*--------------------------------------------------------------------------------------*/

#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __FONTS__ */

