/*
     File:       ColorSync/CMApplication.h
 
     Contains:   Color Matching Interfaces
 
     Copyright:  1992-2005 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult http://developer.apple.com/bugreporter/
 
*/
#ifndef __CMAPPLICATION__
#define __CMAPPLICATION__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __CMICCPROFILE__
#include <ColorSync/CMICCProfile.h>
#endif

#ifndef __CMTYPES__
#include <ColorSync/CMTypes.h>
#endif

#include <ColorSync/CMBase.h>

#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if !__LP64__
#if defined(_MSC_VER)
#pragma pack(push, CMApplication_h, 2)
#else
#pragma options align=mac68k
#endif
#endif

enum {
  kDefaultCMMSignature          = 'appl'
};

#if !__LP64__ && !TARGET_OS_WIN32
/* PicComment IDs */
enum {
  cmBeginProfile                = 220,
  cmEndProfile                  = 221,
  cmEnableMatching              = 222,
  cmDisableMatching             = 223,
  cmComment                     = 224
};

/* PicComment selectors for cmComment */
enum {
  cmBeginProfileSel             = 0,
  cmContinueProfileSel          = 1,
  cmEndProfileSel               = 2,
  cmProfileIdentifierSel        = 3
};

/* Defines for version 1.0 CMProfileSearchRecord.fieldMask */
enum {
  cmMatchCMMType                = 0x00000001,
  cmMatchApplProfileVersion     = 0x00000002,
  cmMatchDataType               = 0x00000004,
  cmMatchDeviceType             = 0x00000008,
  cmMatchDeviceManufacturer     = 0x00000010,
  cmMatchDeviceModel            = 0x00000020,
  cmMatchDeviceAttributes       = 0x00000040,
  cmMatchFlags                  = 0x00000080,
  cmMatchOptions                = 0x00000100,
  cmMatchWhite                  = 0x00000200,
  cmMatchBlack                  = 0x00000400
};

/* Defines for version 2.0 CMSearchRecord.searchMask */
enum {
  cmMatchAnyProfile             = 0x00000000,
  cmMatchProfileCMMType         = 0x00000001,
  cmMatchProfileClass           = 0x00000002,
  cmMatchDataColorSpace         = 0x00000004,
  cmMatchProfileConnectionSpace = 0x00000008,
  cmMatchManufacturer           = 0x00000010,
  cmMatchModel                  = 0x00000020,
  cmMatchAttributes             = 0x00000040,
  cmMatchProfileFlags           = 0x00000080
};

#endif // !__LP64__ && !TARGET_OS_WIN32

/* Flags for PostScript-related functions */
enum {
  cmPS7bit                      = 1,
  cmPS8bit                      = 2
};

#if !__LP64__ && !TARGET_OS_WIN32
/* Flags for profile embedding functions */
enum {
  cmEmbedWholeProfile           = 0x00000000,
  cmEmbedProfileIdentifier      = 0x00000001
};
#endif // !__LP64__ && !TARGET_OS_WIN32

/* Commands for CMFlattenUPP() */
enum {
  cmOpenReadSpool               = 1,
  cmOpenWriteSpool              = 2,
  cmReadSpool                   = 3,
  cmWriteSpool                  = 4,
  cmCloseSpool                  = 5
};

/* Commands for CMAccessUPP() */
enum {
  cmOpenReadAccess              = 1,
  cmOpenWriteAccess             = 2,
  cmReadAccess                  = 3,
  cmWriteAccess                 = 4,
  cmCloseAccess                 = 5,
  cmCreateNewAccess             = 6,
  cmAbortWriteAccess            = 7,
  cmBeginAccess                 = 8,
  cmEndAccess                   = 9
};

/* Use types for CMGet/SetDefaultProfileByUse() */
enum {
  cmInputUse                    = 'inpt',
  cmOutputUse                   = 'outp',
  cmDisplayUse                  = 'dply',
  cmProofUse                    = 'pruf'
};


/* Union of 1.0 2.0, and 4.0 profile header variants */
union CMAppleProfileHeader {
#if !__LP64__ && !TARGET_OS_WIN32
  CMHeader            cm1;
#endif // !__LP64__ && !TARGET_OS_WIN32
  CM2Header           cm2;
  CM4Header           cm4;
};
typedef union CMAppleProfileHeader      CMAppleProfileHeader;

/* CWConcatColorWorld() definitions */
typedef struct CMConcatProfileSet {
  UInt16              keyIndex;               /* Zero-based */
  UInt16              count;                  /* Min 1 */
  CMProfileRef        profileSet[1];          /* Variable. Ordered from Source -> Dest */
} CMConcatProfileSet;

/* NCWConcatColorWorld() definitions */
typedef struct NCMConcatProfileSpec {
  UInt32              renderingIntent;        /* renderingIntent override */
  UInt32              transformTag;           /* transform enumerations defined below */
  CMProfileRef        profile;                /* profile */
} NCMConcatProfileSpec;

typedef struct NCMConcatProfileSet {
  OSType              cmm;                    /* e.g. 'KCMS', 'appl', ...  uniquely ids the cmm, or 0000 */
  UInt32              flags;                  /* specify quality, lookup only, no gamut checking ... */
  UInt32              flagsMask;              /* which bits of 'flags' to use to override profile */
  UInt32              profileCount;           /* how many ProfileSpecs in the following set */
  NCMConcatProfileSpec  profileSpecs[1];      /* Variable. Ordered from Source -> Dest */
} NCMConcatProfileSet;

enum {
  kNoTransform                  = 0,    /* Not used */
  kUseAtoB                      = 1,    /* Use 'A2B*' tag from this profile or equivalent */
  kUseBtoA                      = 2,    /* Use 'B2A*' tag from this profile or equivalent */
  kUseBtoB                      = 3,    /* Use 'pre*' tag from this profile or equivalent */
                                        /* For typical device profiles the following synonyms may be useful */
  kDeviceToPCS                  = kUseAtoB, /* Device Dependent to Device Independent */
  kPCSToDevice                  = kUseBtoA, /* Device Independent to Device Dependent */
  kPCSToPCS                     = kUseBtoB, /* Independent, through device's gamut */
  kUseProfileIntent             = (int)0xFFFFFFFF /* For renderingIntent in NCMConcatProfileSpec    */
};


/* ColorSync color data types */
typedef struct CMRGBColor {
  UInt16              red;                    /* 0..65535 */
  UInt16              green;
  UInt16              blue;
} CMRGBColor;

typedef struct CMCMYKColor {
  UInt16              cyan;                   /* 0..65535 */
  UInt16              magenta;
  UInt16              yellow;
  UInt16              black;
} CMCMYKColor;

