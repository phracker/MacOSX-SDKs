/*
     File:       QD/ATSUnicode.h
 
     Contains:   Public interfaces for Apple Type Services for Unicode Imaging
 
     Version:    Quickdraw-96.21~1
 
     Copyright:  © 1997-2002 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __ATSUNICODE__
#define __ATSUNICODE__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __ATSLAYOUTTYPES__
#include <ATS/ATSLayoutTypes.h>
#endif

#ifndef __FONTS__
#include <QD/Fonts.h>
#endif

#ifndef __QUICKDRAW__
#include <QD/Quickdraw.h>
#endif

#ifndef __SFNTTYPES__
#include <ATS/SFNTTypes.h>
#endif

#ifndef __SFNTLAYOUTTYPES__
#include <ATS/SFNTLayoutTypes.h>
#endif

#ifndef __ATSTYPES__
#include <ATS/ATSTypes.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

/********************************/
/*  Types and related constants */
/********************************/
/*
   UniCharArrayHandle and UniCharArrayOffset are defined in the
   TextCommon interface file.
*/

/*
    ATSUTextMeasurement is specific to ATSUI in that measurement
    quantities are in fractional Fixed format instead of shorts
    used in QuickDraw Text.  This provides exact outline metrics and
    line specifications such as line width, ascent, descent, and so on.  
*/
typedef Fixed                           ATSUTextMeasurement;
/*
    ATSUFontID indicates a particular font family and face.  
    ATSUFontID's are not guaranteed to remain constant across 
    reboots.  Clients should use the font's unique name to 
    get a font token to store in documents which is 
    guaranteed to remain constant across reboots. 
*/
typedef FMFont                          ATSUFontID;
/*
    ATSUFontFeatureType and ATSUFontFeatureSelector are used 
    to identify font features.  
*/
typedef UInt16                          ATSUFontFeatureType;
typedef UInt16                          ATSUFontFeatureSelector;
/*
    ATSUFontVariationAxis and ATSUFontVariationValue are used 
    in connection with font variations.  
*/
typedef FourCharCode                    ATSUFontVariationAxis;
typedef Fixed                           ATSUFontVariationValue;
/*
    ATSUTextLayout is used to store the attribute information 
    associated with a contiguous block of UniChar's (UInt16's) 
    in memory.  It's typed to be an opaque structure.  
*/
typedef struct OpaqueATSUTextLayout*    ATSUTextLayout;
/*
    ATSUStyle is used to store a set of individual attributes, 
    font features, and font variations.  It's typed to be 
    an opaque structure.  
*/
typedef struct OpaqueATSUStyle*         ATSUStyle;
/*
    ATSUFontFallbacks is used to store the desired font fallback 
    list and associated fallback cache information.  It's typed
    to be an opaque structure.  
*/
typedef struct OpaqueATSUFontFallbacks*  ATSUFontFallbacks;
/*
    ATSUAttributeTag is used to indicate the particular type 
    of attribute under consideration:  font, size, color, 
    and so on.  
    Each style run may have at most one attribute with a 
    given ATSUAttributeTag (i.e., a style run can't have 
    more than one font or size) but may have none.  
    Note: Apple reserves values 0 to 65,535 (0 to 0x0000FFFF).
    ATSUI clients may create their own tags with any other value.
*/
typedef UInt32 ATSUAttributeTag;
enum {
                                        /*    Layout and Line Control Attribute Tags*/
  kATSULineWidthTag             = 1L,   /*    Type:       ATSUTextMeasurement >= 0*/
                                        /*    Default value: 0*/
  kATSULineRotationTag          = 2L,   /*    Type:       Fixed (fixed value in degrees in right-handed coordinate system)*/
                                        /*    Default value: 0*/
  kATSULineDirectionTag         = 3L,   /*    Type:       Boolean; values 0 or 1 (see below for value identities)*/
                                        /*    Default value: GetSysDirection() ? kATSURightToLeftBaseDirection : kATSULeftToRightBaseDirection*/
  kATSULineJustificationFactorTag = 4L, /*    Type:       Fract between 0 and 1*/
                                        /*    Default value: kATSUNoJustification*/
  kATSULineFlushFactorTag       = 5L,   /*    Type:       Fract between 0 and 1 */
                                        /*    Default value: kATSUStartAlignment*/
  kATSULineBaselineValuesTag    = 6L,   /*    Type:       BslnBaselineRecord*/
                                        /*    Default value: All zeros.  Calculated from other style attributes (e.g., font and point size)*/
  kATSULineLayoutOptionsTag     = 7L,   /*    Type:       ATSLineLayoutOptions (see ATSLayoutTypes.h)*/
                                        /*    Default value: kATSLineNoLayoutOptions - other options listed in ATSLayoutTypes.h*/
  kATSULineAscentTag            = 8L,   /*    Type:       ATSUTextMeasurement >= 0*/
                                        /*    Default value: Maximum typographical ascent of all fonts used on line or textLayout*/
  kATSULineDescentTag           = 9L,   /*    Type:       ATSUTextMeasurement >= 0*/
                                        /*    Default value: Maximum typographical descent+leading of all fonts used on line or textLayout*/
  kATSULineLangRegionTag        = 10L,  /*    Type:       RegionCode - region values listed in script.h interface file*/
                                        /*    Default value: kTextRegionDontCare*/
  kATSULineTextLocatorTag       = 11L,  /*    Type:       TextBreakLocatorRef*/
                                        /*    Default value: NULL - set Region derived locator or the default Text Utilities locator*/
  kATSULineTruncationTag        = 12L,  /*    Type:       ATSULineTruncation*/
                                        /*    Default value: kATSUTruncateNone                                                       */
  kATSULineFontFallbacksTag     = 13L,  /*    Type:       ATSUFontFallbacks*/
                                        /*    Default value: globally set font fallbacks using the ATSUSetFontFallbacks                                                     */
  kATSULayoutOperationOverrideTag = 15L, /*    Type:       ATSULayoutOperationOverrideSpecifier (MacOS 10.2 or later) */
                                        /*    Default value:     NULL*/
  kATSUMaxLineTag               = 16L,  /*    This is just for convenience - the upper limit of the ATSUTextLayout attribute tags*/
                                        /* Obsolete layout tags */
  kATSULineLanguageTag          = 10L,  /*    Use kATSULineLangRegionTag           */
                                        /* Special layout tags */
  kATSUCGContextTag             = 32767L, /*    Type:       CGContextRef (MacOS X systems only)*/
                                        /*    Default value: NULL*/
                                        /*    Run Style Attribute Tags*/
                                        /* QuickDraw compatibility tags */
  kATSUQDBoldfaceTag            = 256L, /*    Type:       Boolean    */
                                        /*    Default value: false*/
  kATSUQDItalicTag              = 257L, /*    Type:       Boolean       */
                                        /*    Default value: false*/
  kATSUQDUnderlineTag           = 258L, /*    Type:       Boolean    */
                                        /*    Default value: false*/
  kATSUQDCondensedTag           = 259L, /*    Type:       Boolean    */
                                        /*    Default value: false*/
  kATSUQDExtendedTag            = 260L, /*    Type:       Boolean    */
                                        /*    Default value: false*/
                                        /* Common run tags */
  kATSUFontTag                  = 261L, /*    Type:       ATSUFontID */
                                        /*    Default value: GetScriptVariable( smSystemScript, smScriptAppFond )*/
  kATSUSizeTag                  = 262L, /*    Type:       Fixed  */
                                        /*    Default value: GetScriptVariable( smSystemScript, smScriptAppFondSize )    */
  kATSUColorTag                 = 263L, /*    Type:       RGBColor*/
                                        /*    Default value: (0, 0, 0)*/
                                        /*    Less common run tags */
  kATSULangRegionTag            = 264L, /*    Type:       RegionCode - region values listed in script.h interface file*/
                                        /*    Default value: GetScriptManagerVariable( smRegionCode )*/
  kATSUVerticalCharacterTag     = 265L, /*    Type:       ATSUVerticalCharacterType  */
                                        /*    Default value: kATSUStronglyHorizontal*/
  kATSUImposeWidthTag           = 266L, /*    Type:       ATSUTextMeasurement >= 0*/
                                        /*    Default value: kATSUseGlyphAdvance - all glyphs use their own font defined advance widths*/
  kATSUBeforeWithStreamShiftTag = 267L, /*    Type:       Fixed*/
                                        /*    Default value: 0*/
  kATSUAfterWithStreamShiftTag  = 268L, /*    Type:       Fixed*/
                                        /*    Default value: 0*/
  kATSUCrossStreamShiftTag      = 269L, /*    Type:       Fixed*/
                                        /*    Default value: 0*/
  kATSUTrackingTag              = 270L, /*    Type:       Fixed*/
                                        /*    Default value: kATSNoTracking*/
  kATSUHangingInhibitFactorTag  = 271L, /*    Type:       Fract between 0 and 1*/
                                        /*    Default value: 0*/
  kATSUKerningInhibitFactorTag  = 272L, /*    Type:       Fract between 0 and 1*/
                                        /*    Default value: 0*/
  kATSUDecompositionFactorTag   = 273L, /*    Type:       Fixed (-1.0 -> 1.0)*/
                                        /*    Default value: 0*/
  kATSUBaselineClassTag         = 274L, /*    Type:       BslnBaselineClass  (see SFNTLayoutTypes.h)*/
                                        /*    Default value: kBSLNRomanBaseline - set to kBSLNNoBaselineOverride to use intrinsic baselines*/
  kATSUPriorityJustOverrideTag  = 275L, /*    Type:       ATSJustPriorityWidthDeltaOverrides (see ATSLayoutTypes.h)*/
                                        /*    Default value: all zeros*/
  kATSUNoLigatureSplitTag       = 276L, /*    Type:       Boolean*/
                                        /*    Default value: false - ligatures and compound characters have divisable components.*/
  kATSUNoCaretAngleTag          = 277L, /*    Type:       Boolean*/
                                        /*    Default value: false - use the character's angularity to determine its boundaries*/
  kATSUSuppressCrossKerningTag  = 278L, /*    Type:       Boolean*/
                                        /*    Default value: false - do not suppress automatic cross kerning (defined by font)*/
  kATSUNoOpticalAlignmentTag    = 279L, /*    Type:       Boolean*/
                                        /*    Default value: false - do not suppress character's automatic optical positional alignment*/
  kATSUForceHangingTag          = 280L, /*    Type:       Boolean*/
                                        /*    Default value: false - do not force the character's to hang beyond the line boundaries*/
  kATSUNoSpecialJustificationTag = 281L, /*    Type:       Boolean*/
                                        /*    Default value: false - perform post-compensation justification if needed*/
  kATSUStyleTextLocatorTag      = 282L, /*    Type:       TextBreakLocatorRef*/
                                        /*    Default value: NULL - region derived locator or the default Text Utilities locator*/
  kATSUStyleRenderingOptionsTag = 283L, /*    Type:       ATSStyleRenderingOptions (see ATSLayoutTypes.h)*/
                                        /*    Default value: kATSStyleNoOptions - other options listed in ATSLayoutTypes.h*/
  kATSUAscentTag                = 284L, /*    Type:       ATSUTextMeasurement >= 0  (MacOS 10.2 or later)*/
                                        /*    Default value: Ascent value of style's font with current pointSize*/
  kATSUDescentTag               = 285L, /*    Type:       ATSUTextMeasurement >= 0  (MacOS 10.2 or later)*/
                                        /*    Default value: Descent value of style's font with current pointSize*/
  kATSULeadingTag               = 286L, /*    Type:       ATSUTextMeasurement >= 0  (MacOS 10.2 or later)*/
                                        /*    Default value: Leading value of style's font with current pointSize (usually value 0)*/
  kATSUGlyphSelectorTag         = 287L, /*    Type:       ATSUGlyphSelector  (MacOS 10.2 or later)*/
                                        /*    Default value: 0 - use the glyphs derived by ATSUI layout*/
  kATSURGBAlphaColorTag         = 288L, /*    Type:       ATSURGBAlphaColor  (MacOS 10.2 or later)*/
                                        /*    Default value: (0, 0, 0, 1)*/
  kATSUFontMatrixTag            = 289L, /*    Type:       CGAffineTransform  (MacOS 10.2 or later)*/
                                        /*    Default value: [1, 0, 0, 1, 0, 0] ==> CGAffineTransformIdentity*/
  kATSUMaxStyleTag              = 290L, /*    This is just for convenience - the upper limit of the ATSUStyle attribute tags */
                                        /* obsolete style tags */
  kATSULanguageTag              = 264L, /*    use kATSULangRegionTag               */
                                        /* max */
  kATSUMaxATSUITagValue         = 65535L /*    This is the maximum Apple ATSUI reserved tag value.  Client defined tags must be larger.*/
};

