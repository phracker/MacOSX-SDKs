/*
     File:       QD/QDOffscreen.h
 
     Contains:   Quickdraw Offscreen GWorld Interfaces.
 
     Version:    Quickdraw-150~1
 
     Copyright:  © 1985-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __QDOFFSCREEN__
#define __QDOFFSCREEN__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
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

/*
    NOTE:  With the exception of noNewDeviceBit and nativeEndianPixMapBit,
           he following definitions for the GWorldFlags parameter in NewGWorld
           are all obsolete on Mac OS X, and ignored.
*/
enum {
  pixPurgeBit                   = 0,
  noNewDeviceBit                = 1,
  useTempMemBit                 = 2,
  keepLocalBit                  = 3,
  useDistantHdwrMemBit          = 4,
  useLocalHdwrMemBit            = 5,
  pixelsPurgeableBit            = 6,
  pixelsLockedBit               = 7,
  nativeEndianPixMapBit         = 8,
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
  kNativeEndianPixMap           = 1L << nativeEndianPixMapBit,
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
  GWorldFlags   flags)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long            rowBytes)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LockPixels()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
LockPixels(PixMapHandle pm)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  UnlockPixels()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
UnlockPixels(PixMapHandle pm)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  GWorldFlags   flags)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DisposeGWorld()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DisposeGWorld(GWorldPtr offscreenGWorld)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  GDHandle *  gdh)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  GDHandle   gdh)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CTabChanged()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
CTabChanged(CTabHandle ctab)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PixPatChanged()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PixPatChanged(PixPatHandle ppat)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PortChanged()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PortChanged(GrafPtr port)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GDeviceChanged()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GDeviceChanged(GDHandle gdh)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  AllowPurgePixels()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
AllowPurgePixels(PixMapHandle pm)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NoPurgePixels()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
NoPurgePixels(PixMapHandle pm)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPixelsState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern GWorldFlags 
GetPixelsState(PixMapHandle pm)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  GWorldFlags    state)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPixBaseAddr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Ptr 
GetPixBaseAddr(PixMapHandle pm)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPixRowBytes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern long 
GetPixRowBytes(PixMapHandle pm)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  PixMapHandle *  offscreenPixMap)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DisposeScreenBuffer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DisposeScreenBuffer(PixMapHandle offscreenPixMap)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetGWorldDevice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern GDHandle 
GetGWorldDevice(GWorldPtr offscreenGWorld)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QDDone()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
QDDone(GrafPtr port)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  OffscreenVersion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
OffscreenVersion(void)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  PixMapHandle *  offscreenPixMap)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PixMap32Bit()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
PixMap32Bit(PixMapHandle pmHandle)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetGWorldPixMap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern PixMapHandle 
GetGWorldPixMap(GWorldPtr offscreenGWorld)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



#ifdef __cplusplus
}
#endif

#endif /* __QDOFFSCREEN__ */

