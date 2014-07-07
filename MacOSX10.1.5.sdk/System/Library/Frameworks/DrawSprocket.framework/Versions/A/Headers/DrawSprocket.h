/*
     File:       DrawSprocket/DrawSprocket.h
 
     Contains:   Games Sprockets: DrawSprocket interfaces
 
     Version:    DrawSprocket-2.0.33~1
 
     Copyright:  © 1999-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __DRAWSPROCKET__
#define __DRAWSPROCKET__

#ifndef __CARBON__
#include <Carbon/Carbon.h>
#endif



#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if PRAGMA_STRUCT_ALIGN
    #pragma options align=power
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

#if PRAGMA_ENUM_ALWAYSINT
    #if defined(__fourbyteints__) && !__fourbyteints__ 
        #define __DRAWSPROCKET__RESTORE_TWOBYTEINTS
        #pragma fourbyteints on
    #endif
    #pragma enumsalwaysint on
#elif PRAGMA_ENUM_OPTIONS
    #pragma option enum=int
#elif PRAGMA_ENUM_PACK
    #if __option(pack_enums)
        #define __DRAWSPROCKET__RESTORE_PACKED_ENUMS
        #pragma options(!pack_enums)
    #endif
#endif

/*
********************************************************************************
** constants
********************************************************************************
*/

enum DSpDepthMask {
  kDSpDepthMask_1               = 1 << 0,
  kDSpDepthMask_2               = 1 << 1,
  kDSpDepthMask_4               = 1 << 2,
  kDSpDepthMask_8               = 1 << 3,
  kDSpDepthMask_16              = 1 << 4,
  kDSpDepthMask_32              = 1 << 5,
  kDSpDepthMask_All             = -1L
};
typedef enum DSpDepthMask DSpDepthMask;


enum DSpColorNeeds {
  kDSpColorNeeds_DontCare       = 0L,
  kDSpColorNeeds_Request        = 1L,
  kDSpColorNeeds_Require        = 2L
};
typedef enum DSpColorNeeds DSpColorNeeds;


enum DSpContextState {
  kDSpContextState_Active       = 0L,
  kDSpContextState_Paused       = 1L,
  kDSpContextState_Inactive     = 2L
};
typedef enum DSpContextState DSpContextState;

/* kDSpContextOption_QD3DAccel not yet implemented */

enum DSpContextOption {
                                        /*    kDSpContextOption_QD3DAccel       = 1<<0,*/
  kDSpContextOption_PageFlip    = 1 << 1,
  kDSpContextOption_DontSyncVBL = 1 << 2,
  kDSpContextOption_Stereoscopic = 1 << 3
};
typedef enum DSpContextOption DSpContextOption;


enum DSpAltBufferOption {
  kDSpAltBufferOption_RowBytesEqualsWidth = 1 << 0
};
typedef enum DSpAltBufferOption DSpAltBufferOption;


enum DSpBufferKind {
  kDSpBufferKind_Normal         = 0
};
typedef enum DSpBufferKind DSpBufferKind;


enum DSpBlitMode {
  kDSpBlitMode_Plain            = 0,
  kDSpBlitMode_SrcKey           = 1 << 0,
  kDSpBlitMode_DstKey           = 1 << 1,
  kDSpBlitMode_Interpolation    = 1 << 2
};
typedef enum DSpBlitMode DSpBlitMode;

/*
********************************************************************************
** data types
********************************************************************************
*/
typedef struct OpaqueDSpAltBufferReference*  DSpAltBufferReference;
typedef struct OpaqueDSpContextReference*  DSpContextReference;
typedef const struct OpaqueDSpContextReference*  DSpContextReferenceConst;
#define kDSpEveryContext ((DSpContextReference)NULL)
typedef CALLBACK_API_C( Boolean , DSpEventProcPtr )(EventRecord * inEvent);
typedef CALLBACK_API_C( Boolean , DSpCallbackProcPtr )(DSpContextReference inContext, void *inRefCon);
typedef STACK_UPP_TYPE(DSpEventProcPtr)                         DSpEventUPP;
typedef STACK_UPP_TYPE(DSpCallbackProcPtr)                      DSpCallbackUPP;
/*
 *  NewDSpEventUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  NewDSpCallbackUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  DisposeDSpEventUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  DisposeDSpCallbackUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  InvokeDSpEventUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  InvokeDSpCallbackUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

struct DSpContextAttributes {
  Fixed               frequency;
  UInt32              displayWidth;
  UInt32              displayHeight;
  UInt32              reserved1;
  UInt32              reserved2;
  UInt32              colorNeeds;
  CTabHandle          colorTable;
  OptionBits          contextOptions;
  OptionBits          backBufferDepthMask;
  OptionBits          displayDepthMask;
  UInt32              backBufferBestDepth;
  UInt32              displayBestDepth;
  UInt32              pageCount;
  char                filler[3];
  Boolean             gameMustConfirmSwitch;
  UInt32              reserved3[4];
};
typedef struct DSpContextAttributes     DSpContextAttributes;
typedef DSpContextAttributes *          DSpContextAttributesPtr;
struct DSpAltBufferAttributes {
  UInt32              width;
  UInt32              height;
  DSpAltBufferOption  options;
  UInt32              reserved[4];
};
typedef struct DSpAltBufferAttributes   DSpAltBufferAttributes;
typedef struct DSpBlitInfo              DSpBlitInfo;
typedef CALLBACK_API_C( void , DSpBlitDoneProc )(DSpBlitInfo * info);
struct DSpBlitInfo {
  Boolean             completionFlag;
  char                filler[3];
  DSpBlitDoneProc     completionProc;
  DSpContextReference  srcContext;
  CGrafPtr            srcBuffer;
  Rect                srcRect;
  UInt32              srcKey;

  DSpContextReference  dstContext;
  CGrafPtr            dstBuffer;
  Rect                dstRect;
  UInt32              dstKey;

  DSpBlitMode         mode;
  UInt32              reserved[4];
};


typedef DSpBlitInfo *                   DSpBlitInfoPtr;
/*
********************************************************************************
** function prototypes
********************************************************************************
*/

