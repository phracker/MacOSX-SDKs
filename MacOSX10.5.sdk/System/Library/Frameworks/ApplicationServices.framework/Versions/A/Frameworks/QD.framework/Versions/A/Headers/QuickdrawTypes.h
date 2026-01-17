/*
     File:       QD/QuickdrawTypes.h
 
     Contains:   Type definitions from the former Quickdraw.i
 
     Version:    Quickdraw-242~94
 
     Copyright:  © 2005-2006 by Apple Inc. all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __QUICKDRAWTYPES__
#define __QUICKDRAWTYPES__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif


#ifndef __COREGRAPHICS__
#include <CoreGraphics/CoreGraphics.h>
#endif

#ifndef __QUICKDRAWTEXT__
#include <QD/QuickdrawText.h>
#endif

#ifndef __CMTYPES__
#include <ColorSync/CMTypes.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 2)

enum {
  invalColReq                   = -1    /*invalid color table request*/
};

enum {
                                        /* transfer modes */
  srcCopy                       = 0,    /*the 16 transfer modes*/
  srcOr                         = 1,
  srcXor                        = 2,
  srcBic                        = 3,
  notSrcCopy                    = 4,
  notSrcOr                      = 5,
  notSrcXor                     = 6,
  notSrcBic                     = 7,
  patCopy                       = 8,
  patOr                         = 9,
  patXor                        = 10,
  patBic                        = 11,
  notPatCopy                    = 12,
  notPatOr                      = 13,
  notPatXor                     = 14,
  notPatBic                     = 15,   /* Special Text Transfer Mode */
  grayishTextOr                 = 49,
  hilitetransfermode            = 50,
  hilite                        = 50,   /* Arithmetic transfer modes */
  blend                         = 32,
  addPin                        = 33,
  addOver                       = 34,
  subPin                        = 35,
  addMax                        = 37,
  adMax                         = 37,
  subOver                       = 38,
  adMin                         = 39,
  ditherCopy                    = 64,   /* Transparent mode constant */
  transparent                   = 36
};

enum {
  italicBit                     = 1,
  ulineBit                      = 2,
  outlineBit                    = 3,
  shadowBit                     = 4,
  condenseBit                   = 5,
  extendBit                     = 6
};

enum {
                                        /* QuickDraw color separation constants */
  normalBit                     = 0,    /*normal screen mapping*/
  inverseBit                    = 1,    /*inverse screen mapping*/
  redBit                        = 4,    /*RGB additive mapping*/
  greenBit                      = 3,
  blueBit                       = 2,
  cyanBit                       = 8,    /*CMYBk subtractive mapping*/
  magentaBit                    = 7,
  yellowBit                     = 6,
  blackBit                      = 5
};

enum {
  blackColor                    = 33,   /* colors expressed in these mappings */
  whiteColor                    = 30,
  redColor                      = 205,
  greenColor                    = 341,
  blueColor                     = 409,
  cyanColor                     = 273,
  magentaColor                  = 137,
  yellowColor                   = 69
};

enum {
  picLParen                     = 0,    /* standard picture comments */
  picRParen                     = 1
};

/* gdType values */
enum {
  clutType                      = 0,    /* lookup table */
  fixedType                     = 1,    /* fixed table - now unused */
  directType                    = 2     /* direct values */
};

/* gdFlags bits. Bits 1..10 are legacy, and currently unused */
enum {
  gdDevType                     = 0,    /* 0 = monochrome 1 = color */
  interlacedDevice              = 2,
  hwMirroredDevice              = 4,
  roundedDevice                 = 5,
  hasAuxMenuBar                 = 6,
  burstDevice                   = 7,
  ext32Device                   = 8,
  ramInit                       = 10,
  mainScreen                    = 11,   /* 1 if main screen */
  allInit                       = 12,   /* 1 if all devices initialized */
  screenDevice                  = 13,   /* 1 if screen device */
  noDriver                      = 14,   /* 1 if no driver for this GDevice */
  screenActive                  = 15    /* 1 if in use*/
};

enum {
  hiliteBit                     = 7,    /* flag bit in LMGet/SetHiliteMode */
  pHiliteBit                    = 0     /* flag bit in LMGet/SetHiliteMode when used with BitClr */
};

/* miscellaneous constants */
enum {
  defQDColors                   = 127,  /* (legacy - now unused) */
  RGBDirect                     = 16,   /* 16 & 32 bits/pixel pixelType value */
  baseAddr32                    = 4     /* pmVersion value: pixmap base address is 32-bit address */
};

enum {
  sysPatListID                  = 0,
  iBeamCursor                   = 1,
  crossCursor                   = 2,
  plusCursor                    = 3,
  watchCursor                   = 4
};

enum {
  kQDGrafVerbFrame              = 0,
  kQDGrafVerbPaint              = 1,
  kQDGrafVerbErase              = 2,
  kQDGrafVerbInvert             = 3,
  kQDGrafVerbFill               = 4
};

#if OLDROUTINENAMES
enum {
  frame                         = kQDGrafVerbFrame,
  paint                         = kQDGrafVerbPaint,
  erase                         = kQDGrafVerbErase,
  invert                        = kQDGrafVerbInvert,
  fill                          = kQDGrafVerbFill
};

#endif  /* OLDROUTINENAMES */

typedef SInt8                           GrafVerb;
enum {
  chunky                        = 0,
  chunkyPlanar                  = 1,
  planar                        = 2
};

typedef SInt8                           PixelType;
typedef short                           Bits16[16];

/***************   IMPORTANT NOTE REGARDING Pattern  **************************************
   Patterns were originally defined as:
   
        C:          typedef unsigned char Pattern[8];
        Pascal:     Pattern = PACKED ARRAY [0..7] OF 0..255;
        
   The old array definition of Pattern would cause 68000 based CPU's to crash in certain circum-
   stances. The new struct definition is safe, but may require source code changes to compile.
    
*********************************************************************************************/
struct Pattern {
  UInt8               pat[8];
};
typedef struct Pattern                  Pattern;
/*
 ConstPatternParam is no longer needed.  It was first created when Pattern was an array.
 Now that Pattern is a struct, it is more straight forward to just add the "const" qualifier
 on the parameter type (e.g. "const Pattern * pat" instead of "ConstPatternParam pat").
*/
typedef const Pattern *                 ConstPatternParam;
typedef Pattern *                       PatPtr;
typedef PatPtr *                        PatHandle;
typedef SignedByte                      QDByte;
typedef QDByte *                        QDPtr;
typedef QDPtr *                         QDHandle;
typedef short                           QDErr;
enum {
  singleDevicesBit              = 0,
  dontMatchSeedsBit             = 1,
  allDevicesBit                 = 2
};

enum {
  singleDevices                 = 1 << singleDevicesBit,
  dontMatchSeeds                = 1 << dontMatchSeedsBit,
  allDevices                    = 1 << allDevicesBit
};

typedef unsigned long                   DeviceLoopFlags;
/*
    PrinterStatusOpcode.  For communication with downloading and printing services.
*/
typedef SInt32                          PrinterStatusOpcode;
enum {
  kPrinterFontStatus            = 0,
  kPrinterScalingStatus         = 1
};

