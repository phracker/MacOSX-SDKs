/*
     File:       ColorSync/CMICCProfile.h
 
     Contains:   ICC Profile Format Definitions
 
     Version:    ColorSync-174.3.3~45
 
     Copyright:  © 1994-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __CMICCPROFILE__
#define __CMICCPROFILE__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif


#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#pragma options align=mac68k

/* ICC Profile version constants  */
enum {
  cmICCProfileVersion4          = 0x04000000,
  cmICCProfileVersion2          = 0x02000000,
  cmICCProfileVersion21         = 0x02100000,
  cmCS2ProfileVersion           = cmICCProfileVersion2,
  cmCS1ProfileVersion           = 0x00000100 /* ColorSync 1.0 profile version */
};

/* Current Major version number */
enum {
  cmProfileMajorVersionMask     = (long)0xFF000000,
  cmCurrentProfileMajorVersion  = 0x02000000
};

/* magic cookie number for anonymous file ID */
enum {
  cmMagicNumber                 = 'acsp'
};


/************************************************************************/
/*************** ColorSync 2.0 profile specification ********************/
/************************************************************************/
/**** flags field  ****/
enum {
  cmICCReservedFlagsMask        = 0x0000FFFF, /* these bits of the flags field are defined and reserved by ICC */
  cmEmbeddedMask                = 0x00000001, /* if bit 0 is 0 then not embedded profile, if 1 then embedded profile */
  cmEmbeddedUseMask             = 0x00000002, /* if bit 1 is 0 then ok to use anywhere, if 1 then ok to use as embedded profile only */
  cmBlackPointCompensationMask  = 0x00000004, /* if bit 1 is 0 then ok to use anywhere, if 1 then ok to use as embedded profile only */
  cmCMSReservedFlagsMask        = (long)0xFFFF0000, /* these bits of the flags field are defined and reserved by CMS vendor */
  cmQualityMask                 = 0x00030000, /* if bits 16-17 is 0 then normal, if 1 then draft, if 2 then best */
  cmInterpolationMask           = 0x00040000, /* if bit 18 is 0 then interpolation, if 1 then lookup only */
  cmGamutCheckingMask           = 0x00080000 /* if bit 19 is 0 then create gamut checking info, if 1 then no gamut checking info */
};

/* copyright-protection flag options */
enum {
  cmEmbeddedProfile             = 0,    /* 0 is not embedded profile, 1 is embedded profile */
  cmEmbeddedUse                 = 1     /* 0 is to use anywhere, 1 is to use as embedded profile only */
};

/* speed and quality flag options */
enum {
  cmNormalMode                  = 0,    /* it uses the least significent two bits in the high word of flag */
  cmDraftMode                   = 1,    /* it should be evaulated like this: right shift 16 bits first, mask off the */
  cmBestMode                    = 2     /* high 14 bits, and then compare with the enum to determine the option value */
};

/* black point compensation flag option */
enum {
  cmBlackPointCompensation      = 1     /* 0 do not apply Black Point Compensation, 1 apply */
};


/**** deviceAttributes fields ****/
/* deviceAttributes[0] is defined by and reserved for device vendors */
/* deviceAttributes[1] is defined by and reserved for ICC */
/* The following bits of deviceAttributes[1] are currently defined */
enum {
  cmReflectiveTransparentMask   = 0x00000001, /* if bit 0 is 0 then reflective media, if 1 then transparency media */
  cmGlossyMatteMask             = 0x00000002 /* if bit 1 is 0 then glossy, if 1 then matte */
};

/* device/media attributes element values  */
enum {
  cmReflective                  = 0,    /* if bit 0 is 0 then reflective media, if 1 then transparency media */
  cmGlossy                      = 1     /* if bit 1 is 0 then glossy, if 1 then matte */
};


/**** renderingIntent field ****/
enum {
  cmPerceptual                  = 0,    /* Photographic images */
  cmRelativeColorimetric        = 1,    /* Logo Colors */
  cmSaturation                  = 2,    /* Business graphics */
  cmAbsoluteColorimetric        = 3     /* Logo Colors */
};



/* data type element values */
enum {
  cmAsciiData                   = 0,
  cmBinaryData                  = 1
};

/* screen encodings  */
enum {
  cmPrtrDefaultScreens          = 0,    /* Use printer default screens.  0 is false, 1 is ture */
  cmLinesPer                    = 1     /* 0 is LinesPerCm, 1 is LinesPerInch */
};

/* 2.0 tag type information */
enum {
  cmNumHeaderElements           = 10
};