typedef struct CMCMYColor {
  UInt16              cyan;                   /* 0..65535 */
  UInt16              magenta;
  UInt16              yellow;
} CMCMYColor;

typedef struct CMHLSColor {
  UInt16              hue;                    /* 0..65535. Fraction of circle. Red at 0 */
  UInt16              lightness;              /* 0..65535 */
  UInt16              saturation;             /* 0..65535 */
} CMHLSColor;

typedef struct CMHSVColor {
  UInt16              hue;                    /* 0..65535. Fraction of circle. Red at 0 */
  UInt16              saturation;             /* 0..65535 */
  UInt16              value;                  /* 0..65535 */
} CMHSVColor;

typedef struct CMLabColor {
  UInt16              L;                      /* 0..65535 maps to 0..100 */
  UInt16              a;                      /* 0..65535 maps to -128..127.996 */
  UInt16              b;                      /* 0..65535 maps to -128..127.996 */
} CMLabColor;

typedef struct CMLuvColor {
  UInt16              L;                      /* 0..65535 maps to 0..100 */
  UInt16              u;                      /* 0..65535 maps to -128..127.996 */
  UInt16              v;                      /* 0..65535 maps to -128..127.996 */
} CMLuvColor;

typedef struct CMYxyColor {
  UInt16              capY;                   /* 0..65535 maps to 0..1 */
  UInt16              x;                      /* 0..65535 maps to 0..1 */
  UInt16              y;                      /* 0..65535 maps to 0..1 */
} CMYxyColor;

typedef struct CMGrayColor {
  UInt16              gray;                   /* 0..65535 */
} CMGrayColor;

typedef struct CMMultichannel5Color {
  UInt8               components[5];          /* 0..255 */
} CMMultichannel5Color;

typedef struct CMMultichannel6Color {
  UInt8               components[6];          /* 0..255 */
} CMMultichannel6Color;

typedef struct CMMultichannel7Color {
  UInt8               components[7];          /* 0..255 */
} CMMultichannel7Color;

typedef struct CMMultichannel8Color {
  UInt8               components[8];          /* 0..255 */
} CMMultichannel8Color;

typedef struct CMNamedColor {
  UInt32              namedColorIndex;        /* 0..a lot */
} CMNamedColor;

typedef union CMColor {
  CMRGBColor          rgb;
  CMHSVColor          hsv;
  CMHLSColor          hls;
  CMXYZColor          XYZ;
  CMLabColor          Lab;
  CMLuvColor          Luv;
  CMYxyColor          Yxy;
  CMCMYKColor         cmyk;
  CMCMYColor          cmy;
  CMGrayColor         gray;
  CMMultichannel5Color  mc5;
  CMMultichannel6Color  mc6;
  CMMultichannel7Color  mc7;
  CMMultichannel8Color  mc8;
  CMNamedColor        namedColor;
} CMColor;

#if !__LP64__ && !TARGET_OS_WIN32
/* GetIndexedProfile() search definition*/
typedef struct CMProfileSearchRecord {
  CMHeader            header;
  UInt32              fieldMask;
  UInt32              reserved[2];
} CMProfileSearchRecord, *CMProfileSearchRecordPtr, **CMProfileSearchRecordHandle;

/* CMNewProfileSearch() search definition */
typedef struct CMSearchRecord {
  OSType              CMMType;
  OSType              profileClass;
  OSType              dataColorSpace;
  OSType              profileConnectionSpace;
  UInt32              deviceManufacturer;
  UInt32              deviceModel;
  UInt32              deviceAttributes[2];
  UInt32              profileFlags;
  UInt32              searchMask;
  CMProfileFilterUPP  filter;
} CMSearchRecord;
#endif // !__LP64__ && !TARGET_OS_WIN32

/* CMMIterateUPP() structure */
typedef struct CMMInfo {
  size_t              dataSize;               /* Size of this structure - compatibility*/
  OSType              CMMType;                /* Signature, e.g. 'appl', 'HDM ' or 'KCMS'*/
  OSType              CMMMfr;                 /* Vendor, e.g. 'appl'*/
  UInt32              CMMVersion;             /* CMM version number*/
  unsigned char       ASCIIName[32];          /* pascal string - name*/
  unsigned char       ASCIIDesc[256];         /* pascal string - description or copyright*/
  UniCharCount        UniCodeNameCount;       /* count of UniChars in following array*/
  UniChar             UniCodeName[32];        /* the name in UniCode chars*/
  UniCharCount        UniCodeDescCount;       /* count of UniChars in following array*/
  UniChar             UniCodeDesc[256];       /* the description in UniCode chars*/
} CMMInfo;

/* GetCWInfo() structures */

#if !__LP64__ && !TARGET_OS_WIN32

typedef struct CMMInfoRecord {
  OSType              CMMType;
  long                CMMVersion;
} CMMInfoRecord;

typedef struct CMCWInfoRecord {
  UInt32              cmmCount;
  CMMInfoRecord       cmmInfo[2];
} CMCWInfoRecord;

/* profile identifier structures */
typedef struct CMProfileIdentifier {
  CM2Header           profileHeader;
  CMDateTime          calibrationDate;
  UInt32              ASCIIProfileDescriptionLen;
  char                ASCIIProfileDescription[1]; /* variable length */
} CMProfileIdentifier, *CMProfileIdentifierPtr;
#endif // !__LP64__ && !TARGET_OS_WIN32

/* colorspace masks */
enum {
  cmColorSpaceSpaceMask         = 0x0000003F,
  cmColorSpacePremulAlphaMask   = 0x00000040,
  cmColorSpaceAlphaMask         = 0x00000080,
  cmColorSpaceSpaceAndAlphaMask = 0x000000FF,
  cmColorSpacePackingMask       = 0x0000FF00,
  cmColorSpaceEncodingMask      = 0x000F0000,
  cmColorSpaceReservedMask      = (int)0xFFF00000
};

/* packing formats */
enum {
  cmNoColorPacking              = 0x0000,
  cmWord5ColorPacking           = 0x0500,
  cmWord565ColorPacking         = 0x0600,
  cmLong8ColorPacking           = 0x0800,
  cmLong10ColorPacking          = 0x0A00,
  cmAlphaFirstPacking           = 0x1000,
  cmOneBitDirectPacking         = 0x0B00,
  cmAlphaLastPacking            = 0x0000,
  cm8_8ColorPacking             = 0x2800,
  cm16_8ColorPacking            = 0x2000,
  cm24_8ColorPacking            = 0x2100,
  cm32_8ColorPacking            = cmLong8ColorPacking,
  cm40_8ColorPacking            = 0x2200,
  cm48_8ColorPacking            = 0x2300,
  cm56_8ColorPacking            = 0x2400,
  cm64_8ColorPacking            = 0x2500,
  cm32_16ColorPacking           = 0x2600,
  cm48_16ColorPacking           = 0x2900,
  cm64_16ColorPacking           = 0x2A00,
  cm32_32ColorPacking           = 0x2700,
  cmLittleEndianPacking         = 0x4000,
  cmReverseChannelPacking       = 0x8000
};

