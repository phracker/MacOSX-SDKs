/*
 * "$Id: i18n.h 6649 2007-07-11 21:46:42Z mike $"
 *
 *   (Private) localization support for the Common UNIX Printing System (CUPS).
 *
 *   Copyright 2007 by Apple Inc.
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

#ifndef _CUPS_I18N_H_
#  define _CUPS_I18N_H_

/*
 * Include necessary headers...
 */

#  include <stdio.h>
#  include "transcode.h"

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */


/*
 * Macro for localized text...
 */

#  define _(x) x


/*
 * Types...
 */

typedef struct _cups_message_s		/**** Message catalog entry ****/
{
  char	*id,				/* Original string */
	*str;				/* Localized string */
} _cups_message_t;

typedef struct _cups_cmap_s		/**** SBCS Charmap Struct ****/
{
  struct _cups_cmap_s	*next;		/* Next charmap in cache */
  int			used;		/* Number of times entry used */
  cups_encoding_t	encoding;	/* Legacy charset encoding */
  cups_ucs2_t		char2uni[256];	/* Map Legacy SBCS -> UCS-2 */
  cups_sbcs_t		*uni2char[256]; /* Map UCS-2 -> Legacy SBCS */
} _cups_cmap_t;

typedef struct _cups_wide2uni_s		/**** Wide to Unicode ****/
{
  cups_vbcs_t		widechar;	/* VBCS 32-bit Char (EUC) */
  cups_ucs2_t		unichar;	/* UCS-2 Char */
} _cups_wide2uni_t;

typedef struct _cups_vmap_s		/**** VBCS Charmap Struct ****/
{
  struct _cups_vmap_s	*next;		/* Next charmap in cache */
  int			used;		/* Number of times entry used */
  cups_encoding_t	encoding;	/* Legacy charset encoding */
  cups_ucs2_t		*char2uni[256]; /* Map 16-bit Char -> UCS-2 */
  int			charcount;	/* Count of 16-bit VBCS Chars */
  _cups_wide2uni_t	*wide2uni;	/* Map 32-bit Char -> UCS-2 */
  int			widecount;	/* Count of 32-bit VBCS Chars */
  cups_vbcs_t		*uni2char[256]; /* Map UCS-2 -> 32-bit VBCS */
  cups_sbcs_t		lead2char[256]; /* Legacy Lead Char - 2-byte */
  cups_sbcs_t		lead3char[256]; /* Legacy Lead Char - 3-byte */
  cups_sbcs_t		lead4char[256]; /* Legacy Lead Char - 4-byte */
} _cups_vmap_t;


/*
 * Prototypes...
 */

extern void		_cupsCharmapFlush(void);
extern void		_cupsCharmapFree(const cups_encoding_t encoding);
extern void		*_cupsCharmapGet(const cups_encoding_t encoding);
extern const char	*_cupsEncodingName(cups_encoding_t encoding);
extern int		_cupsLangPrintf(FILE *fp, const char *message, ...)
#    ifdef __GNUC__
__attribute__ ((__format__ (__printf__, 2, 3)))
#    endif /* __GNUC__ */
;
extern int		_cupsLangPuts(FILE *fp, const char *message);
extern const char	*_cupsLangString(cups_lang_t *lang, const char *message);
extern void		_cupsMessageFree(cups_array_t *a);
extern cups_array_t	*_cupsMessageLoad(const char *filename);
extern const char	*_cupsMessageLookup(cups_array_t *a, const char *m);
extern void		_cupsSetLocale(char *argv[]);

#  ifdef __cplusplus
}
#  endif /* __cplusplus */

#endif /* !_CUPS_I18N_H_ */

/*
 * End of "$Id: i18n.h 6649 2007-07-11 21:46:42Z mike $".
 */
