/* CFHTTPStream.h
   Copyright 2000, Apple, Inc.  All rights reserved.
*/

#if !defined(__CFNETWORK_CFHTTPSTREAM__)
#define __CFNETWORK_CFHTTPSTREAM__ 1

#include <CoreFoundation/CFStream.h>
#include <CFNetwork/CFHTTPMessage.h>

#if defined(__cplusplus)
extern "C" {
#endif

CF_EXPORT 
const SInt32 kCFStreamErrorDomainHTTP;

typedef enum {
    kCFStreamErrorHTTPParseFailure = -1,
    kCFStreamErrorHTTPRedirectionLoop = -2, 
    kCFStreamErrorHTTPBadURL = -3
} CFStreamErrorHTTP;

/* Get-able properties on HTTP streams */

/* Value is a CFHTTPMessage with 0 bytes data. */
CF_EXPORT
const CFStringRef kCFStreamPropertyHTTPResponseHeader;  

/* Value is the CFURL from the final request; will only differ from the URL in the original request if an autoredirection has occurred. */
CF_EXPORT 
const CFStringRef kCFStreamPropertyHTTPFinalURL;  

/*Set-able properties on HTTP streams */

/* HTTP proxy information is set the same way as SOCKS proxies (see CFSocketStream.h).
   Call CFReadStreamSetProperty() passing an HTTP stream and the property kCFStreamPropertyHTTPProxy.  
   The value should be a CFDictionary that includes at least one Host/Port pair from the keys below.  
   The dictionary returned by SystemConfiguration.framework can also be passed directly as the value */
CF_EXPORT const CFStringRef kCFStreamPropertyHTTPProxy;

CF_EXPORT const CFStringRef kCFStreamPropertyHTTPProxyHost; /* matches kSCPropNetProxiesHTTPProxy; value should be a CFString*/
CF_EXPORT const CFStringRef kCFStreamPropertyHTTPProxyPort; /* matches kSCPropNetProxiesHTTPPort; value should be a CFNumber */
CF_EXPORT const CFStringRef kCFStreamPropertyHTTPSProxyHost; /* matches kSCPropNetProxiesHTTPSProxy; value should be a CFString */
CF_EXPORT const CFStringRef kCFStreamPropertyHTTPSProxyPort; /* matches kSCPropNetProxiesHTTPSPort; value should be a CFNumber */


/* Value should be a CFBoolean */
CF_EXPORT 
const CFStringRef kCFStreamPropertyHTTPShouldAutoredirect; 

/* Value should be a CFBoolean.  If this property is set to true, an HTTP stream will look for an appropriate extant persistent connection to use, and if it finds none, will try to create one.  */
CF_EXPORT 
const CFStringRef kCFStreamPropertyHTTPAttemptPersistentConnection; 

/* Creation routines */

/* Creates a read stream for the response to the given request; when the stream is opened, it will begin transmitting the request.  The bytes returned are the pure body bytes; the response header has been parsed off.  To retrieve the response header, ask for kCFStreamPropertyHTTPResponseHeader, above, any time after the first bytes arrive on the stream (or when stream end is reported, if there are no data bytes). */
CF_EXPORT
CFReadStreamRef CFReadStreamCreateForHTTPRequest(CFAllocatorRef alloc, CFHTTPMessageRef request);

/*Creates a read stream for the response to the given requestHeaders plus requestBody.  Use in preference to CFReadStreamCreateForHTTPRequest() when the body of the request is larger than you wish to be resident in memory.  Note that because streams cannot be reset, read streams created this way cannot have autoredirection enabled.  If the Content-Length header is set in requestHeaders, it is assumed that the caller got the length right and that requestBody will report end-of-stream after precisely Content-Length bytes have been read from it.  If the Content-Length header is not set, the chunked transfer-encoding will be added to requestHeaders, and bytes read from requestBody will be transmitted chunked. The body of requestHeaders is ignored. */
CF_EXPORT
CFReadStreamRef CFReadStreamCreateForStreamedHTTPRequest(CFAllocatorRef alloc, CFHTTPMessageRef requestHeaders, CFReadStreamRef requestBody);

CF_EXPORT
void CFHTTPReadStreamSetRedirectsAutomatically(CFReadStreamRef httpStream, Boolean shouldAutoRedirect);

CF_EXPORT
void CFHTTPReadStreamSetProxy(CFReadStreamRef httpStream, CFStringRef proxyHost, CFIndex proxyPort); 

#if defined(__cplusplus)
}
#endif

#endif /* ! __CFNETWORK_CFHTTPSTREAM__ */