/* channel encoding format */
enum {
  cmSRGB16ChannelEncoding       = 0x00010000 /* used for sRGB64 encoding ( ±3.12 format)*/
};

/* general colorspaces */
enum {
  cmNoSpace                     = 0x0000,
  cmRGBSpace                    = 0x0001,
  cmCMYKSpace                   = 0x0002,
  cmHSVSpace                    = 0x0003,
  cmHLSSpace                    = 0x0004,
  cmYXYSpace                    = 0x0005,
  cmXYZSpace                    = 0x0006,
  cmLUVSpace                    = 0x0007,
  cmLABSpace                    = 0x0008,
  cmReservedSpace1              = 0x0009,
  cmGraySpace                   = 0x000A,
  cmReservedSpace2              = 0x000B,
  cmGamutResultSpace            = 0x000C,
  cmNamedIndexedSpace           = 0x0010,
  cmMCFiveSpace                 = 0x0011,
  cmMCSixSpace                  = 0x0012,
  cmMCSevenSpace                = 0x0013,
  cmMCEightSpace                = 0x0014,
  cmAlphaPmulSpace              = 0x0040,
  cmAlphaSpace                  = 0x0080,
  cmRGBASpace                   = cmRGBSpace + cmAlphaSpace,
  cmGrayASpace                  = cmGraySpace + cmAlphaSpace,
  cmRGBAPmulSpace               = cmRGBASpace + cmAlphaPmulSpace,
  cmGrayAPmulSpace              = cmGrayASpace + cmAlphaPmulSpace
};

/* supported CMBitmapColorSpaces - Each of the following is a */
/* combination of a general colospace and a packing formats. */
/* Each can also be or'd with cmReverseChannelPacking. */
enum {
  cmGray8Space                  = cmGraySpace + cm8_8ColorPacking,
  cmGray16Space                 = cmGraySpace,
  cmGray16LSpace                = cmGraySpace + cmLittleEndianPacking,
  cmGrayA16Space                = cmGrayASpace + cm16_8ColorPacking,
  cmGrayA32Space                = cmGrayASpace,
  cmGrayA32LSpace               = cmGrayASpace + cmLittleEndianPacking,
  cmGrayA16PmulSpace            = cmGrayAPmulSpace + cm16_8ColorPacking,
  cmGrayA32PmulSpace            = cmGrayAPmulSpace,
  cmGrayA32LPmulSpace           = cmGrayAPmulSpace + cmLittleEndianPacking,
  cmRGB16Space                  = cmRGBSpace + cmWord5ColorPacking,
  cmRGB16LSpace                 = cmRGBSpace + cmWord5ColorPacking + cmLittleEndianPacking,
  cmRGB565Space                 = cmRGBSpace + cmWord565ColorPacking,
  cmRGB565LSpace                = cmRGBSpace + cmWord565ColorPacking + cmLittleEndianPacking,
  cmRGB24Space                  = cmRGBSpace + cm24_8ColorPacking,
  cmRGB32Space                  = cmRGBSpace + cm32_8ColorPacking,
  cmRGB48Space                  = cmRGBSpace + cm48_16ColorPacking,
  cmRGB48LSpace                 = cmRGBSpace + cm48_16ColorPacking + cmLittleEndianPacking,
  cmARGB32Space                 = cmRGBASpace + cm32_8ColorPacking + cmAlphaFirstPacking,
  cmARGB64Space                 = cmRGBASpace + cm64_16ColorPacking + cmAlphaFirstPacking,
  cmARGB64LSpace                = cmRGBASpace + cm64_16ColorPacking + cmAlphaFirstPacking + cmLittleEndianPacking,
  cmRGBA32Space                 = cmRGBASpace + cm32_8ColorPacking + cmAlphaLastPacking,
  cmRGBA64Space                 = cmRGBASpace + cm64_16ColorPacking + cmAlphaLastPacking,
  cmRGBA64LSpace                = cmRGBASpace + cm64_16ColorPacking + cmAlphaLastPacking + cmLittleEndianPacking,
  cmARGB32PmulSpace             = cmRGBAPmulSpace + cm32_8ColorPacking + cmAlphaFirstPacking,
  cmARGB64PmulSpace             = cmRGBAPmulSpace + cm64_16ColorPacking + cmAlphaFirstPacking,
  cmARGB64LPmulSpace            = cmRGBAPmulSpace + cm64_16ColorPacking + cmAlphaFirstPacking + cmLittleEndianPacking,
  cmRGBA32PmulSpace             = cmRGBAPmulSpace + cm32_8ColorPacking + cmAlphaLastPacking,
  cmRGBA64PmulSpace             = cmRGBAPmulSpace + cm64_16ColorPacking + cmAlphaLastPacking,
  cmRGBA64LPmulSpace            = cmRGBAPmulSpace + cm64_16ColorPacking + cmAlphaLastPacking + cmLittleEndianPacking,
  cmCMYK32Space                 = cmCMYKSpace + cm32_8ColorPacking,
  cmCMYK64Space                 = cmCMYKSpace + cm64_16ColorPacking,
  cmCMYK64LSpace                = cmCMYKSpace + cm64_16ColorPacking + cmLittleEndianPacking,
  cmHSV32Space                  = cmHSVSpace + cmLong10ColorPacking,
  cmHLS32Space                  = cmHLSSpace + cmLong10ColorPacking,
  cmYXY32Space                  = cmYXYSpace + cmLong10ColorPacking,
  cmXYZ24Space                  = cmXYZSpace + cm24_8ColorPacking,
  cmXYZ32Space                  = cmXYZSpace + cmLong10ColorPacking,
  cmXYZ48Space                  = cmXYZSpace + cm48_16ColorPacking,
  cmXYZ48LSpace                 = cmXYZSpace + cm48_16ColorPacking + cmLittleEndianPacking,
  cmLUV32Space                  = cmLUVSpace + cmLong10ColorPacking,
  cmLAB24Space                  = cmLABSpace + cm24_8ColorPacking,
  cmLAB32Space                  = cmLABSpace + cmLong10ColorPacking,
  cmLAB48Space                  = cmLABSpace + cm48_16ColorPacking,
  cmLAB48LSpace                 = cmLABSpace + cm48_16ColorPacking + cmLittleEndianPacking,
  cmGamutResult1Space           = cmOneBitDirectPacking + cmGamutResultSpace,
  cmNamedIndexed32Space         = cm32_32ColorPacking + cmNamedIndexedSpace,
  cmNamedIndexed32LSpace        = cm32_32ColorPacking + cmNamedIndexedSpace + cmLittleEndianPacking,
  cmMCFive8Space                = cm40_8ColorPacking + cmMCFiveSpace,
  cmMCSix8Space                 = cm48_8ColorPacking + cmMCSixSpace,
  cmMCSeven8Space               = cm56_8ColorPacking + cmMCSevenSpace,
  cmMCEight8Space               = cm64_8ColorPacking + cmMCEightSpace
};