/* public tags */
enum {
  cmAToB0Tag                    = 'A2B0',
  cmAToB1Tag                    = 'A2B1',
  cmAToB2Tag                    = 'A2B2',
  cmBlueColorantTag             = 'bXYZ',
  cmBlueTRCTag                  = 'bTRC',
  cmBToA0Tag                    = 'B2A0',
  cmBToA1Tag                    = 'B2A1',
  cmBToA2Tag                    = 'B2A2',
  cmCalibrationDateTimeTag      = 'calt',
  cmChromaticAdaptationTag      = 'chad',
  cmCharTargetTag               = 'targ',
  cmCopyrightTag                = 'cprt',
  cmDeviceMfgDescTag            = 'dmnd',
  cmDeviceModelDescTag          = 'dmdd',
  cmGamutTag                    = 'gamt',
  cmGrayTRCTag                  = 'kTRC',
  cmGreenColorantTag            = 'gXYZ',
  cmGreenTRCTag                 = 'gTRC',
  cmLuminanceTag                = 'lumi',
  cmMeasurementTag              = 'meas',
  cmMediaBlackPointTag          = 'bkpt',
  cmMediaWhitePointTag          = 'wtpt',
  cmNamedColorTag               = 'ncol',
  cmNamedColor2Tag              = 'ncl2',
  cmPreview0Tag                 = 'pre0',
  cmPreview1Tag                 = 'pre1',
  cmPreview2Tag                 = 'pre2',
  cmProfileDescriptionTag       = 'desc',
  cmProfileSequenceDescTag      = 'pseq',
  cmPS2CRD0Tag                  = 'psd0',
  cmPS2CRD1Tag                  = 'psd1',
  cmPS2CRD2Tag                  = 'psd2',
  cmPS2CRD3Tag                  = 'psd3',
  cmPS2CSATag                   = 'ps2s',
  cmPS2RenderingIntentTag       = 'ps2i',
  cmRedColorantTag              = 'rXYZ',
  cmRedTRCTag                   = 'rTRC',
  cmScreeningDescTag            = 'scrd',
  cmScreeningTag                = 'scrn',
  cmTechnologyTag               = 'tech',
  cmUcrBgTag                    = 'bfd ',
  cmViewingConditionsDescTag    = 'vued',
  cmViewingConditionsTag        = 'view'
};

/* custom tags */
enum {
  cmPS2CRDVMSizeTag             = 'psvm',
  cmVideoCardGammaTag           = 'vcgt',
  cmMakeAndModelTag             = 'mmod',
  cmProfileDescriptionMLTag     = 'dscm',
  cmNativeDisplayInfoTag        = 'ndin'
};

/* public type signatures */
enum {
  cmSigCrdInfoType              = 'crdi',
  cmSigCurveType                = 'curv',
  cmSigDataType                 = 'data',
  cmSigDateTimeType             = 'dtim',
  cmSigLut16Type                = 'mft2',
  cmSigLut8Type                 = 'mft1',
  cmSigMeasurementType          = 'meas',
  cmSigMultiFunctA2BType        = 'mAB ',
  cmSigMultiFunctB2AType        = 'mBA ',
  cmSigNamedColorType           = 'ncol',
  cmSigNamedColor2Type          = 'ncl2',
  cmSigParametricCurveType      = 'para',
  cmSigProfileDescriptionType   = 'desc',
  cmSigProfileSequenceDescType  = 'pseq',
  cmSigScreeningType            = 'scrn',
  cmSigS15Fixed16Type           = 'sf32',
  cmSigSignatureType            = 'sig ',
  cmSigTextType                 = 'text',
  cmSigU16Fixed16Type           = 'uf32',
  cmSigU1Fixed15Type            = 'uf16',
  cmSigUInt8Type                = 'ui08',
  cmSigUInt16Type               = 'ui16',
  cmSigUInt32Type               = 'ui32',
  cmSigUInt64Type               = 'ui64',
  cmSigUcrBgType                = 'bfd ',
  cmSigUnicodeTextType          = 'utxt',
  cmSigViewingConditionsType    = 'view',
  cmSigXYZType                  = 'XYZ '
};

/* custom type signatures */
enum {
  cmSigPS2CRDVMSizeType         = 'psvm',
  cmSigVideoCardGammaType       = 'vcgt',
  cmSigMakeAndModelType         = 'mmod',
  cmSigNativeDisplayInfoType    = 'ndin',
  cmSigMultiLocalizedUniCodeType = 'mluc'
};


/* technology tag descriptions */
enum {
  cmTechnologyDigitalCamera     = 'dcam',
  cmTechnologyFilmScanner       = 'fscn',
  cmTechnologyReflectiveScanner = 'rscn',
  cmTechnologyInkJetPrinter     = 'ijet',
  cmTechnologyThermalWaxPrinter = 'twax',
  cmTechnologyElectrophotographicPrinter = 'epho',
  cmTechnologyElectrostaticPrinter = 'esta',
  cmTechnologyDyeSublimationPrinter = 'dsub',
  cmTechnologyPhotographicPaperPrinter = 'rpho',
  cmTechnologyFilmWriter        = 'fprn',
  cmTechnologyVideoMonitor      = 'vidm',
  cmTechnologyVideoCamera       = 'vidc',
  cmTechnologyProjectionTelevision = 'pjtv',
  cmTechnologyCRTDisplay        = 'CRT ',
  cmTechnologyPMDisplay         = 'PMD ',
  cmTechnologyAMDisplay         = 'AMD ',
  cmTechnologyPhotoCD           = 'KPCD',
  cmTechnologyPhotoImageSetter  = 'imgs',
  cmTechnologyGravure           = 'grav',
  cmTechnologyOffsetLithography = 'offs',
  cmTechnologySilkscreen        = 'silk',
  cmTechnologyFlexography       = 'flex'
};


/* Measurement type encodings */
/* Measurement Flare */
enum {
  cmFlare0                      = 0x00000000,
  cmFlare100                    = 0x00000001
};

/* Measurement Geometry */
enum {
  cmGeometryUnknown             = 0x00000000,
  cmGeometry045or450            = 0x00000001,
  cmGeometry0dord0              = 0x00000002
};

/* Standard Observer    */
enum {
  cmStdobsUnknown               = 0x00000000,
  cmStdobs1931TwoDegrees        = 0x00000001,
  cmStdobs1964TenDegrees        = 0x00000002
};