/*
    ATSUAttributeValuePtr is used to provide generic access to
    storage of attribute values, which vary in size.
    ConstATSUAttributeValuePtr is a pointer to a const attribute value.
*/
typedef void *                          ATSUAttributeValuePtr;
typedef const void *                    ConstATSUAttributeValuePtr;
/*
    ATSUAttributeInfo is used to provide a tag/size pairing.  
    This makes it possible to provide the client information   
    about all the attributes for a given range of text.  This   
    structure is only used to return to the client information   
    about a complete set of attributes.  An array of   
    ATSUAttributeInfos is passed as a parameter so that the   
    client can find out what attributes are set and what their   
    individual sizes are; with that information, they can then   
    query about the values of the attributes they're interested   
    in.  Because arrays of ATSUAttributeInfos are used as parameters   
    to functions, they have to be of a fixed size, hence the   
    value is not included in the structure.  
*/
struct ATSUAttributeInfo {
  ATSUAttributeTag    fTag;
  ByteCount           fValueSize;
};
typedef struct ATSUAttributeInfo        ATSUAttributeInfo;
/*
    ATSUCaret contains the complete information needed to render a
    caret.  fX and fY is the position of one of the caret's ends
    relative to the origin position of the line the caret belongs.
    fDeltaX and fDeltaY is the position of the caret's other end.
    Hence, to draw a caret, simply call MoveTo(fX, fY) followed by
    LineTo(fDeltaX, fDeltaY) or equivalent.  The ATSUCaret will
    contain the positions needed to draw carets on angled lines
    and reflect angled carets and leading/trailing split caret
    appearances.
*/
struct ATSUCaret {
  Fixed               fX;
  Fixed               fY;
  Fixed               fDeltaX;
  Fixed               fDeltaY;
};
typedef struct ATSUCaret                ATSUCaret;
/*
    ATSUCursorMovementType is used to indicate how much to move
    the cursor when using the ATSUI cusor movement routines. 
    Note that kATSUByCharacterCluster is only available in Mac OS X
    and in CarbonLib versions 1.3 and later.
*/
typedef UInt16 ATSUCursorMovementType;
enum {
  kATSUByCharacter              = 0,
  kATSUByTypographicCluster     = 1,    /* clusters based on characters or ligatures*/
  kATSUByWord                   = 2,
  kATSUByCharacterCluster       = 3,    /* clusters based on characters only*/
  kATSUByCluster                = 1     /* obsolete name for kATSUByTypographicCluster*/
};

/*
    ATSULineTruncation is for identifying where truncation will occur when
    using a ATSUTextLayout with the ATSULineTruncation layout attribute.
*/
typedef UInt32 ATSULineTruncation;
enum {
  kATSUTruncateNone             = 0,    /* truncation specification - add to any desired truncFeat bit options listed below*/
  kATSUTruncateStart            = 1,    /* for instance, kATSUTruncateEnd with kATSUTruncFeatNoSquishing is value 0x0000000A*/
  kATSUTruncateEnd              = 2,
  kATSUTruncateMiddle           = 3,
  kATSUTruncateSpecificationMask = 0x00000007, /* these bits are reserved for the truncation specification (0 - 7)*/
                                        /* the following bit-field options can be added to the chosen truncation specification*/
  kATSUTruncFeatNoSquishing     = 0x00000008 /* if specified, do not perform any negative justification in lieu of truncation*/
};

/*
    ATSUVerticalCharacterType currently can take two values 
    and is used to indicate whether text is to be laid out 
    as vertical glyphs or horizontal glyphs.  
*/
typedef UInt16 ATSUVerticalCharacterType;
enum {
  kATSUStronglyHorizontal       = 0,
  kATSUStronglyVertical         = 1
};

/*
    ATSUStyleComparison is an enumeration with four values, 
    and is used by ATSUCompareStyles() to indicate if the
    first style parameter contains as a proper subset, is
    equal to, or is contained by the second style parameter.
*/
typedef UInt16 ATSUStyleComparison;
enum {
  kATSUStyleUnequal             = 0,
  kATSUStyleContains            = 1,
  kATSUStyleEquals              = 2,
  kATSUStyleContainedBy         = 3
};

