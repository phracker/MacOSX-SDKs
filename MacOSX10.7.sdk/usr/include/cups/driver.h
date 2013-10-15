/*
 * "$Id: driver.h 626 2008-02-16 00:30:16Z msweet $"
 *
 *   Printer driver utilities header file for CUPS.
 *
 *   Copyright 2007 by Apple Inc.
 *   Copyright 1993-2005 by Easy Software Products.
 *
 *   These coded instructions, statements, and computer programs are the
 *   property of Apple Inc. and are protected by Federal copyright
 *   law.  Distribution and use rights are outlined in the file "LICENSE.txt"
 *   which should have been included with this file.  If this file is
 *   file is missing or damaged, see the license at "http://www.cups.org/".
 */

#ifndef _CUPS_DRIVER_H_
#  define _CUPS_DRIVER_H_

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */

/*
 * Include necessary headers...
 */

#  include <stdio.h>
#  include <stdlib.h>
#  include <time.h>
#  include <math.h>

#  if defined(WIN32) || defined(__EMX__)
#    include <io.h>
#  else
#    include <unistd.h>
#    include <fcntl.h>
#  endif /* WIN32 || __EMX__ */

#  include <cups/cups.h>
#  include <cups/raster.h>


/*
 * Common macros...
 */

#  ifndef min
#    define min(a,b)	((a) < (b) ? (a) : (b))
#    define max(a,b)	((a) > (b) ? (a) : (b))
#  endif /* !min */


/*
 * Constants...
 */

#define CUPS_MAX_CHAN	15		/* Maximum number of color components */
#define CUPS_MAX_LUT	4095		/* Maximum LUT value */
#define CUPS_MAX_RGB	4		/* Maximum number of sRGB components */


/*
 * Types/structures for the various routines.
 */

typedef struct cups_lut_s		/**** Lookup Table for Dithering ****/
{
  short		intensity;		/* Adjusted intensity */
  short		pixel;			/* Output pixel value */
  int		error;			/* Error from desired value */
} cups_lut_t;

typedef struct cups_dither_s		/**** Dithering State ****/
{
  int		width;			/* Width of buffer */
  int		row;			/* Current row */
  int		errors[96];		/* Error values */
} cups_dither_t;

typedef struct cups_sample_s		/**** Color sample point ****/
{
  unsigned char	rgb[3];			/* sRGB values */
  unsigned char	colors[CUPS_MAX_RGB];	/* Color values */
} cups_sample_t;

typedef struct cups_rgb_s		/**** Color separation lookup table ****/
{
  int		cube_size;		/* Size of color cube (2-N) on a side */
  int		num_channels;		/* Number of colors per sample */
  unsigned char	****colors;		/* 4-D array of sample values */
  int		cube_index[256];	/* Index into cube for a given sRGB value */
  int		cube_mult[256];		/* Multiplier value for a given sRGB value */
  int		cache_init;		/* Are cached values initialized? */
  unsigned char	black[CUPS_MAX_RGB];	/* Cached black (sRGB = 0,0,0) */
  unsigned char	white[CUPS_MAX_RGB];	/* Cached white (sRGB = 255,255,255) */
} cups_rgb_t;

typedef struct cups_cmyk_s		/**** Simple CMYK lookup table ****/
{
  unsigned char	black_lut[256];		/* Black generation LUT */
  unsigned char	color_lut[256];		/* Color removal LUT */
  int		ink_limit;		/* Ink limit */
  int		num_channels;		/* Number of components */
  short		*channels[CUPS_MAX_CHAN];
					/* Lookup tables */
} cups_cmyk_t;


/*
 * Globals...
 */

extern const unsigned char
			cups_srgb_lut[256];
					/* sRGB gamma lookup table */
extern const unsigned char
			cups_scmy_lut[256];
					/* sRGB gamma lookup table (inverted) */


/*
 * Prototypes...
 */

/*
 * Attribute function...
 */

extern ppd_attr_t	*cupsFindAttr(ppd_file_t *ppd, const char *name,
			              const char *colormodel,
			              const char *media,
				      const char *resolution,
				      char *spec, int specsize);
			       
