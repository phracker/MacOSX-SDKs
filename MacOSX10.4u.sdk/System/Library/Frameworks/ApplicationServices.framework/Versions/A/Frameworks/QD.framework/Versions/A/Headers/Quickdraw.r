/*
     File:       Quickdraw.r
 
     Contains:   Interface to Quickdraw Graphics
 
     Version:    Quickdraw-192.24~58
 
     Copyright:  © 1985-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __QUICKDRAW_R__
#define __QUICKDRAW_R__

#ifndef __CORESERVICES_R__
#include <CoreServices/CoreServices.r>
#endif

#ifndef OLDPIXMAPSTRUCT
#if TARGET_API_MAC_OS8
#define OLDPIXMAPSTRUCT 1
#else
#define OLDPIXMAPSTRUCT 0
#endif  /* TARGET_API_MAC_OS8 */

#endif  /* !defined(OLDPIXMAPSTRUCT) */

#ifndef OLDGDEVICESTRUCT
#if TARGET_API_MAC_OS8
#define OLDGDEVICESTRUCT 1
#else
#define OLDGDEVICESTRUCT 0
#endif  /* TARGET_API_MAC_OS8 */

#endif  /* !defined(OLDGDEVICESTRUCT) */


/*----------------------------acur ¥ Cursor Pointers -----------------------------------*/
type 'acur' {
       integer = $$CountOf(CursIdArray); /* Nbr of cursors                 */
       fill word;                        /* Next frame to show             */
       array CursIdArray {
           integer;                      /* 'CURS' resource id for a frame */
           fill word;                    /* Pad word to make longint       */
       };
};


/*---------------------------clut ¥ Generic Color Lookup Table---------------------------*/
/*
    clut_RezTemplateVersion:
       0 - original 
      1 - implicit header, auto index value               <-- default
*/
#ifndef clut_RezTemplateVersion
 #ifdef oldTemp                          /* grandfather in use of ÒoldTempÓ */
      #define clut_RezTemplateVersion 0
  #else
      #define clut_RezTemplateVersion 1
  #endif
#endif

type 'clut' {
   #if clut_RezTemplateVersion == 0
       unsigned hex longint;                                   /* ctSeed               */
     integer;                                                /* ctFlags              */
 #else
      unsigned hex longint = 0;                               /* ctSeed               */
     integer = 0;                                            /* ctFlags              */
 #endif
     integer = $$Countof(ColorSpec) - 1;                     /* ctSize               */
     wide array ColorSpec {
 #if clut_RezTemplateVersion == 0
               integer;                                        /* value                */
 #else
              integer = $$ArrayIndex(ColorSpec) - 1;          /* value                */
 #endif
             unsigned integer;                               /* RGB: red             */
             unsigned integer;                               /*      green           */
             unsigned integer;                               /*      blue            */
     };
};


/*----------------------------------- common macros ---------------------------------------*/

#define PixMapHeight    ( $$BitField(Bounds, 32, 16) /* bottom */           \
                      - $$BitField(Bounds, 0, 16) /* top */ )
#define PixMapWidth     ( $$BitField(Bounds, 48, 16) /* right */            \
                      - $$BitField(Bounds, 16, 16) /* left */ )
#define   PixMapBounds    integer = $$BitField(Bounds, 0, 16) /* top */;      \
                      integer = $$BitField(Bounds, 16, 16) /* left */;    \
                      integer = $$BitField(Bounds, 32, 16) /* bottom */;  \
                      integer = $$BitField(Bounds, 48, 16) /* right */
#define    PixMapRowBytes  (((PixMapWidth * $$Word(PixelSize) + 15) / 16) * 2)
#define BitMapRowBytes  (((PixMapWidth + 15) / 16) * 2)

#define    PixMapHeightIndexed     ( $$BitField(Bounds[$$ArrayIndex(PixPatArray)], 32, 16) /* bottom */            \
                              - $$BitField(Bounds[$$ArrayIndex(PixPatArray)], 0, 16) /* top */ )
#define  PixMapWidthIndexed      ( $$BitField(Bounds[$$ArrayIndex(PixPatArray)], 48, 16) /* right */         \
                              - $$BitField(Bounds[$$ArrayIndex(PixPatArray)], 16, 16) /* left */ )
