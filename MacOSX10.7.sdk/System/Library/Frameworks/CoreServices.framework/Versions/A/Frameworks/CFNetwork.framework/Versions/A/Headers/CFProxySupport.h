/*
	 File:	   CFNetwork/CFProxySupport.h
 
	 Contains:   Support for computing which proxy applies when
 
	 Copyright:  Copyright (c) 2006-2008, Apple Inc. All rights reserved.
 
	 Bugs?:	  For bug reports, consult the following page on
				 the World Wide Web:
 
					 http://developer.apple.com/bugreporter/
 
*/
#ifndef __CFPROXYSUPPORT__
#define __CFPROXYSUPPORT__

#ifndef __CFNETWORKDEFS__
#include <CFNetwork/CFNetworkDefs.h>
#endif

#ifndef __CFARRAY__
#include <CoreFoundation/CFArray.h>
#endif

#ifndef __CFSTRING__
#include <CoreFoundation/CFString.h>
#endif

#ifndef __CFURL__
#include <CoreFoundation/CFURL.h>
#endif

#ifndef __CFERROR__
#include <CoreFoundation/CFError.h>
#endif

#ifndef __CFRUNLOOP__
#include <CoreFoundation/CFRunLoop.h>
#endif

#ifndef __CFSTREAM__
#include <CoreFoundation/CFStream.h>
#endif


/* 
	These APIs return arrays of dictionaries, where each dictionary describes a single proxy. 
	The arrays represent the order in which the proxies should be tried - try to download the URL
	using the first entry in the array, and if that fails, try using the second entry, and so on.

	The keys to the proxy dictionaries follow the function declarations; every proxy dictionary 
	will have an entry for kCFProxyTypeKey.  If the type is anything except 
	kCFProxyTypeAutoConfigurationURL, the dictionary will also have entries for the proxy's host
	and port (under kCFProxyHostNameKey and kCFProxyPortNumberKey respectively).  If the type is
	kCFProxyTypeAutoConfigurationURL, it will have an entry for kCFProxyAutoConfigurationURLKey.  
	
	The keys for username and password are optional and will only be present if the username 
	or password could be extracted from the information passed in (i.e. either the URL itself
	or the proxy dictionary supplied).  These APIs do not consult any external credential stores
	(such as the Keychain).
*/

#include <Availability.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*!
	@function CFNetworkCopySystemProxySettings
	@discussion Returns a CFDictionary containing the current system internet proxy settings.
	@result Returns a dictionary containing key-value pairs that represent
		the current internet proxy settings.  See below for definitions of the keys and
		values.
		NULL if no proxy settings have been defined or if an error
		was encountered.
		The caller is responsible for releasing the returned dictionary.
*/
CFN_EXPORT CFDictionaryRef
CFNetworkCopySystemProxySettings( void )					__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);

	
/*
 *  CFNetworkCopyProxiesForURL()
 *  
 *  Discussion:
 *	Given a URL and a proxy dictionary, determines the ordered list
 *	of proxies that should be used to download the given URL.
 *  
 *  Parameters:
 *	
 *	url:
 *	  The URL to be accessed
 *	
 *	proxySettings:
 *	  A dictionary describing the available proxy settings; the
 *	  dictionary's format should match the dictionary returned
 *	  by CFNetworkCopySystemProxySettings described below.
 *  
 *  Result:
 *	An array of dictionaries; each dictionary describes a single
 *	proxy.  See the comment at the top of this file for how to
 *	interpret the returned dictionaries.
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.5 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT CFArrayRef 
CFNetworkCopyProxiesForURL(
  CFURLRef		  url,
  CFDictionaryRef   proxySettings)							__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);




/*
 *  CFProxyAutoConfigurationResultCallback
 *  
 *  Discussion:
 *	Callback function to be called when a PAC file computation
 *	(initiated by either CFNetworkExecuteProxyAutoConfigurationScript
 *	or CFNetworkExecuteProxyAutoConfigurationURL) has completed.
 *  
 *  Parameters:
 *	
 *	client:
 *	  The client reference passed in to
 *	  CFNetworkExecuteProxyAutoConfigurationScript or
 *	  CFNetworkExecuteProxyAutoConfigurationURL
 *	
 *	proxyList:
 *	  Upon success, the list of proxies returned by the
 *	  autoconfiguration script.  The list has the same format as
 *	  returned by CFProxyCopyProxiesForURL, above, except that no
 *	  entry may be of type kCFProxyTypeAutoConfigurationURL.  Note
 *	  that if the client wishes to keep this list, they must retain
 *	  it when they receive this callback.
 *	
 *	error:
 *	  Upon failure, an error object explaining the failure.
 */
