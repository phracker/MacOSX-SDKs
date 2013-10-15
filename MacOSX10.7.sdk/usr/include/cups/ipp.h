/*
 * "$Id: ipp.h 7847 2008-08-19 04:22:14Z mike $"
 *
 *   Internet Printing Protocol definitions for CUPS.
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

#ifndef _CUPS_IPP_H_
#  define _CUPS_IPP_H_

/*
 * Include necessary headers...
 */

#  include "http.h"


/*
 * C++ magic...
 */

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */


/*
 * IPP version string...
 */

#  define IPP_VERSION		"\002\001"

/*
 * IPP registered port number...
 *
 * Note: Applications should never use IPP_PORT, but instead use the
 * ippPort() function to allow overrides via the IPP_PORT environment
 * variable and services file if needed!
 */

#  define IPP_PORT		631

/*
 * Common limits...
 */

#  define IPP_MAX_LENGTH	32767	/* Maximum size of any single value */
#  define IPP_MAX_NAME		256	/* Maximum length of common name values */
#  define IPP_MAX_VALUES	8	/* Power-of-2 allocation increment */


/*
 * Types and structures...
 */

typedef enum ipp_tag_e			/**** Format tags for attributes ****/
{
  IPP_TAG_ZERO = 0x00,			/* Zero tag - used for separators */
  IPP_TAG_OPERATION,			/* Operation group */
  IPP_TAG_JOB,				/* Job group */
  IPP_TAG_END,				/* End-of-attributes */
  IPP_TAG_PRINTER,			/* Printer group */
  IPP_TAG_UNSUPPORTED_GROUP,		/* Unsupported attributes group */
  IPP_TAG_SUBSCRIPTION,			/* Subscription group */
  IPP_TAG_EVENT_NOTIFICATION,		/* Event group */
  IPP_TAG_UNSUPPORTED_VALUE = 0x10,	/* Unsupported value */
  IPP_TAG_DEFAULT,			/* Default value */
  IPP_TAG_UNKNOWN,			/* Unknown value */
  IPP_TAG_NOVALUE,			/* No-value value */
  IPP_TAG_NOTSETTABLE = 0x15,		/* Not-settable value */
  IPP_TAG_DELETEATTR,			/* Delete-attribute value */
  IPP_TAG_ADMINDEFINE,			/* Admin-defined value */
  IPP_TAG_INTEGER = 0x21,		/* Integer value */
  IPP_TAG_BOOLEAN,			/* Boolean value */
  IPP_TAG_ENUM,				/* Enumeration value */
  IPP_TAG_STRING = 0x30,		/* Octet string value */
  IPP_TAG_DATE,				/* Date/time value */
  IPP_TAG_RESOLUTION,			/* Resolution value */
  IPP_TAG_RANGE,			/* Range value */
  IPP_TAG_BEGIN_COLLECTION,		/* Beginning of collection value */
  IPP_TAG_TEXTLANG,			/* Text-with-language value */
  IPP_TAG_NAMELANG,			/* Name-with-language value */
  IPP_TAG_END_COLLECTION,		/* End of collection value */
  IPP_TAG_TEXT = 0x41,			/* Text value */
  IPP_TAG_NAME,				/* Name value */
  IPP_TAG_RESERVED_STRING,		/* Reserved for future string value @private@ */
  IPP_TAG_KEYWORD,			/* Keyword value */
  IPP_TAG_URI,				/* URI value */
  IPP_TAG_URISCHEME,			/* URI scheme value */
  IPP_TAG_CHARSET,			/* Character set value */
  IPP_TAG_LANGUAGE,			/* Language value */
  IPP_TAG_MIMETYPE,			/* MIME media type value */
  IPP_TAG_MEMBERNAME,			/* Collection member name value */
  IPP_TAG_MASK = 0x7fffffff,		/* Mask for copied attribute values */
  IPP_TAG_COPY = -0x7fffffff-1		/* Bitflag for copied attribute values */
} ipp_tag_t;

typedef enum ipp_res_e			/**** Resolution units ****/
{
  IPP_RES_PER_INCH = 3,			/* Pixels per inch */
  IPP_RES_PER_CM			/* Pixels per centimeter */
} ipp_res_t;

