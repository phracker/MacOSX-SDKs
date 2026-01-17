/*
     File:       ColorSync/CMApplication.h
 
     Contains:   Color Matching Interfaces
 
     Version:    ColorSync-174.3.3~45
 
     Copyright:  © 1992-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
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


#define _DECLARE_CS_QD_API_ 0

#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

enum {
  kDefaultCMMSignature          = 'appl'
};

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


/* Flags for PostScript-related functions */
enum {
  cmPS7bit                      = 1,
  cmPS8bit                      = 2
};

/* Flags for profile embedding functions */
enum {
  cmEmbedWholeProfile           = 0x00000000,
  cmEmbedProfileIdentifier      = 0x00000001
};

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
  CMHeader            cm1;
  CM2Header           cm2;
  CM4Header           cm4;
};
typedef union CMAppleProfileHeader      CMAppleProfileHeader;
/* CWConcatColorWorld() definitions */
struct CMConcatProfileSet {
  UInt16              keyIndex;               /* Zero-based */
  UInt16              count;                  /* Min 1 */
  CMProfileRef        profileSet[1];          /* Variable. Ordered from Source -> Dest */
};
typedef struct CMConcatProfileSet       CMConcatProfileSet;
/* NCWConcatColorWorld() definitions */
struct NCMConcatProfileSpec {
  UInt32              renderingIntent;        /* renderingIntent override */
  UInt32              transformTag;           /* transform enumerations defined below */
  CMProfileRef        profile;                /* profile */
};
typedef struct NCMConcatProfileSpec     NCMConcatProfileSpec;
struct NCMConcatProfileSet {
  OSType              cmm;                    /* e.g. 'KCMS', 'appl', ...  uniquely ids the cmm, or 0000 */
  UInt32              flags;                  /* specify quality, lookup only, no gamut checking ... */
  UInt32              flagsMask;              /* which bits of 'flags' to use to override profile */
  UInt32              profileCount;           /* how many ProfileSpecs in the following set */
  NCMConcatProfileSpec  profileSpecs[1];      /* Variable. Ordered from Source -> Dest */
};
typedef struct NCMConcatProfileSet      NCMConcatProfileSet;
enum {
  kNoTransform                  = 0,    /* Not used */
  kUseAtoB                      = 1,    /* Use 'A2B*' tag from this profile or equivalent */
  kUseBtoA                      = 2,    /* Use 'B2A*' tag from this profile or equivalent */
  kUseBtoB                      = 3,    /* Use 'pre*' tag from this profile or equivalent */
                                        /* For typical device profiles the following synonyms may be useful */
  kDeviceToPCS                  = kUseAtoB, /* Device Dependent to Device Independent */
  kPCSToDevice                  = kUseBtoA, /* Device Independent to Device Dependent */
  kPCSToPCS                     = kUseBtoB, /* Independent, through device's gamut */
  kUseProfileIntent             = (long)0xFFFFFFFF /* For renderingIntent in NCMConcatProfileSpec    */
};


