/*
 * "$Id: http.h 7026 2007-10-19 00:57:45Z mike $"
 *
 *   Hyper-Text Transport Protocol definitions for CUPS.
 *
 *   Copyright 2007-2012 by Apple Inc.
 *   Copyright 1997-2007 by Easy Software Products, all rights reserved.
 *
 *   These coded instructions, statements, and computer programs are the
 *   property of Apple Inc. and are protected by Federal copyright
 *   law.  Distribution and use rights are outlined in the file "LICENSE.txt"
 *   which should have been included with this file.  If this file is
 *   file is missing or damaged, see the license at "http://www.cups.org/".
 *
 *   This file is subject to the Apple OS-Developed Software exception.
 */

#ifndef _CUPS_HTTP_H_
#  define _CUPS_HTTP_H_

/*
 * Include necessary headers...
 */

#  include "versioning.h"
#  include "array.h"
#  include <string.h>
#  include <time.h>
#  include <sys/types.h>
#  ifdef WIN32
#    ifndef __CUPS_SSIZE_T_DEFINED
#      define __CUPS_SSIZE_T_DEFINED
/* Windows does not support the ssize_t type, so map it to off_t... */
typedef off_t ssize_t;			/* @private@ */
#    endif /* !__CUPS_SSIZE_T_DEFINED */
#    include <winsock2.h>
#    include <ws2tcpip.h>
#  else
#    ifdef __sgi
#      define INET6			/* IRIX IPv6 support... */
#    endif /* __sgi */
#    include <unistd.h>
#    include <sys/time.h>
#    include <sys/socket.h>
#    include <netdb.h>
#    include <netinet/in.h>
#    include <arpa/inet.h>
#    include <netinet/in_systm.h>
#    include <netinet/ip.h>
#    if !defined(__APPLE__) || !defined(TCP_NODELAY)
#      include <netinet/tcp.h>
#    endif /* !__APPLE__ || !TCP_NODELAY */
#    if defined(AF_UNIX) && !defined(AF_LOCAL)
#      define AF_LOCAL AF_UNIX		/* Older UNIX's have old names... */
#    endif /* AF_UNIX && !AF_LOCAL */
#    ifdef AF_LOCAL
#      include <sys/un.h>
#    endif /* AF_LOCAL */
#    if defined(LOCAL_PEERCRED) && !defined(SO_PEERCRED)
#      define SO_PEERCRED LOCAL_PEERCRED
#    endif /* LOCAL_PEERCRED && !SO_PEERCRED */
#  endif /* WIN32 */


/*
 * C++ magic...
 */

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */


/*
 * Oh, the wonderful world of IPv6 compatibility.  Apparently some
 * implementations expose the (more logical) 32-bit address parts
 * to everyone, while others only expose it to kernel code...  To
 * make supporting IPv6 even easier, each vendor chose different
 * core structure and union names, so the same defines or code
 * can't be used on all platforms.
 *
 * The following will likely need tweaking on new platforms that
 * support IPv6 - the "s6_addr32" define maps to the 32-bit integer
 * array in the in6_addr union, which is named differently on various
 * platforms.
 */

#if defined(AF_INET6) && !defined(s6_addr32)
#  if defined(__sun)
#    define s6_addr32	_S6_un._S6_u32
#  elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__APPLE__)|| defined(__DragonFly__)
#    define s6_addr32	__u6_addr.__u6_addr32
#  elif defined(__osf__)
#    define s6_addr32	s6_un.sa6_laddr
#  elif defined(WIN32)
/*
 * Windows only defines byte and 16-bit word members of the union and
 * requires special casing of all raw address code...
 */
#    define s6_addr32	error_need_win32_specific_code
#  endif /* __sun */
#endif /* AF_INET6 && !s6_addr32 */


/*
 * Limits...
 */

#  define HTTP_MAX_URI		1024	/* Max length of URI string */
#  define HTTP_MAX_HOST		256	/* Max length of hostname string */
#  define HTTP_MAX_BUFFER	2048	/* Max length of data buffer */
#  define HTTP_MAX_VALUE	256	/* Max header field value length */


/*
 * Types and structures...
 */

