/*
     File:       QD/Palettes.h
 
     Contains:   Palette Manager Interfaces.
 
     Version:    Quickdraw-64.6.15~3
 
     Copyright:  © 1987-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __PALETTES__
#define __PALETTES__

#ifndef __QUICKDRAW__
#include <QD/Quickdraw.h>
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
  pmCourteous                   = 0,    /*Record use of color on each device touched.*/
  pmDithered                    = 0x0001,
  pmTolerant                    = 0x0002, /*render ciRGB if ciTolerance is exceeded by best match.*/
  pmAnimated                    = 0x0004, /*reserve an index on each device touched and render ciRGB.*/
  pmExplicit                    = 0x0008, /*no reserve, no render, no record; stuff index into port.*/
  pmWhite                       = 0x0010,
  pmBlack                       = 0x0020,
  pmInhibitG2                   = 0x0100,
  pmInhibitC2                   = 0x0200,
  pmInhibitG4                   = 0x0400,
  pmInhibitC4                   = 0x0800,
  pmInhibitG8                   = 0x1000,
  pmInhibitC8                   = 0x2000, /* NSetPalette Update Constants */
  pmNoUpdates                   = 0x8000, /*no updates*/
  pmBkUpdates                   = 0xA000, /*background updates only*/
  pmFgUpdates                   = 0xC000, /*foreground updates only*/
  pmAllUpdates                  = 0xE000 /*all updates*/
};

struct ColorInfo {
  RGBColor            ciRGB;                  /*true RGB values*/
  short               ciUsage;                /*color usage*/
  short               ciTolerance;            /*tolerance value*/
  short               ciDataFields[3];        /*private fields*/
};
typedef struct ColorInfo                ColorInfo;
typedef ColorInfo *                     ColorInfoPtr;
typedef ColorInfoPtr *                  ColorInfoHandle;
struct Palette {
  short               pmEntries;              /*entries in pmTable*/
  short               pmDataFields[7];        /*private fields*/
  ColorInfo           pmInfo[1];
};
typedef struct Palette                  Palette;
typedef Palette *                       PalettePtr;
typedef PalettePtr *                    PaletteHandle;
/*
 *  InitPalettes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
InitPalettes(void);


/*
 *  NewPalette()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern PaletteHandle 
NewPalette(
  short        entries,
  CTabHandle   srcColors,
  short        srcUsage,
  short        srcTolerance);


/*
 *  GetNewPalette()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern PaletteHandle 
GetNewPalette(short PaletteID);


/*
 *  DisposePalette()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DisposePalette(PaletteHandle srcPalette);


/*
 *  ActivatePalette()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ActivatePalette(WindowRef srcWindow);


/*
 *  SetPalette()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetPalette(
  WindowRef       dstWindow,
  PaletteHandle   srcPalette,
  Boolean         cUpdates);


/*
 *  NSetPalette()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
NSetPalette(
  WindowRef       dstWindow,
  PaletteHandle   srcPalette,
  short           nCUpdates);


/*
 *  GetPalette()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern PaletteHandle 
GetPalette(WindowRef srcWindow);


/*
 *  CopyPalette()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
CopyPalette(
  PaletteHandle   srcPalette,
  PaletteHandle   dstPalette,
  short           srcEntry,
  short           dstEntry,
  short           dstLength);


/*
 *  PmForeColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PmForeColor(short dstEntry);


/*
 *  PmBackColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PmBackColor(short dstEntry);


/*
 *  AnimateEntry()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
AnimateEntry(
  WindowRef         dstWindow,
  short             dstEntry,
  const RGBColor *  srcRGB);


/*
 *  [Mac]AnimatePalette()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacAnimatePalette AnimatePalette
#endif
extern void 
MacAnimatePalette(
  WindowRef    dstWindow,
  CTabHandle   srcCTab,
  short        srcIndex,
  short        dstEntry,
  short        dstLength);


/*
 *  GetEntryColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetEntryColor(
  PaletteHandle   srcPalette,
  short           srcEntry,
  RGBColor *      dstRGB);


/*
 *  SetEntryColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetEntryColor(
  PaletteHandle     dstPalette,
  short             dstEntry,
  const RGBColor *  srcRGB);


/*
 *  GetEntryUsage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetEntryUsage(
  PaletteHandle   srcPalette,
  short           srcEntry,
  short *         dstUsage,
  short *         dstTolerance);


/*
 *  SetEntryUsage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetEntryUsage(
  PaletteHandle   dstPalette,
  short           dstEntry,
  short           srcUsage,
  short           srcTolerance);


/*
 *  CTab2Palette()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
CTab2Palette(
  CTabHandle      srcCTab,
  PaletteHandle   dstPalette,
  short           srcUsage,
  short           srcTolerance);


/*
 *  Palette2CTab()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
Palette2CTab(
  PaletteHandle   srcPalette,
  CTabHandle      dstCTab);


/*
 *  Entry2Index()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
Entry2Index(short entry);


/*
 *  RestoreDeviceClut()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
RestoreDeviceClut(GDHandle gd);


/*
 *  [Mac]ResizePalette()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacResizePalette ResizePalette
#endif
extern void 
MacResizePalette(
  PaletteHandle   p,
  short           size);


/*
 *  SaveFore()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SaveFore(ColorSpec * c);


/*
 *  SaveBack()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SaveBack(ColorSpec * c);


/*
 *  RestoreFore()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
RestoreFore(const ColorSpec * c);


/*
 *  RestoreBack()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
RestoreBack(const ColorSpec * c);


/*
 *  SetDepth()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SetDepth(
  GDHandle   gd,
  short      depth,
  short      whichFlags,
  short      flags);


/*
 *  HasDepth()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
HasDepth(
  GDHandle   gd,
  short      depth,
  short      whichFlags,
  short      flags);


/*
 *  PMgrVersion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
PMgrVersion(void);


/*
 *  SetPaletteUpdates()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetPaletteUpdates(
  PaletteHandle   p,
  short           updates);


/*
 *  GetPaletteUpdates()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
GetPaletteUpdates(PaletteHandle p);


/*
 *  GetGray()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
GetGray(
  GDHandle          device,
  const RGBColor *  backGround,
  RGBColor *        foreGround);





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

#endif /* __PALETTES__ */