struct PrinterFontStatus {
  SInt32              oResult;
  SInt16              iFondID;
  Style               iStyle;
};
typedef struct PrinterFontStatus        PrinterFontStatus;
struct PrinterScalingStatus {
  Point               oScalingFactors;
};
typedef struct PrinterScalingStatus     PrinterScalingStatus;
struct BitMap {
  Ptr                 baseAddr;
  short               rowBytes;
  Rect                bounds;
};
typedef struct BitMap                   BitMap;
typedef BitMap *                        BitMapPtr;
typedef BitMapPtr *                     BitMapHandle;
struct Cursor {
  Bits16              data;
  Bits16              mask;
  Point               hotSpot;
};
typedef struct Cursor                   Cursor;
typedef Cursor *                        CursPtr;
typedef CursPtr *                       CursHandle;
struct PenState {
  Point               pnLoc;
  Point               pnSize;
  short               pnMode;
  Pattern             pnPat;
};
typedef struct PenState                 PenState;
#if !OPAQUE_TOOLBOX_STRUCTS
struct MacRegion {
  unsigned short      rgnSize;                /* size in bytes; don't rely on it */
  Rect                rgnBBox;                /* enclosing rectangle; in Carbon use GetRegionBounds */
};
typedef struct MacRegion                MacRegion;
/*
   The type name "Region" has a name space collision on Win32.
   Use MacRegion to be cross-platfrom safe.
*/
typedef MacRegion                       Region;
typedef MacRegion *                     RgnPtr;
typedef RgnPtr *                        RgnHandle;
#else
typedef struct OpaqueRgnHandle*         RgnHandle;
#endif  /* !OPAQUE_TOOLBOX_STRUCTS */