typedef enum http_auth_e		/**** HTTP authentication types ****/
{
  HTTP_AUTH_NONE,			/* No authentication in use */
  HTTP_AUTH_BASIC,			/* Basic authentication in use */
  HTTP_AUTH_MD5,			/* Digest authentication in use */
  HTTP_AUTH_MD5_SESS,			/* MD5-session authentication in use */
  HTTP_AUTH_MD5_INT,			/* Digest authentication in use for body */
  HTTP_AUTH_MD5_SESS_INT,		/* MD5-session authentication in use for body */
  HTTP_AUTH_NEGOTIATE			/* GSSAPI authentication in use @since CUPS 1.3/OS X 10.5@ */
} http_auth_t;

typedef enum http_encoding_e		/**** HTTP transfer encoding values ****/
{
  HTTP_ENCODE_LENGTH,			/* Data is sent with Content-Length */
  HTTP_ENCODE_CHUNKED,			/* Data is chunked */
  HTTP_ENCODE_FIELDS			/* Sending HTTP fields */
} http_encoding_t;

typedef enum http_encryption_e		/**** HTTP encryption values ****/
{
  HTTP_ENCRYPT_IF_REQUESTED,		/* Encrypt if requested (TLS upgrade) */
  HTTP_ENCRYPT_NEVER,			/* Never encrypt */
  HTTP_ENCRYPT_REQUIRED,		/* Encryption is required (TLS upgrade) */
  HTTP_ENCRYPT_ALWAYS			/* Always encrypt (SSL) */
} http_encryption_t;

typedef enum http_field_e		/**** HTTP field names ****/
{
  HTTP_FIELD_UNKNOWN = -1,		/* Unknown field */
  HTTP_FIELD_ACCEPT_LANGUAGE,		/* Accept-Language field */
  HTTP_FIELD_ACCEPT_RANGES,		/* Accept-Ranges field */
  HTTP_FIELD_AUTHORIZATION,		/* Authorization field */
  HTTP_FIELD_CONNECTION,		/* Connection field */
  HTTP_FIELD_CONTENT_ENCODING,		/* Content-Encoding field */
  HTTP_FIELD_CONTENT_LANGUAGE,		/* Content-Language field */
  HTTP_FIELD_CONTENT_LENGTH,		/* Content-Length field */
  HTTP_FIELD_CONTENT_LOCATION,		/* Content-Location field */
  HTTP_FIELD_CONTENT_MD5,		/* Content-MD5 field */
  HTTP_FIELD_CONTENT_RANGE,		/* Content-Range field */
  HTTP_FIELD_CONTENT_TYPE,		/* Content-Type field */
  HTTP_FIELD_CONTENT_VERSION,		/* Content-Version field */
  HTTP_FIELD_DATE,			/* Date field */
  HTTP_FIELD_HOST,			/* Host field */
  HTTP_FIELD_IF_MODIFIED_SINCE,		/* If-Modified-Since field */
  HTTP_FIELD_IF_UNMODIFIED_SINCE,	/* If-Unmodified-Since field */
  HTTP_FIELD_KEEP_ALIVE,		/* Keep-Alive field */
  HTTP_FIELD_LAST_MODIFIED,		/* Last-Modified field */
  HTTP_FIELD_LINK,			/* Link field */
  HTTP_FIELD_LOCATION,			/* Location field */
  HTTP_FIELD_RANGE,			/* Range field */
  HTTP_FIELD_REFERER,			/* Referer field */
  HTTP_FIELD_RETRY_AFTER,		/* Retry-After field */
  HTTP_FIELD_TRANSFER_ENCODING,		/* Transfer-Encoding field */
  HTTP_FIELD_UPGRADE,			/* Upgrade field */
  HTTP_FIELD_USER_AGENT,		/* User-Agent field */
  HTTP_FIELD_WWW_AUTHENTICATE,		/* WWW-Authenticate field */
  HTTP_FIELD_MAX			/* Maximum field index */
} http_field_t;

typedef enum http_keepalive_e		/**** HTTP keep-alive values ****/
{
  HTTP_KEEPALIVE_OFF = 0,		/* No keep alive support */
  HTTP_KEEPALIVE_ON			/* Use keep alive */
} http_keepalive_t;

