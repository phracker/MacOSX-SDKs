#ifndef __SERVICE_MANAGEMENT__
#define __SERVICE_MANAGEMENT__

#include <TargetConditionals.h>
#include <sys/cdefs.h>

#include <xpc/xpc.h>
#include <CoreFoundation/CoreFoundation.h>
#include <ServiceManagement/SMErrors.h>

#if !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
#include <Security/Authorization.h>
#include <ServiceManagement/SMLoginItem.h>
#else // !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
// Other projects typedef AuthorizationRef, so let's do a #define here to avoid
// collisions at compile-time.
#define AuthorizationRef void *
#endif // !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)

/*! 
 * @abstract
 * The authorization rights key for blessing and installing a privileged helper
 * tool. 
 */
#define kSMRightBlessPrivilegedHelper \
	"com.apple.ServiceManagement.blesshelper"

/*!
 * @abstract
 * The authorization rights key for modifying system daemons. 
 */
#define kSMRightModifySystemDaemons \
	"com.apple.ServiceManagement.daemons.modify"

__BEGIN_DECLS

/*! 
 * @abstract
 * A constant representing the privileged Mach bootstrap context. Modifications
 * to this context require root privileges.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_3_0)
XPC_EXPORT
const CFStringRef kSMDomainSystemLaunchd;

/*! 
 * @abstract
 * A constant representing the Mach bootstrap context associated with the
 * caller's UID. On iOS, this symbol is a synonym for 
 * {@link kSMDomainSystemLaunchd}.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_3_0)
XPC_EXPORT
const CFStringRef kSMDomainUserLaunchd;

/*!
 * @function SMJobCopyDictionary
 *
 * @abstract
 * Copy the job description dictionary for the given job label.
 *
 * @param domain
 * The job's domain (e.g. {@link kSMDomainSystemLaunchd} or
 * {@link kSMDomainUserLaunchd}).
 *
 * @param jobLabel
 * The label identifier for the job to copy.
 *
 * @result
 * A new dictionary describing the job, or NULL if the job could not be found.
 * Must be released by the caller.
 *
 * @discussion
 * The contents of the returned dictionary are NOT wholy representative of the
 * property list on-disk and are not stable from release to release. This 
 * routine is deprecated and will be removed in a future release. There will be
 * no provided replacement.
 */
__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_6, __MAC_10_10, __IPHONE_3_0, __IPHONE_8_0)
XPC_EXPORT XPC_NONNULL2
CFDictionaryRef
SMJobCopyDictionary(CFStringRef domain, CFStringRef jobLabel);

/*!
 * @function SMCopyAllJobDictionaries
 * @abstract
 * Copy the job description dictionaries for all jobs in the given domain.
 *
 * @param domain
 * The job's domain (e.g. {@link kSMDomainSystemLaunchd} or
 * {@link kSMDomainUserLaunchd}).
 *
 * @result
 * A new array containing all job dictionaries, or NULL if an error occurred. 
 * Must be released by the caller.
 *
 * @discussion
 * SMCopyAllJobDictionaries returns an array of the job description dictionaries
 * for all jobs in the given domain, or NULL if an error occurred. This routine
 * is deprecated and will be removed in a future release. There will be no
 * provided replacement.
 *
 * For the specific use of testing the state of a login item that may have been
 * enabled with SMLoginItemSetEnabled() in order to show that state to the
 * user, this function remains the recommended API. A replacement API for this
 * specific use will be provided before this function is removed.
 */
__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_6, __MAC_10_10, __IPHONE_3_0, __IPHONE_8_0)
XPC_EXPORT
CFArrayRef
SMCopyAllJobDictionaries(CFStringRef domain);

/*!
 * @function SMJobSubmit
 * @abstract
 * Submits the given job to the specified domain.
 * 
 * @param domain
 * The job's domain (e.g. {@link kSMDomainSystemLaunchd} or
 * {@link kSMDomainUserLaunchd}).
 *
 * @param job
 * A dictionary describing a job.
 *
 * @param auth
 * An AuthorizationRef containing the {@link kSMRightModifySystemDaemons} right
 * if the given domain is kSMDomainSystemLaunchd. Otherwise, NULL may be passed.
 *
 * @param outError
 * Upon unsuccessful return, a new CFError object describing the error.  Upon 
 * successful return, this argument is set to NULL.  This argument may be NULL. 
 * It is the responsibility of the application to release the error reference.
 *
 * @result 
 * True if the job was submitted successfully, otherwise false.
 *
 * @discussion
 * This routine is deprecated and will be removed in a future release. A 
 * replacement will be provided by libxpc.
 */