typedef enum ipp_finish_e		/**** Finishings ****/
{
  IPP_FINISHINGS_NONE = 3,		/* No finishing */
  IPP_FINISHINGS_STAPLE,		/* Staple (any location) */
  IPP_FINISHINGS_PUNCH,			/* Punch (any location/count) */
  IPP_FINISHINGS_COVER,			/* Add cover */
  IPP_FINISHINGS_BIND,			/* Bind */
  IPP_FINISHINGS_SADDLE_STITCH,		/* Staple interior */
  IPP_FINISHINGS_EDGE_STITCH,		/* Stitch along any side */
  IPP_FINISHINGS_FOLD,			/* Fold (any type) */
  IPP_FINISHINGS_TRIM,			/* Trim (any type) */
  IPP_FINISHINGS_BALE,			/* Bale (any type) */
  IPP_FINISHINGS_BOOKLET_MAKER,		/* Fold to make booklet */
  IPP_FINISHINGS_JOB_OFFSET,		/* Offset for binding (any type) */
  IPP_FINISHINGS_STAPLE_TOP_LEFT = 20,	/* Staple top left corner */
  IPP_FINISHINGS_STAPLE_BOTTOM_LEFT,	/* Staple bottom left corner */
  IPP_FINISHINGS_STAPLE_TOP_RIGHT,	/* Staple top right corner */
  IPP_FINISHINGS_STAPLE_BOTTOM_RIGHT,	/* Staple bottom right corner */
  IPP_FINISHINGS_EDGE_STITCH_LEFT,	/* Stitch along left side */
  IPP_FINISHINGS_EDGE_STITCH_TOP,	/* Stitch along top edge */
  IPP_FINISHINGS_EDGE_STITCH_RIGHT,	/* Stitch along right side */
  IPP_FINISHINGS_EDGE_STITCH_BOTTOM,	/* Stitch along bottom edge */
  IPP_FINISHINGS_STAPLE_DUAL_LEFT,	/* Two staples on left */
  IPP_FINISHINGS_STAPLE_DUAL_TOP,	/* Two staples on top */
  IPP_FINISHINGS_STAPLE_DUAL_RIGHT,	/* Two staples on right */
  IPP_FINISHINGS_STAPLE_DUAL_BOTTOM,	/* Two staples on bottom */
  IPP_FINISHINGS_BIND_LEFT = 50,	/* Bind on left */
  IPP_FINISHINGS_BIND_TOP,		/* Bind on top */
  IPP_FINISHINGS_BIND_RIGHT,		/* Bind on right */
  IPP_FINISHINGS_BIND_BOTTOM		/* Bind on bottom */
} ipp_finish_t;

typedef enum ipp_orient_e		/**** Orientation values ****/
{
  IPP_PORTRAIT = 3,			/* No rotation */
  IPP_LANDSCAPE,			/* 90 degrees counter-clockwise */
  IPP_REVERSE_LANDSCAPE,		/* 90 degrees clockwise */
  IPP_REVERSE_PORTRAIT			/* 180 degrees */
} ipp_orient_t;

typedef enum ipp_quality_e		/**** Qualities ****/
{
  IPP_QUALITY_DRAFT = 3,		/* Draft quality */
  IPP_QUALITY_NORMAL,			/* Normal quality */
  IPP_QUALITY_HIGH			/* High quality */
} ipp_quality_t;

typedef enum ipp_jstate_e		/**** Job states ****/
{
  IPP_JOB_PENDING = 3,			/* Job is waiting to be printed */
  IPP_JOB_HELD,				/* Job is held for printing */
  IPP_JOB_PROCESSING,			/* Job is currently printing */
  IPP_JOB_STOPPED,			/* Job has been stopped */
  IPP_JOB_CANCELED,			/* Job has been canceled */
  IPP_JOB_ABORTED,			/* Job has aborted due to error */
  IPP_JOB_COMPLETED			/* Job has completed successfully */
} ipp_jstate_t;
#define IPP_JOB_CANCELLED IPP_JOB_CANCELED