/*
    ATSUFontFallbackMethod type defines the method by which ATSUI will try to
    find an appropriate font for a character if the assigned font does not
    contain the needed glyph(s) to represent it.  This affects ATSUMatchFontsToText
    and font selection during layout and drawing when ATSUSetTransientFontMatching
    is set ON.
*/
typedef UInt16 ATSUFontFallbackMethod;
enum {
  kATSUDefaultFontFallbacks     = 0,
  kATSULastResortOnlyFallback   = 1,
  kATSUSequentialFallbacksPreferred = 2,
  kATSUSequentialFallbacksExclusive = 3
};

/*
    ATSUTabType type defines the characteristic of ATSUI tabs.
    A Left tab type specifies that the left side of affected text is to be
    maintained flush against the tab stop.  A Right tab type specifies that
    the right side of affected text is to be maintained flush against the
    tab stop.  A Center tab type specifies that the affected text centered
    about the tab stop.
*/

typedef UInt16                          ATSUTabType;
enum {
  kATSULeftTab                  = 0,
  kATSUCenterTab                = 1,
  kATSURightTab                 = 2,
  kATSUNumberTabTypes           = 3
};

/*
    ATSUTab specifies the position and type of tab stop
    to be applied to a ATSUTextLayout set through the ATSUI routine
    ATSUSetTabArray and returned through ATSUGetTabArray.
*/
struct ATSUTab {
  ATSUTextMeasurement  tabPosition;
  ATSUTabType         tabType;
};
typedef struct ATSUTab                  ATSUTab;
/*
    GlyphCollection types represent the specific character collection.  If
    the value is zero, kGlyphCollectionGID, then this indicates that the
    glyph value represents the actual glyphID of a specific font.
*/

typedef UInt16                          GlyphCollection;
enum {
  kGlyphCollectionGID           = 0,
  kGlyphCollectionAdobeCNS1     = 1,
  kGlyphCollectionAdobeGB1      = 2,
  kGlyphCollectionAdobeJapan1   = 3,
  kGlyphCollectionAdobeJapan2   = 4,
  kGlyphCollectionAdobeKorea1   = 5,
  kGlyphCollectionUnspecified   = 0xFF
};

/*
    ATSUGlyphSelector can direct ATSUI to use a specific glyph instead of the one that 
    ATSUI normally derives.  The glyph can be specified either as a glyphID (specific
    to the font used) or CID from a specfic collection defined by the collection entry.
*/
struct ATSUGlyphSelector {
  GlyphCollection     collection;             /* kGlyphCollectionXXX enum*/
  GlyphID             glyphID;                /* GID (when collection==0) or CID*/
};
typedef struct ATSUGlyphSelector        ATSUGlyphSelector;
#if CALL_NOT_IN_CARBON
/*
    ATSUMemoryCallbacks is a union struct that allows the ATSUI 
    client to specify a specific heap for ATSUI use or allocation
    callbacks of which ATSUI is to use each time ATSUI performs a
    memory operation (alloc, grow, free).
*/
typedef CALLBACK_API_C( void *, ATSUCustomAllocFunc )(void *refCon, ByteCount howMuch);
typedef CALLBACK_API_C( void , ATSUCustomFreeFunc )(void *refCon, void *doomedBlock);
typedef CALLBACK_API_C( void *, ATSUCustomGrowFunc )(void *refCon, void *oldBlock, ByteCount oldSize, ByteCount newSize);
union ATSUMemoryCallbacks {
  struct {
    ATSUCustomAllocFunc  Alloc;
    ATSUCustomFreeFunc  Free;
    ATSUCustomGrowFunc  Grow;
    void *              memoryRefCon;
  }                       callbacks;

  THz                 heapToUse;
};
typedef union ATSUMemoryCallbacks       ATSUMemoryCallbacks;
/*
    ATSUHeapSpec provides the ATSUI client a means of specifying the heap
    from which ATSUI should allocate its dynamic memory or specifying
    that ATSUI should use the memory callback provided by the client.
*/
typedef UInt16 ATSUHeapSpec;
enum {
  kATSUUseCurrentHeap           = 0,
  kATSUUseAppHeap               = 1,
  kATSUUseSpecificHeap          = 2,
  kATSUUseCallbacks             = 3
};


/*
    ATSUMemorySetting is used to store the results from a ATSUSetMemoryAlloc
    or a ATSUGetCurrentMemorySetting call.  It can also be used to change the
    current ATSUMemorySetting by passing it into the ATSUSetCurrentMemorySetting
    call.
*/
typedef struct OpaqueATSUMemorySetting*  ATSUMemorySetting;
#endif  /* CALL_NOT_IN_CARBON */

/* Types for ATSUI Low Level API */
struct ATSUGlyphInfo {
  GlyphID             glyphID;
  UInt16              reserved;
  UInt32              layoutFlags;
  UniCharArrayOffset  charIndex;
  ATSUStyle           style;
  Float32             deltaY;
  Float32             idealX;
  SInt16              screenX;
  SInt16              caretX;
};
typedef struct ATSUGlyphInfo            ATSUGlyphInfo;
struct ATSUGlyphInfoArray {
  ATSUTextLayout      layout;
  ItemCount           numGlyphs;
  ATSUGlyphInfo       glyphs[1];
};
typedef struct ATSUGlyphInfoArray       ATSUGlyphInfoArray;
/*********************************************************************************/
/*  ATSUI Highlighting method constants and typedefs                             */
/*********************************************************************************/
typedef UInt32 ATSUHighlightMethod;
enum {
  kInvertHighlighting           = 0,
  kRedrawHighlighting           = 1
};

typedef UInt32 ATSUBackgroundDataType;
enum {
  kATSUBackgroundColor          = 0,
  kATSUBackgroundCallback       = 1
};

struct ATSURGBAlphaColor {
  float               red;
  float               green;
  float               blue;
  float               alpha;
};
typedef struct ATSURGBAlphaColor        ATSURGBAlphaColor;
typedef ATSURGBAlphaColor               ATSUBackgroundColor;

/*
 *  RedrawBackgroundProcPtr
 *  
 *  Discussion:
 *    RedrawBackgroundProcPtr is a pointer to a client-supplied
 *    callback function (e.g. MyRedrawBackgroundProc) for redrawing
 *    complex backgrounds (and optionally the text as well) that can be
 *    called by ATSUI for highlighting if the client has called
 *    ATSUSetHighlightingMethod with iMethod=kRedrawHighlighting. In
 *    order for ATSUI to call the client function, the client must (1)
 *    pass a pointer to the client function to NewRedrawBackgroundUPP()
 *    in order to obtain a RedrawBackgroundUPP, and (2) pass the
 *    RedrawBackgroundUPP in the unhighlightData.backgroundUPP field of
 *    the iUnhighlightData parameter for the  ATSUSetHighlightingMethod
 *    call. When finished, the client should call
 *    DisposeRedrawBackgroundUPP with the RedrawBackgroundUPP.
 *  
 *  Parameters:
 *    
 *    iLayout:
 *      The layout to which the highlighting is being applied. The
 *      client function can use this to redraw the text.
 *    
 *    iTextOffset:
 *      The offset of the text that is being highlighted; can be used
 *      by the client function to redraaw the text.
 *    
 *    iTextLength:
 *      The length of the text that is being highlighted; can be used
 *      by the client function to redraaw the text.
 *    
 *    iUnhighlightArea:
 *      An array of ATSTrapezoids that describes the highlight area.
 *      The ATSTrapezoid array is ALWAYS in QD coordinates.
 *    
 *    iTrapezoidCount:
 *      The count of ATSTrapezoids in iUnhighlightArea.
 *  
 *  Result:
 *    A Boolean result indicating whether ATSUI should redraw the text.
 *    If the client function redraws the text, it should return false,
 *    otherwise it should return true to have ATSUI redraw any text
 *    that needs to be redrawn.
 */
typedef CALLBACK_API( Boolean , RedrawBackgroundProcPtr )(ATSUTextLayout iLayout, UniCharArrayOffset iTextOffset, UniCharCount iTextLength, ATSTrapezoid iUnhighlightArea[], ItemCount iTrapezoidCount);
typedef STACK_UPP_TYPE(RedrawBackgroundProcPtr)                 RedrawBackgroundUPP;
/*
 *  NewRedrawBackgroundUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib on Mac OS X
 *    Non-Carbon CFM:   not available
 */
