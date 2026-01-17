/*
     File:       QD/Quickdraw.h
 
     Contains:   Interface to Quickdraw Graphics
 
     Version:    Quickdraw-282~3
 
     Copyright:  © 1985-2008 by Apple, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __QUICKDRAW__
#define __QUICKDRAW__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __COREGRAPHICS__
#include <CoreGraphics/CoreGraphics.h>
#endif

#ifndef __MIXEDMODE__
#include <CarbonCore/MixedMode.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 2)

#define QD_HEADERS_ARE_PRIVATE 1
typedef struct OpaqueGrafPtr*           GrafPtr;
typedef GrafPtr                         CGrafPtr;
typedef CGrafPtr                        GWorldPtr;
typedef short                           QDErr;
typedef unsigned long                   GWorldFlags;
/* For the convenience of QuickTime */
enum {
  srcCopy                       = 0
};

/* needed in ImageCompression.h */
/* Needed in HIServices/Icons.i */
struct BitMap {
  Ptr                 baseAddr;
  short               rowBytes;
  Rect                bounds;
};
typedef struct BitMap                   BitMap;
typedef BitMap *                        BitMapPtr;
typedef BitMapPtr *                     BitMapHandle;
struct RGBColor {
  unsigned short      red;
  unsigned short      green;
  unsigned short      blue;
};
typedef struct RGBColor                 RGBColor;
struct ColorSpec {
  short               value;
  RGBColor            rgb;
};
typedef struct ColorSpec                ColorSpec;
typedef ColorSpec *                     ColorSpecPtr;
typedef ColorSpec                       CSpecArray[1];
struct ColorTable {
  SInt32              ctSeed;
  short               ctFlags;
  short               ctSize;
  CSpecArray          ctTable;
};
typedef struct ColorTable               ColorTable;
typedef ColorTable *                    CTabPtr;
typedef CTabPtr *                       CTabHandle;
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

#define GETPIXMAPPIXELFORMAT(pm)   ( ((pm)->pixelFormat != 0) ? (UInt32)(pm)->pixelFormat : (UInt32)(pm)->pixelSize )

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


struct Pattern {
  UInt8               pat[8];
};
typedef struct Pattern                  Pattern;
typedef Pattern *                       PatPtr;
typedef PatPtr *                        PatHandle;
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
typedef struct OpaqueRgnHandle*         RgnHandle;
typedef struct GDevice                  GDevice;
typedef GDevice *                       GDPtr;
typedef GDPtr *                         GDHandle;
struct GDevice {
  short               gdRefNum;               /*driver's unit number*/
  short               gdID;                   /*client ID for search procs*/
  short               gdType;                 /*fixed/CLUT/direct*/
  Handle              gdITable;               /*Handle to inverse lookup table*/
  short               gdResPref;              /*preferred resolution of GDITable*/
  Handle              gdSearchProc;           /*search proc list head*/
  Handle              gdCompProc;             /*complement proc list*/
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

struct Picture {
  short               picSize;
  Rect                picFrame;
};
typedef struct Picture                  Picture;
typedef Picture *                       PicPtr;
typedef PicPtr *                        PicHandle;
struct OpenCPicParams {
  Rect                srcRect;
  Fixed               hRes;
  Fixed               vRes;
  short               version;
  short               reserved1;
  SInt32              reserved2;
};
typedef struct OpenCPicParams           OpenCPicParams;
struct FontInfo {
  short               ascent;
  short               descent;
  short               widMax;
  short               leading;
};
typedef struct FontInfo                 FontInfo;

typedef SInt32                          QDRegionParseDirection;
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
NewRegionToRectsUPP(RegionToRectsProcPtr userRoutine)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeRegionToRectsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeRegionToRectsUPP(RegionToRectsUPP userUPP)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

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
  RegionToRectsUPP  userUPP)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

#if __MACH__
  #ifdef __cplusplus
    inline RegionToRectsUPP                                     NewRegionToRectsUPP(RegionToRectsProcPtr userRoutine) { return userRoutine; }
    inline void                                                 DisposeRegionToRectsUPP(RegionToRectsUPP) { }
    inline OSStatus                                             InvokeRegionToRectsUPP(UInt16 message, RgnHandle rgn, const Rect * rect, void * refCon, RegionToRectsUPP userUPP) { return (*userUPP)(message, rgn, rect, refCon); }
  #else
    #define NewRegionToRectsUPP(userRoutine)                    ((RegionToRectsUPP)userRoutine)
    #define DisposeRegionToRectsUPP(userUPP)
    #define InvokeRegionToRectsUPP(message, rgn, rect, refCon, userUPP) (*userUPP)(message, rgn, rect, refCon)
  #endif
