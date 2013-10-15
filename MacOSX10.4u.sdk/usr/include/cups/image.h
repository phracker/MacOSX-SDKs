/*
 * "$Id: image.h,v 1.1.1.12 2005/01/04 19:16:01 jlovell Exp $"
 *
 *   Image library definitions for the Common UNIX Printing System (CUPS).
 *
 *   Copyright 1993-2005 by Easy Software Products.
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
 *   This file is subject to the Apple OS-Developed Software exception.
 */

#ifndef _IMAGE_H_
#  define _IMAGE_H_

/*
 * Include necessary headers...
 */

#  include <stdio.h>
#  include <stdlib.h>
#  include <string.h>
#  include <errno.h>
#  include <config.h>
#  include "raster.h"


/*
 * Maximum image dimensions that we can handle...
 */

#  define IMAGE_MAX_WIDTH	0x07ffffff	/* 2^27-1 to allow for 15-channel data */
#  define IMAGE_MAX_HEIGHT	0x7fffffff	/* 2^31-1 */

/*
 * Colorspaces...
 */

#  define IMAGE_CMYK	-4		/* Cyan, magenta, yellow, and black */
#  define IMAGE_CMY	-3		/* Cyan, magenta, and yellow */
#  define IMAGE_BLACK	-1		/* Black */
#  define IMAGE_WHITE	1		/* White (luminance) */
#  define IMAGE_RGB	3		/* Red, green, and blue */
#  define IMAGE_RGB_CMYK 4		/* Use RGB or CMYK */

/*
 * Tile definitions...
 */

#  define TILE_SIZE	256		/* 256x256 pixel tiles */
#  define TILE_MINIMUM	10		/* Minimum number of tiles */

/*
 * min/max/abs macros...
 */

#ifndef max
#  define 	max(a,b)	((a) > (b) ? (a) : (b))
#endif /* !max */
#ifndef min
#  define 	min(a,b)	((a) < (b) ? (a) : (b))
#endif /* !min */
#ifndef abs
#  define	abs(a)		((a) < 0 ? -(a) : (a))
#endif /* !abs */


/*
 * Image byte type...
 */

typedef unsigned char ib_t;

/*
 * Tile cache structure...
 */

typedef struct ic_str
{
  struct ic_str	*prev,		/* Previous tile in cache */
		*next;		/* Next tile in cache */
  void		*tile;		/* Tile this is attached to */
  ib_t		*pixels;	/* Pixel data */
} ic_t;

/*
 * Tile structure...
 */

typedef struct
{
  int		dirty;		/* True if tile is dirty */
  long		pos;		/* Position of tile on disk (-1 if not written) */
  ic_t		*ic;		/* Pixel data */
} itile_t;

/*
 * Image structure...
 */

typedef struct
{
  int		colorspace;	/* Colorspace of image */
  unsigned	xsize,		/* Width of image in pixels */
		ysize,		/* Height of image in pixels */
		xppi,		/* X resolution in pixels-per-inch */
		yppi,		/* Y resolution in pixels-per-inch */
		num_ics,	/* Number of cached tiles */
		max_ics;	/* Maximum number of cached tiles */
  itile_t	**tiles;	/* Tiles in image */
  ic_t		*first,		/* First cached tile in image */
		*last;		/* Last cached tile in image */
  FILE		*cachefile;	/* Tile cache file */
  char		cachename[256];	/* Tile cache filename */
} image_t;

/*
 * Image row zooming structure...
 */

typedef struct
{
  image_t	*img;		/* Image to zoom */
  unsigned	xorig,
		yorig,
		width,		/* Width of input area */
		height,		/* Height of input area */
		depth,		/* Number of bytes per pixel */
		rotated,	/* Non-zero if image needs to be rotated */
		xsize,		/* Width of output image */
		ysize,		/* Height of output image */
		xmax,		/* Maximum input image X position */
		ymax,		/* Maximum input image Y position */
		xmod,		/* Threshold for Bresenheim rounding */
		ymod;		/* ... */
  int		xstep,		/* Amount to step for each pixel along X */
		xincr,
		instep,		/* Amount to step pixel pointer along X */
		inincr,
		ystep,		/* Amount to step for each pixel along Y */
		yincr,
		row;		/* Current row */
  ib_t		*rows[2],	/* Horizontally scaled pixel data */
		*in;		/* Unscaled input pixel data */
} izoom_t;


/*
 * Basic image functions...
 */

extern image_t	*ImageOpen(char *filename, int primary, int secondary,
		           int saturation, int hue, const ib_t *lut);