extern RedrawBackgroundUPP
NewRedrawBackgroundUPP(RedrawBackgroundProcPtr userRoutine)   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeRedrawBackgroundUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib on Mac OS X
 *    Non-Carbon CFM:   not available
 */
extern void
DisposeRedrawBackgroundUPP(RedrawBackgroundUPP userUPP)       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeRedrawBackgroundUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib on Mac OS X
 *    Non-Carbon CFM:   not available
 */
extern Boolean
InvokeRedrawBackgroundUPP(
  ATSUTextLayout       iLayout,
  UniCharArrayOffset   iTextOffset,
  UniCharCount         iTextLength,
  ATSTrapezoid         iUnhighlightArea[],
  ItemCount            iTrapezoidCount,
  RedrawBackgroundUPP  userUPP)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

union ATSUBackgroundData {
  ATSUBackgroundColor  backgroundColor;
  RedrawBackgroundUPP  backgroundUPP;
};
typedef union ATSUBackgroundData        ATSUBackgroundData;
struct ATSUUnhighlightData {
  ATSUBackgroundDataType  dataType;
  ATSUBackgroundData  unhighlightData;
};
typedef struct ATSUUnhighlightData      ATSUUnhighlightData;
/********************/
/*  Other constants */
/********************/
/* Line direction types (used for kATSULineDirectionTag values) */
enum {
  kATSULeftToRightBaseDirection = 0,    /*    Impose left-to-right or top-to-bottom dominant direction */
  kATSURightToLeftBaseDirection = 1     /*    Impose right-to-left or bottom-to-top dominant direction */
};

/* LineFlushFactor convenience defined values */
#define kATSUStartAlignment         ((Fract) 0x00000000L)
#define kATSUEndAlignment           ((Fract) 0x40000000L)
#define kATSUCenterAlignment        ((Fract) 0x20000000L)
/* LineJustificationFactor convenience defined values */
#define kATSUNoJustification        ((Fract) 0x00000000L)
#define kATSUFullJustification      ((Fract) 0x40000000L)
/* Other constants  */
enum {
  kATSUInvalidFontID            = 0
};


enum {
  kATSUUseLineControlWidth      = 0x7FFFFFFF
};


enum {
  kATSUNoSelector               = 0x0000FFFF
};


enum {
  kATSUUseGrafPortPenLoc        = (unsigned long)0xFFFFFFFF,
  kATSUClearAll                 = (unsigned long)0xFFFFFFFF
};


enum {
  kATSUFromTextBeginning        = (unsigned long)0xFFFFFFFF,
  kATSUToTextEnd                = (unsigned long)0xFFFFFFFF
};



/****************/
/*  Functions   */
/****************/

/* ---------------------------------------------------------------------------- */
/*  Clipboard support, flattened style version 0                                */
/* ---------------------------------------------------------------------------- */
/*
    Warning: ATSUCopyToHandle & ATSUPasteFromHandle have been deprecated
    Use their replacements, ATSUFlattenStyleRunsToStream and , instead if available or
    perform your own flattening
*/
/*
 *  ATSUCopyToHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUCopyToHandle(
  ATSUStyle   iStyle,
  Handle      oStyleHandle)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUPasteFromHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUPasteFromHandle(
  ATSUStyle   iStyle,
  Handle      iStyleHandle)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Memory allocation specification functions (not in Carbon)                   */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUCreateMemorySetting()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.6 and later
 */


/*
 *  ATSUSetCurrentMemorySetting()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.6 and later
 */


/*
 *  ATSUGetCurrentMemorySetting()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.6 and later
 */


/*
 *  ATSUDisposeMemorySetting()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.6 and later
 */


/* ---------------------------------------------------------------------------- */
/*  Font fallback object functions                                              */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUCreateFontFallbacks()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSUCreateFontFallbacks(ATSUFontFallbacks * oFontFallback)    AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  ATSUDisposeFontFallbacks()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSUDisposeFontFallbacks(ATSUFontFallbacks iFontFallbacks)    AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  ATSUSetObjFontFallbacks()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSUSetObjFontFallbacks(
  ATSUFontFallbacks        iFontFallbacks,
  ItemCount                iFontFallbacksCount,
  const ATSUFontID         iFonts[],
  ATSUFontFallbackMethod   iFontFallbackMethod)               AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  ATSUGetObjFontFallbacks()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSUGetObjFontFallbacks(
  ATSUFontFallbacks         iFontFallbacks,
  ItemCount                 iMaxFontFallbacksCount,
  ATSUFontID                oFonts[],
  ATSUFontFallbackMethod *  oFontFallbackMethod,
  ItemCount *               oActualFallbacksCount)            AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Basic style functions                                                       */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUCreateStyle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUCreateStyle(ATSUStyle * oStyle)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUCreateAndCopyStyle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUCreateAndCopyStyle(
  ATSUStyle    iStyle,
  ATSUStyle *  oStyle)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUDisposeStyle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUDisposeStyle(ATSUStyle iStyle)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUSetStyleRefCon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUSetStyleRefCon(
  ATSUStyle   iStyle,
  UInt32      iRefCon)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetStyleRefCon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetStyleRefCon(
  ATSUStyle   iStyle,
  UInt32 *    oRefCon)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Style comparison                                                            */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUCompareStyles()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUCompareStyles(
  ATSUStyle              iFirstStyle,
  ATSUStyle              iSecondStyle,
  ATSUStyleComparison *  oComparison)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Attribute manipulations                                                     */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUCopyAttributes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUCopyAttributes(
  ATSUStyle   iSourceStyle,
  ATSUStyle   iDestinationStyle)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUOverwriteAttributes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUOverwriteAttributes(
  ATSUStyle   iSourceStyle,
  ATSUStyle   iDestinationStyle)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUUnderwriteAttributes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUUnderwriteAttributes(
  ATSUStyle   iSourceStyle,
  ATSUStyle   iDestinationStyle)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Empty styles                                                                */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUClearStyle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUClearStyle(ATSUStyle iStyle)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUStyleIsEmpty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUStyleIsEmpty(
  ATSUStyle   iStyle,
  Boolean *   oIsClear)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Get and set attributes                                                      */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUCalculateBaselineDeltas()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUCalculateBaselineDeltas(
  ATSUStyle            iStyle,
  BslnBaselineClass    iBaselineClass,
  BslnBaselineRecord   oBaselineDeltas)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUSetAttributes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUSetAttributes(
  ATSUStyle                     iStyle,
  ItemCount                     iAttributeCount,
  const ATSUAttributeTag        iTag[],
  const ByteCount               iValueSize[],
  const ATSUAttributeValuePtr   iValue[])                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetAttribute()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetAttribute(
  ATSUStyle               iStyle,
  ATSUAttributeTag        iTag,
  ByteCount               iExpectedValueSize,
  ATSUAttributeValuePtr   oValue,
  ByteCount *             oActualValueSize)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetAllAttributes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetAllAttributes(
  ATSUStyle           iStyle,
  ATSUAttributeInfo   oAttributeInfoArray[],
  ItemCount           iTagValuePairArraySize,
  ItemCount *         oTagValuePairCount)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUClearAttributes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUClearAttributes(
  ATSUStyle                iStyle,
  ItemCount                iTagCount,
  const ATSUAttributeTag   iTag[])                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Font features                                                               */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUSetFontFeatures()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUSetFontFeatures(
  ATSUStyle                       iStyle,
  ItemCount                       iFeatureCount,
  const ATSUFontFeatureType       iType[],
  const ATSUFontFeatureSelector   iSelector[])                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetFontFeature()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetFontFeature(
  ATSUStyle                  iStyle,
  ItemCount                  iFeatureIndex,
  ATSUFontFeatureType *      oFeatureType,
  ATSUFontFeatureSelector *  oFeatureSelector)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetAllFontFeatures()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetAllFontFeatures(
  ATSUStyle                 iStyle,
  ItemCount                 iMaximumFeatureCount,
  ATSUFontFeatureType       oFeatureType[],
  ATSUFontFeatureSelector   oFeatureSelector[],
  ItemCount *               oActualFeatureCount)              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUClearFontFeatures()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUClearFontFeatures(
  ATSUStyle                       iStyle,
  ItemCount                       iFeatureCount,
  const ATSUFontFeatureType       iType[],
  const ATSUFontFeatureSelector   iSelector[])                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Font variations                                                             */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUSetVariations()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUSetVariations(
  ATSUStyle                      iStyle,
  ItemCount                      iVariationCount,
  const ATSUFontVariationAxis    iAxes[],
  const ATSUFontVariationValue   iValue[])                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetFontVariationValue()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetFontVariationValue(
  ATSUStyle                 iStyle,
  ATSUFontVariationAxis     iFontVariationAxis,
  ATSUFontVariationValue *  oFontVariationValue)              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetAllFontVariations()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetAllFontVariations(
  ATSUStyle                iStyle,
  ItemCount                iVariationCount,
  ATSUFontVariationAxis    oVariationAxes[],
  ATSUFontVariationValue   oFontVariationValues[],
  ItemCount *              oActualVariationCount)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUClearFontVariations()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUClearFontVariations(
  ATSUStyle                     iStyle,
  ItemCount                     iAxisCount,
  const ATSUFontVariationAxis   iAxis[])                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Basic text-layout functions                                                 */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUCreateTextLayout()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUCreateTextLayout(ATSUTextLayout * oTextLayout)            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUCreateAndCopyTextLayout()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.6 and later
 */