#endif

#if !__LP64__
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
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework [32-bit only]
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QDBeginCGContext(
  CGrafPtr        inPort,
  CGContextRef *  outContext)                                 AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  QDEndCGContext()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework [32-bit only]
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QDEndCGContext(
  CGrafPtr        inPort,
  CGContextRef *  inoutContext)                               AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;



/* TruncCode is needed in Appearance.h for TruncateThemeText */
#endif  /* !__LP64__ */

typedef short                           TruncCode;
/* DragConstraint is needed in Controls.h */
typedef UInt16                          DragConstraint;
enum {
  kNoConstraint                 = 0,
  kVerticalConstraint           = 1,
  kHorizontalConstraint         = 2
};



typedef CALLBACK_API( void , DragGrayRgnProcPtr )(void);
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

/*
 *  This set of definitions "belongs" in MacWindows.
 *  But, there is a circularity in the headers where MacWindows includes Controls
 *  and Controls includes MacWindows. To break the circle, the information
 *  needed by Controls is moved from MacWindows to Quickdraw.
 */
typedef struct OpaqueWindowPtr*         WindowPtr;
typedef struct OpaqueDialogPtr*         DialogPtr;
typedef WindowPtr                       WindowRef;
/*
 * Something for Quickdraw.r (needed by Icons.r etc. in HIToolbox):
 */



/* Temporary, until QuickTime resolves rdar://7359491 */
struct VDGammaRecord {
  Ptr                 csGTable;               /*pointer to gamma table*/
};
typedef struct VDGammaRecord            VDGammaRecord;
typedef VDGammaRecord *                 VDGamRecPtr;
/* CQDProcs needed by QTKit.framework/.../QTUtilities_Private.h */
/* CQDProcs requires all the following */
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
typedef SInt8                           GrafVerb;
typedef SInt32                          PrinterStatusOpcode;
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
typedef CALLBACK_API_C( OSStatus , QDPrinterStatusProcPtr )(PrinterStatusOpcode opcode, CGrafPtr currentPort, void *printerStatus);
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
typedef STACK_UPP_TYPE(QDPrinterStatusProcPtr)                  QDPrinterStatusUPP;
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
 *  NewQDPrinterStatusUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QDPrinterStatusUPP
NewQDPrinterStatusUPP(QDPrinterStatusProcPtr userRoutine)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

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
 *  DisposeQDPrinterStatusUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQDPrinterStatusUPP(QDPrinterStatusUPP userUPP)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

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

/*
 *  InvokeQDPrinterStatusUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeQDPrinterStatusUPP(
  PrinterStatusOpcode  opcode,
  CGrafPtr             currentPort,
  void *               printerStatus,
  QDPrinterStatusUPP   userUPP)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

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
    inline QDPrinterStatusUPP                                   NewQDPrinterStatusUPP(QDPrinterStatusProcPtr userRoutine) { return userRoutine; }
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
    inline void                                                 DisposeQDPrinterStatusUPP(QDPrinterStatusUPP) { }
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
    inline OSStatus                                             InvokeQDPrinterStatusUPP(PrinterStatusOpcode opcode, CGrafPtr currentPort, void * printerStatus, QDPrinterStatusUPP userUPP) { return (*userUPP)(opcode, currentPort, printerStatus); }
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
    #define NewQDPrinterStatusUPP(userRoutine)                  ((QDPrinterStatusUPP)userRoutine)
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
    #define DisposeQDPrinterStatusUPP(userUPP)
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
    #define InvokeQDPrinterStatusUPP(opcode, currentPort, printerStatus, userUPP) (*userUPP)(opcode, currentPort, printerStatus)
  #endif
#endif

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
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Temporary until HIToolbox gets fixed */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
struct GrafPort {
  short               whatever[87];
};
typedef struct GrafPort                 GrafPort;
typedef GrafPort                        CGrafPort;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif /* __QUICKDRAW__ */

