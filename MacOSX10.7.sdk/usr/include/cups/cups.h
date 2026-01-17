/*
 * "$Id: cups.h 8781 2009-08-28 17:34:54Z mike $"
 *
 *   API definitions for CUPS.
 *
 *   Copyright 2007-2011 by Apple Inc.
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
#    include <stddef.h>
/* Windows does not support the ssize_t type, so map it to off_t... */
typedef off_t ssize_t;			/* @private@ */
#  endif /* WIN32 && !__CUPS_SSIZE_T_DEFINED */

#  include "file.h"
#  include "ipp.h"
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

#  define CUPS_VERSION		1.0500
#  define CUPS_VERSION_MAJOR	1
#  define CUPS_VERSION_MINOR	5
#  define CUPS_VERSION_PATCH	0

#  define CUPS_BC_FD		3	/* Back-channel file descriptor for select/poll */
#  define CUPS_DATE_ANY		(time_t)-1
#  define CUPS_EXCLUDE_NONE	(const char *)0
#  define CUPS_FORMAT_AUTO	"application/octet-stream"
#  define CUPS_FORMAT_COMMAND	"application/vnd.cups-command"
#  define CUPS_FORMAT_PDF	"application/pdf"
#  define CUPS_FORMAT_POSTSCRIPT "application/postscript"
#  define CUPS_FORMAT_RAW	"application/vnd.cups-raw"
#  define CUPS_FORMAT_TEXT	"text/plain"
#  define CUPS_HTTP_DEFAULT	(http_t *)0
#  define CUPS_INCLUDE_ALL	(const char *)0
#  define CUPS_JOBID_ALL	-1
#  define CUPS_JOBID_CURRENT	0
#  define CUPS_LENGTH_VARIABLE	(ssize_t)0
#  define CUPS_TIMEOUT_DEFAULT	0
#  define CUPS_WHICHJOBS_ALL	-1
#  define CUPS_WHICHJOBS_ACTIVE	0
#  define CUPS_WHICHJOBS_COMPLETED 1


/*
 * Types and structures...
 */

typedef unsigned cups_ptype_t;		/**** Printer type/capability bits ****/
enum cups_ptype_e			/**** Printer type/capability bit constants ****/
{					/* Not a typedef'd enum so we can OR */
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
  CUPS_PRINTER_DELETE = 0x100000,	/* Delete printer @since CUPS 1.2/Mac OS X 10.5@ */
  CUPS_PRINTER_NOT_SHARED = 0x200000,	/* Printer is not shared @since CUPS 1.2/Mac OS X 10.5@ */
  CUPS_PRINTER_AUTHENTICATED = 0x400000,/* Printer requires authentication @since CUPS 1.2/Mac OS X 10.5@ */
  CUPS_PRINTER_COMMANDS = 0x800000,	/* Printer supports maintenance commands @since CUPS 1.2/Mac OS X 10.5@ */
  CUPS_PRINTER_DISCOVERED = 0x1000000,	/* Printer was automatically discovered and added @since CUPS 1.3/Mac OS X 10.5@ */
  CUPS_PRINTER_SCANNER = 0x2000000,	/* Scanner-only device @since CUPS 1.4/Mac OS X 10.6@ */
  CUPS_PRINTER_MFP = 0x4000000,		/* Printer with scanning capabilities @since CUPS 1.4/Mac OS X 10.6@ */
  CUPS_PRINTER_OPTIONS = 0x6fffc	/* ~(CLASS | REMOTE | IMPLICIT | DEFAULT | FAX | REJECTING | DELETE | NOT_SHARED | AUTHENTICATED | COMMANDS | DISCOVERED) @private@ */
};

typedef const char *(*cups_password_cb_t)(const char *prompt);
					/**** Password callback ****/

typedef const char *(*cups_password_cb2_t)(const char *prompt, http_t *http,
					   const char *method,
					   const char *resource,
					   void *user_data);
					/**** New password callback @since CUPS 1.4/Mac OS X 10.6@ ****/

