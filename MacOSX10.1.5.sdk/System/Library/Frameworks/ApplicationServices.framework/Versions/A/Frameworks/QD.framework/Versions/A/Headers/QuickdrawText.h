/*
     File:       QD/QuickdrawText.h
 
     Contains:   Quickdraw Text Interfaces.
 
     Version:    Quickdraw-64.6.15~3
 
     Copyright:  © 1983-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __QUICKDRAWTEXT__
#define __QUICKDRAWTEXT__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __MIXEDMODE__
#include <CarbonCore/MixedMode.h>
#endif

#ifndef __INTLRESOURCES__
#include <CarbonCore/IntlResources.h>
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
  ByteCount   size);



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
NewStyleRunDirectionUPP(StyleRunDirectionProcPtr userRoutine);

/*
 *  DisposeStyleRunDirectionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeStyleRunDirectionUPP(StyleRunDirectionUPP userUPP);

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
  StyleRunDirectionUPP  userUPP);

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
  Point           denom);


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
  Point           denom);


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
  Point           denom);


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
  Point           denom);


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
  Point           denom);


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
  OffsetTable   offsets);


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
  long   textLength);


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
  Ptr                    dirParam);


/*
 *  TextFont()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TextFont(short font);


/*
 *  TextFace()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TextFace(StyleParameter face);


/*
 *  TextMode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TextMode(short mode);


/*
 *  TextSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
TextSize(short size);


/*
 *  SpaceExtra()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SpaceExtra(Fixed extra);


/*
 *  DrawChar()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DrawChar(CharParameter ch);


/*
 *  DrawString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DrawString(ConstStr255Param s);


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
  short         byteCount);


/*
 *  CharWidth()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
CharWidth(CharParameter ch);


/*
 *  StringWidth()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern short 
StringWidth(ConstStr255Param s);


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
  short         byteCount);


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
  void *        charLocs);


/*
 *  GetFontInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetFontInfo(FontInfo * info);


/*
 *  CharExtra()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
CharExtra(Fixed extra);


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
  Point         denom);


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
  FontInfo *    info);


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
  long *   textOffset);


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
  TruncCode   truncWhere);


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
  TruncCode   truncWhere);



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
  const Point *  denom);


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

#endif /* __QUICKDRAWTEXT__ */