typedef enum http_state_e		/**** HTTP state values; states
					 **** are server-oriented...
					 ****/
{
  HTTP_WAITING,				/* Waiting for command */
  HTTP_OPTIONS,				/* OPTIONS command, waiting for blank line */
  HTTP_GET,				/* GET command, waiting for blank line */
  HTTP_GET_SEND,			/* GET command, sending data */
  HTTP_HEAD,				/* HEAD command, waiting for blank line */
  HTTP_POST,				/* POST command, waiting for blank line */
  HTTP_POST_RECV,			/* POST command, receiving data */
  HTTP_POST_SEND,			/* POST command, sending data */
  HTTP_PUT,				/* PUT command, waiting for blank line */
  HTTP_PUT_RECV,			/* PUT command, receiving data */
  HTTP_DELETE,				/* DELETE command, waiting for blank line */
  HTTP_TRACE,				/* TRACE command, waiting for blank line */
  HTTP_CLOSE,				/* CLOSE command, waiting for blank line */
  HTTP_STATUS				/* Command complete, sending status */
} http_state_t;

typedef enum http_status_e		/**** HTTP status codes ****/
{
  HTTP_ERROR = -1,			/* An error response from httpXxxx() */

  HTTP_CONTINUE = 100,			/* Everything OK, keep going... */
  HTTP_SWITCHING_PROTOCOLS,		/* HTTP upgrade to TLS/SSL */

  HTTP_OK = 200,			/* OPTIONS/GET/HEAD/POST/TRACE command was successful */
  HTTP_CREATED,				/* PUT command was successful */
  HTTP_ACCEPTED,			/* DELETE command was successful */
  HTTP_NOT_AUTHORITATIVE,		/* Information isn't authoritative */
  HTTP_NO_CONTENT,			/* Successful command, no new data */
  HTTP_RESET_CONTENT,			/* Content was reset/recreated */
  HTTP_PARTIAL_CONTENT,			/* Only a partial file was recieved/sent */

  HTTP_MULTIPLE_CHOICES = 300,		/* Multiple files match request */
  HTTP_MOVED_PERMANENTLY,		/* Document has moved permanently */
  HTTP_MOVED_TEMPORARILY,		/* Document has moved temporarily */
  HTTP_SEE_OTHER,			/* See this other link... */
  HTTP_NOT_MODIFIED,			/* File not modified */
  HTTP_USE_PROXY,			/* Must use a proxy to access this URI */

  HTTP_BAD_REQUEST = 400,		/* Bad request */
  HTTP_UNAUTHORIZED,			/* Unauthorized to access host */
  HTTP_PAYMENT_REQUIRED,		/* Payment required */
  HTTP_FORBIDDEN,			/* Forbidden to access this URI */
  HTTP_NOT_FOUND,			/* URI was not found */
  HTTP_METHOD_NOT_ALLOWED,		/* Method is not allowed */
  HTTP_NOT_ACCEPTABLE,			/* Not Acceptable */
  HTTP_PROXY_AUTHENTICATION,		/* Proxy Authentication is Required */
  HTTP_REQUEST_TIMEOUT,			/* Request timed out */
  HTTP_CONFLICT,			/* Request is self-conflicting */
  HTTP_GONE,				/* Server has gone away */
  HTTP_LENGTH_REQUIRED,			/* A content length or encoding is required */
  HTTP_PRECONDITION,			/* Precondition failed */
  HTTP_REQUEST_TOO_LARGE,		/* Request entity too large */
  HTTP_URI_TOO_LONG,			/* URI too long */
  HTTP_UNSUPPORTED_MEDIATYPE,		/* The requested media type is unsupported */
  HTTP_REQUESTED_RANGE,			/* The requested range is not satisfiable */
  HTTP_EXPECTATION_FAILED,		/* The expectation given in an Expect header field was not met */
  HTTP_UPGRADE_REQUIRED = 426,		/* Upgrade to SSL/TLS required */

  HTTP_SERVER_ERROR = 500,		/* Internal server error */
  HTTP_NOT_IMPLEMENTED,			/* Feature not implemented */
  HTTP_BAD_GATEWAY,			/* Bad gateway */
  HTTP_SERVICE_UNAVAILABLE,		/* Service is unavailable */
  HTTP_GATEWAY_TIMEOUT,			/* Gateway connection timed out */
  HTTP_NOT_SUPPORTED,			/* HTTP version not supported */

  HTTP_AUTHORIZATION_CANCELED = 1000,	/* User canceled authorization @since CUPS 1.4@ */
  HTTP_PKI_ERROR,			/* Error negotiating a secure connection @since CUPS 1.5/OS X 10.7@ */
  HTTP_WEBIF_DISABLED			/* Web interface is disabled @private@ */
} http_status_t;