#define    PixMapRowBytesIndexed   (((PixMapWidthIndexed * $$Word(PixelSize[$$ArrayIndex(PixPatArray)]) + 15) / 16) * 2)


/* RGB colors */
#define whiteRGB $FFFF, $FFFF, $FFFF
#define blackRGB 0, 0, 0

/* colors for 'crsr' resources */
#define transparentRGB $FFFF, $FFFF, $FFFF
#define invertRGB 0, 0, 0


/*------------------------crsr ¥ old Color Cursor template----------------------------------*/
/*
 crsr_RezTemplateVersion:
       0 - original 
      1 - color plus simplified source format             <-- default
*/
#ifndef crsr_RezTemplateVersion
 #ifdef oldTemp                          /* grandfather in use of ÒoldTempÓ */
      #define crsr_RezTemplateVersion 0
  #else
      #define crsr_RezTemplateVersion 1
  #endif
#endif


type 'crsr' {
 #if crsr_RezTemplateVersion == 0
       hex unsigned integer    oldCursor   = $8000,            /* Type of cursor       */
                             colorCursor = $8001;
   #else
      unsigned hex integer = $8001;                           /* Type of cursor       */
 #endif      
       unsigned longint = pixMap / 8;                          /* Offset to pixMap     */
     unsigned longint = pixelData / 8;                       /* Offset to pixel data */
     fill long;                                              /* Expanded cursor data */
     fill word;                                              /* Expanded data depth  */
     fill long;                                              /* Reserved             */
     hex string [32];                                        /* One bit cursor data  */
     hex string [32];                                        /* One bit cursor mask  */
     point;                                                  /* Hot spot             */
     fill long;                                              /* Table id             */
     fill long;                                              /* id for cursor        */

        /* IconPMap (pixMap) record */
 pixMap:
        fill long;                                              /* Base address         */
     unsigned bitstring[1] = 1;                              /* New pixMap flag      */
     unsigned bitstring[2] = 0;                              /* Must be 0            */
 #if crsr_RezTemplateVersion == 0    
       unsigned bitstring[13];                                 /* Offset to next row   */
     rect;                                                   /* Bitmap bounds        */
     integer;                                                /* pixMap version number*/
     integer unpacked;                                       /* Packing format       */
     unsigned longint;                                       /* Size of pixel data   */
     unsigned hex longint;                                   /* h. resolution (ppi) (fixed) */
      unsigned hex longint;                                   /* v. resolution (ppi) (fixed) */
      integer         chunky, chunkyPlanar, planar;           /* Pixel storage format */
     integer;                                                /* # bits in pixel      */
     integer;                                                /* # components in pixel*/
     integer;                                                /* # bits per field     */
     unsigned longint;                                       /* Offset to next plane */
     unsigned longint = colorTable / 8;                      /* Offset to color table*/
     fill long;                                              /* Reserved             */

    pixelData:
     hex string [(colorTable - pixelData) / 8];              /* Pixel data           */
 #else


   pMapRowBytes:
      unsigned bitstring[13] = PixMapRowBytes;                /* Offset to next row   */

    Bounds: 
       rect = { 0, 0, 16, 16 };                                /* Bitmap bounds        */
     integer = 0;                                            /* pixMap vers number   */
     integer = 0;                                            /* Packing format       */
     fill long;                                              /* Size of pixel data   */
     unsigned hex longint = $00480000;                       /* h. resolution (ppi)  */
     unsigned hex longint = $00480000;                       /* v. resolution (ppi)  */
     integer = 0 /* chunky */;                               /* Pixel storage format */
 PixelSize:
     integer;                                                /* # bits in pixel      */
     integer = 1;                                            /* # components in pixel*/
     integer = $$Word(PixelSize);                            /* # bits per field     */
     fill long;
     unsigned longint = ColorTable / 8;
     fill long;

    PixelData:
     hex string [PixMapRowBytes * PixMapHeight];
    #endif

        /* Color Table */
  colorTable:
        unsigned hex longint;                                   /* ctSeed               */
     integer;                                                /* ctFlags              */
     integer = $$Countof(ColorSpec) - 1;                     /* ctSize               */
     wide array ColorSpec {
             integer;                                        /* value                */
             unsigned integer;                               /* RGB: red             */
             unsigned integer;                               /*      green           */
             unsigned integer;                               /*      blue            */
     };
};