/* Standard Illuminant */
enum {
  cmIlluminantUnknown           = 0x00000000,
  cmIlluminantD50               = 0x00000001,
  cmIlluminantD65               = 0x00000002,
  cmIlluminantD93               = 0x00000003,
  cmIlluminantF2                = 0x00000004,
  cmIlluminantD55               = 0x00000005,
  cmIlluminantA                 = 0x00000006,
  cmIlluminantEquiPower         = 0x00000007,
  cmIlluminantF8                = 0x00000008
};

/* Spot Function Value */
enum {
  cmSpotFunctionUnknown         = 0,
  cmSpotFunctionDefault         = 1,
  cmSpotFunctionRound           = 2,
  cmSpotFunctionDiamond         = 3,
  cmSpotFunctionEllipse         = 4,
  cmSpotFunctionLine            = 5,
  cmSpotFunctionSquare          = 6,
  cmSpotFunctionCross           = 7
};

/* Color Space Signatures */
enum {
  cmXYZData                     = 'XYZ ',
  cmLabData                     = 'Lab ',
  cmLuvData                     = 'Luv ',
  cmYCbCrData                   = 'YCbr',
  cmYxyData                     = 'Yxy ',
  cmRGBData                     = 'RGB ',
  cmSRGBData                    = 'sRGB',
  cmGrayData                    = 'GRAY',
  cmHSVData                     = 'HSV ',
  cmHLSData                     = 'HLS ',
  cmCMYKData                    = 'CMYK',
  cmCMYData                     = 'CMY ',
  cmMCH5Data                    = 'MCH5',
  cmMCH6Data                    = 'MCH6',
  cmMCH7Data                    = 'MCH7',
  cmMCH8Data                    = 'MCH8',
  cm3CLRData                    = '3CLR',
  cm4CLRData                    = '4CLR',
  cm5CLRData                    = '5CLR',
  cm6CLRData                    = '6CLR',
  cm7CLRData                    = '7CLR',
  cm8CLRData                    = '8CLR',
  cm9CLRData                    = '9CLR',
  cm10CLRData                   = 'ACLR',
  cm11CLRData                   = 'BCLR',
  cm12CLRData                   = 'CCLR',
  cm13CLRData                   = 'DCLR',
  cm14CLRData                   = 'ECLR',
  cm15CLRData                   = 'FCLR',
  cmNamedData                   = 'NAME'
};

/* profileClass enumerations */
enum {
  cmInputClass                  = 'scnr',
  cmDisplayClass                = 'mntr',
  cmOutputClass                 = 'prtr',
  cmLinkClass                   = 'link',
  cmAbstractClass               = 'abst',
  cmColorSpaceClass             = 'spac',
  cmNamedColorClass             = 'nmcl'
};

/* platform enumerations */
enum {
  cmMacintosh                   = 'APPL',
  cmMicrosoft                   = 'MSFT',
  cmSolaris                     = 'SUNW',
  cmSiliconGraphics             = 'SGI ',
  cmTaligent                    = 'TGNT'
};

/* parametric curve type enumerations */
enum {
  cmParametricType0             = 0,    /* Y = X^gamma */
  cmParametricType1             = 1,    /* Y = (aX+b)^gamma     [X>=-b/a],  Y = 0    [X<-b/a] */
  cmParametricType2             = 2,    /* Y = (aX+b)^gamma + c [X>=-b/a],  Y = c    [X<-b/a] */
  cmParametricType3             = 3,    /* Y = (aX+b)^gamma     [X>=d],     Y = cX   [X<d]    */
  cmParametricType4             = 4     /* Y = (aX+b)^gamma + e [X>=d],     Y = cX+f [X<d]    */
};


/* ColorSync 1.0 elements */
enum {
  cmCS1ChromTag                 = 'chrm',
  cmCS1TRCTag                   = 'trc ',
  cmCS1NameTag                  = 'name',
  cmCS1CustTag                  = 'cust'
};

/* General element data types */
struct CMDateTime {
  UInt16              year;
  UInt16              month;
  UInt16              dayOfTheMonth;
  UInt16              hours;
  UInt16              minutes;
  UInt16              seconds;
};
typedef struct CMDateTime               CMDateTime;
struct CMFixedXYColor {
  Fixed               x;
  Fixed               y;
};
typedef struct CMFixedXYColor           CMFixedXYColor;
struct CMFixedXYZColor {
  Fixed               X;
  Fixed               Y;
  Fixed               Z;
};
typedef struct CMFixedXYZColor          CMFixedXYZColor;

typedef UInt16                          CMXYZComponent;
struct CMXYZColor {
  CMXYZComponent      X;
  CMXYZComponent      Y;
  CMXYZComponent      Z;
};
typedef struct CMXYZColor               CMXYZColor;
/* Typedef for Profile MD5 message digest */
/* Derived from the RSA Data Security, Inc. MD5 Message-Digest Algorithm */

typedef unsigned char                   CMProfileMD5[16];
typedef CMProfileMD5 *                  CMProfileMD5Ptr;

/*
 *  CMProfileMD5AreEqual()
 *  
 *  Availability:       available as macro/inline
 */
#ifdef __cplusplus
  inline Boolean CMProfileMD5AreEqual(CMProfileMD5 a, CMProfileMD5 b)
  {
    return  ((long*)a)[0]==((long*)b)[0] && ((long*)a)[1]==((long*)b)[1] &&
         ((long*)a)[2]==((long*)b)[2] && ((long*)a)[3]==((long*)b)[3];
  }
#else
  #define CMProfileMD5AreEqual(a, b) (\
    ((long*)a)[0]==((long*)b)[0] && ((long*)a)[1]==((long*)b)[1] && \
  ((long*)a)[2]==((long*)b)[2] && ((long*)a)[3]==((long*)b)[3])
