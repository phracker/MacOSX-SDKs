/*
 * "$Id: cups.h 6981 2007-09-19 21:51:55Z mike $"
 *
 *   API definitions for the Common UNIX Printing System (CUPS).
 *
 *   Copyright 2007 by Apple Inc.
 *   Copyright 1997-2007 by Easy Software Products.
 *
 *   These coded instructions, statements, and computer programs are the
 *   property of Apple Inc. and are protected by Federal copyright
 *   law.  Distribution and use rights are outlined in the file "LICENSE.txt"
 *   which should have been included with this file.  If this file is
 *   file is missing or damaged, see the license at "http://www.cups.org/".
 *
 *   This file is subject to the Apple OS-Developed Software exception.
 */

#ifndef _CUPS_CUPS_H_
#  define _CUPS_CUPS_H_

/*
 * Include necessary headers...
 */

#  include <sys/types.h>
#  if defined(WIN32) && !defined(__CUPS_SSIZE_T_DEFINED)
#    define __CUPS_SSIZE_T_DEFINED
/* Windows does not support the ssize_t type, so map it to off_t... */
typedef off_t ssize_t;			/* @private@ */
#  endif /* WIN32 && !__CUPS_SSIZE_T_DEFINED */

#  include "ipp.h"
#  include "ppd.h"
#  include "language.h"


/*
 * With GCC 3.0 and higher, we can mark old APIs "deprecated" so you get
 * a warning at compile-time.
 */

#  if defined(__GNUC__) && __GNUC__ > 2
#    define _CUPS_DEPRECATED __attribute__ ((__deprecated__))
#  else
#    define _CUPS_DEPRECATED
#  endif /* __GNUC__ && __GNUC__ > 2 */


/*
 * C++ magic...
 */

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */


/*
 * Constants...
 */

#  define CUPS_VERSION		1.0303
#  define CUPS_VERSION_MAJOR	1
#  define CUPS_VERSION_MINOR	3
#  define CUPS_VERSION_PATCH	3
#  define CUPS_DATE_ANY		-1


/*
 * Types and structures...
 */

typedef unsigned cups_ptype_t;		/**** Printer Type/Capability Bits ****/
enum cups_ptype_e			/* Not a typedef'd enum so we can OR */
{
  CUPS_PRINTER_LOCAL = 0x0000,		/* Local printer or class */
  CUPS_PRINTER_CLASS = 0x0001,		/* Printer class */
  CUPS_PRINTER_REMOTE = 0x0002,		/* Remote printer or class */
  CUPS_PRINTER_BW = 0x0004,		/* Can do B&W printing */
  CUPS_PRINTER_COLOR = 0x0008,		/* Can do color printing */
  CUPS_PRINTER_DUPLEX = 0x0010,		/* Can do duplexing */
  CUPS_PRINTER_STAPLE = 0x0020,		/* Can staple output */
  CUPS_PRINTER_COPIES = 0x0040,		/* Can do copies */
  CUPS_PRINTER_COLLATE = 0x0080,	/* Can collage copies */
  CUPS_PRINTER_PUNCH = 0x0100,		/* Can punch output */
  CUPS_PRINTER_COVER = 0x0200,		/* Can cover output */
  CUPS_PRINTER_BIND = 0x0400,		/* Can bind output */
  CUPS_PRINTER_SORT = 0x0800,		/* Can sort output */
  CUPS_PRINTER_SMALL = 0x1000,		/* Can do Letter/Legal/A4 */
  CUPS_PRINTER_MEDIUM = 0x2000,		/* Can do Tabloid/B/C/A3/A2 */
  CUPS_PRINTER_LARGE = 0x4000,		/* Can do D/E/A1/A0 */
  CUPS_PRINTER_VARIABLE = 0x8000,	/* Can do variable sizes */
  CUPS_PRINTER_IMPLICIT = 0x10000,	/* Implicit class */
  CUPS_PRINTER_DEFAULT = 0x20000,	/* Default printer on network */
  CUPS_PRINTER_FAX = 0x40000,		/* Fax queue */
  CUPS_PRINTER_REJECTING = 0x80000,	/* Printer is rejecting jobs */
  CUPS_PRINTER_DELETE = 0x100000,	/* Delete printer @since CUPS 1.2@ */
  CUPS_PRINTER_NOT_SHARED = 0x200000,	/* Printer is not shared @since CUPS 1.2@ */
  CUPS_PRINTER_AUTHENTICATED = 0x400000,/* Printer requires authentication @since CUPS 1.2@ */
  CUPS_PRINTER_COMMANDS = 0x800000,	/* Printer supports maintenance commands @since CUPS 1.2@ */
  CUPS_PRINTER_DISCOVERED = 0x1000000,	/* Printer was automatically discovered and added @since CUPS 1.3@ */
  CUPS_PRINTER_OPTIONS = 0x6fffc	/* ~(CLASS | REMOTE | IMPLICIT | DEFAULT | FAX | REJECTING | DELETE | NOT_SHARED | AUTHENTICATED | COMMANDS | DISCOVERED) */
};