struct Picture {
  short               picSize;
  Rect                picFrame;
};
typedef struct Picture                  Picture;
typedef Picture *                       PicPtr;
typedef PicPtr *                        PicHandle;
struct MacPolygon {
  short               polySize;
  Rect                polyBBox;
  Point               polyPoints[1];
};
typedef struct MacPolygon               MacPolygon;
/*
   The type name "Polygon" has a name space collision on Win32.
   Use MacPolygon to be cross-platfrom safe.
*/
typedef MacPolygon                      Polygon;
typedef MacPolygon *                    PolyPtr;
typedef PolyPtr *                       PolyHandle;
typedef CALLBACK_API( void , QDTextProcPtr )(short byteCount, const void *textBuf, Point numer, Point denom);
typedef CALLBACK_API( void , QDLineProcPtr )(Point newPt);
typedef CALLBACK_API( void , QDRectProcPtr )(GrafVerb verb, const Rect *r);
typedef CALLBACK_API( void , QDRRectProcPtr )(GrafVerb verb, const Rect *r, short ovalWidth, short ovalHeight);
typedef CALLBACK_API( void , QDOvalProcPtr )(GrafVerb verb, const Rect *r);
typedef CALLBACK_API( void , QDArcProcPtr )(GrafVerb verb, const Rect *r, short startAngle, short arcAngle);
typedef CALLBACK_API( void , QDPolyProcPtr )(GrafVerb verb, PolyHandle poly);
typedef CALLBACK_API( void , QDRgnProcPtr )(GrafVerb verb, RgnHandle rgn);
typedef CALLBACK_API( void , QDBitsProcPtr )(const BitMap *srcBits, const Rect *srcRect, const Rect *dstRect, short mode, RgnHandle maskRgn);
typedef CALLBACK_API( void , QDCommentProcPtr )(short kind, short dataSize, Handle dataHandle);
typedef CALLBACK_API( short , QDTxMeasProcPtr )(short byteCount, const void *textAddr, Point *numer, Point *denom, FontInfo *info);
typedef CALLBACK_API( void , QDGetPicProcPtr )(void *dataPtr, short byteCount);
typedef CALLBACK_API( void , QDPutPicProcPtr )(const void *dataPtr, short byteCount);
typedef CALLBACK_API( void , QDOpcodeProcPtr )(const Rect *fromRect, const Rect *toRect, UInt16 opcode, SInt16 version);
/* The following is unused on Mac OS X - ignore it! */
typedef CALLBACK_API_C( OSStatus , QDStdGlyphsProcPtr )(void *dataStream, ByteCount size);
typedef CALLBACK_API( void , QDJShieldCursorProcPtr )(short left, short top, short right, short bottom);
typedef STACK_UPP_TYPE(QDTextProcPtr)                           QDTextUPP;
typedef STACK_UPP_TYPE(QDLineProcPtr)                           QDLineUPP;
typedef STACK_UPP_TYPE(QDRectProcPtr)                           QDRectUPP;
typedef STACK_UPP_TYPE(QDRRectProcPtr)                          QDRRectUPP;
typedef STACK_UPP_TYPE(QDOvalProcPtr)                           QDOvalUPP;
typedef STACK_UPP_TYPE(QDArcProcPtr)                            QDArcUPP;
typedef STACK_UPP_TYPE(QDPolyProcPtr)                           QDPolyUPP;
typedef STACK_UPP_TYPE(QDRgnProcPtr)                            QDRgnUPP;
typedef STACK_UPP_TYPE(QDBitsProcPtr)                           QDBitsUPP;
typedef STACK_UPP_TYPE(QDCommentProcPtr)                        QDCommentUPP;
typedef STACK_UPP_TYPE(QDTxMeasProcPtr)                         QDTxMeasUPP;
typedef STACK_UPP_TYPE(QDGetPicProcPtr)                         QDGetPicUPP;
typedef STACK_UPP_TYPE(QDPutPicProcPtr)                         QDPutPicUPP;
typedef STACK_UPP_TYPE(QDOpcodeProcPtr)                         QDOpcodeUPP;
typedef STACK_UPP_TYPE(QDStdGlyphsProcPtr)                      QDStdGlyphsUPP;
typedef STACK_UPP_TYPE(QDJShieldCursorProcPtr)                  QDJShieldCursorUPP;
struct QDProcs {
  QDTextUPP           textProc;
  QDLineUPP           lineProc;
  QDRectUPP           rectProc;
  QDRRectUPP          rRectProc;
  QDOvalUPP           ovalProc;
  QDArcUPP            arcProc;
  QDPolyUPP           polyProc;
  QDRgnUPP            rgnProc;
  QDBitsUPP           bitsProc;
  QDCommentUPP        commentProc;
  QDTxMeasUPP         txMeasProc;
  QDGetPicUPP         getPicProc;
  QDPutPicUPP         putPicProc;
};
typedef struct QDProcs                  QDProcs;
typedef QDProcs *                       QDProcsPtr;
/*
 *  NewQDTextUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDTextUPP
NewQDTextUPP(QDTextProcPtr userRoutine)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  NewQDLineUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDLineUPP
NewQDLineUPP(QDLineProcPtr userRoutine)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  NewQDRectUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDRectUPP
NewQDRectUPP(QDRectProcPtr userRoutine)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  NewQDRRectUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDRRectUPP
NewQDRRectUPP(QDRRectProcPtr userRoutine)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  NewQDOvalUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDOvalUPP
NewQDOvalUPP(QDOvalProcPtr userRoutine)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  NewQDArcUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDArcUPP
NewQDArcUPP(QDArcProcPtr userRoutine)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  NewQDPolyUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDPolyUPP
NewQDPolyUPP(QDPolyProcPtr userRoutine)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  NewQDRgnUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDRgnUPP
NewQDRgnUPP(QDRgnProcPtr userRoutine)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  NewQDBitsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDBitsUPP
NewQDBitsUPP(QDBitsProcPtr userRoutine)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  NewQDCommentUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDCommentUPP
NewQDCommentUPP(QDCommentProcPtr userRoutine)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  NewQDTxMeasUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDTxMeasUPP
NewQDTxMeasUPP(QDTxMeasProcPtr userRoutine)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  NewQDGetPicUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDGetPicUPP
NewQDGetPicUPP(QDGetPicProcPtr userRoutine)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  NewQDPutPicUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDPutPicUPP
NewQDPutPicUPP(QDPutPicProcPtr userRoutine)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  NewQDOpcodeUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDOpcodeUPP
NewQDOpcodeUPP(QDOpcodeProcPtr userRoutine)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  NewQDStdGlyphsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDStdGlyphsUPP
NewQDStdGlyphsUPP(QDStdGlyphsProcPtr userRoutine)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  NewQDJShieldCursorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDJShieldCursorUPP
NewQDJShieldCursorUPP(QDJShieldCursorProcPtr userRoutine)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeQDTextUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDTextUPP(QDTextUPP userUPP)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeQDLineUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDLineUPP(QDLineUPP userUPP)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeQDRectUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDRectUPP(QDRectUPP userUPP)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeQDRRectUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDRRectUPP(QDRRectUPP userUPP)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeQDOvalUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDOvalUPP(QDOvalUPP userUPP)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeQDArcUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDArcUPP(QDArcUPP userUPP)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeQDPolyUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDPolyUPP(QDPolyUPP userUPP)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeQDRgnUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDRgnUPP(QDRgnUPP userUPP)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeQDBitsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDBitsUPP(QDBitsUPP userUPP)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeQDCommentUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDCommentUPP(QDCommentUPP userUPP)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeQDTxMeasUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDTxMeasUPP(QDTxMeasUPP userUPP)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeQDGetPicUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDGetPicUPP(QDGetPicUPP userUPP)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeQDPutPicUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDPutPicUPP(QDPutPicUPP userUPP)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeQDOpcodeUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDOpcodeUPP(QDOpcodeUPP userUPP)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeQDStdGlyphsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDStdGlyphsUPP(QDStdGlyphsUPP userUPP)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeQDJShieldCursorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDJShieldCursorUPP(QDJShieldCursorUPP userUPP)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokeQDTextUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQDTextUPP(
  short         byteCount,
  const void *  textBuf,
  Point         numer,
  Point         denom,
  QDTextUPP     userUPP)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokeQDLineUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQDLineUPP(
  Point      newPt,
  QDLineUPP  userUPP)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokeQDRectUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQDRectUPP(
  GrafVerb      verb,
  const Rect *  r,
  QDRectUPP     userUPP)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokeQDRRectUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQDRRectUPP(
  GrafVerb      verb,
  const Rect *  r,
  short         ovalWidth,
  short         ovalHeight,
  QDRRectUPP    userUPP)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokeQDOvalUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQDOvalUPP(
  GrafVerb      verb,
  const Rect *  r,
  QDOvalUPP     userUPP)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokeQDArcUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQDArcUPP(
  GrafVerb      verb,
  const Rect *  r,
  short         startAngle,
  short         arcAngle,
  QDArcUPP      userUPP)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokeQDPolyUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQDPolyUPP(
  GrafVerb    verb,
  PolyHandle  poly,
  QDPolyUPP   userUPP)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokeQDRgnUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQDRgnUPP(
  GrafVerb   verb,
  RgnHandle  rgn,
  QDRgnUPP   userUPP)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokeQDBitsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQDBitsUPP(
  const BitMap *  srcBits,
  const Rect *    srcRect,
  const Rect *    dstRect,
  short           mode,
  RgnHandle       maskRgn,
  QDBitsUPP       userUPP)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokeQDCommentUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQDCommentUPP(
  short         kind,
  short         dataSize,
  Handle        dataHandle,
  QDCommentUPP  userUPP)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokeQDTxMeasUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern short
InvokeQDTxMeasUPP(
  short         byteCount,
  const void *  textAddr,
  Point *       numer,
  Point *       denom,
  FontInfo *    info,
  QDTxMeasUPP   userUPP)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokeQDGetPicUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQDGetPicUPP(
  void *       dataPtr,
  short        byteCount,
  QDGetPicUPP  userUPP)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokeQDPutPicUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQDPutPicUPP(
  const void *  dataPtr,
  short         byteCount,
  QDPutPicUPP   userUPP)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokeQDOpcodeUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQDOpcodeUPP(
  const Rect *  fromRect,
  const Rect *  toRect,
  UInt16        opcode,
  SInt16        version,
  QDOpcodeUPP   userUPP)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokeQDStdGlyphsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeQDStdGlyphsUPP(
  void *          dataStream,
  ByteCount       size,
  QDStdGlyphsUPP  userUPP)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokeQDJShieldCursorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQDJShieldCursorUPP(
  short               left,
  short               top,
  short               right,
  short               bottom,
  QDJShieldCursorUPP  userUPP)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

#if __MACH__
  #ifdef __cplusplus
    inline QDTextUPP                                            NewQDTextUPP(QDTextProcPtr userRoutine) { return userRoutine; }
    inline QDLineUPP                                            NewQDLineUPP(QDLineProcPtr userRoutine) { return userRoutine; }
    inline QDRectUPP                                            NewQDRectUPP(QDRectProcPtr userRoutine) { return userRoutine; }
    inline QDRRectUPP                                           NewQDRRectUPP(QDRRectProcPtr userRoutine) { return userRoutine; }
    inline QDOvalUPP                                            NewQDOvalUPP(QDOvalProcPtr userRoutine) { return userRoutine; }
    inline QDArcUPP                                             NewQDArcUPP(QDArcProcPtr userRoutine) { return userRoutine; }
    inline QDPolyUPP                                            NewQDPolyUPP(QDPolyProcPtr userRoutine) { return userRoutine; }
    inline QDRgnUPP                                             NewQDRgnUPP(QDRgnProcPtr userRoutine) { return userRoutine; }
    inline QDBitsUPP                                            NewQDBitsUPP(QDBitsProcPtr userRoutine) { return userRoutine; }
    inline QDCommentUPP                                         NewQDCommentUPP(QDCommentProcPtr userRoutine) { return userRoutine; }
    inline QDTxMeasUPP                                          NewQDTxMeasUPP(QDTxMeasProcPtr userRoutine) { return userRoutine; }
    inline QDGetPicUPP                                          NewQDGetPicUPP(QDGetPicProcPtr userRoutine) { return userRoutine; }
    inline QDPutPicUPP                                          NewQDPutPicUPP(QDPutPicProcPtr userRoutine) { return userRoutine; }
    inline QDOpcodeUPP                                          NewQDOpcodeUPP(QDOpcodeProcPtr userRoutine) { return userRoutine; }
    inline QDStdGlyphsUPP                                       NewQDStdGlyphsUPP(QDStdGlyphsProcPtr userRoutine) { return userRoutine; }
    inline QDJShieldCursorUPP                                   NewQDJShieldCursorUPP(QDJShieldCursorProcPtr userRoutine) { return userRoutine; }
    inline void                                                 DisposeQDTextUPP(QDTextUPP) { }
    inline void                                                 DisposeQDLineUPP(QDLineUPP) { }
    inline void                                                 DisposeQDRectUPP(QDRectUPP) { }
    inline void                                                 DisposeQDRRectUPP(QDRRectUPP) { }
    inline void                                                 DisposeQDOvalUPP(QDOvalUPP) { }
    inline void                                                 DisposeQDArcUPP(QDArcUPP) { }
    inline void                                                 DisposeQDPolyUPP(QDPolyUPP) { }
    inline void                                                 DisposeQDRgnUPP(QDRgnUPP) { }
    inline void                                                 DisposeQDBitsUPP(QDBitsUPP) { }
    inline void                                                 DisposeQDCommentUPP(QDCommentUPP) { }
    inline void                                                 DisposeQDTxMeasUPP(QDTxMeasUPP) { }
    inline void                                                 DisposeQDGetPicUPP(QDGetPicUPP) { }
    inline void                                                 DisposeQDPutPicUPP(QDPutPicUPP) { }
    inline void                                                 DisposeQDOpcodeUPP(QDOpcodeUPP) { }
    inline void                                                 DisposeQDStdGlyphsUPP(QDStdGlyphsUPP) { }
    inline void                                                 DisposeQDJShieldCursorUPP(QDJShieldCursorUPP) { }
    inline void                                                 InvokeQDTextUPP(short byteCount, const void * textBuf, Point numer, Point denom, QDTextUPP userUPP) { (*userUPP)(byteCount, textBuf, numer, denom); }
    inline void                                                 InvokeQDLineUPP(Point newPt, QDLineUPP userUPP) { (*userUPP)(newPt); }
    inline void                                                 InvokeQDRectUPP(GrafVerb verb, const Rect * r, QDRectUPP userUPP) { (*userUPP)(verb, r); }
    inline void                                                 InvokeQDRRectUPP(GrafVerb verb, const Rect * r, short ovalWidth, short ovalHeight, QDRRectUPP userUPP) { (*userUPP)(verb, r, ovalWidth, ovalHeight); }
    inline void                                                 InvokeQDOvalUPP(GrafVerb verb, const Rect * r, QDOvalUPP userUPP) { (*userUPP)(verb, r); }
    inline void                                                 InvokeQDArcUPP(GrafVerb verb, const Rect * r, short startAngle, short arcAngle, QDArcUPP userUPP) { (*userUPP)(verb, r, startAngle, arcAngle); }
    inline void                                                 InvokeQDPolyUPP(GrafVerb verb, PolyHandle poly, QDPolyUPP userUPP) { (*userUPP)(verb, poly); }
    inline void                                                 InvokeQDRgnUPP(GrafVerb verb, RgnHandle rgn, QDRgnUPP userUPP) { (*userUPP)(verb, rgn); }
    inline void                                                 InvokeQDBitsUPP(const BitMap * srcBits, const Rect * srcRect, const Rect * dstRect, short mode, RgnHandle maskRgn, QDBitsUPP userUPP) { (*userUPP)(srcBits, srcRect, dstRect, mode, maskRgn); }
    inline void                                                 InvokeQDCommentUPP(short kind, short dataSize, Handle dataHandle, QDCommentUPP userUPP) { (*userUPP)(kind, dataSize, dataHandle); }
    inline short                                                InvokeQDTxMeasUPP(short byteCount, const void * textAddr, Point * numer, Point * denom, FontInfo * info, QDTxMeasUPP userUPP) { return (*userUPP)(byteCount, textAddr, numer, denom, info); }
    inline void                                                 InvokeQDGetPicUPP(void * dataPtr, short byteCount, QDGetPicUPP userUPP) { (*userUPP)(dataPtr, byteCount); }
    inline void                                                 InvokeQDPutPicUPP(const void * dataPtr, short byteCount, QDPutPicUPP userUPP) { (*userUPP)(dataPtr, byteCount); }
    inline void                                                 InvokeQDOpcodeUPP(const Rect * fromRect, const Rect * toRect, UInt16 opcode, SInt16 version, QDOpcodeUPP userUPP) { (*userUPP)(fromRect, toRect, opcode, version); }
    inline OSStatus                                             InvokeQDStdGlyphsUPP(void * dataStream, ByteCount size, QDStdGlyphsUPP userUPP) { return (*userUPP)(dataStream, size); }
    inline void                                                 InvokeQDJShieldCursorUPP(short left, short top, short right, short bottom, QDJShieldCursorUPP userUPP) { (*userUPP)(left, top, right, bottom); }
  #else
    #define NewQDTextUPP(userRoutine)                           ((QDTextUPP)userRoutine)
    #define NewQDLineUPP(userRoutine)                           ((QDLineUPP)userRoutine)
    #define NewQDRectUPP(userRoutine)                           ((QDRectUPP)userRoutine)
    #define NewQDRRectUPP(userRoutine)                          ((QDRRectUPP)userRoutine)
    #define NewQDOvalUPP(userRoutine)                           ((QDOvalUPP)userRoutine)
    #define NewQDArcUPP(userRoutine)                            ((QDArcUPP)userRoutine)
    #define NewQDPolyUPP(userRoutine)                           ((QDPolyUPP)userRoutine)
    #define NewQDRgnUPP(userRoutine)                            ((QDRgnUPP)userRoutine)
    #define NewQDBitsUPP(userRoutine)                           ((QDBitsUPP)userRoutine)
    #define NewQDCommentUPP(userRoutine)                        ((QDCommentUPP)userRoutine)
    #define NewQDTxMeasUPP(userRoutine)                         ((QDTxMeasUPP)userRoutine)
    #define NewQDGetPicUPP(userRoutine)                         ((QDGetPicUPP)userRoutine)
    #define NewQDPutPicUPP(userRoutine)                         ((QDPutPicUPP)userRoutine)
    #define NewQDOpcodeUPP(userRoutine)                         ((QDOpcodeUPP)userRoutine)
    #define NewQDStdGlyphsUPP(userRoutine)                      ((QDStdGlyphsUPP)userRoutine)
    #define NewQDJShieldCursorUPP(userRoutine)                  ((QDJShieldCursorUPP)userRoutine)
    #define DisposeQDTextUPP(userUPP)
    #define DisposeQDLineUPP(userUPP)
    #define DisposeQDRectUPP(userUPP)
    #define DisposeQDRRectUPP(userUPP)
    #define DisposeQDOvalUPP(userUPP)
    #define DisposeQDArcUPP(userUPP)
    #define DisposeQDPolyUPP(userUPP)
    #define DisposeQDRgnUPP(userUPP)
    #define DisposeQDBitsUPP(userUPP)
    #define DisposeQDCommentUPP(userUPP)
    #define DisposeQDTxMeasUPP(userUPP)
    #define DisposeQDGetPicUPP(userUPP)
    #define DisposeQDPutPicUPP(userUPP)
    #define DisposeQDOpcodeUPP(userUPP)
    #define DisposeQDStdGlyphsUPP(userUPP)
    #define DisposeQDJShieldCursorUPP(userUPP)
    #define InvokeQDTextUPP(byteCount, textBuf, numer, denom, userUPP) (*userUPP)(byteCount, textBuf, numer, denom)
    #define InvokeQDLineUPP(newPt, userUPP)                     (*userUPP)(newPt)
    #define InvokeQDRectUPP(verb, r, userUPP)                   (*userUPP)(verb, r)
    #define InvokeQDRRectUPP(verb, r, ovalWidth, ovalHeight, userUPP) (*userUPP)(verb, r, ovalWidth, ovalHeight)
    #define InvokeQDOvalUPP(verb, r, userUPP)                   (*userUPP)(verb, r)
    #define InvokeQDArcUPP(verb, r, startAngle, arcAngle, userUPP) (*userUPP)(verb, r, startAngle, arcAngle)
    #define InvokeQDPolyUPP(verb, poly, userUPP)                (*userUPP)(verb, poly)
    #define InvokeQDRgnUPP(verb, rgn, userUPP)                  (*userUPP)(verb, rgn)
    #define InvokeQDBitsUPP(srcBits, srcRect, dstRect, mode, maskRgn, userUPP) (*userUPP)(srcBits, srcRect, dstRect, mode, maskRgn)
    #define InvokeQDCommentUPP(kind, dataSize, dataHandle, userUPP) (*userUPP)(kind, dataSize, dataHandle)
    #define InvokeQDTxMeasUPP(byteCount, textAddr, numer, denom, info, userUPP) (*userUPP)(byteCount, textAddr, numer, denom, info)
    #define InvokeQDGetPicUPP(dataPtr, byteCount, userUPP)      (*userUPP)(dataPtr, byteCount)
    #define InvokeQDPutPicUPP(dataPtr, byteCount, userUPP)      (*userUPP)(dataPtr, byteCount)
    #define InvokeQDOpcodeUPP(fromRect, toRect, opcode, version, userUPP) (*userUPP)(fromRect, toRect, opcode, version)
    #define InvokeQDStdGlyphsUPP(dataStream, size, userUPP)     (*userUPP)(dataStream, size)
    #define InvokeQDJShieldCursorUPP(left, top, right, bottom, userUPP) (*userUPP)(left, top, right, bottom)
  #endif
#endif

#if !OPAQUE_TOOLBOX_STRUCTS
struct GrafPort {
  short               device;                 /* not available in Carbon*/
  BitMap              portBits;               /* in Carbon use GetPortBitMapForCopyBits or IsPortColor*/
  Rect                portRect;               /* in Carbon use Get/SetPortBounds*/
  RgnHandle           visRgn;                 /* in Carbon use Get/SetPortVisibleRegion*/
  RgnHandle           clipRgn;                /* in Carbon use Get/SetPortClipRegion*/
  Pattern             bkPat;                  /* not available in Carbon all GrafPorts are CGrafPorts*/
  Pattern             fillPat;                /* not available in Carbon all GrafPorts are CGrafPorts*/
  Point               pnLoc;                  /* in Carbon use GetPortPenLocation or MoveTo*/
  Point               pnSize;                 /* in Carbon use Get/SetPortPenSize*/
  short               pnMode;                 /* in Carbon use Get/SetPortPenMode*/
  Pattern             pnPat;                  /* not available in Carbon all GrafPorts are CGrafPorts*/
  short               pnVis;                  /* in Carbon use GetPortPenVisibility or Show/HidePen*/
  short               txFont;                 /* in Carbon use GetPortTextFont or TextFont*/
  StyleField          txFace;                 /* in Carbon use GetPortTextFace or TextFace*/
                                              /*StyleField occupies 16-bits, but only first 8-bits are used*/
  short               txMode;                 /* in Carbon use GetPortTextMode or TextMode*/
  short               txSize;                 /* in Carbon use GetPortTextSize or TextSize*/
  Fixed               spExtra;                /* in Carbon use GetPortSpExtra or SpaceExtra*/
  long                fgColor;                /* not available in Carbon */
  long                bkColor;                /* not available in Carbon*/
  short               colrBit;                /* not available in Carbon*/
  short               patStretch;             /* not available in Carbon*/
  Handle              picSave;                /* in Carbon use IsPortPictureBeingDefined*/
  Handle              rgnSave;                /* not available in Carbon*/
  Handle              polySave;               /* not available in Carbon*/
  QDProcsPtr          grafProcs;              /* not available in Carbon all GrafPorts are CGrafPorts*/
};
typedef struct GrafPort                 GrafPort;
typedef GrafPort *                      GrafPtr;
/*
 *  This set of definitions "belongs" in Windows.
 *  But, there is a circularity in the headers where Windows includes Controls and
 *  Controls includes Windows. To break the circle, the information
 *  needed by Controls is moved from Windows to Quickdraw.
 */