typedef enum ipp_pstate_e		/**** Printer states ****/
{
  IPP_PRINTER_IDLE = 3,			/* Printer is idle */
  IPP_PRINTER_PROCESSING,		/* Printer is working */
  IPP_PRINTER_STOPPED			/* Printer is stopped */
} ipp_pstate_t;

typedef enum ipp_state_e		/**** IPP states ****/
{
  IPP_ERROR = -1,			/* An error occurred */
  IPP_IDLE,				/* Nothing is happening/request completed */
  IPP_HEADER,				/* The request header needs to be sent/received */
  IPP_ATTRIBUTE,			/* One or more attributes need to be sent/received */
  IPP_DATA				/* IPP request data needs to be sent/received */
} ipp_state_t;

typedef enum ipp_op_e			/**** IPP operations ****/
{
  IPP_PRINT_JOB = 0x0002,		/* Print a single file */
  IPP_PRINT_URI,			/* Print a single URL @private@ */
  IPP_VALIDATE_JOB,			/* Validate job options */
  IPP_CREATE_JOB,			/* Create an empty print job */
  IPP_SEND_DOCUMENT,			/* Add a file to a job */
  IPP_SEND_URI,				/* Add a URL to a job @private@ */
  IPP_CANCEL_JOB,			/* Cancel a job */
  IPP_GET_JOB_ATTRIBUTES,		/* Get job attributes */
  IPP_GET_JOBS,				/* Get a list of jobs */
  IPP_GET_PRINTER_ATTRIBUTES,		/* Get printer attributes */
  IPP_HOLD_JOB,				/* Hold a job for printing */
  IPP_RELEASE_JOB,			/* Release a job for printing */
  IPP_RESTART_JOB,			/* Reprint a job */
  IPP_PAUSE_PRINTER = 0x0010,		/* Stop a printer */
  IPP_RESUME_PRINTER,			/* Start a printer */
  IPP_PURGE_JOBS,			/* Cancel all jobs */
  IPP_SET_PRINTER_ATTRIBUTES,		/* Set printer attributes @private@ */
  IPP_SET_JOB_ATTRIBUTES,		/* Set job attributes */
  IPP_GET_PRINTER_SUPPORTED_VALUES,	/* Get supported attribute values */
  IPP_CREATE_PRINTER_SUBSCRIPTION,	/* Create a printer subscription @since CUPS 1.2/Mac OS X 10.5@ */
  IPP_CREATE_JOB_SUBSCRIPTION,		/* Create a job subscription @since CUPS 1.2/Mac OS X 10.5@ */
  IPP_GET_SUBSCRIPTION_ATTRIBUTES,	/* Get subscription attributes @since CUPS 1.2/Mac OS X 10.5@ */
  IPP_GET_SUBSCRIPTIONS,		/* Get list of subscriptions @since CUPS 1.2/Mac OS X 10.5@ */
  IPP_RENEW_SUBSCRIPTION,		/* Renew a printer subscription @since CUPS 1.2/Mac OS X 10.5@ */
  IPP_CANCEL_SUBSCRIPTION,		/* Cancel a subscription @since CUPS 1.2/Mac OS X 10.5@ */
  IPP_GET_NOTIFICATIONS,		/* Get notification events @since CUPS 1.2/Mac OS X 10.5@ */
  IPP_SEND_NOTIFICATIONS,		/* Send notification events @private@ */
  IPP_GET_PRINT_SUPPORT_FILES = 0x0021,	/* Get printer support files @private@ */
  IPP_ENABLE_PRINTER,			/* Start a printer */
  IPP_DISABLE_PRINTER,			/* Stop a printer */
  IPP_PAUSE_PRINTER_AFTER_CURRENT_JOB,	/* Stop printer after the current job @private@ */
  IPP_HOLD_NEW_JOBS,			/* Hold new jobs @private@ */
  IPP_RELEASE_HELD_NEW_JOBS,		/* Release new jobs @private@ */
  IPP_DEACTIVATE_PRINTER,		/* Stop a printer @private@ */
  IPP_ACTIVATE_PRINTER,			/* Start a printer @private@ */
  IPP_RESTART_PRINTER,			/* Restart a printer @private@ */
  IPP_SHUTDOWN_PRINTER,			/* Turn a printer off @private@ */
  IPP_STARTUP_PRINTER,			/* Turn a printer on @private@ */
  IPP_REPROCESS_JOB,			/* Reprint a job @private@ */
  IPP_CANCEL_CURRENT_JOB,		/* Cancel the current job @private@ */
  IPP_SUSPEND_CURRENT_JOB,		/* Suspend the current job @private@ */
  IPP_RESUME_JOB,			/* Resume the current job @private@ */
  IPP_PROMOTE_JOB,			/* Promote a job to print sooner @private@ */
  IPP_SCHEDULE_JOB_AFTER,		/* Schedule a job to print after another @private@ */
  IPP_CANCEL_DOCUMENT = 0x0033,		/* Cancel-Document @private@ */
  IPP_GET_DOCUMENT_ATTRIBUTES,		/* Get-Document-Attributes @private@ */
  IPP_GET_DOCUMENTS,			/* Get-Documents @private@ */
  IPP_DELETE_DOCUMENT,			/* Delete-Document @private@ */
  IPP_SET_DOCUMENT_ATTRIBUTES,		/* Set-Document-Attributes @private@ */
  IPP_CANCEL_JOBS,			/* Cancel-Jobs */
  IPP_CANCEL_MY_JOBS,			/* Cancel-My-Jobs */
  IPP_RESUBMIT_JOB,			/* Resubmit-Job */
  IPP_CLOSE_JOB,			/* Close-Job */
  IPP_PRIVATE = 0x4000,			/* Reserved @private@ */
  CUPS_GET_DEFAULT,			/* Get the default printer */
  CUPS_GET_PRINTERS,			/* Get a list of printers and/or classes */
  CUPS_ADD_MODIFY_PRINTER,		/* Add or modify a printer */
  CUPS_DELETE_PRINTER,			/* Delete a printer */
  CUPS_GET_CLASSES,			/* Get a list of classes @deprecated@ */
  CUPS_ADD_MODIFY_CLASS,		/* Add or modify a class */
  CUPS_DELETE_CLASS,			/* Delete a class */
  CUPS_ACCEPT_JOBS,			/* Accept new jobs on a printer */
  CUPS_REJECT_JOBS,			/* Reject new jobs on a printer */
  CUPS_SET_DEFAULT,			/* Set the default printer */
  CUPS_GET_DEVICES,			/* Get a list of supported devices */
  CUPS_GET_PPDS,			/* Get a list of supported drivers */
  CUPS_MOVE_JOB,			/* Move a job to a different printer */
  CUPS_AUTHENTICATE_JOB,		/* Authenticate a job @since CUPS 1.2/Mac OS X 10.5@ */
  CUPS_GET_PPD,				/* Get a PPD file @since CUPS 1.3/Mac OS X 10.5@ */
  CUPS_GET_DOCUMENT = 0x4027		/* Get a document file @since CUPS 1.4/Mac OS X 10.6@ */
} ipp_op_t;