#endif

struct CM2Header {
  UInt32              size;                   /* This is the total size of the Profile */
  OSType              CMMType;                /* CMM signature,  Registered with CS2 consortium  */
  UInt32              profileVersion;         /* Version of CMProfile format */
  OSType              profileClass;           /* input, display, output, devicelink, abstract, or color conversion profile type */
  OSType              dataColorSpace;         /* color space of data */
  OSType              profileConnectionSpace; /* profile connection color space */
  CMDateTime          dateTime;               /* date and time of profile creation */
  OSType              CS2profileSignature;    /* 'acsp' constant ColorSync 2.0 file ID */
  OSType              platform;               /* primary profile platform, Registered with CS2 consortium */
  UInt32              flags;                  /* profile flags */
  OSType              deviceManufacturer;     /* Registered with ICC consortium */
  UInt32              deviceModel;            /* Registered with ICC consortium */
  UInt32              deviceAttributes[2];    /* Attributes[0] is for device vendors, [1] is for ICC */
  UInt32              renderingIntent;        /* preferred rendering intent of tagged object */
  CMFixedXYZColor     white;                  /* profile illuminant */
  OSType              creator;                /* profile creator */
  char                reserved[44];           /* reserved for future use */
};
typedef struct CM2Header                CM2Header;
struct CM4Header {
  UInt32              size;                   /* This is the total size of the Profile */
  OSType              CMMType;                /* CMM signature,  Registered with CS2 consortium  */
  UInt32              profileVersion;         /* Version of CMProfile format */
  OSType              profileClass;           /* input, display, output, devicelink, abstract, or color conversion profile type */
  OSType              dataColorSpace;         /* color space of data */
  OSType              profileConnectionSpace; /* profile connection color space */
  CMDateTime          dateTime;               /* date and time of profile creation */
  OSType              CS2profileSignature;    /* 'acsp' constant ColorSync 2.0 file ID */
  OSType              platform;               /* primary profile platform, Registered with CS2 consortium */
  UInt32              flags;                  /* profile flags */
  OSType              deviceManufacturer;     /* Registered with ICC consortium */
  UInt32              deviceModel;            /* Registered with ICC consortium */
  UInt32              deviceAttributes[2];    /* Attributes[0] is for device vendors, [1] is for ICC */
  UInt32              renderingIntent;        /* preferred rendering intent of tagged object */
  CMFixedXYZColor     white;                  /* profile illuminant */
  OSType              creator;                /* profile creator */
  CMProfileMD5        digest;                 /* Profile message digest */
  char                reserved[28];           /* reserved for future use */
};
typedef struct CM4Header                CM4Header;
struct CMTagRecord {
  OSType              tag;                    /* Registered with CS2 consortium */
  UInt32              elementOffset;          /* Relative to start of CMProfile */
  UInt32              elementSize;
};
typedef struct CMTagRecord              CMTagRecord;
struct CMTagElemTable {
  UInt32              count;
  CMTagRecord         tagList[1];             /* variable size, determined by count */
};
typedef struct CMTagElemTable           CMTagElemTable;
struct CM2Profile {
  CM2Header           header;
  CMTagElemTable      tagTable;
  char                elemData[1];            /* variable size data for tagged element storage */
};
typedef struct CM2Profile               CM2Profile;
typedef CM2Profile *                    CM2ProfilePtr;
typedef CM2ProfilePtr *                 CM2ProfileHandle;
/* Tag Type Definitions */
struct CMAdaptationMatrixType {
  OSType              typeDescriptor;         /* 'sf32' = cmSigS15Fixed16Type */
  unsigned long       reserved;               /* fill with 0x00 */
  Fixed               adaptationMatrix[9];    /* fixed size of nine matrix entries */
};
typedef struct CMAdaptationMatrixType   CMAdaptationMatrixType;
struct CMCurveType {
  OSType              typeDescriptor;         /* 'curv' = cmSigCurveType */
  UInt32              reserved;               /* fill with 0x00 */
  UInt32              countValue;             /* number of entries in table that follows */
  UInt16              data[1];                /* variable size, determined by countValue */
};
typedef struct CMCurveType              CMCurveType;
struct CMDataType {
  OSType              typeDescriptor;         /* 'data' = cmSigDataType*/
  UInt32              reserved;               /* fill with 0x00 */
  UInt32              dataFlag;               /* 0 = ASCII, 1 = binary */
  char                data[1];                /* variable size, determined by tag element size */
};
typedef struct CMDataType               CMDataType;
struct CMDateTimeType {
  OSType              typeDescriptor;         /* 'dtim' = cmSigDateTimeType */
  UInt32              reserved;               /* fill with 0x00 */
  CMDateTime          dateTime;               /* */
};
typedef struct CMDateTimeType           CMDateTimeType;
struct CMLut16Type {
  OSType              typeDescriptor;         /* 'mft2' = cmSigLut16Type */
  UInt32              reserved;               /* fill with 0x00 */
  UInt8               inputChannels;          /* Number of input channels */
  UInt8               outputChannels;         /* Number of output channels */
  UInt8               gridPoints;             /* Number of clutTable grid points */
  UInt8               reserved2;              /* fill with 0x00 */
  Fixed               matrix[3][3];           /* */
  UInt16              inputTableEntries;      /* Number of entries in 1-D input luts */
  UInt16              outputTableEntries;     /* Number of entries in 1-D output luts */
  UInt16              inputTable[1];          /* variable size, determined by inputChannels*inputTableEntries */
#if 0 /* NOTE: Field offsets are variable from here on. */
  /* In order to correctly reflect the actual format of this tag, some of the fields in */
  /* this structure have been removed because they follow an array field of variable size. */
  /* As a result, the size of this structure has changed from previous versions of this interface. */
  /* Code that relies on sizeof(CMLut16Type) should be changed. */
  UInt16              CLUT[];                 /* variable size, determined by (gridPoints^inputChannels)*outputChannels */
  UInt16              outputTable[];          /* variable size, determined by outputChannels*outputTableEntries */
#endif
};
typedef struct CMLut16Type              CMLut16Type;
struct CMLut8Type {
  OSType              typeDescriptor;         /* 'mft1' = cmSigLut8Type */
  UInt32              reserved;               /* fill with 0x00 */
  UInt8               inputChannels;          /* Number of input channels */
  UInt8               outputChannels;         /* Number of output channels */
  UInt8               gridPoints;             /* Number of clutTable grid points */
  UInt8               reserved2;              /* fill with 0x00 */
  Fixed               matrix[3][3];           /* */
  UInt8               inputTable[1];          /* variable size, determined by inputChannels*256 */
#if 0 /* NOTE: Field offsets are variable from here on. */
  /* In order to correctly reflect the actual format of this tag, some of the fields in */
  /* this structure have been removed because they follow an array field of variable size. */
  /* As a result, the size of this structure has changed from previous versions of this interface. */
  /* Code that relies on sizeof(CMLut8Type) should be changed. */
  UInt8               CLUT[];                 /* variable size, determined by (gridPoints^inputChannels)*outputChannels */
  UInt8               outputTable[];          /* variable size, determined by outputChannels*256 */
#endif
};
typedef struct CMLut8Type               CMLut8Type;
struct CMMultiFunctLutType {
  OSType              typeDescriptor;         /* 'mAB ' = cmSigMultiFunctA2BType or 'mBA ' = cmSigMultiFunctB2AType */
  UInt32              reserved;               /* fill with 0x00 */
  UInt8               inputChannels;          /* Number of input channels */
  UInt8               outputChannels;         /* Number of output channels */
  UInt16              reserved2;              /* fill with 0x00 */
  UInt32              offsetBcurves;          /* offset to first "B" curve */
  UInt32              offsetMatrix;           /* offset to 3x4 matrix */
  UInt32              offsetMcurves;          /* offset to first "M" curve */
  UInt32              offsetCLUT;             /* offset to multi-dimensional LUT of type CMMultiFunctCLUTType */
  UInt32              offsetAcurves;          /* offset to first "A" curve */
  UInt8               data[1];                /* variable size */
};
typedef struct CMMultiFunctLutType      CMMultiFunctLutType;
typedef CMMultiFunctLutType             CMMultiFunctLutA2BType;
typedef CMMultiFunctLutType             CMMultiFunctLutB2AType;
struct CMMultiFunctCLUTType {
  UInt8               gridPoints[16];         /* grigpoints for each input channel dimension (remaining are 0) */
  UInt8               entrySize;              /* bytes per lut enrty (1 or 2) */
  UInt8               reserved[3];            /* fill with 0x00 */
  UInt8               data[1];                /* variable size, determined by above */
};
typedef struct CMMultiFunctCLUTType     CMMultiFunctCLUTType;
struct CMMeasurementType {
  OSType              typeDescriptor;         /* 'meas' = cmSigMeasurementType */
  UInt32              reserved;               /* fill with 0x00 */
  UInt32              standardObserver;       /* cmStdobsUnknown, cmStdobs1931TwoDegrees, cmStdobs1964TenDegrees */
  CMFixedXYZColor     backingXYZ;             /* absolute XYZ values of backing */
  UInt32              geometry;               /* cmGeometryUnknown, cmGeometry045or450 (0/45), cmGeometry0dord0 (0/d or d/0) */
  UInt32              flare;                  /* cmFlare0, cmFlare100 */
  UInt32              illuminant;             /* cmIlluminantUnknown, cmIlluminantD50, ... */
};
typedef struct CMMeasurementType        CMMeasurementType;
struct CMNamedColorType {
  OSType              typeDescriptor;         /* 'ncol' = cmSigNamedColorType */
  UInt32              reserved;               /* fill with 0x00 */
  UInt32              vendorFlag;             /* */
  UInt32              count;                  /* count of named colors in array that follows */
  UInt8               prefixName[1];          /* variable size, max = 32 */
#if 0 /* NOTE: Field offsets are variable from here on. */
  /* In order to correctly reflect the actual format of this tag, some of the fields in */
  /* this structure have been removed because they follow an array field of variable size. */
  /* As a result, the size of this structure has changed from previous versions of this interface. */
  /* Code that relies on sizeof(CMNamedColorType) should be changed. */
  UInt8               suffixName[];           /* variable size, max = 32 */
  struct {
    UInt8             rootName[];             /* variable size, max = 32 */
    UInt8             colorCoords[];          /* variable size */
  } colorName[];                              /* variable size */
#endif
};
typedef struct CMNamedColorType         CMNamedColorType;
struct CMNamedColor2EntryType {
  UInt8               rootName[32];           /* 32 byte field.  7 bit ASCII null terminated */
  UInt16              PCSColorCoords[3];      /* Lab or XYZ color */
  UInt16              DeviceColorCoords[1];   /* variable size */
};
typedef struct CMNamedColor2EntryType   CMNamedColor2EntryType;
struct CMNamedColor2Type {
  OSType              typeDescriptor;         /* 'ncl2' = cmSigNamedColor2Type */
  UInt32              reserved;               /* fill with 0x00 */
  UInt32              vendorFlag;             /* lower 16 bits reserved for ICC use */
  UInt32              count;                  /* count of named colors in array that follows */
  UInt32              deviceChannelCount;     /* number of device channels, 0 indicates no device value available */
  UInt8               prefixName[32];         /* Fixed 32 byte size.  7 bit ASCII null terminated */
  UInt8               suffixName[32];         /* Fixed 32 byte size.  7 bit ASCII null terminated */
  char                data[1];                /* variable size data for CMNamedColor2EntryType */
};
typedef struct CMNamedColor2Type        CMNamedColor2Type;
struct CMNativeDisplayInfo {
  UInt32              dataSize;               /* Size of this structure */
  CMFixedXYColor      redPhosphor;            /* Phosphors - native cromaticity values of the display  */
  CMFixedXYColor      greenPhosphor;
  CMFixedXYColor      bluePhosphor;
  CMFixedXYColor      whitePoint;
  Fixed               redGammaValue;          /* Gammas - native gamma values of the display */
  Fixed               greenGammaValue;
  Fixed               blueGammaValue;
                                              /*  Gamma tables - if if gammaChannels is not zero, */
                                              /*  native gamma tables are preferred over values */
                                              /*  redGammaValue, greenGammaValue, blueGammaValue */
  UInt16              gammaChannels;          /* # of gamma channels (1 or 3) */
  UInt16              gammaEntryCount;        /* 1-based number of entries per channel */
  UInt16              gammaEntrySize;         /* size in bytes of each entry */
  char                gammaData[1];           /* variable size, determined by channels*entryCount*entrySize */
};
typedef struct CMNativeDisplayInfo      CMNativeDisplayInfo;
struct CMNativeDisplayInfoType {
  OSType              typeDescriptor;         /* 'ndin' = cmSigNativeDisplayInfoType */
  unsigned long       reserved;               /* fill with 0x00 */
  CMNativeDisplayInfo  nativeDisplayInfo;     /* data of type CMNativeDisplayInfo */
};
typedef struct CMNativeDisplayInfoType  CMNativeDisplayInfoType;
struct CMParametricCurveType {
  OSType              typeDescriptor;         /* 'para' = cmSigParametricCurveType */
  UInt32              reserved;               /* fill with 0x00 */
  UInt16              functionType;           /* cmParametricType0, cmParametricType1, etc. */
  UInt16              reserved2;              /* fill with 0x00 */
  Fixed               value[1];               /* variable size, determined by functionType */
};
typedef struct CMParametricCurveType    CMParametricCurveType;
struct CMTextDescriptionType {
  OSType              typeDescriptor;         /* 'desc' = cmSigProfileDescriptionType */
  UInt32              reserved;               /* fill with 0x00 */
  UInt32              ASCIICount;             /* Count of bytes (including null terminator)  */
  UInt8               ASCIIName[2];           /* variable size, determined by ASCIICount.  7 bit ASCII null terminated */
#if 0 /* NOTE: Field offsets are variable from here on. */
  /* In order to correctly reflect the actual format of this tag, some of the fields in */
  /* this structure have been removed because they follow an array field of variable size. */
  /* As a result, the size of this structure has changed from previous versions of this interface. */
  /* Code that relies on sizeof(CMTextDescriptionType) should be changed. */
  UInt32              UniCodeCode;            /* Unused */
  UInt32              UniCodeCount;           /* Count of 2-byte characters (including null terminator) */
  UInt8               UniCodeName[];          /* variable size, determined by UniCodeCount */
  SInt16              ScriptCodeCode;         /* Mac-defined script code */
  UInt8               ScriptCodeCount;        /* Count of bytes (including null terminator) */
  UInt8               ScriptCodeName[];       /* variable size, determined by ScriptCodeCount */
#endif
};
typedef struct CMTextDescriptionType    CMTextDescriptionType;
struct CMTextType {
  OSType              typeDescriptor;         /* 'text' = cmSigTextType */
  UInt32              reserved;               /* fill with 0x00 */
  UInt8               text[1];                /* variable size, determined by tag element size */
};
typedef struct CMTextType               CMTextType;
struct CMUnicodeTextType {
  OSType              typeDescriptor;         /* 'utxt' = cmSigUnicodeTextType */
  UInt32              reserved;               /* fill with 0x00 */
  UniChar             text[1];                /* variable size, determined by tag element size  */
};
typedef struct CMUnicodeTextType        CMUnicodeTextType;
struct CMScreeningChannelRec {
  Fixed               frequency;
  Fixed               angle;
  UInt32              spotFunction;
};
typedef struct CMScreeningChannelRec    CMScreeningChannelRec;
struct CMScreeningType {
  OSType              typeDescriptor;         /* 'scrn' = cmSigScreeningType */
  UInt32              reserved;               /* fill with 0x00 */
  UInt32              screeningFlag;          /* bit 0 : use printer default screens, bit 1 : inch/cm */
  UInt32              channelCount;           /* */
  CMScreeningChannelRec  channelInfo[1];      /* variable size, determined by channelCount */
};
typedef struct CMScreeningType          CMScreeningType;
struct CMSignatureType {
  OSType              typeDescriptor;         /* 'sig ' = cmSigSignatureType */
  UInt32              reserved;               /* fill with 0x00 */
  OSType              signature;
};
typedef struct CMSignatureType          CMSignatureType;
struct CMS15Fixed16ArrayType {
  OSType              typeDescriptor;         /* 'sf32' = cmSigS15Fixed16Type */
  UInt32              reserved;               /* fill with 0x00 */
  Fixed               value[1];               /* variable size, determined by tag element size */
};
typedef struct CMS15Fixed16ArrayType    CMS15Fixed16ArrayType;
struct CMU16Fixed16ArrayType {
  OSType              typeDescriptor;         /* 'uf32' = cmSigU16Fixed16Type */
  UInt32              reserved;               /* fill with 0x00 */
  UInt32              value[1];               /* variable size, determined by tag element size */
};
typedef struct CMU16Fixed16ArrayType    CMU16Fixed16ArrayType;
struct CMUInt8ArrayType {
  OSType              typeDescriptor;         /* 'ui08' = cmSigUInt8Type */
  UInt32              reserved;               /* fill with 0x00 */
  UInt8               value[1];               /* variable size, determined by tag element size */
};
typedef struct CMUInt8ArrayType         CMUInt8ArrayType;
struct CMUInt16ArrayType {
  OSType              typeDescriptor;         /* 'ui16' = cmSigUInt16Type */
  UInt32              reserved;               /* fill with 0x00 */
  UInt16              value[1];               /* variable size, determined by tag element size */
};
typedef struct CMUInt16ArrayType        CMUInt16ArrayType;
struct CMUInt32ArrayType {
  OSType              typeDescriptor;         /* 'ui32' = cmSigUInt32Type */
  UInt32              reserved;               /* fill with 0x00 */
  UInt32              value[1];               /* variable size, determined by tag element size */
};
typedef struct CMUInt32ArrayType        CMUInt32ArrayType;
struct CMUInt64ArrayType {
  OSType              typeDescriptor;         /* 'ui64' = cmSigUInt64Type */
  UInt32              reserved;               /* fill with 0x00 */
  UInt32              value[1];               /* variable size, determined by tag element size */
};
typedef struct CMUInt64ArrayType        CMUInt64ArrayType;
struct CMViewingConditionsType {
  OSType              typeDescriptor;         /* 'view' = cmSigViewingConditionsType */
  UInt32              reserved;               /* fill with 0x00 */
  CMFixedXYZColor     illuminant;             /* absolute XYZs of illuminant  in cd/m^2 */
  CMFixedXYZColor     surround;               /* absolute XYZs of surround in cd/m^2 */
  UInt32              stdIlluminant;          /* see definitions of std illuminants */
};
typedef struct CMViewingConditionsType  CMViewingConditionsType;
struct CMXYZType {
  OSType              typeDescriptor;         /* 'XYZ ' = cmSigXYZType */
  UInt32              reserved;               /* fill with 0x00 */
  CMFixedXYZColor     XYZ[1];                 /* variable size, determined by tag element size */
};
typedef struct CMXYZType                CMXYZType;
struct CMProfileSequenceDescType {
  OSType              typeDescriptor;         /* 'pseq' = cmProfileSequenceDescTag */
  UInt32              reserved;               /* fill with 0x00 */
  UInt32              count;                  /* Number of descriptions */
  char                data[1];                /* variable size data explained in ICC spec */
};
typedef struct CMProfileSequenceDescType CMProfileSequenceDescType;
struct CMUcrBgType {
  OSType              typeDescriptor;         /* 'bfd ' = cmSigUcrBgType */
  UInt32              reserved;               /* fill with 0x00 */
  UInt32              ucrCount;               /* Number of UCR entries */
  UInt16              ucrValues[1];           /* variable size, determined by ucrCount */
#if 0 /* NOTE: Field offsets are variable from here on. */
  /* In order to correctly reflect the actual format of this tag, some of the fields in */
  /* this structure have been removed because they follow an array field of variable size. */
  /* As a result, the size of this structure has changed from previous versions of this interface. */
  /* Code that relies on sizeof(CMUcrBgType) should be changed. */
  UInt32              bgCount;                /* Number of BG entries */
  UInt16              bgValues[];             /* variable size, determined by bgCount */
  UInt8               ucrbgASCII[];           /* null terminated ASCII string */
#endif
};
typedef struct CMUcrBgType              CMUcrBgType;
/* Private Tag Type Definitions */
struct CMIntentCRDVMSize {
  long                renderingIntent;        /* rendering intent */
  UInt32              VMSize;                 /* VM size taken up by the CRD */
};
typedef struct CMIntentCRDVMSize        CMIntentCRDVMSize;
struct CMPS2CRDVMSizeType {
  OSType              typeDescriptor;         /* 'psvm' = cmSigPS2CRDVMSizeType */
  UInt32              reserved;               /* fill with 0x00 */
  UInt32              count;                  /* number of intent entries */
  CMIntentCRDVMSize   intentCRD[1];           /* variable size, determined by count */
};
typedef struct CMPS2CRDVMSizeType       CMPS2CRDVMSizeType;
enum {
  cmVideoCardGammaTableType     = 0,
  cmVideoCardGammaFormulaType   = 1
};