typedef GrafPtr                         WindowPtr;
typedef WindowPtr                       DialogPtr;
#else
typedef struct OpaqueWindowPtr*         WindowPtr;
typedef struct OpaqueDialogPtr*         DialogPtr;
typedef struct OpaqueGrafPtr*           GrafPtr;
#endif  /* !OPAQUE_TOOLBOX_STRUCTS */

typedef WindowPtr                       WindowRef;
/* DragConstraint constants to pass to DragGray,DragTheRgn, or ConstrainedDragRgn*/
typedef UInt16                          DragConstraint;
enum {
  kNoConstraint                 = 0,
  kVerticalConstraint           = 1,
  kHorizontalConstraint         = 2
};


typedef CALLBACK_API( void , DragGrayRgnProcPtr )(void);
/*
 *  Here ends the list of things that "belong" in Windows.
 */


struct RGBColor {
  unsigned short      red;                    /*magnitude of red component*/
  unsigned short      green;                  /*magnitude of green component*/
  unsigned short      blue;                   /*magnitude of blue component*/
};
typedef struct RGBColor                 RGBColor;
typedef RGBColor *                      RGBColorPtr;
typedef RGBColorPtr *                   RGBColorHdl;
typedef CALLBACK_API( Boolean , ColorSearchProcPtr )(RGBColor *rgb, long *position);
typedef CALLBACK_API( Boolean , ColorComplementProcPtr )(RGBColor * rgb);
typedef STACK_UPP_TYPE(DragGrayRgnProcPtr)                      DragGrayRgnUPP;
typedef STACK_UPP_TYPE(ColorSearchProcPtr)                      ColorSearchUPP;
typedef STACK_UPP_TYPE(ColorComplementProcPtr)                  ColorComplementUPP;
/*
 *  NewDragGrayRgnUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DragGrayRgnUPP
NewDragGrayRgnUPP(DragGrayRgnProcPtr userRoutine)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  NewColorSearchUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ColorSearchUPP
NewColorSearchUPP(ColorSearchProcPtr userRoutine)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  NewColorComplementUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ColorComplementUPP
NewColorComplementUPP(ColorComplementProcPtr userRoutine)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeDragGrayRgnUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDragGrayRgnUPP(DragGrayRgnUPP userUPP)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeColorSearchUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeColorSearchUPP(ColorSearchUPP userUPP)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeColorComplementUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeColorComplementUPP(ColorComplementUPP userUPP)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokeDragGrayRgnUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeDragGrayRgnUPP(DragGrayRgnUPP userUPP)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokeColorSearchUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeColorSearchUPP(
  RGBColor *      rgb,
  long *          position,
  ColorSearchUPP  userUPP)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokeColorComplementUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeColorComplementUPP(
  RGBColor *          rgb,
  ColorComplementUPP  userUPP)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

#if __MACH__
  #ifdef __cplusplus
    inline DragGrayRgnUPP                                       NewDragGrayRgnUPP(DragGrayRgnProcPtr userRoutine) { return userRoutine; }
    inline ColorSearchUPP                                       NewColorSearchUPP(ColorSearchProcPtr userRoutine) { return userRoutine; }
    inline ColorComplementUPP                                   NewColorComplementUPP(ColorComplementProcPtr userRoutine) { return userRoutine; }
    inline void                                                 DisposeDragGrayRgnUPP(DragGrayRgnUPP) { }
    inline void                                                 DisposeColorSearchUPP(ColorSearchUPP) { }
    inline void                                                 DisposeColorComplementUPP(ColorComplementUPP) { }
    inline void                                                 InvokeDragGrayRgnUPP(DragGrayRgnUPP userUPP) { (*userUPP)(); }
    inline Boolean                                              InvokeColorSearchUPP(RGBColor * rgb, long * position, ColorSearchUPP userUPP) { return (*userUPP)(rgb, position); }
    inline Boolean                                              InvokeColorComplementUPP(RGBColor * rgb, ColorComplementUPP userUPP) { return (*userUPP)(rgb); }
  #else
    #define NewDragGrayRgnUPP(userRoutine)                      ((DragGrayRgnUPP)userRoutine)
    #define NewColorSearchUPP(userRoutine)                      ((ColorSearchUPP)userRoutine)
    #define NewColorComplementUPP(userRoutine)                  ((ColorComplementUPP)userRoutine)
    #define DisposeDragGrayRgnUPP(userUPP)
    #define DisposeColorSearchUPP(userUPP)
    #define DisposeColorComplementUPP(userUPP)
    #define InvokeDragGrayRgnUPP(userUPP)                       (*userUPP)()
    #define InvokeColorSearchUPP(rgb, position, userUPP)        (*userUPP)(rgb, position)
    #define InvokeColorComplementUPP(rgb, userUPP)              (*userUPP)(rgb)
  #endif
#endif

struct ColorSpec {
  short               value;                  /*index or other value*/
  RGBColor            rgb;                    /*true color*/
};
typedef struct ColorSpec                ColorSpec;
typedef ColorSpec *                     ColorSpecPtr;
typedef ColorSpec                       CSpecArray[1];
struct ColorTable {
  SInt32              ctSeed;                 /*unique identifier for table*/
  short               ctFlags;                /*high bit: 0 = PixMap; 1 = device*/
  short               ctSize;                 /*number of entries in CTTable*/
  CSpecArray          ctTable;                /*array [0..0] of ColorSpec*/
};
typedef struct ColorTable               ColorTable;
typedef ColorTable *                    CTabPtr;
typedef CTabPtr *                       CTabHandle;
struct xColorSpec {
  short               value;                  /*index or other value*/
  RGBColor            rgb;                    /*true color*/
  short               xalpha;
};
typedef struct xColorSpec               xColorSpec;
typedef xColorSpec *                    xColorSpecPtr;
typedef xColorSpec                      xCSpecArray[1];
struct MatchRec {
  unsigned short      red;
  unsigned short      green;
  unsigned short      blue;
  long                matchData;
};
typedef struct MatchRec                 MatchRec;
/* keep this around in case anybody relies on it */
#define OLDPIXMAPSTRUCT 0
#define NON_MAC_PIXEL_FORMATS 1