/*
 * Byte checking functions...
 */

extern int		cupsCheckBytes(const unsigned char *, int);
extern int		cupsCheckValue(const unsigned char *, int,
			               const unsigned char);

/*
 * Dithering functions...
 */

extern void		cupsDitherLine(cups_dither_t *d, const cups_lut_t *lut,
			               const short *data, int num_channels,
				       unsigned char *p);
extern cups_dither_t	*cupsDitherNew(int width);
extern void		cupsDitherDelete(cups_dither_t *);

/*
 * Lookup table functions for dithering...
 */

extern cups_lut_t	*cupsLutNew(int num_vals, const float *vals);
extern void		cupsLutDelete(cups_lut_t *lut);
extern cups_lut_t	*cupsLutLoad(ppd_file_t *ppd,
			             const char *colormodel,
				     const char *media,
			             const char *resolution,
				     const char *ink);


/*
 * Bit packing functions...
 */

extern void		cupsPackHorizontal(const unsigned char *,
			                   unsigned char *, int,
					   const unsigned char, const int);
extern void		cupsPackHorizontal2(const unsigned char *,
			                    unsigned char *, int, const int);
extern void		cupsPackHorizontalBit(const unsigned char *,
			                      unsigned char *, int,
					      const unsigned char,
					      const unsigned char);
extern void		cupsPackVertical(const unsigned char *, unsigned char *,
			                 int, const unsigned char, const int);

/*
 * Color separation functions...
 */

extern void		cupsRGBDelete(cups_rgb_t *rgb);
extern void		cupsRGBDoGray(cups_rgb_t *rgb,
			              const unsigned char *input,
			              unsigned char *output, int num_pixels);
extern void		cupsRGBDoRGB(cups_rgb_t *rgb,
			             const unsigned char *input,
			             unsigned char *output, int num_pixels);
extern cups_rgb_t	*cupsRGBLoad(ppd_file_t *ppd,
			             const char *colormodel,
				     const char *media,
			             const char *resolution);
extern cups_rgb_t	*cupsRGBNew(int num_samples, cups_sample_t *samples,
			            int cube_size, int num_channels);

/*
 * CMYK separation functions...
 */

extern cups_cmyk_t	*cupsCMYKNew(int num_channels);
extern void		cupsCMYKDelete(cups_cmyk_t *cmyk);
extern void		cupsCMYKDoBlack(const cups_cmyk_t *cmyk,
			                const unsigned char *input,
			                short *output, int num_pixels);
extern void		cupsCMYKDoCMYK(const cups_cmyk_t *cmyk,
			               const unsigned char *input,
			               short *output, int num_pixels);
extern void		cupsCMYKDoGray(const cups_cmyk_t *cmyk,
			               const unsigned char *input,
			               short *output, int num_pixels);
extern void		cupsCMYKDoRGB(const cups_cmyk_t *cmyk,
			              const unsigned char *input,
			              short *output, int num_pixels);
extern cups_cmyk_t	*cupsCMYKLoad(ppd_file_t *ppd,
			              const char *colormodel,
				      const char *media,
			              const char *resolution);
extern void		cupsCMYKSetBlack(cups_cmyk_t *cmyk,
			                 float lower, float upper);
extern void		cupsCMYKSetCurve(cups_cmyk_t *cmyk, int channel,
			                 int num_xypoints,
					 const float *xypoints);
extern void		cupsCMYKSetGamma(cups_cmyk_t *cmyk, int channel,
			                 float gamval, float density);
extern void		cupsCMYKSetInkLimit(cups_cmyk_t *cmyk, float limit);
extern void		cupsCMYKSetLtDk(cups_cmyk_t *cmyk, int channel,
			                float light, float dark);


/*
 * Convenience macro for writing print data...
 */

#  define cupsWritePrintData(s,n) fwrite((s), 1, (n), stdout)

#  ifdef __cplusplus
}
#  endif /* __cplusplus */

#endif /* !_CUPS_DRIVER_H_ */

/*
 * End of "$Id: driver.h 626 2008-02-16 00:30:16Z msweet $".
 */

