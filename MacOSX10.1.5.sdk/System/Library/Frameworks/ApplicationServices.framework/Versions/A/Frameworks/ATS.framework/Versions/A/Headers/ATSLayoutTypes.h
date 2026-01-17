/*
     File:       ATS/ATSLayoutTypes.h
 
     Contains:   Apple Type Services layout public structures and constants.
 
     Version:    ATS-77.1~62
 
     Copyright:  © 1994-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __ATSLAYOUTTYPES__
#define __ATSLAYOUTTYPES__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __SFNTLAYOUTTYPES__
#include <ATS/SFNTLayoutTypes.h>
#endif


#ifndef __ATSTYPES__
#include <ATS/ATSTypes.h>
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

/* --------------------------------------------------------------------------- */
/* CONSTANTS and related scalar types */
/* --------------------------------------------------------------------------- */
/* Miscellaneous constants */
enum {
  kATSUseLineHeight             = 0x7FFFFFFF, /* assignment to use natural line ascent/descent values */
  kATSNoTracking                = (long)0x80000000 /* negativeInfinity */
};

typedef UInt32                          ATSLineLayoutOptions;
enum {
  kATSLineNoLayoutOptions       = 0x00000000, /* no options */
  kATSLineIsDisplayOnly         = 0x00000001, /* specifies to optimize for displaying text only */
  kATSLineHasNoHangers          = 0x00000002, /* specifies that no hangers to be formed on the line */
  kATSLineHasNoOpticalAlignment = 0x00000004, /* specifies that no optical alignment to be performed on the line */
  kATSLineKeepSpacesOutOfMargin = 0x00000008, /* specifies that space charcters should not be treated as hangers */
  kATSLineNoSpecialJustification = 0x00000010, /* specifies no post-compensation justification is to be performed */
  kATSLineLastNoJustification   = 0x00000020, /* specifies that if the line is the last of a paragraph, it will not get justified */
  kATSLineFractDisable          = 0x00000040, /* specifies that the displayed line glyphs will adjust for device metrics */
  kATSLineImposeNoAngleForEnds  = 0x00000080, /* specifies that the carets at the ends of the line will be guarenteed to be perpendicular to the baseline */
  kATSLineFillOutToWidth        = 0x00000100, /* highlights for the line end characters will be extended to 0 and the specified line width */
  kATSLineTabAdjustEnabled      = 0x00000200, /* specifies that the tab character width will be automatically adjusted to fit the specified line width */
  kATSLineIgnoreFontLeading     = 0x00000400, /* specifies that any leading value specified by a font will be ignored */
  kATSLineAppleReserved         = (long)0xFFFFF800 /* these bits are reserved by Apple and will result in a invalid value error if attemped to set */
};

typedef UInt32                          ATSStyleRenderingOptions;
enum {
  kATSStyleNoOptions            = 0x00000000, /* no options */
  kATSStyleApplyHints           = 0x00000001, /* specifies that ATS produce "hinted" glyph outlines (default is on) */
                                        /*    kATSStyleApplyAntiAliasing           = 0x00000002L,  |* specifies that ATS produce antialiased glyph images (default is on) future feature *|*/
  kATSStyleAppleReserved        = (long)0xFFFFFFFE /* these bits are reserved by Apple and will result in a invalid value error if attemped to set */
};

/* For accessing glyph bounds */
enum {
  kATSUseCaretOrigins           = 0,
  kATSUseDeviceOrigins          = 1,
  kATSUseFractionalOrigins      = 2,
  kATSUseOriginFlags            = 3
};

/* --------------------------------------------------------------------------- */
/* STRUCTURED TYPES and related constants */
/* --------------------------------------------------------------------------- */

/*
    The ATSTrapezoid structure supplies a convenient container
    for glyph bounds in trapezoidal form.
*/
struct ATSTrapezoid {
  FixedPoint          upperLeft;
  FixedPoint          upperRight;
  FixedPoint          lowerRight;
  FixedPoint          lowerLeft;
};
typedef struct ATSTrapezoid             ATSTrapezoid;
/*
    The JustWidthDeltaEntryOverride structure specifies values for the grow and shrink case during
    justification, both on the left and on the right. It also contains flags.  This particular structure
    is used for passing justification overrides to LLC.  For further sfnt resource 'just' table
    constants and structures, see SFNTLayoutTypes.h.
*/
struct ATSJustWidthDeltaEntryOverride {
  Fixed               beforeGrowLimit;        /* ems AW can grow by at most on LT */
  Fixed               beforeShrinkLimit;      /* ems AW can shrink by at most on LT */
  Fixed               afterGrowLimit;         /* ems AW can grow by at most on RB */
  Fixed               afterShrinkLimit;       /* ems AW can shrink by at most on RB */
  JustificationFlags  growFlags;              /* flags controlling grow case */
  JustificationFlags  shrinkFlags;            /* flags controlling shrink case */
};
typedef struct ATSJustWidthDeltaEntryOverride ATSJustWidthDeltaEntryOverride;
/* The JustPriorityOverrides type is an array of 4 width delta records, one per priority level override. */
typedef ATSJustWidthDeltaEntryOverride  ATSJustPriorityWidthDeltaOverrides[4];
/* --------------------------------------------------------------------------- */

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

#endif /* __ATSLAYOUTTYPES__ */