typedef CALLBACK_API_C( void , CFProxyAutoConfigurationResultCallback )(void *client, CFArrayRef proxyList, CFErrorRef error);

/*
 *  CFNetworkCopyProxiesForAutoConfigurationScript()
 *  
 *  Discussion:
 *	Synchronously executes the given proxy autoconfiguration script
 *	and returns a valid proxyList and NULL error upon success or a
 *	NULL proxyList and valid error on failure.
 *  
 *  Parameters:
 *	
 *	proxyAutoConfigurationScript:
 *	  A CFString containing the code of the script to be executed.
 *	
 *	targetURL:
 *	  The URL that should be input in to the autoconfiguration script.
 *	
 *	error:
 *	  A return argument that will contain a valid error in case of
 *	  failure.
 *  
 *  Result:
 *	An array of dictionaries describing the proxies returned by the
 *	script or NULL on failure.
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.5 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT CFArrayRef 
CFNetworkCopyProxiesForAutoConfigurationScript(
  CFStringRef   proxyAutoConfigurationScript,
  CFURLRef	  targetURL,
  CFErrorRef *  error)										__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);


/*
 *  CFNetworkExecuteProxyAutoConfigurationScript()
 *  
 *  Discussion:
 *	Begins the process of executing proxyAutoConfigurationScript to
 *	determine the correct proxy to use to retrieve targetURL.  The
 *	caller should schedule the returned run loop source; when the
 *	results are found, the caller's callback will be called via the
 *	run loop, passing a valid proxyList and NULL error upon success,
 *	or a NULL proxyList and valid error on failure.  The caller
 *	should invalidate the returned run loop source if it wishes to
 *	terminate the request before completion. The returned
 *	RunLoopSource will be removed from all run loops and modes on
 *	which it was scheduled after the callback returns.
 *  
 *  Parameters:
 *	
 *	proxyAutoConfigurationScript:
 *	  A CFString containing the code of the script to be executed.
 *	
 *	targetURL:
 *	  The URL that should be passed to the autoconfiguration script.
 *	
 *	cb:
 *	  A client callback to notify the caller of completion.
 *	
 *	clientContext:
 *	  a stream context containing a client info object and optionally
 *	  retain / release callbacks for said info object.
 *  
 *  Result:
 *	A CFRunLoopSource which the client can use to schedule execution
 *	of the AutoConfiguration Script.
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.5 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT CFRunLoopSourceRef 
CFNetworkExecuteProxyAutoConfigurationScript(
  CFStringRef							  proxyAutoConfigurationScript,
  CFURLRef								 targetURL,
  CFProxyAutoConfigurationResultCallback   cb,
  CFStreamClientContext *				  clientContext)	 __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);



/*
 *  CFNetworkExecuteProxyAutoConfigurationURL()
 *  
 *  Discussion:
 *	As CFNetworkExecuteProxyAutoConfigurationScript(), above, except
 *	that CFNetworkExecuteProxyAutoConfigurationURL will additionally
 *	download the contents of proxyAutoConfigURL, convert it to a
 *	JavaScript string, and then execute that script.
 *  Ownership for the returned CFRunLoopSourceRef follows the copy rule, 
 *  the client is responsible for releasing the object.
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.5 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT CFRunLoopSourceRef 
CFNetworkExecuteProxyAutoConfigurationURL(
  CFURLRef								 proxyAutoConfigURL,
  CFURLRef								 targetURL,
  CFProxyAutoConfigurationResultCallback   cb,
  CFStreamClientContext *				  clientContext)	 __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);


/*
 *  kCFProxyTypeKey
 *  
 *  Discussion:
 *	Key for the type of proxy being represented; value will be one of
 *	the kCFProxyType constants listed below.
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.5 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFProxyTypeKey							 __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*
 *  kCFProxyHostNameKey
 *  
 *  Discussion:
 *	Key for the proxy's hostname; value is a CFString.  Note that
 *	this may be an IPv4 or IPv6 dotted-IP string.
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.5 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFProxyHostNameKey						 __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*
 *  kCFProxyPortNumberKey
 *  
 *  Discussion:
 *	Key for the proxy's port number; value is a CFNumber specifying
 *	the port on which to contact the proxy
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.5 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFProxyPortNumberKey					   __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*
 *  kCFProxyAutoConfigurationURLKey
 *  
 *  Discussion:
 *	Key for the proxy's PAC file location; this key is only present
 *	if the proxy's type is kCFProxyTypeAutoConfigurationURL.  Value
 *	is a CFURL specifying the location of a proxy auto-configuration
 *	file
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.5 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFProxyAutoConfigurationURLKey			 __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*
 *  kCFProxyAutoConfigurationJavaScriptKey
 *  
 *  Discussion:
 *	Key for the proxy's PAC script
 *	The value is a CFString that contains the full JavaScript soure text for the PAC file.
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.5 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFProxyAutoConfigurationJavaScriptKey			 __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_3_0);


/*
 *  kCFProxyUsernameKey
 *  
 *  Discussion:
 *	Key for the username to be used with the proxy; value is a
 *	CFString. Note that this key will only be present if the username
 *	could be extracted from the information passed in.  No external
 *	credential stores (like the Keychain) are consulted.
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.5 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFProxyUsernameKey						 __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*
 *  kCFProxyPasswordKey
 *  
 *  Discussion:
 *	Key for the password to be used with the proxy; value is a
 *	CFString. Note that this key will only be present if the username
 *	could be extracted from the information passed in.  No external
 *	credential stores (like the Keychain) are consulted.
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.5 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFProxyPasswordKey						 __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/* 
	Possible values for kCFProxyTypeKey:
	kCFProxyTypeNone - no proxy should be used; contact the origin server directly
	kCFProxyTypeHTTP - the proxy is an HTTP proxy
	kCFProxyTypeHTTPS - the proxy is a tunneling proxy as used for HTTPS
	kCFProxyTypeSOCKS - the proxy is a SOCKS proxy
	kCFProxyTypeFTP - the proxy is an FTP proxy
	kCFProxyTypeAutoConfigurationURL - the proxy is specified by a proxy autoconfiguration (PAC) file
*/
/*
 *  kCFProxyTypeNone
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.5 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFProxyTypeNone							__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);
/*
 *  kCFProxyTypeHTTP
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.5 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFProxyTypeHTTP							__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);
/*
 *  kCFProxyTypeHTTPS
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.5 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFProxyTypeHTTPS						   __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);
/*
 *  kCFProxyTypeSOCKS
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.5 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFProxyTypeSOCKS						   __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);
/*
 *  kCFProxyTypeFTP
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.5 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFProxyTypeFTP							 __OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);
/*
 *  kCFProxyTypeAutoConfigurationURL
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.5 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFProxyTypeAutoConfigurationURL			__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);
/*
 *
 *
 */
