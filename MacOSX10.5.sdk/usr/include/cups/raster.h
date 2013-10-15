/*
 * "$Id: raster.h 6649 2007-07-11 21:46:42Z mike $"
 *
 *   Raster file definitions for the Common UNIX Printing System (CUPS).
 *
 *   Copyright 2007 by Apple Inc.
 *   Copyright 1997-2006 by Easy Software Products.
 *
 *   This file is part of the CUPS Imaging library.
 *
 *   These coded instructions, statements, and computer programs are the
 *   property of Apple Inc. and are protected by Federal copyright
 *   law.  Distribution and use rights are outlined in the file "LICENSE.txt"
 *   which should have been included with this file.  If this file is
 *   file is missing or damaged, see the license at "http://www.cups.org/".
 *
 *   This file is subject to the Apple OS-Developed Software exception.
 */

#ifndef _CUPS_RASTER_H_
#  define _CUPS_RASTER_H_

/*
 * Include necessary headers...
 */

#  include <cups/cups.h>

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */

/*
 * Every non-PostScript printer driver that supports raster images
 * should use the application/vnd.cups-raster image file format.
 * Since both the PostScript RIP (pstoraster, based on GNU/GPL
 * Ghostscript) and Image RIP (imagetoraster, located in the filter
 * directory) use it, using this format saves you a lot of work.
 * Also, the PostScript RIP passes any printer options that are in
 * a PS file to your driver this way as well...
 */

/*
 * Constants...
 */

#  define CUPS_RASTER_SYNC	0x52615333	/* RaS3 */
#  define CUPS_RASTER_REVSYNC	0x33536152	/* 3SaR */

#  define CUPS_RASTER_SYNCv1	0x52615374	/* RaSt */
#  define CUPS_RASTER_REVSYNCv1	0x74536152	/* tSaR */

#  define CUPS_RASTER_SYNCv2	0x52615332	/* RaS2 */
#  define CUPS_RASTER_REVSYNCv2	0x32536152	/* 2SaR */


/*
 * The following definition can be used to determine if the
 * colorimetric colorspaces (CIEXYZ, CIELAB, and ICCn) are
 * defined...
 */

#  define CUPS_RASTER_HAVE_COLORIMETRIC 1


/*
 * Types...
 */

typedef enum cups_adv_e			/**** AdvanceMedia attribute values ****/
{
  CUPS_ADVANCE_NONE = 0,		/* Never advance the roll */
  CUPS_ADVANCE_FILE = 1,		/* Advance the roll after this file */
  CUPS_ADVANCE_JOB = 2,			/* Advance the roll after this job */
  CUPS_ADVANCE_SET = 3,			/* Advance the roll after this set */
  CUPS_ADVANCE_PAGE = 4			/* Advance the roll after this page */
} cups_adv_t;

typedef enum cups_bool_e		/**** Boolean type ****/
{
  CUPS_FALSE = 0,			/* Logical false */
  CUPS_TRUE = 1				/* Logical true */
} cups_bool_t;

