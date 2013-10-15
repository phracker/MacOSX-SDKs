/*
 *  SMErrors.h
 *  launchdadd
 *
 *  Created by Damien Sorresso on 5/19/08.
 *  Copyright 2008 Apple Inc. All rights reserved.
 *
 */

#ifndef __SMERRORS_H__
#define __SMERRORS_H__

#include <CoreFoundation/CoreFoundation.h>
#include <TargetConditionals.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

// Error domains.
extern const CFStringRef kSMErrorDomainIPC;
extern const CFStringRef kSMErrorDomainFramework;
extern const CFStringRef kSMErrorDomainLaunchd;

/*!
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
 *				No job with the given label was found.
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