typedef void (*cups_device_cb_t)(const char *device_class,
                                 const char *device_id, const char *device_info,
                                 const char *device_make_and_model,
                                 const char *device_uri,
				 const char *device_location, void *user_data);
					/**** Device callback @since CUPS 1.4/Mac OS X 10.6@ ****/

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

typedef int (*cups_client_cert_cb_t)(http_t *http, void *tls,
				     cups_array_t *distinguished_names,
				     void *user_data);
					/**** Client credentials callback @since CUPS 1.5/Mac OS X 10.7@ ****/

typedef int (*cups_server_cert_cb_t)(http_t *http, void *tls,
				     cups_array_t *certs, void *user_data);
					/**** Server credentials callback @since CUPS 1.5/Mac OS X 10.7@ ****/


/*
 * Functions...
 */

extern int		cupsCancelJob(const char *name, int job_id);
extern ipp_t		*cupsDoFileRequest(http_t *http, ipp_t *request,
			                   const char *resource,
					   const char *filename);
extern ipp_t		*cupsDoRequest(http_t *http, ipp_t *request,
			               const char *resource);
extern http_encryption_t cupsEncryption(void);
extern void		cupsFreeJobs(int num_jobs, cups_job_t *jobs);
extern int		cupsGetClasses(char ***classes) _CUPS_DEPRECATED;
extern const char	*cupsGetDefault(void);
extern int		cupsGetJobs(cups_job_t **jobs, const char *name,
			            int myjobs, int whichjobs);
extern const char	*cupsGetPPD(const char *name);
extern int		cupsGetPrinters(char ***printers) _CUPS_DEPRECATED;
extern ipp_status_t	cupsLastError(void);
extern int		cupsPrintFile(const char *name, const char *filename,
			              const char *title, int num_options,
				      cups_option_t *options);
extern int		cupsPrintFiles(const char *name, int num_files,
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
			                     const char *resource) _CUPS_API_1_1_20;
extern http_status_t	cupsGetFile(http_t *http, const char *resource,
			            const char *filename) _CUPS_API_1_1_20;
extern http_status_t	cupsGetFd(http_t *http, const char *resource, int fd);
extern http_status_t	cupsPutFile(http_t *http, const char *resource,
			            const char *filename) _CUPS_API_1_1_20;
extern http_status_t	cupsPutFd(http_t *http, const char *resource, int fd) _CUPS_API_1_1_20;

/**** New in CUPS 1.1.21 ****/
extern const char	*cupsGetDefault2(http_t *http) _CUPS_API_1_1_21;
extern int		cupsGetDests2(http_t *http, cups_dest_t **dests) _CUPS_API_1_1_21;
extern int		cupsGetJobs2(http_t *http, cups_job_t **jobs,
			             const char *name, int myjobs,
				     int whichjobs) _CUPS_API_1_1_21;
extern const char	*cupsGetPPD2(http_t *http, const char *name) _CUPS_API_1_1_21;
extern int		cupsPrintFile2(http_t *http, const char *name,
			               const char *filename,
				       const char *title, int num_options,
				       cups_option_t *options) _CUPS_API_1_1_21;
extern int		cupsPrintFiles2(http_t *http, const char *name,
			                int num_files, const char **files,
					const char *title, int num_options,
					cups_option_t *options) _CUPS_API_1_1_21;
extern int		cupsSetDests2(http_t *http, int num_dests,
			              cups_dest_t *dests) _CUPS_API_1_1_21;

/**** New in CUPS 1.2/Mac OS X 10.5 ****/
extern ssize_t		cupsBackChannelRead(char *buffer, size_t bytes,
			                    double timeout) _CUPS_API_1_2;
extern ssize_t		cupsBackChannelWrite(const char *buffer, size_t bytes,
			                     double timeout) _CUPS_API_1_2;
extern void		cupsEncodeOptions2(ipp_t *ipp, int num_options,
					   cups_option_t *options,
					   ipp_tag_t group_tag) _CUPS_API_1_2;