typedef enum cups_cspace_e		/**** cupsColorSpace attribute values ****/
{
  CUPS_CSPACE_W = 0,			/* Luminance */
  CUPS_CSPACE_RGB = 1,			/* Red, green, blue */
  CUPS_CSPACE_RGBA = 2,			/* Red, green, blue, alpha */
  CUPS_CSPACE_K = 3,			/* Black */
  CUPS_CSPACE_CMY = 4,			/* Cyan, magenta, yellow */
  CUPS_CSPACE_YMC = 5,			/* Yellow, magenta, cyan */
  CUPS_CSPACE_CMYK = 6,			/* Cyan, magenta, yellow, black */
  CUPS_CSPACE_YMCK = 7,			/* Yellow, magenta, cyan, black */
  CUPS_CSPACE_KCMY = 8,			/* Black, cyan, magenta, yellow */
  CUPS_CSPACE_KCMYcm = 9,		/* Black, cyan, magenta, yellow, *
					 * light-cyan, light-magenta     */
  CUPS_CSPACE_GMCK = 10,		/* Gold, magenta, yellow, black */
  CUPS_CSPACE_GMCS = 11,		/* Gold, magenta, yellow, silver */
  CUPS_CSPACE_WHITE = 12,		/* White ink (as black) */
  CUPS_CSPACE_GOLD = 13,		/* Gold foil */
  CUPS_CSPACE_SILVER = 14,		/* Silver foil */

  CUPS_CSPACE_CIEXYZ = 15,		/* CIE XYZ @since CUPS 1.1.19@ */
  CUPS_CSPACE_CIELab = 16,		/* CIE Lab @since CUPS 1.1.19@ */
  CUPS_CSPACE_RGBW = 17,		/* Red, green, blue, white @since CUPS 1.2@ */

  CUPS_CSPACE_ICC1 = 32,		/* ICC-based, 1 color @since CUPS 1.1.19@ */
  CUPS_CSPACE_ICC2 = 33,		/* ICC-based, 2 colors @since CUPS 1.1.19@ */
  CUPS_CSPACE_ICC3 = 34,		/* ICC-based, 3 colors @since CUPS 1.1.19@ */
  CUPS_CSPACE_ICC4 = 35,		/* ICC-based, 4 colors @since CUPS 1.1.19@ */
  CUPS_CSPACE_ICC5 = 36,		/* ICC-based, 5 colors @since CUPS 1.1.19@ */
  CUPS_CSPACE_ICC6 = 37,		/* ICC-based, 6 colors @since CUPS 1.1.19@ */
  CUPS_CSPACE_ICC7 = 38,		/* ICC-based, 7 colors @since CUPS 1.1.19@ */
  CUPS_CSPACE_ICC8 = 39,		/* ICC-based, 8 colors @since CUPS 1.1.19@ */
  CUPS_CSPACE_ICC9 = 40,		/* ICC-based, 9 colors @since CUPS 1.1.19@ */
  CUPS_CSPACE_ICCA = 41,		/* ICC-based, 10 colors @since CUPS 1.1.19@ */
  CUPS_CSPACE_ICCB = 42,		/* ICC-based, 11 colors @since CUPS 1.1.19@ */
  CUPS_CSPACE_ICCC = 43,		/* ICC-based, 12 colors @since CUPS 1.1.19@ */
  CUPS_CSPACE_ICCD = 44,		/* ICC-based, 13 colors @since CUPS 1.1.19@ */
  CUPS_CSPACE_ICCE = 45,		/* ICC-based, 14 colors @since CUPS 1.1.19@ */
  CUPS_CSPACE_ICCF = 46			/* ICC-based, 15 colors @since CUPS 1.1.19@ */
} cups_cspace_t;

typedef enum cups_cut_e			/**** CutMedia attribute values ****/
{
  CUPS_CUT_NONE = 0,			/* Never cut the roll */
  CUPS_CUT_FILE = 1,			/* Cut the roll after this file */
  CUPS_CUT_JOB = 2,			/* Cut the roll after this job */
  CUPS_CUT_SET = 3,			/* Cut the roll after this set */
  CUPS_CUT_PAGE = 4			/* Cut the roll after this page */
} cups_cut_t;

typedef enum cups_edge_e		/**** LeadingEdge attribute values ****/
{
  CUPS_EDGE_TOP = 0,			/* Leading edge is the top of the page */
  CUPS_EDGE_RIGHT = 1,			/* Leading edge is the right of the page */
  CUPS_EDGE_BOTTOM = 2,			/* Leading edge is the bottom of the page */
  CUPS_EDGE_LEFT = 3			/* Leading edge is the left of the page */
} cups_edge_t;

typedef enum cups_jog_e			/**** Jog attribute values ****/
{
  CUPS_JOG_NONE = 0,			/* Never move pages */
  CUPS_JOG_FILE = 1,			/* Move pages after this file */
  CUPS_JOG_JOB = 2,			/* Move pages after this job */
  CUPS_JOG_SET = 3			/* Move pages after this set */
} cups_jog_t;

typedef enum cups_mode_e		/**** Raster modes ****/
{
  CUPS_RASTER_READ = 0,			/* Open stream for reading */
  CUPS_RASTER_WRITE = 1,		/* Open stream for writing */
  CUPS_RASTER_WRITE_COMPRESSED = 2	/* Open stream for compressed writing @since CUPS 1.3@ */
} cups_mode_t;

typedef enum cups_order_e		/**** cupsColorOrder attribute values ****/
{
  CUPS_ORDER_CHUNKED = 0,		/* CMYK CMYK CMYK ... */
  CUPS_ORDER_BANDED = 1,		/* CCC MMM YYY KKK ... */
  CUPS_ORDER_PLANAR = 2			/* CCC ... MMM ... YYY ... KKK ... */
} cups_order_t;

typedef enum cups_orient_e		/**** Orientation attribute values ****/
{
  CUPS_ORIENT_0 = 0,			/* Don't rotate the page */
  CUPS_ORIENT_90 = 1,			/* Rotate the page counter-clockwise */
  CUPS_ORIENT_180 = 2,			/* Turn the page upside down */
  CUPS_ORIENT_270 = 3			/* Rotate the page clockwise */
} cups_orient_t;