#define GETPIXMAPPIXELFORMAT(pm)   ( ((pm)->pixelFormat != 0) ? (UInt32)(pm)->pixelFormat : (UInt32)(pm)->pixelSize )

/* QuickTime 3.0 changed the original PixMap data structure, replacing the 
   old planeBytes field by "pixelFormat", and pmReserved by pmExt (a Handle to
   additional private info). On Mac OS X, most QuickTime-specific changes were
   merged into Quickdraw.
   32-bit constants for the new pixelFormat field are enumerated below.
   Please note that not all predefined pixelFormat constants are supported under
   all circumstances. For example, because of performance tuning on ppc systems,
   many QD drawing functions don't support little-endian pixelFormat destinations
   on ppc systems.
*/
/* Values for PixMap.pixelFormat (BE = Big Endian, LE = Little Endian)*/
enum {
                                        /* The original pixel formats supported by 32-bit Color Quickdraw*/
  k1MonochromePixelFormat       = 0x00000001, /* 1 bit indexed*/
  k2IndexedPixelFormat          = 0x00000002, /* 2 bit indexed*/
  k4IndexedPixelFormat          = 0x00000004, /* 4 bit indexed*/
  k8IndexedPixelFormat          = 0x00000008, /* 8 bit indexed*/
  k16BE555PixelFormat           = 0x00000010, /* 16 bit BE rgb 555 (Mac)*/
  k24RGBPixelFormat             = 0x00000018, /* 24 bit rgb */
  k32ARGBPixelFormat            = 0x00000020, /* 32 bit argb    (Mac)*/
                                        /* QuickTime additions*/
  k1IndexedGrayPixelFormat      = 0x00000021, /* 1 bit indexed gray*/
  k2IndexedGrayPixelFormat      = 0x00000022, /* 2 bit indexed gray*/
  k4IndexedGrayPixelFormat      = 0x00000024, /* 4 bit indexed gray*/
  k8IndexedGrayPixelFormat      = 0x00000028, /* 8 bit indexed gray*/
  k16LE555PixelFormat           = 'L555', /* 16 bit LE rgb 555 (PC)*/
  k16LE5551PixelFormat          = '5551', /* 16 bit LE rgb 5551*/
  k16BE565PixelFormat           = 'B565', /* 16 bit BE rgb 565*/
  k16LE565PixelFormat           = 'L565', /* 16 bit LE rgb 565*/
  k24BGRPixelFormat             = '24BG', /* 24 bit bgr */
  k32BGRAPixelFormat            = 'BGRA', /* 32 bit bgra    (Matrox)*/
  k32ABGRPixelFormat            = 'ABGR', /* 32 bit abgr    */
  k32RGBAPixelFormat            = 'RGBA', /* 32 bit rgba    */
  kYUVSPixelFormat              = 'yuvs', /* YUV 4:2:2 byte ordering 16-unsigned = 'YUY2'*/
  kYUVUPixelFormat              = 'yuvu', /* YUV 4:2:2 byte ordering 16-signed*/
  kYVU9PixelFormat              = 'YVU9', /* YVU9 Planar    9*/
  kYUV411PixelFormat            = 'Y411', /* YUV 4:1:1 Interleaved  16*/
  kYVYU422PixelFormat           = 'YVYU', /* YVYU 4:2:2 byte ordering   16*/
  kUYVY422PixelFormat           = 'UYVY', /* UYVY 4:2:2 byte ordering   16*/
  kYUV211PixelFormat            = 'Y211', /* YUV 2:1:1 Packed   8*/
  k2vuyPixelFormat              = '2vuy' /* UYVY 4:2:2 byte ordering   16*/
};