typedef enum http_uri_status_e		/**** URI separation status @since CUPS 1.2@ ****/
{
  HTTP_URI_OVERFLOW = -8,		/* URI buffer for httpAssembleURI is too small */
  HTTP_URI_BAD_ARGUMENTS = -7,		/* Bad arguments to function (error) */
  HTTP_URI_BAD_RESOURCE = -6,		/* Bad resource in URI (error) */
  HTTP_URI_BAD_PORT = -5,		/* Bad port number in URI (error) */
  HTTP_URI_BAD_HOSTNAME = -4,		/* Bad hostname in URI (error) */
  HTTP_URI_BAD_USERNAME = -3,		/* Bad username in URI (error) */
  HTTP_URI_BAD_SCHEME = -2,		/* Bad scheme in URI (error) */
  HTTP_URI_BAD_URI = -1,		/* Bad/empty URI (error) */
  HTTP_URI_OK = 0,			/* URI decoded OK */
  HTTP_URI_MISSING_SCHEME,		/* Missing scheme in URI (warning) */
  HTTP_URI_UNKNOWN_SCHEME,		/* Unknown scheme in URI (warning) */
  HTTP_URI_MISSING_RESOURCE		/* Missing resource in URI (warning) */
} http_uri_status_t;

typedef enum http_uri_coding_e		/**** URI en/decode flags ****/
{
  HTTP_URI_CODING_NONE = 0,		/* Don't en/decode anything */
  HTTP_URI_CODING_USERNAME = 1,		/* En/decode the username portion */
  HTTP_URI_CODING_HOSTNAME = 2,		/* En/decode the hostname portion */
  HTTP_URI_CODING_RESOURCE = 4,		/* En/decode the resource portion */
  HTTP_URI_CODING_MOST = 7,		/* En/decode all but the query */
  HTTP_URI_CODING_QUERY = 8,		/* En/decode the query portion */
  HTTP_URI_CODING_ALL = 15		/* En/decode everything */
} http_uri_coding_t;

typedef enum http_version_e		/**** HTTP version numbers ****/
{
  HTTP_0_9 = 9,				/* HTTP/0.9 */
  HTTP_1_0 = 100,			/* HTTP/1.0 */
  HTTP_1_1 = 101			/* HTTP/1.1 */
} http_version_t;

typedef union _http_addr_u		/**** Socket address union, which
					 **** makes using IPv6 and other
					 **** address types easier and
					 **** more portable. @since CUPS 1.2/OS X 10.5@
					 ****/
{
  struct sockaddr	addr;		/* Base structure for family value */
  struct sockaddr_in	ipv4;		/* IPv4 address */
#ifdef AF_INET6
  struct sockaddr_in6	ipv6;		/* IPv6 address */
#endif /* AF_INET6 */
#ifdef AF_LOCAL
  struct sockaddr_un	un;		/* Domain socket file */
#endif /* AF_LOCAL */
  char			pad[256];	/* Padding to ensure binary compatibility */
} http_addr_t;

typedef struct http_addrlist_s		/**** Socket address list, which is
					 **** used to enumerate all of the
					 **** addresses that are associated
					 **** with a hostname. @since CUPS 1.2/OS X 10.5@
					 ****/
{
  struct http_addrlist_s *next;		/* Pointer to next address in list */
  http_addr_t		addr;		/* Address */
} http_addrlist_t;

typedef struct _http_s http_t;		/**** HTTP connection type ****/

typedef struct http_credential_s	/**** HTTP credential data @since CUPS 1.5/OS X 10.7@ ****/
{
  void		*data;			/* Pointer to credential data */
  size_t	datalen;		/* Credential length */
} http_credential_t;

