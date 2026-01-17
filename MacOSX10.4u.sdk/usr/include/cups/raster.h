/*
 * "$Id: raster.h,v 1.6 2005/01/04 22:10:43 jlovell Exp $"
 *
 *   Raster file definitions for the Common UNIX Printing System (CUPS).
 *
 *   Copyright 1997-2005 by Easy Software Products.
 *
 *   This file is part of the CUPS Imaging library.
 *
 *   These coded instructions, statements, and computer programs are the
 *   property of Easy Software Products and are protected by Federal
 *   copyright law.  Distribution and use rights are outlined in the file
 *   "LICENSE.txt" which should have been included with this file.  If this
 *   file is missing or damaged please contact Easy Software Products
 *   at:
 *
 *       Attn: CUPS Licensing Information
 *       Easy Software Products
 *       44141 Airport View Drive, Suite 204
 *       Hollywood, Maryland 20636 USA
 *
 *       Voice: (301) 373-9600
 *       EMail: cups-info@cups.org
 *         WWW: http://www.cups.org
 *
 *   This code and any derivative of it may be used and distributed
 *   freely under the terms of the GNU General Public License when
 *   used with GNU/GPL Ghostscript or its derivatives.  Use of the code
 *   (or any derivative of it) with software other than GNU/GPL
 *   GhostScript (or its derivatives) is governed by the CUPS license
 *   agreement.
 *
 *   This file is subject to the Apple OS-Developed Software exception.
 */

#ifndef _CUPS_RASTER_H_
#  define _CUPS_RASTER_H_

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */

/*
 * Every non-PostScript printer driver that supports raster images should
 * use the application/vnd.cups-raster image file format.  Since both the
 * PostScript RIP (pstoraster, based on GNU Ghostscript) and Image RIP
 * (imagetoraster, located in the filter directory) use it, using this format
 * saves you a lot of work.  Also, the PostScript RIP passes any printer
 * options that are in a PS file to your driver this way as well...
 */

/*
 * Constants...
 */

#  define CUPS_RASTER_SYNC	0x52615374	/* RaSt */
#  define CUPS_RASTER_REVSYNC	0x74536152	/* tSaR */


/*
 * The following definition can be used to determine if the
 * colorimetric colorspaces (CIEXYZ, CIELAB, and ICCn) are
 * defined...
 */

#  define CUPS_RASTER_HAVE_COLORIMETRIC 1


/*
 * Types...
 */

typedef enum
{
  CUPS_RASTER_READ,			/* Open stream for reading */
  CUPS_RASTER_WRITE			/* Open stream for writing */
} cups_mode_t;

typedef enum
{
  CUPS_FALSE,				/* Logical false */
  CUPS_TRUE				/* Logical true */
} cups_bool_t;

typedef enum
{
  CUPS_JOG_NONE,			/* Never move pages */
  CUPS_JOG_FILE,			/* Move pages after this file */
  CUPS_JOG_JOB,				/* Move pages after this job */
  CUPS_JOG_SET				/* Move pages after this set */
} cups_jog_t;

typedef enum
{
  CUPS_ORIENT_0,			/* Don't rotate the page */
  CUPS_ORIENT_90,			/* Rotate the page counter-clockwise */
  CUPS_ORIENT_180,			/* Turn the page upside down */
  CUPS_ORIENT_270			/* Rotate the page clockwise */
} cups_orient_t;

typedef enum
{
  CUPS_CUT_NONE,			/* Never cut the roll */
  CUPS_CUT_FILE,			/* Cut the roll after this file */
  CUPS_CUT_JOB,				/* Cut the roll after this job */
  CUPS_CUT_SET,				/* Cut the roll after this set */
  CUPS_CUT_PAGE				/* Cut the roll after this page */
} cups_cut_t;

typedef enum
{
  CUPS_ADVANCE_NONE,			/* Never advance the roll */
  CUPS_ADVANCE_FILE,			/* Advance the roll after this file */
  CUPS_ADVANCE_JOB,			/* Advance the roll after this job */
  CUPS_ADVANCE_SET,			/* Advance the roll after this set */
  CUPS_ADVANCE_PAGE			/* Advance the roll after this page */
} cups_adv_t;