typedef UInt32                          CMBitmapColorSpace;

typedef struct CMBitmap {
  char *              image;
  size_t              width;
  size_t              height;
  size_t              rowBytes;
  size_t              pixelSize;
  CMBitmapColorSpace  space;
  UInt32              user1;
  UInt32              user2;
} CMBitmap;


/* Profile Locations */

enum {
#if !__LP64__ && !TARGET_OS_WIN32
  CS_MAX_PATH                   = 256
#elif TARGET_OS_WIN32
  CS_MAX_PATH                   = 1024,
  WIN_CS_MAX_PATH               = CS_MAX_PATH / sizeof(TCHAR)
#else
  CS_MAX_PATH                   = 1024
#endif // !__LP64__ && !TARGET_OS_WIN32
};


enum {
  cmNoProfileBase               = 0,
#if !__LP64__ && !TARGET_OS_WIN32
  cmFileBasedProfile            = 1,
  cmHandleBasedProfile          = 2,
  cmPtrBasedProfile             = 3,
  cmProcedureBasedProfile       = 4,
#endif // !__LP64__ && !TARGET_OS_WIN32
  cmPathBasedProfile            = 5,
  cmBufferBasedProfile          = 6
};


#if !__LP64__ && !TARGET_OS_WIN32
/* This structure is deprecated in Mac OS X 10.5. Use CMPathLocation instead.*/
typedef struct CMFileLocation {
  FSSpec              spec;
} CMFileLocation;
#endif // !__LP64__ && !TARGET_OS_WIN32

typedef struct CMHandleLocation {
  Handle              h;
} CMHandleLocation;

#if !__LP64__ && !TARGET_OS_WIN32
/* This structure is deprecated in Mac OS X 10.5. Use CMBufferLocation instead.*/
typedef struct CMPtrLocation {
  Ptr                 p;
} CMPtrLocation;

/* This structure is deprecated in Mac OS X 10.5.*/
typedef struct CMProcedureLocation {
  CMProfileAccessUPP  proc;
  void *              refCon;
} CMProcedureLocation;
#endif // !__LP64__ && !TARGET_OS_WIN32

typedef struct CMPathLocation {
#if TARGET_OS_WIN32
  TCHAR               path[WIN_CS_MAX_PATH];
#else
  char                path[CS_MAX_PATH];
#endif
} CMPathLocation;

typedef struct CMBufferLocation {
  void *              buffer;
  UInt32              size;
} CMBufferLocation;

typedef union CMProfLoc {
#if !__LP64__ && !TARGET_OS_WIN32
  CMFileLocation      fileLoc;
#endif // !__LP64__ && !TARGET_OS_WIN32
  CMHandleLocation    handleLoc;
#if !__LP64__ && !TARGET_OS_WIN32
  CMPtrLocation       ptrLoc;
  CMProcedureLocation procLoc;
#endif // !__LP64__ && !TARGET_OS_WIN32
  CMPathLocation      pathLoc;
  CMBufferLocation    bufferLoc;
} CMProfLoc;

typedef struct CMProfileLocation {
  short               locType;
  CMProfLoc           u;
} CMProfileLocation;

enum {
  cmOriginalProfileLocationSize = 72,
  cmCurrentProfileLocationSize  = sizeof(CMProfileLocation)
};


/* Struct and enums used for Profile iteration */

enum {
  cmProfileIterateDataVersion1  = 0x00010000,
  cmProfileIterateDataVersion2  = 0x00020000, /* Added makeAndModel*/
  cmProfileIterateDataVersion3  = 0x00030000 /* Added MD5 digest*/
};

typedef struct CMProfileIterateData {
  UInt32              dataVersion;            /* cmProfileIterateDataVersion2 */
  CM2Header           header;
  ScriptCode          code;
  Str255              name;
  CMProfileLocation   location;
  UniCharCount        uniCodeNameCount;
  UniChar *           uniCodeName;
  unsigned char *     asciiName;
  CMMakeAndModel *    makeAndModel;
  CMProfileMD5 *      digest;                 /* Derived from the RSA Data Security, Inc. MD5 Message-Digest Algorithm */
} CMProfileIterateData;


/* Caller-supplied callback function for Profile iteration */

typedef CALLBACK_API( OSErr , CMProfileIterateProcPtr )(CMProfileIterateData *iterateData, void *refCon);

typedef STACK_UPP_TYPE(CMProfileIterateProcPtr)                 CMProfileIterateUPP;

