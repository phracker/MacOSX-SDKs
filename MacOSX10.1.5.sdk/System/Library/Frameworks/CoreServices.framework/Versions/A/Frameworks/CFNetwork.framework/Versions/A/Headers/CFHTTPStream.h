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

/* Properties that can be retrieved from HTTP streams */
CF_EXPORT
const CFStringRef kCFStreamPropertyHTTPResponseHeader;  /* Value is a CFHTTPMessage with 0 bytes data. */

CF_EXPORT
CFReadStreamRef CFReadStreamCreateForHTTPRequest(CFAllocatorRef alloc, CFHTTPMessageRef request);

CF_EXPORT
void CFHTTPReadStreamSetRedirectsAutomatically(CFReadStreamRef httpStream, Boolean shouldAutoRedirect);

CF_EXPORT
void CFHTTPReadStreamSetProxy(CFReadStreamRef httpStream, CFStringRef proxyHost, CFIndex proxyPort); 

#if defined(__cplusplus)
}
#endif

#endif /* ! __CFNETWORK_CFHTTPSTREAM__ */

