/*
 * ColorSync - ColorSyncTransform.h
 * Copyright (c)  2008 Apple Inc.
 * All rights reserved.
 */

#ifndef __COLORSYNCTRANSFORM__
#define __COLORSYNCTRANSFORM__

#ifdef __cplusplus
extern "C" {
#endif

#include <ColorSync/ColorSyncBase.h>

typedef struct ColorSyncTransform* ColorSyncTransformRef;

CSEXTERN CFTypeID ColorSyncTransformGetTypeID(void);
   /*
    * returns the CFTypeID for ColorSyncTransforms.
    */

CSEXTERN ColorSyncTransformRef ColorSyncTransformCreate (CFArrayRef profileSequence, CFDictionaryRef options);
   /*
    *   profileSequence  - array of dictionaries, each one containing a profile object and the
    *                      information on the usage of the profile in the transform.
    *               
    *               Required keys:
    *               ==============
    *                      kColorSyncProfile           : ColorSyncProfileRef
    *                      kColorSyncRenderingIntent   : CFStringRef defining rendering intent
    *                      kColorSyncTransformTag      : CFStringRef defining which tags to use 
    *               Optional key:
    *               =============
    *                      kColorSyncBlackPointCompensation : CFBooleanRef to enable/disable BPC
    *   
    *   options      - dictionary with additional public global options (e.g. preferred CMM, quality,
    *                       etc... It can also contain custom options that are CMM specific.
    *
    *   returns ColorSyncTransformRef or NULL in case of failure
    */


CSEXTERN CFTypeRef ColorSyncTransformCopyProperty(ColorSyncTransformRef transform, CFTypeRef key, CFDictionaryRef options);
   /*
    *   transform - transform from which to copy the property
    *   key       - CFTypeRef to be used as a key to identify the property
    */


CSEXTERN void ColorSyncTransformSetProperty(ColorSyncTransformRef transform, CFTypeRef key, CFTypeRef property);
   /*
    *   transform - transform in which to set the property
    *   key       - CFTypeRef to be used as a key to identify the property
    *   property  - CFTypeRef to be set as the property
    */

enum ColorSyncDataDepth {
    kColorSync1BitGamut             = 1,
    kColorSync8BitInteger           = 2,
    kColorSync16BitInteger          = 3,
    kColorSync16BitFloat            = 4,
    kColorSync32BitInteger          = 5,
    kColorSync32BitNamedColorIndex  = 6,
    kColorSync32BitFloat            = 7,
    kColorSync10BitInteger          = 8
};

typedef enum ColorSyncDataDepth ColorSyncDataDepth;

enum ColorSyncAlphaInfo {
    kColorSyncAlphaNone,               /* For example, RGB. */
    kColorSyncAlphaPremultipliedLast,  /* For example, premultiplied RGBA */
    kColorSyncAlphaPremultipliedFirst, /* For example, premultiplied ARGB */
    kColorSyncAlphaLast,               /* For example, non-premultiplied RGBA */
    kColorSyncAlphaFirst,              /* For example, non-premultiplied ARGB */
    kColorSyncAlphaNoneSkipLast,       /* For example, RBGX. */
    kColorSyncAlphaNoneSkipFirst,      /* For example, XRGB. */
};

typedef enum ColorSyncAlphaInfo ColorSyncAlphaInfo;

enum {
    kColorSyncAlphaInfoMask = 0x1F,
    
    kColorSyncByteOrderMask = 0x7000,
    kColorSyncByteOrderDefault = (0 << 12),
    kColorSyncByteOrder16Little = (1 << 12),
    kColorSyncByteOrder32Little = (2 << 12),
    kColorSyncByteOrder16Big = (3 << 12),
    kColorSyncByteOrder32Big = (4 << 12)
};


typedef uint32_t ColorSyncDataLayout;

CSEXTERN bool ColorSyncTransformConvert (ColorSyncTransformRef transform, size_t width, size_t height,
                                         void* dst, ColorSyncDataDepth dstDepth,
                                         ColorSyncDataLayout dstLayout, size_t dstBytesPerRow,
                                         const void* src, ColorSyncDataDepth srcDepth,
                                         ColorSyncDataLayout srcLayout, size_t srcBytesPerRow,
                                         CFDictionaryRef options);
   /*
    *   transform         - transform to be used for converting color
    *   width             - width of the image in pixels
    *   height            - height of the image in pixels
    *   dst               - a pointer to the destination where the results will be written.
    *   dstDepth          - describes the bit depth and type of the destination color components
    *   dstFormat         - describes the format and byte packing of the destination pixels
    *   dstBytesPerRow    - number of bytes in the row of data
    *   src               - a pointer to the data to be converted.
    *   srcDepth          - describes the bit depth and type of the source color components
    *   srcFormat         - describes the format and byte packing of the source pixels
    *   srcBytesPerRow    - number of bytes in the row of data
    *
    *   returns true if conversion was successful or false otherwise 
    */


/* Keys and values for profile specific info and options */
CSEXTERN CFStringRef kColorSyncProfile;
CSEXTERN CFStringRef kColorSyncRenderingIntent;

    /* Legal values for kColorSyncRenderingIntent */
        CSEXTERN CFStringRef kColorSyncRenderingIntentPerceptual;
        CSEXTERN CFStringRef kColorSyncRenderingIntentRelative;
        CSEXTERN CFStringRef kColorSyncRenderingIntentSaturation;
        CSEXTERN CFStringRef kColorSyncRenderingIntentAbsolute;
        CSEXTERN CFStringRef kColorSyncRenderingIntentUseProfileHeader;

CSEXTERN CFStringRef kColorSyncTransformTag;

    /* Legal values for kColorSyncTransformTag */
        CSEXTERN CFStringRef kColorSyncTransformDeviceToPCS;
        CSEXTERN CFStringRef kColorSyncTransformPCSToPCS;
        CSEXTERN CFStringRef kColorSyncTransformPCSToDevice;
        CSEXTERN CFStringRef kColorSyncTransformDeviceToDevice;
        CSEXTERN CFStringRef kColorSyncTransformGamutCheck;

CSEXTERN CFStringRef kColorSyncBlackPointCompensation;

/* Global transform options */
CSEXTERN CFStringRef kColorSyncPreferredCMM;       /* ColorSyncCMMRef of the preferred CMM */
CSEXTERN CFStringRef kColorSyncConvertQuality;

    /* Legal values for kColorSyncConvertQuality */
        CSEXTERN CFStringRef kColorSyncBestQuality;      /* do not coalesce profile transforms (default) */
        CSEXTERN CFStringRef kColorSyncNormalQuality;    /* coalesce all transforms */
        CSEXTERN CFStringRef kColorSyncDraftQuality;     /* coalesce all transforms, do not interpolate */

/* Conversion options */
CSEXTERN CFStringRef kColorSyncConvertThreadCount; /* applies to large amounts of data; 0 for number of CPUs */
CSEXTERN CFStringRef kColorSyncConvertUseVectorUnit; /* applies to large amounts of data; CFBooleanRef value; default true*/

/* Public keys for copying transform properties */

CSEXTERN CFStringRef kColorSyncTranformInfo;         /* dictionary with the following keys */
    CSEXTERN CFStringRef kColorSyncTransformCreator; /* name of the CMM that created the transform */
    CSEXTERN CFStringRef kColorSyncTransformSrcSpace;
    CSEXTERN CFStringRef kColorSyncTransformDstSpace;

/*
 * =============================
 *
 *  Code Fragment Support
 *
 * =============================
 *
 * ColorSync can return parameters for standard components of color conversion,
 * i.e. tone rendering curves (TRCs), 3x4 matrices (3x3 + 3x1), multi-dimensional
 * interpolation tables and Black Point Compensation.
 * The parameters are wrapped in CFArray or CFData objects specific to the
 * component type and placed in a CFDictionary under a key that identifies the 
 * type of the component. The complete code fragment is a CFArray of component
 * dictionaries that are placed in the in the order they have to be executed.
 * 
 * A code fragment is created by calling ColorSyncTransformCopyProperty with the key 
 * specifying the type of the code fragment to be created. NULL pointer will be
 * returnde if the requested code fragment cannot be created. The code fragment
 * will be stored in the ColorSyncTransform list of properties and can be removed by 
 * by calling ColorSyncTransformSetProperty with NULL value.
 */

/*
 * Types of Code Fragments:
 *
 * 1. Full conversion: all non-NULL components based on all the tags from the
 *                     sequence of profiles passed to create the ColorWorld with
 *                     an exception of adjacent matrices that can be collapsed to
 *                     one matrix.
 * 2. Parametric:      same as above, except that the returned code fragment consists
 *                     only of parametric curves, matrices and BPC components.
 * 3. Simplified:      Full conversion is collapsed to one
 *                     multi-dimensional table with N inputs and M outputs.
 */
 
    
CSEXTERN CFStringRef kColorSyncTransformCodeFragmentType;           /* CFSTR("com.apple.cmm.CodeFragmentType")  */
CSEXTERN CFStringRef kColorSyncTransformFullConversionData;         /* CFSTR("com.apple.cmm.FullConversion") */
CSEXTERN CFStringRef kColorSyncTransformSimplifiedConversionData;   /* CFSTR("com.apple.cmm.SimplifiedConversion") */
CSEXTERN CFStringRef kColorSyncTransformParametricConversionData;   /* CFSTR("com.apple.cmm.ParametricConversion") */

/*
 * Matrix: represented as a CFArray of three CFArrays of four CFNumbers (Float32)
 *         each, performin the following matrix operation
 *         y[3] = 3x3 matrix *x[3] + 3x1 vector (last column)
 */
CSEXTERN CFStringRef kColorSyncConversionMatrix;        /* CFSTR("com.apple.cmm.Matrix") */

/*
 * Tone Rendering Curves:
 *
 * 1. Parametric curves: represented as a CFArray of seven CFNumbers (Float32)
 *                       [gamma a b c d e f]
 *  Curve Type 0  Y = X^gamma
 *  Curve Type 1  Y = (aX+b)^gamma     [X >= -b/a],  Y = 0  [X < -b/a]
 *  Curve Type 2  Y = (aX+b)^gamma + c [X >= -b/a],  Y = c  [X < -b/a]
 *  Curve Type 3  Y = (aX+b)^gamma     [X >= d],     Y = cX [X < d]
 *  Curve Type 4  Y = (aX+b)^gamma + e [X >= d],     Y = cX + f [X < d]
 *
 * 2. 1-dimensional lookup with interpolation:
 *                  represented as CFData containing a Float32 table[gridPoints]
 */
 
CSEXTERN CFStringRef kColorSyncConversionParamCurve0;   /* CFSTR("com.apple.cmm.ParamCurve0") */
CSEXTERN CFStringRef kColorSyncConversionParamCurve1;   /* CFSTR("com.apple.cmm.ParamCurve1") */
CSEXTERN CFStringRef kColorSyncConversionParamCurve2;   /* CFSTR("com.apple.cmm.ParamCurve2") */
CSEXTERN CFStringRef kColorSyncConversionParamCurve3;   /* CFSTR("com.apple.cmm.ParamCurve3") */
CSEXTERN CFStringRef kColorSyncConversionParamCurve4;   /* CFSTR("com.apple.cmm.ParamCurve4") */
CSEXTERN CFStringRef kColorSyncConversion1DLut;         /* CFSTR("com.apple.cmm.1D-LUT") */
CSEXTERN CFStringRef kColorSyncConversionGridPoints;    /* CFSTR("com.apple.cmm.GridPointCount") */
CSEXTERN CFStringRef kColorSyncConversionChannelID;     /* CFSTR("com.apple.cmm.ChannelID") */

/*
 * Multi-dimensional lookup with interpolation:
 *
 *       represented as CFData containing a table for N inputs, M outputs 
 *       and P gridPoints in each direction. The dimension corresponding to the
 *       first input channel varies least rapidly, and the dimension corresponding
 *       to the last input channel varies most rapidly. Each grid point value contains
 *       M uint16_t numbers, one for each of output channels (M is the number of outputs).
 */
 

CSEXTERN CFStringRef kColorSyncConversion3DLut;      /* CFSTR("com.apple.cmm.3D-LUT") */
CSEXTERN CFStringRef kColorSyncConversionNDLut;      /* CFSTR("com.apple.cmm.ND-LUT") */
CSEXTERN CFStringRef kColorSyncConversionInpChan;    /* CFSTR("com.apple.cmm.InputChannels") */
CSEXTERN CFStringRef kColorSyncConversionOutChan;    /* CFSTR("com.apple.cmm.OutputChannels") */

/*
 * Black Point Compensation: represented as an CFArray of CFNumbers (Float32)
 *
 * 1. Scaling in Luminance: CFArray containing two numbers.
 * 2. Scaling in XYZ: CFArray containing six numbers.
 */
 
CSEXTERN CFStringRef kColorSyncConversionBPC;   /* CFSTR("com.apple.cmm.BPC") */

CSEXTERN CFStringRef kColorSyncFixedPointRange; /* CFSTR("com.apple.cmm.FixedPointRange") */

#ifdef __cplusplus
}
#endif

#endif /* __COLORSYNCTRANSFORM__ */
