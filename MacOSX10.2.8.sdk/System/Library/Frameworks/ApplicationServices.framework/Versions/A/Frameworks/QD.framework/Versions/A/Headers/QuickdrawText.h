/*
     File:       QD/QuickdrawText.h
 
     Contains:   Quickdraw Text Interfaces.
 
     Version:    Quickdraw-96.21~1
 
     Copyright:  © 1983-2002 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __QUICKDRAWTEXT__
#define __QUICKDRAWTEXT__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif


#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

/* new CGrafPort bottleneck ("newProc2") function, used in Unicode Text drawing */
/*
 *  StandardGlyphs()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickDrawText 8.5 and later
 */
extern OSStatus 
StandardGlyphs(
  void *      dataStream,
  ByteCount   size)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



enum {
                                        /* CharToPixel directions */
  leftCaret                     = 0,    /*Place caret for left block*/
  rightCaret                    = -1,   /*Place caret for right block*/
  kHilite                       = 1     /*Direction is SysDirection*/
};

enum {
  smLeftCaret                   = 0,    /*Place caret for left block - obsolete */
  smRightCaret                  = -1,   /*Place caret for right block - obsolete */
  smHilite                      = 1     /*Direction is TESysJust - obsolete */
};

enum {
                                        /*Constants for styleRunPosition argument in PortionLine, DrawJustified, MeasureJustified, CharToPixel, and PixelToChar.*/
  onlyStyleRun                  = 0,    /* This is the only style run on the line */
  leftStyleRun                  = 1,    /* This is leftmost of multiple style runs on the line */
  rightStyleRun                 = 2,    /* This is rightmost of multiple style runs on the line */
  middleStyleRun                = 3,    /* There are multiple style runs on the line and this is neither the leftmost nor the rightmost. */
  smOnlyStyleRun                = 0,    /* obsolete */
  smLeftStyleRun                = 1,    /* obsolete */
  smRightStyleRun               = 2,    /* obsolete */
  smMiddleStyleRun              = 3     /* obsolete */
};

/* type for styleRunPosition parameter in PixelToChar etc. */
typedef short                           JustStyleCode;
/* Type for truncWhere parameter in TruncString, TruncText */
typedef short                           TruncCode;
enum {
                                        /* Constants for truncWhere argument in TruncString and TruncText */
  truncEnd                      = 0,    /* Truncate at end */
  truncMiddle                   = 0x4000, /* Truncate in middle */
  smTruncEnd                    = 0,    /* Truncate at end - obsolete */
  smTruncMiddle                 = 0x4000 /* Truncate in middle - obsolete */
};

enum {
                                        /* Constants for TruncString and TruncText results */
  notTruncated                  = 0,    /* No truncation was necessary */
  truncated                     = 1,    /* Truncation performed */
  truncErr                      = -1,   /* General error */
  smNotTruncated                = 0,    /* No truncation was necessary - obsolete */
  smTruncated                   = 1,    /* Truncation performed   - obsolete */
  smTruncErr                    = -1    /* General error - obsolete */
};

typedef SInt8                           StyledLineBreakCode;
enum {
  smBreakWord                   = 0,
  smBreakChar                   = 1,
  smBreakOverflow               = 2
};

/*QuickTime3.0*/
enum {
                                        /* Constants for txFlags (which used to be the pad field after txFace) */
  tfAntiAlias                   = 1 << 0,
  tfUnicode                     = 1 << 1
};


struct FontInfo {
  short               ascent;
  short               descent;
  short               widMax;
  short               leading;
};
typedef struct FontInfo                 FontInfo;

typedef short                           FormatOrder[1];
typedef FormatOrder *                   FormatOrderPtr;
/* FormatStatus was moved to TextUtils.i */
/* OffsetTable moved to IntlResources.i */

