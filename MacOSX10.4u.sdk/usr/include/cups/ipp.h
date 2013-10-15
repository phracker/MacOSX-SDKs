/*
 * "$Id: ipp.h,v 1.1.1.15 2005/01/04 19:15:09 jlovell Exp $"
 *
 *   Internet Printing Protocol definitions for the Common UNIX Printing
 *   System (CUPS).
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

#  define IPP_VERSION		"\001\001"

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

#  define IPP_MAX_NAME		256
#  define IPP_MAX_VALUES	10	/* Now just an allocation increment */


/*
 * Types and structures...
 */

typedef enum			/**** Format tags for attribute formats... ****/
{
  IPP_TAG_ZERO = 0x00,
  IPP_TAG_OPERATION,
  IPP_TAG_JOB,
  IPP_TAG_END,
  IPP_TAG_PRINTER,
  IPP_TAG_UNSUPPORTED_GROUP,
  IPP_TAG_SUBSCRIPTION,
  IPP_TAG_EVENT_NOTIFICATION,
  IPP_TAG_UNSUPPORTED_VALUE = 0x10,
  IPP_TAG_DEFAULT,
  IPP_TAG_UNKNOWN,
  IPP_TAG_NOVALUE,
  IPP_TAG_NOTSETTABLE = 0x15,
  IPP_TAG_DELETEATTR,
  IPP_TAG_ADMINDEFINE,
  IPP_TAG_INTEGER = 0x21,
  IPP_TAG_BOOLEAN,
  IPP_TAG_ENUM,
  IPP_TAG_STRING = 0x30,
  IPP_TAG_DATE,
  IPP_TAG_RESOLUTION,
  IPP_TAG_RANGE,
  IPP_TAG_BEGIN_COLLECTION,
  IPP_TAG_TEXTLANG,
  IPP_TAG_NAMELANG,
  IPP_TAG_END_COLLECTION,
  IPP_TAG_TEXT = 0x41,
  IPP_TAG_NAME,
  IPP_TAG_KEYWORD = 0x44,
  IPP_TAG_URI,
  IPP_TAG_URISCHEME,
  IPP_TAG_CHARSET,
  IPP_TAG_LANGUAGE,
  IPP_TAG_MIMETYPE,
  IPP_TAG_MEMBERNAME,
  IPP_TAG_MASK = 0x7fffffff,	/* Mask for copied attribute values */
  IPP_TAG_COPY = -0x7fffffff-1	/* Bitflag for copied attribute values */
} ipp_tag_t;

typedef enum			/**** Resolution units... ****/
{
  IPP_RES_PER_INCH = 3,
  IPP_RES_PER_CM
} ipp_res_t;

typedef enum			/**** Finishings... ****/
{
  IPP_FINISHINGS_NONE = 3,
  IPP_FINISHINGS_STAPLE,
  IPP_FINISHINGS_PUNCH,
  IPP_FINISHINGS_COVER,
  IPP_FINISHINGS_BIND,
  IPP_FINISHINGS_SADDLE_STITCH,
  IPP_FINISHINGS_EDGE_STITCH,
  IPP_FINISHINGS_FOLD,
  IPP_FINISHINGS_TRIM,
  IPP_FINISHINGS_BALE,
  IPP_FINISHINGS_BOOKLET_MAKER,
  IPP_FINISHINGS_JOB_OFFSET,
  IPP_FINISHINGS_STAPLE_TOP_LEFT = 20,
  IPP_FINISHINGS_STAPLE_BOTTOM_LEFT,
  IPP_FINISHINGS_STAPLE_TOP_RIGHT,
  IPP_FINISHINGS_STAPLE_BOTTOM_RIGHT,
  IPP_FINISHINGS_EDGE_STITCH_LEFT,
  IPP_FINISHINGS_EDGE_STITCH_TOP,
  IPP_FINISHINGS_EDGE_STITCH_RIGHT,
  IPP_FINISHINGS_EDGE_STITCH_BOTTOM,
  IPP_FINISHINGS_STAPLE_DUAL_LEFT,
  IPP_FINISHINGS_STAPLE_DUAL_TOP,
  IPP_FINISHINGS_STAPLE_DUAL_RIGHT,
  IPP_FINISHINGS_STAPLE_DUAL_BOTTOM,
  IPP_FINISHINGS_BIND_LEFT = 50,
  IPP_FINISHINGS_BIND_TOP,
  IPP_FINISHINGS_BIND_RIGHT,
  IPP_FINISHINGS_BIND_BOTTOM
} ipp_finish_t;

