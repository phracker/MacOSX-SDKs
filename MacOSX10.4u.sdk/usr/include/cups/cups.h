/*
 * "$Id: cups.h,v 1.4 2005/01/04 22:10:38 jlovell Exp $"
 *
 *   API definitions for the Common UNIX Printing System (CUPS).
 *
 *   Copyright 1997-2005 by Easy Software Products.
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

#ifndef _CUPS_CUPS_H_
#  define _CUPS_CUPS_H_

/*
 * Include necessary headers...
 */

#  include "ipp.h"
#  include "ppd.h"


/*
 * C++ magic...
 */

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */


/*
 * Constants...
 */

#  define CUPS_VERSION		1.0123
#  define CUPS_VERSION_MAJOR	1
#  define CUPS_VERSION_MINOR	1
#  define CUPS_VERSION_PATCH	23
#  define CUPS_DATE_ANY		-1


/*
 * Types and structures...
 */

typedef unsigned cups_ptype_t;		/**** Printer Type/Capability Bits ****/
enum					/* Not a typedef'd enum so we can OR */
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
  CUPS_PRINTER_DELETE = 0x100000,	/* Delete printer */
  CUPS_PRINTER_OPTIONS = 0x6fffc	/* ~(CLASS | REMOTE | IMPLICIT) */
};

typedef struct				/**** Printer Options ****/
{
  char		*name;			/* Name of option */
  char		*value;			/* Value of option */
} cups_option_t;

typedef struct				/**** Destination ****/
{
  char		*name,			/* Printer or class name */
		*instance;		/* Local instance name or NULL */
  int		is_default;		/* Is this printer the default? */
  int		num_options;		/* Number of options */
  cups_option_t	*options;		/* Options */
} cups_dest_t;

typedef struct				/**** Job ****/
{
  int		id;			/* The job ID */
  char		*dest,			/* Printer or class name */
		*title,			/* Title/job name */
		*user,			/* User the submitted the job */
		*format;		/* Document format */
  ipp_jstate_t	state;			/* Job state */
  int		size,			/* Size in kilobytes */
		priority;		/* Priority (1-100) */
  time_t	completed_time,		/* Time the job was completed */
		creation_time,		/* Time the job was created */
		processing_time;	/* Time the job was processed */
} cups_job_t;


/*
 * Functions...
 */

extern int		cupsCancelJob(const char *printer, int job);
#define			cupsDoRequest(http,request,resource) cupsDoFileRequest((http),(request),(resource),NULL)
extern ipp_t		*cupsDoFileRequest(http_t *http, ipp_t *request,
			                   const char *resource, const char *filename);
extern http_encryption_t cupsEncryption(void);
extern void		cupsFreeJobs(int num_jobs, cups_job_t *jobs);
extern int		cupsGetClasses(char ***classes);
extern const char	*cupsGetDefault(void);
extern int		cupsGetJobs(cups_job_t **jobs, const char *dest,
			            int myjobs, int completed);
extern const char	*cupsGetPPD(const char *printer);
extern int		cupsGetPrinters(char ***printers);
extern ipp_status_t	cupsLastError(void);
extern int		cupsPrintFile(const char *printer, const char *filename,
			              const char *title, int num_options,
				      cups_option_t *options);
extern int		cupsPrintFiles(const char *printer, int num_files,
			               const char **files, const char *title,
				       int num_options, cups_option_t *options);
extern char		*cupsTempFile(char *filename, int len);
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
extern int		cupsParseOptions(const char *arg, int num_options,
			                 cups_option_t **options);
extern int		cupsMarkOptions(ppd_file_t *ppd, int num_options,
			                cups_option_t *options);

extern const char	*cupsGetPassword(const char *prompt);
extern const char	*cupsServer(void);
extern void		cupsSetEncryption(http_encryption_t e);
extern void		cupsSetPasswordCB(const char *(*cb)(const char *));
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


#  ifdef __cplusplus
}
#  endif /* __cplusplus */

#endif /* !_CUPS_CUPS_H_ */

/*
 * End of "$Id: cups.h,v 1.4 2005/01/04 22:10:38 jlovell Exp $".
 */