extern const char	*cupsLastErrorString(void) _CUPS_API_1_2;
extern char		*cupsNotifySubject(cups_lang_t *lang, ipp_t *event) _CUPS_API_1_2;
extern char		*cupsNotifyText(cups_lang_t *lang, ipp_t *event) _CUPS_API_1_2;
extern int		cupsRemoveOption(const char *name, int num_options,
			                 cups_option_t **options) _CUPS_API_1_2;
extern cups_file_t	*cupsTempFile2(char *filename, int len) _CUPS_API_1_2;

/**** New in CUPS 1.3/Mac OS X 10.5 ****/
extern ipp_t		*cupsDoIORequest(http_t *http, ipp_t *request,
			                 const char *resource, int infile,
					 int outfile) _CUPS_API_1_3;
extern char		*cupsGetServerPPD(http_t *http, const char *name) _CUPS_API_1_3;
extern int		cupsRemoveDest(const char *name,
			               const char *instance,
				       int num_dests, cups_dest_t **dests) _CUPS_API_1_3;
extern void		cupsSetDefaultDest(const char *name,
			                   const char *instance,
					   int num_dests,
					   cups_dest_t *dests) _CUPS_API_1_3;

/**** New in CUPS 1.4/Mac OS X 10.6 ****/
extern ipp_status_t	cupsCancelJob2(http_t *http, const char *name,
			               int job_id, int purge) _CUPS_API_1_4;
extern int		cupsCreateJob(http_t *http, const char *name,
				      const char *title, int num_options,
				      cups_option_t *options) _CUPS_API_1_4;
extern ipp_status_t	cupsFinishDocument(http_t *http,
			                   const char *name) _CUPS_API_1_4;
extern ipp_status_t	cupsGetDevices(http_t *http, int timeout,
			               const char *include_schemes,
			               const char *exclude_schemes,
				       cups_device_cb_t callback,
				       void *user_data) _CUPS_API_1_4;
extern cups_dest_t	*cupsGetNamedDest(http_t *http, const char *name,
			                  const char *instance) _CUPS_API_1_4;
extern const char	*cupsGetPassword2(const char *prompt, http_t *http,
					  const char *method,
					  const char *resource) _CUPS_API_1_4;
extern http_status_t	cupsGetPPD3(http_t *http, const char *name,
			            time_t *modtime, char *buffer,
				    size_t bufsize) _CUPS_API_1_4;
extern ipp_t		*cupsGetResponse(http_t *http,
			                 const char *resource) _CUPS_API_1_4;
extern ssize_t		cupsReadResponseData(http_t *http, char *buffer,
			                     size_t length) _CUPS_API_1_4;
extern http_status_t	cupsSendRequest(http_t *http, ipp_t *request,
			                const char *resource,
					size_t length) _CUPS_API_1_4;
extern void		cupsSetPasswordCB2(cups_password_cb2_t cb,
			                   void *user_data) _CUPS_API_1_4;
extern http_status_t	cupsStartDocument(http_t *http, const char *name,
			                  int job_id, const char *docname,
					  const char *format,
					  int last_document) _CUPS_API_1_4;
extern http_status_t	cupsWriteRequestData(http_t *http, const char *buffer,
			                     size_t length) _CUPS_API_1_4;

/**** New in CUPS 1.5 ****/
extern void		cupsSetClientCertCB(cups_client_cert_cb_t cb,
					    void *user_data) _CUPS_API_1_5;
extern int		cupsSetCredentials(cups_array_t *certs) _CUPS_API_1_5;
extern void		cupsSetServerCertCB(cups_server_cert_cb_t cb,
					    void *user_data) _CUPS_API_1_5;


#  ifdef __cplusplus
}
#  endif /* __cplusplus */

#endif /* !_CUPS_CUPS_H_ */

/*
 * End of "$Id: cups.h 8781 2009-08-28 17:34:54Z mike $".
 */
