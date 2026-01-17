/*
 * "$Id: language.h 6649 2007-07-11 21:46:42Z mike $"
 *
 *   Multi-language support for the Common UNIX Printing System (CUPS).
 *
 *   Copyright 2007-2008 by Apple Inc.
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

#ifndef _CUPS_LANGUAGE_H_
#  define _CUPS_LANGUAGE_H_

/*
 * Include necessary headers...
 */

#  include <locale.h>
#  include "array.h"

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */


/*
 * Types...
 */

typedef enum cups_encoding_e		/**** Language Encodings ****/
{
  CUPS_AUTO_ENCODING = -1,		/* Auto-detect the encoding @private@ */
  CUPS_US_ASCII,			/* US ASCII */
  CUPS_ISO8859_1,			/* ISO-8859-1 */
  CUPS_ISO8859_2,			/* ISO-8859-2 */
  CUPS_ISO8859_3,			/* ISO-8859-3 */
  CUPS_ISO8859_4,			/* ISO-8859-4 */
  CUPS_ISO8859_5,			/* ISO-8859-5 */
  CUPS_ISO8859_6,			/* ISO-8859-6 */
  CUPS_ISO8859_7,			/* ISO-8859-7 */
  CUPS_ISO8859_8,			/* ISO-8859-8 */
  CUPS_ISO8859_9,			/* ISO-8859-9 */
  CUPS_ISO8859_10,			/* ISO-8859-10 */
  CUPS_UTF8,				/* UTF-8 */
  CUPS_ISO8859_13,			/* ISO-8859-13 */
  CUPS_ISO8859_14,			/* ISO-8859-14 */
  CUPS_ISO8859_15,			/* ISO-8859-15 */
  CUPS_WINDOWS_874,			/* CP-874 */
  CUPS_WINDOWS_1250,			/* CP-1250 */
  CUPS_WINDOWS_1251,			/* CP-1251 */
  CUPS_WINDOWS_1252,			/* CP-1252 */
  CUPS_WINDOWS_1253,			/* CP-1253 */
  CUPS_WINDOWS_1254,			/* CP-1254 */
  CUPS_WINDOWS_1255,			/* CP-1255 */
  CUPS_WINDOWS_1256,			/* CP-1256 */
  CUPS_WINDOWS_1257,			/* CP-1257 */
  CUPS_WINDOWS_1258,			/* CP-1258 */
  CUPS_KOI8_R,				/* KOI-8-R */
  CUPS_KOI8_U,				/* KOI-8-U */
  CUPS_ISO8859_11,			/* ISO-8859-11 */
  CUPS_ISO8859_16,			/* ISO-8859-16 */
  CUPS_MAC_ROMAN,			/* MacRoman */
  CUPS_ENCODING_SBCS_END = 63,		/* End of single-byte encodings @private@ */

  CUPS_WINDOWS_932,			/* Japanese JIS X0208-1990 */
  CUPS_WINDOWS_936,			/* Simplified Chinese GB 2312-80 */
  CUPS_WINDOWS_949,			/* Korean KS C5601-1992 */
  CUPS_WINDOWS_950,			/* Traditional Chinese Big Five */
  CUPS_WINDOWS_1361,			/* Korean Johab */
  CUPS_ENCODING_DBCS_END = 127,		/* End of double-byte encodings @private@ */

  CUPS_EUC_CN,				/* EUC Simplified Chinese */
  CUPS_EUC_JP,				/* EUC Japanese */
  CUPS_EUC_KR,				/* EUC Korean */
  CUPS_EUC_TW,				/* EUC Traditional Chinese */
  CUPS_JIS_X0213,			/* JIS X0213 aka Shift JIS */
  CUPS_ENCODING_VBCS_END = 191		/* End of variable-length encodings @private@ */
} cups_encoding_t;

typedef struct cups_lang_s		/**** Language Cache Structure ****/
{
  struct cups_lang_s	*next;		/* Next language in cache */
  int			used;		/* Number of times this entry has been used. */
  cups_encoding_t	encoding;	/* Text encoding */
  char			language[16];	/* Language/locale name */
  cups_array_t		*strings;	/* Message strings @private@ */
} cups_lang_t;


/*
 * Prototypes...
 */

extern cups_lang_t	*cupsLangDefault(void);
extern const char	*cupsLangEncoding(cups_lang_t *lang);
extern void		cupsLangFlush(void);
extern void		cupsLangFree(cups_lang_t *lang);
extern cups_lang_t	*cupsLangGet(const char *language);

#  ifdef __cplusplus
}
#  endif /* __cplusplus */

#endif /* !_CUPS_LANGUAGE_H_ */

/*
 * End of "$Id: language.h 6649 2007-07-11 21:46:42Z mike $".
 */