extern OSStatus 
ATSUCreateAndCopyTextLayout(
  ATSUTextLayout    iTextLayout,
  ATSUTextLayout *  oTextLayout)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUCreateTextLayoutWithTextPtr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUCreateTextLayoutWithTextPtr(
  ConstUniCharArrayPtr   iText,
  UniCharArrayOffset     iTextOffset,
  UniCharCount           iTextLength,
  UniCharCount           iTextTotalLength,
  ItemCount              iNumberOfRuns,
  const UniCharCount     iRunLengths[],
  ATSUStyle              iStyles[],
  ATSUTextLayout *       oTextLayout)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUCreateTextLayoutWithTextHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUCreateTextLayoutWithTextHandle(
  UniCharArrayHandle   iText,
  UniCharArrayOffset   iTextOffset,
  UniCharCount         iTextLength,
  UniCharCount         iTextTotalLength,
  ItemCount            iNumberOfRuns,
  const UniCharCount   iRunLengths[],
  ATSUStyle            iStyles[],
  ATSUTextLayout *     oTextLayout)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUClearLayoutCache()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.6 and later
 */
extern OSStatus 
ATSUClearLayoutCache(
  ATSUTextLayout       iTextLayout,
  UniCharArrayOffset   iLineStart)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUDisposeTextLayout()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUDisposeTextLayout(ATSUTextLayout iTextLayout)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUSetTextLayoutRefCon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUSetTextLayoutRefCon(
  ATSUTextLayout   iTextLayout,
  UInt32           iRefCon)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetTextLayoutRefCon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetTextLayoutRefCon(
  ATSUTextLayout   iTextLayout,
  UInt32 *         oRefCon)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Glyph bounds retrieval                                                      */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUGetGlyphBounds()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.6 and later
 */
extern OSStatus 
ATSUGetGlyphBounds(
  ATSUTextLayout        iTextLayout,
  ATSUTextMeasurement   iTextBasePointX,
  ATSUTextMeasurement   iTextBasePointY,
  UniCharArrayOffset    iBoundsCharStart,
  UniCharCount          iBoundsCharLength,
  UInt16                iTypeOfBounds,
  ItemCount             iMaxNumberOfBounds,
  ATSTrapezoid          oGlyphBounds[],
  ItemCount *           oActualNumberOfBounds)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Idle processing                                                             */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUIdle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUIdle(ATSUTextLayout iTextLayout)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Text location                                                               */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUSetTextPointerLocation()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUSetTextPointerLocation(
  ATSUTextLayout         iTextLayout,
  ConstUniCharArrayPtr   iText,
  UniCharArrayOffset     iTextOffset,
  UniCharCount           iTextLength,
  UniCharCount           iTextTotalLength)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUSetTextHandleLocation()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUSetTextHandleLocation(
  ATSUTextLayout       iTextLayout,
  UniCharArrayHandle   iText,
  UniCharArrayOffset   iTextOffset,
  UniCharCount         iTextLength,
  UniCharCount         iTextTotalLength)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetTextLocation()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetTextLocation(
  ATSUTextLayout        iTextLayout,
  void **               oText,
  Boolean *             oTextIsStoredInHandle,
  UniCharArrayOffset *  oOffset,
  UniCharCount *        oTextLength,
  UniCharCount *        oTextTotalLength)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Text manipulation                                                           */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUTextDeleted()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUTextDeleted(
  ATSUTextLayout       iTextLayout,
  UniCharArrayOffset   iDeletedRangeStart,
  UniCharCount         iDeletedRangeLength)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUTextInserted()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUTextInserted(
  ATSUTextLayout       iTextLayout,
  UniCharArrayOffset   iInsertionLocation,
  UniCharCount         iInsertionLength)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUTextMoved()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUTextMoved(
  ATSUTextLayout         iTextLayout,
  ConstUniCharArrayPtr   iNewLocation)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Layout controls                                                             */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUCopyLayoutControls()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUCopyLayoutControls(
  ATSUTextLayout   iSourceTextLayout,
  ATSUTextLayout   iDestTextLayout)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUSetLayoutControls()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUSetLayoutControls(
  ATSUTextLayout                iTextLayout,
  ItemCount                     iAttributeCount,
  const ATSUAttributeTag        iTag[],
  const ByteCount               iValueSize[],
  const ATSUAttributeValuePtr   iValue[])                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetLayoutControl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetLayoutControl(
  ATSUTextLayout          iTextLayout,
  ATSUAttributeTag        iTag,
  ByteCount               iExpectedValueSize,
  ATSUAttributeValuePtr   oValue,
  ByteCount *             oActualValueSize)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetAllLayoutControls()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetAllLayoutControls(
  ATSUTextLayout      iTextLayout,
  ATSUAttributeInfo   oAttributeInfoArray[],
  ItemCount           iTagValuePairArraySize,
  ItemCount *         oTagValuePairCount)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUClearLayoutControls()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUClearLayoutControls(
  ATSUTextLayout           iTextLayout,
  ItemCount                iTagCount,
  const ATSUAttributeTag   iTag[])                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Single line layout controls                                                 */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUCopyLineControls()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.6 and later
 */
extern OSStatus 
ATSUCopyLineControls(
  ATSUTextLayout       iSourceTextLayout,
  UniCharArrayOffset   iSourceLineStart,
  ATSUTextLayout       iDestTextLayout,
  UniCharArrayOffset   iDestLineStart)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUSetLineControls()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.6 and later
 */
extern OSStatus 
ATSUSetLineControls(
  ATSUTextLayout                iTextLayout,
  UniCharArrayOffset            iLineStart,
  ItemCount                     iAttributeCount,
  const ATSUAttributeTag        iTag[],
  const ByteCount               iValueSize[],
  const ATSUAttributeValuePtr   iValue[])                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetLineControl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.6 and later
 */
extern OSStatus 
ATSUGetLineControl(
  ATSUTextLayout          iTextLayout,
  UniCharArrayOffset      iLineStart,
  ATSUAttributeTag        iTag,
  ByteCount               iExpectedValueSize,
  ATSUAttributeValuePtr   oValue,
  ByteCount *             oActualValueSize)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetAllLineControls()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.6 and later
 */
extern OSStatus 
ATSUGetAllLineControls(
  ATSUTextLayout       iTextLayout,
  UniCharArrayOffset   iLineStart,
  ATSUAttributeInfo    oAttributeInfoArray[],
  ItemCount            iTagValuePairArraySize,
  ItemCount *          oTagValuePairCount)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUClearLineControls()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.6 and later
 */
extern OSStatus 
ATSUClearLineControls(
  ATSUTextLayout           iTextLayout,
  UniCharArrayOffset       iLineStart,
  ItemCount                iTagCount,
  const ATSUAttributeTag   iTag[])                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Style run processing                                                        */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUSetRunStyle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUSetRunStyle(
  ATSUTextLayout       iTextLayout,
  ATSUStyle            iStyle,
  UniCharArrayOffset   iRunStart,
  UniCharCount         iRunLength)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetRunStyle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetRunStyle(
  ATSUTextLayout        iTextLayout,
  UniCharArrayOffset    iOffset,
  ATSUStyle *           oStyle,
  UniCharArrayOffset *  oRunStart,
  UniCharCount *        oRunLength)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetContinuousAttributes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetContinuousAttributes(
  ATSUTextLayout       iTextLayout,
  UniCharArrayOffset   iOffset,
  UniCharCount         iLength,
  ATSUStyle            oStyle)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Drawing and measuring                                                       */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUDrawText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUDrawText(
  ATSUTextLayout        iTextLayout,
  UniCharArrayOffset    iLineOffset,
  UniCharCount          iLineLength,
  ATSUTextMeasurement   iLocationX,
  ATSUTextMeasurement   iLocationY)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Warning: ATSUMeasureText has been deprecated
    Use its replacement, ATSUGetUnjustifiedBounds, instead if available