struct PixMap {
  Ptr                 baseAddr;               /* pointer to pixels */
  short               rowBytes;               /* offset to next line */
  Rect                bounds;                 /* encloses bitmap */
  short               pmVersion;              /* pixMap version number */
  short               packType;               /* defines packing format */
  SInt32              packSize;               /* length of pixel data */
  Fixed               hRes;                   /* horiz. resolution (ppi) */
  Fixed               vRes;                   /* vert. resolution (ppi) */
  short               pixelType;              /* defines pixel type */
  short               pixelSize;              /* # bits in pixel */
  short               cmpCount;               /* # components in pixel */
  short               cmpSize;                /* # bits per component */
  OSType              pixelFormat;            /* fourCharCode representation */
  CTabHandle          pmTable;                /* color map for this pixMap */
  void *              pmExt;                  /* Handle to pixMap extension */
};
typedef struct PixMap                   PixMap;
typedef PixMap *                        PixMapPtr;
typedef PixMapPtr *                     PixMapHandle;
struct PixPat {
  short               patType;                /*type of pattern*/
  PixMapHandle        patMap;                 /*the pattern's pixMap*/
  Handle              patData;                /*pixmap's data*/
  Handle              patXData;               /*expanded Pattern data*/
  short               patXValid;              /*flags whether expanded Pattern valid*/
  Handle              patXMap;                /*Handle to expanded Pattern data*/
  Pattern             pat1Data;               /*old-Style pattern/RGB color*/
};
typedef struct PixPat                   PixPat;
typedef PixPat *                        PixPatPtr;
typedef PixPatPtr *                     PixPatHandle;
struct CCrsr {
  short               crsrType;               /*type of cursor*/
  PixMapHandle        crsrMap;                /*the cursor's pixmap*/
  Handle              crsrData;               /*cursor's data*/
  Handle              crsrXData;              /*expanded cursor data*/
  short               crsrXValid;             /*depth of expanded data (0 if none)*/
  Handle              crsrXHandle;            /*future use*/
  Bits16              crsr1Data;              /*one-bit cursor*/
  Bits16              crsrMask;               /*cursor's mask*/
  Point               crsrHotSpot;            /*cursor's hotspot*/
  SInt32              crsrXTable;             /*private*/
  SInt32              crsrID;                 /*private*/
};
typedef struct CCrsr                    CCrsr;
typedef CCrsr *                         CCrsrPtr;
typedef CCrsrPtr *                      CCrsrHandle;
struct GammaTbl {
  short               gVersion;               /*gamma version number*/
  short               gType;                  /*gamma data type*/
  short               gFormulaSize;           /*Formula data size*/
  short               gChanCnt;               /*number of channels of data*/
  short               gDataCnt;               /*number of values/channel*/
  short               gDataWidth;             /*bits/corrected value (data packed to next larger byte size)*/
  short               gFormulaData[1];        /*data for formulas followed by gamma values*/
};
typedef struct GammaTbl                 GammaTbl;
typedef GammaTbl *                      GammaTblPtr;
typedef GammaTblPtr *                   GammaTblHandle;
struct ITab {
  SInt32              iTabSeed;               /*copy of CTSeed from source CTable*/
  short               iTabRes;                /*bits/channel resolution of iTable*/
  Byte                iTTable[1];             /*byte colortable index values*/
};
typedef struct ITab                     ITab;
typedef ITab *                          ITabPtr;
typedef ITabPtr *                       ITabHandle;
struct SProcRec {
  Handle              nxtSrch;                /*SProcHndl Handle to next SProcRec*/
  ColorSearchUPP      srchProc;               /*search procedure proc ptr*/
};
typedef struct SProcRec                 SProcRec;
typedef SProcRec *                      SProcPtr;
typedef SProcPtr *                      SProcHndl;
struct CProcRec {
  Handle              nxtComp;                /*CProcHndl Handle to next CProcRec*/
  ColorComplementUPP  compProc;               /*complement procedure proc ptr*/
};
typedef struct CProcRec                 CProcRec;
typedef CProcRec *                      CProcPtr;
typedef CProcPtr *                      CProcHndl;
/* keep this around in case anybody relies on it */
#define OLDGDEVICESTRUCT 0
typedef struct GDevice                  GDevice;
typedef GDevice *                       GDPtr;
typedef GDPtr *                         GDHandle;
struct GDevice {
  short               gdRefNum;               /*driver's unit number*/
  short               gdID;                   /*client ID for search procs*/
  short               gdType;                 /*fixed/CLUT/direct*/
  ITabHandle          gdITable;               /*Handle to inverse lookup table*/
  short               gdResPref;              /*preferred resolution of GDITable*/
  SProcHndl           gdSearchProc;           /*search proc list head*/
  CProcHndl           gdCompProc;             /*complement proc list*/
  short               gdFlags;                /*grafDevice flags word*/
  PixMapHandle        gdPMap;                 /*describing pixMap*/
  SInt32              gdRefCon;               /*reference value*/
  GDHandle            gdNextGD;               /*GDHandle Handle of next gDevice*/
  Rect                gdRect;                 /* device's bounds in global coordinates*/
  SInt32              gdMode;                 /*device's current mode*/
  short               gdCCBytes;              /*depth of expanded cursor data*/
  short               gdCCDepth;              /*depth of expanded cursor data*/
  Handle              gdCCXData;              /*Handle to cursor's expanded data*/
  Handle              gdCCXMask;              /*Handle to cursor's expanded mask*/
  Handle              gdExt;                  /*QuickTime 3.0 private info*/
};