/*
 * The page header structure contains the standard PostScript page device
 * dictionary, along with some CUPS-specific parameters that are provided
 * by the RIPs...
 *
 * The API supports a "version 1" (from CUPS 1.0 and 1.1) and a "version 2"
 * (from CUPS 1.2 and higher) page header, for binary compatibility.
 */

typedef struct cups_page_header_s	/**** Version 1 Page Header ****/
{
  /**** Standard Page Device Dictionary String Values ****/
  char		MediaClass[64];		/* MediaClass string */
  char		MediaColor[64];		/* MediaColor string */
  char		MediaType[64];		/* MediaType string */
  char		OutputType[64];		/* OutputType string */

  /**** Standard Page Device Dictionary Integer Values ****/
  unsigned	AdvanceDistance;	/* AdvanceDistance value in points */
  cups_adv_t	AdvanceMedia;		/* AdvanceMedia value (see above) */
  cups_bool_t	Collate;		/* Collated copies value */
  cups_cut_t	CutMedia;		/* CutMedia value (see above) */
  cups_bool_t	Duplex;			/* Duplexed (double-sided) value */
  unsigned	HWResolution[2];	/* Resolution in dots-per-inch */
  unsigned	ImagingBoundingBox[4];	/* Pixel region that is painted (points) */
  cups_bool_t	InsertSheet;		/* InsertSheet value */
  cups_jog_t	Jog;			/* Jog value (see above) */
  cups_edge_t	LeadingEdge;		/* LeadingEdge value (see above) */
  unsigned	Margins[2];		/* Lower-lefthand margins in points */
  cups_bool_t	ManualFeed;		/* ManualFeed value */
  unsigned	MediaPosition;		/* MediaPosition value */
  unsigned	MediaWeight;		/* MediaWeight value in grams/m^2 */
  cups_bool_t	MirrorPrint;		/* MirrorPrint value */
  cups_bool_t	NegativePrint;		/* NegativePrint value */
  unsigned	NumCopies;		/* Number of copies to produce */
  cups_orient_t	Orientation;		/* Orientation value (see above) */
  cups_bool_t	OutputFaceUp;		/* OutputFaceUp value */
  unsigned	PageSize[2];		/* Width and length of page in points */
  cups_bool_t	Separations;		/* Separations value */
  cups_bool_t	TraySwitch;		/* TraySwitch value */
  cups_bool_t	Tumble;			/* Tumble value */

  /**** CUPS Page Device Dictionary Values ****/
  unsigned	cupsWidth;		/* Width of page image in pixels */
  unsigned	cupsHeight;		/* Height of page image in pixels */
  unsigned	cupsMediaType;		/* Media type code */
  unsigned	cupsBitsPerColor;	/* Number of bits for each color */
  unsigned	cupsBitsPerPixel;	/* Number of bits for each pixel */
  unsigned	cupsBytesPerLine;	/* Number of bytes per line */
  cups_order_t	cupsColorOrder;		/* Order of colors */
  cups_cspace_t	cupsColorSpace;		/* True colorspace */
  unsigned	cupsCompression;	/* Device compression to use */
  unsigned	cupsRowCount;		/* Rows per band */
  unsigned	cupsRowFeed;		/* Feed between bands */
  unsigned	cupsRowStep;		/* Spacing between lines */
} cups_page_header_t;