/* Old names for the operations */
#define CUPS_ADD_PRINTER	CUPS_ADD_MODIFY_PRINTER
#define CUPS_ADD_CLASS		CUPS_ADD_MODIFY_CLASS

typedef enum ipp_status_e		/**** IPP status codes ****/
{
  IPP_OK = 0x0000,			/* successful-ok */
  IPP_OK_SUBST,				/* successful-ok-ignored-or-substituted-attributes */
  IPP_OK_CONFLICT,			/* successful-ok-conflicting-attributes */
  IPP_OK_IGNORED_SUBSCRIPTIONS,		/* successful-ok-ignored-subscriptions */
  IPP_OK_IGNORED_NOTIFICATIONS,		/* successful-ok-ignored-notifications */
  IPP_OK_TOO_MANY_EVENTS,		/* successful-ok-too-many-events */
  IPP_OK_BUT_CANCEL_SUBSCRIPTION,	/* successful-ok-but-cancel-subscription */
  IPP_OK_EVENTS_COMPLETE,		/* successful-ok-events-complete */
  IPP_REDIRECTION_OTHER_SITE = 0x200,	/* redirection-other-site @private@ */
  CUPS_SEE_OTHER = 0x280,		/* cups-see-other */
  IPP_BAD_REQUEST = 0x0400,		/* client-error-bad-request */
  IPP_FORBIDDEN,			/* client-error-forbidden */
  IPP_NOT_AUTHENTICATED,		/* client-error-not-authenticated */
  IPP_NOT_AUTHORIZED,			/* client-error-not-authorized */
  IPP_NOT_POSSIBLE,			/* client-error-not-possible */
  IPP_TIMEOUT,				/* client-error-timeout */
  IPP_NOT_FOUND,			/* client-error-not-found */
  IPP_GONE,				/* client-error-gone */
  IPP_REQUEST_ENTITY,			/* client-error-request-entity-too-large */
  IPP_REQUEST_VALUE,			/* client-error-request-value-too-long */
  IPP_DOCUMENT_FORMAT,			/* client-error-document-format-not-supported */
  IPP_ATTRIBUTES,			/* client-error-attributes-or-values-not-supported */
  IPP_URI_SCHEME,			/* client-error-uri-scheme-not-supported */
  IPP_CHARSET,				/* client-error-charset-not-supported */
  IPP_CONFLICT,				/* client-error-conflicting-attributes */
  IPP_COMPRESSION_NOT_SUPPORTED,	/* client-error-compression-not-supported */
  IPP_COMPRESSION_ERROR,		/* client-error-compression-error */
  IPP_DOCUMENT_FORMAT_ERROR,		/* client-error-document-format-error */
  IPP_DOCUMENT_ACCESS_ERROR,		/* client-error-document-access-error */
  IPP_ATTRIBUTES_NOT_SETTABLE,		/* client-error-attributes-not-settable */
  IPP_IGNORED_ALL_SUBSCRIPTIONS,	/* client-error-ignored-all-subscriptions */
  IPP_TOO_MANY_SUBSCRIPTIONS,		/* client-error-too-many-subscriptions */
  IPP_IGNORED_ALL_NOTIFICATIONS,	/* client-error-ignored-all-notifications */
  IPP_PRINT_SUPPORT_FILE_NOT_FOUND,	/* client-error-print-support-file-not-found */

  IPP_INTERNAL_ERROR = 0x0500,		/* server-error-internal-error */
  IPP_OPERATION_NOT_SUPPORTED,		/* server-error-operation-not-supported */
  IPP_SERVICE_UNAVAILABLE,		/* server-error-service-unavailable */
  IPP_VERSION_NOT_SUPPORTED,		/* server-error-version-not-supported */
  IPP_DEVICE_ERROR,			/* server-error-device-error */
  IPP_TEMPORARY_ERROR,			/* server-error-temporary-error */
  IPP_NOT_ACCEPTING,			/* server-error-not-accepting-jobs */
  IPP_PRINTER_BUSY,			/* server-error-busy */
  IPP_ERROR_JOB_CANCELED,		/* server-error-job-canceled */
  IPP_MULTIPLE_JOBS_NOT_SUPPORTED,	/* server-error-multiple-document-jobs-not-supported */
  IPP_PRINTER_IS_DEACTIVATED,		/* server-error-printer-is-deactivated */

  IPP_AUTHENTICATION_CANCELED = 0x1000,	/* Authentication canceled by user @since CUPS 1.5/Mac OS X 10.7@ */
  IPP_PKI_ERROR,			/* Error negotiating a secure connection @since CUPS 1.5/Mac OS X 10.7@ */
  IPP_UPGRADE_REQUIRED			/* TLS upgrade required */
} ipp_status_t;
#define IPP_ERROR_JOB_CANCELLED IPP_ERROR_JOB_CANCELED