struct CMVideoCardGammaTable {
  UInt16              channels;               /* # of gamma channels (1 or 3) */
  UInt16              entryCount;             /* 1-based number of entries per channel */
  UInt16              entrySize;              /* size in bytes of each entry */
  char                data[1];                /* variable size, determined by channels*entryCount*entrySize */
};
typedef struct CMVideoCardGammaTable    CMVideoCardGammaTable;
struct CMVideoCardGammaFormula {
  Fixed               redGamma;               /* must be > 0.0 */
  Fixed               redMin;                 /* must be > 0.0 and < 1.0 */
  Fixed               redMax;                 /* must be > 0.0 and < 1.0 */
  Fixed               greenGamma;             /* must be > 0.0 */
  Fixed               greenMin;               /* must be > 0.0 and < 1.0 */
  Fixed               greenMax;               /* must be > 0.0 and < 1.0 */
  Fixed               blueGamma;              /* must be > 0.0 */
  Fixed               blueMin;                /* must be > 0.0 and < 1.0 */
  Fixed               blueMax;                /* must be > 0.0 and < 1.0 */
};
typedef struct CMVideoCardGammaFormula  CMVideoCardGammaFormula;
struct CMVideoCardGamma {
  UInt32              tagType;
  union {
    CMVideoCardGammaTable  table;
    CMVideoCardGammaFormula  formula;
  }                       u;
};
typedef struct CMVideoCardGamma         CMVideoCardGamma;
struct CMVideoCardGammaType {
  OSType              typeDescriptor;         /* 'vcgt' = cmSigVideoCardGammaType */
  UInt32              reserved;               /* fill with 0x00 */
  CMVideoCardGamma    gamma;
};
typedef struct CMVideoCardGammaType     CMVideoCardGammaType;
struct CMMakeAndModel {
  OSType              manufacturer;
  UInt32              model;
  UInt32              serialNumber;
  UInt32              manufactureDate;
  UInt32              reserved1;              /* fill with 0x00 */
  UInt32              reserved2;              /* fill with 0x00 */
  UInt32              reserved3;              /* fill with 0x00 */
  UInt32              reserved4;              /* fill with 0x00 */
};
typedef struct CMMakeAndModel           CMMakeAndModel;
struct CMMakeAndModelType {
  OSType              typeDescriptor;         /* 'mmod' = cmSigMakeAndModelType */
  UInt32              reserved;               /* fill with 0x00 */
  CMMakeAndModel      makeAndModel;
};
typedef struct CMMakeAndModelType       CMMakeAndModelType;
struct CMMultiLocalizedUniCodeEntryRec {
  char                languageCode[2];        /* language code from ISO-639 */
  char                regionCode[2];          /* region code from ISO-3166 */
  UInt32              textLength;             /* the length in bytes of the string */
  UInt32              textOffset;             /* the offset from the start of tag in bytes */
};
typedef struct CMMultiLocalizedUniCodeEntryRec CMMultiLocalizedUniCodeEntryRec;
struct CMMultiLocalizedUniCodeType {
  OSType              typeDescriptor;         /* 'mluc' = cmSigMultiLocalizedUniCodeType */
  UInt32              reserved;               /* fill with 0x00 */
  UInt32              entryCount;             /* 1-based number of name records that follow */
  UInt32              entrySize;              /* size in bytes of name records that follow */

