/*
     File:       PMRaster.h
 
     Contains:   Mac OS X Printing Manager Raster Definitions.
 
     Version:    Technology: Mac OS X
                 Release:    1.0
 
     Copyright:  © 1998-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __PMRASTER__
#define __PMRASTER__

#include <ApplicationServices/ApplicationServices.h>

#ifdef __cplusplus
extern "C" {
#endif

/* MIME type for our raster format (will move to PMDefinitions.h) */
#define kPMDataFormatRaster     CFSTR( "application/vnd.apple.printing-raster" )

typedef UInt32 PMPixelLayout;
enum {
    kPMDataPlanar               = 0x0001,                       /* One color for all pixels, followed by next color. */
    kPMDataChunky               = 0x0002,                       /* All colors for each pixel before next pixel. */
    kPMDataUnused               = 0xFFFC                        /* Remaining bits not used at this time. */
};

/* Pixel formats supported at this time: */

typedef UInt32 PMPixelFormat;
enum {
    kPMGray_1                   = 0x0001,                       /* 1 bit gray scale (B/W) data only (not implemented). */
    kPMGray_8                   = 0x0002,                       /* 8 bit grayscale. 256 possible values, no color table assumed */
    kPMRGB_16                   = 0x0004,                       /* 16 bit, 5-5-5 RGB data, with MSB unused. */
    kPMRGB_24                   = 0x0008,                       /* 24 bit, 8-8-8 RGB data, no unused bits or bytes. */
    kPMXRGB_32                  = 0x0010,                       /* 32 bit x-8-8-8 RGB data, first byte unused in each pixel. */
    kPMRGBX_32                  = 0x0020,                       /* 32 bit 8-8-8-x RGB data, last byte unused in each pixel. */
    kPMRGBX_32_Sep_Gray_8       = 0x0040,                       /* Same as kPMRGBX_32 but with an extra plane of 8-bit K-separation. */
    kPMCMYK_32                  = 0x0080,                       /* 32 bit 8-8-8-8 CMYK data. All bytes used. */
    kPMUnused                   = 0xFF00                        /* Remaining bits are unused for now and should be clear. */
};


typedef UInt32 PMBandOrder;
enum {
    kPMFirstBand                = 0x0000,                            /* First band of the frame */
    kPMMiddleBand               = 0x0001,                            /* Mid-pack band */
    kPMLastBand                 = 0x0002,                            /* Last band */
    kPMLoneBand                 = 0x0003                             /* The only band (whole frame) */
};

/* PMRasterBand: */

struct PMRasterBand {
    Ptr                             baseAddress;                /* ptr to where data is stored */
    UInt32                     		size;                       /* #bytes in band      */
    UInt32                          yOffset;                    /* Band position in the page.  */
    UInt32                          height;                     /* How many scanlines in this band. */
    UInt32                          depth;                      /* How many bits per pixel for this band. */
    PMBandOrder                   	order;                      /* band order in page: first, middle, last, lone. */
};
typedef struct PMRasterBand             PMRasterBand;

#ifdef __cplusplus
}
#endif

#endif /* __PMRASTER__ */