typedef unsigned char ipp_uchar_t;	/**** Unsigned 8-bit integer/character ****/

/**** New in CUPS 1.2 ****/
typedef ssize_t	(*ipp_iocb_t)(void *, ipp_uchar_t *, size_t);
					/**** IPP IO Callback Function @since CUPS 1.2/Mac OS X 10.5@ ****/

typedef union ipp_request_u		/**** Request Header ****/
{
  struct				/* Any Header */
  {
    ipp_uchar_t	version[2];		/* Protocol version number */
    int		op_status;		/* Operation ID or status code*/
    int		request_id;		/* Request ID */
  }		any;

  struct				/* Operation Header */
  {
    ipp_uchar_t	version[2];		/* Protocol version number */
    ipp_op_t	operation_id;		/* Operation ID */
    int		request_id;		/* Request ID */
  }		op;

  struct				/* Status Header */
  {
    ipp_uchar_t	version[2];		/* Protocol version number */
    ipp_status_t status_code;		/* Status code */
    int		request_id;		/* Request ID */
  }		status;

  /**** New in CUPS 1.1.19 ****/
  struct				/* Event Header @since CUPS 1.1.19/Mac OS X 10.3@ */
  {
    ipp_uchar_t	version[2];		/* Protocol version number */
    ipp_status_t status_code;		/* Status code */
    int		request_id;		/* Request ID */
  }		event;
} ipp_request_t;

