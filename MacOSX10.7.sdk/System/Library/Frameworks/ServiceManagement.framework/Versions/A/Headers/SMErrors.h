/*
 *  SMErrors.h
 *  launchdadd
 *
 *  Created by Damien Sorresso on 5/19/08.
 *  Copyright 2008 Apple Inc. All rights reserved.
 *
 */
/*! @header
    The header containing error codes returned by functions
    in the ServiceManagement framework.  You do not need
    to include this directly;
    {@link //apple_ref/doc/header/ServiceManagement.h ServiceManagement.h}
    includes it for you.
 */

#ifndef __SMERRORS_H__
#define __SMERRORS_H__

#include <CoreFoundation/CoreFoundation.h>
#include <TargetConditionals.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

// Error domains.
/*! @abstract Service management IPC error domain */
extern const CFStringRef kSMErrorDomainIPC;
/*! @abstract Service management Framework error domain */
extern const CFStringRef kSMErrorDomainFramework;
/*! @abstract Service management launchd error domain */
extern const CFStringRef kSMErrorDomainLaunchd;

/*!
 * @enum Service Management Errors
 * @abstract Errors returned by service management functions.
 * @discussion
 * @const kSMErrorInternalFailure
 *				An internal failure has occurred.
 * @const kSMErrorInvalidSignature
 *				The Application's code signature does not meet the 
 *				requirements to perform the operation.
 * @const kSMErrorAuthorizationFailure
 *				The request required authorization (i.e. adding a job 
 *				to the kSMDomainSystemLaunchd) but the AuthorizationRef
 *				did not contain the required right.
 * @const kSMErrorToolNotValid 
 *				The specified path does not exist or the tool at the specified
 *				path is not valid.
 * @const kSMErrorJobNotFound 
 *				A job with the given label could not be found.
 * @const kSMErrorServiceUnavailable 
 *				The service required to perform this operation is unavailable 
 *				or is no longer accepting requests.
 */

enum {
	kSMErrorInternalFailure			= 2,
	kSMErrorInvalidSignature,
	kSMErrorAuthorizationFailure,
	kSMErrorToolNotValid,
	kSMErrorJobNotFound,
	kSMErrorServiceUnavailable,
	kSMErrorJobPlistNotFound,
	kSMErrorJobMustBeEnabled,
};

__END_DECLS

#endif /* __SMERRORS_H__ */
