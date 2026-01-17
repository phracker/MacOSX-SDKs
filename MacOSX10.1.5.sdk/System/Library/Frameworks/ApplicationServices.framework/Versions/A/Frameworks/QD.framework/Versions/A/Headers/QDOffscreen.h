/*
     File:       QD/QDOffscreen.h
 
     Contains:   Quickdraw Offscreen GWorld Interfaces.
 
     Version:    Quickdraw-64.6.15~3
 
     Copyright:  © 1985-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __QDOFFSCREEN__
#define __QDOFFSCREEN__

#ifndef __MACERRORS__
#include <CarbonCore/MacErrors.h>
#endif

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
  pixPurgeBit                   = 0,
  noNewDeviceBit                = 1,
  useTempMemBit                 = 2,
  keepLocalBit                  = 3,
  useDistantHdwrMemBit          = 4,
  useLocalHdwrMemBit            = 5,
  pixelsPurgeableBit            = 6,
  pixelsLockedBit               = 7,
  mapPixBit                     = 16,
  newDepthBit                   = 17,
  alignPixBit                   = 18,
  newRowBytesBit                = 19,
  reallocPixBit                 = 20,
  clipPixBit                    = 28,
  stretchPixBit                 = 29,
  ditherPixBit                  = 30,
  gwFlagErrBit                  = 31
};

enum {
  pixPurge                      = 1L << pixPurgeBit,
  noNewDevice                   = 1L << noNewDeviceBit,
  useTempMem                    = 1L << useTempMemBit,
  keepLocal                     = 1L << keepLocalBit,
  useDistantHdwrMem             = 1L << useDistantHdwrMemBit,
  useLocalHdwrMem               = 1L << useLocalHdwrMemBit,
  pixelsPurgeable               = 1L << pixelsPurgeableBit,
  pixelsLocked                  = 1L << pixelsLockedBit,
  kAllocDirectDrawSurface       = 1L << 14,
  mapPix                        = 1L << mapPixBit,
  newDepth                      = 1L << newDepthBit,
  alignPix                      = 1L << alignPixBit,
  newRowBytes                   = 1L << newRowBytesBit,
  reallocPix                    = 1L << reallocPixBit,
  clipPix                       = 1L << clipPixBit,
  stretchPix                    = 1L << stretchPixBit,
  ditherPix                     = 1L << ditherPixBit,
  gwFlagErr                     = 1L << gwFlagErrBit
};

typedef unsigned long                   GWorldFlags;
/* Type definition of a GWorldPtr */
typedef CGrafPtr                        GWorldPtr;
/*
 *  NewGWorld()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern QDErr 
NewGWorld(
  GWorldPtr *   offscreenGWorld,
  short         PixelDepth,
  const Rect *  boundsRect,
  CTabHandle    cTable,                /* can be NULL */
  GDHandle      aGDevice,              /* can be NULL */
  GWorldFlags   flags);


/* GDevice attribute bits for Carbon and QuickTime 3.0*/
enum {
  deviceIsIndirect              = (1L << 0),
  deviceNeedsLock               = (1L << 1),
  deviceIsStatic                = (1L << 2),
  deviceIsExternalBuffer        = (1L << 3),
  deviceIsDDSurface             = (1L << 4),
  deviceIsDCISurface            = (1L << 5),
  deviceIsGDISurface            = (1L << 6),
  deviceIsAScreen               = (1L << 7),
  deviceIsOverlaySurface        = (1L << 8)
};

#if TARGET_OS_WIN32
/*
 *  GetGDeviceSurface()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  GetGDeviceAttributes()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/* to allocate non-mac-rgb GWorlds use QTNewGWorld (ImageCompression.h) */
/*
 *  NewGWorldFromHBITMAP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


#endif  /* TARGET_OS_WIN32 */

/*
 *  NewGWorldFromPtr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern QDErr 
NewGWorldFromPtr(
  GWorldPtr *     offscreenGWorld,
  unsigned long   PixelFormat,
  const Rect *    boundsRect,
  CTabHandle      cTable,                /* can be NULL */
  GDHandle        aGDevice,              /* can be NULL */
  GWorldFlags     flags,
  Ptr             newBuffer,
  long            rowBytes);


/*
 *  LockPixels()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
LockPixels(PixMapHandle pm);


/*
 *  UnlockPixels()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
UnlockPixels(PixMapHandle pm);


/*
 *  UpdateGWorld()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern GWorldFlags 
UpdateGWorld(
  GWorldPtr *   offscreenGWorld,
  short         pixelDepth,
  const Rect *  boundsRect,
  CTabHandle    cTable,
  GDHandle      aGDevice,              /* can be NULL */
  GWorldFlags   flags);


/*
 *  DisposeGWorld()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DisposeGWorld(GWorldPtr offscreenGWorld);


/*
 *  GetGWorld()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetGWorld(
  CGrafPtr *  port,
  GDHandle *  gdh);


/*
 *  SetGWorld()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetGWorld(
  CGrafPtr   port,
  GDHandle   gdh);


/*
 *  CTabChanged()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
CTabChanged(CTabHandle ctab);


/*
 *  PixPatChanged()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PixPatChanged(PixPatHandle ppat);


/*
 *  PortChanged()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PortChanged(GrafPtr port);


/*
 *  GDeviceChanged()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GDeviceChanged(GDHandle gdh);


/*
 *  AllowPurgePixels()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
AllowPurgePixels(PixMapHandle pm);


/*
 *  NoPurgePixels()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
NoPurgePixels(PixMapHandle pm);


/*
 *  GetPixelsState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern GWorldFlags 
GetPixelsState(PixMapHandle pm);


/*
 *  SetPixelsState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetPixelsState(
  PixMapHandle   pm,
  GWorldFlags    state);


/*
 *  GetPixBaseAddr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Ptr 
GetPixBaseAddr(PixMapHandle pm);


/*
 *  GetPixRowBytes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern long 
GetPixRowBytes(PixMapHandle pm);


/*
 *  NewScreenBuffer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern QDErr 
NewScreenBuffer(
  const Rect *    globalRect,
  Boolean         purgeable,
  GDHandle *      gdh,
  PixMapHandle *  offscreenPixMap);


/*
 *  DisposeScreenBuffer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DisposeScreenBuffer(PixMapHandle offscreenPixMap);


/*
 *  GetGWorldDevice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern GDHandle 
GetGWorldDevice(GWorldPtr offscreenGWorld);


/*
 *  QDDone()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
QDDone(GrafPtr port);


/*
 *  OffscreenVersion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
OffscreenVersion(void);


/*
 *  NewTempScreenBuffer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern QDErr 
NewTempScreenBuffer(
  const Rect *    globalRect,
  Boolean         purgeable,
  GDHandle *      gdh,
  PixMapHandle *  offscreenPixMap);


/*
 *  PixMap32Bit()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
PixMap32Bit(PixMapHandle pmHandle);


/*
 *  GetGWorldPixMap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern PixMapHandle 
GetGWorldPixMap(GWorldPtr offscreenGWorld);



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

#endif /* __QDOFFSCREEN__ */