/**** New in CUPS 1.1.19 ****/
typedef struct ipp_s ipp_t;

typedef union ipp_value_u		/**** Attribute Value ****/
{
  int		integer;		/* Integer/enumerated value */

  char		boolean;		/* Boolean value */

  ipp_uchar_t	date[11];		/* Date/time value */

  struct
  {
    int		xres,			/* Horizontal resolution */
		yres;			/* Vertical resolution */
    ipp_res_t	units;			/* Resolution units */
  }		resolution;		/* Resolution value */

  struct
  {
    int		lower,			/* Lower value */
		upper;			/* Upper value */
  }		range;			/* Range of integers value */

  struct
  {
    char	*charset;		/* Character set */
    char	*text;			/* String */
  }		string;			/* String with language value */

  struct
  {
    int		length;			/* Length of attribute */
    void	*data;			/* Data in attribute */
  }		unknown;		/* Unknown attribute type */

/**** New in CUPS 1.1.19 ****/
  ipp_t		*collection;		/* Collection value @since CUPS 1.1.19/Mac OS X 10.3@ */
} ipp_value_t;

typedef struct ipp_attribute_s		/**** Attribute ****/
{
  struct ipp_attribute_s *next;		/* Next attribute in list */
  ipp_tag_t	group_tag,		/* Job/Printer/Operation group tag */
		value_tag;		/* What type of value is it? */
  char		*name;			/* Name of attribute */
  int		num_values;		/* Number of values */
  ipp_value_t	values[1];		/* Values */
} ipp_attribute_t;

struct ipp_s				/**** IPP Request/Response/Notification ****/
{
  ipp_state_t	state;			/* State of request */
  ipp_request_t	request;		/* Request header */
  ipp_attribute_t *attrs;		/* Attributes */
  ipp_attribute_t *last;		/* Last attribute in list */
  ipp_attribute_t *current;		/* Current attribute (for read/write) */
  ipp_tag_t	curtag;			/* Current attribute group tag */

/**** New in CUPS 1.2 ****/
  ipp_attribute_t *prev;		/* Previous attribute (for read) @since CUPS 1.2/Mac OS X 10.5@ */

/**** New in CUPS 1.4.4 ****/
  int		use;			/* Use count @since CUPS 1.4.4/Mac OS X 10.6.?@ */
};


/*
 * Prototypes...
 */

extern ipp_attribute_t	*ippAddBoolean(ipp_t *ipp, ipp_tag_t group,
			               const char *name, char value);
extern ipp_attribute_t	*ippAddBooleans(ipp_t *ipp, ipp_tag_t group,
			                const char *name, int num_values,
					const char *values);
extern ipp_attribute_t	*ippAddDate(ipp_t *ipp, ipp_tag_t group,
			            const char *name, const ipp_uchar_t *value);
extern ipp_attribute_t	*ippAddInteger(ipp_t *ipp, ipp_tag_t group,
			               ipp_tag_t type, const char *name,
				       int value);
extern ipp_attribute_t	*ippAddIntegers(ipp_t *ipp, ipp_tag_t group,
			                ipp_tag_t type, const char *name,
					int num_values, const int *values);
extern ipp_attribute_t	*ippAddRange(ipp_t *ipp, ipp_tag_t group,
			             const char *name, int lower, int upper);