typedef int (*http_timeout_cb_t)(http_t *http, void *user_data);
					/**** HTTP timeout callback @since CUPS 1.5/OS X 10.7@ ****/



/*
 * Prototypes...
 */

extern void		httpBlocking(http_t *http, int b);
extern int		httpCheck(http_t *http);
extern void		httpClearFields(http_t *http);
extern void		httpClose(http_t *http);
extern http_t		*httpConnect(const char *host, int port);
extern http_t		*httpConnectEncrypt(const char *host, int port,
			                    http_encryption_t encryption);
extern int		httpDelete(http_t *http, const char *uri);
extern int		httpEncryption(http_t *http, http_encryption_t e);
extern int		httpError(http_t *http);
extern void		httpFlush(http_t *http);
extern int		httpGet(http_t *http, const char *uri);
extern char		*httpGets(char *line, int length, http_t *http);
extern const char	*httpGetDateString(time_t t);
extern time_t		httpGetDateTime(const char *s);
extern const char	*httpGetField(http_t *http, http_field_t field);
extern struct hostent	*httpGetHostByName(const char *name);
extern char		*httpGetSubField(http_t *http, http_field_t field,
			                 const char *name, char *value);
extern int		httpHead(http_t *http, const char *uri);
extern void		httpInitialize(void);
extern int		httpOptions(http_t *http, const char *uri);
extern int		httpPost(http_t *http, const char *uri);
extern int		httpPrintf(http_t *http, const char *format, ...)
			__attribute__ ((__format__ (__printf__, 2, 3)));
extern int		httpPut(http_t *http, const char *uri);
extern int		httpRead(http_t *http, char *buffer, int length) _CUPS_DEPRECATED;
extern int		httpReconnect(http_t *http);
extern void		httpSeparate(const char *uri, char *method,
			             char *username, char *host, int *port,
				     char *resource) _CUPS_DEPRECATED;
extern void		httpSetField(http_t *http, http_field_t field,
			             const char *value);
extern const char	*httpStatus(http_status_t status);
extern int		httpTrace(http_t *http, const char *uri);
extern http_status_t	httpUpdate(http_t *http);
extern int		httpWrite(http_t *http, const char *buffer, int length) _CUPS_DEPRECATED;
extern char		*httpEncode64(char *out, const char *in) _CUPS_DEPRECATED;
extern char		*httpDecode64(char *out, const char *in) _CUPS_DEPRECATED;
extern int		httpGetLength(http_t *http) _CUPS_DEPRECATED;
extern char		*httpMD5(const char *, const char *, const char *,
			         char [33]);
extern char		*httpMD5Final(const char *, const char *, const char *,
			              char [33]);
extern char		*httpMD5String(const unsigned char *, char [33]);

/**** New in CUPS 1.1.19 ****/
extern void		httpClearCookie(http_t *http) _CUPS_API_1_1_19;
extern const char	*httpGetCookie(http_t *http) _CUPS_API_1_1_19;
extern void		httpSetCookie(http_t *http, const char *cookie) _CUPS_API_1_1_19;
extern int		httpWait(http_t *http, int msec) _CUPS_API_1_1_19;

/**** New in CUPS 1.1.21 ****/
extern char		*httpDecode64_2(char *out, int *outlen, const char *in) _CUPS_API_1_1_21;
extern char		*httpEncode64_2(char *out, int outlen, const char *in,
			                int inlen) _CUPS_API_1_1_21;
extern void		httpSeparate2(const char *uri,
			              char *method, int methodlen,
			              char *username, int usernamelen,
				      char *host, int hostlen, int *port,
				      char *resource, int resourcelen) _CUPS_DEPRECATED;

/**** New in CUPS 1.2/OS X 10.5 ****/
extern int		httpAddrAny(const http_addr_t *addr) _CUPS_API_1_2;
extern http_addrlist_t	*httpAddrConnect(http_addrlist_t *addrlist, int *sock) _CUPS_API_1_2;
extern int		httpAddrEqual(const http_addr_t *addr1,
			              const http_addr_t *addr2) _CUPS_API_1_2;
extern void		httpAddrFreeList(http_addrlist_t *addrlist) _CUPS_API_1_2;
extern http_addrlist_t	*httpAddrGetList(const char *hostname, int family,
			                 const char *service) _CUPS_API_1_2;
