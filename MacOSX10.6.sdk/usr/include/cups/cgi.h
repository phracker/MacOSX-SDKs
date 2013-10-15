/*
 * "$Id: cgi.h 6649 2007-07-11 21:46:42Z mike $"
 *
 *   CGI support library definitions for CUPS.
 *
 *   Copyright 2007-2010 by Apple Inc.
 *   Copyright 1997-2006 by Easy Software Products.
 *
 *   These coded instructions, statements, and computer programs are the
 *   property of Apple Inc. and are protected by Federal copyright
 *   law.  Distribution and use rights are outlined in the file "LICENSE.txt"
 *   which should have been included with this file.  If this file is
 *   file is missing or damaged, see the license at "http://www.cups.org/".
 */

#ifndef _CUPS_CGI_H_
#  define _CUPS_CGI_H_

#  include <stdio.h>
#  include <stdlib.h>
#  include <time.h>
#  include <sys/stat.h>

#  ifdef WIN32
#    include <direct.h>
#    include <io.h>
#  else
#    include <unistd.h>
#  endif /* WIN32 */

#  include <cups/cups.h>
#  include <cups/array.h>
#  include "help-index.h"


/*
 * C++ magic...
 */

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */

/*
 * Types...
 */

typedef struct cgi_file_s		/**** Uploaded file data ****/
{
  char		tempfile[1024],		/* Temporary file containing data */
		*name,			/* Variable name */
		*filename,		/* Original filename */
		*mimetype;		/* MIME media type */
  size_t	filesize;		/* Size of uploaded file */
} cgi_file_t;


/*
 * Prototypes...
 */

extern void		cgiAbort(const char *title, const char *stylesheet,
			         const char *format, ...);
extern int		cgiCheckVariables(const char *names);
extern void		cgiClearVariables(void);
extern void		*cgiCompileSearch(const char *query);
extern void		cgiCopyTemplateFile(FILE *out, const char *tmpl);
extern void		cgiCopyTemplateLang(const char *tmpl);
extern int		cgiDoSearch(void *search, const char *text);
extern void		cgiEndHTML(void);
extern void		cgiEndMultipart(void);
extern char		*cgiFormEncode(char *dst, const char *src,
			               size_t dstsize);
extern void		cgiFreeSearch(void *search);
extern const char	*cgiGetArray(const char *name, int element);
extern void		cgiGetAttributes(ipp_t *request, const char *tmpl);
extern const char	*cgiGetCookie(const char *name);
extern const cgi_file_t	*cgiGetFile(void);
extern cups_array_t	*cgiGetIPPObjects(ipp_t *response, void *search);
extern int		cgiGetSize(const char *name);
extern char		*cgiGetTemplateDir(void);
extern const char	*cgiGetVariable(const char *name);
extern int		cgiInitialize(void);
extern int		cgiIsPOST(void);
extern void		cgiMoveJobs(http_t *http, const char *dest, int job_id);
extern void		cgiPrintCommand(http_t *http, const char *dest,
			                const char *command, const char *title);
extern void		cgiPrintTestPage(http_t *http, const char *dest);
extern char		*cgiRewriteURL(const char *uri, char *url, int urlsize,
			               const char *newresource);
extern void		cgiSetArray(const char *name, int element,
			            const char *value);
extern void		cgiSetCookie(const char *name, const char *value,
			             const char *path, const char *domain,
				     time_t expires, int secure);
extern ipp_attribute_t	*cgiSetIPPObjectVars(ipp_attribute_t *obj,
			                     const char *prefix, int element);
extern int		cgiSetIPPVars(ipp_t *response, const char *filter_name,
			              const char *filter_value,
			              const char *prefix, int parent_el);
extern void		cgiSetServerVersion(void);
extern void		cgiSetSize(const char *name, int size);
extern void		cgiSetVariable(const char *name, const char *value);
extern void		cgiShowIPPError(const char *message);
extern void		cgiShowJobs(http_t *http, const char *dest);
extern void		cgiStartHTML(const char *title);
extern void		cgiStartMultipart(void);
extern int		cgiSupportsMultipart(void);
extern const char	*cgiText(const char *message);

#  ifdef __cplusplus
}
#  endif /* __cplusplus */

#endif /* !_CUPS_CGI_H_ */

/*
 * End of "$Id: cgi.h 6649 2007-07-11 21:46:42Z mike $".
 */