*/
/*
 *  ATSUMeasureText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUMeasureText(
  ATSUTextLayout         iTextLayout,
  UniCharArrayOffset     iLineStart,
  UniCharCount           iLineLength,
  ATSUTextMeasurement *  oTextBefore,
  ATSUTextMeasurement *  oTextAfter,
  ATSUTextMeasurement *  oAscent,
  ATSUTextMeasurement *  oDescent)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetUnjustifiedBounds()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSUGetUnjustifiedBounds(
  ATSUTextLayout         iTextLayout,
  UniCharArrayOffset     iLineStart,
  UniCharCount           iLineLength,
  ATSUTextMeasurement *  oTextBefore,
  ATSUTextMeasurement *  oTextAfter,
  ATSUTextMeasurement *  oAscent,
  ATSUTextMeasurement *  oDescent)                            AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  ATSUMeasureTextImage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUMeasureTextImage(
  ATSUTextLayout        iTextLayout,
  UniCharArrayOffset    iLineOffset,
  UniCharCount          iLineLength,
  ATSUTextMeasurement   iLocationX,
  ATSUTextMeasurement   iLocationY,
  Rect *                oTextImageRect)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Highlighting                                                                */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUHighlightText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUHighlightText(
  ATSUTextLayout        iTextLayout,
  ATSUTextMeasurement   iTextBasePointX,
  ATSUTextMeasurement   iTextBasePointY,
  UniCharArrayOffset    iHighlightStart,
  UniCharCount          iHighlightLength)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUUnhighlightText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUUnhighlightText(
  ATSUTextLayout        iTextLayout,
  ATSUTextMeasurement   iTextBasePointX,
  ATSUTextMeasurement   iTextBasePointY,
  UniCharArrayOffset    iHighlightStart,
  UniCharCount          iHighlightLength)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetTextHighlight()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetTextHighlight(
  ATSUTextLayout        iTextLayout,
  ATSUTextMeasurement   iTextBasePointX,
  ATSUTextMeasurement   iTextBasePointY,
  UniCharArrayOffset    iHighlightStart,
  UniCharCount          iHighlightLength,
  RgnHandle             oHighlightRegion)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUHighlightInactiveText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSUHighlightInactiveText(
  ATSUTextLayout        iTextLayout,
  ATSUTextMeasurement   iTextBasePointX,
  ATSUTextMeasurement   iTextBasePointY,
  UniCharArrayOffset    iHighlightStart,
  UniCharCount          iHighlightLength)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Hit-testing                                                                 */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUPositionToOffset()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUPositionToOffset(
  ATSUTextLayout        iTextLayout,
  ATSUTextMeasurement   iLocationX,
  ATSUTextMeasurement   iLocationY,
  UniCharArrayOffset *  ioPrimaryOffset,
  Boolean *             oIsLeading,
  UniCharArrayOffset *  oSecondaryOffset)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUOffsetToPosition()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUOffsetToPosition(
  ATSUTextLayout       iTextLayout,
  UniCharArrayOffset   iOffset,
  Boolean              iIsLeading,
  ATSUCaret *          oMainCaret,
  ATSUCaret *          oSecondCaret,
  Boolean *            oCaretIsSplit)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUPositionToCursorOffset()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 9.2.2 and later
 */
extern OSStatus 
ATSUPositionToCursorOffset(
  ATSUTextLayout           iTextLayout,
  ATSUTextMeasurement      iLocationX,
  ATSUTextMeasurement      iLocationY,
  ATSUCursorMovementType   iMovementType,
  UniCharArrayOffset *     ioPrimaryOffset,
  Boolean *                oIsLeading,
  UniCharArrayOffset *     oSecondaryOffset)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUOffsetToCursorPosition()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 9.2.2 and later
 */
extern OSStatus 
ATSUOffsetToCursorPosition(
  ATSUTextLayout           iTextLayout,
  UniCharArrayOffset       iOffset,
  Boolean                  iIsLeading,
  ATSUCursorMovementType   iMovementType,
  ATSUCaret *              oMainCaret,
  ATSUCaret *              oSecondCaret,
  Boolean *                oCaretIsSplit)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Cursor movement                                                             */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUNextCursorPosition()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUNextCursorPosition(
  ATSUTextLayout           iTextLayout,
  UniCharArrayOffset       iOldOffset,
  ATSUCursorMovementType   iMovementType,
  UniCharArrayOffset *     oNewOffset)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUPreviousCursorPosition()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUPreviousCursorPosition(
  ATSUTextLayout           iTextLayout,
  UniCharArrayOffset       iOldOffset,
  ATSUCursorMovementType   iMovementType,
  UniCharArrayOffset *     oNewOffset)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSURightwardCursorPosition()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSURightwardCursorPosition(
  ATSUTextLayout           iTextLayout,
  UniCharArrayOffset       iOldOffset,
  ATSUCursorMovementType   iMovementType,
  UniCharArrayOffset *     oNewOffset)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSULeftwardCursorPosition()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSULeftwardCursorPosition(
  ATSUTextLayout           iTextLayout,
  UniCharArrayOffset       iOldOffset,
  ATSUCursorMovementType   iMovementType,
  UniCharArrayOffset *     oNewOffset)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Line breaking                                                               */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUBatchBreakLines()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSUBatchBreakLines(
  ATSUTextLayout        iTextLayout,
  UniCharArrayOffset    iRangeStart,
  UniCharCount          iRangeLength,
  ATSUTextMeasurement   iLineWidth,
  ItemCount *           oBreakCount)                          AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  ATSUBreakLine()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUBreakLine(
  ATSUTextLayout        iTextLayout,
  UniCharArrayOffset    iLineStart,
  ATSUTextMeasurement   iLineWidth,
  Boolean               iUseAsSoftLineBreak,
  UniCharArrayOffset *  oLineBreak)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUSetSoftLineBreak()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUSetSoftLineBreak(
  ATSUTextLayout       iTextLayout,
  UniCharArrayOffset   iLineBreak)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetSoftLineBreaks()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetSoftLineBreaks(
  ATSUTextLayout       iTextLayout,
  UniCharArrayOffset   iRangeStart,
  UniCharCount         iRangeLength,
  ItemCount            iMaximumBreaks,
  UniCharArrayOffset   oBreaks[],
  ItemCount *          oBreakCount)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUClearSoftLineBreaks()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUClearSoftLineBreaks(
  ATSUTextLayout       iTextLayout,
  UniCharArrayOffset   iRangeStart,
  UniCharCount         iRangeLength)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Tab support                                                                 */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUSetTabArray()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSUSetTabArray(
  ATSUTextLayout   iTextLayout,
  const ATSUTab    iTabs[],
  ItemCount        iTabCount)                                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  ATSUGetTabArray()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSUGetTabArray(
  ATSUTextLayout   iTextLayout,
  ItemCount        iMaxTabCount,
  ATSUTab          oTabs[],
  ItemCount *      oTabCount)                                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Font matching                                                               */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUSetFontFallbacks()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.6 and later
 */
extern OSStatus 
ATSUSetFontFallbacks(
  ItemCount                iFontFallbacksCount,
  const ATSUFontID         iFontIDs[],
  ATSUFontFallbackMethod   iFontFallbackMethod)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetFontFallbacks()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.6 and later
 */