                                              /* variable-length data for storage of CMMultiLocalizedUniCodeEntryRec */

                                              /* variable-length data for storage of Unicode strings*/
};
typedef struct CMMultiLocalizedUniCodeType CMMultiLocalizedUniCodeType;
/************************************************************************/
/*************** ColorSync 1.0 profile specification ********************/
/************************************************************************/
enum {
  cmGrayResponse                = 0,
  cmRedResponse                 = 1,
  cmGreenResponse               = 2,
  cmBlueResponse                = 3,
  cmCyanResponse                = 4,
  cmMagentaResponse             = 5,
  cmYellowResponse              = 6,
  cmUcrResponse                 = 7,
  cmBgResponse                  = 8,
  cmOnePlusLastResponse         = 9
};


/* Device types */
enum {
  cmMonitorDevice               = 'mntr',
  cmScannerDevice               = 'scnr',
  cmPrinterDevice               = 'prtr'
};


struct CMIString {
  ScriptCode          theScript;
  Str63               theString;
};
typedef struct CMIString                CMIString;
/* Profile options */
enum {
  cmPerceptualMatch             = 0x0000, /* Default. For photographic images */
  cmColorimetricMatch           = 0x0001, /* Exact matching when possible */
  cmSaturationMatch             = 0x0002 /* For solid colors */
};