extern void	ImageClose(image_t *img);
extern void	ImageSetColorSpace(cups_cspace_t cs);
extern void	ImageSetMaxTiles(image_t *img, int max_tiles);
extern void	ImageSetProfile(float d, float g, float matrix[3][3]);

#define 	ImageGetDepth(img)	((img)->colorspace < 0 ? -(img)->colorspace : (img)->colorspace)
extern int	ImageGetCol(image_t *img, int x, int y, int height, ib_t *pixels);
extern int	ImageGetRow(image_t *img, int x, int y, int width, ib_t *pixels);
extern int	ImagePutCol(image_t *img, int x, int y, int height, const ib_t *pixels);
extern int	ImagePutRow(image_t *img, int x, int y, int width, const ib_t *pixels);

/*
 * File formats...
 */

extern int	ImageReadBMP(image_t *img, FILE *fp, int primary, int secondary,
		             int saturation, int hue, const ib_t *lut);
extern int	ImageReadFPX(image_t *img, FILE *fp, int primary, int secondary,
		             int saturation, int hue, const ib_t *lut);
extern int	ImageReadGIF(image_t *img, FILE *fp, int primary, int secondary,
		             int saturation, int hue, const ib_t *lut);
extern int	ImageReadJPEG(image_t *img, FILE *fp, int primary, int secondary,
		              int saturation, int hue, const ib_t *lut);
extern int	ImageReadPIX(image_t *img, FILE *fp, int primary, int secondary,
		             int saturation, int hue, const ib_t *lut);
extern int	ImageReadPNG(image_t *img, FILE *fp, int primary, int secondary,
		             int saturation, int hue, const ib_t *lut);
extern int	ImageReadPNM(image_t *img, FILE *fp, int primary, int secondary,
		             int saturation, int hue, const ib_t *lut);
extern int	ImageReadPhotoCD(image_t *img, FILE *fp, int primary,
		                 int secondary, int saturation, int hue,
				 const ib_t *lut);
extern int	ImageReadSGI(image_t *img, FILE *fp, int primary, int secondary,
		             int saturation, int hue, const ib_t *lut);
extern int	ImageReadSunRaster(image_t *img, FILE *fp, int primary,
		                   int secondary, int saturation, int hue,
				   const ib_t *lut);
extern int	ImageReadTIFF(image_t *img, FILE *fp, int primary, int secondary,
		              int saturation, int hue, const ib_t *lut);

/*
 * Colorspace conversions...
 */

extern void	ImageWhiteToWhite(const ib_t *in, ib_t *out, int count);
extern void	ImageWhiteToRGB(const ib_t *in, ib_t *out, int count);
extern void	ImageWhiteToBlack(const ib_t *in, ib_t *out, int count);
extern void	ImageWhiteToCMY(const ib_t *in, ib_t *out, int count);
extern void	ImageWhiteToCMYK(const ib_t *in, ib_t *out, int count);

extern void	ImageRGBToWhite(const ib_t *in, ib_t *out, int count);
extern void	ImageRGBToRGB(const ib_t *in, ib_t *out, int count);
extern void	ImageRGBToBlack(const ib_t *in, ib_t *out, int count);
extern void	ImageRGBToCMY(const ib_t *in, ib_t *out, int count);
extern void	ImageRGBToCMYK(const ib_t *in, ib_t *out, int count);

extern void	ImageCMYKToWhite(const ib_t *in, ib_t *out, int count);
extern void	ImageCMYKToRGB(const ib_t *in, ib_t *out, int count);
extern void	ImageCMYKToBlack(const ib_t *in, ib_t *out, int count);
extern void	ImageCMYKToCMY(const ib_t *in, ib_t *out, int count);
extern void	ImageCMYKToCMYK(const ib_t *in, ib_t *out, int count);

extern void	ImageRGBAdjust(ib_t *pixels, int count, int saturation, int hue);

extern void	ImageLut(ib_t *pixels, int count, const ib_t *lut);

/*
 * Image scaling operations...
 */

extern izoom_t	*ImageZoomAlloc(image_t *img, int x0, int y0, int x1, int y1,
		                int xsize, int ysize, int rotated);
extern void	ImageZoomFill(izoom_t *z, int iy);
extern void	ImageZoomQFill(izoom_t *z, int iy);
extern void	ImageZoomFree(izoom_t *z);


#endif /* !_IMAGE_H_ */

/*
 * End of "$Id: image.h,v 1.1.1.12 2005/01/04 19:16:01 jlovell Exp $".
 */