/*
** global operations
*/
/*
 *  DSpStartup()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */
extern OSStatus 
DSpStartup(void);


/*
 *  DSpShutdown()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */
extern OSStatus 
DSpShutdown(void);


/*
 *  DSpGetVersion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.7 and later
 */
extern NumVersion 
DSpGetVersion(void);


/*
 *  DSpGetFirstContext()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */
extern OSStatus 
DSpGetFirstContext(
  DisplayIDType          inDisplayID,
  DSpContextReference *  outContext);


/*
 *  DSpGetNextContext()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */
extern OSStatus 
DSpGetNextContext(
  DSpContextReference    inCurrentContext,
  DSpContextReference *  outContext);


/*
 *  DSpGetCurrentContext()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.7 and later
 */
extern OSStatus 
DSpGetCurrentContext(
  DisplayIDType          inDisplayID,
  DSpContextReference *  outContext);


/*
 *  DSpFindBestContext()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */
extern OSStatus 
DSpFindBestContext(
  DSpContextAttributesPtr   inDesiredAttributes,
  DSpContextReference *     outContext);


/*
 *  DSpFindBestContextOnDisplayID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.7 and later
 */
extern OSStatus 
DSpFindBestContextOnDisplayID(
  DSpContextAttributesPtr   inDesiredAttributes,
  DSpContextReference *     outContext,
  DisplayIDType             inDisplayID);


/*
 *  DSpCanUserSelectContext()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */


/*
 *  DSpUserSelectContext()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */


/*
 *  DSpProcessEvent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */
extern OSStatus 
DSpProcessEvent(
  EventRecord *  inEvent,
  Boolean *      outEventWasProcessed);


/*
 *  DSpSetBlankingColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */
extern OSStatus 
DSpSetBlankingColor(const RGBColor * inRGBColor);


/*
 *  DSpSetDebugMode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */
extern OSStatus 
DSpSetDebugMode(Boolean inDebugMode);


/*
 *  DSpFindContextFromPoint()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */
extern OSStatus 
DSpFindContextFromPoint(
  Point                  inGlobalPoint,
  DSpContextReference *  outContext);


/*
 *  DSpGetMouse()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */
extern OSStatus 
DSpGetMouse(Point * outGlobalPoint);


/*
** alternate buffer operations
*/
/*
 *  DSpAltBuffer_New()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */


/*
 *  DSpAltBuffer_Dispose()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */


/*
 *  DSpAltBuffer_InvalRect()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */


/*
 *  DSpAltBuffer_GetCGrafPtr()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */


/*
** context operations
*/
/* general */
/*
 *  DSpContext_GetAttributes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */
extern OSStatus 
DSpContext_GetAttributes(
  DSpContextReferenceConst   inContext,
  DSpContextAttributesPtr    outAttributes);


/*
 *  DSpContext_Reserve()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */
extern OSStatus 
DSpContext_Reserve(
  DSpContextReference       inContext,
  DSpContextAttributesPtr   inDesiredAttributes);


/*
 *  DSpContext_Queue()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.7 and later
 */
extern OSStatus 
DSpContext_Queue(
  DSpContextReference       inParentContext,
  DSpContextReference       inChildContext,
  DSpContextAttributesPtr   inDesiredAttributes);


/*
 *  DSpContext_Switch()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.7 and later
 */
extern OSStatus 
DSpContext_Switch(
  DSpContextReference   inOldContext,
  DSpContextReference   inNewContext);


/*
 *  DSpContext_Release()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */
extern OSStatus 
DSpContext_Release(DSpContextReference inContext);


/*
 *  DSpContext_Dispose()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
DSpContext_Dispose(DSpContextReference inContext);


/*
 *  DSpContext_GetDisplayID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */
extern OSStatus 
DSpContext_GetDisplayID(
  DSpContextReferenceConst   inContext,
  DisplayIDType *            outDisplayID);


/*
 *  DSpContext_GlobalToLocal()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */
extern OSStatus 
DSpContext_GlobalToLocal(
  DSpContextReferenceConst   inContext,
  Point *                    ioPoint);


/*
 *  DSpContext_LocalToGlobal()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */
extern OSStatus 
DSpContext_LocalToGlobal(
  DSpContextReferenceConst   inContext,
  Point *                    ioPoint);


/*
 *  DSpContext_SetVBLProc()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */


/*
 *  DSpContext_GetFlattenedSize()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */


/*
 *  DSpContext_Flatten()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */


/*
 *  DSpContext_Restore()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */


/*
 *  DSpContext_GetMonitorFrequency()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */
extern OSStatus 
DSpContext_GetMonitorFrequency(
  DSpContextReferenceConst   inContext,
  Fixed *                    outFrequency);


/*
 *  DSpContext_SetMaxFrameRate()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */


/*
 *  DSpContext_GetMaxFrameRate()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */


/*
 *  DSpContext_SetState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */
extern OSStatus 
DSpContext_SetState(
  DSpContextReference   inContext,
  DSpContextState       inState);


/*
 *  DSpContext_GetState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */
extern OSStatus 
DSpContext_GetState(
  DSpContextReferenceConst   inContext,
  DSpContextState *          outState);


/*
 *  DSpContext_IsBusy()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */
extern OSStatus 
DSpContext_IsBusy(
  DSpContextReferenceConst   inContext,
  Boolean *                  outBusyFlag);


/* dirty rectangles */
/*
 *  DSpContext_SetDirtyRectGridSize()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */


/*
 *  DSpContext_GetDirtyRectGridSize()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */


/*
 *  DSpContext_GetDirtyRectGridUnits()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */


/*
 *  DSpContext_InvalBackBufferRect()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */


/* underlays */
/*
 *  DSpContext_SetUnderlayAltBuffer()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */


/*
 *  DSpContext_GetUnderlayAltBuffer()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */


/* gamma */
/*
 *  DSpContext_FadeGammaOut()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */
extern OSStatus 
DSpContext_FadeGammaOut(
  DSpContextReference   inContext,
  RGBColor *            inZeroIntensityColor);


/*
 *  DSpContext_FadeGammaIn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */
extern OSStatus 
DSpContext_FadeGammaIn(
  DSpContextReference   inContext,
  RGBColor *            inZeroIntensityColor);


/*
 *  DSpContext_FadeGamma()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */
extern OSStatus 
DSpContext_FadeGamma(
  DSpContextReference   inContext,
  SInt32                inPercentOfOriginalIntensity,
  RGBColor *            inZeroIntensityColor);


/* buffering */
/*
 *  DSpContext_SwapBuffers()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */
extern OSStatus 
DSpContext_SwapBuffers(
  DSpContextReference   inContext,
  DSpCallbackUPP        inBusyProc,
  void *                inUserRefCon);


/*
 *  DSpContext_GetBackBuffer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */
extern OSStatus 
DSpContext_GetBackBuffer(
  DSpContextReference   inContext,
  DSpBufferKind         inBufferKind,
  CGrafPtr *            outBackBuffer);


/*
 *  DSpContext_GetFrontBuffer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.1 and later
 */
extern OSStatus 
DSpContext_GetFrontBuffer(
  DSpContextReferenceConst   inContext,
  CGrafPtr *                 outFrontBuffer);


/* clut operations */
/*
 *  DSpContext_SetCLUTEntries()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */
extern OSStatus 
DSpContext_SetCLUTEntries(
  DSpContextReference   inContext,
  const ColorSpec *     inEntries,
  UInt16                inStartingEntry,
  UInt16                inLastEntry);


/*
 *  DSpContext_GetCLUTEntries()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in DrawSprocket.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.0 and later
 */
extern OSStatus 
DSpContext_GetCLUTEntries(
  DSpContextReferenceConst   inContext,
  ColorSpec *                outEntries,
  UInt16                     inStartingEntry,
  UInt16                     inLastEntry);


/* blit operations */
/*
 *  DSpBlit_Faster()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.1 and later
 */


/*
 *  DSpBlit_Fastest()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in DrawSprocketLib 1.1 and later
 */




#if PRAGMA_ENUM_ALWAYSINT
    #pragma enumsalwaysint reset
    #ifdef __DRAWSPROCKET__RESTORE_TWOBYTEINTS
        #pragma fourbyteints off
    #endif
#elif PRAGMA_ENUM_OPTIONS
    #pragma option enum=reset
#elif defined(__DRAWSPROCKET__RESTORE_PACKED_ENUMS)
    #pragma options(pack_enums)
#endif

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

#endif /* __DRAWSPROCKET__ */

