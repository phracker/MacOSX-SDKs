/*
 * "$Id: http.h,v 1.15 2005/01/20 03:24:54 jlovell Exp $"
 *
 *   Hyper-Text Transport Protocol definitions for the Common UNIX Printing
 *   System (CUPS).
 *
 *   Copyright 1997-2005 by Easy Software Products, all rights reserved.
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

#ifndef _CUPS_HTTP_H_
#  define _CUPS_HTTP_H_

/*
 * Include necessary headers...
 */

#  include <string.h>
#  include <time.h>
#  ifdef WIN32
#    include <winsock.h>
#  else
#    include <unistd.h>
#    include <sys/time.h>
#    include <sys/types.h>
#    include <sys/socket.h>
#    include <netdb.h>
#    include <netinet/in.h>
#    include <arpa/inet.h>
#    include <netinet/in_systm.h>
#    include <netinet/ip.h>
#    if !defined(__APPLE__) || !defined(TCP_NODELAY)
#      include <netinet/tcp.h>
#    endif /* !__APPLE__ || !TCP_NODELAY */
#  endif /* WIN32 */

#  include "md5.h"


/*
 * C++ magic...
 */

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */


/*
 * Limits...
 */

#  define HTTP_MAX_URI		1024	/* Max length of URI string */
#  define HTTP_MAX_HOST		256	/* Max length of hostname string */
#  define HTTP_MAX_BUFFER	2048	/* Max length of data buffer */
#  define HTTP_MAX_VALUE	256	/* Max header field value length */


/*
 * HTTP state values...
 */

typedef enum			/* States are server-oriented */
{
  HTTP_WAITING,			/* Waiting for command */
  HTTP_OPTIONS,			/* OPTIONS command, waiting for blank line */
  HTTP_GET,			/* GET command, waiting for blank line */
  HTTP_GET_SEND,		/* GET command, sending data */
  HTTP_HEAD,			/* HEAD command, waiting for blank line */
  HTTP_POST,			/* POST command, waiting for blank line */
  HTTP_POST_RECV,		/* POST command, receiving data */
  HTTP_POST_SEND,		/* POST command, sending data */
  HTTP_PUT,			/* PUT command, waiting for blank line */
  HTTP_PUT_RECV,		/* PUT command, receiving data */
  HTTP_DELETE,			/* DELETE command, waiting for blank line */
  HTTP_TRACE,			/* TRACE command, waiting for blank line */
  HTTP_CLOSE,			/* CLOSE command, waiting for blank line */
  HTTP_STATUS			/* Command complete, sending status */
} http_state_t;


/*
 * HTTP version numbers...
 */

typedef enum
{
  HTTP_0_9 = 9,			/* HTTP/0.9 */
  HTTP_1_0 = 100,		/* HTTP/1.0 */
  HTTP_1_1 = 101		/* HTTP/1.1 */
} http_version_t;


/*
 * HTTP keep-alive values...
 */

typedef enum
{
  HTTP_KEEPALIVE_OFF = 0,
  HTTP_KEEPALIVE_ON
} http_keepalive_t;


/*
 * HTTP transfer encoding values...
 */

typedef enum
{
  HTTP_ENCODE_LENGTH,		/* Data is sent with Content-Length */
  HTTP_ENCODE_CHUNKED		/* Data is chunked */
} http_encoding_t;


/*
 * HTTP encryption values...
 */

typedef enum
{
  HTTP_ENCRYPT_IF_REQUESTED,	/* Encrypt if requested (TLS upgrade) */
  HTTP_ENCRYPT_NEVER,		/* Never encrypt */
  HTTP_ENCRYPT_REQUIRED,	/* Encryption is required (TLS upgrade) */
  HTTP_ENCRYPT_ALWAYS		/* Always encrypt (SSL) */
} http_encryption_t;


/*
 * HTTP authentication types...
 */

typedef enum
{
  HTTP_AUTH_NONE,		/* No authentication in use */
  HTTP_AUTH_BASIC,		/* Basic authentication in use */
  HTTP_AUTH_MD5,		/* Digest authentication in use */
  HTTP_AUTH_MD5_SESS,		/* MD5-session authentication in use */
  HTTP_AUTH_MD5_INT,		/* Digest authentication in use for body */
  HTTP_AUTH_MD5_SESS_INT	/* MD5-session authentication in use for body */
} http_auth_t;


/*
 * HTTP status codes...
 */