extern int		httpAddrLength(const http_addr_t *addr) _CUPS_API_1_2;
extern int		httpAddrLocalhost(const http_addr_t *addr) _CUPS_API_1_2;
extern char		*httpAddrLookup(const http_addr_t *addr,
                                        char *name, int namelen) _CUPS_API_1_2;
extern char		*httpAddrString(const http_addr_t *addr,
			                char *s, int slen) _CUPS_API_1_2;
extern http_uri_status_t httpAssembleURI(http_uri_coding_t encoding,
			                 char *uri, int urilen,
			        	 const char *scheme,
					 const char *username,
					 const char *host, int port,
					 const char *resource) _CUPS_API_1_2;
extern http_uri_status_t httpAssembleURIf(http_uri_coding_t encoding,
			                  char *uri, int urilen,
			        	  const char *scheme,
					  const char *username,
					  const char *host, int port,
					  const char *resourcef, ...) _CUPS_API_1_2;
extern int		httpFlushWrite(http_t *http) _CUPS_API_1_2;
extern int		httpGetBlocking(http_t *http) _CUPS_API_1_2;
extern const char	*httpGetDateString2(time_t t, char *s, int slen) _CUPS_API_1_2;
extern int		httpGetFd(http_t *http) _CUPS_API_1_2;
extern const char	*httpGetHostname(http_t *http, char *s, int slen) _CUPS_API_1_2;
extern off_t		httpGetLength2(http_t *http) _CUPS_API_1_2;
extern http_status_t	httpGetStatus(http_t *http) _CUPS_API_1_2;
extern char		*httpGetSubField2(http_t *http, http_field_t field,
			                  const char *name, char *value,
					  int valuelen) _CUPS_API_1_2;
extern ssize_t		httpRead2(http_t *http, char *buffer, size_t length) _CUPS_API_1_2;
extern http_uri_status_t httpSeparateURI(http_uri_coding_t decoding,
			                 const char *uri,
			        	 char *scheme, int schemelen,
			        	 char *username, int usernamelen,
					 char *host, int hostlen, int *port,
					 char *resource, int resourcelen) _CUPS_API_1_2;
extern void		httpSetExpect(http_t *http, http_status_t expect) _CUPS_API_1_2;
extern void		httpSetLength(http_t *http, size_t length) _CUPS_API_1_2;
extern ssize_t		httpWrite2(http_t *http, const char *buffer,
			           size_t length) _CUPS_API_1_2;

/**** New in CUPS 1.3/OS X 10.5 ****/
extern char		*httpGetAuthString(http_t *http) _CUPS_API_1_3;
extern void		httpSetAuthString(http_t *http, const char *scheme,
			                  const char *data) _CUPS_API_1_3;

/**** New in CUPS 1.5/OS X 10.7 ****/
extern int		httpAddCredential(cups_array_t *credentials,
			                  const void *data, size_t datalen)
					  _CUPS_API_1_5;
extern int		httpCopyCredentials(http_t *http,
					    cups_array_t **credentials)
					    _CUPS_API_1_5;
extern void		httpFreeCredentials(cups_array_t *certs) _CUPS_API_1_5;
extern int		httpSetCredentials(http_t *http, cups_array_t *certs)
					   _CUPS_API_1_5;
extern void		httpSetTimeout(http_t *http, double timeout,
			               http_timeout_cb_t cb, void *user_data)
			               _CUPS_API_1_5;

/**** New in CUPS 1.6/OS X 10.8 ****/
extern http_addrlist_t	*httpAddrConnect2(http_addrlist_t *addrlist, int *sock,
			                  int msec, int *cancel)
			                  _CUPS_API_1_6;
extern http_state_t	httpGetState(http_t *http) _CUPS_API_1_6;
extern http_version_t	httpGetVersion(http_t *http) _CUPS_API_1_6;
extern int		httpReconnect2(http_t *http, int msec, int *cancel)
			               _CUPS_API_1_6;


/*
 * C++ magic...
 */

#  ifdef __cplusplus
}
#  endif /* __cplusplus */
#endif /* !_CUPS_HTTP_H_ */

/*
 * End of "$Id: http.h 7026 2007-10-19 00:57:45Z mike $".
 */
