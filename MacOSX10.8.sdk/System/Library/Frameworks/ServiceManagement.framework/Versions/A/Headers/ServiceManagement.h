/*
 *  ServiceManagement.h
 *  Copyright (c) 2008 Apple Inc.  All rights reserved.
 */
/*! @header
    The main header for the ServiceManagement framework.  This header
    provides support for loading and unloading launchd jobs
    and reading and manipulating job dictionaries from within
    an application.
 */

#ifndef __SERVICE_MANAGEMENT_H__
#define __SERVICE_MANAGEMENT_H__

#include <ServiceManagement/SMErrors.h>
#if !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
#include <ServiceManagement/SMLoginItem.h>
#endif
#include <CoreFoundation/CoreFoundation.h>

#if !TARGET_OS_EMBEDDED
#include <Security/Authorization.h>
#else
typedef void * AuthorizationRef;
#endif

/*! @abstract The authorization rights key for blessing and installing a privileged helper tool. */
#define kSMRightBlessPrivilegedHelper	"com.apple.ServiceManagement.blesshelper"
/*! @abstract The authorization rights key for modifying system daemons. */
#define kSMRightModifySystemDaemons		"com.apple.ServiceManagement.daemons.modify"

__BEGIN_DECLS

/*! @abstract System-level launchd domain.

 */
extern const CFStringRef kSMDomainSystemLaunchd;
/*! @abstract User-level launchd domain.
 */
extern const CFStringRef kSMDomainUserLaunchd;

// Info.plist Keys
/*! @abstract Privileged executables property list key */
extern const CFStringRef kSMInfoKeyPrivilegedExecutables;	/* "SMPrivilegedExecutables" */
/*! @abstract Authorized clients property list key */
extern const CFStringRef kSMInfoKeyAuthorizedClients;		/* "SMAuthorizedClients" */

#pragma mark Examining Jobs
/*! @group Examining Jobs */
/*!
 * @function		SMJobCopyDictionary
 * @abstract		Copy the job description dictionary for the given job label.
 * @discussion		SMJobCopyDictionary returns a copy of the job description
 *					dictionary for the given job label, or NULL if no job with the given
 *					label was found or an error occurred.
 *
 * @param			domain		The job's domain (e.g. {@link kSMDomainSystemLaunchd}).
 * @param			jobLabel	The label identifier for the job to copy.
 *
 * @result			A new dictionary describing the job, or NULL if the job could not be found.
 *					Must be released by the caller.
 */
CFDictionaryRef SMJobCopyDictionary(CFStringRef domain, CFStringRef jobLabel);

/*!
 * @function		SMCopyAllJobDictionaries
 * @abstract		Copy the job description dictionaries for all jobs in the
 *					given domain.
 * @discussion		SMCopyAllJobDictionaries returns an array of the job
 *					description dictionaries for all jobs in the given domain, or NULL
 *					if an error occurred.
 *
 * @param			domain		The desired domain (e.g. {@link kSMDomainSystemLaunchd}).
 *
 * @result			A new array containing all job dictionaries, or NULL if an error
 *					occurred.  Must be released by the caller.
 */
CFArrayRef SMCopyAllJobDictionaries(CFStringRef domain);

/*!
 * @function		SMJobSubmit
 * @abstract		Submits the given job to the specified domain.
 * @discussion		SMJobSubmit submits the given job to the specified domain.
 * 
 * @param			domain		The job's domain (e.g. {@link kSMDomainSystemLaunchd}).
 * @param			job			A dictionary describing a job.
 * @param			auth		An AuthorizationRef containing the {@link kSMRightModifySystemDaemons} right if the
 *								given domain is {@link kSMDomainSystemLaunchd}.
 * @param			outError	An output reference to a CFErrorRef describing the specific
 *								error encountered while submitting the job dictionary, or NULL
 *								if no error occurred. It is the responsibility of the application to
 *								release the error reference. This argument may be NULL.
 * @result			true if the job was submitted successfully, otherwise false.
 */
