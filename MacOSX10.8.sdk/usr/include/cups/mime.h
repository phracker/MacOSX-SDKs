/*
 * "$Id: mime.h 7694 2008-06-26 00:23:20Z mike $"
 *
 *   MIME type/conversion database definitions for CUPS.
 *
 *   Copyright 2007-2011 by Apple Inc.
 *   Copyright 1997-2007 by Easy Software Products, all rights reserved.
 *
 *   These coded instructions, statements, and computer programs are the
 *   property of Apple Inc. and are protected by Federal copyright
 *   law.  Distribution and use rights are outlined in the file "LICENSE.txt"
 *   which should have been included with this file.  If this file is
 *   file is missing or damaged, see the license at "http://www.cups.org/".
 */

#ifndef _CUPS_MIME_H_
#  define _CUPS_MIME_H_

#  include <cups/array.h>
#  include <cups/ipp.h>
#  include <cups/file.h>


/*
 * C++ magic...
 */

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */


/*
 * Constants...
 */

#  define MIME_MAX_SUPER	16		/* Maximum size of supertype name */
#  define MIME_MAX_TYPE		IPP_MAX_NAME	/* Maximum size of type name */
#  define MIME_MAX_FILTER	256		/* Maximum size of filter pathname */
#  define MIME_MAX_BUFFER	4096		/* Maximum size of file buffer */


/*
 * Types/structures...
 */

typedef enum
{
  MIME_MAGIC_NOP,			/* No operation */
  MIME_MAGIC_AND,			/* Logical AND of all children */
  MIME_MAGIC_OR,			/* Logical OR of all children */
  MIME_MAGIC_MATCH,			/* Filename match */
  MIME_MAGIC_ASCII,			/* ASCII characters in range */
  MIME_MAGIC_PRINTABLE,			/* Printable characters (32-255) in range */
  MIME_MAGIC_STRING,			/* String matches */
  MIME_MAGIC_CHAR,			/* Character/byte matches */
  MIME_MAGIC_SHORT,			/* Short/16-bit word matches */
  MIME_MAGIC_INT,			/* Integer/32-bit word matches */
  MIME_MAGIC_LOCALE,			/* Current locale matches string */
  MIME_MAGIC_CONTAINS,			/* File contains a string */
  MIME_MAGIC_ISTRING			/* Case-insensitive string matches */
} mime_op_t;

typedef struct _mime_magic_s		/**** MIME Magic Data ****/
{
  struct _mime_magic_s	*prev,		/* Previous rule */
			*next,		/* Next rule */
			*parent,	/* Parent rules */
			*child;		/* Child rules */
  short		op,			/* Operation code (see above) */
		invert;			/* Invert the result */
  int		offset,			/* Offset in file */
		region,			/* Region length */
		length;			/* Length of data */
  union
  {
    char	matchv[64];		/* Match value */
    char	localev[64];		/* Locale value */
    char	stringv[64];		/* String value */
    unsigned char charv;		/* Byte value */
    unsigned short shortv;		/* Short value */
    unsigned	intv;			/* Integer value */
  }		value;
} mime_magic_t;

typedef struct _mime_type_s		/**** MIME Type Data ****/
{
  mime_magic_t	*rules;			/* Rules used to detect this type */
  int		priority;		/* Priority of this type */
  char		super[MIME_MAX_SUPER],	/* Super-type name ("image", "application", etc.) */
		type[MIME_MAX_TYPE];	/* Type name ("png", "postscript", etc.) */
} mime_type_t;

typedef struct _mime_filter_s		/**** MIME Conversion Filter Data ****/
{
  mime_type_t	*src,			/* Source type */
		*dst;			/* Destination type */
  int		cost;			/* Relative cost */
  char		filter[MIME_MAX_FILTER];/* Filter program to use */
  size_t	maxsize;		/* Maximum file size for this filter */
} mime_filter_t;

typedef void (*mime_error_cb_t)(void *ctx, const char *message);

typedef struct _mime_s			/**** MIME Database ****/
{
  cups_array_t		*types;		/* File types */
  cups_array_t		*filters;	/* Type conversion filters */
  cups_array_t		*srcs;		/* Filters sorted by source type */
  mime_error_cb_t	error_cb;	/* Error message callback */
  void			*error_ctx;	/* Pointer for callback */
} mime_t;


/*
 * Functions...
 */

extern void		mimeDelete(mime_t *mime);
extern mime_t		*mimeNew(void) _CUPS_API_1_5;
extern mime_t		*mimeLoad(const char *pathname, const char *filterpath);
extern mime_t		*mimeLoadFilters(mime_t *mime, const char *pathname,
			                 const char *filterpath);
extern mime_t		*mimeLoadTypes(mime_t *mime, const char *pathname);

extern mime_type_t	*mimeAddType(mime_t *mime, const char *super,
			             const char *type);
extern int		mimeAddTypeRule(mime_type_t *mt, const char *rule);
extern void		mimeDeleteType(mime_t *mime, mime_type_t *mt);
extern mime_type_t	*mimeFileType(mime_t *mime, const char *pathname,
			              const char *filename, int *compression);
extern mime_type_t	*mimeFirstType(mime_t *mime);
extern mime_type_t	*mimeNextType(mime_t *mime);
extern int		mimeNumTypes(mime_t *mime);
extern mime_type_t	*mimeType(mime_t *mime, const char *super,
				  const char *type);

extern mime_filter_t	*mimeAddFilter(mime_t *mime, mime_type_t *src,
			               mime_type_t *dst, int cost,
				       const char *filter);
extern void		mimeDeleteFilter(mime_t *mime, mime_filter_t *filter);
extern cups_array_t	*mimeFilter(mime_t *mime, mime_type_t *src,
			            mime_type_t *dst, int *cost);
extern cups_array_t	*mimeFilter2(mime_t *mime, mime_type_t *src,
			             size_t srcsize, mime_type_t *dst,
				     int *cost);
extern mime_filter_t	*mimeFilterLookup(mime_t *mime, mime_type_t *src,
			                  mime_type_t *dst);
extern mime_filter_t	*mimeFirstFilter(mime_t *mime);
extern mime_filter_t	*mimeNextFilter(mime_t *mime);
extern int		mimeNumFilters(mime_t *mime);
extern void		mimeSetErrorCallback(mime_t *mime, mime_error_cb_t cb,
			                     void *context) _CUPS_API_1_5;

#  ifdef __cplusplus
}
#  endif /* __cplusplus */
#endif /* !_CUPS_MIME_H_ */

/*
 * End of "$Id: mime.h 7694 2008-06-26 00:23:20Z mike $".
 */