struct GrafVars {
  RGBColor            rgbOpColor;             /*color for addPin  subPin and average*/
  RGBColor            rgbHiliteColor;         /*color for hiliting*/
  Handle              pmFgColor;              /*palette Handle for foreground color*/
  short               pmFgIndex;              /*index value for foreground*/
  Handle              pmBkColor;              /*palette Handle for background color*/
  short               pmBkIndex;              /*index value for background*/
  short               pmFlags;                /*flags for Palette Manager*/
};
typedef struct GrafVars                 GrafVars;
typedef GrafVars *                      GVarPtr;
typedef GVarPtr *                       GVarHandle;

#if !OPAQUE_TOOLBOX_STRUCTS
typedef struct CGrafPort                CGrafPort;
typedef CGrafPort *                     CGrafPtr;
#else
typedef GrafPtr                         CGrafPtr;
#endif  /* !OPAQUE_TOOLBOX_STRUCTS */

typedef CALLBACK_API_C( OSStatus , QDPrinterStatusProcPtr )(PrinterStatusOpcode opcode, CGrafPtr currentPort, void *printerStatus);
typedef STACK_UPP_TYPE(QDPrinterStatusProcPtr)                  QDPrinterStatusUPP;

struct CQDProcs {
  QDTextUPP           textProc;
  QDLineUPP           lineProc;
  QDRectUPP           rectProc;
  QDRRectUPP          rRectProc;
  QDOvalUPP           ovalProc;
  QDArcUPP            arcProc;
  QDPolyUPP           polyProc;
  QDRgnUPP            rgnProc;
  QDBitsUPP           bitsProc;
  QDCommentUPP        commentProc;
  QDTxMeasUPP         txMeasProc;
  QDGetPicUPP         getPicProc;
  QDPutPicUPP         putPicProc;
  QDOpcodeUPP         opcodeProc;
  UniversalProcPtr    newProc1;               /* this is the StdPix bottleneck -- see ImageCompression.h */
  QDStdGlyphsUPP      glyphsProc;             /* unused on Mac OS X */
  QDPrinterStatusUPP  printerStatusProc;      /* was newProc3;  now used to communicate status between Printing code and System imaging code */
  UniversalProcPtr    newProc4;
  UniversalProcPtr    newProc5;
  UniversalProcPtr    newProc6;
};
typedef struct CQDProcs                 CQDProcs;
typedef CQDProcs *                      CQDProcsPtr;
#if !OPAQUE_TOOLBOX_STRUCTS
struct CGrafPort {
  short               device;                 /* not available in Carbon*/
  PixMapHandle        portPixMap;             /* in Carbon use GetPortPixMap*/
  short               portVersion;            /* in Carbon use IsPortColor*/
  Handle              grafVars;               /* not available in Carbon*/
  short               chExtra;                /* in Carbon use GetPortChExtra*/
  short               pnLocHFrac;             /* in Carbon use Get/SetPortFracHPenLocation*/
  Rect                portRect;               /* in Carbon use Get/SetPortBounds*/
  RgnHandle           visRgn;                 /* in Carbon use Get/SetPortVisibleRegion*/
  RgnHandle           clipRgn;                /* in Carbon use Get/SetPortClipRegion*/
  PixPatHandle        bkPixPat;               /* in Carbon use GetPortBackPixPat or BackPixPat*/
  RGBColor            rgbFgColor;             /* in Carbon use GetPortForeColor or RGBForeColor*/
  RGBColor            rgbBkColor;             /* in Carbon use GetPortBackColor or RGBBackColor*/
  Point               pnLoc;                  /* in Carbon use GetPortPenLocation or MoveTo*/
  Point               pnSize;                 /* in Carbon use Get/SetPortPenSize*/
  short               pnMode;                 /* in Carbon use Get/SetPortPenMode*/
  PixPatHandle        pnPixPat;               /* in Carbon use Get/SetPortPenPixPat*/
  PixPatHandle        fillPixPat;             /* in Carbon use GetPortFillPixPat*/
  short               pnVis;                  /* in Carbon use GetPortPenVisibility or Show/HidePen*/
  short               txFont;                 /* in Carbon use GetPortTextFont or TextFont*/
  StyleField          txFace;                 /* in Carbon use GetPortTextFace or TextFace*/
                                              /*StyleField occupies 16-bits, but only first 8-bits are used*/
  short               txMode;                 /* in Carbon use GetPortTextMode or TextMode*/
  short               txSize;                 /* in Carbon use GetPortTextSize or TextSize*/
  Fixed               spExtra;                /* in Carbon use GetPortSpExtra or SpaceExtra*/
  SInt32              fgColor;                /* not available in Carbon*/
  SInt32              bkColor;                /* not available in Carbon*/
  short               colrBit;                /* not available in Carbon*/
  short               patStretch;             /* not available in Carbon*/
  Handle              picSave;                /* in Carbon use IsPortPictureBeingDefined*/
  Handle              rgnSave;                /* in Carbon use IsPortRegionBeingDefined*/
  Handle              polySave;               /* in Carbon use IsPortPolyBeingDefined*/
  CQDProcsPtr         grafProcs;              /* in Carbon use Get/SetPortGrafProcs*/
};