extern OSStatus 
ATSUGetFontFallbacks(
  ItemCount                 iMaxFontFallbacksCount,
  ATSUFontID                oFontIDs[],
  ATSUFontFallbackMethod *  oFontFallbackMethod,
  ItemCount *               oActualFallbacksCount)            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUMatchFontsToText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUMatchFontsToText(
  ATSUTextLayout        iTextLayout,
  UniCharArrayOffset    iTextStart,
  UniCharCount          iTextLength,
  ATSUFontID *          oFontID,
  UniCharArrayOffset *  oChangedOffset,
  UniCharCount *        oChangedLength)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUSetTransientFontMatching()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUSetTransientFontMatching(
  ATSUTextLayout   iTextLayout,
  Boolean          iTransientFontMatching)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetTransientFontMatching()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetTransientFontMatching(
  ATSUTextLayout   iTextLayout,
  Boolean *        oTransientFontMatching)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Font ID's                                                                   */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUFontCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUFontCount(ItemCount * oFontCount)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetFontIDs()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetFontIDs(
  ATSUFontID   oFontIDs[],
  ItemCount    iArraySize,
  ItemCount *  oFontCount)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUFONDtoFontID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUFONDtoFontID(
  short         iFONDNumber,
  Style         iFONDStyle,
  ATSUFontID *  oFontID)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUFontIDtoFOND()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUFontIDtoFOND(
  ATSUFontID   iFontID,
  short *      oFONDNumber,
  Style *      oFONDStyle)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Font names                                                                  */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUCountFontNames()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUCountFontNames(
  ATSUFontID   iFontID,
  ItemCount *  oFontNameCount)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetIndFontName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetIndFontName(
  ATSUFontID          iFontID,
  ItemCount           iFontNameIndex,
  ByteCount           iMaximumNameLength,
  Ptr                 oName,
  ByteCount *         oActualNameLength,
  FontNameCode *      oFontNameCode,
  FontPlatformCode *  oFontNamePlatform,
  FontScriptCode *    oFontNameScript,
  FontLanguageCode *  oFontNameLanguage)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUFindFontName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUFindFontName(
  ATSUFontID         iFontID,
  FontNameCode       iFontNameCode,
  FontPlatformCode   iFontNamePlatform,
  FontScriptCode     iFontNameScript,
  FontLanguageCode   iFontNameLanguage,
  ByteCount          iMaximumNameLength,
  Ptr                oName,
  ByteCount *        oActualNameLength,
  ItemCount *        oFontNameIndex)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUFindFontFromName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUFindFontFromName(
  Ptr                iName,
  ByteCount          iNameLength,
  FontNameCode       iFontNameCode,
  FontPlatformCode   iFontNamePlatform,
  FontScriptCode     iFontNameScript,
  FontLanguageCode   iFontNameLanguage,
  ATSUFontID *       oFontID)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Font features                                                               */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUCountFontFeatureTypes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUCountFontFeatureTypes(
  ATSUFontID   iFontID,
  ItemCount *  oTypeCount)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUCountFontFeatureSelectors()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUCountFontFeatureSelectors(
  ATSUFontID            iFontID,
  ATSUFontFeatureType   iType,
  ItemCount *           oSelectorCount)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetFontFeatureTypes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetFontFeatureTypes(
  ATSUFontID            iFontID,
  ItemCount             iMaximumTypes,
  ATSUFontFeatureType   oTypes[],
  ItemCount *           oActualTypeCount)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetFontFeatureSelectors()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetFontFeatureSelectors(
  ATSUFontID                iFontID,
  ATSUFontFeatureType       iType,
  ItemCount                 iMaximumSelectors,
  ATSUFontFeatureSelector   oSelectors[],
  Boolean                   oSelectorIsOnByDefault[],
  ItemCount *               oActualSelectorCount,
  Boolean *                 oIsMutuallyExclusive)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetFontFeatureNameCode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetFontFeatureNameCode(
  ATSUFontID                iFontID,
  ATSUFontFeatureType       iType,
  ATSUFontFeatureSelector   iSelector,
  FontNameCode *            oNameCode)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Font tracking value & names                                                 */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUCountFontTracking()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.6 and later
 */
extern OSStatus 
ATSUCountFontTracking(
  ATSUFontID                  iFontID,
  ATSUVerticalCharacterType   iCharacterOrientation,
  ItemCount *                 oTrackingCount)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetIndFontTracking()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.6 and later
 */
extern OSStatus 
ATSUGetIndFontTracking(
  ATSUFontID                  iFontID,
  ATSUVerticalCharacterType   iCharacterOrientation,
  ItemCount                   iTrackIndex,
  Fixed *                     oFontTrackingValue,
  FontNameCode *              oNameCode)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Font variations                                                             */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUCountFontVariations()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUCountFontVariations(
  ATSUFontID   iFontID,
  ItemCount *  oVariationCount)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetIndFontVariation()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetIndFontVariation(
  ATSUFontID                iFontID,
  ItemCount                 iVariationIndex,
  ATSUFontVariationAxis *   oATSUFontVariationAxis,
  ATSUFontVariationValue *  oMinimumValue,
  ATSUFontVariationValue *  oMaximumValue,
  ATSUFontVariationValue *  oDefaultValue)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetFontVariationNameCode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetFontVariationNameCode(
  ATSUFontID              iFontID,
  ATSUFontVariationAxis   iAxis,
  FontNameCode *          oNameCode)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/*  Font Instances                                                              */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUCountFontInstances()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUCountFontInstances(
  ATSUFontID   iFontID,
  ItemCount *  oInstances)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetFontInstance()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetFontInstance(
  ATSUFontID               iFontID,
  ItemCount                iFontInstanceIndex,
  ItemCount                iMaximumVariations,
  ATSUFontVariationAxis    oAxes[],
  ATSUFontVariationValue   oValues[],
  ItemCount *              oActualVariationCount)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetFontInstanceNameCode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 8.5 and later
 */
extern OSStatus 
ATSUGetFontInstanceNameCode(
  ATSUFontID      iFontID,
  ItemCount       iInstanceIndex,
  FontNameCode *  oNameCode)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/********************************************************************************/
/* ATSUI Low-Level API.  For more low-level calls, see ATSUnicodeDirectAccess.h */
/********************************************************************************/
/* ---------------------------------------------------------------------------- */
/* GlyphInfo access                                                             */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUGetGlyphInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 9.1 and later
 */
extern OSStatus 
ATSUGetGlyphInfo(
  ATSUTextLayout        iTextLayout,
  UniCharArrayOffset    iLineStart,
  UniCharCount          iLineLength,
  ByteCount *           ioBufferSize,
  ATSUGlyphInfoArray *  oGlyphInfoPtr)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUDrawGlyphInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 9.1 and later
 */
extern OSStatus 
ATSUDrawGlyphInfo(
  ATSUGlyphInfoArray *  iGlyphInfoArray,
  Float32Point          iLocation)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/* Font Data Access                                                             */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUGlyphGetIdealMetrics()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 9.1 and later
 */
extern OSStatus 
ATSUGlyphGetIdealMetrics(
  ATSUStyle              iATSUStyle,
  ItemCount              iNumOfGlyphs,
  GlyphID                iGlyphIDs[],
  ByteOffset             iInputOffset,
  ATSGlyphIdealMetrics   oIdealMetrics[])                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGetNativeCurveType()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 9.1 and later
 */
extern OSStatus 
ATSUGetNativeCurveType(
  ATSUStyle       iATSUStyle,
  ATSCurveType *  oCurveType)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/* Device specific routines                                                     */
/* ---------------------------------------------------------------------------- */
/*
 *  ATSUGlyphGetScreenMetrics()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 9.1 and later
 */
extern OSStatus 
ATSUGlyphGetScreenMetrics(
  ATSUStyle               iATSUStyle,
  ItemCount               iNumOfGlyphs,
  GlyphID                 iGlyphIDs[],
  ByteOffset              iInputOffset,
  Boolean                 iForcingAntiAlias,
  Boolean                 iAntiAliasSwitch,
  ATSGlyphScreenMetrics   oScreenMetrics[])                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ---------------------------------------------------------------------------- */
