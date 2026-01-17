/*
 * "$Id: adminutil.h 7026 2007-10-19 00:57:45Z mike $"
 *
 *   Administration utility API definitions for CUPS.
 *
 *   Copyright 2007-2010 by Apple Inc.
 *   Copyright 2001-2007 by Easy Software Products.
 *
 *   These coded instructions, statements, and computer programs are the
 *   property of Apple Inc. and are protected by Federal copyright
 *   law.  Distribution and use rights are outlined in the file "LICENSE.txt"
 *   which should have been included with this file.  If this file is
 *   file is missing or damaged, see the license at "http://www.cups.org/".
 *
 *   This file is subject to the Apple OS-Developed Software exception.
 */

#ifndef _CUPS_ADMINUTIL_H_
#  define _CUPS_ADMINUTIL_H_

/*
 * Include necessary headers...
 */

#  include "cups.h"


/*
 * C++ magic...
 */

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */


/*
 * Constants...
 */

#  define CUPS_SERVER_DEBUG_LOGGING	"_debug_logging"
#  define CUPS_SERVER_REMOTE_ADMIN	"_remote_admin"
#  define CUPS_SERVER_REMOTE_ANY	"_remote_any"
#  define CUPS_SERVER_REMOTE_PRINTERS	"_remote_printers"
#  define CUPS_SERVER_SHARE_PRINTERS	"_share_printers"
#  define CUPS_SERVER_USER_CANCEL_ANY	"_user_cancel_any"


/*
 * Functions...
 */

extern int	cupsAdminExportSamba(const char *dest, const char *ppd,
		                     const char *samba_server,
			             const char *samba_user,
				     const char *samba_password,
				     FILE *logfile) _CUPS_API_1_2;
extern char	*cupsAdminCreateWindowsPPD(http_t *http, const char *dest,
		                           char *buffer, int bufsize) _CUPS_API_1_2;

extern int	cupsAdminGetServerSettings(http_t *http,
			                   int *num_settings,
		                           cups_option_t **settings) _CUPS_API_1_3;
extern int	cupsAdminSetServerSettings(http_t *http,
		                           int num_settings,
		                           cups_option_t *settings) _CUPS_API_1_3;


#  ifdef __cplusplus
}
#  endif /* __cplusplus */

#endif /* !_CUPS_ADMINUTIL_H_ */

/*
 * End of "$Id: adminutil.h 7026 2007-10-19 00:57:45Z mike $".
 */