/* ColorSync color data types */
struct CMRGBColor {
  UInt16              red;                    /* 0..65535 */
  UInt16              green;
  UInt16              blue;
};
typedef struct CMRGBColor               CMRGBColor;
struct CMCMYKColor {
  UInt16              cyan;                   /* 0..65535 */
  UInt16              magenta;
  UInt16              yellow;
  UInt16              black;
};
typedef struct CMCMYKColor              CMCMYKColor;
struct CMCMYColor {
  UInt16              cyan;                   /* 0..65535 */
  UInt16              magenta;
  UInt16              yellow;
};
typedef struct CMCMYColor               CMCMYColor;
struct CMHLSColor {
  UInt16              hue;                    /* 0..65535. Fraction of circle. Red at 0 */
  UInt16              lightness;              /* 0..65535 */
  UInt16              saturation;             /* 0..65535 */
};
typedef struct CMHLSColor               CMHLSColor;
struct CMHSVColor {
  UInt16              hue;                    /* 0..65535. Fraction of circle. Red at 0 */
  UInt16              saturation;             /* 0..65535 */
  UInt16              value;                  /* 0..65535 */
};
typedef struct CMHSVColor               CMHSVColor;
struct CMLabColor {
  UInt16              L;                      /* 0..65535 maps to 0..100 */
  UInt16              a;                      /* 0..65535 maps to -128..127.996 */
  UInt16              b;                      /* 0..65535 maps to -128..127.996 */
};
typedef struct CMLabColor               CMLabColor;
struct CMLuvColor {
  UInt16              L;                      /* 0..65535 maps to 0..100 */
  UInt16              u;                      /* 0..65535 maps to -128..127.996 */
  UInt16              v;                      /* 0..65535 maps to -128..127.996 */
};
typedef struct CMLuvColor               CMLuvColor;
struct CMYxyColor {
  UInt16              capY;                   /* 0..65535 maps to 0..1 */
  UInt16              x;                      /* 0..65535 maps to 0..1 */
  UInt16              y;                      /* 0..65535 maps to 0..1 */
};
typedef struct CMYxyColor               CMYxyColor;
struct CMGrayColor {
  UInt16              gray;                   /* 0..65535 */
};
typedef struct CMGrayColor              CMGrayColor;
struct CMMultichannel5Color {
  UInt8               components[5];          /* 0..255 */
};
typedef struct CMMultichannel5Color     CMMultichannel5Color;
struct CMMultichannel6Color {
  UInt8               components[6];          /* 0..255 */
};
typedef struct CMMultichannel6Color     CMMultichannel6Color;
struct CMMultichannel7Color {
  UInt8               components[7];          /* 0..255 */
};
typedef struct CMMultichannel7Color     CMMultichannel7Color;
struct CMMultichannel8Color {
  UInt8               components[8];          /* 0..255 */
};
typedef struct CMMultichannel8Color     CMMultichannel8Color;
struct CMNamedColor {
  UInt32              namedColorIndex;        /* 0..a lot */
};
typedef struct CMNamedColor             CMNamedColor;
union CMColor {
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
};
typedef union CMColor                   CMColor;
/* GetIndexedProfile() search definition */
struct CMProfileSearchRecord {
  CMHeader            header;
  UInt32              fieldMask;
  UInt32              reserved[2];
};
typedef struct CMProfileSearchRecord    CMProfileSearchRecord;
typedef CMProfileSearchRecord *         CMProfileSearchRecordPtr;
typedef CMProfileSearchRecordPtr *      CMProfileSearchRecordHandle;
/* CMNewProfileSearch() search definition */
struct CMSearchRecord {
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
};
typedef struct CMSearchRecord           CMSearchRecord;
/* CMMIterateUPP() structure */
struct CMMInfo {
  UInt32              dataSize;               /* Size of this structure - compatibility*/
  OSType              CMMType;                /* Signature, e.g. 'appl', 'HDM ' or 'KCMS'*/
  OSType              CMMMfr;                 /* Vendor, e.g. 'appl'*/
  UInt32              CMMVersion;             /* CMM version number*/
  unsigned char       ASCIIName[32];          /* pascal string - name*/
  unsigned char       ASCIIDesc[256];         /* pascal string - description or copyright*/
  UniCharCount        UniCodeNameCount;       /* count of UniChars in following array*/
  UniChar             UniCodeName[32];        /* the name in UniCode chars*/
  UniCharCount        UniCodeDescCount;       /* count of UniChars in following array*/
  UniChar             UniCodeDesc[256];       /* the description in UniCode chars*/
};
typedef struct CMMInfo                  CMMInfo;
/* GetCWInfo() structures */
struct CMMInfoRecord {
  OSType              CMMType;
  long                CMMVersion;
};
typedef struct CMMInfoRecord            CMMInfoRecord;
struct CMCWInfoRecord {
  UInt32              cmmCount;
  CMMInfoRecord       cmmInfo[2];
};
typedef struct CMCWInfoRecord           CMCWInfoRecord;
/* profile identifier structures */
struct CMProfileIdentifier {
  CM2Header           profileHeader;
  CMDateTime          calibrationDate;
  UInt32              ASCIIProfileDescriptionLen;
  char                ASCIIProfileDescription[1]; /* variable length */
};
typedef struct CMProfileIdentifier      CMProfileIdentifier;
typedef CMProfileIdentifier *           CMProfileIdentifierPtr;
/* colorspace masks */
enum {
  cmColorSpaceSpaceMask         = 0x0000003F,
  cmColorSpacePremulAlphaMask   = 0x00000040,
  cmColorSpaceAlphaMask         = 0x00000080,
  cmColorSpaceSpaceAndAlphaMask = 0x000000FF,
  cmColorSpacePackingMask       = 0x0000FF00,
  cmColorSpaceEncodingMask      = 0x000F0000,
  cmColorSpaceReservedMask      = (long)0xFFF00000
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
struct CMBitmap {
  char *              image;
  long                width;
  long                height;
  long                rowBytes;
  long                pixelSize;
  CMBitmapColorSpace  space;
  long                user1;
  long                user2;
};
typedef struct CMBitmap                 CMBitmap;
/* Profile Locations */
enum {
  CS_MAX_PATH                   = 256
};

enum {
  cmNoProfileBase               = 0,
  cmFileBasedProfile            = 1,
  cmHandleBasedProfile          = 2,
  cmPtrBasedProfile             = 3,
  cmProcedureBasedProfile       = 4,
  cmPathBasedProfile            = 5,
  cmBufferBasedProfile          = 6
};

struct CMFileLocation {
  FSSpec              spec;
};
typedef struct CMFileLocation           CMFileLocation;
struct CMHandleLocation {
  Handle              h;
};
typedef struct CMHandleLocation         CMHandleLocation;
struct CMPtrLocation {
  Ptr                 p;
};
typedef struct CMPtrLocation            CMPtrLocation;
struct CMProcedureLocation {
  CMProfileAccessUPP  proc;
  void *              refCon;
};
typedef struct CMProcedureLocation      CMProcedureLocation;
struct CMPathLocation {
  char                path[256];
};
typedef struct CMPathLocation           CMPathLocation;
struct CMBufferLocation {
  void *              buffer;
  UInt32              size;
};
typedef struct CMBufferLocation         CMBufferLocation;
union CMProfLoc {
  CMFileLocation      fileLoc;
  CMHandleLocation    handleLoc;
  CMPtrLocation       ptrLoc;
  CMProcedureLocation  procLoc;
  CMPathLocation      pathLoc;
  CMBufferLocation    bufferLoc;
};
typedef union CMProfLoc                 CMProfLoc;
struct CMProfileLocation {
  short               locType;
  CMProfLoc           u;
};
typedef struct CMProfileLocation        CMProfileLocation;
enum {
  cmOriginalProfileLocationSize = 72,
  cmCurrentProfileLocationSize  = 2 + CS_MAX_PATH
};

/* Struct and enums used for Profile iteration */
enum {
  cmProfileIterateDataVersion1  = 0x00010000,
  cmProfileIterateDataVersion2  = 0x00020000, /* Added makeAndModel*/
  cmProfileIterateDataVersion3  = 0x00030000 /* Added MD5 digest*/
};

struct CMProfileIterateData {
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
};
typedef struct CMProfileIterateData     CMProfileIterateData;
/* Caller-supplied callback function for Profile & CMM iteration */
typedef CALLBACK_API( OSErr , CMProfileIterateProcPtr )(CMProfileIterateData *iterateData, void *refCon);
typedef CALLBACK_API( OSErr , CMMIterateProcPtr )(CMMInfo *iterateData, void *refCon);
typedef STACK_UPP_TYPE(CMProfileIterateProcPtr)                 CMProfileIterateUPP;
typedef STACK_UPP_TYPE(CMMIterateProcPtr)                       CMMIterateUPP;
/*
 *  NewCMProfileIterateUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern CMProfileIterateUPP
NewCMProfileIterateUPP(CMProfileIterateProcPtr userRoutine)   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewCMMIterateUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern CMMIterateUPP
NewCMMIterateUPP(CMMIterateProcPtr userRoutine)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeCMProfileIterateUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeCMProfileIterateUPP(CMProfileIterateUPP userUPP)       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeCMMIterateUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeCMMIterateUPP(CMMIterateUPP userUPP)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeCMProfileIterateUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeCMProfileIterateUPP(
  CMProfileIterateData *  iterateData,
  void *                  refCon,
  CMProfileIterateUPP     userUPP)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeCMMIterateUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeCMMIterateUPP(
  CMMInfo *      iterateData,
  void *         refCon,
  CMMIterateUPP  userUPP)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

typedef CALLBACK_API_C( void , CMLabToLabProcPtr )(float *L, float *a, float *b, void *refcon);
/* Creating Profiles */
/*
 *  CMNewProfile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMNewProfile(
  CMProfileRef *             prof,
  const CMProfileLocation *  theProfile)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CWNewLinkProfile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CWNewLinkProfile(
  CMProfileRef *             prof,
  const CMProfileLocation *  targetLocation,
  CMConcatProfileSet *       profileSet)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NCWNewLinkProfile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.6 and later
 */
extern CMError 
NCWNewLinkProfile(
  CMProfileRef *             prof,
  const CMProfileLocation *  targetLocation,
  NCMConcatProfileSet *      profileSet,
  CMConcatCallBackUPP        proc,
  void *                     refCon)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMMakeProfile()
 *  
 *  Summary:
 *    Make a display or abstract profile.
 *  
 *  Discussion:
 *    Adds appropriate tags to a profile to make display or abstract
 *    profile based on an specification dictionary. 
 *    
 *    One key in the specification dictionary must be "profileType" 
 *    which must have a CFString value of "abstractLab", "displayRGB" 
 *    or "displayID".  It can also contain the keys/values: 
 *      "description"  CFString (optional) 
 *      "copyright"    CFString (optional) 
 *    
 *    For profileType of "abstractLab", the dictionary 
 *    should also contain the keys/values: 
 *      "gridPoints"   CFNumber(SInt32) (should be odd) 
 *      "proc"         CFNumber(SInt64) 
 *                     (coerced from a LabToLabProcPtr) 
 *      "refcon"       CFNumber(SInt64) (optional) 
 *                     (coerced from a void*) 
 *    
 *    For profileType of "displayRGB", the dictionary 
 *    should also contain the keys/values: 
 *      "targetGamma"  CFNumber(Float)  (e.g. 1.8)  (optional) 
 *      "targetWhite"  CFNumber(SInt32) (e.g. 6500) (optional) 
 *      "gammaR"       CFNumber(Float)  (e.g. 2.5) 
 *      "gammaG"       CFNumber(Float)  (e.g. 2.5) 
 *      "gammaB"       CFNumber(Float)  (e.g. 2.5) 
 *      "tableChans"   CFNumber(SInt32) (1 or 3) (optional) 
 *      "tableEntries" CFNumber(SInt32) (e.g 16 or 255) (optional) 
 *      "tableEntrySize" CFNumber(SInt32) (1 or 2) (optional) 
 *      "tableData"    CFData (lut in RRRGGGBBB order) (optional) 
 *     either 
 *      "phosphorRx"   CFNumber(Float) 
 *      "phosphorRy"   CFNumber(Float) 
 *      "phosphorGx"   CFNumber(Float) 
 *      "phosphorGy"   CFNumber(Float) 
 *      "phosphorBx"   CFNumber(Float) 
 *      "phosphorBy"   CFNumber(Float) 
 *      or 
 *      "phosphorSet"  CFString ("WideRGB", "700/525/450nm", 
 *                      "P22-EBU", "HDTV", "CCIR709", "sRGB", 
 *                      "AdobeRGB98" or "Trinitron") 
 *     either 
 *      "whitePointx"  CFNumber(Float) 
 *      "whitePointy"  CFNumber(Float) 
 *      or 
 *      "whiteTemp"    CFNumber(SInt32)  (e.g. 5000, 6500, 9300) 
 *    
 *    For profileType of "displayID", the dictionary 
 *    should also contain the keys/values: 
 *      "targetGamma"  CFNumber(Float)  (e.g. 1.8)  (optional) 
 *      "targetWhite"  CFNumber(SInt32) (e.g. 6500) (optional) 
 *      "displayID     CFNumber(SInt32) 
 *    Optionally, the keys/values for "displayRGB" can be 
 *    provided to override the valuses from the display.
 *  
 *  Parameters:
 *    
 *    prof:
 *      (in) the profile to modify
 *    
 *    spec:
 *      (in) specification dictionary
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
CMMakeProfile(
  CMProfileRef      prof,
  CFDictionaryRef   spec)                                     AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/* Accessing Profiles */
/*
 *  CMOpenProfile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMOpenProfile(
  CMProfileRef *             prof,
  const CMProfileLocation *  theProfile)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMCloseProfile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMCloseProfile(CMProfileRef prof)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMUpdateProfile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMUpdateProfile(CMProfileRef prof)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMCopyProfile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMCopyProfile(
  CMProfileRef *             targetProf,
  const CMProfileLocation *  targetLocation,
  CMProfileRef               srcProf)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMValidateProfile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMValidateProfile(
  CMProfileRef   prof,
  Boolean *      valid,
  Boolean *      preferredCMMnotfound)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMGetProfileLocation()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMGetProfileLocation(
  CMProfileRef         prof,
  CMProfileLocation *  theProfile)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NCMGetProfileLocation()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.5 and later
 */
extern CMError 
NCMGetProfileLocation(
  CMProfileRef         prof,
  CMProfileLocation *  theProfile,
  UInt32 *             locationSize)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMProfileCopyICCData()
 *  
 *  Summary:
 *    Return a copy of the icc data specified by `prof'.
 *  
 *  Parameters:
 *    
 *    allocator:
 *      (in) The object to be used to allocate memory for the data
 *    
 *    prof:
 *      (in) The profile to query
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFDataRef 
CMProfileCopyICCData(
  CFAllocatorRef   allocator,
  CMProfileRef     prof)                                      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  CMFlattenProfile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMFlattenProfile(
  CMProfileRef   prof,
  UInt32         flags,
  CMFlattenUPP   proc,
  void *         refCon,
  Boolean *      preferredCMMnotfound)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NCMUnflattenProfile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.6 and later
 */
extern CMError 
NCMUnflattenProfile(
  CMProfileLocation *  targetLocation,
  CMFlattenUPP         proc,
  void *               refCon,
  Boolean *            preferredCMMnotfound)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMUnflattenProfile()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */


/*
 *  CMGetProfileHeader()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMGetProfileHeader(
  CMProfileRef            prof,
  CMAppleProfileHeader *  header)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMSetProfileHeader()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMSetProfileHeader(
  CMProfileRef                  prof,
  const CMAppleProfileHeader *  header)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMCloneProfileRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMCloneProfileRef(CMProfileRef prof)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMGetProfileRefCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMGetProfileRefCount(
  CMProfileRef   prof,
  long *         count)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMProfileModified()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMProfileModified(
  CMProfileRef   prof,
  Boolean *      modified)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMGetProfileMD5()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
CMGetProfileMD5(
  CMProfileRef   prof,
  CMProfileMD5   digest)                                      AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;



/* Accessing Profile Elements */
/*
 *  CMCountProfileElements()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMCountProfileElements(
  CMProfileRef   prof,
  UInt32 *       elementCount)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMProfileElementExists()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMProfileElementExists(
  CMProfileRef   prof,
  OSType         tag,
  Boolean *      found)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMGetProfileElement()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMGetProfileElement(
  CMProfileRef   prof,
  OSType         tag,
  UInt32 *       elementSize,
  void *         elementData)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMSetProfileElement()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMSetProfileElement(
  CMProfileRef   prof,
  OSType         tag,
  UInt32         elementSize,
  const void *   elementData)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMSetProfileElementSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMSetProfileElementSize(
  CMProfileRef   prof,
  OSType         tag,
  UInt32         elementSize)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMSetProfileElementReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMSetProfileElementReference(
  CMProfileRef   prof,
  OSType         elementTag,
  OSType         referenceTag)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMGetPartialProfileElement()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMGetPartialProfileElement(
  CMProfileRef   prof,
  OSType         tag,
  UInt32         offset,
  UInt32 *       byteCount,
  void *         elementData)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMSetPartialProfileElement()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMSetPartialProfileElement(
  CMProfileRef   prof,
  OSType         tag,
  UInt32         offset,
  UInt32         byteCount,
  const void *   elementData)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMGetIndProfileElementInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMGetIndProfileElementInfo(
  CMProfileRef   prof,
  UInt32         index,
  OSType *       tag,
  UInt32 *       elementSize,
  Boolean *      refs)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMGetIndProfileElement()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMGetIndProfileElement(
  CMProfileRef   prof,
  UInt32         index,
  UInt32 *       elementSize,
  void *         elementData)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMRemoveProfileElement()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMRemoveProfileElement(
  CMProfileRef   prof,
  OSType         tag)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* Accessing Profile Descriptions */
/*
 *  CMGetScriptProfileDescription()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMGetScriptProfileDescription(
  CMProfileRef   prof,
  Str255         name,
  ScriptCode *   code)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMGetProfileDescriptions()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.6 and later
 */
extern CMError 
CMGetProfileDescriptions(
  CMProfileRef    prof,
  char *          aName,
  UInt32 *        aCount,
  Str255          mName,
  ScriptCode *    mCode,
  UniChar *       uName,
  UniCharCount *  uCount)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMSetProfileDescriptions()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.6 and later
 */
extern CMError 
CMSetProfileDescriptions(
  CMProfileRef       prof,
  const char *       aName,
  UInt32             aCount,
  ConstStr255Param   mName,
  ScriptCode         mCode,
  const UniChar *    uName,
  UniCharCount       uCount)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMCopyProfileLocalizedStringDictionary()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in ColorSyncLib 3.1 and later
 */
extern CMError 
CMCopyProfileLocalizedStringDictionary(
  CMProfileRef       prof,
  OSType             tag,
  CFDictionaryRef *  theDict)                                 AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  CMSetProfileLocalizedStringDictionary()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in ColorSyncLib 3.1 and later
 */
extern CMError 
CMSetProfileLocalizedStringDictionary(
  CMProfileRef      prof,
  OSType            tag,
  CFDictionaryRef   theDict)                                  AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  CMCopyProfileLocalizedString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in ColorSyncLib 3.1 and later
 */
extern CMError 
CMCopyProfileLocalizedString(
  CMProfileRef   prof,
  OSType         tag,
  CFStringRef    reqLocale,
  CFStringRef *  locale,
  CFStringRef *  str)                                         AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  CMCopyProfileDescriptionString()
 *  
 *  Summary:
 *    Returns the name of a profile as a CFString.
 *  
 *  Discussion:
 *    If the profile is multi-localized, the best localized name for
 *    the current process is returned.
 *  
 *  Parameters:
 *    
 *    prof:
 *      (in) the profile to query
 *    
 *    str:
 *      (out) returns the name
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
CMCopyProfileDescriptionString(
  CMProfileRef   prof,
  CFStringRef *  str)                                         AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/* Accessing Name-Class Profiles */
/*
 *  CMGetNamedColorInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMGetNamedColorInfo(
  CMProfileRef   prof,
  UInt32 *       deviceChannels,
  OSType *       deviceColorSpace,
  OSType *       PCSColorSpace,
  UInt32 *       count,
  StringPtr      prefix,
  StringPtr      suffix)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMGetNamedColorValue()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMGetNamedColorValue(
  CMProfileRef   prof,
  StringPtr      name,
  CMColor *      deviceColor,
  CMColor *      PCSColor)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMGetIndNamedColorValue()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMGetIndNamedColorValue(
  CMProfileRef   prof,
  UInt32         index,
  CMColor *      deviceColor,
  CMColor *      PCSColor)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMGetNamedColorIndex()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMGetNamedColorIndex(
  CMProfileRef   prof,
  StringPtr      name,
  UInt32 *       index)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMGetNamedColorName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMGetNamedColorName(
  CMProfileRef   prof,
  UInt32         index,
  StringPtr      name)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* Working with ColorWorlds */
/*
 *  NCWNewColorWorld()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
NCWNewColorWorld(
  CMWorldRef *   cw,
  CMProfileRef   src,
  CMProfileRef   dst)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CWConcatColorWorld()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CWConcatColorWorld(
  CMWorldRef *          cw,
  CMConcatProfileSet *  profileSet)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NCWConcatColorWorld()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.6 and later
 */
extern CMError 
NCWConcatColorWorld(
  CMWorldRef *           cw,
  NCMConcatProfileSet *  profileSet,
  CMConcatCallBackUPP    proc,
  void *                 refCon)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMGetCWInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 1.0 and later
 */
extern CMError 
CMGetCWInfo(
  CMWorldRef        cw,
  CMCWInfoRecord *  info)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CWDisposeColorWorld()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 1.0 and later
 */
extern void 
CWDisposeColorWorld(CMWorldRef cw)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CWMatchColors()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 1.0 and later
 */
extern CMError 
CWMatchColors(
  CMWorldRef   cw,
  CMColor *    myColors,
  UInt32       count)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CWCheckColors()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 1.0 and later
 */
extern CMError 
CWCheckColors(
  CMWorldRef   cw,
  CMColor *    myColors,
  UInt32       count,
  UInt8 *      result)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CWMatchBitmap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CWMatchBitmap(
  CMWorldRef            cw,
  CMBitmap *            bitmap,
  CMBitmapCallBackUPP   progressProc,
  void *                refCon,
  CMBitmap *            matchedBitmap)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CWCheckBitmap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CWCheckBitmap(
  CMWorldRef            cw,
  const CMBitmap *      bitmap,
  CMBitmapCallBackUPP   progressProc,
  void *                refCon,
  CMBitmap *            resultBitmap)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* OpenGL support */
enum {
  cmTextureRGBtoRGBX8           = 0     /* RGB to 8-bit RGBx texture*/
};

/*
 *  CWFillLookupTexture()
 *  
 *  Summary:
 *    Fills a 3d lookup texture from a colorworld.
 *  
 *  Discussion:
 *    The resulting table is suitable for use in OpenGL to accelerate
 *    color management in hardware.
 *  
 *  Parameters:
 *    
 *    cw:
 *      (in) the colorworld to use
 *    
 *    gridPoints:
 *      (in) number of grid points per channel in the texture
 *    
 *    format:
 *      (in) format of pixels in texture (e.g. cmTextureRGBtoRGBX8)
 *    
 *    dataSize:
 *      (in) size in bytes of texture data to fill
 *    
 *    data:
 *      (in/out) pointer to texture data to fill
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
CWFillLookupTexture(
  CMWorldRef   cw,
  UInt32       gridPoints,
  UInt32       format,
  UInt32       dataSize,
  void *       data)                                          AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/* Working with Quickdraw */
#if _DECLARE_CS_QD_API_
/*
 *  CWMatchPixMap()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 1.0 and later
 */
extern CMError 
CWMatchPixMap(
  CMWorldRef            cw,
  PixMap *              myPixMap,
  CMBitmapCallBackUPP   progressProc,
  void *                refCon);


/*
 *  CWCheckPixMap()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 1.0 and later
 */
extern CMError 
CWCheckPixMap(
  CMWorldRef            cw,
  PixMap *              myPixMap,
  CMBitmapCallBackUPP   progressProc,
  void *                refCon,
  BitMap *              resultBitMap);


/*
 *  NCMBeginMatching()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
NCMBeginMatching(
  CMProfileRef   src,
  CMProfileRef   dst,
  CMMatchRef *   myRef);


/*
 *  CMEndMatching()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern void 
CMEndMatching(CMMatchRef myRef);


/*
 *  NCMDrawMatchedPicture()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern void 
NCMDrawMatchedPicture(
  PicHandle      myPicture,
  CMProfileRef   dst,
  Rect *         myRect);


/*
 *  CMEnableMatchingComment()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern void 
CMEnableMatchingComment(Boolean enableIt);


/*
 *  NCMUseProfileComment()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
NCMUseProfileComment(
  CMProfileRef   prof,
  UInt32         flags);


#endif  /* _DECLARE_CS_QD_API_ */

/* Accessing Special Profiles */
/*
 *  CMGetSystemProfile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMGetSystemProfile(CMProfileRef * prof)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMSetSystemProfile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMSetSystemProfile(const FSSpec * profileFileSpec)            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NCMSetSystemProfile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.6 and later
 */
extern CMError 
NCMSetSystemProfile(const CMProfileLocation * profLoc)        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMGetDefaultProfileBySpace()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.5 and later
 */
extern CMError 
CMGetDefaultProfileBySpace(
  OSType          dataColorSpace,
  CMProfileRef *  prof)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMSetDefaultProfileBySpace()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.5 and later
 */
extern CMError 
CMSetDefaultProfileBySpace(
  OSType         dataColorSpace,
  CMProfileRef   prof)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMGetDefaultProfileByUse()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 3.0 and later
 */
extern CMError 
CMGetDefaultProfileByUse(
  OSType          use,
  CMProfileRef *  prof)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMSetDefaultProfileByUse()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 3.0 and later
 */
extern CMError 
CMSetDefaultProfileByUse(
  OSType         use,
  CMProfileRef   prof)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMGetProfileByAVID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.5 and later
 */
extern CMError 
CMGetProfileByAVID(
  CMDisplayIDType   theID,
  CMProfileRef *    prof)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMSetProfileByAVID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.5 and later
 */
extern CMError 
CMSetProfileByAVID(
  CMDisplayIDType   theID,
  CMProfileRef      prof)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMGetGammaByAVID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 3.0 and later
 */
extern CMError 
CMGetGammaByAVID(
  CMDisplayIDType     theID,
  CMVideoCardGamma *  gamma,
  UInt32 *            size)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMSetGammaByAVID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 3.0 and later
 */
extern CMError 
CMSetGammaByAVID(
  CMDisplayIDType     theID,
  CMVideoCardGamma *  gamma)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* Searching for Profiles */
/*
 *  CMIterateColorSyncFolder()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.5 and later
 */
extern CMError 
CMIterateColorSyncFolder(
  CMProfileIterateUPP   proc,
  UInt32 *              seed,
  UInt32 *              count,
  void *                refCon)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMGetColorSyncFolderSpec()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMGetColorSyncFolderSpec(
  short     vRefNum,
  Boolean   createFolder,
  short *   foundVRefNum,
  long *    foundDirID)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMNewProfileSearch()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMNewProfileSearch(
  CMSearchRecord *      searchSpec,
  void *                refCon,
  UInt32 *              count,
  CMProfileSearchRef *  searchResult)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMUpdateProfileSearch()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMUpdateProfileSearch(
  CMProfileSearchRef   search,
  void *               refCon,
  UInt32 *             count)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMDisposeProfileSearch()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern void 
CMDisposeProfileSearch(CMProfileSearchRef search)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMSearchGetIndProfile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMSearchGetIndProfile(
  CMProfileSearchRef   search,
  UInt32               index,
  CMProfileRef *       prof)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMSearchGetIndProfileFileSpec()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMSearchGetIndProfileFileSpec(
  CMProfileSearchRef   search,
  UInt32               index,
  FSSpec *             profileFile)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMCreateProfileIdentifier()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMCreateProfileIdentifier(
  CMProfileRef             prof,
  CMProfileIdentifierPtr   ident,
  UInt32 *                 size)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMProfileIdentifierFolderSearch()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMProfileIdentifierFolderSearch(
  CMProfileIdentifierPtr   ident,
  UInt32 *                 matchedCount,
  CMProfileSearchRef *     searchResult)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMProfileIdentifierListSearch()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMProfileIdentifierListSearch(
  CMProfileIdentifierPtr   ident,
  CMProfileRef *           profileList,
  UInt32                   listSize,
  UInt32 *                 matchedCount,
  CMProfileRef *           matchedList)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* Utilities */
/*
 *  CMGetPreferredCMM()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.5 and later
 */
extern CMError 
CMGetPreferredCMM(
  OSType *   cmmType,
  Boolean *  preferredCMMnotfound)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMIterateCMMInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.6 and later
 */
extern CMError 
CMIterateCMMInfo(
  CMMIterateUPP   proc,
  UInt32 *        count,
  void *          refCon)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMGetColorSyncVersion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.6 and later
 */
extern CMError 
CMGetColorSyncVersion(UInt32 * version)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMLaunchControlPanel()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 3.0 and later
 */
extern CMError 
CMLaunchControlPanel(UInt32 flags)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* Converting Colors */
/*
 *  CMConvertXYZToLab()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMConvertXYZToLab(
  const CMColor *     src,
  const CMXYZColor *  white,
  CMColor *           dst,
  UInt32              count)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMConvertLabToXYZ()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMConvertLabToXYZ(
  const CMColor *     src,
  const CMXYZColor *  white,
  CMColor *           dst,
  UInt32              count)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMConvertXYZToLuv()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMConvertXYZToLuv(
  const CMColor *     src,
  const CMXYZColor *  white,
  CMColor *           dst,
  UInt32              count)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMConvertLuvToXYZ()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMConvertLuvToXYZ(
  const CMColor *     src,
  const CMXYZColor *  white,
  CMColor *           dst,
  UInt32              count)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMConvertXYZToYxy()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMConvertXYZToYxy(
  const CMColor *  src,
  CMColor *        dst,
  UInt32           count)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMConvertYxyToXYZ()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMConvertYxyToXYZ(
  const CMColor *  src,
  CMColor *        dst,
  UInt32           count)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMConvertRGBToHLS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMConvertRGBToHLS(
  const CMColor *  src,
  CMColor *        dst,
  UInt32           count)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMConvertHLSToRGB()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMConvertHLSToRGB(
  const CMColor *  src,
  CMColor *        dst,
  UInt32           count)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMConvertRGBToHSV()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMConvertRGBToHSV(
  const CMColor *  src,
  CMColor *        dst,
  UInt32           count)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMConvertHSVToRGB()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMConvertHSVToRGB(
  const CMColor *  src,
  CMColor *        dst,
  UInt32           count)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMConvertRGBToGray()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMConvertRGBToGray(
  const CMColor *  src,
  CMColor *        dst,
  UInt32           count)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMConvertXYZToFixedXYZ()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMConvertXYZToFixedXYZ(
  const CMXYZColor *  src,
  CMFixedXYZColor *   dst,
  UInt32              count)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMConvertFixedXYZToXYZ()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.1 and later
 */
extern CMError 
CMConvertFixedXYZToXYZ(
  const CMFixedXYZColor *  src,
  CMXYZColor *             dst,
  UInt32                   count)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMConvertXYZToXYZ()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CMError 
CMConvertXYZToXYZ(
  const CMColor *         src,
  const CMXYZColor *      srcIlluminant,
  CMColor *               dst,
  const CMXYZColor *      dstIlluminant,
  CMChromaticAdaptation   method,
  UInt32                  count)                              AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;



/* Working with PostScript */
/*
 *  CMGetPS2ColorSpace()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMGetPS2ColorSpace(
  CMProfileRef   srcProf,
  UInt32         flags,
  CMFlattenUPP   proc,
  void *         refCon,
  Boolean *      preferredCMMnotfound)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMGetPS2ColorRenderingIntent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMGetPS2ColorRenderingIntent(
  CMProfileRef   srcProf,
  UInt32         flags,
  CMFlattenUPP   proc,
  void *         refCon,
  Boolean *      preferredCMMnotfound)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMGetPS2ColorRendering()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
CMGetPS2ColorRendering(
  CMProfileRef   srcProf,
  CMProfileRef   dstProf,
  UInt32         flags,
  CMFlattenUPP   proc,
  void *         refCon,
  Boolean *      preferredCMMnotfound)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMGetPS2ColorRenderingVMSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorSyncLib 2.0 and later
 */
extern CMError 
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



#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __CMAPPLICATION__ */