#if TARGET_RT_MAC_CFM
  CSEXTERN CMProfileIterateUPP
  NewCMProfileIterateUPP(CMProfileIterateProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

  CSEXTERN OSErr
  InvokeCMProfileIterateUPP(
    CMProfileIterateData *  iterateData,
    void *                  refCon,
    CMProfileIterateUPP     userUPP)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

  CSEXTERN void
  DisposeCMProfileIterateUPP(CMProfileIterateUPP userUPP)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
#else
  CF_INLINE CMProfileIterateUPP NewCMProfileIterateUPP(CMProfileIterateProcPtr userRoutine)
    { return (CMProfileIterateUPP)userRoutine; }

  CF_INLINE OSErr InvokeCMProfileIterateUPP(CMProfileIterateData * iterateData, void * refCon, CMProfileIterateUPP userUPP)
    { return (*((CMProfileIterateProcPtr)userUPP))(iterateData, refCon); }

#ifdef __cplusplus
  CF_INLINE void DisposeCMProfileIterateUPP(CMProfileIterateUPP) {}
#else
  CF_INLINE void DisposeCMProfileIterateUPP(CMProfileIterateUPP userUPP) {}
#endif
#endif // TARGET_RT_MAC_CFM


/* Caller-supplied callback function for CMM iteration */

typedef CALLBACK_API( OSErr , CMMIterateProcPtr )(CMMInfo *iterateData, void *refCon);

typedef STACK_UPP_TYPE(CMMIterateProcPtr)                       CMMIterateUPP;

#if TARGET_RT_MAC_CFM
  CSEXTERN CMMIterateUPP
  NewCMMIterateUPP(CMMIterateProcPtr userRoutine)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

  CSEXTERN OSErr
  InvokeCMMIterateUPP(
    CMMInfo *      iterateData,
    void *         refCon,
    CMMIterateUPP  userUPP)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

  CSEXTERN void
  DisposeCMMIterateUPP(CMMIterateUPP userUPP)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
#else
  CF_INLINE CMMIterateUPP NewCMMIterateUPP(CMMIterateProcPtr userRoutine)
    { return (CMMIterateUPP)userRoutine; }

  CF_INLINE OSErr InvokeCMMIterateUPP(CMMInfo * iterateData, void * refCon, CMMIterateUPP userUPP)
    { return (*((CMMIterateProcPtr)userUPP))(iterateData, refCon); }

#ifdef __cplusplus
  CF_INLINE void DisposeCMMIterateUPP(CMMIterateUPP) {}
#else
  CF_INLINE void DisposeCMMIterateUPP(CMMIterateUPP userUPP) {}
#endif
#endif // TARGET_RT_MAC_CFM


typedef CALLBACK_API_C( void , CMLabToLabProcPtr )(float *L, float *a, float *b, void *refcon);


/* Creating Profiles */

CSEXTERN CMError 
CMNewProfile(
  CMProfileRef *             prof,
  const CMProfileLocation *  theProfile)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#if !__LP64__ && !TARGET_OS_WIN32
/* This function is deprecated in Mac OS X 10.5. Use NCWNewLinkProfile instead.*/
CSEXTERN CMError 
CWNewLinkProfile(
  CMProfileRef *             prof,
  const CMProfileLocation *  targetLocation,
  CMConcatProfileSet *       profileSet)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
#endif // !__LP64__ && !TARGET_OS_WIN32


CSEXTERN CMError 
NCWNewLinkProfile(
  CMProfileRef *             prof,
  const CMProfileLocation *  targetLocation,
  NCMConcatProfileSet *      profileSet,
  CMConcatCallBackUPP        proc,
  void *                     refCon)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*!
    @function    CMMakeProfile
    @abstract    Make a display or abstract profile.
    @discussion  Adds appropriate tags to a profile to make display or abstract
                 profile based on an specification dictionary.
	One key in the specification dictionary must be "profileType" 
	which must have a CFString value of "abstractLab", "displayRGB" 
	or "displayID".  It can also contain the keys/values:
	  <PRE>
	  "description"    CFString (optional)
	  "copyright"      CFString (optional)
	  </PRE>
	For profileType of "abstractLab", the dictionary
	should also contain the keys/values:
	  <PRE>
	  "gridPoints"     CFNumber(SInt32) (should be odd)
	  "proc"           CFNumber(SInt64) (coerced from a LabToLabProcPtr)
	  "refcon"         CFNumber(SInt64) (coerced from a void*) (optional) 
	  </PRE>
	For profileType of "displayRGB", the dictionary
	should also contain the keys/values:
	  <PRE>
	  "targetGamma"    CFNumber(Float)  (e.g. 1.8)  (optional)
	  "targetWhite"    CFNumber(SInt32) (e.g. 6500) (optional)
	  "gammaR"         CFNumber(Float)  (e.g. 2.5)
	  "gammaG"         CFNumber(Float)  (e.g. 2.5)
	  "gammaB"         CFNumber(Float)  (e.g. 2.5)
	  "tableChans"     CFNumber(SInt32) (1 or 3) (optional)
	  "tableEntries"   CFNumber(SInt32) (e.g 16 or 255) (optional)
	  "tableEntrySize" CFNumber(SInt32) (1 or 2) (optional)
	  "tableData"      CFData (lut in RRRGGGBBB order) (optional)
	  
	  either
	  "phosphorRx"     CFNumber(Float)
	  "phosphorRy"     CFNumber(Float)
	  "phosphorGx"     CFNumber(Float)
	  "phosphorGy"     CFNumber(Float)
	  "phosphorBx"     CFNumber(Float)
	  "phosphorBy"     CFNumber(Float)
	  or
	  "phosphorSet"    CFString ("WideRGB", "700/525/450nm", "P22-EBU", "HDTV", 
	                             "CCIR709", "sRGB", "AdobeRGB98" or "Trinitron")
	  either
	  "whitePointx"    CFNumber(Float)
	  "whitePointy"    CFNumber(Float)
	  or
	  "whiteTemp"      CFNumber(SInt32)  (e.g. 5000, 6500, 9300)
	  </PRE>
	For profileType of "displayID", the dictionary
	should also contain the keys/values:
	  <PRE>
	  "targetGamma"    CFNumber(Float)  (e.g. 1.8)  (optional)
	  "targetWhite"    CFNumber(SInt32) (e.g. 6500) (optional)
	  "displayID       CFNumber(SInt32)
	  Optionally, the keys/values for "displayRGB" can be
	  provided to override the values from the display.
	  </PRE>
    
    @param       prof       (in) the profile to modify
    @param       spec       (in) specification dictionary
*/
CSEXTERN CMError 
CMMakeProfile(
  CMProfileRef      prof,
  CFDictionaryRef   spec)                                     AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/* Accessing Profiles */

CSEXTERN CMError 
CMOpenProfile(
  CMProfileRef *             prof,
  const CMProfileLocation *  theProfile)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMCloseProfile(CMProfileRef prof)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMUpdateProfile(CMProfileRef prof)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMCopyProfile(
  CMProfileRef *             targetProf,
  const CMProfileLocation *  targetLocation,
  CMProfileRef               srcProf)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMValidateProfile(
  CMProfileRef   prof,
  Boolean *      valid,
  Boolean *      preferredCMMnotfound)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#if !__LP64__ && !TARGET_OS_WIN32
/* This function is deprecated in Mac OS X 10.5. Use NCMGetProfileLocation instead.*/
CSEXTERN CMError 
CMGetProfileLocation(
  CMProfileRef         prof,
  CMProfileLocation *  location)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
#endif // !__LP64__ && !TARGET_OS_WIN32


CSEXTERN CMError 
NCMGetProfileLocation(
  CMProfileRef         prof,
  CMProfileLocation *  theProfile,
  UInt32 *             locationSize)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*!
    @function    CMProfileCopyICCData
    @abstract    Return a copy of the icc data specified by `prof'.
    @param       allocator  (in) The object to be used to allocate memory for the data
    @param       prof       (in) The profile to query
 */
CSEXTERN CFDataRef 
CMProfileCopyICCData(
  CFAllocatorRef   allocator,
  CMProfileRef     prof)                                      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


#if !__LP64__ && !TARGET_OS_WIN32
/* This function is deprecated in Mac OS X 10.5. Use CMCopyProfile instead.*/
CSEXTERN CMError 
CMFlattenProfile(
  CMProfileRef   prof,
  UInt32         flags,
  CMFlattenUPP   proc,
  void *         refCon,
  Boolean *      preferredCMMnotfound)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
#endif // !__LP64__ && !TARGET_OS_WIN32


#if !__LP64__ && !TARGET_OS_WIN32
/* This function is deprecated in Mac OS X 10.5.*/
CSEXTERN CMError 
NCMUnflattenProfile(
  CMProfileLocation *  targetLocation,
  CMFlattenUPP         proc,
  void *               refCon,
  Boolean *            preferredCMMnotfound)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
#endif // !__LP64__ && !TARGET_OS_WIN32


CSEXTERN CMError 
CMGetProfileHeader(
  CMProfileRef            prof,
  CMAppleProfileHeader *  header)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMSetProfileHeader(
  CMProfileRef                  prof,
  const CMAppleProfileHeader *  header)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMCloneProfileRef(CMProfileRef prof)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMGetProfileRefCount(
  CMProfileRef   prof,
  long *         count)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMProfileModified(
  CMProfileRef   prof,
  Boolean *      modified)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMGetProfileMD5(
  CMProfileRef   prof,
  CMProfileMD5   digest)                                      AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/* Accessing Profile Elements */

CSEXTERN CMError 
CMCountProfileElements(
  CMProfileRef   prof,
  UInt32 *       elementCount)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMProfileElementExists(
  CMProfileRef   prof,
  OSType         tag,
  Boolean *      found)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMGetProfileElement(
  CMProfileRef   prof,
  OSType         tag,
  UInt32 *       elementSize,
  void *         elementData)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMSetProfileElement(
  CMProfileRef   prof,
  OSType         tag,
  UInt32         elementSize,
  const void *   elementData)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMSetProfileElementSize(
  CMProfileRef   prof,
  OSType         tag,
  UInt32         elementSize)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMSetProfileElementReference(
  CMProfileRef   prof,
  OSType         elementTag,
  OSType         referenceTag)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMGetPartialProfileElement(
  CMProfileRef   prof,
  OSType         tag,
  UInt32         offset,
  UInt32 *       byteCount,
  void *         elementData)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMSetPartialProfileElement(
  CMProfileRef   prof,
  OSType         tag,
  UInt32         offset,
  UInt32         byteCount,
  const void *   elementData)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMGetIndProfileElementInfo(
  CMProfileRef   prof,
  UInt32         index,
  OSType *       tag,
  UInt32 *       elementSize,
  Boolean *      refs)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMGetIndProfileElement(
  CMProfileRef   prof,
  UInt32         index,
  UInt32 *       elementSize,
  void *         elementData)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMRemoveProfileElement(
  CMProfileRef   prof,
  OSType         tag)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Accessing Profile Descriptions */

#if !__LP64__ && !TARGET_OS_WIN32
/* This function is deprecated in Mac OS X 10.5. Use CMCopyProfileDescriptionString instead.*/
CSEXTERN CMError 
CMGetScriptProfileDescription(
  CMProfileRef   prof,
  Str255         name,
  ScriptCode *   code)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
#endif // !__LP64__ && !TARGET_OS_WIN32


CSEXTERN CMError 
CMGetProfileDescriptions(
  CMProfileRef    prof,
  char *          aName,
  UInt32 *        aCount,
  Str255          mName,
  ScriptCode *    mCode,
  UniChar *       uName,
  UniCharCount *  uCount)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMSetProfileDescriptions(
  CMProfileRef       prof,
  const char *       aName,
  UInt32             aCount,
  ConstStr255Param   mName,
  ScriptCode         mCode,
  const UniChar *    uName,
  UniCharCount       uCount)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMCopyProfileLocalizedStringDictionary(
  CMProfileRef       prof,
  OSType             tag,
  CFDictionaryRef *  theDict)                                 AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


CSEXTERN CMError 
CMSetProfileLocalizedStringDictionary(
  CMProfileRef      prof,
  OSType            tag,
  CFDictionaryRef   theDict)                                  AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


CSEXTERN CMError 
CMCopyProfileLocalizedString(
  CMProfileRef   prof,
  OSType         tag,
  CFStringRef    reqLocale,
  CFStringRef *  locale,
  CFStringRef *  str)                                         AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*!
    @function    CMCopyProfileDescriptionString
    @abstract    Returns the name of a profile as a CFString.
    @discussion  If the profile is multi-localized, the best localized name for the current process is returned.
    @param       prof       (in) the profile to query
    @param       str        (out) returns the name
*/
CSEXTERN CMError 
CMCopyProfileDescriptionString(
  CMProfileRef   prof,
  CFStringRef *  str)                                         AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/* Accessing Name-Class Profiles */

CSEXTERN CMError 
CMGetNamedColorInfo(
  CMProfileRef   prof,
  UInt32 *       deviceChannels,
  OSType *       deviceColorSpace,
  OSType *       PCSColorSpace,
  UInt32 *       count,
  StringPtr      prefix,
  StringPtr      suffix)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMGetNamedColorValue(
  CMProfileRef   prof,
  StringPtr      name,
  CMColor *      deviceColor,
  CMColor *      PCSColor)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMGetIndNamedColorValue(
  CMProfileRef   prof,
  UInt32         index,
  CMColor *      deviceColor,
  CMColor *      PCSColor)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMGetNamedColorIndex(
  CMProfileRef   prof,
  StringPtr      name,
  UInt32 *       index)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMGetNamedColorName(
  CMProfileRef   prof,
  UInt32         index,
  StringPtr      name)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Working with ColorWorlds */

CSEXTERN CMError 
NCWNewColorWorld(
  CMWorldRef *   cw,
  CMProfileRef   src,
  CMProfileRef   dst)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#if !__LP64__ && !TARGET_OS_WIN32
CSEXTERN CMError 
CWConcatColorWorld(
  CMWorldRef *          cw,
  CMConcatProfileSet *  profileSet)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
#endif // !__LP64__ && !TARGET_OS_WIN32


CSEXTERN CMError 
NCWConcatColorWorld(
  CMWorldRef *           cw,
  NCMConcatProfileSet *  profileSet,
  CMConcatCallBackUPP    proc,
  void *                 refCon)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#if !__LP64__ && !TARGET_OS_WIN32
/* This function is deprecated in Mac OS X 10.5.*/
CSEXTERN CMError 
CMGetCWInfo(
  CMWorldRef        cw,
  CMCWInfoRecord *  info)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
#endif // !__LP64__ && !TARGET_OS_WIN32


CSEXTERN void 
CWDisposeColorWorld(CMWorldRef cw)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CWMatchColors(
  CMWorldRef   cw,
  CMColor *    myColors,
  size_t       count)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CWCheckColors(
  CMWorldRef   cw,
  CMColor *    myColors,
  size_t       count,
  UInt8 *      result)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CWMatchBitmap(
  CMWorldRef            cw,
  CMBitmap *            bitmap,
  CMBitmapCallBackUPP   progressProc,
  void *                refCon,
  CMBitmap *            matchedBitmap)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CWCheckBitmap(
  CMWorldRef            cw,
  const CMBitmap *      bitmap,
  CMBitmapCallBackUPP   progressProc,
  void *                refCon,
  CMBitmap *            resultBitmap)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

CSEXTERN UInt32
CWGetCMMSignature(
  CMWorldRef    cw)                                           AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* OpenGL support */
enum {
  cmTextureRGBtoRGBX8           = 0,    /* RGB to  8-bit RGBx texture*/
  cmTextureRGBtoRGBX16          = 1,    /* RGB to 16-bit RGBx texture*/
  cmTextureRGBtoRGBXFloat32     = 2     /* RGB to 32-bit float RGBx texture */
};

/*!
    @function    CWFillLookupTexture
    @abstract    Fills a 3d lookup texture from a colorworld.
    @discussion  The resulting table is suitable for use in OpenGL to 
                 accelerate color management in hardware.
    @param       cw             (in) the colorworld to use
    @param       gridPoints     (in) number of grid points per channel in the texture
    @param       format         (in) format of pixels in texture (e.g. cmTextureRGBtoRGBX8)
    @param       dataSize       (in) size in bytes of texture data to fill
    @param       data           (in/out) pointer to texture data to fill
*/
CSEXTERN CMError 
CWFillLookupTexture(
  CMWorldRef   cw,
  UInt32       gridPoints,
  UInt32       format,
  UInt32       dataSize,
  void *       data)                                          AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/* Accessing Special Profiles */

CSEXTERN CMError 
CMGetSystemProfile(CMProfileRef * prof)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#if !__LP64__ && !TARGET_OS_WIN32
/* This function is deprecated in Mac OS X 10.5. Use CMSetProfileByAVID instead.*/
CSEXTERN CMError 
CMSetSystemProfile(const FSSpec * profileFileSpec)            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
#endif // !__LP64__ && !TARGET_OS_WIN32


#if !__LP64__ && !TARGET_OS_WIN32
/* This function is deprecated in Mac OS X 10.5. Use CMSetProfileByAVID instead.*/
CSEXTERN CMError 
NCMSetSystemProfile(const CMProfileLocation * profLoc)        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
#endif // !__LP64__ && !TARGET_OS_WIN32


CSEXTERN CMError 
CMGetDefaultProfileBySpace(
  OSType          dataColorSpace,
  CMProfileRef *  prof)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#if !__LP64__ && !TARGET_OS_WIN32
/* This function is deprecated in Mac OS X 10.5.*/
CSEXTERN CMError 
CMSetDefaultProfileBySpace(
  OSType         dataColorSpace,
  CMProfileRef   prof)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
#endif // !__LP64__ && !TARGET_OS_WIN32


CSEXTERN CMError 
CMGetDefaultProfileByUse(
  OSType          use,
  CMProfileRef *  prof)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#if !__LP64__ && !TARGET_OS_WIN32
/* This function is deprecated in Mac OS X 10.5.*/
CSEXTERN CMError 
CMSetDefaultProfileByUse(
  OSType         use,
  CMProfileRef   prof)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
#endif // !__LP64__ && !TARGET_OS_WIN32


CSEXTERN CMError 
CMGetProfileByAVID(
  CMDisplayIDType   theID,
  CMProfileRef *    prof)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMSetProfileByAVID(
  CMDisplayIDType   theID,
  CMProfileRef      prof)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMGetGammaByAVID(
  CMDisplayIDType     theID,
  CMVideoCardGamma *  gamma,
  UInt32 *            size)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMSetGammaByAVID(
  CMDisplayIDType     theID,
  CMVideoCardGamma *  gamma)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Searching for Profiles */

CSEXTERN CMError 
CMIterateColorSyncFolder(
  CMProfileIterateUPP   proc,
  UInt32 *              seed,
  UInt32 *              count,
  void *                refCon)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#if !__LP64__ && !TARGET_OS_WIN32

/* This function is deprecated in Mac OS X 10.5. Use CMIterateColorSyncFolder instead.*/
CSEXTERN CMError 
CMGetColorSyncFolderSpec(
  short     vRefNum,
  Boolean   createFolder,
  short *   foundVRefNum,
  long *    foundDirID)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/* This function is deprecated in Mac OS X 10.5. Use CMIterateColorSyncFolder instead.*/
CSEXTERN CMError 
CMNewProfileSearch(
  CMSearchRecord *      searchSpec,
  void *                refCon,
  UInt32 *              count,
  CMProfileSearchRef *  searchResult)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/* This function is deprecated in Mac OS X 10.5. Use CMIterateColorSyncFolder instead.*/
CSEXTERN CMError 
CMUpdateProfileSearch(
  CMProfileSearchRef   search,
  void *               refCon,
  UInt32 *             count)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/* This function is deprecated in Mac OS X 10.5. Use CMIterateColorSyncFolder instead.*/
CSEXTERN void 
CMDisposeProfileSearch(
  CMProfileSearchRef search)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/* This function is deprecated in Mac OS X 10.5. Use CMIterateColorSyncFolder instead.*/
CSEXTERN CMError 
CMSearchGetIndProfile(
  CMProfileSearchRef   search,
  UInt32               index,
  CMProfileRef *       prof)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/* This function is deprecated in Mac OS X 10.5. Use CMIterateColorSyncFolder instead.*/
CSEXTERN CMError 
CMSearchGetIndProfileFileSpec(
  CMProfileSearchRef   search,
  UInt32               index,
  FSSpec *             spec)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/* This function is deprecated in Mac OS X 10.5. Use CMIterateColorSyncFolder instead.*/
CSEXTERN CMError 
CMCreateProfileIdentifier(
  CMProfileRef             prof,
  CMProfileIdentifierPtr   ident,
  UInt32 *                 size)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/* This function is deprecated in Mac OS X 10.5. Use CMIterateColorSyncFolder instead.*/
CSEXTERN CMError 
CMProfileIdentifierFolderSearch(
  CMProfileIdentifierPtr   ident,
  UInt32 *                 matchedCount,
  CMProfileSearchRef *     searchResult)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/* This function is deprecated in Mac OS X 10.5. Use CMIterateColorSyncFolder instead.*/
CSEXTERN CMError 
CMProfileIdentifierListSearch(
  CMProfileIdentifierPtr   ident,
  CMProfileRef *           profileList,
  UInt32                   listSize,
  UInt32 *                 matchedCount,
  CMProfileRef *           matchedList)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

#endif // !__LP64__ && !TARGET_OS_WIN32


/* Utilities */

#if !__LP64__ && !TARGET_OS_WIN32

CSEXTERN CMError 
CMGetPreferredCMM(
  OSType *   cmmType,
  Boolean *  prefCMMnotfound)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


CSEXTERN CMError 
CMSetPreferredCMM(
  OSType     cmmType)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

#endif /* !__LP64__ && !TARGET_OS_WIN32 */

CSEXTERN CMError 
CMIterateCMMInfo(
  CMMIterateUPP   proc,
  UInt32 *        count,
  void *          refCon)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMGetColorSyncVersion(UInt32 * version)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMLaunchControlPanel(UInt32 flags)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Converting Colors */

#if !__LP64__ && !TARGET_OS_WIN32

/* This function is deprecated in Mac OS X 10.5. Use CMConvertXYZFloatBitmap instead.*/
CSEXTERN CMError 
CMConvertXYZToLab(
  const CMColor *     src,
  const CMXYZColor *  white,
  CMColor *           dst,
  size_t              count)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/* This function is deprecated in Mac OS X 10.5. Use CMConvertXYZFloatBitmap instead.*/
CSEXTERN CMError 
CMConvertLabToXYZ(
  const CMColor *     src,
  const CMXYZColor *  white,
  CMColor *           dst,
  size_t              count)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/* This function is deprecated in Mac OS X 10.5. Use CMConvertXYZFloatBitmap instead.*/
CSEXTERN CMError 
CMConvertXYZToLuv(
  const CMColor *     src,
  const CMXYZColor *  white,
  CMColor *           dst,
  size_t              count)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/* This function is deprecated in Mac OS X 10.5. Use CMConvertXYZFloatBitmap instead.*/
CSEXTERN CMError 
CMConvertLuvToXYZ(
  const CMColor *     src,
  const CMXYZColor *  white,
  CMColor *           dst,
  size_t              count)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/* This function is deprecated in Mac OS X 10.5. Use CMConvertXYZFloatBitmap instead.*/
CSEXTERN CMError 
CMConvertXYZToYxy(
  const CMColor *  src,
  CMColor *        dst,
  size_t           count)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/* This function is deprecated in Mac OS X 10.5. Use CMConvertXYZFloatBitmap instead.*/
CSEXTERN CMError 
CMConvertYxyToXYZ(
  const CMColor *  src,
  CMColor *        dst,
  size_t           count)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/* This function is deprecated in Mac OS X 10.5. Use CMConvertRGBFloatBitmap instead.*/
CSEXTERN CMError 
CMConvertRGBToHLS(
  const CMColor *  src,
  CMColor *        dst,
  size_t           count)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/* This function is deprecated in Mac OS X 10.5. Use CMConvertRGBFloatBitmap instead.*/
CSEXTERN CMError 
CMConvertHLSToRGB(
  const CMColor *  src,
  CMColor *        dst,
  size_t           count)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/* This function is deprecated in Mac OS X 10.5. Use CMConvertRGBFloatBitmap instead.*/
CSEXTERN CMError 
CMConvertRGBToHSV(
  const CMColor *  src,
  CMColor *        dst,
  size_t           count)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/* This function is deprecated in Mac OS X 10.5. Use CMConvertRGBFloatBitmap instead.*/
CSEXTERN CMError 
CMConvertHSVToRGB(
  const CMColor *  src,
  CMColor *        dst,
  size_t           count)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/* This function is deprecated in Mac OS X 10.5. Use CMConvertRGBFloatBitmap instead.*/
CSEXTERN CMError 
CMConvertRGBToGray(
  const CMColor *  src,
  CMColor *        dst,
  size_t           count)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/* This function is deprecated in Mac OS X 10.5.*/
CSEXTERN CMError 
CMConvertXYZToFixedXYZ(
  const CMXYZColor *  src,
  CMFixedXYZColor *   dst,
  size_t              count)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/* This function is deprecated in Mac OS X 10.5.*/
CSEXTERN CMError 
CMConvertFixedXYZToXYZ(
  const CMFixedXYZColor *  src,
  CMXYZColor *             dst,
  size_t                   count)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/* This function is deprecated in Mac OS X 10.5. Use CMConvertXYZFloatBitmap instead.*/
CSEXTERN CMError 
CMConvertXYZToXYZ(
  const CMColor *         src,
  const CMXYZColor *      srcIlluminant,
  CMColor *               dst,
  const CMXYZColor *      dstIlluminant,
  CMChromaticAdaptation   method,
  size_t                  count)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

#endif // !__LP64__ && !TARGET_OS_WIN32


/* Working with PostScript */

CSEXTERN CMError 
CMGetPS2ColorSpace(
  CMProfileRef   srcProf,
  UInt32         flags,
  CMFlattenUPP   proc,
  void *         refCon,
  Boolean *      preferredCMMnotfound)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMGetPS2ColorRenderingIntent(
  CMProfileRef   srcProf,
  UInt32         flags,
  CMFlattenUPP   proc,
  void *         refCon,
  Boolean *      preferredCMMnotfound)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMGetPS2ColorRendering(
  CMProfileRef   srcProf,
  CMProfileRef   dstProf,
  UInt32         flags,
  CMFlattenUPP   proc,
  void *         refCon,
  Boolean *      preferredCMMnotfound)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


CSEXTERN CMError 
CMGetPS2ColorRenderingVMSize(
  CMProfileRef   srcProf,
  CMProfileRef   dstProf,
  UInt32 *       vmSize,
  Boolean *      preferredCMMnotfound)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* Notifications */

/*
 *  Clients can register for notifications of ColorSync preference changes by
 *  using the kCMPrefsChangedNotification key. This notification will be sent
 *  if the user changes ColorSync preferences such as:
 *      the default profile by colors space, (CMSetDefaultProfileBySpace)
 *      the default profile by device useage, (CMSetDefaultProfileByUse)
 *      or the preferred CMM.
 *  See <CMDeviceIntegration.h> for more notifications that can be sent.
 */
#define    kCMPrefsChangedNotification     CFSTR("AppleColorSyncPreferencesChangedNotification")



#if !__LP64__
#if defined(_MSC_VER)
#pragma pack(pop, CMApplication_h)
#else
#pragma options align=reset
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif /* __CMAPPLICATION__ */

