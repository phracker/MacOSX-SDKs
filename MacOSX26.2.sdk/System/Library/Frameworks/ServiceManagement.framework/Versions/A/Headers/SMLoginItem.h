#ifndef __SERVICE_MANAGEMENT_LOGIN_ITEM__
#define __SERVICE_MANAGEMENT_LOGIN_ITEM__

#include <TargetConditionals.h>
#include <sys/cdefs.h>

#include <xpc/xpc.h>
#include <CoreFoundation/CoreFoundation.h>

__BEGIN_DECLS

/*!
 * @function SMLoginItemSetEnabled
 *
 * @abstract 
 * Enable a helper application located in the main application bundle's 
 * Contents/Library/LoginItems directory.
 *
 * This API has been deprecated. Please use SMAppService to enable SMLoginItems
 *
 * @param identifier
 * The bundle identifier of the helper application bundle.
 *
 * @param enabled
 * The Boolean enabled state of the helper application. This value is effective
 * only for the currently logged in user. If true, the helper application will
 * be started immediately (and upon subsequent logins) and kept running. If
 * false, the helper application will no longer be kept running.
 *
 * @result 
 * Returns true if the requested change has taken effect.
 */
__OSX_DEPRECATED(10.6, 13.0, "Please use SMAppService instead")
XPC_EXPORT XPC_NONNULL1
Boolean
SMLoginItemSetEnabled(CFStringRef identifier, Boolean enabled);

__END_DECLS

#endif // __SERVICE_MANAGEMENT_LOGIN_ITEM__