extern ipp_attribute_t	*ippAddRanges(ipp_t *ipp, ipp_tag_t group,
			              const char *name, int num_values,
				      const int *lower, const int *upper);
extern ipp_attribute_t	*ippAddResolution(ipp_t *ipp, ipp_tag_t group,
			                  const char *name, ipp_res_t units,
					  int xres, int yres);
extern ipp_attribute_t	*ippAddResolutions(ipp_t *ipp, ipp_tag_t group,
			                   const char *name, int num_values,
					   ipp_res_t units, const int *xres,
					   const int *yres);
extern ipp_attribute_t	*ippAddSeparator(ipp_t *ipp);
extern ipp_attribute_t	*ippAddString(ipp_t *ipp, ipp_tag_t group,
			              ipp_tag_t type, const char *name,
				      const char *charset, const char *value);
extern ipp_attribute_t	*ippAddStrings(ipp_t *ipp, ipp_tag_t group,
			               ipp_tag_t type, const char *name,
				       int num_values, const char *charset,
				       const char * const *values);
extern time_t		ippDateToTime(const ipp_uchar_t *date);
extern void		ippDelete(ipp_t *ipp);
extern const char	*ippErrorString(ipp_status_t error);
extern ipp_attribute_t	*ippFindAttribute(ipp_t *ipp, const char *name,
			                  ipp_tag_t type);
extern ipp_attribute_t	*ippFindNextAttribute(ipp_t *ipp, const char *name,
			                      ipp_tag_t type);
extern size_t		ippLength(ipp_t *ipp);
extern ipp_t		*ippNew(void);
extern ipp_state_t	ippRead(http_t *http, ipp_t *ipp);
extern const ipp_uchar_t *ippTimeToDate(time_t t);
extern ipp_state_t	ippWrite(http_t *http, ipp_t *ipp);
extern int		ippPort(void);
extern void		ippSetPort(int p);

/**** New in CUPS 1.1.19 ****/
extern ipp_attribute_t	*ippAddCollection(ipp_t *ipp, ipp_tag_t group,
			                  const char *name, ipp_t *value) _CUPS_API_1_1_19;
extern ipp_attribute_t	*ippAddCollections(ipp_t *ipp, ipp_tag_t group,
			                   const char *name, int num_values,
					   const ipp_t **values) _CUPS_API_1_1_19;
extern void		ippDeleteAttribute(ipp_t *ipp, ipp_attribute_t *attr) _CUPS_API_1_1_19;
extern ipp_state_t	ippReadFile(int fd, ipp_t *ipp) _CUPS_API_1_1_19;
extern ipp_state_t	ippWriteFile(int fd, ipp_t *ipp) _CUPS_API_1_1_19;

/**** New in CUPS 1.2 ****/
extern ipp_attribute_t	*ippAddOctetString(ipp_t *ipp, ipp_tag_t group,
			                   const char *name,
					   const void *data, int datalen) _CUPS_API_1_2;
extern ipp_status_t	ippErrorValue(const char *name) _CUPS_API_1_2;
extern ipp_t		*ippNewRequest(ipp_op_t op) _CUPS_API_1_2;
extern const char	*ippOpString(ipp_op_t op) _CUPS_API_1_2;
extern ipp_op_t		ippOpValue(const char *name) _CUPS_API_1_2;
extern ipp_state_t	ippReadIO(void *src, ipp_iocb_t cb, int blocking,
			          ipp_t *parent, ipp_t *ipp) _CUPS_API_1_2;
extern ipp_state_t	ippWriteIO(void *dst, ipp_iocb_t cb, int blocking,
			           ipp_t *parent, ipp_t *ipp) _CUPS_API_1_2;

/**** New in CUPS 1.4 ****/
extern const char	*ippTagString(ipp_tag_t tag) _CUPS_API_1_4;
extern ipp_tag_t	ippTagValue(const char *name) _CUPS_API_1_4;


/*
 * C++ magic...
 */

#  ifdef __cplusplus
}
#  endif /* __cplusplus */
#endif /* !_CUPS_IPP_H_ */

/*
 * End of "$Id: ipp.h 7847 2008-08-19 04:22:14Z mike $".
 */
