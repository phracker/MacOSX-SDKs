/*
     File:       ATS/ScalerStreamTypes.h
 
     Contains:   Scaler streaming data structures and constants for OFA 1.x
 
     Version:    ATS
 
     Copyright:  © 1994-2011 by Apple Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __SCALERSTREAMTYPES__
#define __SCALERSTREAMTYPES__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __SFNTTYPES__
#include <ATS/SFNTTypes.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#pragma pack(push, 2)

/* ScalerStream input/output types */
enum {
  cexec68K                      = 0x00000001,
  truetypeStreamType            = 0x00000001,
  type1StreamType               = 0x00000002,
  type3StreamType               = 0x00000004,
  type42StreamType              = 0x00000008,
  type42GXStreamType            = 0x00000010,
  portableStreamType            = 0x00000020,
  flattenedStreamType           = 0x00000040,
  cidType2StreamType            = 0x00000080,
  cidType0StreamType            = 0x00000100,
  type1CFFStreamType            = 0x00000200,
  evenOddModifierStreamType     = 0x00008000,
  eexecBinaryModifierStreamType = 0x00010000, /* encrypted portion of Type1Stream to be binary */
  unicodeMappingModifierStreamType = 0x00020000, /* include glyph ID to unicode mapping info for PDF */
  scalerSpecifcModifierMask     = 0x0000F000, /* for scaler's internal use */
  streamTypeModifierMask        = (int)0xFFFFF000 /* 16 bits for Apple, 4 bits for scaler */
};

/* Possible streamed font formats */
typedef UInt32                          scalerStreamTypeFlag;
enum {
  downloadStreamAction          = 0,    /* Transmit the (possibly sparse) font data */
  asciiDownloadStreamAction     = 1,    /* Transmit font data to a 7-bit ASCII destination */
  fontSizeQueryStreamAction     = 2,    /* Estimate in-printer memory used if the font were downloaded */
  encodingOnlyStreamAction      = 3,    /* Transmit only the encoding for the font */
  prerequisiteQueryStreamAction = 4,    /* Return a list of prerequisite items needed for the font */
  prerequisiteItemStreamAction  = 5,    /* Transmit a specified prerequisite item */
  variationQueryStreamAction    = 6,    /* Return information regarding support for variation streaming */
  variationPSOperatorStreamAction = 7   /* Transmit Postscript code necessary to effect variation of a font */
};

typedef SInt32                          scalerStreamAction;
enum {
  selectAllVariations           = -1    /* Special variationCount value meaning include all variation data */
};

struct scalerPrerequisiteItem {
  SInt32              enumeration;            /* Shorthand tag identifying the item */
  SInt32              size;                   /* Worst case vm in printer item requires. Never > than 16-bit quantity */
  unsigned char       name[1];                /* Name to be used by the client when emitting the item (Pascal string) */
};
typedef struct scalerPrerequisiteItem   scalerPrerequisiteItem;
struct scalerStream {
  const void *        streamRefCon;           /* <- private reference for client */
  const char *        targetVersion;          /* <- e.g. Postscript printer name (C string) */
  scalerStreamTypeFlag  types;                /* <->    Data stream formats desired/supplied */
  scalerStreamAction  action;                 /* <-     What action to take */
  UInt32              memorySize;             /* -> Worst case memory use (vm) in printer or as sfnt */
  SInt32              variationCount;         /* <- The number of variations, or selectAllVariations */
  const void *        variations;             /* <- A pointer to an array of the variations (gxFontVariation) */
  union {
                                              /* Normal font streaming information*/
    struct {
      const unsigned short * encoding;        /* <- Intention is * unsigned short[256] */
      SInt32 *            glyphBits;          /* <->    Bitvector: a bit for each glyph, 1 = desired/supplied */
      const char *        name;               /* <->    The printer font name to use/used (C string) */
    }                       font;

                                              /* Used to obtain a list of prerequisites from the scaler*/
    struct {
      SInt32              size;               /* ->     Size of the prereq. list in bytes (0 indicates no prerequisites)*/
      const void *        list;               /* <- Pointer to client block to hold list (nil = list size query only) */
    }                       prerequisiteQuery;

    SInt32              prerequisiteItem;     /* <-     Enumeration value for the prerequisite item to be streamed.*/

    SInt32              variationQueryResult; /* -> Output from the variationQueryStreamAction */
  }                       info;
};
typedef struct scalerStream             scalerStream;
struct scalerStreamData {
  SInt32              hexFlag;                /* Indicates that the data is to be interpreted as hex, versus binary */
  SInt32              byteCount;              /* Number of bytes in the data being streamed */
  const void *        data;                   /* Pointer to the data being streamed */
};
typedef struct scalerStreamData         scalerStreamData;

#pragma pack(pop)


#endif /* __SCALERSTREAMTYPES__ */

