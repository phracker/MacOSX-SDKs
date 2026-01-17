#ifndef __SERVICE_MANAGEMENT_ERRORS__
#define __SERVICE_MANAGEMENT_ERRORS__

#include <TargetConditionals.h>
#include <sys/cdefs.h>

#include <xpc/xpc.h>
#include <CoreFoundation/CoreFoundation.h>

__BEGIN_DECLS

__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_6, __MAC_10_10, __IPHONE_3_0, __IPHONE_8_0)
XPC_EXPORT
const CFStringRef kSMErrorDomainIPC;

__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_6, __MAC_10_10, __IPHONE_3_0, __IPHONE_8_0)
XPC_EXPORT
const CFStringRef kSMErrorDomainFramework;

__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_6, __MAC_10_10, __IPHONE_3_0, __IPHONE_8_0)
XPC_EXPORT
const CFStringRef kSMErrorDomainLaunchd;

/*!
 * @enum Service Management Errors
 *
 * @abstract Errors returned by service management functions.
 *
 * @const kSMErrorInternalFailure
 * An internal failure has occurred.
 *
 * @const kSMErrorInvalidSignature
 * The Application's code signature does not meet the requirements to perform
 * the operation.
 *
 * @const kSMErrorAuthorizationFailure
 * The request required authorization (i.e. adding a job to the
 * {@link kSMDomainSystemLaunchd} domain) but the AuthorizationRef did not
 * contain the required right.
 *
 * @const kSMErrorToolNotValid 
 * The specified path does not exist or the tool at the specified path is not
 * valid.
 *
 * @const kSMErrorJobNotFound 
 * A job with the given label could not be found.
 *
 * @const kSMErrorServiceUnavailable 
 * The service required to perform this operation is unavailable or is no longer
 * accepting requests.
 */
enum {
	kSMErrorInternalFailure = 2,
	kSMErrorInvalidSignature,
	kSMErrorAuthorizationFailure,
	kSMErrorToolNotValid,
	kSMErrorJobNotFound,
	kSMErrorServiceUnavailable,
	kSMErrorJobPlistNotFound,
	kSMErrorJobMustBeEnabled,
	kSMErrorInvalidPlist,
};

__END_DECLS

#endif // __SERVICE_MANAGEMENT_ERRORS__