typedef enum			/**** Orientation... ****/
{
  IPP_PORTRAIT = 3,		/* No rotation */
  IPP_LANDSCAPE,		/* 90 degrees counter-clockwise */
  IPP_REVERSE_LANDSCAPE,	/* 90 degrees clockwise */
  IPP_REVERSE_PORTRAIT		/* 180 degrees */
} ipp_orient_t;

typedef enum			/**** Qualities... ****/
{
  IPP_QUALITY_DRAFT = 3,
  IPP_QUALITY_NORMAL,
  IPP_QUALITY_HIGH
} ipp_quality_t;

typedef enum			/**** Job States.... */
{
  IPP_JOB_PENDING = 3,
  IPP_JOB_HELD,
  IPP_JOB_PROCESSING,
  IPP_JOB_STOPPED,
  IPP_JOB_CANCELLED,
  IPP_JOB_ABORTED,
  IPP_JOB_COMPLETED
} ipp_jstate_t;

typedef enum			/**** Printer States.... */
{
  IPP_PRINTER_IDLE = 3,
  IPP_PRINTER_PROCESSING,
  IPP_PRINTER_STOPPED
} ipp_pstate_t;

typedef enum			/**** IPP states... ****/
{
  IPP_ERROR = -1,		/* An error occurred */
  IPP_IDLE,			/* Nothing is happening/request completed */
  IPP_HEADER,			/* The request header needs to be sent/received */
  IPP_ATTRIBUTE,		/* One or more attributes need to be sent/received */
  IPP_DATA			/* IPP request data needs to be sent/received */
} ipp_state_t;

typedef enum			/**** IPP operations... ****/
{
  IPP_PRINT_JOB = 0x0002,
  IPP_PRINT_URI,
  IPP_VALIDATE_JOB,
  IPP_CREATE_JOB,
  IPP_SEND_DOCUMENT,
  IPP_SEND_URI,
  IPP_CANCEL_JOB,
  IPP_GET_JOB_ATTRIBUTES,
  IPP_GET_JOBS,
  IPP_GET_PRINTER_ATTRIBUTES,
  IPP_HOLD_JOB,
  IPP_RELEASE_JOB,
  IPP_RESTART_JOB,
  IPP_PAUSE_PRINTER = 0x0010,
  IPP_RESUME_PRINTER,
  IPP_PURGE_JOBS,
  IPP_SET_PRINTER_ATTRIBUTES,
  IPP_SET_JOB_ATTRIBUTES,
  IPP_GET_PRINTER_SUPPORTED_VALUES,
  IPP_CREATE_PRINTER_SUBSCRIPTION,
  IPP_CREATE_JOB_SUBSCRIPTION,
  IPP_GET_SUBSCRIPTION_ATTRIBUTES,
  IPP_GET_SUBSCRIPTIONS,
  IPP_RENEW_SUBSCRIPTION,
  IPP_CANCEL_SUBSCRIPTION,
  IPP_GET_NOTIFICATIONS,
  IPP_SEND_NOTIFICATIONS,
  IPP_GET_PRINT_SUPPORT_FILES = 0x0021,
  IPP_ENABLE_PRINTER,
  IPP_DISABLE_PRINTER,
  IPP_PAUSE_PRINTER_AFTER_CURRENT_JOB,
  IPP_HOLD_NEW_JOBS,
  IPP_RELEASE_HELD_NEW_JOBS,
  IPP_DEACTIVATE_PRINTER,
  IPP_ACTIVATE_PRINTER,
  IPP_RESTART_PRINTER,
  IPP_SHUTDOWN_PRINTER,
  IPP_STARTUP_PRINTER,
  IPP_REPROCESS_JOB,
  IPP_CANCEL_CURRENT_JOB,
  IPP_SUSPEND_CURRENT_JOB,
  IPP_RESUME_JOB,
  IPP_PROMOTE_JOB,
  IPP_SCHEDULE_JOB_AFTER,
  IPP_PRIVATE = 0x4000,
  CUPS_GET_DEFAULT,
  CUPS_GET_PRINTERS,
  CUPS_ADD_PRINTER,
  CUPS_DELETE_PRINTER,
  CUPS_GET_CLASSES,
  CUPS_ADD_CLASS,
  CUPS_DELETE_CLASS,
  CUPS_ACCEPT_JOBS,
  CUPS_REJECT_JOBS,
  CUPS_SET_DEFAULT,
  CUPS_GET_DEVICES,
  CUPS_GET_PPDS,
  CUPS_MOVE_JOB,
  CUPS_ADD_DEVICE,
  CUPS_DELETE_DEVICE
} ipp_op_t;

