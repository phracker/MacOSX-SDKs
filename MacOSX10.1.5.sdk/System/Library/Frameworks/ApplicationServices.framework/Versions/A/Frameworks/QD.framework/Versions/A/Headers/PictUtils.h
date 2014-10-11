/*
     File:       QD/PictUtils.h
 
     Contains:   Picture Utilities Interfaces.
 
     Version:    Quickdraw-64.6.15~3
 
     Copyright:  © 1990-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __PICTUTILS__
#define __PICTUTILS__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __PALETTES__
#include <QD/Palettes.h>
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

/* verbs for the GetPictInfo, GetPixMapInfo, and NewPictInfo calls */
enum {
  returnColorTable              = 0x0001,
  returnPalette                 = 0x0002,
  recordComments                = 0x0004,
  recordFontInfo                = 0x0008,
  suppressBlackAndWhite         = 0x0010
};

enum {
                                        /* color pick methods */
  systemMethod                  = 0,    /* system color pick method */
  popularMethod                 = 1,    /* method that chooses the most popular set of colors */
  medianMethod                  = 2     /* method that chooses a good average mix of colors */
};

enum {
                                        /* color bank types */
  ColorBankIsCustom             = -1,
  ColorBankIsExactAnd555        = 0,
  ColorBankIs555                = 1
};

