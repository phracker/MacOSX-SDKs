/*	CFHTTPMessage.h
	Copyright 1998-2000, Apple, Inc. All rights reserved.
*/

#if !defined(__CFNETWORK_CFHTTPMESSAGE__)
#define __CFNETWORK_CFHTTPMESSAGE__ 1

#include <CoreFoundation/CFString.h>
#include <CoreFoundation/CFURL.h>

#if defined(__cplusplus)
extern "C" {
#endif

CF_EXPORT const CFStringRef kCFHTTPVersion1_0;
CF_EXPORT const CFStringRef kCFHTTPVersion1_1;
CF_EXPORT const CFStringRef kCFHTTPAuthenticationSchemeBasic;
CF_EXPORT const CFStringRef kCFHTTPAuthenticationSchemeDigest; /* Currently unsupported */

typedef struct __CFHTTPMessage * CFHTTPMessageRef;

CF_EXPORT
CFTypeID CFHTTPMessageGetTypeID(void);
    
CF_EXPORT
CFHTTPMessageRef CFHTTPMessageCreateRequest(CFAllocatorRef allocator, CFStringRef requestMethod, CFURLRef url, CFStringRef httpVersion);

/* Pass NULL to use the standard description for the given status code, as found in RFC 2616 */
CF_EXPORT
CFHTTPMessageRef CFHTTPMessageCreateResponse(CFAllocatorRef allocator, int statusCode, CFStringRef statusDescription, CFStringRef httpVersion);

/* Creates an empty request or response, which you can then append bytes to via CFHTTPMessageAppendBytes().  The HTTP header information will be parsed out as the bytes are appended. */
CF_EXPORT
CFHTTPMessageRef CFHTTPMessageCreateEmpty(CFAllocatorRef allocator, Boolean isRequest);

CF_EXPORT
CFHTTPMessageRef CFHTTPMessageCreateCopy(CFAllocatorRef allocator, CFHTTPMessageRef message);

/* Whether the message is a response or a request */
CF_EXPORT
Boolean CFHTTPMessageIsRequest(CFHTTPMessageRef message);

CF_EXPORT
CFStringRef CFHTTPMessageCopyVersion(CFHTTPMessageRef message);

CF_EXPORT
CFDataRef CFHTTPMessageCopyBody(CFHTTPMessageRef message);

CF_EXPORT
void CFHTTPMessageSetBody(CFHTTPMessageRef message, CFDataRef bodyData);

CF_EXPORT
CFStringRef CFHTTPMessageCopyHeaderFieldValue(CFHTTPMessageRef message, CFStringRef headerField);

CF_EXPORT
CFDictionaryRef CFHTTPMessageCopyAllHeaderFields(CFHTTPMessageRef message);

CF_EXPORT
void CFHTTPMessageSetHeaderFieldValue(CFHTTPMessageRef message, CFStringRef headerField, CFStringRef value);

/* The following function appends the given bytes to the message given (parsing out any control information if appropriate).  Returns FALSE if a parsing error occurs while processing the new data. */
CF_EXPORT
Boolean CFHTTPMessageAppendBytes(CFHTTPMessageRef message, const UInt8 *newBytes, CFIndex numBytes);

/* Whether further header data is expected by the message */
CF_EXPORT
Boolean CFHTTPMessageIsHeaderComplete(CFHTTPMessageRef message);

CF_EXPORT
CFDataRef CFHTTPMessageCopySerializedMessage(CFHTTPMessageRef request);

/* Request functions */
CF_EXPORT
CFURLRef CFHTTPMessageCopyRequestURL(CFHTTPMessageRef request);

CF_EXPORT
CFStringRef CFHTTPMessageCopyRequestMethod(CFHTTPMessageRef request);

/* Tries to modify request to contain the authentication information 
   requested by authenticationFailureResponse (which presumably is a 
   401 or 407 response).  Returns TRUE if successful; FALSE otherwise 
   (leaving request unmodified).  If authenticationScheme is NULL, the 
   strongest supported scheme listed in failedResponse will be used. */
CF_EXPORT
Boolean CFHTTPMessageAddAuthentication(CFHTTPMessageRef request, CFHTTPMessageRef authenticationFailureResponse, CFStringRef username, CFStringRef password, CFStringRef authenticationScheme, Boolean forProxy);


/* Response functions */
CF_EXPORT
UInt32 CFHTTPMessageGetResponseStatusCode(CFHTTPMessageRef response);

CF_EXPORT
CFStringRef CFHTTPMessageCopyResponseStatusLine(CFHTTPMessageRef response);

#if defined(__cplusplus)
}
#endif

#endif /* !__CFNETWORK_CFHTTPMESSAGE__ */