typedef enum			/**** IPP status codes... ****/
{
  IPP_OK = 0x0000,
  IPP_OK_SUBST,
  IPP_OK_CONFLICT,
  IPP_OK_IGNORED_SUBSCRIPTIONS,
  IPP_OK_IGNORED_NOTIFICATIONS,
  IPP_OK_TOO_MANY_EVENTS,
  IPP_OK_BUT_CANCEL_SUBSCRIPTION,
  IPP_REDIRECTION_OTHER_SITE = 0x300,
  IPP_BAD_REQUEST = 0x0400,
  IPP_FORBIDDEN,
  IPP_NOT_AUTHENTICATED,
  IPP_NOT_AUTHORIZED,
  IPP_NOT_POSSIBLE,
  IPP_TIMEOUT,
  IPP_NOT_FOUND,
  IPP_GONE,
  IPP_REQUEST_ENTITY,
  IPP_REQUEST_VALUE,
  IPP_DOCUMENT_FORMAT,
  IPP_ATTRIBUTES,
  IPP_URI_SCHEME,
  IPP_CHARSET,
  IPP_CONFLICT,
  IPP_COMPRESSION_NOT_SUPPORTED,
  IPP_COMPRESSION_ERROR,
  IPP_DOCUMENT_FORMAT_ERROR,
  IPP_DOCUMENT_ACCESS_ERROR,
  IPP_ATTRIBUTES_NOT_SETTABLE,
  IPP_IGNORED_ALL_SUBSCRIPTIONS,
  IPP_TOO_MANY_SUBSCRIPTIONS,
  IPP_IGNORED_ALL_NOTIFICATIONS,
  IPP_PRINT_SUPPORT_FILE_NOT_FOUND,

  IPP_INTERNAL_ERROR = 0x0500,
  IPP_OPERATION_NOT_SUPPORTED,
  IPP_SERVICE_UNAVAILABLE,
  IPP_VERSION_NOT_SUPPORTED,
  IPP_DEVICE_ERROR,
  IPP_TEMPORARY_ERROR,
  IPP_NOT_ACCEPTING,
  IPP_PRINTER_BUSY,
  IPP_ERROR_JOB_CANCELLED,
  IPP_MULTIPLE_JOBS_NOT_SUPPORTED,
  IPP_PRINTER_IS_DEACTIVATED
} ipp_status_t;

typedef unsigned char ipp_uchar_t;/**** Unsigned 8-bit integer/character ****/

/**** New in CUPS 1.1.19 ****/
typedef int	(*ipp_iocb_t)(void *, ipp_uchar_t *, int);
				/**** IPP IO Callback Function ****/

typedef union			/**** Request Header ****/
{
  struct			/* Any Header */
  {
    ipp_uchar_t	version[2];	/* Protocol version number */
    int		op_status;	/* Operation ID or status code*/
    int		request_id;	/* Request ID */
  }		any;

  struct			/* Operation Header */
  {
    ipp_uchar_t	version[2];	/* Protocol version number */
    ipp_op_t	operation_id;	/* Operation ID */
    int		request_id;	/* Request ID */
  }		op;

  struct			/* Status Header */
  {
    ipp_uchar_t	version[2];	/* Protocol version number */
    ipp_status_t status_code;	/* Status code */
    int		request_id;	/* Request ID */
  }		status;

  /**** New in CUPS 1.1.19 ****/
  struct			/* Event Header */
  {
    ipp_uchar_t	version[2];	/* Protocol version number */
    ipp_status_t status_code;	/* Status code */
    int		request_id;	/* Request ID */
  }		event;
} ipp_request_t;

/**** New in CUPS 1.1.19 ****/
typedef struct ipp_str ipp_t;

typedef union			/**** Attribute Value ****/
{
  int		integer;	/* Integer/enumerated value */

  char		boolean;	/* Boolean value */

  ipp_uchar_t	date[11];	/* Date/time value */

  struct
  {
    int		xres,		/* Horizontal resolution */
		yres;		/* Vertical resolution */
    ipp_res_t	units;		/* Resolution units */
  }		resolution;	/* Resolution value */

  struct
  {
    int		lower,		/* Lower value */
		upper;		/* Upper value */
  }		range;		/* Range of integers value */

  struct
  {
    char	*charset;	/* Character set */
    char	*text;		/* String */
  }		string;		/* String with language value */

  struct
  {
    int		length;		/* Length of attribute */
    void	*data;		/* Data in attribute */
  }		unknown;	/* Unknown attribute type */

/**** New in CUPS 1.1.19 ****/
  ipp_t		*collection;	/* Collection value */
} ipp_value_t;

