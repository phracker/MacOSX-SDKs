/*
 * "$Id: transcode.h 7026 2007-10-19 00:57:45Z mike $"
 *
 *   Transcoding definitions for CUPS.
 *
 *   Copyright 2007-2011 by Apple Inc.
 *   Copyright 1997-2006 by Easy Software Products.
 *
 *   These coded instructions, statements, and computer programs are the
 *   property of Apple Inc. and are protected by Federal copyright
 *   law.  Distribution and use rights are outlined in the file "LICENSE.txt"
 *   which should have been included with this file.  If this file is
 *   file is missing or damaged, see the license at "http://www.cups.org/".
 *
 *   This file is subject to the Apple OS-Developed Software exception.
 */

#ifndef _CUPS_TRANSCODE_H_
#  define _CUPS_TRANSCODE_H_

/*
 * Include necessary headers...
 */

#  include "language.h"

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */


/*
 * Constants...
 */

#  define CUPS_MAX_USTRING	8192	/* Max size of Unicode string */


/*
 * Types...
 */

typedef unsigned char  cups_utf8_t;	/* UTF-8 Unicode/ISO-10646 unit */
typedef unsigned long  cups_utf32_t;	/* UTF-32 Unicode/ISO-10646 unit */
typedef unsigned short cups_ucs2_t;	/* UCS-2 Unicode/ISO-10646 unit */
typedef unsigned long  cups_ucs4_t;	/* UCS-4 Unicode/ISO-10646 unit */
typedef unsigned char  cups_sbcs_t;	/* SBCS Legacy 8-bit unit */
typedef unsigned short cups_dbcs_t;	/* DBCS Legacy 16-bit unit */
typedef unsigned long  cups_vbcs_t;	/* VBCS Legacy 32-bit unit */
					/* EUC uses 8, 16, 24, 32-bit */


/*
 * Prototypes...
 */

extern int	cupsCharsetToUTF8(cups_utf8_t *dest,
				  const char *src,
				  const int maxout,
				  const cups_encoding_t encoding) _CUPS_API_1_2;
extern int	cupsUTF8ToCharset(char *dest,
				  const cups_utf8_t *src,
				  const int maxout,
				  const cups_encoding_t encoding) _CUPS_API_1_2;
extern int	cupsUTF8ToUTF32(cups_utf32_t *dest,
				const cups_utf8_t *src,
				const int maxout) _CUPS_API_1_2;
extern int	cupsUTF32ToUTF8(cups_utf8_t *dest,
				const cups_utf32_t *src,
				const int maxout) _CUPS_API_1_2;

#  ifdef __cplusplus
}
#  endif /* __cplusplus */

#endif /* !_CUPS_TRANSCODE_H_ */


/*
 * End of "$Id: transcode.h 7026 2007-10-19 00:57:45Z mike $"
 */