/*----------------------------CURS ¥ Cursor---------------------------------------------*/
type 'CURS' {
      hex string [32];                                        /* Data                 */
     hex string [32];                                        /* Mask                 */
     point;                                                  /* Hot spot             */
};


/*----------------------------PAT  ¥ Quickdraw Pattern----------------------------------*/
type 'PAT ' {
      hex string[8];                                          /* Pattern              */
};


/*----------------------------PAT# ¥ Quickdraw Pattern List-----------------------------*/
type 'PAT#' {
      integer = $$Countof(PatArray);
     array PatArray {
               hex string[8];                                  /* Pattern              */
     };
};


/*----------------------------PICT ¥ Quickdraw Picture----------------------------------*/
#ifndef __PICT_R__
    #ifndef PICT_RezTemplateVersion
        #define PICT_RezTemplateVersion 0
    #endif
    #ifndef __PICTUTILS_R__
        #include <QD/PictUtils.r>
    #endif
#endif __PICT_R__

/*------------------------ppat ¥ Pixel Pattern old template---------------------------------*/
/*
 ppat_RezTemplateVersion:
       0 - original 
      1 - color plus simplified source format             <-- default
*/
#ifndef ppat_RezTemplateVersion
 #ifdef oldTemp                          /* grandfather in use of ÒoldTempÓ */
      #define ppat_RezTemplateVersion 0
  #else
      #define ppat_RezTemplateVersion 1
  #endif
#endif


type 'ppat' {
 #if ppat_RezTemplateVersion == 0 
      /* PixPat record */
        integer     oldPattern,                                 /* Pattern type         */
                 newPattern,
                    ditherPattern;
 #else
      integer = 1 /* newPattern */;                           /* Pattern type         */
 #endif
     unsigned longint = PixMap / 8;                          /* Offset to pixmap     */
     unsigned longint = PixelData / 8;                       /* Offset to data       */
     fill long;                                              /* Expanded pixel image */
     fill word;                                              /* Pattern valid flag   */
     fill long;                                              /* expanded pattern     */
     hex string [8];                                         /* old-style pattern    */

        /* PixMap record */
    PixMap:
        fill long;                                              /* Base address         */
     unsigned bitstring[1] = 1;                              /* New pixMap flag      */
     unsigned bitstring[2] = 0;                              /* Must be 0            */
 #if ppat_RezTemplateVersion == 0 
      unsigned bitstring[13];                                 /* Offset to next row   */
     rect;                                                   /* Bitmap bounds        */
     integer;                                                /* pixMap vers number   */
     integer     unpacked;                                   /* Packing format       */
     unsigned longint;                                       /* size of pixel data   */
     unsigned hex longint;                                   /* h. resolution (ppi) (fixed) */
      unsigned hex longint;                                   /* v. resolution (ppi) (fixed) */
      integer         chunky, chunkyPlanar, planar;           /* Pixel storage format */
     integer;                                                /* # bits in pixel      */
     integer;                                                /* # components in pixel*/
     integer;                                                /* # bits per field     */
     unsigned longint;                                       /* Offset to next plane */
     unsigned longint = ColorTable / 8;                      /* Offset to color table*/
     fill long;                                              /* Reserved             */

    PixelData:
     hex string [(ColorTable - PixelData) / 8];
 #else


   pMapRowBytes:
      unsigned bitstring[13] = PixMapRowBytes;                /* Offset to next row   */
 Bounds: rect;                                                   /* Bitmap bounds        */
     integer = 0;                                            /* pixMap vers number   */
     integer = 0;                                            /* Packing format       */
     fill long;                                              /* Size of pixel data   */
     unsigned hex longint = $00480000;                       /* h. resolution (ppi)  */
     unsigned hex longint = $00480000;                       /* v. resolution (ppi)  */
     integer = 0 /* chunky */;                               /* Pixel storage format */
 PixelSize:
     integer;                                                /* # bits in pixel      */
     integer = 1;                                            /* # components in pixel*/
     integer = $$Word(PixelSize);                            /* # bits per field     */
     fill long;
     unsigned longint = ColorTable / 8;
     fill long;

    PixelData:
     hex string [PixMapRowBytes * PixMapHeight];
    #endif
 
   ColorTable:
        unsigned hex longint;                                   /* ctSeed               */
     integer;                                                /* ctFlags              */
     integer = $$Countof(ColorSpec) - 1;                     /* ctSize               */
     wide array ColorSpec {
 #if ppat_RezTemplateVersion == 0
               integer;                                        /* value                */
 #else
              integer = $$ArrayIndex(ColorSpec) - 1;          /* value                */
 #endif
             unsigned integer;                               /* RGB: red             */
             unsigned integer;                               /*      green           */
             unsigned integer;                               /*      blue            */
     };
};