/* ATSUGlyphGetQuadraticPaths callbacks                                         */
/* ---------------------------------------------------------------------------- */
typedef CALLBACK_API( OSStatus , ATSQuadraticLineProcPtr )(const Float32Point *pt1, const Float32Point *pt2, void *callBackDataPtr);
typedef CALLBACK_API( OSStatus , ATSQuadraticCurveProcPtr )(const Float32Point *pt1, const Float32Point *controlPt, const Float32Point *pt2, void *callBackDataPtr);
typedef CALLBACK_API( OSStatus , ATSQuadraticNewPathProcPtr )(void * callBackDataPtr);
typedef CALLBACK_API( OSStatus , ATSQuadraticClosePathProcPtr )(void * callBackDataPtr);
typedef STACK_UPP_TYPE(ATSQuadraticLineProcPtr)                 ATSQuadraticLineUPP;
typedef STACK_UPP_TYPE(ATSQuadraticCurveProcPtr)                ATSQuadraticCurveUPP;
typedef STACK_UPP_TYPE(ATSQuadraticNewPathProcPtr)              ATSQuadraticNewPathUPP;
typedef STACK_UPP_TYPE(ATSQuadraticClosePathProcPtr)            ATSQuadraticClosePathUPP;
/*
 *  NewATSQuadraticLineUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ATSQuadraticLineUPP
NewATSQuadraticLineUPP(ATSQuadraticLineProcPtr userRoutine)   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewATSQuadraticCurveUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ATSQuadraticCurveUPP
NewATSQuadraticCurveUPP(ATSQuadraticCurveProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewATSQuadraticNewPathUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ATSQuadraticNewPathUPP
NewATSQuadraticNewPathUPP(ATSQuadraticNewPathProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewATSQuadraticClosePathUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ATSQuadraticClosePathUPP
NewATSQuadraticClosePathUPP(ATSQuadraticClosePathProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeATSQuadraticLineUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeATSQuadraticLineUPP(ATSQuadraticLineUPP userUPP)       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeATSQuadraticCurveUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeATSQuadraticCurveUPP(ATSQuadraticCurveUPP userUPP)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeATSQuadraticNewPathUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeATSQuadraticNewPathUPP(ATSQuadraticNewPathUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeATSQuadraticClosePathUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeATSQuadraticClosePathUPP(ATSQuadraticClosePathUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeATSQuadraticLineUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeATSQuadraticLineUPP(
  const Float32Point *  pt1,
  const Float32Point *  pt2,
  void *                callBackDataPtr,
  ATSQuadraticLineUPP   userUPP)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeATSQuadraticCurveUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeATSQuadraticCurveUPP(
  const Float32Point *  pt1,
  const Float32Point *  controlPt,
  const Float32Point *  pt2,
  void *                callBackDataPtr,
  ATSQuadraticCurveUPP  userUPP)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeATSQuadraticNewPathUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeATSQuadraticNewPathUPP(
  void *                  callBackDataPtr,
  ATSQuadraticNewPathUPP  userUPP)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeATSQuadraticClosePathUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeATSQuadraticClosePathUPP(
  void *                    callBackDataPtr,
  ATSQuadraticClosePathUPP  userUPP)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  ATSUGlyphGetQuadraticPaths()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 9.1 and later
 */
extern OSStatus 
ATSUGlyphGetQuadraticPaths(
  ATSUStyle                  iATSUStyle,
  GlyphID                    iGlyphID,
  ATSQuadraticNewPathUPP     iNewPathProc,
  ATSQuadraticLineUPP        iLineProc,
  ATSQuadraticCurveUPP       iCurveProc,
  ATSQuadraticClosePathUPP   iClosePathProc,
  void *                     iCallbackDataPtr,
  OSStatus *                 oCallbackResult)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* ATSUGlyphGetCubicPaths callbacks */
typedef CALLBACK_API( OSStatus , ATSCubicMoveToProcPtr )(const Float32Point *pt, void *callBackDataPtr);
typedef CALLBACK_API( OSStatus , ATSCubicLineToProcPtr )(const Float32Point *pt, void *callBackDataPtr);
typedef CALLBACK_API( OSStatus , ATSCubicCurveToProcPtr )(const Float32Point *pt1, const Float32Point *pt2, const Float32Point *pt3, void *callBackDataPtr);
typedef CALLBACK_API( OSStatus , ATSCubicClosePathProcPtr )(void * callBackDataPtr);
typedef STACK_UPP_TYPE(ATSCubicMoveToProcPtr)                   ATSCubicMoveToUPP;
typedef STACK_UPP_TYPE(ATSCubicLineToProcPtr)                   ATSCubicLineToUPP;
typedef STACK_UPP_TYPE(ATSCubicCurveToProcPtr)                  ATSCubicCurveToUPP;
typedef STACK_UPP_TYPE(ATSCubicClosePathProcPtr)                ATSCubicClosePathUPP;
/*
 *  NewATSCubicMoveToUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ATSCubicMoveToUPP
NewATSCubicMoveToUPP(ATSCubicMoveToProcPtr userRoutine)       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewATSCubicLineToUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ATSCubicLineToUPP
NewATSCubicLineToUPP(ATSCubicLineToProcPtr userRoutine)       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewATSCubicCurveToUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ATSCubicCurveToUPP
NewATSCubicCurveToUPP(ATSCubicCurveToProcPtr userRoutine)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewATSCubicClosePathUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ATSCubicClosePathUPP
NewATSCubicClosePathUPP(ATSCubicClosePathProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeATSCubicMoveToUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeATSCubicMoveToUPP(ATSCubicMoveToUPP userUPP)           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeATSCubicLineToUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeATSCubicLineToUPP(ATSCubicLineToUPP userUPP)           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeATSCubicCurveToUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeATSCubicCurveToUPP(ATSCubicCurveToUPP userUPP)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeATSCubicClosePathUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeATSCubicClosePathUPP(ATSCubicClosePathUPP userUPP)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeATSCubicMoveToUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeATSCubicMoveToUPP(
  const Float32Point *  pt,
  void *                callBackDataPtr,
  ATSCubicMoveToUPP     userUPP)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeATSCubicLineToUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeATSCubicLineToUPP(
  const Float32Point *  pt,
  void *                callBackDataPtr,
  ATSCubicLineToUPP     userUPP)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeATSCubicCurveToUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeATSCubicCurveToUPP(
  const Float32Point *  pt1,
  const Float32Point *  pt2,
  const Float32Point *  pt3,
  void *                callBackDataPtr,
  ATSCubicCurveToUPP    userUPP)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeATSCubicClosePathUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeATSCubicClosePathUPP(
  void *                callBackDataPtr,
  ATSCubicClosePathUPP  userUPP)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  ATSUGlyphGetCubicPaths()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 9.1 and later
 */
extern OSStatus 
ATSUGlyphGetCubicPaths(
  ATSUStyle              iATSUStyle,
  GlyphID                iGlyphID,
  ATSCubicMoveToUPP      iMoveToProc,
  ATSCubicLineToUPP      iLineToProc,
  ATSCubicCurveToUPP     iCurveToProc,
  ATSCubicClosePathUPP   iClosePathProc,
  void *                 iCallbackDataPtr,
  OSStatus *             oCallbackResult)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ATSUGlyphGetCurvePaths()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ATSUnicodeLib 9.1 and later
 */
extern OSStatus 
ATSUGlyphGetCurvePaths(
  ATSUStyle         iATSUStyle,
  GlyphID           iGlyphID,
  ByteCount *       ioBufferSize,
  ATSUCurvePaths *  oPaths)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*************************************************************************/
/*
 *  ATSUSetHighlightingMethod()
 *  
 *  Discussion:
 *    By default ATSUI will highlight text by simply inverting the
 *    text. When a user is using gray-scale text this does not always
 *    provide the best appearance. On MacOS 9 gray-scale is available,
 *    but can be turned off by a user.  MacOS X always uses gray-scale.
 *     A better way to highlight gray-scale text is to first paint the
 *    highlight color and then redraw the text.  Begining with version
 *    2.0 (?) of ATSUI this method is available.  However,
 *    unhighlighting text when this technique is used is more
 *    complicated.  The details of exactly what the background looks
 *    like must be known to whoever unhighlights the text. When using
 *    the redraw method of highlighting ATSUI will redraw the
 *    background if it is a single color(e.g. white).  If this is the
 *    case set iMethod to kRedrawToHighlight, set
 *    iUnhighlightData.dataType to kATSUBackgroundColor and specify the
 *    background color in
 *    iUnhighlightData.unhighlightData.backgroundColor.  When these
 *    settings are supplied then ATSUI will calculate the highlight
 *    area paint it with the specified backgroundColor and then redraw
 *    the text. For more complex backgrounds (multiple colors,
 *    patterns, pictures, etc.) you need to supply a callback that
 *    ATSUI will call when the background needs to be repainted (See
 *    above RedrawBackgroundProcPtr ).  When your callback is called
 *    you should redraw the background.  If you choose to also redraw
 *    the text then you should return false as a function result. If
 *    you return true ATSUI will redraw any text that needs to be
 *    redrawn.
 *  
 *  Parameters:
 *    
 *    iTextLayout:
 *      The layout to which this highlight method should be applied.
 *    
 *    iMethod:
 *      The type of highlighting to use (inversion or redrawing) The
 *      default is inversion.  If you are happy with that technique
 *      there is no reason to call this function.
 *    
 *    iUnhighlightData:
 *      Data needed to redraw the background or NULL if inversion is
 *      being chosen.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSUSetHighlightingMethod(
  ATSUTextLayout               iTextLayout,
  ATSUHighlightMethod          iMethod,
  const ATSUUnhighlightData *  iUnhighlightData)              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __ATSUNICODE__ */

