/* CFSocketStream.h
   Copyright 2000, Apple, Inc.  All rights reserved.
*/

#if !defined(__CFNETWORK_CFSOCKETSTREAM__)
#define __CFNETWORK_CFSOCKETSTREAM__ 1

#include <CoreFoundation/CFStream.h>

#if defined(__cplusplus)
extern "C" {
#endif


/* Secure stream support */

extern const int kCFStreamErrorDomainSSL;

/*
** Secure streams usage
**
** To set a stream to be secure, call CFReadStreamSetProperty or CFWriteStreamSetProperty
** with the property name set to kCFStreamPropertySocketSecurityLevel and the value being one
** of the following values.  Streams may set a security level after open in order to allow
** on-the-fly securing of a stream.
*/

CF_EXPORT const CFStringRef kCFStreamPropertySocketSecurityLevel; /*Value should be one of the following strings */
CF_EXPORT const CFStringRef kCFStreamSocketSecurityLevelNone;
CF_EXPORT const CFStringRef kCFStreamSocketSecurityLevelSSLv2;
CF_EXPORT const CFStringRef kCFStreamSocketSecurityLevelSSLv3;
CF_EXPORT const CFStringRef kCFStreamSocketSecurityLevelTLSv1;
CF_EXPORT const CFStringRef kCFStreamSocketSecurityLevelNegotiatedSSL; /* TLS or SSL with fallback to lower versions; this is what HTTPS does, for instance */



/* SOCKS proxy support */

CF_EXPORT const int kCFStreamErrorDomainSOCKS;	/* SOCKS proxy error domain */


CF_INLINE
SInt32 CFSocketStreamSOCKSGetErrorSubdomain(CFStreamError* error) {
    return ((error->domain >> 16) & 0x0000FFFF);
}

CF_INLINE
SInt32 CFSocketStreamSOCKSGetError(CFStreamError* error) {
    return (error->domain & 0x0000FFFF);
}


enum {
	kCFStreamErrorSOCKSSubDomainNone = 0,		/* Error code is a general SOCKS error */
	kCFStreamErrorSOCKSSubDomainVersionCode,	/* Error code is the version of SOCKS which the server wishes to use */
	kCFStreamErrorSOCKS4SubDomainResponse,		/* Error code is the status code returned by the server */
	kCFStreamErrorSOCKS5SubDomainUserPass,		/* Error code is the status code that the server returned */
	kCFStreamErrorSOCKS5SubDomainMethod,		/* Error code is the server's desired negotiation method */
    kCFStreamErrorSOCKS5SubDomainResponse		/* Error code is the response code that the server returned in reply to the connection request */
};

enum {
// kCFStreamErrorSOCKSNoSubDomain
	kCFStreamErrorSOCKS5BadResponseAddr = 1,
	kCFStreamErrorSOCKS5BadState,
	kCFStreamErrorSOCKSUnknownClientVersion,

// kCFStreamErrorSOCKS4ResponseCode:
	kCFStreamErrorSOCKS4RequestFailed = 91,	/* request rejected or failed */
	kCFStreamErrorSOCKS4IdentdFailed = 92,	/* request rejected because SOCKS server cannot connect to identd on the client */
	kCFStreamErrorSOCKS4IdConflict = 93,	/* request rejected because the client program and identd report different user-ids */

// kCFStreamErrorSOCKS5MethodCode
	kSOCKS5NoAcceptableMethod = 0xFF	/* other values indicate the server's desired method */
};


/*
** SOCKS Proxy usage
**
** To set a stream to use a SOCKS proxy, call CFReadStreamSetProperty or CFWriteStreamSetProperty
** with the property name set to kCFStreamPropertySOCKSProxy and the value being a dictionary
** with at least the following two keys: kCFStreamPropertySOCKSProxyHost and kCFStreamPropertySOCKSProxyPort.
** The dictionary returned by SystemConfiguration for SOCKS proxies will work without alteration.
**
** The key kCFStreamPropertySOCKSProxyHost should contain a CFStringRef value representing
** the SOCKS proxy host.  The key kCFStreamPropertySOCKSProxyPort should contain a CFNumberRef which
** itself is of type kCFNumberSInt32Type.  This value should represent the port on which the proxy
** is listening.
**
** By default, SOCKS5 will be used unless there is a kCFStreamPropertySOCKSVersion
** key in the dictionary.  Its value must be kCFStreamSocketSOCKSVersion4 or
** kCFStreamSocketSOCKSVersion5 to set SOCKS4 or SOCKS5, respectively.
**
** To set a user name and/or password, if required, the dictionary must contain the key(s)
** kCFStreamPropertySOCKSUser and/or kCFStreamPropertySOCKSPassword with the value being
** the user's name as a CFStringRef and/or the user's password as a CFStringRef, respectively.
**
** kCFStreamPropertySOCKSProxy can be set through CFReadStreamSetProperty or
** CFWriteStreamSetProperty.  The property can be copied through CFReadStreamCopyProperty
** or CFWriteStreamCopyProperty.
*/
CF_EXPORT const CFStringRef kCFStreamPropertySOCKSProxy;
CF_EXPORT const CFStringRef kCFStreamPropertySOCKSProxyHost;	/* Defined to match kSCPropNetProxiesSOCKSProxy */
CF_EXPORT const CFStringRef kCFStreamPropertySOCKSProxyPort;	/* Defined to match kSCPropNetProxiesSOCKSPort */
CF_EXPORT const CFStringRef kCFStreamPropertySOCKSVersion;
CF_EXPORT const CFStringRef kCFStreamSocketSOCKSVersion4;
CF_EXPORT const CFStringRef kCFStreamSocketSOCKSVersion5;
CF_EXPORT const CFStringRef kCFStreamPropertySOCKSUser;
CF_EXPORT const CFStringRef kCFStreamPropertySOCKSPassword;

/*
** Set the value to kCFBooleanTrue if the stream should
** close and release the underlying native socket when
** the stream is released.  Set the value to kCFBooleanFalse
** to keep the native socket from closing and releasing
** when the stream is released.
**
** If the stream was created with a native socket, the
** default property setting on the stream is kCFBooleanFalse.
**
** The kCFStreamPropertyShouldCloseNativeSocket can be set through CFReadStreamSetProperty or
** CFWriteStreamSetProperty.  The property can be copied through CFReadStreamCopyProperty
** or CFWriteStreamCopyProperty.
*/
CF_EXPORT const CFStringRef kCFStreamPropertyShouldCloseNativeSocket;


/*
** DEPRECATED
** 
** These enum values and CFSocketStreamPairSetSecurityProtocol have been deprecated
** in favor of CFReadStreamSetProperty and CFWriteStreamSetProperty with the
** previously mentioned property and values.
**
*/ 
typedef enum {
    kCFStreamSocketSecurityNone = 0,	/* DEPRECATED */
    kCFStreamSocketSecuritySSLv2,		/* DEPRECATED */
    kCFStreamSocketSecuritySSLv3,		/* DEPRECATED */
    kCFStreamSocketSecuritySSLv23,		/* DEPRECATED Use SSLv3 if available; if not, try SSLv2 */
    kCFStreamSocketSecurityTLSv1		/* DEPRECATED */
} CFStreamSocketSecurityProtocol;		/* DEPRECATED */

/*
** DEPRECATED
** 
** CFSocketStreamPairSetSecurityProtocol has been deprecated in favor of
** CFReadStreamSetProperty and CFWriteStreamSetProperty with the previously
** mentioned property and values.
*/
CF_EXPORT
Boolean CFSocketStreamPairSetSecurityProtocol(CFReadStreamRef socketReadStream, CFWriteStreamRef socketWriteStream, CFStreamSocketSecurityProtocol securityProtocol);


#if defined(__cplusplus)
}
#endif

#endif /* ! __CFNETWORK_CFSOCKETSTREAM__ */