#endif  /* !OPAQUE_TOOLBOX_STRUCTS */

#if OPAQUE_TOOLBOX_STRUCTS
typedef WindowPtr                       CWindowPtr;
#else
typedef CGrafPtr                        CWindowPtr;
#endif  /* OPAQUE_TOOLBOX_STRUCTS */

struct ReqListRec {
  short               reqLSize;               /*request list size*/
  short               reqLData[1];            /*request list data*/
};
typedef struct ReqListRec               ReqListRec;
struct OpenCPicParams {
  Rect                srcRect;
  Fixed               hRes;
  Fixed               vRes;
  short               version;
  short               reserved1;
  SInt32              reserved2;
};
typedef struct OpenCPicParams           OpenCPicParams;
typedef CALLBACK_API( void , DeviceLoopDrawingProcPtr )(short depth, short deviceFlags, GDHandle targetDevice, SRefCon userData);
typedef STACK_UPP_TYPE(DeviceLoopDrawingProcPtr)                DeviceLoopDrawingUPP;
/*
 *  NewQDPrinterStatusUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  NewDeviceLoopDrawingUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DeviceLoopDrawingUPP
NewDeviceLoopDrawingUPP(DeviceLoopDrawingProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeQDPrinterStatusUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  DisposeDeviceLoopDrawingUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDeviceLoopDrawingUPP(DeviceLoopDrawingUPP userUPP)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokeQDPrinterStatusUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  InvokeDeviceLoopDrawingUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeDeviceLoopDrawingUPP(
  short                 depth,
  short                 deviceFlags,
  GDHandle              targetDevice,
  SRefCon               userData,
  DeviceLoopDrawingUPP  userUPP)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

#if __MACH__
  #ifdef __cplusplus
    inline DeviceLoopDrawingUPP                                 NewDeviceLoopDrawingUPP(DeviceLoopDrawingProcPtr userRoutine) { return userRoutine; }
    inline void                                                 DisposeDeviceLoopDrawingUPP(DeviceLoopDrawingUPP) { }
    inline void                                                 InvokeDeviceLoopDrawingUPP(short depth, short deviceFlags, GDHandle targetDevice, SRefCon userData, DeviceLoopDrawingUPP userUPP) { (*userUPP)(depth, deviceFlags, targetDevice, userData); }
  #else
    #define NewDeviceLoopDrawingUPP(userRoutine)                ((DeviceLoopDrawingUPP)userRoutine)
    #define DisposeDeviceLoopDrawingUPP(userUPP)
    #define InvokeDeviceLoopDrawingUPP(depth, deviceFlags, targetDevice, userData, userUPP) (*userUPP)(depth, deviceFlags, targetDevice, userData)
  #endif
#endif

#if !OPAQUE_TOOLBOX_STRUCTS || !TARGET_API_MAC_CARBON
struct QDGlobals {
  char                privates[76];
  SInt32              randSeed;               /* in Carbon use GetQDGlobalsRandomSeed*/
  BitMap              screenBits;             /* in Carbon use GetQDGlobalsScreenBits*/
  Cursor              arrow;                  /* in Carbon use GetQDGlobalsArrow*/
  Pattern             dkGray;                 /* in Carbon use GetQDGlobalsDarkGray*/
  Pattern             ltGray;                 /* in Carbon use GetQDGlobalsLightGray*/
  Pattern             gray;                   /* in Carbon use GetQDGlobalsGray*/
  Pattern             black;                  /* in Carbon use GetQDGlobalsBlack*/
  Pattern             white;                  /* in Carbon use GetQDGlobalsWhite*/
  GrafPtr             thePort;                /* in Carbon use GetQDGlobalsThePort*/
};
typedef struct QDGlobals                QDGlobals;
typedef QDGlobals *                     QDGlobalsPtr;
typedef QDGlobalsPtr *                  QDGlobalsHdl;
#endif  /* !OPAQUE_TOOLBOX_STRUCTS || !TARGET_API_MAC_CARBON */















#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif /* __QUICKDRAWTYPES__ */

