/*
     File:       QD/Quickdraw.h
 
     Contains:   Interface to Quickdraw Graphics
 
     Version:    Quickdraw-64.6.15~3
 
     Copyright:  © 1985-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __QUICKDRAW__
#define __QUICKDRAW__

#ifndef __COMPONENTS__
#include <CarbonCore/Components.h>
#endif


#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __MIXEDMODE__
#include <CarbonCore/MixedMode.h>
#endif

#ifndef __QUICKDRAWTEXT__
#include <QD/QuickdrawText.h>
#endif

#ifndef __CGCONTEXT__
#include <CoreGraphics/CGContext.h>
#endif

#ifndef __CMTYPES__
#include <ColorSync/CMTypes.h>
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
  blackColor                    = 33,   /*colors expressed in these mappings*/
  whiteColor                    = 30,
  redColor                      = 205,
  greenColor                    = 341,
  blueColor                     = 409,
  cyanColor                     = 273,
  magentaColor                  = 137,
  yellowColor                   = 69
};

enum {
  picLParen                     = 0,    /*standard picture comments*/
  picRParen                     = 1,
  clutType                      = 0,    /*0 if lookup table*/
  fixedType                     = 1,    /*1 if fixed table*/
  directType                    = 2,    /*2 if direct values*/
  gdDevType                     = 0     /*0 = monochrome 1 = color*/
};

enum {
  interlacedDevice              = 2,    /* 1 if single pixel lines look bad */
  roundedDevice                 = 5,    /* 1 if device has been “rounded” into the GrayRgn */
  hasAuxMenuBar                 = 6,    /* 1 if device has an aux menu bar on it */
  burstDevice                   = 7,
  ext32Device                   = 8,
  ramInit                       = 10,   /*1 if initialized from 'scrn' resource*/
  mainScreen                    = 11,   /* 1 if main screen */
  allInit                       = 12,   /* 1 if all devices initialized */
  screenDevice                  = 13,   /*1 if screen device [not used]*/
  noDriver                      = 14,   /* 1 if no driver for this GDevice */
  screenActive                  = 15,   /*1 if in use*/
  hiliteBit                     = 7,    /*flag bit in LMGet/SetHiliteMode*/
  pHiliteBit                    = 0,    /*flag bit in LMGet/SetHiliteMode when used with BitClr*/
  defQDColors                   = 127,  /*resource ID of clut for default QDColors*/
                                        /* pixel type */
  RGBDirect                     = 16,   /* 16 & 32 bits/pixel pixelType value */
                                        /* pmVersion values */
  baseAddr32                    = 4     /*pixmap base address is 32-bit address*/
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
NewQDTextUPP(QDTextProcPtr userRoutine);

/*
 *  NewQDLineUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDLineUPP
NewQDLineUPP(QDLineProcPtr userRoutine);

/*
 *  NewQDRectUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDRectUPP
NewQDRectUPP(QDRectProcPtr userRoutine);

/*
 *  NewQDRRectUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDRRectUPP
NewQDRRectUPP(QDRRectProcPtr userRoutine);

/*
 *  NewQDOvalUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDOvalUPP
NewQDOvalUPP(QDOvalProcPtr userRoutine);

/*
 *  NewQDArcUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDArcUPP
NewQDArcUPP(QDArcProcPtr userRoutine);

/*
 *  NewQDPolyUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDPolyUPP
NewQDPolyUPP(QDPolyProcPtr userRoutine);

/*
 *  NewQDRgnUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDRgnUPP
NewQDRgnUPP(QDRgnProcPtr userRoutine);

/*
 *  NewQDBitsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDBitsUPP
NewQDBitsUPP(QDBitsProcPtr userRoutine);

/*
 *  NewQDCommentUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDCommentUPP
NewQDCommentUPP(QDCommentProcPtr userRoutine);

/*
 *  NewQDTxMeasUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDTxMeasUPP
NewQDTxMeasUPP(QDTxMeasProcPtr userRoutine);

/*
 *  NewQDGetPicUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDGetPicUPP
NewQDGetPicUPP(QDGetPicProcPtr userRoutine);

/*
 *  NewQDPutPicUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDPutPicUPP
NewQDPutPicUPP(QDPutPicProcPtr userRoutine);

/*
 *  NewQDOpcodeUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDOpcodeUPP
NewQDOpcodeUPP(QDOpcodeProcPtr userRoutine);

/*
 *  NewQDStdGlyphsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDStdGlyphsUPP
NewQDStdGlyphsUPP(QDStdGlyphsProcPtr userRoutine);

/*
 *  NewQDJShieldCursorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDJShieldCursorUPP
NewQDJShieldCursorUPP(QDJShieldCursorProcPtr userRoutine);

/*
 *  DisposeQDTextUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDTextUPP(QDTextUPP userUPP);

/*
 *  DisposeQDLineUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDLineUPP(QDLineUPP userUPP);

/*
 *  DisposeQDRectUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDRectUPP(QDRectUPP userUPP);

/*
 *  DisposeQDRRectUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDRRectUPP(QDRRectUPP userUPP);

/*
 *  DisposeQDOvalUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDOvalUPP(QDOvalUPP userUPP);

/*
 *  DisposeQDArcUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDArcUPP(QDArcUPP userUPP);

/*
 *  DisposeQDPolyUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDPolyUPP(QDPolyUPP userUPP);

/*
 *  DisposeQDRgnUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDRgnUPP(QDRgnUPP userUPP);

/*
 *  DisposeQDBitsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDBitsUPP(QDBitsUPP userUPP);

/*
 *  DisposeQDCommentUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDCommentUPP(QDCommentUPP userUPP);

/*
 *  DisposeQDTxMeasUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDTxMeasUPP(QDTxMeasUPP userUPP);

/*
 *  DisposeQDGetPicUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDGetPicUPP(QDGetPicUPP userUPP);

/*
 *  DisposeQDPutPicUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDPutPicUPP(QDPutPicUPP userUPP);

/*
 *  DisposeQDOpcodeUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDOpcodeUPP(QDOpcodeUPP userUPP);

/*
 *  DisposeQDStdGlyphsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDStdGlyphsUPP(QDStdGlyphsUPP userUPP);

/*
 *  DisposeQDJShieldCursorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDJShieldCursorUPP(QDJShieldCursorUPP userUPP);

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
  QDTextUPP     userUPP);

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
  QDLineUPP  userUPP);

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
  QDRectUPP     userUPP);

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
  QDRRectUPP    userUPP);

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
  QDOvalUPP     userUPP);

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
  QDArcUPP      userUPP);

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
  QDPolyUPP   userUPP);

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
  QDRgnUPP   userUPP);

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
  QDBitsUPP       userUPP);

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
  QDCommentUPP  userUPP);

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
  QDTxMeasUPP   userUPP);

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
  QDGetPicUPP  userUPP);

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
  QDPutPicUPP   userUPP);

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
  QDOpcodeUPP   userUPP);

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
  QDStdGlyphsUPP  userUPP);

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
  QDJShieldCursorUPP  userUPP);

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
NewDragGrayRgnUPP(DragGrayRgnProcPtr userRoutine);

/*
 *  NewColorSearchUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ColorSearchUPP
NewColorSearchUPP(ColorSearchProcPtr userRoutine);

/*
 *  NewColorComplementUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ColorComplementUPP
NewColorComplementUPP(ColorComplementProcPtr userRoutine);

/*
 *  DisposeDragGrayRgnUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDragGrayRgnUPP(DragGrayRgnUPP userUPP);

/*
 *  DisposeColorSearchUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeColorSearchUPP(ColorSearchUPP userUPP);

/*
 *  DisposeColorComplementUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeColorComplementUPP(ColorComplementUPP userUPP);

/*
 *  InvokeDragGrayRgnUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeDragGrayRgnUPP(DragGrayRgnUPP userUPP);

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
  ColorSearchUPP  userUPP);

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
  ColorComplementUPP  userUPP);

struct ColorSpec {
  short               value;                  /*index or other value*/
  RGBColor            rgb;                    /*true color*/
};
typedef struct ColorSpec                ColorSpec;
typedef ColorSpec *                     ColorSpecPtr;
typedef ColorSpec                       CSpecArray[1];
struct ColorTable {
  long                ctSeed;                 /*unique identifier for table*/
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
/*
    QuickTime 3.0 makes PixMap data structure available on non-Mac OS's.
    In order to implement PixMap in these alternate environments, the PixMap
    had to be extended. The pmReserved field was changed to pmExt which is
    a Handle to extra info.  The planeBytes field was changed to pixelFormat.
    
    In OS X, Quickdraw also uses the new PixMap data structure.
*/
#ifndef OLDPIXMAPSTRUCT
#if TARGET_API_MAC_OS8
#define OLDPIXMAPSTRUCT 1
#else
#define OLDPIXMAPSTRUCT 0
#endif  /* TARGET_API_MAC_OS8 */

#endif  /* !defined(OLDPIXMAPSTRUCT) */


#if OLDPIXMAPSTRUCT
   #define GETPIXMAPPIXELFORMAT(pm)        ( (pm)->pixelSize )
#else
  #define GETPIXMAPPIXELFORMAT(pm)        ( ((pm)->pixelFormat != 0) ? (pm)->pixelFormat : (pm)->pixelSize )
#endif


#if TARGET_OS_MAC && TARGET_API_MAC_OS8
    #define NON_MAC_PIXEL_FORMATS   0
#else
    #define NON_MAC_PIXEL_FORMATS   1
#endif

/* pixel formats*/
enum {
  k1MonochromePixelFormat       = 0x00000001, /* 1 bit indexed*/
  k2IndexedPixelFormat          = 0x00000002, /* 2 bit indexed*/
  k4IndexedPixelFormat          = 0x00000004, /* 4 bit indexed*/
  k8IndexedPixelFormat          = 0x00000008, /* 8 bit indexed*/
  k16BE555PixelFormat           = 0x00000010, /* 16 bit BE rgb 555 (Mac)*/
  k24RGBPixelFormat             = 0x00000018, /* 24 bit rgb */
  k32ARGBPixelFormat            = 0x00000020, /* 32 bit argb    (Mac)*/
  k1IndexedGrayPixelFormat      = 0x00000021, /* 1 bit indexed gray*/
  k2IndexedGrayPixelFormat      = 0x00000022, /* 2 bit indexed gray*/
  k4IndexedGrayPixelFormat      = 0x00000024, /* 4 bit indexed gray*/
  k8IndexedGrayPixelFormat      = 0x00000028 /* 8 bit indexed gray*/
};


/* values for PixMap.pixelFormat*/
enum {
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
  Ptr                 baseAddr;               /*pointer to pixels*/
  short               rowBytes;               /*offset to next line*/
  Rect                bounds;                 /*encloses bitmap*/
  short               pmVersion;              /*pixMap version number*/
  short               packType;               /*defines packing format*/
  long                packSize;               /*length of pixel data*/
  Fixed               hRes;                   /*horiz. resolution (ppi)*/
  Fixed               vRes;                   /*vert. resolution (ppi)*/
  short               pixelType;              /*defines pixel type*/
  short               pixelSize;              /*# bits in pixel*/
  short               cmpCount;               /*# components in pixel*/
  short               cmpSize;                /*# bits per component*/
#if OLDPIXMAPSTRUCT
  long                planeBytes;             /*offset to next plane*/
  CTabHandle          pmTable;                /*color map for this pixMap*/
  long                pmReserved;
#else
  OSType                          pixelFormat;                /*fourCharCode representation*/
    CTabHandle                      pmTable;                    /*color map for this pixMap*/
  void*                           pmExt;                      /*Handle to pixMap extension*/
#endif
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
  long                crsrXTable;             /*private*/
  long                crsrID;                 /*private*/
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
  long                iTabSeed;               /*copy of CTSeed from source CTable*/
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
/*
    QuickTime 3.0 makes GDevice data structure available on non-Mac OS's.
    In order to implement GDevice in these alternate environments, the GDevice
    had to be extended. The gdReserved field was changed to gdExt which is
    a Handle to extra info.  
*/
#ifndef OLDGDEVICESTRUCT
#if TARGET_API_MAC_OS8
#define OLDGDEVICESTRUCT 1
#else
#define OLDGDEVICESTRUCT 0
#endif  /* TARGET_API_MAC_OS8 */

#endif  /* !defined(OLDGDEVICESTRUCT) */

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
  long                gdRefCon;               /*reference value*/
  GDHandle            gdNextGD;               /*GDHandle Handle of next gDevice*/
  Rect                gdRect;                 /* device's bounds in global coordinates*/
  long                gdMode;                 /*device's current mode*/
  short               gdCCBytes;              /*depth of expanded cursor data*/
  short               gdCCDepth;              /*depth of expanded cursor data*/
  Handle              gdCCXData;              /*Handle to cursor's expanded data*/
  Handle              gdCCXMask;              /*Handle to cursor's expanded mask*/
#if OLDGDEVICESTRUCT
  long                gdReserved;             /*future use. MUST BE 0*/
#else
  Handle                          gdExt;                      /*QuickTime 3.0 private info*/
#endif
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
  QDStdGlyphsUPP      glyphsProc;             /* was newProc2; now used in Unicode text drawing */
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
  long                fgColor;                /* not available in Carbon*/
  long                bkColor;                /* not available in Carbon*/
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
  long                reserved2;
};
typedef struct OpenCPicParams           OpenCPicParams;
enum {
  kCursorImageMajorVersion      = 0x0001,
  kCursorImageMinorVersion      = 0x0000
};

struct CursorImageRec {
  UInt16              majorVersion;
  UInt16              minorVersion;
  PixMapHandle        cursorPixMap;
  BitMapHandle        cursorBitMask;
};
typedef struct CursorImageRec           CursorImageRec;
typedef CursorImageRec *                CursorImagePtr;
typedef CALLBACK_API( void , DeviceLoopDrawingProcPtr )(short depth, short deviceFlags, GDHandle targetDevice, long userData);
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
NewDeviceLoopDrawingUPP(DeviceLoopDrawingProcPtr userRoutine);

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
DisposeDeviceLoopDrawingUPP(DeviceLoopDrawingUPP userUPP);

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
  long                  userData,
  DeviceLoopDrawingUPP  userUPP);