__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_6, __MAC_10_10, __IPHONE_3_0, __IPHONE_8_0)
XPC_EXPORT XPC_NONNULL2
Boolean
SMJobSubmit(CFStringRef domain, CFDictionaryRef job, AuthorizationRef auth,
	CFErrorRef *outError);

/*!
 * @function SMJobRemove
 *
 * @abstract
 * Removes the job with the given label from the specified domain.
 *
 * @param domain
 * The job's domain (e.g. {@link kSMDomainSystemLaunchd} or
 * {@link kSMDomainUserLaunchd}).
 *
 * @param jobLabel
 * The label for the job to remove.
 *
 * @param auth
 * An AuthorizationRef containing the {@link kSMRightModifySystemDaemons} right
 * if the given domain is kSMDomainSystemLaunchd. Otherwise, NULL may be passed.
 *
 * @param wait
 * Pass true to block until the process for the given job has exited.
 *
 * @param outError
 * Upon unsuccessful return, a new CFError object describing the error.  Upon 
 * successful return, this argument is set to NULL.  This argument may be NULL. 
 * It is the responsibility of the application to release the error reference.
 *
 * @result
 * True if the job was removed successfully, otherwise false.
 *
 * @discussion
 * This routine is deprecated and will be removed in a future release. A
 * replacement will be provided by libxpc.
 */
__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_6, __MAC_10_10, __IPHONE_3_0, __IPHONE_8_0)
XPC_EXPORT XPC_NONNULL2
Boolean
SMJobRemove(CFStringRef domain, CFStringRef jobLabel,
	AuthorizationRef auth, Boolean wait, CFErrorRef *outError);

#if !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
/*!
 * @function SMJobBless
 *
 * If the job is already installed, success is returned.
 *
 * In order to use this function the following requirements must be met:
 *
 * 1.	The calling application and target executable tool must both be signed.
 * 
 * 2.	The calling application's Info.plist must include a
 *		"SMPrivilegedExecutables" dictionary of strings. Each string is a
 *		textual representation of a code signing requirement used to determine
 *		whether the application owns the privileged tool once installed (i.e. in
 *		order for subsequent versions to update the installed version).
 *
 *		Each key of SMPrivilegedExecutables is a reverse-DNS label for the helper
 *		tool (must be globally unique).
 *
 * 3.	The helper tool must have an embedded Info.plist containing an 
 *		"SMAuthorizedClients" array of strings. Each string is a textual 
 *		representation of a code signing requirement describing a client which 
 *		is allowed to add and remove the tool.
 *
 * 4.	The helper tool must have an embedded launchd plist. The only required 
 *		key in this plist is the Label key. When the launchd plist is extracted 
 *		and written to disk, the key for ProgramArguments will be set to an 
 *		array of 1 element pointing to a standard location. You cannot specify 
 *		your own Program or ProgramArguments, so do not rely on custom command 
 *		line arguments being passed to your tool. Pass any parameters via IPC.
 *		This plist must be embedded in the __TEXT,__launchd_plist section of the
 *		binary.
 *
 *		A property list may be embedded in an executable at link-time with the
 *		-sectcreate linker flag.
 *
 * 5.	The helper tool must reside in the Contents/Library/LaunchServices 
 *		directory inside the application bundle, and its name must be its 
 *		launchd job label. So if your launchd job label is 
 *		"com.apple.Mail.helper", this must be the name of the tool in your 
 *		application bundle.
 * 
 * @param domain
 * The job's domain. Passing any value other than {@link kSMDomainSystemLaunchd}
 * will result in undefined behavior.
 *
 * @param executableLabel
 * The label of the privileged executable to install. This label must be one of
 * the keys found in the SMPrivilegedExecutables dictionary in the application's
 * Info.plist.
 *
 * @param auth
 * An authorization reference containing the 
 * {@link kSMRightBlessPrivilegedHelper} right.
 *
 * @param outError
 * Upon unsuccessful return, a new CFError object describing the error.  Upon 
 * successful return, this argument is set to NULL.  This argument may be NULL. 
 * It is the responsibility of the application to release the error reference.
 *
 * @result
 * True if the helper tool was successfully bootstrapped, otherwise false.
 *
 * @discussion
 * SMJobBless submits the executable for the given label as a launchd job.  This
 * routine obviates the need for a setuid helper invoked via
 * AuthorizationExecuteWithPrivileges() in order to install a launchd plist.
 */
__OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_3_0)
XPC_EXPORT XPC_NONNULL2
Boolean
SMJobBless(CFStringRef domain, CFStringRef executableLabel,
	AuthorizationRef auth, CFErrorRef *outError);
#endif // !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)

#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
#undef AuthorizationRef
#endif // (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)

__END_DECLS

#endif // __SERVICE_MANAGEMENT__