Boolean SMJobSubmit(CFStringRef domain, CFDictionaryRef job, AuthorizationRef auth, CFErrorRef *outError);

/*!
 * @function		SMJobRemove
 * @abstract		Removes the job with the given label from the specified domain.
 * @discussion		SMJobSubmit removes the job specified by label from the domain. If the job is
 *					currently running, it will conditionally block until the running process has
 *					exited.
 * 
 * @param			domain		The job's domain (e.g. {@link kSMDomainSystemLaunchd}).
 * @param			jobLabel	The label for the job to remove.
 * @param			auth		An AuthorizationRef containing the {@link kSMRightModifySystemDaemons} right if the
 *								given domain is {@link kSMDomainSystemLaunchd}.
 * @param			wait		Pass true to block until the process for the given job has exited.
 * @param			outError	An output reference to a CFErrorRef describing the specific
 *								error encountered while submitting the job dictionary, or NULL
 *								if no error occurred. It is the responsibility of the application to
 *								release the error reference. This argument may be NULL.
 *
 * @result			true if the job was removed successfully, otherwise false.
 */
Boolean SMJobRemove(CFStringRef domain, CFStringRef jobLabel, AuthorizationRef auth, Boolean wait, CFErrorRef *outError);

#pragma mark Adding Jobs Securely
/*! @group Adding Jobs Securely */
/*!
 * @function		SMJobBless
 * @abstract		Submits the executable for the given label as a launchd job.
 * @discussion		SMJobBless submits the executable for the given
 *					label as a launchd job.  This function obviates the need for a
 *					setuid helper invoked via AuthorizationExecuteWithPrivileges() in order
 *					to install a launchd plist.
 *
 * If the job is already installed, success is returned.
 *
 * In order to use this function the following requirements must be met:
 *
 * 1.	The calling application and target executable tool must both be signed.
 * 
 * 2.	The calling application's Info.plist must include a
 *		"SMPrivilegedExecutables" dictionary of strings. Each string is a textual
 *		representation of a code signing requirement used to determine whether
 *		the application owns the privileged tool once installed (i.e. in order
 *		for subsequent versions to update the installed version).
 * 
 *		Each key of SMPrivilegedExecutables is a reverse-DNS label for the helper
 *		tool (must be globally unique).
 *
 * 3.	The helper tool must have an embedded Info.plist containing an "SMAuthorizedClients"
 *		array of strings. Each string is a textual representation of a code signing
 *		requirement describing a client which is allowed to add and remove the tool.
 *
 * 4.	The helper tool must have an embedded launchd plist. The only required key in this
 *		plist is the Label key. When the launchd plist is extracted and written to disk, 
 *		the key for ProgramArguments will be set to an array of 1 element pointing to a 
 *		standard location. You cannot specify your own program arguments, so do not rely
 *		on custom command line arguments being passed to your tool. Pass any parameters via IPC.
 *
 * 5.	The helper tool must reside in the Contents/Library/LaunchServices directory inside the
 *		application bundle, and its name must be its launchd job label. So if your launchd job
 *		label is "com.apple.Mail.helper", this must be the name of the tool in your application
 *		bundle.
 * 
 * @param			domain				The job's domain. Only {@link kSMDomainSystemLaunchd} is supported.
 * @param			executableLabel		The label of the privileged executable to install.
 *										This label must be one of the keys found in the SMPrivilegedExecutables
 *										dictionary in the application's Info.plist.
 * @param			auth				An authorization reference containing the {@link kSMRightBlessPrivilegedHelper} right.
 * @param			outError			An output reference to a CFErrorRef describing the specific
 *										error encountered while submitting the executable tool, or NULL if
 *										successful.  It is the responsibility of the application to release the
 *										error reference.  This argument may be NULL.
 *
 * @result			True if the job was successfully submitted, otherwise false.
 */
Boolean SMJobBless(CFStringRef domain, CFStringRef executableLabel, AuthorizationRef auth, CFErrorRef *outError);

__END_DECLS

#endif /* __SERVICE_MANAGEMENT_H__ */
