/*
     File:       CFNetwork/CFHTTPMessage.h
 
     Contains:   CoreFoundation Network socket streams header
 
     Version:    CFNetwork-71.2~1
 
     Copyright:  © 2001-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __CFHTTPMESSAGE__
#define __CFHTTPMESSAGE__

#ifndef __CFSTRING__
#include <CoreFoundation/CFString.h>
#endif

#ifndef __CFURL__
#include <CoreFoundation/CFURL.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  kCFHTTPVersion1_0
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kCFHTTPVersion1_0                           AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;
/*
 *  kCFHTTPVersion1_1
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kCFHTTPVersion1_1                           AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;
/*
 *  kCFHTTPAuthenticationSchemeBasic
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kCFHTTPAuthenticationSchemeBasic            AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
/*
 *  kCFHTTPAuthenticationSchemeDigest
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kCFHTTPAuthenticationSchemeDigest           AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
/* Currently unsupported */
typedef struct __CFHTTPMessage*         CFHTTPMessageRef;
/*
 *  CFHTTPMessageGetTypeID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFTypeID 
CFHTTPMessageGetTypeID(void)                                  AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  CFHTTPMessageCreateRequest()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFHTTPMessageRef 
CFHTTPMessageCreateRequest(
  CFAllocatorRef   allocator,
  CFStringRef      requestMethod,
  CFURLRef         url,
  CFStringRef      httpVersion)                               AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/* Pass NULL to use the standard description for the given status code, as found in RFC 2616*/
/*
 *  CFHTTPMessageCreateResponse()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFHTTPMessageRef 
CFHTTPMessageCreateResponse(
  CFAllocatorRef   allocator,
  int              statusCode,
  CFStringRef      statusDescription,
  CFStringRef      httpVersion)                               AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/* Creates an empty request or response, which you can then append bytes to via CFHTTPMessageAppendBytes().  The HTTP header information will be parsed out as the bytes are appended.*/
/*
 *  CFHTTPMessageCreateEmpty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFHTTPMessageRef 
CFHTTPMessageCreateEmpty(
  CFAllocatorRef   allocator,
  Boolean          isRequest)                                 AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  CFHTTPMessageCreateCopy()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFHTTPMessageRef 
CFHTTPMessageCreateCopy(
  CFAllocatorRef     allocator,
  CFHTTPMessageRef   message)                                 AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/* Whether the message is a response or a request*/
/*
 *  CFHTTPMessageIsRequest()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
CFHTTPMessageIsRequest(CFHTTPMessageRef message)              AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  CFHTTPMessageCopyVersion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef 
CFHTTPMessageCopyVersion(CFHTTPMessageRef message)            AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  CFHTTPMessageCopyBody()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFDataRef 
CFHTTPMessageCopyBody(CFHTTPMessageRef message)               AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  CFHTTPMessageSetBody()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
CFHTTPMessageSetBody(
  CFHTTPMessageRef   message,
  CFDataRef          bodyData)                                AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  CFHTTPMessageCopyHeaderFieldValue()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef 
CFHTTPMessageCopyHeaderFieldValue(
  CFHTTPMessageRef   message,
  CFStringRef        headerField)                             AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  CFHTTPMessageCopyAllHeaderFields()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFDictionaryRef 
CFHTTPMessageCopyAllHeaderFields(CFHTTPMessageRef message)    AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  CFHTTPMessageSetHeaderFieldValue()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
CFHTTPMessageSetHeaderFieldValue(
  CFHTTPMessageRef   message,
  CFStringRef        headerField,
  CFStringRef        value)                                   AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/* The following function appends the given bytes to the message given (parsing out any control information if appropriate).  Returns FALSE if a parsing error occurs while processing the new data.*/
/*
 *  CFHTTPMessageAppendBytes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
CFHTTPMessageAppendBytes(
  CFHTTPMessageRef   message,
  const UInt8 *      newBytes,
  CFIndex            numBytes)                                AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/* Whether further header data is expected by the message*/
/*
 *  CFHTTPMessageIsHeaderComplete()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
CFHTTPMessageIsHeaderComplete(CFHTTPMessageRef message)       AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  CFHTTPMessageCopySerializedMessage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFDataRef 
CFHTTPMessageCopySerializedMessage(CFHTTPMessageRef request)  AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*********************/
/* Request functions */
/*********************/
/*
 *  CFHTTPMessageCopyRequestURL()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFURLRef 
CFHTTPMessageCopyRequestURL(CFHTTPMessageRef request)         AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  CFHTTPMessageCopyRequestMethod()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef 
CFHTTPMessageCopyRequestMethod(CFHTTPMessageRef request)      AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/* Tries to modify request to contain the authentication information 
   requested by authenticationFailureResponse (which presumably is a 
   401 or 407 response).  Returns TRUE if successful; FALSE otherwise 
   (leaving request unmodified).  If authenticationScheme is NULL, the 
   strongest supported scheme listed in failedResponse will be used. */
/*
 *  CFHTTPMessageAddAuthentication()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
CFHTTPMessageAddAuthentication(
  CFHTTPMessageRef   request,
  CFHTTPMessageRef   authenticationFailureResponse,
  CFStringRef        username,
  CFStringRef        password,
  CFStringRef        authenticationScheme,
  Boolean            forProxy)                                AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/**********************/
/* Response functions */
/**********************/
/*
 *  CFHTTPMessageGetResponseStatusCode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern UInt32 
CFHTTPMessageGetResponseStatusCode(CFHTTPMessageRef response) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  CFHTTPMessageCopyResponseStatusLine()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef 
CFHTTPMessageCopyResponseStatusLine(CFHTTPMessageRef response) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;



#ifdef __cplusplus
}
#endif

#endif /* __CFHTTPMESSAGE__ */