/* Profile flags */
enum {
  cmNativeMatchingPreferred     = 0x00000001, /* Default to native not preferred */
  cmTurnOffCache                = 0x00000002 /* Default to turn on CMM cache */
};


typedef long                            CMMatchOption;
typedef long                            CMMatchFlag;
struct CMHeader {
  UInt32              size;
  OSType              CMMType;
  UInt32              applProfileVersion;
  OSType              dataType;
  OSType              deviceType;
  OSType              deviceManufacturer;
  UInt32              deviceModel;
  UInt32              deviceAttributes[2];
  UInt32              profileNameOffset;
  UInt32              customDataOffset;
  CMMatchFlag         flags;
  CMMatchOption       options;
  CMXYZColor          white;
  CMXYZColor          black;
};
typedef struct CMHeader                 CMHeader;
struct CMProfileChromaticities {
  CMXYZColor          red;
  CMXYZColor          green;
  CMXYZColor          blue;
  CMXYZColor          cyan;
  CMXYZColor          magenta;
  CMXYZColor          yellow;
};
typedef struct CMProfileChromaticities  CMProfileChromaticities;
struct CMProfileResponse {
  UInt16              counts[9];
  UInt16              data[1];                /* Variable size */
};
typedef struct CMProfileResponse        CMProfileResponse;
struct CMProfile {
  CMHeader            header;
  CMProfileChromaticities  profile;
  CMProfileResponse   response;
  CMIString           profileName;
  char                customData[1];          /* Variable size */
};
typedef struct CMProfile                CMProfile;
typedef CMProfile *                     CMProfilePtr;
typedef CMProfilePtr *                  CMProfileHandle;



#pragma options align=reset


#endif /* __CMICCPROFILE__ */

