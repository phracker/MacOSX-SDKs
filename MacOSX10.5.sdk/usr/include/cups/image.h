/*
 * "$Id: image.h 6649 2007-07-11 21:46:42Z mike $"
 *
 *   Image library definitions for the Common UNIX Printing System (CUPS).
 *
 *   Copyright 2007 by Apple Inc.
 *   Copyright 1993-2006 by Easy Software Products.
 *
 *   These coded instructions, statements, and computer programs are the
 *   property of Apple Inc. and are protected by Federal copyright
 *   law.  Distribution and use rights are outlined in the file "LICENSE.txt"
 *   which should have been included with this file.  If this file is
 *   file is missing or damaged, see the license at "http://www.cups.org/".
 *
 *   This file is subject to the Apple OS-Developed Software exception.
 */

#ifndef _CUPS_IMAGE_H_
#  define _CUPS_IMAGE_H_

/*
 * Include necessary headers...
 */

#  include <stdio.h>
#  include "raster.h"

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */

/*
 * Constants...
 */

typedef enum cups_icspace_e		/**** Image colorspaces ****/
{
  CUPS_IMAGE_CMYK = -4,			/* Cyan, magenta, yellow, and black */
  CUPS_IMAGE_CMY = -3,			/* Cyan, magenta, and yellow */
  CUPS_IMAGE_BLACK = -1,		/* Black */
  CUPS_IMAGE_WHITE = 1,			/* White (luminance) */
  CUPS_IMAGE_RGB = 3,			/* Red, green, and blue */
  CUPS_IMAGE_RGB_CMYK = 4		/* Use RGB or CMYK */
} cups_icspace_t;


/*
 * Types and structures...
 */

typedef unsigned char cups_ib_t;	/**** Image byte ****/

struct cups_image_s;
typedef struct cups_image_s cups_image_t;
					/**** Image file data ****/

struct cups_izoom_s;
typedef struct cups_izoom_s cups_izoom_t;
					/**** Image zoom data ****/


/*
 * Prototypes...
 */

extern void		cupsImageClose(cups_image_t *img);
extern void		cupsImageCMYKToBlack(const cups_ib_t *in,
			                     cups_ib_t *out, int count);
extern void		cupsImageCMYKToCMY(const cups_ib_t *in,
			                   cups_ib_t *out, int count);
extern void		cupsImageCMYKToCMYK(const cups_ib_t *in,
			                    cups_ib_t *out, int count);
extern void		cupsImageCMYKToRGB(const cups_ib_t *in,
			                   cups_ib_t *out, int count);
extern void		cupsImageCMYKToWhite(const cups_ib_t *in,
			                     cups_ib_t *out, int count);
extern int		cupsImageGetCol(cups_image_t *img, int x, int y,
			                int height, cups_ib_t *pixels);
extern cups_icspace_t	cupsImageGetColorSpace(cups_image_t *img);
extern int		cupsImageGetDepth(cups_image_t *img);
extern unsigned		cupsImageGetHeight(cups_image_t *img);
extern int		cupsImageGetRow(cups_image_t *img, int x, int y,
			                int width, cups_ib_t *pixels);
extern unsigned		cupsImageGetWidth(cups_image_t *img);
extern unsigned		cupsImageGetXPPI(cups_image_t *img);
extern unsigned		cupsImageGetYPPI(cups_image_t *img);
extern void		cupsImageLut(cups_ib_t *pixels, int count,
			             const cups_ib_t *lut);
extern cups_image_t	*cupsImageOpen(const char *filename,
			               cups_icspace_t primary,
				       cups_icspace_t secondary,
			               int saturation, int hue,
				       const cups_ib_t *lut);
extern void		cupsImageRGBAdjust(cups_ib_t *pixels, int count,
			                   int saturation, int hue);
extern void		cupsImageRGBToBlack(const cups_ib_t *in,
			                    cups_ib_t *out, int count);
extern void		cupsImageRGBToCMY(const cups_ib_t *in,
			                  cups_ib_t *out, int count);
extern void		cupsImageRGBToCMYK(const cups_ib_t *in,
			                   cups_ib_t *out, int count);
extern void		cupsImageRGBToRGB(const cups_ib_t *in,
			                  cups_ib_t *out, int count);
extern void		cupsImageRGBToWhite(const cups_ib_t *in,
			                    cups_ib_t *out, int count);
extern void		cupsImageSetMaxTiles(cups_image_t *img, int max_tiles);
extern void		cupsImageSetProfile(float d, float g,
			                    float matrix[3][3]);
extern void		cupsImageSetRasterColorSpace(cups_cspace_t cs);
extern void		cupsImageWhiteToBlack(const cups_ib_t *in,
			                      cups_ib_t *out, int count);
extern void		cupsImageWhiteToCMY(const cups_ib_t *in,
			                    cups_ib_t *out, int count);
extern void		cupsImageWhiteToCMYK(const cups_ib_t *in,
			                     cups_ib_t *out, int count);
extern void		cupsImageWhiteToRGB(const cups_ib_t *in,
			                    cups_ib_t *out, int count);
extern void		cupsImageWhiteToWhite(const cups_ib_t *in,
			                      cups_ib_t *out, int count);


#  ifdef __cplusplus
}
#  endif /* __cplusplus */

#endif /* !_CUPS_IMAGE_H_ */

/*
 * End of "$Id: image.h 6649 2007-07-11 21:46:42Z mike $".
 */