/**** New in CUPS 1.2 ****/
typedef struct cups_page_header2_s	/**** Version 2 Page Header @since CUPS 1.2@ ****/
{
  /**** Standard Page Device Dictionary String Values ****/
  char		MediaClass[64];		/* MediaClass string */
  char		MediaColor[64];		/* MediaColor string */
  char		MediaType[64];		/* MediaType string */
  char		OutputType[64];		/* OutputType string */

  /**** Standard Page Device Dictionary Integer Values ****/
  unsigned	AdvanceDistance;	/* AdvanceDistance value in points */
  cups_adv_t	AdvanceMedia;		/* AdvanceMedia value (see above) */
  cups_bool_t	Collate;		/* Collated copies value */
  cups_cut_t	CutMedia;		/* CutMedia value (see above) */
  cups_bool_t	Duplex;			/* Duplexed (double-sided) value */
  unsigned	HWResolution[2];	/* Resolution in dots-per-inch */
  unsigned	ImagingBoundingBox[4];	/* Pixel region that is painted (points) */
  cups_bool_t	InsertSheet;		/* InsertSheet value */
  cups_jog_t	Jog;			/* Jog value (see above) */
  cups_edge_t	LeadingEdge;		/* LeadingEdge value (see above) */
  unsigned	Margins[2];		/* Lower-lefthand margins in points */
  cups_bool_t	ManualFeed;		/* ManualFeed value */
  unsigned	MediaPosition;		/* MediaPosition value */
  unsigned	MediaWeight;		/* MediaWeight value in grams/m^2 */
  cups_bool_t	MirrorPrint;		/* MirrorPrint value */
  cups_bool_t	NegativePrint;		/* NegativePrint value */
  unsigned	NumCopies;		/* Number of copies to produce */
  cups_orient_t	Orientation;		/* Orientation value (see above) */
  cups_bool_t	OutputFaceUp;		/* OutputFaceUp value */
  unsigned	PageSize[2];		/* Width and length of page in points */
  cups_bool_t	Separations;		/* Separations value */
  cups_bool_t	TraySwitch;		/* TraySwitch value */
  cups_bool_t	Tumble;			/* Tumble value */

  /**** CUPS Page Device Dictionary Values ****/
  unsigned	cupsWidth;		/* Width of page image in pixels */
  unsigned	cupsHeight;		/* Height of page image in pixels */
  unsigned	cupsMediaType;		/* Media type code */
  unsigned	cupsBitsPerColor;	/* Number of bits for each color */
  unsigned	cupsBitsPerPixel;	/* Number of bits for each pixel */
  unsigned	cupsBytesPerLine;	/* Number of bytes per line */
  cups_order_t	cupsColorOrder;		/* Order of colors */
  cups_cspace_t	cupsColorSpace;		/* True colorspace */
  unsigned	cupsCompression;	/* Device compression to use */
  unsigned	cupsRowCount;		/* Rows per band */
  unsigned	cupsRowFeed;		/* Feed between bands */
  unsigned	cupsRowStep;		/* Spacing between lines */

  /**** Version 2 Dictionary Values ****/
  unsigned	cupsNumColors;		/* Number of colors @since CUPS 1.2@ */
  float		cupsBorderlessScalingFactor;
					/* Scaling that was applied to page data @since CUPS 1.2@ */
  float		cupsPageSize[2];	/* Floating point PageSize (scaling *
  					 * factor not applied) @since CUPS 1.2@ */
  float		cupsImagingBBox[4];	/* Floating point ImagingBoundingBox *
					 * (scaling factor not applied) @since CUPS 1.2@ */
  unsigned	cupsInteger[16];	/* User-defined integer values @since CUPS 1.2@ */
  float		cupsReal[16];		/* User-defined floating-point values @since CUPS 1.2@ */
  char		cupsString[16][64];	/* User-defined string values @since CUPS 1.2@ */
  char		cupsMarkerType[64];	/* Ink/toner type @since CUPS 1.2@ */
  char		cupsRenderingIntent[64];/* Color rendering intent @since CUPS 1.2@ */
  char		cupsPageSizeName[64];	/* PageSize name @since CUPS 1.2@ */
} cups_page_header2_t;

typedef struct _cups_raster_s cups_raster_t;
					/**** Raster stream data ****/

typedef int (*cups_interpret_cb_t)(cups_page_header2_t *header, int preferred_bits);


/*
 * Prototypes...
 */

extern void		cupsRasterClose(cups_raster_t *r);
extern cups_raster_t	*cupsRasterOpen(int fd, cups_mode_t mode);
extern unsigned		cupsRasterReadHeader(cups_raster_t *r,
			                     cups_page_header_t *h);
extern unsigned		cupsRasterReadPixels(cups_raster_t *r,
			                     unsigned char *p, unsigned len);
extern unsigned		cupsRasterWriteHeader(cups_raster_t *r,
			                      cups_page_header_t *h);
extern unsigned		cupsRasterWritePixels(cups_raster_t *r,
			                      unsigned char *p, unsigned len);

/**** New in CUPS 1.2 ****/
extern int		cupsRasterInterpretPPD(cups_page_header2_t *h,
			                       ppd_file_t *ppd,
					       int num_options,
					       cups_option_t *options,
					       cups_interpret_cb_t func);
extern unsigned		cupsRasterReadHeader2(cups_raster_t *r,
			                      cups_page_header2_t *h);
extern unsigned		cupsRasterWriteHeader2(cups_raster_t *r,
			                       cups_page_header2_t *h);

/**** New in CUPS 1.3 ****/
extern const char	*cupsRasterErrorString(void);

#  ifdef __cplusplus
}
#  endif /* __cplusplus */

#endif /* !_CUPS_RASTER_H_ */

/*
 * End of "$Id: raster.h 6649 2007-07-11 21:46:42Z mike $".
 */