/*----------------------------ppt# ¥ list of pixpats;--------------------------------------*/
type 'ppt#' {
                                           /* PixPat offsets (calculate them some day!?!) */
  integer = $$CountOf(OffsetArray);
  array OffsetArray {                     /* [$$CountOf(PixPatArray)] */ 
        unsigned longint                    /* = PixPat[$$ArrayIndex(OffsetArray)] / 8 */;
 };

    array PixPatArray {
    PixPat:
        /* PixPat record */
        integer = 1 /* newPattern */;                           /* Pattern type         */
     unsigned longint = PixMap[$$ArrayIndex(PixPatArray)] / 8;   /* Offset to pixmap     */
     unsigned longint = PixelData[$$ArrayIndex(PixPatArray)] / 8;    /* Offset to data       */
     fill long;                                              /* Expanded pixel image */
     fill word;                                              /* Pattern valid flag   */
     fill long;                                              /* expanded pattern     */
     hex string [8];                                         /* old-style pattern    */
 
       /* PixMap record */
    PixMap:
        fill long;                                              /* Base address         */
     unsigned bitstring[1] = 1;                              /* New pixMap flag      */
     unsigned bitstring[2] = 0;                              /* Must be 0            */
 pMapRowBytesIndexed:
       unsigned bitstring[13] = PixMapRowBytesIndexed;         /* Offset to next row   */
 Bounds:     
       rect;                                                   /* Bitmap bounds        */
     integer = 0;                                            /* pixMap vers number   */
     integer = 0;                                            /* Packing format       */
     fill long;                                              /* Size of pixel data   */
     unsigned hex longint = $00480000;                       /* h. resolution (ppi)  */
     unsigned hex longint = $00480000;                       /* v. resolution (ppi)  */
     integer = 0 /* chunky */;                               /* Pixel storage format */
 PixelSize:
     integer;                                                /* # bits in pixel      */
     integer = 1;                                            /* # components in pixel*/
     integer = $$Word(PixelSize[$$ArrayIndex(PixPatArray)]); /* # bits per field     */
     fill long;
     unsigned longint = ColorTable[$$ArrayIndex(PixPatArray)] / 8;
      fill long;
 
   PixelData:
     hex string [PixMapRowBytesIndexed * PixMapHeightIndexed];

    
   ColorTable:
        unsigned hex longint = 0;                               /* ctSeed               */
     integer = 0;                                            /* ctFlags              */
     integer = $$Countof(ColorSpec[$$ArrayIndex(PixPatArray)]) - 1;  /* ctSize               */
     wide array ColorSpec {
             integer = $$ArrayIndex(ColorSpec[$$ArrayIndex(PixPatArray)]) - 1;/* value               */
             unsigned integer;                               /* RGB: red             */
             unsigned integer;                               /*      green           */
             unsigned integer;                               /*      blue            */
     };
 };
};


/*----------------------------mitq ¥ Default queue sizes for MakeITable--------------------------------------*/
type 'mitq' {              /* default MakeITable queue sizes */
   wide array [3] {
       unsigned longint;   /* queue size for 3, 4, and 5 bit inverse tables */
    };
};


#endif /* __QUICKDRAW_R__ */