typedef enum
{
  HTTP_ERROR = -1,		/* An error response from httpXxxx() */

  HTTP_CONTINUE = 100,		/* Everything OK, keep going... */
  HTTP_SWITCHING_PROTOCOLS,	/* HTTP upgrade to TLS/SSL */

  HTTP_OK = 200,		/* OPTIONS/GET/HEAD/POST/TRACE command was successful */
  HTTP_CREATED,			/* PUT command was successful */
  HTTP_ACCEPTED,		/* DELETE command was successful */
  HTTP_NOT_AUTHORITATIVE,	/* Information isn't authoritative */
  HTTP_NO_CONTENT,		/* Successful command, no new data */
  HTTP_RESET_CONTENT,		/* Content was reset/recreated */
  HTTP_PARTIAL_CONTENT,		/* Only a partial file was recieved/sent */

  HTTP_MULTIPLE_CHOICES = 300,	/* Multiple files match request */
  HTTP_MOVED_PERMANENTLY,	/* Document has moved permanently */
  HTTP_MOVED_TEMPORARILY,	/* Document has moved temporarily */
  HTTP_SEE_OTHER,		/* See this other link... */
  HTTP_NOT_MODIFIED,		/* File not modified */
  HTTP_USE_PROXY,		/* Must use a proxy to access this URI */

  HTTP_BAD_REQUEST = 400,	/* Bad request */
  HTTP_UNAUTHORIZED,		/* Unauthorized to access host */
  HTTP_PAYMENT_REQUIRED,	/* Payment required */
  HTTP_FORBIDDEN,		/* Forbidden to access this URI */
  HTTP_NOT_FOUND,		/* URI was not found */
  HTTP_METHOD_NOT_ALLOWED,	/* Method is not allowed */
  HTTP_NOT_ACCEPTABLE,		/* Not Acceptable */
  HTTP_PROXY_AUTHENTICATION,	/* Proxy Authentication is Required */
  HTTP_REQUEST_TIMEOUT,		/* Request timed out */
  HTTP_CONFLICT,		/* Request is self-conflicting */
  HTTP_GONE,			/* Server has gone away */
  HTTP_LENGTH_REQUIRED,		/* A content length or encoding is required */
  HTTP_PRECONDITION,		/* Precondition failed */
  HTTP_REQUEST_TOO_LARGE,	/* Request entity too large */
  HTTP_URI_TOO_LONG,		/* URI too long */
  HTTP_UNSUPPORTED_MEDIATYPE,	/* The requested media type is unsupported */
  HTTP_UPGRADE_REQUIRED = 426,	/* Upgrade to SSL/TLS required */

  HTTP_SERVER_ERROR = 500,	/* Internal server error */
  HTTP_NOT_IMPLEMENTED,		/* Feature not implemented */
  HTTP_BAD_GATEWAY,		/* Bad gateway */
  HTTP_SERVICE_UNAVAILABLE,	/* Service is unavailable */
  HTTP_GATEWAY_TIMEOUT,		/* Gateway connection timed out */
  HTTP_NOT_SUPPORTED		/* HTTP version not supported */
} http_status_t;


/*
 * HTTP field names...
 */

typedef enum
{
  HTTP_FIELD_UNKNOWN = -1,
  HTTP_FIELD_ACCEPT_LANGUAGE,
  HTTP_FIELD_ACCEPT_RANGES,
  HTTP_FIELD_AUTHORIZATION,
  HTTP_FIELD_CONNECTION,
  HTTP_FIELD_CONTENT_ENCODING,
  HTTP_FIELD_CONTENT_LANGUAGE,
  HTTP_FIELD_CONTENT_LENGTH,
  HTTP_FIELD_CONTENT_LOCATION,
  HTTP_FIELD_CONTENT_MD5,
  HTTP_FIELD_CONTENT_RANGE,
  HTTP_FIELD_CONTENT_TYPE,
  HTTP_FIELD_CONTENT_VERSION,
  HTTP_FIELD_DATE,
  HTTP_FIELD_HOST,
  HTTP_FIELD_IF_MODIFIED_SINCE,
  HTTP_FIELD_IF_UNMODIFIED_SINCE,
  HTTP_FIELD_KEEP_ALIVE,
  HTTP_FIELD_LAST_MODIFIED,
  HTTP_FIELD_LINK,
  HTTP_FIELD_LOCATION,
  HTTP_FIELD_RANGE,
  HTTP_FIELD_REFERER,
  HTTP_FIELD_RETRY_AFTER,
  HTTP_FIELD_TRANSFER_ENCODING,
  HTTP_FIELD_UPGRADE,
  HTTP_FIELD_USER_AGENT,
  HTTP_FIELD_WWW_AUTHENTICATE,
  HTTP_FIELD_MAX
} http_field_t;
  

/*
 * HTTP connection structure...
 */