typedef CALLBACK_API( Boolean , StyleRunDirectionProcPtr )(short styleRunIndex, void *dirParam);
typedef STACK_UPP_TYPE(StyleRunDirectionProcPtr)                StyleRunDirectionUPP;
/*
 *  NewStyleRunDirectionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern StyleRunDirectionUPP
NewStyleRunDirectionUPP(StyleRunDirectionProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeStyleRunDirectionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeStyleRunDirectionUPP(StyleRunDirectionUPP userUPP)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeStyleRunDirectionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeStyleRunDirectionUPP(
  short                 styleRunIndex,
  void *                dirParam,
  StyleRunDirectionUPP  userUPP)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  Pixel2Char()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  Char2Pixel()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PixelToChar()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
PixelToChar(
  Ptr             textBuf,
  long            textLength,
  Fixed           slop,
  Fixed           pixelWidth,
  Boolean *       leadingEdge,
  Fixed *         widthRemaining,
  JustStyleCode   styleRunPosition,
  Point           numer,
  Point           denom)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CharToPixel()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
CharToPixel(
  Ptr             textBuf,
  long            textLength,
  Fixed           slop,
  long            offset,
  short           direction,
  JustStyleCode   styleRunPosition,
  Point           numer,
  Point           denom)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DrawJustified()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DrawJustified(
  Ptr             textPtr,
  long            textLength,
  Fixed           slop,
  JustStyleCode   styleRunPosition,
  Point           numer,
  Point           denom)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MeasureJustified()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
MeasureJustified(
  Ptr             textPtr,
  long            textLength,
  Fixed           slop,
  Ptr             charLocs,
  JustStyleCode   styleRunPosition,
  Point           numer,
  Point           denom)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PortionLine()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Fixed 
PortionLine(
  Ptr             textPtr,
  long            textLen,
  JustStyleCode   styleRunPosition,
  Point           numer,
  Point           denom)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  HiliteText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
HiliteText(
  Ptr           textPtr,
  short         textLength,
  short         firstOffset,
  short         secondOffset,
  OffsetTable   offsets)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DrawJust()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  MeasureJust()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PortionText()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  VisibleLength()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern long 
VisibleLength(
  Ptr    textPtr,
  long   textLength)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetFormatOrder()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetFormatOrder(
  FormatOrderPtr         ordering,
  short                  firstFormat,
  short                  lastFormat,
  Boolean                lineRight,
  StyleRunDirectionUPP   rlDirProc,
  Ptr                    dirParam)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TextFont()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TextFont(short font)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TextFace()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TextFace(StyleParameter face)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TextMode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TextMode(short mode)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TextSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TextSize(short size)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpaceExtra()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SpaceExtra(Fixed extra)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DrawChar()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DrawChar(CharParameter ch)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DrawString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DrawString(ConstStr255Param s)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  [Mac]DrawText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
#if TARGET_OS_MAC
    #define MacDrawText DrawText
#endif
extern void 
MacDrawText(
  const void *  textBuf,
  short         firstByte,
  short         byteCount)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CharWidth()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
CharWidth(CharParameter ch)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  StringWidth()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
StringWidth(ConstStr255Param s)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TextWidth()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
TextWidth(
  const void *  textBuf,
  short         firstByte,
  short         byteCount)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MeasureText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
MeasureText(
  short         count,
  const void *  textAddr,
  void *        charLocs)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetFontInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetFontInfo(FontInfo * info)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CharExtra()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
CharExtra(Fixed extra)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  StdText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
StdText(
  short         count,
  const void *  textAddr,
  Point         numer,
  Point         denom)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  StdTxMeas()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
StdTxMeas(
  short         byteCount,
  const void *  textAddr,
  Point *       numer,
  Point *       denom,
  FontInfo *    info)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  StyledLineBreak()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern StyledLineBreakCode 
StyledLineBreak(
  Ptr      textPtr,
  long     textLen,
  long     textStart,
  long     textEnd,
  long     flags,
  Fixed *  textWidth,
  long *   textOffset)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TruncString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
TruncString(
  short       width,
  Str255      theString,
  TruncCode   truncWhere)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TruncText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
TruncText(
  short       width,
  Ptr         textPtr,
  short *     length,
  TruncCode   truncWhere)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  drawstring()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  stringwidth()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  stdtext()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
stdtext(
  short          count,
  const void *   textAddr,
  const Point *  numer,
  const Point *  denom)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SwapQDTextFlags()
 *  
 *  Discussion:
 *    Obsolete. Use QDSwapTextFlags instead (in Quickdraw.h).
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern UInt32 
SwapQDTextFlags(UInt32 newFlags)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



#if OLDROUTINENAMES
#define NPixel2Char(textBuf, textLen, slop, pixelWidth, leadingEdge, widthRemaining, styleRunPosition, numer, denom) \
    PixelToChar(textBuf, textLen, slop, pixelWidth, leadingEdge, widthRemaining, styleRunPosition, numer, denom) 
#define NChar2Pixel(textBuf, textLen, slop, offset, direction, styleRunPosition, numer, denom) \
    CharToPixel(textBuf, textLen, slop, offset, direction, styleRunPosition, numer, denom)
#define NDrawJust(textPtr, textLength, slop, styleRunPosition, numer, denom) \
    DrawJustified(textPtr, textLength, slop, styleRunPosition, numer, denom)
#define NMeasureJust(textPtr, textLength, slop, charLocs, styleRunPosition, numer, denom) \
    MeasureJustified(textPtr, textLength, slop, charLocs, styleRunPosition, numer, denom)
#define NPortionText(textPtr, textLen, styleRunPosition, numer, denom)\
    PortionLine(textPtr, textLen, styleRunPosition, numer, denom)
#endif  /* OLDROUTINENAMES */


#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __QUICKDRAWTEXT__ */