#if !OPAQUE_TOOLBOX_STRUCTS || !TARGET_API_MAC_CARBON
struct QDGlobals {
  char                privates[76];
  long                randSeed;               /* in Carbon use GetQDGlobalsRandomSeed*/
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
extern QDGlobals qd;

#endif  /* !OPAQUE_TOOLBOX_STRUCTS || !TARGET_API_MAC_CARBON */

/*
 *  InitGraf()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  OpenPort()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  InitPort()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  ClosePort()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
   These are Carbon only routines. They do nothing at all on
   Mac OS 8, but work flawlessly on Mac OS X.
*/
/*
 *  LockPortBits()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
LockPortBits(GrafPtr port);


/*
 *  UnlockPortBits()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
UnlockPortBits(GrafPtr port);


/* Break a region up into rectangles.*/

enum {
  kQDParseRegionFromTop         = (1 << 0),
  kQDParseRegionFromBottom      = (1 << 1),
  kQDParseRegionFromLeft        = (1 << 2),
  kQDParseRegionFromRight       = (1 << 3),
  kQDParseRegionFromTopLeft     = kQDParseRegionFromTop | kQDParseRegionFromLeft,
  kQDParseRegionFromBottomRight = kQDParseRegionFromBottom | kQDParseRegionFromRight
};

typedef SInt32                          QDRegionParseDirection;
enum {
  kQDRegionToRectsMsgInit       = 1,
  kQDRegionToRectsMsgParse      = 2,
  kQDRegionToRectsMsgTerminate  = 3
};

typedef CALLBACK_API_C( OSStatus , RegionToRectsProcPtr )(UInt16 message, RgnHandle rgn, const Rect *rect, void *refCon);
typedef STACK_UPP_TYPE(RegionToRectsProcPtr)                    RegionToRectsUPP;
/*
 *  NewRegionToRectsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern RegionToRectsUPP
NewRegionToRectsUPP(RegionToRectsProcPtr userRoutine);

/*
 *  DisposeRegionToRectsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeRegionToRectsUPP(RegionToRectsUPP userUPP);

/*
 *  InvokeRegionToRectsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeRegionToRectsUPP(
  UInt16            message,
  RgnHandle         rgn,
  const Rect *      rect,
  void *            refCon,
  RegionToRectsUPP  userUPP);

/*
 *  QDRegionToRects()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QDRegionToRects(
  RgnHandle                rgn,
  QDRegionParseDirection   dir,
  RegionToRectsUPP         proc,
  void *                   userData);


#if TARGET_OS_WIN32
/*
 *  GetPortHWND()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  GetHWNDPort()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


#define GetPortHWND(port)  (HWND)GetPortNativeWindow(port)
#define GetHWNDPort(theHWND) GetNativeWindowPort(theHWND)
/*
 *  GetPortHDC()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  GetPortHBITMAP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  GetPortHPALETTE()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  GetPortHFONT()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  GetDIBFromPICT()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  GetPICTFromDIB()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


#endif  /* TARGET_OS_WIN32 */

/*
 *  [Mac]SetPort()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacSetPort SetPort
#endif
extern void 
MacSetPort(GrafPtr port);


/*
 *  GetPort()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetPort(GrafPtr * port);


/*
 *  QDSwapPort()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
QDSwapPort(
  CGrafPtr    inNewPort,
  CGrafPtr *  outOldPort);


/*
 *  GrafDevice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GrafDevice(short device);


/*
 *  SetPortBits()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetPortBits(const BitMap * bm);


/*
 *  PortSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PortSize(
  short   width,
  short   height);


/*
 *  MovePortTo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
MovePortTo(
  short   leftGlobal,
  short   topGlobal);


/*
 *  SetOrigin()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetOrigin(
  short   h,
  short   v);


/*
 *  SetClip()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetClip(RgnHandle rgn);


/*
 *  GetClip()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetClip(RgnHandle rgn);


/*
 *  ClipRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ClipRect(const Rect * r);


/*
 *  BackPat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
BackPat(const Pattern * pat);


/*
 *  InitCursor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
InitCursor(void);


/*
 *  [Mac]SetCursor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacSetCursor SetCursor
#endif
extern void 
MacSetCursor(const Cursor * crsr);


/*
 *  HideCursor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
HideCursor(void);


/*
 *  [Mac]ShowCursor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacShowCursor ShowCursor
#endif
extern void 
MacShowCursor(void);


/*
 *  ObscureCursor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ObscureCursor(void);


/*
 *  HidePen()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
HidePen(void);


/*
 *  ShowPen()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ShowPen(void);


/*
 *  GetPen()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetPen(Point * pt);


/*
 *  GetPenState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetPenState(PenState * pnState);


/*
 *  SetPenState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetPenState(const PenState * pnState);


/*
 *  PenSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PenSize(
  short   width,
  short   height);


/*
 *  PenMode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PenMode(short mode);


/*
 *  PenPat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PenPat(const Pattern * pat);


/*
 *  PenNormal()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PenNormal(void);


/*
 *  MoveTo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
MoveTo(
  short   h,
  short   v);


/*
 *  Move()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
Move(
  short   dh,
  short   dv);


/*
 *  [Mac]LineTo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacLineTo LineTo
#endif
extern void 
MacLineTo(
  short   h,
  short   v);


/*
 *  Line()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
Line(
  short   dh,
  short   dv);


/*
 *  ForeColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ForeColor(long color);


/*
 *  BackColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
BackColor(long color);


/*
 *  ColorBit()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ColorBit(short whichBit);


/*
 *  [Mac]SetRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacSetRect SetRect
#endif
extern void 
MacSetRect(
  Rect *  r,
  short   left,
  short   top,
  short   right,
  short   bottom);


/*
 *  [Mac]OffsetRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacOffsetRect OffsetRect
#endif
extern void 
MacOffsetRect(
  Rect *  r,
  short   dh,
  short   dv);


/*
 *  [Mac]InsetRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacInsetRect InsetRect
#endif
extern void 
MacInsetRect(
  Rect *  r,
  short   dh,
  short   dv);


/*
 *  SectRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
SectRect(
  const Rect *  src1,
  const Rect *  src2,
  Rect *        dstRect);


/*
 *  [Mac]UnionRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacUnionRect UnionRect
#endif
extern void 
MacUnionRect(
  const Rect *  src1,
  const Rect *  src2,
  Rect *        dstRect);


/*
 *  [Mac]EqualRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacEqualRect EqualRect
#endif
extern Boolean 
MacEqualRect(
  const Rect *  rect1,
  const Rect *  rect2);


/*
 *  EmptyRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
EmptyRect(const Rect * r);


/*
 *  [Mac]FrameRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacFrameRect FrameRect
#endif
extern void 
MacFrameRect(const Rect * r);


/*
 *  PaintRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PaintRect(const Rect * r);


/*
 *  EraseRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
EraseRect(const Rect * r);


/*
 *  [Mac]InvertRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacInvertRect InvertRect
#endif
extern void 
MacInvertRect(const Rect * r);


/*
 *  [Mac]FillRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacFillRect FillRect
#endif
extern void 
MacFillRect(
  const Rect *     r,
  const Pattern *  pat);


/*
 *  FrameOval()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FrameOval(const Rect * r);


/*
 *  PaintOval()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PaintOval(const Rect * r);


/*
 *  EraseOval()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
EraseOval(const Rect * r);


/*
 *  InvertOval()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
InvertOval(const Rect * r);


/*
 *  FillOval()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FillOval(
  const Rect *     r,
  const Pattern *  pat);


/*
 *  FrameRoundRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FrameRoundRect(
  const Rect *  r,
  short         ovalWidth,
  short         ovalHeight);


/*
 *  PaintRoundRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PaintRoundRect(
  const Rect *  r,
  short         ovalWidth,
  short         ovalHeight);


/*
 *  EraseRoundRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
EraseRoundRect(
  const Rect *  r,
  short         ovalWidth,
  short         ovalHeight);


/*
 *  InvertRoundRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
InvertRoundRect(
  const Rect *  r,
  short         ovalWidth,
  short         ovalHeight);


/*
 *  FillRoundRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FillRoundRect(
  const Rect *     r,
  short            ovalWidth,
  short            ovalHeight,
  const Pattern *  pat);


/*
 *  FrameArc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FrameArc(
  const Rect *  r,
  short         startAngle,
  short         arcAngle);


/*
 *  PaintArc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PaintArc(
  const Rect *  r,
  short         startAngle,
  short         arcAngle);


/*
 *  EraseArc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
EraseArc(
  const Rect *  r,
  short         startAngle,
  short         arcAngle);


/*
 *  InvertArc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
InvertArc(
  const Rect *  r,
  short         startAngle,
  short         arcAngle);


/*
 *  FillArc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FillArc(
  const Rect *     r,
  short            startAngle,
  short            arcAngle,
  const Pattern *  pat);


/*
 *  NewRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern RgnHandle 
NewRgn(void);


/*
 *  OpenRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
OpenRgn(void);


/*
 *  CloseRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
CloseRgn(RgnHandle dstRgn);


/*
 *  BitMapToRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
BitMapToRegion(
  RgnHandle       region,
  const BitMap *  bMap);


/*
 *  HandleToRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
HandleToRgn(
  Handle      oldRegion,
  RgnHandle   region);


/*
 *  RgnToHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
RgnToHandle(
  RgnHandle   region,
  Handle      flattenedRgnDataHdl);


/*
 *  DisposeRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DisposeRgn(RgnHandle rgn);


/*
 *  [Mac]CopyRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacCopyRgn CopyRgn
#endif
extern void 
MacCopyRgn(
  RgnHandle   srcRgn,
  RgnHandle   dstRgn);


/*
 *  SetEmptyRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetEmptyRgn(RgnHandle rgn);


/*
 *  [Mac]SetRectRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacSetRectRgn SetRectRgn
#endif
extern void 
MacSetRectRgn(
  RgnHandle   rgn,
  short       left,
  short       top,
  short       right,
  short       bottom);


/*
 *  RectRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
RectRgn(
  RgnHandle     rgn,
  const Rect *  r);


/*
 *  [Mac]OffsetRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacOffsetRgn OffsetRgn
#endif
extern void 
MacOffsetRgn(
  RgnHandle   rgn,
  short       dh,
  short       dv);


/*
 *  InsetRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
InsetRgn(
  RgnHandle   rgn,
  short       dh,
  short       dv);


/*
 *  SectRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SectRgn(
  RgnHandle   srcRgnA,
  RgnHandle   srcRgnB,
  RgnHandle   dstRgn);


/*
 *  [Mac]UnionRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacUnionRgn UnionRgn
#endif
extern void 
MacUnionRgn(
  RgnHandle   srcRgnA,
  RgnHandle   srcRgnB,
  RgnHandle   dstRgn);


/*
 *  DiffRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DiffRgn(
  RgnHandle   srcRgnA,
  RgnHandle   srcRgnB,
  RgnHandle   dstRgn);


/*
 *  [Mac]XorRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacXorRgn XorRgn
#endif
extern void 
MacXorRgn(
  RgnHandle   srcRgnA,
  RgnHandle   srcRgnB,
  RgnHandle   dstRgn);


/*
 *  RectInRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
RectInRgn(
  const Rect *  r,
  RgnHandle     rgn);


/*
 *  [Mac]EqualRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacEqualRgn EqualRgn
#endif
extern Boolean 
MacEqualRgn(
  RgnHandle   rgnA,
  RgnHandle   rgnB);


/*
 *  EmptyRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
EmptyRgn(RgnHandle rgn);


/*
 *  [Mac]FrameRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacFrameRgn FrameRgn
#endif
extern void 
MacFrameRgn(RgnHandle rgn);


/*
 *  [Mac]PaintRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacPaintRgn PaintRgn
#endif
extern void 
MacPaintRgn(RgnHandle rgn);


/*
 *  EraseRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
EraseRgn(RgnHandle rgn);


/*
 *  [Mac]InvertRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacInvertRgn InvertRgn
#endif
extern void 
MacInvertRgn(RgnHandle rgn);


/*
 *  [Mac]FillRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacFillRgn FillRgn
#endif
extern void 
MacFillRgn(
  RgnHandle        rgn,
  const Pattern *  pat);


/*
 *  ScrollRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ScrollRect(
  const Rect *  r,
  short         dh,
  short         dv,
  RgnHandle     updateRgn);


/*
 *  CopyBits()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
CopyBits(
  const BitMap *  srcBits,
  const BitMap *  dstBits,
  const Rect *    srcRect,
  const Rect *    dstRect,
  short           mode,
  RgnHandle       maskRgn);      /* can be NULL */


/*
 *  SeedFill()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SeedFill(
  const void *  srcPtr,
  void *        dstPtr,
  short         srcRow,
  short         dstRow,
  short         height,
  short         words,
  short         seedH,
  short         seedV);


/*
 *  CalcMask()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
CalcMask(
  const void *  srcPtr,
  void *        dstPtr,
  short         srcRow,
  short         dstRow,
  short         height,
  short         words);


/*
 *  CopyMask()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
CopyMask(
  const BitMap *  srcBits,
  const BitMap *  maskBits,
  const BitMap *  dstBits,
  const Rect *    srcRect,
  const Rect *    maskRect,
  const Rect *    dstRect);


/*
 *  OpenPicture()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern PicHandle 
OpenPicture(const Rect * picFrame);


/*
 *  PicComment()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PicComment(
  short    kind,
  short    dataSize,
  Handle   dataHandle);


/*
 *  ClosePicture()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ClosePicture(void);


/*
 *  DrawPicture()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DrawPicture(
  PicHandle     myPicture,
  const Rect *  dstRect);


/*
 *  KillPicture()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
KillPicture(PicHandle myPicture);


/*
 *  OpenPoly()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern PolyHandle 
OpenPoly(void);


/*
 *  ClosePoly()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ClosePoly(void);


/*
 *  KillPoly()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
KillPoly(PolyHandle poly);


/*
 *  OffsetPoly()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
OffsetPoly(
  PolyHandle   poly,
  short        dh,
  short        dv);


/*
 *  FramePoly()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FramePoly(PolyHandle poly);


/*
 *  PaintPoly()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PaintPoly(PolyHandle poly);


/*
 *  ErasePoly()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ErasePoly(PolyHandle poly);


/*
 *  InvertPoly()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
InvertPoly(PolyHandle poly);


/*
 *  FillPoly()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FillPoly(
  PolyHandle       poly,
  const Pattern *  pat);


/*
 *  SetPt()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetPt(
  Point *  pt,
  short    h,
  short    v);


/*
 *  LocalToGlobal()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LocalToGlobal(Point * pt);


/*
 *  GlobalToLocal()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GlobalToLocal(Point * pt);


/*
 *  Random()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
Random(void);


/*
 *  StuffHex()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
StuffHex(
  void *             thingPtr,
  ConstStr255Param   s);


/*
 *  [Mac]GetPixel()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacGetPixel GetPixel
#endif
extern Boolean 
MacGetPixel(
  short   h,
  short   v);


/*
 *  ScalePt()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ScalePt(
  Point *       pt,
  const Rect *  srcRect,
  const Rect *  dstRect);


/*
 *  MapPt()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
MapPt(
  Point *       pt,
  const Rect *  srcRect,
  const Rect *  dstRect);


/*
 *  MapRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
MapRect(
  Rect *        r,
  const Rect *  srcRect,
  const Rect *  dstRect);


/*
 *  MapRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
MapRgn(
  RgnHandle     rgn,
  const Rect *  srcRect,
  const Rect *  dstRect);


/*
 *  MapPoly()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
MapPoly(
  PolyHandle    poly,
  const Rect *  srcRect,
  const Rect *  dstRect);


/*
 *  SetStdProcs()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetStdProcs(QDProcs * procs);


/*
 *  StdRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
StdRect(
  GrafVerb      verb,
  const Rect *  r);


/*
 *  StdRRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
StdRRect(
  GrafVerb      verb,
  const Rect *  r,
  short         ovalWidth,
  short         ovalHeight);


/*
 *  StdOval()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
StdOval(
  GrafVerb      verb,
  const Rect *  r);


/*
 *  StdArc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
StdArc(
  GrafVerb      verb,
  const Rect *  r,
  short         startAngle,
  short         arcAngle);


/*
 *  StdPoly()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
StdPoly(
  GrafVerb     verb,
  PolyHandle   poly);


/*
 *  StdRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
StdRgn(
  GrafVerb    verb,
  RgnHandle   rgn);


/*
 *  StdBits()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
StdBits(
  const BitMap *  srcBits,
  const Rect *    srcRect,
  const Rect *    dstRect,
  short           mode,
  RgnHandle       maskRgn);


/*
 *  StdComment()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
StdComment(
  short    kind,
  short    dataSize,
  Handle   dataHandle);


/*
 *  StdGetPic()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
StdGetPic(
  void *  dataPtr,
  short   byteCount);


/*
 *  StdPutPic()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
StdPutPic(
  const void *  dataPtr,
  short         byteCount);


/*
 *  StdOpcode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
StdOpcode(
  const Rect *  fromRect,
  const Rect *  toRect,
  UInt16        opcode,
  SInt16        version);


/*
 *  AddPt()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
AddPt(
  Point    src,
  Point *  dst);


/*
 *  EqualPt()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
EqualPt(
  Point   pt1,
  Point   pt2);


/*
 *  [Mac]PtInRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacPtInRect PtInRect
#endif
extern Boolean 
MacPtInRect(
  Point         pt,
  const Rect *  r);


/*
 *  Pt2Rect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
Pt2Rect(
  Point   pt1,
  Point   pt2,
  Rect *  dstRect);


/*
 *  PtToAngle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PtToAngle(
  const Rect *  r,
  Point         pt,
  short *       angle);


/*
 *  SubPt()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SubPt(
  Point    src,
  Point *  dst);


/*
 *  PtInRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
PtInRgn(
  Point       pt,
  RgnHandle   rgn);


/*
 *  StdLine()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
StdLine(Point newPt);


/*
 *  OpenCPort()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  InitCPort()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  CloseCPort()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  NewPixMap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern PixMapHandle 
NewPixMap(void);


/*
 *  DisposePixMap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DisposePixMap(PixMapHandle pm);


/*
 *  CopyPixMap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
CopyPixMap(
  PixMapHandle   srcPM,
  PixMapHandle   dstPM);


/*
 *  NewPixPat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern PixPatHandle 
NewPixPat(void);


/*
 *  DisposePixPat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DisposePixPat(PixPatHandle pp);


/*
 *  CopyPixPat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
CopyPixPat(
  PixPatHandle   srcPP,
  PixPatHandle   dstPP);


/*
 *  PenPixPat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PenPixPat(PixPatHandle pp);


/*
 *  BackPixPat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
BackPixPat(PixPatHandle pp);


/*
 *  GetPixPat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern PixPatHandle 
GetPixPat(short patID);


/*
 *  MakeRGBPat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
MakeRGBPat(
  PixPatHandle      pp,
  const RGBColor *  myColor);


/*
 *  FillCRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FillCRect(
  const Rect *   r,
  PixPatHandle   pp);


/*
 *  FillCOval()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FillCOval(
  const Rect *   r,
  PixPatHandle   pp);


/*
 *  FillCRoundRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FillCRoundRect(
  const Rect *   r,
  short          ovalWidth,
  short          ovalHeight,
  PixPatHandle   pp);


/*
 *  FillCArc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FillCArc(
  const Rect *   r,
  short          startAngle,
  short          arcAngle,
  PixPatHandle   pp);


/*
 *  FillCRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FillCRgn(
  RgnHandle      rgn,
  PixPatHandle   pp);


/*
 *  FillCPoly()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FillCPoly(
  PolyHandle     poly,
  PixPatHandle   pp);


/*
 *  RGBForeColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
RGBForeColor(const RGBColor * color);


/*
 *  RGBBackColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
RGBBackColor(const RGBColor * color);


/*
 *  SetCPixel()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetCPixel(
  short             h,
  short             v,
  const RGBColor *  cPix);


/*
 *  SetPortPix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetPortPix(PixMapHandle pm);


/*
 *  GetCPixel()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetCPixel(
  short       h,
  short       v,
  RGBColor *  cPix);


/*
 *  GetForeColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetForeColor(RGBColor * color);


/*
 *  GetBackColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetBackColor(RGBColor * color);


/*
 *  SeedCFill()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SeedCFill(
  const BitMap *   srcBits,
  const BitMap *   dstBits,
  const Rect *     srcRect,
  const Rect *     dstRect,
  short            seedH,
  short            seedV,
  ColorSearchUPP   matchProc,
  long             matchData);


/*
 *  CalcCMask()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
CalcCMask(
  const BitMap *    srcBits,
  const BitMap *    dstBits,
  const Rect *      srcRect,
  const Rect *      dstRect,
  const RGBColor *  seedRGB,
  ColorSearchUPP    matchProc,
  long              matchData);


/*
 *  OpenCPicture()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern PicHandle 
OpenCPicture(const OpenCPicParams * newHeader);


/*
 *  OpColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
OpColor(const RGBColor * color);


/*
 *  HiliteColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
HiliteColor(const RGBColor * color);


/*
 *  DisposeCTable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DisposeCTable(CTabHandle cTable);


/*
 *  GetCTable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern CTabHandle 
GetCTable(short ctID);


/*
 *  GetCCursor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern CCrsrHandle 
GetCCursor(short crsrID);


/*
 *  SetCCursor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetCCursor(CCrsrHandle cCrsr);


/*
 *  AllocCursor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
AllocCursor(void);


/*
 *  DisposeCCursor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DisposeCCursor(CCrsrHandle cCrsr);


/* GetCIcon(), PlotCIcon(), and DisposeCIcon() moved to Icons.h*/

/*
 *  SetStdCProcs()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetStdCProcs(CQDProcs * procs);


/*
 *  GetMaxDevice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern GDHandle 
GetMaxDevice(const Rect * globalRect);


/*
 *  GetCTSeed()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
GetCTSeed(void);


/*
 *  GetDeviceList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern GDHandle 
GetDeviceList(void);


/*
 *  GetMainDevice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern GDHandle 
GetMainDevice(void);


/*
 *  GetNextDevice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern GDHandle 
GetNextDevice(GDHandle curDevice);


/*
 *  TestDeviceAttribute()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
TestDeviceAttribute(
  GDHandle   gdh,
  short      attribute);


/*
 *  SetDeviceAttribute()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetDeviceAttribute(
  GDHandle   gdh,
  short      attribute,
  Boolean    value);


/*
 *  InitGDevice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
InitGDevice(
  short      qdRefNum,
  long       mode,
  GDHandle   gdh);


/*
 *  NewGDevice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern GDHandle 
NewGDevice(
  short   refNum,
  long    mode);


/*
 *  DisposeGDevice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DisposeGDevice(GDHandle gdh);


/*
 *  SetGDevice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetGDevice(GDHandle gd);


/*
 *  GetGDevice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern GDHandle 
GetGDevice(void);


/*
 *  Color2Index()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
Color2Index(const RGBColor * myColor);


/*
 *  Index2Color()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
Index2Color(
  long        index,
  RGBColor *  aColor);


/*
 *  InvertColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
InvertColor(RGBColor * myColor);


/*
 *  RealColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
RealColor(const RGBColor * color);


/*
 *  GetSubTable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetSubTable(
  CTabHandle   myColors,
  short        iTabRes,
  CTabHandle   targetTbl);


/*
 *  MakeITable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
MakeITable(
  CTabHandle   cTabH,
  ITabHandle   iTabH,
  short        res);


/*
 *  AddSearch()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
AddSearch(ColorSearchUPP searchProc);


/*
 *  AddComp()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
AddComp(ColorComplementUPP compProc);


/*
 *  DelSearch()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DelSearch(ColorSearchUPP searchProc);


/*
 *  DelComp()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DelComp(ColorComplementUPP compProc);


/*
 *  SetClientID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetClientID(short id);


/*
 *  ProtectEntry()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ProtectEntry(
  short     index,
  Boolean   protect);


/*
 *  ReserveEntry()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ReserveEntry(
  short     index,
  Boolean   reserve);


/*
 *  SetEntries()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetEntries(
  short        start,
  short        count,
  CSpecArray   aTable);


/*
 *  SaveEntries()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SaveEntries(
  CTabHandle    srcTable,
  CTabHandle    resultTable,
  ReqListRec *  selection);


/*
 *  RestoreEntries()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
RestoreEntries(
  CTabHandle    srcTable,
  CTabHandle    dstTable,
  ReqListRec *  selection);


/*
 *  QDError()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
QDError(void);


/*
 *  CopyDeepMask()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
CopyDeepMask(
  const BitMap *  srcBits,
  const BitMap *  maskBits,
  const BitMap *  dstBits,
  const Rect *    srcRect,
  const Rect *    maskRect,
  const Rect *    dstRect,
  short           mode,
  RgnHandle       maskRgn);       /* can be NULL */


/*
 *  DeviceLoop()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DeviceLoop(
  RgnHandle              drawingRgn,
  DeviceLoopDrawingUPP   drawingProc,
  long                   userData,
  DeviceLoopFlags        flags);




/*
 *  GetMaskTable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Ptr 
GetMaskTable(void);



/*
 *  GetPattern()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern PatHandle 
GetPattern(short patternID);


/*
 *  [Mac]GetCursor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacGetCursor GetCursor
#endif
extern CursHandle 
MacGetCursor(short cursorID);


/*
 *  GetPicture()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern PicHandle 
GetPicture(short pictureID);


/*
 *  DeltaPoint()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
DeltaPoint(
  Point   ptA,
  Point   ptB);


/*
 *  ShieldCursor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ShieldCursor(
  const Rect *  shieldRect,
  Point         offsetPt);


/*
 *  ScreenRes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ScreenRes(
  short *  scrnHRes,
  short *  scrnVRes);


/*
 *  GetIndPattern()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetIndPattern(
  Pattern *  thePat,
  short      patternListID,
  short      index);


/*
 *  ptinrect()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  pt2rect()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  pttoangle()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  ptinrgn()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  addpt()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  subpt()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  equalpt()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  stuffhex()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  stdline()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  shieldcursor()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  deltapoint()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
deltapoint(
  Point *  ptA,
  Point *  ptB);


#if OLDROUTINENAMES
#define DisposPixMap(pm) DisposePixMap(pm)
#define DisposPixPat(pp) DisposePixPat(pp)
#define DisposCTable(cTable) DisposeCTable(cTable)
#define DisposCCursor(cCrsr) DisposeCCursor(cCrsr)
#define DisposGDevice(gdh) DisposeGDevice(gdh)
#endif  /* OLDROUTINENAMES */

/*
    From ToolUtils.i
*/
/*
 *  PackBits()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PackBits(
  Ptr *   srcPtr,
  Ptr *   dstPtr,
  short   srcBytes);


/*
 *  UnpackBits()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
UnpackBits(
  Ptr *   srcPtr,
  Ptr *   dstPtr,
  short   dstBytes);


/*
 *  SlopeFromAngle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Fixed 
SlopeFromAngle(short angle);


/*
 *  AngleFromSlope()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
AngleFromSlope(Fixed slope);


/* New transfer modes */
enum {
  colorXorXFer                  = 52,
  noiseXFer                     = 53,
  customXFer                    = 54
};

/* Custom XFer flags */
enum {
  kXFer1PixelAtATime            = 0x00000001, /* 1 pixel passed to custom XFer proc*/
  kXFerConvertPixelToRGB32      = 0x00000002 /* All color depths converted to 32 bit RGB*/
};

struct CustomXFerRec {
  UInt32              version;
  void *              srcPixels;
  void *              destPixels;
  void *              resultPixels;
  UInt32              refCon;
  UInt32              pixelSize;
  UInt32              pixelCount;
  Point               firstPixelHV;
  Rect                destBounds;
};
typedef struct CustomXFerRec            CustomXFerRec;
typedef CustomXFerRec *                 CustomXFerRecPtr;
typedef CALLBACK_API( void , CustomXFerProcPtr )(CustomXFerRecPtr info);
/*
 *  GetPortCustomXFerProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
GetPortCustomXFerProc(
  CGrafPtr             port,
  CustomXFerProcPtr *  proc,
  UInt32 *             flags,
  UInt32 *             refCon);


/*
 *  SetPortCustomXFerProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
SetPortCustomXFerProc(
  CGrafPtr            port,
  CustomXFerProcPtr   proc,
  UInt32              flags,
  UInt32              refCon);



enum {
  kCursorComponentsVersion      = 0x00010001
};

enum {
  kCursorComponentType          = 'curs'
};

/* Cursor Component capabilities flags */
enum {
  cursorDoesAnimate             = 1L << 0,
  cursorDoesHardware            = 1L << 1,
  cursorDoesUnreadableScreenBits = 1L << 2
};

/* Cursor Component output mode flags */
enum {
  kRenderCursorInHardware       = 1L << 0,
  kRenderCursorInSoftware       = 1L << 1
};

/* Cursor Component Info */
struct CursorInfo {
  long                version;                /* use kCursorComponentsVersion */
  long                capabilities;
  long                animateDuration;        /* approximate time between animate tickles */
  Rect                bounds;
  Point               hotspot;
  long                reserved;               /* must set to zero */

};
typedef struct CursorInfo               CursorInfo;
/* Cursor Component Selectors */
enum {
  kCursorComponentInit          = 0x0001,
  kCursorComponentGetInfo       = 0x0002,
  kCursorComponentSetOutputMode = 0x0003,
  kCursorComponentSetData       = 0x0004,
  kCursorComponentReconfigure   = 0x0005,
  kCursorComponentDraw          = 0x0006,
  kCursorComponentErase         = 0x0007,
  kCursorComponentMove          = 0x0008,
  kCursorComponentAnimate       = 0x0009,
  kCursorComponentLastReserved  = 0x0050
};

/*
 *  OpenCursorComponent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
OpenCursorComponent(
  Component            c,
  ComponentInstance *  ci);


/*
 *  CloseCursorComponent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
CloseCursorComponent(ComponentInstance ci);


/*
 *  SetCursorComponent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
SetCursorComponent(ComponentInstance ci);


/*
 *  CursorComponentChanged()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
CursorComponentChanged(ComponentInstance ci);


/*
 *  CursorComponentSetData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
CursorComponentSetData(
  ComponentInstance   ci,
  long                data);


/* Quickdraw-specific ColorSync matching */
/*
 *  CWMatchPixMap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
CWMatchPixMap(
  CMWorldRef            cw,
  PixMap *              myPixMap,
  CMBitmapCallBackUPP   progressProc,
  void *                refCon);


/*
 *  CWCheckPixMap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
CWCheckPixMap(
  CMWorldRef            cw,
  PixMap *              myPixMap,
  CMBitmapCallBackUPP   progressProc,
  void *                refCon,
  BitMap *              resultBitMap);


/*
 *  NCMBeginMatching()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
NCMBeginMatching(
  CMProfileRef   src,
  CMProfileRef   dst,
  CMMatchRef *   myRef);


/*
 *  CMEndMatching()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
CMEndMatching(CMMatchRef myRef);


/*
 *  NCMDrawMatchedPicture()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
NCMDrawMatchedPicture(
  PicHandle      myPicture,
  CMProfileRef   dst,
  Rect *         myRect);


/*
 *  CMEnableMatchingComment()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
CMEnableMatchingComment(Boolean enableIt);


/*
 *  NCMUseProfileComment()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
NCMUseProfileComment(
  CMProfileRef   prof,
  UInt32         flags);


/* Available in CarbonLib... */
/*
 *  IsValidPort()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
IsValidPort(CGrafPtr port);



/* GrafPort */
/* Getters */
/*
 *  GetPortPixMap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern PixMapHandle 
GetPortPixMap(CGrafPtr port);


/*
 *  GetPortBitMapForCopyBits()
 *  
 *  Discussion:
 *    GetPortBitMapForCopyBits is provided for the specific purpose of
 *    using the return value as a parameter to CopyBits. The return
 *    value can be used as the srcBits or dstBits parameter to CopyBits
 *    regardless of whether the port is color. If the port parameter is
 *    a color port, however, the returned BitMapPtr does not actually
 *    point to a BitMap; it points to the PixMapHandle and other fields
 *    in the CGrafPort structure. You should not dereference the
 *    BitMapPtr or otherwise depend on its contents unless you've
 *    confirmed that this port is a non-color port.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0.2 and later
 */
extern const BitMap * 
GetPortBitMapForCopyBits(CGrafPtr port);


/*
 *  GetPortBounds()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Rect * 
GetPortBounds(
  CGrafPtr   port,
  Rect *     rect);


/*
 *  GetPortForeColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern RGBColor * 
GetPortForeColor(
  CGrafPtr    port,
  RGBColor *  foreColor);


/*
 *  GetPortBackColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern RGBColor * 
GetPortBackColor(
  CGrafPtr    port,
  RGBColor *  backColor);


/*
 *  GetPortOpColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern RGBColor * 
GetPortOpColor(
  CGrafPtr    port,
  RGBColor *  opColor);


/*
 *  GetPortHiliteColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern RGBColor * 
GetPortHiliteColor(
  CGrafPtr    port,
  RGBColor *  hiliteColor);


/*
 *  GetPortGrafProcs()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern CQDProcsPtr 
GetPortGrafProcs(CGrafPtr port);


/*
 *  GetPortTextFont()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern short 
GetPortTextFont(CGrafPtr port);


/*
 *  GetPortTextFace()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Style 
GetPortTextFace(CGrafPtr port);


/*
 *  GetPortTextMode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern short 
GetPortTextMode(CGrafPtr port);


/*
 *  GetPortTextSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern short 
GetPortTextSize(CGrafPtr port);


/*
 *  GetPortChExtra()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern short 
GetPortChExtra(CGrafPtr port);


/*
 *  GetPortFracHPenLocation()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern short 
GetPortFracHPenLocation(CGrafPtr port);


/*
 *  GetPortSpExtra()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Fixed 
GetPortSpExtra(CGrafPtr port);


/*
 *  GetPortPenVisibility()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern short 
GetPortPenVisibility(CGrafPtr port);


/*
 *  GetPortVisibleRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern RgnHandle 
GetPortVisibleRegion(
  CGrafPtr    port,
  RgnHandle   visRgn);


/*
 *  GetPortClipRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern RgnHandle 
GetPortClipRegion(
  CGrafPtr    port,
  RgnHandle   clipRgn);


/*
 *  GetPortBackPixPat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern PixPatHandle 
GetPortBackPixPat(
  CGrafPtr       port,
  PixPatHandle   backPattern);


/*
 *  GetPortPenPixPat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern PixPatHandle 
GetPortPenPixPat(
  CGrafPtr       port,
  PixPatHandle   penPattern);


/*
 *  GetPortFillPixPat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern PixPatHandle 
GetPortFillPixPat(
  CGrafPtr       port,
  PixPatHandle   fillPattern);


/*
 *  GetPortPenSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Point * 
GetPortPenSize(
  CGrafPtr   port,
  Point *    penSize);


/*
 *  GetPortPenMode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern SInt32 
GetPortPenMode(CGrafPtr port);


/*
 *  GetPortPenLocation()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Point * 
GetPortPenLocation(
  CGrafPtr   port,
  Point *    penLocation);


/*
 *  IsPortRegionBeingDefined()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Boolean 
IsPortRegionBeingDefined(CGrafPtr port);


/*
 *  IsPortPictureBeingDefined()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Boolean 
IsPortPictureBeingDefined(CGrafPtr port);


/*
 *  IsPortPolyBeingDefined()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.3 and later
 */
extern Boolean 
IsPortPolyBeingDefined(CGrafPtr port);


/*
 *  IsPortOffscreen()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Boolean 
IsPortOffscreen(CGrafPtr port);


/*
 *  IsPortColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0.2 and later
 */
extern Boolean 
IsPortColor(CGrafPtr port);


/*
 *  IsPortVisibleRegionEmpty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
IsPortVisibleRegionEmpty(CGrafPtr port);


/*
 *  IsPortClipRegionEmpty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
IsPortClipRegionEmpty(CGrafPtr port);


/*
 *  SectRegionWithPortClipRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
SectRegionWithPortClipRegion(
  CGrafPtr    port,
  RgnHandle   ioRegion);


/*
 *  SectRegionWithPortVisibleRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
SectRegionWithPortVisibleRegion(
  CGrafPtr    port,
  RgnHandle   ioRegion);


/*
 *  SwapPortPicSaveHandle()
 *  
 *  Summary:
 *    Sets the port's picSave Handle, and returns the previous picSave
 *  
 *  Discussion:
 *    Historically, the picSave field in a GrafPort is != NULL if a
 *    Picture is being defined; and it has been documented that picture
 *    definition can be temporarily suspended by saving the current
 *    picSave Handle and setting picSave to NULL. Restoring the saved
 *    picSave Handle resumes picture definition.
 *  
 *  Parameters:
 *    
 *    port:
 *      The port whose picSave field is being swapped.
 *    
 *    inPicSaveHdl:
 *      The picSave Handle to be set.
 *  
 *  Result:
 *    The previous picSave Handle in the port.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern Handle 
SwapPortPicSaveHandle(
  CGrafPtr   port,
  Handle     inPicSaveHdl);


/* Setters */
/*
 *  SetPortBounds()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetPortBounds(
  CGrafPtr      port,
  const Rect *  rect);


/*
 *  SetPortOpColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetPortOpColor(
  CGrafPtr          port,
  const RGBColor *  opColor);


/*
 *  SetPortGrafProcs()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetPortGrafProcs(
  CGrafPtr    port,
  CQDProcs *  procs);


/*
 *  SetPortTextFont()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
SetPortTextFont(
  CGrafPtr   port,
  short      txFont);


/*
 *  SetPortTextSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
SetPortTextSize(
  CGrafPtr   port,
  short      txSize);


/*
 *  SetPortTextFace()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
SetPortTextFace(
  CGrafPtr         port,
  StyleParameter   face);


/*
 *  SetPortTextMode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
SetPortTextMode(
  CGrafPtr   port,
  short      mode);


/*
 *  SetPortVisibleRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetPortVisibleRegion(
  CGrafPtr    port,
  RgnHandle   visRgn);


/*
 *  SetPortClipRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetPortClipRegion(
  CGrafPtr    port,
  RgnHandle   clipRgn);


/*
 *  SetPortPenPixPat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetPortPenPixPat(
  CGrafPtr       port,
  PixPatHandle   penPattern);


/*
 *  SetPortFillPixPat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.2 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.2 and later
 */
extern void 
SetPortFillPixPat(
  CGrafPtr       port,
  PixPatHandle   penPattern);


/*
 *  SetPortBackPixPat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetPortBackPixPat(
  CGrafPtr       port,
  PixPatHandle   backPattern);


/*
 *  SetPortPenSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetPortPenSize(
  CGrafPtr   port,
  Point      penSize);


/*
 *  SetPortPenMode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetPortPenMode(
  CGrafPtr   port,
  SInt32     penMode);


/*
 *  SetPortFracHPenLocation()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetPortFracHPenLocation(
  CGrafPtr   port,
  short      pnLocHFrac);


/* PixMap */
/*
 *  GetPixBounds()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Rect * 
GetPixBounds(
  PixMapHandle   pixMap,
  Rect *         bounds);


/*
 *  GetPixDepth()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern short 
GetPixDepth(PixMapHandle pixMap);


/* QDGlobals */
/* Getters */
/*
 *  GetQDGlobalsRandomSeed()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern long 
GetQDGlobalsRandomSeed(void);


/*
 *  GetQDGlobalsScreenBits()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern BitMap * 
GetQDGlobalsScreenBits(BitMap * screenBits);


/*
 *  GetQDGlobalsArrow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Cursor * 
GetQDGlobalsArrow(Cursor * arrow);


/*
 *  GetQDGlobalsDarkGray()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Pattern * 
GetQDGlobalsDarkGray(Pattern * dkGray);


/*
 *  GetQDGlobalsLightGray()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Pattern * 
GetQDGlobalsLightGray(Pattern * ltGray);


/*
 *  GetQDGlobalsGray()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Pattern * 
GetQDGlobalsGray(Pattern * gray);


/*
 *  GetQDGlobalsBlack()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Pattern * 
GetQDGlobalsBlack(Pattern * black);


/*
 *  GetQDGlobalsWhite()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Pattern * 
GetQDGlobalsWhite(Pattern * white);


/*
 *  GetQDGlobalsThePort()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern CGrafPtr 
GetQDGlobalsThePort(void);


/* Setters */
/*
 *  SetQDGlobalsRandomSeed()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetQDGlobalsRandomSeed(long randomSeed);


/*
 *  SetQDGlobalsArrow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetQDGlobalsArrow(const Cursor * arrow);


/* Regions */
/*
 *  GetRegionBounds()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Rect * 
GetRegionBounds(
  RgnHandle   region,
  Rect *      bounds);


/*
 *  IsRegionRectangular()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Boolean 
IsRegionRectangular(RgnHandle region);


/* Utilities */
/* To prevent upward dependencies, GetWindowFromPort() is defined in Window Manager interface: */
/*      pascal WindowRef        GetWindowFromPort(CGrafPtr port); */
/* NewPtr/OpenCPort doesn't work with opaque structures */
/*
 *  CreateNewPort()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern CGrafPtr 
CreateNewPort(void);


/*
 *  DisposePort()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
DisposePort(CGrafPtr port);



/*
 *  SetQDError()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0.2 and later
 */
extern void 
SetQDError(OSErr err);


/*
   Routines available on Mac OS X to flush buffered window ports...
   These calls do nothing on Mac OS 8/9. QDIsPortBuffered will always return false there.
*/

/*
 *  QDIsPortBuffered()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
QDIsPortBuffered(CGrafPtr port);


/*
 *  QDIsPortBufferDirty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
QDIsPortBufferDirty(CGrafPtr port);


/*
 *  QDFlushPortBuffer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
QDFlushPortBuffer(
  CGrafPtr    port,
  RgnHandle   region);      /* can be NULL */


/*
 *  QDGetDirtyRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QDGetDirtyRegion(
  CGrafPtr    port,
  RgnHandle   rgn);


/*
 *  QDSetDirtyRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QDSetDirtyRegion(
  CGrafPtr    port,
  RgnHandle   rgn);


/*
 *  QDAddRectToDirtyRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QDAddRectToDirtyRegion(
  CGrafPtr      inPort,
  const Rect *  inBounds);


/*
 *  QDAddRegionToDirtyRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QDAddRegionToDirtyRegion(
  CGrafPtr    inPort,
  RgnHandle   inRegion);



/*
 *  CreateCGContextForPort()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateCGContextForPort(
  CGrafPtr        inPort,
  CGContextRef *  outContext);


/*
 *  ClipCGContextToRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ClipCGContextToRegion(
  CGContextRef   gc,
  const Rect *   portRect,
  RgnHandle      region);


/*
 *  SyncCGContextOriginWithPort()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SyncCGContextOriginWithPort(
  CGContextRef   inContext,
  CGrafPtr       port);


/*
 *  QDBeginCGContext()
 *  
 *  Summary:
 *    Allow CoreGraphics drawing in a CGrafPort
 *  
 *  Discussion:
 *    So far, CreateCGContextForPort() was used to create a CGContext
 *    for CG drawing from a CGrafPort. However, if the current port is
 *    a printing port, the CreateCGContextForPort fails; consequently,
 *    there was no way to mix Quickdraw and CoreGraphics drawing and
 *    still print it. If, instead, the CoreGraphics drawing is
 *    bracketed by QDBeginCGContext/QDEndCGContext calls, the drawing
 *    will also appear in print. There are some restrictions on the
 *    usage of QDBeginCGContext/QDEndCGContext:
 *    - Between QDBeginCGContext and QDEndCGContext, Quickdraw drawing
 *    is disabled; only CoreGraphics drawing is allowed
 *    - QDBeginCGContext/QDEndCGContext calls can not be nested
 *    - QDEndCGContext releases the CGContext returned from
 *    QDBeginCGContext and sets it to NULL.
 *  
 *  Parameters:
 *    
 *    inPort:
 *      The current port
 *    
 *    outContext:
 *      The CGContextRef to be used for CG drawing
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QDBeginCGContext(
  CGrafPtr        inPort,
  CGContextRef *  outContext);


/*
 *  QDEndCGContext()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QDEndCGContext(
  CGrafPtr        inPort,
  CGContextRef *  inoutContext);


/*
    The following routines are implemented in CarbonLib, and on Mac OS X in QD proper.
    They save the pixel data of a region in a packed format for quick save/restore 
    without using a lot of memory to do a large, hollow region, such as the region
    used when drag hiliting (which is where this is used).
*/

typedef struct OpaqueQDRegionBitsRef*   QDRegionBitsRef;
/*
 *  QDSaveRegionBits()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern QDRegionBitsRef 
QDSaveRegionBits(RgnHandle region);


/*
 *  QDRestoreRegionBits()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QDRestoreRegionBits(
  RgnHandle         region,
  QDRegionBitsRef   regionBits);


/*
 *  QDDisposeRegionBits()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QDDisposeRegionBits(QDRegionBitsRef regionBits);


/*
   Developers need a way to go from a CGDirectDisplay environment to Quickdraw.
   The following is equivalent to CreateNewPort(), but instead of taking the
   portPixMap from the current GDevice, it uses the GDevice corresponding to
   the CGSDisplayID passed in. If the CGSDisplayID is invalid, the mainDevice
   is used instead.
*/
/*
 *  CreateNewPortForCGDisplayID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern CGrafPtr 
CreateNewPortForCGDisplayID(UInt32 inCGDisplayID);


/*
   In Mac OS X, developers should be able to turn the WaitCursor (spinning wheel)
   on and off. QDDisplayWaitCursor() keeps track of nested calls.
   Passing FALSE will resume automatic wait cursor operation.
   Call this function only from an application in the foreground.
*/
/*
 *  QDDisplayWaitCursor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
QDDisplayWaitCursor(Boolean forceWaitCursor);


/*
 *  QDSetPatternOrigin()
 *  
 *  Summary:
 *    Sets the pattern origin for the current port.
 *  
 *  Discussion:
 *    When a QuickDraw drawing operation uses a pattern (either a
 *    black&white pattern or a PixPat), the pattern's image is aligned
 *    with port origin, modified by the pattern origin of the port. For
 *    example, if the background pattern is a 10x10 image, and a
 *    rectangle with coordinates (3, 3, 10, 10) is filled with that
 *    pattern, then only the bottom right 7x7 portion of the pattern
 *    image will be drawn into the rectangle. When drawing a pattern,
 *    QuickDraw always starts with the port origin and then adjusts it
 *    by the pattern origin to determine the actual origin point of
 *    pattern drawing. QDSetPatternOrigin can be used to set the
 *    pattern origin relative to the port origin. It is often used in
 *    conjuction with SetOrigin to maintain the pattern alignment at
 *    (0,0) in a window's content area, regardless of the port origin;
 *    for example, after changing the port's origin to (10,10), an
 *    application might change the port's pattern origin to (-10, -10)
 *    so that patterns are still aligned with the window's content area.
 *  
 *  Parameters:
 *    
 *    origin:
 *      The new pattern origin of the port.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in NQD 8.5 and later
 */
extern void 
QDSetPatternOrigin(Point origin);


/*
 *  QDGetPatternOrigin()
 *  
 *  Summary:
 *    Returns the pattern origin of the current port.
 *  
 *  Parameters:
 *    
 *    origin:
 *      On exit, contains the current port's pattern origin.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in NQD 8.5 and later
 */
extern void 
QDGetPatternOrigin(Point * origin);



/* 
    LowMem accessor functions previously in LowMem.h
*/
/*
 *  LMGetScrVRes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt16 
LMGetScrVRes(void);


/*
 *  LMSetScrVRes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetScrVRes(SInt16 value);


/*
 *  LMGetScrHRes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt16 
LMGetScrHRes(void);


/*
 *  LMSetScrHRes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetScrHRes(SInt16 value);


/*
 *  LMGetMainDevice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern GDHandle 
LMGetMainDevice(void);


/*
 *  LMSetMainDevice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetMainDevice(GDHandle value);


/*
 *  LMGetDeviceList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern GDHandle 
LMGetDeviceList(void);


/*
 *  LMSetDeviceList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetDeviceList(GDHandle value);


/*
 *  LMGetQDColors()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Handle 
LMGetQDColors(void);


/*
 *  LMSetQDColors()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetQDColors(Handle value);


/*
 *  LMGetWidthListHand()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Handle 
LMGetWidthListHand(void);


/*
 *  LMSetWidthListHand()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetWidthListHand(Handle value);


/*
 *  LMGetHiliteMode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern UInt8 
LMGetHiliteMode(void);


/*
 *  LMSetHiliteMode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetHiliteMode(UInt8 value);


/*
 *  LMGetWidthPtr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Ptr 
LMGetWidthPtr(void);


/*
 *  LMSetWidthPtr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetWidthPtr(Ptr value);


/*
 *  LMGetWidthTabHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Handle 
LMGetWidthTabHandle(void);


/*
 *  LMSetWidthTabHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetWidthTabHandle(Handle value);


/*
 *  LMGetLastSPExtra()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt32 
LMGetLastSPExtra(void);


/*
 *  LMSetLastSPExtra()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetLastSPExtra(SInt32 value);


/*
 *  LMGetLastFOND()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Handle 
LMGetLastFOND(void);


/*
 *  LMSetLastFOND()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetLastFOND(Handle value);


/*
 *  LMGetFractEnable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern UInt8 
LMGetFractEnable(void);


/*
 *  LMSetFractEnable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetFractEnable(UInt8 value);


/*
 *  LMGetTheGDevice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern GDHandle 
LMGetTheGDevice(void);


/*
 *  LMSetTheGDevice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetTheGDevice(GDHandle value);



/*
 *  LMGetHiliteRGB()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMGetHiliteRGB(RGBColor * hiliteRGBValue);


/*
 *  LMSetHiliteRGB()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetHiliteRGB(const RGBColor * hiliteRGBValue);


/*
 *  LMGetCursorNew()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern Boolean 
LMGetCursorNew(void);


/*
 *  LMSetCursorNew()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern void 
LMSetCursorNew(Boolean value);



















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

#endif /* __QUICKDRAW__ */