typedef enum
{
  CUPS_EDGE_TOP,			/* Leading edge is the top of the page */
  CUPS_EDGE_RIGHT,			/* Leading edge is the right of the page */
  CUPS_EDGE_BOTTOM,			/* Leading edge is the bottom of the page */
  CUPS_EDGE_LEFT			/* Leading edge is the left of the page */
} cups_edge_t;

typedef enum
{
  CUPS_ORDER_CHUNKED,			/* CMYK CMYK CMYK ... */
  CUPS_ORDER_BANDED,			/* CCC MMM YYY KKK ... */
  CUPS_ORDER_PLANAR			/* CCC ... MMM ... YYY ... KKK ... */
} cups_order_t;

typedef enum
{
  CUPS_CSPACE_W,			/* Luminance */
  CUPS_CSPACE_RGB,			/* Red, green, blue */
  CUPS_CSPACE_RGBA,			/* Red, green, blue, alpha */
  CUPS_CSPACE_K,			/* Black */
  CUPS_CSPACE_CMY,			/* Cyan, magenta, yellow */
  CUPS_CSPACE_YMC,			/* Yellow, magenta, cyan */
  CUPS_CSPACE_CMYK,			/* Cyan, magenta, yellow, black */
  CUPS_CSPACE_YMCK,			/* Yellow, magenta, cyan, black */
  CUPS_CSPACE_KCMY,			/* Black, cyan, magenta, yellow */
  CUPS_CSPACE_KCMYcm,			/* Black, cyan, magenta, yellow, *
					 * light-cyan, light-magenta     */
  CUPS_CSPACE_GMCK,			/* Gold, magenta, yellow, black */
  CUPS_CSPACE_GMCS,			/* Gold, magenta, yellow, silver */
  CUPS_CSPACE_WHITE,			/* White ink (as black) */
  CUPS_CSPACE_GOLD,			/* Gold foil */
  CUPS_CSPACE_SILVER,			/* Silver foil */

  CUPS_CSPACE_CIEXYZ,			/* CIE XYZ */
  CUPS_CSPACE_CIELab,			/* CIE Lab */

  CUPS_CSPACE_RGBW,			/* composite RGB with W separation */

  CUPS_CSPACE_ICC1 = 32,		/* ICC-based, 1 color */
  CUPS_CSPACE_ICC2,			/* ICC-based, 2 colors */
  CUPS_CSPACE_ICC3,			/* ICC-based, 3 colors */
  CUPS_CSPACE_ICC4,			/* ICC-based, 4 colors */
  CUPS_CSPACE_ICC5,			/* ICC-based, 5 colors */
  CUPS_CSPACE_ICC6,			/* ICC-based, 6 colors */
  CUPS_CSPACE_ICC7,			/* ICC-based, 7 colors */
  CUPS_CSPACE_ICC8,			/* ICC-based, 8 colors */
  CUPS_CSPACE_ICC9,			/* ICC-based, 9 colors */
  CUPS_CSPACE_ICCA,			/* ICC-based, 10 colors */
  CUPS_CSPACE_ICCB,			/* ICC-based, 11 colors */
  CUPS_CSPACE_ICCC,			/* ICC-based, 12 colors */
  CUPS_CSPACE_ICCD,			/* ICC-based, 13 colors */
  CUPS_CSPACE_ICCE,			/* ICC-based, 14 colors */
  CUPS_CSPACE_ICCF			/* ICC-based, 15 colors */
} cups_cspace_t;


/*
 * The page header structure contains the standard PostScript page device
 * dictionary, along with some CUPS-specific parameters that are provided
 * by the RIPs...
 */

typedef struct
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


/*
 * The raster structure maintains information about a raster data
 * stream...
 */

typedef struct
{
  unsigned	sync;			/* Sync word from start of stream */
  int		fd;			/* File descriptor */
  cups_mode_t	mode;			/* Read/write mode */
} cups_raster_t;


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

#  ifdef __cplusplus
}
#  endif /* __cplusplus */

#endif /* !_CUPS_RASTER_H_ */

/*
 * End of "$Id: raster.h,v 1.6 2005/01/04 22:10:43 jlovell Exp $".
 */