typedef const char *(*cups_password_cb_t)(const char *);
					/**** Password callback ****/

typedef struct cups_option_s		/**** Printer Options ****/
{
  char		*name;			/* Name of option */
  char		*value;			/* Value of option */
} cups_option_t;

typedef struct cups_dest_s		/**** Destination ****/
{
  char		*name,			/* Printer or class name */
		*instance;		/* Local instance name or NULL */
  int		is_default;		/* Is this printer the default? */
  int		num_options;		/* Number of options */
  cups_option_t	*options;		/* Options */
} cups_dest_t;

typedef struct cups_job_s		/**** Job ****/
{
  int		id;			/* The job ID */
  char		*dest;			/* Printer or class name */
  char		*title;			/* Title/job name */
  char		*user;			/* User the submitted the job */
  char		*format;		/* Document format */
  ipp_jstate_t	state;			/* Job state */
  int		size;			/* Size in kilobytes */
  int		priority;		/* Priority (1-100) */
  time_t	completed_time;		/* Time the job was completed */
  time_t	creation_time;		/* Time the job was created */
  time_t	processing_time;	/* Time the job was processed */
} cups_job_t;


/*
 * Functions...
 */

extern int		cupsCancelJob(const char *printer, int job);
extern ipp_t		*cupsDoFileRequest(http_t *http, ipp_t *request,
			                   const char *resource,
					   const char *filename);
extern ipp_t		*cupsDoRequest(http_t *http, ipp_t *request,
			               const char *resource);
extern http_encryption_t cupsEncryption(void);
extern void		cupsFreeJobs(int num_jobs, cups_job_t *jobs);
extern int		cupsGetClasses(char ***classes) _CUPS_DEPRECATED;
extern const char	*cupsGetDefault(void);
extern int		cupsGetJobs(cups_job_t **jobs, const char *dest,
			            int myjobs, int completed);
extern const char	*cupsGetPPD(const char *printer);
extern int		cupsGetPrinters(char ***printers) _CUPS_DEPRECATED;
extern ipp_status_t	cupsLastError(void);
extern int		cupsPrintFile(const char *printer, const char *filename,
			              const char *title, int num_options,
				      cups_option_t *options);
extern int		cupsPrintFiles(const char *printer, int num_files,
			               const char **files, const char *title,
				       int num_options, cups_option_t *options);
extern char		*cupsTempFile(char *filename, int len) _CUPS_DEPRECATED;
extern int		cupsTempFd(char *filename, int len);

extern int		cupsAddDest(const char *name, const char *instance,
			            int num_dests, cups_dest_t **dests);
extern void		cupsFreeDests(int num_dests, cups_dest_t *dests);
extern cups_dest_t	*cupsGetDest(const char *name, const char *instance,
			             int num_dests, cups_dest_t *dests);