typedef struct
{
  int			fd;		/* File descriptor for this socket */
  int			blocking;	/* To block or not to block */
  int			error;		/* Last error on read */
  time_t		activity;	/* Time since last read/write */
  http_state_t		state;		/* State of client */
  http_status_t		status;		/* Status of last request */
  http_version_t	version;	/* Protocol version */
  http_keepalive_t	keep_alive;	/* Keep-alive supported? */
  struct sockaddr_in	hostaddr;	/* Address of connected host */
  char			hostname[HTTP_MAX_HOST],
  					/* Name of connected host */
			fields[HTTP_FIELD_MAX][HTTP_MAX_VALUE];
					/* Field values */
  char			*data;		/* Pointer to data buffer */
  http_encoding_t	data_encoding;	/* Chunked or not */
  int			deprecated_data_remaining;
  					/* DEPRECATED: mirrors data_remaining below as */
  					/*   min(INT_MAX, data_remaining) */
  int			used;		/* Number of bytes used in buffer */
  char			buffer[HTTP_MAX_BUFFER];
					/* Buffer for messages */
  int			auth_type;	/* Authentication in use */
  md5_state_t		md5_state;	/* MD5 state */
  char			nonce[HTTP_MAX_VALUE];
					/* Nonce value */
  int			nonce_count;	/* Nonce count */
  void			*tls;		/* TLS state information */
  http_encryption_t	encryption;	/* Encryption requirements */
  /**** New in CUPS 1.1.19 ****/
  fd_set		*input_set;	/* select() set for httpWait() */
  http_status_t		expect;		/* Expect: header */
  char			*cookie;	/* Cookie value(s) */
  /**** New in CUPS 1.1.20 ****/
  char			authstring[HTTP_MAX_VALUE],
					/* Current Authentication value */
			userpass[HTTP_MAX_VALUE];
					/* Username:password string */
  int			digest_tries;	/* Number of tries for digest auth */
  /**** New in CUPS 1.1.20+ ****/
  off_t			data_remaining;	/* Number of bytes left */
} http_t;


/*
 * Prototypes...
 */

#  define		httpBlocking(http,b)	(http)->blocking = (b)
extern int		httpCheck(http_t *http);
#  define		httpClearFields(http)	memset((http)->fields, 0, sizeof((http)->fields)),\
						httpSetField((http), HTTP_FIELD_HOST, (http)->hostname)
extern void		httpClose(http_t *http);
extern http_t		*httpConnect(const char *host, int port);
extern http_t		*httpConnectEncrypt(const char *host, int port,
			                    http_encryption_t encrypt);
extern int		httpDelete(http_t *http, const char *uri);
extern int		httpEncryption(http_t *http, http_encryption_t e);
#  define		httpError(http) ((http)->error)
extern void		httpFlush(http_t *http);
extern int		httpGet(http_t *http, const char *uri);
extern char		*httpGets(char *line, int length, http_t *http);
extern const char	*httpGetDateString(time_t t);
extern time_t		httpGetDateTime(const char *s);
#  define		httpGetField(http,field)	(http)->fields[field]
extern struct hostent	*httpGetHostByName(const char *name);
extern char		*httpGetSubField(http_t *http, http_field_t field,
			                 const char *name, char *value);
extern int		httpHead(http_t *http, const char *uri);
extern void		httpInitialize(void);
extern int		httpOptions(http_t *http, const char *uri);
extern int		httpPost(http_t *http, const char *uri);
extern int		httpPrintf(http_t *http, const char *format, ...)
#  ifdef __GNUC__
__attribute__ ((__format__ (__printf__, 2, 3)))
#  endif /* __GNUC__ */
;
extern int		httpPut(http_t *http, const char *uri);
extern int		httpRead(http_t *http, char *buffer, int length);
extern int		httpReconnect(http_t *http);
extern void		httpSeparate(const char *uri, char *method,
			             char *username, char *host, int *port,
				     char *resource);
extern void		httpSetField(http_t *http, http_field_t field,
			             const char *value);
extern const char	*httpStatus(http_status_t status);
extern int		httpTrace(http_t *http, const char *uri);
extern http_status_t	httpUpdate(http_t *http);
extern int		httpWrite(http_t *http, const char *buffer, int length);
extern char		*httpEncode64(char *out, const char *in);
extern char		*httpDecode64(char *out, const char *in);
extern int		httpGetLength(http_t *http);
extern char		*httpMD5(const char *, const char *, const char *,
			         char [33]);
extern char		*httpMD5Final(const char *, const char *, const char *,
			              char [33]);
extern char		*httpMD5String(const md5_byte_t *, char [33]);

/**** New in CUPS 1.1.19 ****/
extern void		httpClearCookie(http_t *http);
#define httpGetCookie(http) ((http)->cookie)
extern void		httpSetCookie(http_t *http, const char *cookie);
extern int		httpWait(http_t *http, int msec);

/**** New in CUPS 1.1.21 ****/
extern char		*httpDecode64_2(char *out, int *outlen, const char *in);
extern char		*httpEncode64_2(char *out, int outlen, const char *in,
			                int inlen);
extern void		httpSeparate2(const char *uri,
			              char *method, int methodlen,
			              char *username, int usernamelen,
				      char *host, int hostlen, int *port,
				      char *resource, int resourcelen);

extern void		httpSeparateApple(const char *uri,
			              char *method, int methodlen,
			              char *username, int usernamelen,
				      char *host, int hostlen, int *port,
				      char *resource, int resourcelen, int decode);


/*
 * C++ magic...
 */

#  ifdef __cplusplus
}
#  endif /* __cplusplus */
#endif /* !_CUPS_HTTP_H_ */

/*
 * End of "$Id: http.h,v 1.15 2005/01/20 03:24:54 jlovell Exp $".
 */