typedef long                            PictInfoID;
struct CommentSpec {
  short               count;                  /* number of occurrances of this comment ID */
  short               ID;                     /* ID for the comment in the picture */
};
typedef struct CommentSpec              CommentSpec;
typedef CommentSpec *                   CommentSpecPtr;
typedef CommentSpecPtr *                CommentSpecHandle;
struct FontSpec {
  short               pictFontID;             /* ID of the font in the picture */
  short               sysFontID;              /* ID of the same font in the current system file */
  long                size[4];                /* bit array of all the sizes found (1..127) (bit 0 means > 127) */
  short               style;                  /* combined style of all occurrances of the font */
  long                nameOffset;             /* offset into the fontNamesHdl handle for the font’s name */
};
typedef struct FontSpec                 FontSpec;
typedef FontSpec *                      FontSpecPtr;
typedef FontSpecPtr *                   FontSpecHandle;
struct PictInfo {
  short               version;                /* this is always zero, for now */
  long                uniqueColors;           /* the number of actual colors in the picture(s)/pixmap(s) */
  PaletteHandle       thePalette;             /* handle to the palette information */
  CTabHandle          theColorTable;          /* handle to the color table */
  Fixed               hRes;                   /* maximum horizontal resolution for all the pixmaps */
  Fixed               vRes;                   /* maximum vertical resolution for all the pixmaps */
  short               depth;                  /* maximum depth for all the pixmaps (in the picture) */
  Rect                sourceRect;             /* the picture frame rectangle (this contains the entire picture) */
  long                textCount;              /* total number of text strings in the picture */
  long                lineCount;              /* total number of lines in the picture */
  long                rectCount;              /* total number of rectangles in the picture */
  long                rRectCount;             /* total number of round rectangles in the picture */
  long                ovalCount;              /* total number of ovals in the picture */
  long                arcCount;               /* total number of arcs in the picture */
  long                polyCount;              /* total number of polygons in the picture */
  long                regionCount;            /* total number of regions in the picture */
  long                bitMapCount;            /* total number of bitmaps in the picture */
  long                pixMapCount;            /* total number of pixmaps in the picture */
  long                commentCount;           /* total number of comments in the picture */
  long                uniqueComments;         /* the number of unique comments in the picture */
  CommentSpecHandle   commentHandle;          /* handle to all the comment information */
  long                uniqueFonts;            /* the number of unique fonts in the picture */
  FontSpecHandle      fontHandle;             /* handle to the FontSpec information */
  Handle              fontNamesHandle;        /* handle to the font names */
  long                reserved1;
  long                reserved2;
};
typedef struct PictInfo                 PictInfo;
typedef PictInfo *                      PictInfoPtr;
typedef PictInfoPtr *                   PictInfoHandle;
typedef CALLBACK_API( OSErr , InitPickMethodProcPtr )(SInt16 colorsRequested, UInt32 *dataRef, SInt16 *colorBankType);
typedef CALLBACK_API( OSErr , RecordColorsProcPtr )(UInt32 dataRef, RGBColor *colorsArray, SInt32 colorCount, SInt32 *uniqueColors);
typedef CALLBACK_API( OSErr , CalcColorTableProcPtr )(UInt32 dataRef, SInt16 colorsRequested, void *colorBankPtr, CSpecArray resultPtr);
typedef CALLBACK_API( OSErr , DisposeColorPickMethodProcPtr )(UInt32 dataRef);
typedef STACK_UPP_TYPE(InitPickMethodProcPtr)                   InitPickMethodUPP;
typedef STACK_UPP_TYPE(RecordColorsProcPtr)                     RecordColorsUPP;
typedef STACK_UPP_TYPE(CalcColorTableProcPtr)                   CalcColorTableUPP;
typedef STACK_UPP_TYPE(DisposeColorPickMethodProcPtr)           DisposeColorPickMethodUPP;
/*
 *  NewInitPickMethodUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern InitPickMethodUPP
NewInitPickMethodUPP(InitPickMethodProcPtr userRoutine);

/*
 *  NewRecordColorsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern RecordColorsUPP
NewRecordColorsUPP(RecordColorsProcPtr userRoutine);

/*
 *  NewCalcColorTableUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern CalcColorTableUPP
NewCalcColorTableUPP(CalcColorTableProcPtr userRoutine);

/*
 *  NewDisposeColorPickMethodUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DisposeColorPickMethodUPP
NewDisposeColorPickMethodUPP(DisposeColorPickMethodProcPtr userRoutine);

/*
 *  DisposeInitPickMethodUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeInitPickMethodUPP(InitPickMethodUPP userUPP);

/*
 *  DisposeRecordColorsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeRecordColorsUPP(RecordColorsUPP userUPP);

/*
 *  DisposeCalcColorTableUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeCalcColorTableUPP(CalcColorTableUPP userUPP);

/*
 *  DisposeDisposeColorPickMethodUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDisposeColorPickMethodUPP(DisposeColorPickMethodUPP userUPP);

/*
 *  InvokeInitPickMethodUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeInitPickMethodUPP(
  SInt16             colorsRequested,
  UInt32 *           dataRef,
  SInt16 *           colorBankType,
  InitPickMethodUPP  userUPP);

/*
 *  InvokeRecordColorsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeRecordColorsUPP(
  UInt32           dataRef,
  RGBColor *       colorsArray,
  SInt32           colorCount,
  SInt32 *         uniqueColors,
  RecordColorsUPP  userUPP);

/*
 *  InvokeCalcColorTableUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeCalcColorTableUPP(
  UInt32             dataRef,
  SInt16             colorsRequested,
  void *             colorBankPtr,
  CSpecArray         resultPtr,
  CalcColorTableUPP  userUPP);

/*
 *  InvokeDisposeColorPickMethodUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeDisposeColorPickMethodUPP(
  UInt32                     dataRef,
  DisposeColorPickMethodUPP  userUPP);

/*
 *  GetPictInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
GetPictInfo(
  PicHandle   thePictHandle,
  PictInfo *  thePictInfo,
  short       verb,
  short       colorsRequested,
  short       colorPickMethod,
  short       version);


/*
 *  GetPixMapInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
GetPixMapInfo(
  PixMapHandle   thePixMapHandle,
  PictInfo *     thePictInfo,
  short          verb,
  short          colorsRequested,
  short          colorPickMethod,
  short          version);


/*
 *  NewPictInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
NewPictInfo(
  PictInfoID *  thePictInfoID,
  short         verb,
  short         colorsRequested,
  short         colorPickMethod,
  short         version);


/*
 *  RecordPictInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
RecordPictInfo(
  PictInfoID   thePictInfoID,
  PicHandle    thePictHandle);


/*
 *  RecordPixMapInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
RecordPixMapInfo(
  PictInfoID     thePictInfoID,
  PixMapHandle   thePixMapHandle);


/*
 *  RetrievePictInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
RetrievePictInfo(
  PictInfoID   thePictInfoID,
  PictInfo *   thePictInfo,
  short        colorsRequested);


/*
 *  DisposePictInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
DisposePictInfo(PictInfoID thePictInfoID);


#if OLDROUTINENAMES
#define DisposPictInfo(thePictInfoID) DisposePictInfo(thePictInfoID)
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

#endif /* __PICTUTILS__ */