CFN_EXPORT const CFStringRef kCFProxyTypeAutoConfigurationJavaScript    __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_3_0);
	
/*
 *  kCFProxyAutoConfigHTTPResponse
 *  
 *  Availability:
 *	Mac OS X:		 in version 10.5 and later in CoreServices.framework
 *	CarbonLib:		not available
 *	Non-Carbon CFM:   not available
 */
CFN_EXPORT const CFStringRef kCFProxyAutoConfigurationHTTPResponseKey			__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);
	

#if TARGET_OS_MAC
/*
 *  kCFNetworkProxiesExceptionsList
 *  
 *  Discussion:
 *	Key for the list of host name patterns that should bypass the proxy; value is a
 *	CFArray of CFStrings.  
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesExceptionsList		__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
/*
 *  kCFNetworkProxiesExcludeSimpleHostnames
 *  
 *  Discussion:
 *	Key whose value indicates if simple hostnames will be excluded; value is a
 *	CFNumber.  Simple hostnames will be excluded if the key is present and has a 
 *	non-zero value.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesExcludeSimpleHostnames	__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
/*
 *  kCFNetworkProxiesFTPEnable
 *  
 *  Discussion:
 *	Key for the enabled status of the ftp proxy; value is a
 *	CFNumber.  The proxy is enabled if the key is present and has a non-zero value.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesFTPEnable			__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
/*
 *  kCFNetworkProxiesFTPPassive
 *  
 *  Discussion:
 *	Key for the state of passive mode for the ftp proxy; value is a
 *	CFNumber.  A value of one indicates that passive mode is enabled, a value
 *	of zero indicates that passive mode is not enabled.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesFTPPassive		__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
/*
 *  kCFNetworkProxiesFTPPort
 *  
 *  Discussion:
 *	Key for the port number associated with the ftp proxy; value is a
 *	CFNumber which is the port number.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesFTPPort			__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
/*
 *  kCFNetworkProxiesFTPProxy
 *  
 *  Discussion:
 *	Key for the host name associated with the ftp proxy; value is a
 *	CFString which is the proxy host name.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesFTPProxy			__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
/*
 *  kCFNetworkProxiesGopherEnable
 *  
 *  Discussion:
 *	Key for the enabled status of the gopher proxy; value is a
 *	CFNumber.  The proxy is enabled if the key is present and has a non-zero value.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesGopherEnable		__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
/*
 *  kCFNetworkProxiesGopherPort
 *  
 *  Discussion:
 *	Key for the port number associated with the gopher proxy; value is a
 *	CFNumber which is the port number.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesGopherPort		__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
/*
 *  kCFNetworkProxiesGopherProxy
 *  
 *  Discussion:
 *	Key for the host name associated with the gopher proxy; value is a
 *	CFString which is the proxy host name.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesGopherProxy		__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
/*
 *  kCFNetworkProxiesHTTPEnable
 *  
 *  Discussion:
 *	Key for the enabled status of the HTTP proxy; value is a
 *	CFNumber.  The proxy is enabled if the key is present and has a non-zero value.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesHTTPEnable		__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);
/*
 *  kCFNetworkProxiesHTTPPort
 *  
 *  Discussion:
 *	Key for the port number associated with the HTTP proxy; value is a
 *	CFNumber which is the port number.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesHTTPPort			__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);
/*
 *  kCFNetworkProxiesHTTPProxy
 *  
 *  Discussion:
 *	Key for the host name associated with the HTTP proxy; value is a
 *	CFString which is the proxy host name.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesHTTPProxy			__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);
/*
 *  kCFNetworkProxiesHTTPSEnable
 *  
 *  Discussion:
 *	Key for the enabled status of the HTTPS proxy; value is a
 *	CFNumber.  The proxy is enabled if the key is present and has a non-zero value.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesHTTPSEnable		__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
/*
 *  kCFNetworkProxiesHTTPSPort
 *  
 *  Discussion:
 *	Key for the port number associated with the HTTPS proxy; value is a
 *	CFNumber which is the port number.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesHTTPSPort			__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
/*
 *  kCFNetworkProxiesHTTPSProxy
 *  
 *  Discussion:
 *	Key for the host name associated with the HTTPS proxy; value is a
 *	CFString which is the proxy host name.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesHTTPSProxy		__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
/*
 *  kCFNetworkProxiesRTSPEnable
 *  
 *  Discussion:
 *	Key for the enabled status of the RTSP proxy; value is a
 *	CFNumber.  The proxy is enabled if the key is present and has a non-zero value.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesRTSPEnable		__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
/*
 *  kCFNetworkProxiesRTSPPort
 *  
 *  Discussion:
 *	Key for the port number associated with the RTSP proxy; value is a
 *	CFNumber which is the port number.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesRTSPPort			__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
/*
 *  kCFNetworkProxiesRTSPProxy
 *  
 *  Discussion:
 *	Key for the host name associated with the RTSP proxy; value is a
 *	CFString which is the proxy host name.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesRTSPProxy			__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
/*
 *  kCFNetworkProxiesSOCKSEnable
 *  
 *  Discussion:
 *	Key for the enabled status of the SOCKS proxy; value is a
 *	CFNumber.  The proxy is enabled if the key is present and has a non-zero value.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesSOCKSEnable		__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
/*
 *  kCFNetworkProxiesSOCKSPort
 *  
 *  Discussion:
 *	Key for the port number associated with the SOCKS proxy; value is a
 *	CFNumber which is the port number.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesSOCKSPort			__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
/*
 *  kCFNetworkProxiesSOCKSProxy
 *  
 *  Discussion:
 *	Key for the host name associated with the SOCKS proxy; value is a
 *	CFString which is the proxy host name.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesSOCKSProxy		__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
/*
 *  kCFNetworkProxiesProxyAutoConfigEnable
 *  
 *  Discussion:
 *	Key for the enabled status ProxyAutoConfig (PAC); value is a
 *	CFNumber.  ProxyAutoConfig is enabled if the key is present and has a non-zero value.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesProxyAutoConfigEnable	__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);
/*
 *  kCFNetworkProxiesProxyAutoConfigURLString
 *  
 *  Discussion:
 *	Key for the url which indicates the location of the ProxyAutoConfig (PAC) file; value is a
 *	CFString which is url for the PAC file.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesProxyAutoConfigURLString	__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_2_0);
/*
 * kCFNetworkProxiesProxyAutoConfigJavaScript
 *
 * Discussion:
 * Key for the string which is the full JavaScript source of the ProxyAutoConfig (PAC) script;  value is a
 * CFString with is the full text source of the PAC script.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesProxyAutoConfigJavaScript	__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_3_0);
	
/*
 *  kCFNetworkProxiesProxyAutoDiscoveryEnable
 *  
 *  Discussion:
 *	Key for the enabled status of proxy auto discovery; value is a
 *	CFNumber.  Proxy auto discovery is enabled if the key is present and has a non-zero value.
 */
CFN_EXPORT const CFStringRef kCFNetworkProxiesProxyAutoDiscoveryEnable	__OSX_AVAILABLE_STARTING(__MAC_10_6,__IPHONE_NA);
#endif // TARGET_OS_MAC

#ifdef __cplusplus
}
#endif

#endif /* __CFPROXYSUPPORT__ */

