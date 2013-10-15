/*
	 File:	   CFNetwork/CFHTTPStream.h
 
	 Contains:   CoreFoundation Network HTTP streams header
 
	 Copyright:  Copyright (c) 2001-2008 Apple Inc. All rights reserved.
 
	 Bugs?:	  For bug reports, consult the following page on
				 the World Wide Web:
 
					 http://developer.apple.com/bugreporter/
 
*/
#ifndef __CFHTTPSTREAM__
#define __CFHTTPSTREAM__

#ifndef __CFNETWORKDEFS__
#include <CFNetwork/CFNetworkDefs.h>
#endif

#ifndef __CFSTREAM__
#include <CoreFoundation/CFStream.h>
#endif

#ifndef __CFHTTPMESSAGE__
#include <CFNetwork/CFHTTPMessage.h>
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
 *  kCFStreamErrorDomainHTTP
 *  
 *  Discussion:
 *	Result code returned by HTTP server
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.1 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT const SInt32 kCFStreamErrorDomainHTTP						 __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_2_0);

/*
 *  CFStreamErrorHTTP
 *  
 *  Discussion:
 *	Errors from the kCFStreamErrorDomainHTTP domain.
 */
enum CFStreamErrorHTTP {

  /*
   * Could not parse the request/response.
   */
  kCFStreamErrorHTTPParseFailure = -1,

  /*
   * A loop was detected during redirection.
   */
  kCFStreamErrorHTTPRedirectionLoop = -2,

  /*
   * Could not retreive url for request/response.
   */
  kCFStreamErrorHTTPBadURL	  = -3
};
typedef enum CFStreamErrorHTTP CFStreamErrorHTTP;

/*
 *  kCFStreamPropertyHTTPResponseHeader
 *  
 *  Discussion:
 *	Stream property key, for copy operations. Value is a
 *	CFHTTPMessage with 0 bytes data.
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.1 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyHTTPResponseHeader		 __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_2_0);


/*
 *  kCFStreamPropertyHTTPFinalURL
 *  
 *  Discussion:
 *	Stream property key, for copy operations. The response header
 *	value is the CFURL from the final request; will only differ from
 *	the URL in the original request if an autoredirection has
 *	occurred.
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.2 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyHTTPFinalURL			   __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);

/*
 *  kCFStreamPropertyHTTPFinalRequest
 *  
 *  Discussion:
 *	Stream property key, for copy operations. The value is the
 *	CFHTTPMessage transmitted by the stream, after all modifications
 *	(such as for authentication, connection policy, or redirection)
 *	have been made.
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.5 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyHTTPFinalRequest		   __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*
 *  kCFStreamPropertyHTTPProxy
 *  
 *  Discussion:
 *	Stream property key, for both set and copy operations. The value
 *	is a CFDictionary. HTTP proxy information is set the same way as
 *	SOCKS proxies (see CFSocketStream.h). Call
 *	CFReadStreamSetProperty() passing an HTTP stream and the property
 *	kCFStreamPropertyHTTPProxy. The value should include at least one
 *	Host/Port pair from the keys below. Use the dictionary returned
 *	by SystemConfiguration.framework to set the default values for
 *	the system. HTTP proxies are not applied automatically.
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.2 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyHTTPProxy				  __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);


/*
 *  kCFStreamPropertyHTTPProxyHost
 *  
 *  Discussion:
 *	Proxy dictionary key. The hostname of an HTTP proxy. The value is
 *	a CFString. The key name matches kSCPropNetProxiesHTTPProxy.
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.2 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyHTTPProxyHost			  __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);


/*
 *  kCFStreamPropertyHTTPProxyPort
 *  
 *  Discussion:
 *	Proxy dictionary key. Value is a CFNumber.
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.2 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyHTTPProxyPort			  __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);
/* matches kSCPropNetProxiesHTTPPort */


/*
 *  kCFStreamPropertyHTTPSProxyHost
 *  
 *  Discussion:
 *	Proxy dictionary key. Value is a CFString.
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.2 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyHTTPSProxyHost			 __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);
/* matches kSCPropNetProxiesHTTPSProxy */


/*
 *  kCFStreamPropertyHTTPSProxyPort
 *  
 *  Discussion:
 *	Proxy dictionary key. Value is a CFNumber.
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.2 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyHTTPSProxyPort			 __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);
/* matches kSCPropNetProxiesHTTPSPort */


