#ifndef __IOKIT_IOCFURLACCESS_H
#define __IOKIT_IOCFURLACCESS_H

#include <CoreFoundation/CoreFoundation.h>

CFTypeRef IOURLCreatePropertyFromResource(CFAllocatorRef alloc, CFURLRef url, CFStringRef property, SInt32 *errorCode);

Boolean IOURLCreateDataAndPropertiesFromResource(CFAllocatorRef alloc, CFURLRef url, CFDataRef *resourceData, CFDictionaryRef *properties, CFArrayRef desiredProperties, SInt32 *errorCode);

Boolean IOURLWriteDataAndPropertiesToResource(CFURLRef url, CFDataRef dataToWrite, CFDictionaryRef propertiesToWrite, SInt32 *errorCode);

#ifdef HAVE_CFURLACCESS

#define kIOURLFileExists		kCFURLFileExists
#define kIOURLFileDirectoryContents	kCFURLFileDirectoryContents
#define kIOURLFileLength		kCFURLFileLength
#define kIOURLFileLastModificationTime	kCFURLFileLastModificationTime
#define kIOURLFilePOSIXMode		kCFURLFilePOSIXMode
#define kIOURLFileOwnerID		kCFURLFileOwnerID

/* Common error codes; this list is expected to grow */

typedef CFURLError IOURLError;

enum {
    kIOURLUnknownError 			= kCFURLUnknownError,
    kIOURLUnknownSchemeError 		= kCFURLUnknownSchemeError,
    kIOURLResourceNotFoundError 	= kCFURLResourceNotFoundError,
    kIOURLResourceAccessViolationError 	= kCFURLResourceAccessViolationError,
    kIOURLRemoteHostUnavailableError 	= kCFURLRemoteHostUnavailableError,
    kIOURLImproperArgumentsError 	= kCFURLImproperArgumentsError,
    kIOURLUnknownPropertyKeyError 	= kCFURLUnknownPropertyKeyError,
    kIOURLPropertyKeyUnavailableError 	= kCFURLPropertyKeyUnavailableError,
    kIOURLTimeoutError 			= kCFURLTimeoutError
};

#else /* !HAVE_CFURLACCESS */

#define kIOURLFileExists		CFSTR("kIOURLFileExists")
#define kIOURLFileDirectoryContents	CFSTR("kIOURLFileDirectoryContents")
#define kIOURLFileLength		CFSTR("kIOURLFileLength")
#define kIOURLFileLastModificationTime	CFSTR("kIOURLFileLastModificationTime")
#define kIOURLFilePOSIXMode		CFSTR("kIOURLFilePOSIXMode")
#define kIOURLFileOwnerID		CFSTR("kIOURLFileOwnerID")

/* Common error codes; this list is expected to grow */

typedef enum {
      kIOURLUnknownError = -10,
          kIOURLUnknownSchemeError = -11,
          kIOURLResourceNotFoundError = -12,
          kIOURLResourceAccessViolationError = -13,
          kIOURLRemoteHostUnavailableError = -14,
          kIOURLImproperArgumentsError = -15,
          kIOURLUnknownPropertyKeyError = -16,
          kIOURLPropertyKeyUnavailableError = -17,
          kIOURLTimeoutError = -18
} IOURLError;

#endif /* !HAVE_CFURLACCESS */

#endif /* __IOKIT_IOCFURLACCESS_H */
