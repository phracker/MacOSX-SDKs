/*
     File:       ATS/ScalerStreamTypes.h
 
     Contains:   Scaler streaming data structures and constants for OFA 1.x
 
     Version:    ATS-184.7.7~42
 
     Copyright:  © 1994-2006 by Apple Computer, Inc., all rights reserved.
 
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

#pragma options align=mac68k

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
  streamTypeModifierMask        = (long)0xFFFFF000 /* 16 bits for Apple, 4 bits for scaler */
};

/* Possible streamed font formats */
typedef unsigned long                   scalerStreamTypeFlag;
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

typedef long                            scalerStreamAction;
enum {
  selectAllVariations           = -1    /* Special variationCount value meaning include all variation data */
};

struct scalerPrerequisiteItem {
  long                enumeration;            /* Shorthand tag identifying the item */
  long                size;                   /* Worst case vm in printer item requires */
  unsigned char       name[1];                /* Name to be used by the client when emitting the item (Pascal string) */
};
typedef struct scalerPrerequisiteItem   scalerPrerequisiteItem;
struct scalerStream {
  const void *        streamRefCon;           /* <- private reference for client */
  const char *        targetVersion;          /* <- e.g. Postscript printer name (C string) */
  scalerStreamTypeFlag  types;                /* <->    Data stream formats desired/supplied */
  scalerStreamAction  action;                 /* <-     What action to take */
  unsigned long       memorySize;             /* -> Worst case memory use (vm) in printer or as sfnt */
  long                variationCount;         /* <- The number of variations, or selectAllVariations */
  const void *        variations;             /* <- A pointer to an array of the variations (gxFontVariation) */
  union {
                                              /* Normal font streaming information*/
    struct {
      const unsigned short * encoding;        /* <- Intention is * unsigned short[256] */
      long *              glyphBits;          /* <->    Bitvector: a bit for each glyph, 1 = desired/supplied */
      char *              name;               /* <->    The printer font name to use/used (C string) */
    }                       font;

                                              /* Used to obtain a list of prerequisites from the scaler*/
    struct {
      long                size;               /* ->     Size of the prereq. list in bytes (0 indicates no prerequisites)*/
      void *              list;               /* <- Pointer to client block to hold list (nil = list size query only) */
    }                       prerequisiteQuery;

    long                prerequisiteItem;     /* <-     Enumeration value for the prerequisite item to be streamed.*/

    long                variationQueryResult; /* -> Output from the variationQueryStreamAction */
  }                       info;
};
typedef struct scalerStream             scalerStream;
struct scalerStreamData {
  long                hexFlag;                /* Indicates that the data is to be interpreted as hex, versus binary */
  long                byteCount;              /* Number of bytes in the data being streamed */
  const void *        data;                   /* Pointer to the data being streamed */
};
typedef struct scalerStreamData         scalerStreamData;

#pragma options align=reset


#endif /* __SCALERSTREAMTYPES__ */

