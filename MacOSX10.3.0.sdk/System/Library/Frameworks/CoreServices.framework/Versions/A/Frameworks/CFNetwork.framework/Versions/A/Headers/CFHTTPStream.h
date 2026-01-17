/*
     File:       CFNetwork/CFHTTPStream.h
 
     Contains:   CoreFoundation Network HTTP streams header
 
     Version:    CFNetwork-71.2~1
 
     Copyright:  © 2001-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __CFHTTPSTREAM__
#define __CFHTTPSTREAM__

#ifndef __CFSTREAM__
#include <CoreFoundation/CFStream.h>
#endif

#ifndef __CFHTTPMESSAGE__
#include <CFNetwork/CFHTTPMessage.h>
#endif




#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if PRAGMA_ENUM_ALWAYSINT
    #pragma enumsalwaysint on
#endif

/*
 *  kCFStreamErrorDomainHTTP
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const SInt32 kCFStreamErrorDomainHTTP                         AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;
enum CFStreamErrorHTTP {
  kCFStreamErrorHTTPParseFailure = -1,
  kCFStreamErrorHTTPRedirectionLoop = -2,
  kCFStreamErrorHTTPBadURL      = -3
};
typedef enum CFStreamErrorHTTP CFStreamErrorHTTP;

/* Value is a CFHTTPMessage with 0 bytes data. */
/*
 *  kCFStreamPropertyHTTPResponseHeader
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kCFStreamPropertyHTTPResponseHeader         AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;
/* Value is the CFURL from the final request; will only differ from the URL in the original request if an autoredirection has occurred. */
/*
 *  kCFStreamPropertyHTTPFinalURL
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kCFStreamPropertyHTTPFinalURL               AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
/**************************************/
/*Set-able properties on HTTP streams */
/**************************************/
/* HTTP proxy information is set the same way as SOCKS proxies (see CFSocketStream.h).
   Call CFReadStreamSetProperty() passing an HTTP stream and the property kCFStreamPropertyHTTPProxy.  
   The value should be a CFDictionary that includes at least one Host/Port pair from the keys below.  
   The dictionary returned by SystemConfiguration.framework can also be passed directly as the value */
/*
 *  kCFStreamPropertyHTTPProxy
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kCFStreamPropertyHTTPProxy                  AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
/*
 *  kCFStreamPropertyHTTPProxyHost
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kCFStreamPropertyHTTPProxyHost              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
/* matches kSCPropNetProxiesHTTPProxy; value should be a CFString*/
/*
 *  kCFStreamPropertyHTTPProxyPort
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kCFStreamPropertyHTTPProxyPort              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
/* matches kSCPropNetProxiesHTTPPort; value should be a CFNumber */
/*
 *  kCFStreamPropertyHTTPSProxyHost
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kCFStreamPropertyHTTPSProxyHost             AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
/* matches kSCPropNetProxiesHTTPSProxy; value should be a CFString */
/*
 *  kCFStreamPropertyHTTPSProxyPort
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kCFStreamPropertyHTTPSProxyPort             AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
/* matches kSCPropNetProxiesHTTPSPort; value should be a CFNumber */
/* Value should be a CFBoolean */
/*
 *  kCFStreamPropertyHTTPShouldAutoredirect
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kCFStreamPropertyHTTPShouldAutoredirect     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
/* Value should be a CFBoolean.  If this property is set to true, an HTTP stream will look for an appropriate extant persistent connection to use, and if it finds none, will try to create one.  */
/*
 *  kCFStreamPropertyHTTPAttemptPersistentConnection
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kCFStreamPropertyHTTPAttemptPersistentConnection AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
/* Value is a CFNumber; this property can only be retrieved, not set.  The number returned is the number of bytes from the body of the request that have been written to the underlying socket */
/*
 *  kCFStreamPropertyHTTPRequestBytesWrittenCount
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kCFStreamPropertyHTTPRequestBytesWrittenCount AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
/*********************/
/* Creation routines */
/*********************/
/* Creates a read stream for the response to the given request; when the stream is opened,
  it will begin transmitting the request.  The bytes returned are the pure body bytes; the response header has been parsed off.
  To retrieve the response header, ask for kCFStreamPropertyHTTPResponseHeader, above, any time after the first bytes arrive on 
  the stream (or when stream end is reported, if there are no data bytes).
*/
/*
 *  CFReadStreamCreateForHTTPRequest()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFReadStreamRef 
CFReadStreamCreateForHTTPRequest(
  CFAllocatorRef     alloc,
  CFHTTPMessageRef   request)                                 AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/* Creates a read stream for the response to the given requestHeaders plus requestBody.  Use in preference to
  CFReadStreamCreateForHTTPRequest() when the body of the request is larger than you wish to be resident in memory.  Note that 
  because streams cannot be reset, read streams created this way cannot have autoredirection enabled.  If the Content-Length 
  header is set in requestHeaders, it is assumed that the caller got the length right and that requestBody will report 
  end-of-stream after precisely Content-Length bytes have been read from it.  If the Content-Length header is not set, the 
  chunked transfer-encoding will be added to requestHeaders, and bytes read from requestBody will be transmitted chunked.
  The body of requestHeaders is ignored.
*/
/*
 *  CFReadStreamCreateForStreamedHTTPRequest()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFReadStreamRef 
CFReadStreamCreateForStreamedHTTPRequest(
  CFAllocatorRef     alloc,
  CFHTTPMessageRef   requestHeaders,
  CFReadStreamRef    requestBody)                             AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Deprecated - Use the properties kCFStreamPropertyHTTPShouldAutoredirect and kCFStreamPropertyHTTPProxy above instead */
/*
 *  CFHTTPReadStreamSetRedirectsAutomatically()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
CFHTTPReadStreamSetRedirectsAutomatically(
  CFReadStreamRef   httpStream,
  Boolean           shouldAutoRedirect)                       AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  CFHTTPReadStreamSetProxy()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
CFHTTPReadStreamSetProxy(
  CFReadStreamRef   httpStream,
  CFStringRef       proxyHost,
  CFIndex           proxyPort)                                AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;



#if PRAGMA_ENUM_ALWAYSINT
    #pragma enumsalwaysint reset
#endif

#ifdef __cplusplus
}
#endif

#endif /* __CFHTTPSTREAM__ */