extern int		cupsGetDests(cups_dest_t **dests);
extern void		cupsSetDests(int num_dests, cups_dest_t *dests);

extern int		cupsAddOption(const char *name, const char *value,
			              int num_options, cups_option_t **options);
extern void		cupsEncodeOptions(ipp_t *ipp, int num_options,
					  cups_option_t *options);
extern void		cupsFreeOptions(int num_options, cups_option_t *options);
extern const char	*cupsGetOption(const char *name, int num_options,
			               cups_option_t *options);
extern int		cupsMarkOptions(ppd_file_t *ppd, int num_options,
			                cups_option_t *options);
extern int		cupsParseOptions(const char *arg, int num_options,
			                 cups_option_t **options);

extern const char	*cupsGetPassword(const char *prompt);
extern const char	*cupsServer(void);
extern void		cupsSetEncryption(http_encryption_t e);
extern void		cupsSetPasswordCB(cups_password_cb_t cb);
extern void		cupsSetServer(const char *server);
extern void		cupsSetUser(const char *user);
extern const char	*cupsUser(void);

/**** New in CUPS 1.1.20 ****/
extern int		cupsDoAuthentication(http_t *http, const char *method,
			                     const char *resource);
extern http_status_t	cupsGetFile(http_t *http, const char *resource,
			            const char *filename);
extern http_status_t	cupsGetFd(http_t *http, const char *resource, int fd);
extern http_status_t	cupsPutFile(http_t *http, const char *resource,
			            const char *filename);
extern http_status_t	cupsPutFd(http_t *http, const char *resource, int fd);

/**** New in CUPS 1.1.21 ****/
extern const char	*cupsGetDefault2(http_t *http);
extern int		cupsGetDests2(http_t *http, cups_dest_t **dests);
extern int		cupsGetJobs2(http_t *http, cups_job_t **jobs,
			             const char *dest, int myjobs,
				     int completed);
extern const char	*cupsGetPPD2(http_t *http, const char *printer);
extern int		cupsPrintFile2(http_t *http, const char *printer,
			               const char *filename,
				       const char *title, int num_options,
				       cups_option_t *options);
extern int		cupsPrintFiles2(http_t *http, const char *printer,
			                int num_files, const char **files,
					const char *title, int num_options,
					cups_option_t *options);
extern int		cupsSetDests2(http_t *http, int num_dests,
			              cups_dest_t *dests);

/**** New in CUPS 1.2 ****/
extern ssize_t		cupsBackChannelRead(char *buffer, size_t bytes,
			                    double timeout);
extern ssize_t		cupsBackChannelWrite(const char *buffer, size_t bytes,
			                     double timeout);
extern void		cupsEncodeOptions2(ipp_t *ipp, int num_options,
					   cups_option_t *options,
					   ipp_tag_t group_tag);
extern const char	*cupsLastErrorString(void);
extern char		*cupsNotifySubject(cups_lang_t *lang, ipp_t *event);
extern char		*cupsNotifyText(cups_lang_t *lang, ipp_t *event);
extern int		cupsRemoveOption(const char *name, int num_options,
			                 cups_option_t **options);
extern cups_file_t	*cupsTempFile2(char *filename, int len);

/**** New in CUPS 1.3 ****/
extern ipp_t		*cupsDoIORequest(http_t *http, ipp_t *request,
			                 const char *resource, int infile,
					 int outfile);
extern char		*cupsGetServerPPD(http_t *http, const char *name);
extern int		cupsRemoveDest(const char *name,
			               const char *instance,
				       int num_dests, cups_dest_t **dests);
extern void		cupsSetDefaultDest(const char *name,
			                   const char *instance,
					   int num_dests,
					   cups_dest_t *dests);


#  ifdef __cplusplus
}
#  endif /* __cplusplus */

#endif /* !_CUPS_CUPS_H_ */

/*
 * End of "$Id: cups.h 6981 2007-09-19 21:51:55Z mike $".
 */