/*
 *  kCFStreamPropertyHTTPShouldAutoredirect
 *  
 *  Discussion:
 *	Stream property key. Value is a CFBoolean. Redirection is not
 *	performed by default.
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.2 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyHTTPShouldAutoredirect	 __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);


/*
 *  kCFStreamPropertyHTTPAttemptPersistentConnection
 *  
 *  Discussion:
 *	Stream property key. Value is a CFBoolean.  If this property is
 *	set to kCFBooleanTrue, an HTTP stream will look for an
 *	appropriate extant persistent connection to use, and if it finds
 *	none, will try to create one. Persistent connections are not used
 *	by default.
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.2 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyHTTPAttemptPersistentConnection __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);


/*
 *  kCFStreamPropertyHTTPRequestBytesWrittenCount
 *  
 *  Discussion:
 *	Stream property key. Value is a CFNumber. This property can only
 *	be retrieved, not set. The number returned is the number of bytes
 *	from the body of the request that have been written to the
 *	underlying socket
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.3 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFStreamPropertyHTTPRequestBytesWrittenCount __OSX_AVAILABLE_STARTING(__MAC_10_3,__IPHONE_2_0);


/*********************/
/* Creation routines */
/*********************/
/*
 *  CFReadStreamCreateForHTTPRequest()
 *  
 *  Discussion:
 *	Create an HTTP read stream for the response to the given request.
 *	When the stream is opened, it will begin transmitting the
 *	request. The bytes returned are the pure body bytes; the response
 *	header has been parsed off. To retrieve the response header, ask
 *	for kCFStreamPropertyHTTPResponseHeader, above, any time after
 *	the first bytes arrive on the stream (or when stream end is
 *	reported, if there are no data bytes). When an HTTP/1.1 server
 *	returns a chunked a response, the chunks will be formed into one
 *	continuous stream.
 *  
 *  Parameters:
 *	
 *	alloc:
 *	  A pointer to the CFAllocator which should be used to allocate
 *	  memory for the CF read stream and its storage for values. If
 *	  this reference is not a valid CFAllocator, the behavior is
 *	  undefined.
 *	
 *	request:
 *	  A pointer to a CFHTTPMessage created by the
 *	  CFHTTPMessageCreateRequest function.
 *  
 *  Result:
 *	A pointer to the CF read stream created, or NULL if failed. It is
 *	caller's responsibilty to release the memory allocated for the
 *	read stream.
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.1 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT CFReadStreamRef 
CFReadStreamCreateForHTTPRequest(
  CFAllocatorRef	 alloc,
  CFHTTPMessageRef   request)								 __OSX_AVAILABLE_STARTING(__MAC_10_1,__IPHONE_2_0);


/*
 *  CFReadStreamCreateForStreamedHTTPRequest()
 *  
 *  Discussion:
 *	Creates a read stream for the response to the given
 *	requestHeaders plus requestBody. Use in preference to
 *	CFReadStreamCreateForHTTPRequest() when the body of the request
 *	is larger than you wish to be resident in memory.  Note that
 *	because streams cannot be reset, read streams created this way
 *	cannot have autoredirection enabled.  If the Content-Length
 *	header is set in requestHeaders, it is assumed that the caller
 *	got the length right and that requestBody will report
 *	end-of-stream after precisely Content-Length bytes have been read
 *	from it. If the Content-Length header is not set, the chunked
 *	transfer-encoding will be added to requestHeaders, and bytes read
 *	from requestBody will be transmitted chunked. The body of
 *	requestHeaders is ignored.
 *  
 *  Parameters:
 *	
 *	alloc:
 *	  A pointer to the CFAllocator which should be used to allocate
 *	  memory for the CF read stream and its storage for values. If
 *	  this reference is not a valid CFAllocator, the behavior is
 *	  undefined.
 *	
 *	requestHeaders:
 *	  A pointer to a CFHTTPMessage created by the
 *	  CFHTTPMessageCreateRequest function. The body of requestHeaders
 *	  is ignored.
 *	
 *	requestBody:
 *	  A pointer to a CFReadStream.
 *  
 *  Result:
 *	A pointer to the CF read stream created, or NULL if failed. It is
 *	caller's responsibilty to release the memory allocated for the
 *	read stream.
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.2 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT CFReadStreamRef 
CFReadStreamCreateForStreamedHTTPRequest(
  CFAllocatorRef	 alloc,
  CFHTTPMessageRef   requestHeaders,
  CFReadStreamRef	requestBody)							 __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);


/*
 *  CFHTTPReadStreamSetRedirectsAutomatically()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *	Use the kCFStreamPropertyHTTPShouldAutoredirect property above
 *	instead.
 *  
 *  Discussion:
 *	Sets the redirection property on the http stream.
 *  
 *  Parameters:
 *	
 *	httpStream:
 *	  A pointer to the CFHTTPStream to be set.
 *	
 *	shouldAutoRedirect:
 *	  A boolean indicating whether to redirect or not.
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.1 and later in CoreServices.framework but deprecated in 10.3
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT void 
CFHTTPReadStreamSetRedirectsAutomatically(
  CFReadStreamRef   httpStream,
  Boolean		   shouldAutoRedirect)					   __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_3,__IPHONE_NA,__IPHONE_NA);


/*
 *  CFHTTPReadStreamSetProxy()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *	Use the kCFStreamPropertyHTTPProxy above instead.
 *  
 *  Discussion:
 *	Sets the redirection property on the http stream.
 *  
 *  Parameters:
 *	
 *	httpStream:
 *	  A pointer to the CFHTTPStream to be set.
 *	
 *	proxyHost:
 *	  The proxy hostname. A CFString value.
 *	
 *	proxyPort:
 *	  The port number. A CFNumber value.
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.1 and later in CoreServices.framework but deprecated in 10.3
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT void 
CFHTTPReadStreamSetProxy(
  CFReadStreamRef   httpStream,
  CFStringRef	   proxyHost,
  CFIndex		   proxyPort)								__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_3,__IPHONE_NA,__IPHONE_NA);



#if PRAGMA_ENUM_ALWAYSINT
	#pragma enumsalwaysint reset
#endif

#ifdef __cplusplus
}
#endif

#endif /* __CFHTTPSTREAM__ */

