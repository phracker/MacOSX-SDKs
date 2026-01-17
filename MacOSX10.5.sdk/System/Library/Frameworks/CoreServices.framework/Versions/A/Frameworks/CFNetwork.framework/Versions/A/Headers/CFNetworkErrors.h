/*
     File:       CFNetwork/CFNetworkErrors.h
 
     Contains:   CFNetwork error header
 
     Copyright:  Copyright (c) 2006-2008, Apple Inc. All rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __CFNETWORKERRORS__
#define __CFNETWORKERRORS__

#ifndef __CFNETWORKDEFS__
#include <CFNetwork/CFNetworkDefs.h>
#endif

#ifndef __CFSTRING__
#include <CoreFoundation/CFString.h>
#endif



#include <Availability.h>

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
 *  kCFErrorDomainCFNetwork
 *  
 *  Discussion:
 *    Error domain for all errors originating in CFNetwork. Error codes
 *    may be interpreted using the list below.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFErrorDomainCFNetwork                     __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*
 *  kCFErrorDomainWinSock
 *  
 *  Discussion:
 *    On Windows, errors originating from WinSock are represented using
 *    this domain.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFErrorDomainWinSock                       __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);


/*
 *  CFNetworkErrors
 *  
 *  Discussion:
 *    The list of all error codes returned under the error domain
 *    kCFErrorDomainCFNetwork
 */
enum CFNetworkErrors {
  kCFHostErrorHostNotFound      = 1,
  kCFHostErrorUnknown           = 2,    /* Query the kCFGetAddrInfoFailureKey to get the value returned from getaddrinfo; lookup in netdb.h*/
                                        /* SOCKS errors; in all cases you may query kCFSOCKSStatusCodeKey to recover the status code returned by the server*/
  kCFSOCKSErrorUnknownClientVersion = 100,
  kCFSOCKSErrorUnsupportedServerVersion = 101, /* Query the kCFSOCKSVersionKey to find the version requested by the server*/
                                        /* SOCKS4-specific errors*/
  kCFSOCKS4ErrorRequestFailed   = 110,  /* request rejected or failed by the server*/
  kCFSOCKS4ErrorIdentdFailed    = 111,  /* request rejected because SOCKS server cannot connect to identd on the client*/
  kCFSOCKS4ErrorIdConflict      = 112,  /* request rejected because the client program and identd report different user-ids*/
  kCFSOCKS4ErrorUnknownStatusCode = 113, /* SOCKS5-specific errors*/
  kCFSOCKS5ErrorBadState        = 120,
  kCFSOCKS5ErrorBadResponseAddr = 121,
  kCFSOCKS5ErrorBadCredentials  = 122,
  kCFSOCKS5ErrorUnsupportedNegotiationMethod = 123, /* query kCFSOCKSNegotiationMethodKey to find the method requested*/
  kCFSOCKS5ErrorNoAcceptableMethod = 124, /* Errors originating from CFNetServices*/
  kCFNetServiceErrorUnknown     = -72000L,
  kCFNetServiceErrorCollision   = -72001L,
  kCFNetServiceErrorNotFound    = -72002L,
  kCFNetServiceErrorInProgress  = -72003L,
  kCFNetServiceErrorBadArgument = -72004L,
  kCFNetServiceErrorCancel      = -72005L,
  kCFNetServiceErrorInvalid     = -72006L,
  kCFNetServiceErrorTimeout     = -72007L,
  kCFNetServiceErrorDNSServiceFailure = -73000L, /* An error from DNS discovery; look at kCFDNSServiceFailureKey to get the error number and interpret using dns_sd.h*/
                                        /* FTP errors; query the kCFFTPStatusCodeKey to get the status code returned by the server*/
  kCFFTPErrorUnexpectedStatusCode = 200, /* HTTP errors*/
  kCFErrorHTTPAuthenticationTypeUnsupported = 300,
  kCFErrorHTTPBadCredentials    = 301,
  kCFErrorHTTPConnectionLost    = 302,
  kCFErrorHTTPParseFailure      = 303,
  kCFErrorHTTPRedirectionLoopDetected = 304,
  kCFErrorHTTPBadURL            = 305,
  kCFErrorHTTPProxyConnectionFailure = 306,
  kCFErrorHTTPBadProxyCredentials = 307,
  kCFErrorPACFileError          = 308
};
typedef enum CFNetworkErrors CFNetworkErrors;


/* Keys used by CFNetwork to pass additional error information back to the user within CFError's userInfo dictionary */
/*
 *  kCFGetAddrInfoFailureKey
 *  
 *  Discussion:
 *    When an error of kCFHostErrorUnknown is returned, this key's
 *    value is set to a CFNumber containing the raw error value
 *    returned by getaddrinfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFGetAddrInfoFailureKey                    __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*
 *  kCFSOCKSStatusCodeKey
 *  
 *  Discussion:
 *    When a SOCKS failure has occurred, this key's value is set to a
 *    CFString containing the status value returned by the SOCKS server.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFSOCKSStatusCodeKey                       __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*
 *  kCFSOCKSVersionKey
 *  
 *  Discussion:
 *    When an error of kCFSOCKSErrorUnsupportedServerVersion is
 *    returned, this key's value is set to a CFString containing the
 *    version number requested by the server.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFSOCKSVersionKey                          __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*
 *  kCFSOCKSNegotiationMethodKey
 *  
 *  Discussion:
 *    When an error of kCFSOCKS5ErrorUnsupportedNegotiationMethod is
 *    returned, this key's value is set to a CFString containing the
 *    negotiation method requested by the server.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFSOCKSNegotiationMethodKey                __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*
 *  kCFDNSServiceFailureKey
 *  
 *  Discussion:
 *    When an error of kCFNetServicesErrorDNSServiceFailure is
 *    returned, this key's value is set to a CFNumber containing the
 *    value returned from DNS; interret it using the values dns_sd.h
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFDNSServiceFailureKey                     __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*
 *  kCFFTPStatusCodeKey
 *  
 *  Discussion:
 *    When an error of kCFFTPErrorUnexpectedStatusCode is returned,
 *    this key's value is set to a CFString containing the status code
 *    returned by the server
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFFTPStatusCodeKey                         __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

#if PRAGMA_ENUM_ALWAYSINT
    #pragma enumsalwaysint reset
#endif

#ifdef __cplusplus
}
#endif

#endif /* __CFNETWORKERRORS__ */