typedef struct ipp_attribute_s	/**** Attribute ****/
{
  struct ipp_attribute_s *next;	/* Next attribute in list */
  ipp_tag_t	group_tag,	/* Job/Printer/Operation group tag */
		value_tag;	/* What type of value is it? */
  char		*name;		/* Name of attribute */
  int		num_values;	/* Number of values */
  ipp_value_t	values[1];	/* Values */
} ipp_attribute_t;

struct ipp_str			/**** IPP Request/Response/Notification ****/
{
  ipp_state_t	state;		/* State of request */
  ipp_request_t	request;	/* Request header */
  ipp_attribute_t *attrs,	/* Attributes */
		*last,		/* Last attribute in list */
		*current;	/* Current attribute (for read/write) */
  ipp_tag_t	curtag;		/* Current attribute group tag */
};


/*
 * Prototypes...
 */

extern ipp_attribute_t	*ippAddBoolean(ipp_t *ipp, ipp_tag_t group, const char *name, char value);
extern ipp_attribute_t	*ippAddBooleans(ipp_t *ipp, ipp_tag_t group, const char *name, int num_values, const char *values);
extern ipp_attribute_t	*ippAddDate(ipp_t *ipp, ipp_tag_t group, const char *name, const ipp_uchar_t *value);
extern ipp_attribute_t	*ippAddInteger(ipp_t *ipp, ipp_tag_t group, ipp_tag_t type, const char *name, int value);
extern ipp_attribute_t	*ippAddIntegers(ipp_t *ipp, ipp_tag_t group, ipp_tag_t type, const char *name, int num_values, const int *values);
extern ipp_attribute_t	*ippAddRange(ipp_t *ipp, ipp_tag_t group, const char *name, int lower, int upper);
extern ipp_attribute_t	*ippAddRanges(ipp_t *ipp, ipp_tag_t group, const char *name, int num_values, const int *lower, const int *upper);
extern ipp_attribute_t	*ippAddResolution(ipp_t *ipp, ipp_tag_t group, const char *name, ipp_res_t units, int xres, int yres);
extern ipp_attribute_t	*ippAddResolutions(ipp_t *ipp, ipp_tag_t group, const char *name, int num_values, ipp_res_t units, const int *xres, const int *yres);
extern ipp_attribute_t	*ippAddSeparator(ipp_t *ipp);
extern ipp_attribute_t	*ippAddString(ipp_t *ipp, ipp_tag_t group, ipp_tag_t type, const char *name, const char *charset, const char *value);
extern ipp_attribute_t	*ippAddStrings(ipp_t *ipp, ipp_tag_t group, ipp_tag_t type, const char *name, int num_values, const char *charset, const char * const *values);
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
extern ipp_attribute_t	*ippAddCollection(ipp_t *ipp, ipp_tag_t group, const char *name, ipp_t *value);
extern ipp_attribute_t	*ippAddCollections(ipp_t *ipp, ipp_tag_t group, const char *name, int num_values, const ipp_t **values);
extern void		ippDeleteAttribute(ipp_t *ipp, ipp_attribute_t *attr);
extern ipp_state_t	ippReadFile(int fd, ipp_t *ipp);
extern ipp_state_t	ippReadIO(void *src, ipp_iocb_t cb, int blocking, ipp_t *parent, ipp_t *ipp);
extern ipp_state_t	ippWriteFile(int fd, ipp_t *ipp);
extern ipp_state_t	ippWriteIO(void *dst, ipp_iocb_t cb, int blocking, ipp_t *parent, ipp_t *ipp);


/*
 * "Private" functions used internally by CUPS...
 */

extern ipp_attribute_t	*_ipp_add_attr(ipp_t *, int);
extern void		_ipp_free_attr(ipp_attribute_t *);


/*
 * C++ magic...
 */

#  ifdef __cplusplus
}
#  endif /* __cplusplus */
#endif /* !_CUPS_IPP_H_ */

/*
 * End of "$Id: ipp.h,v 1.1.1.15 2005/01/04 19:15:09 jlovell Exp $".
 */
