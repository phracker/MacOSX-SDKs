/*
 *  Copyright (c) 2010 Apple Inc. All rights reserved.
 */

#ifndef __SM_LOGIN_ITEM_H__
#define __SM_LOGIN_ITEM_H__

#include <sys/cdefs.h>

__BEGIN_DECLS

/*!
 * @function SMLoginItemSetEnabled
 * @abstract Enable a helper application located in the main application
 * bundle's Contents/Library/LoginItems directory.
 *
 * @param identifier The bundle identifier of the helper application bundle.
 * @param enabled The Boolean enabled state of the helper application. This
 * value is effective only for the currently logged in user. If true, the
 * helper application will be started immediately (and upon subsequent logins)
 * and kept running. If false, the helper application will no longer be kept
 * running.
 *
 * @result Returns true if the requested change has taken effect.
 */

Boolean SMLoginItemSetEnabled(CFStringRef identifier, Boolean enabled);

__END_DECLS

#endif /* __SM_LOGIN_ITEM_H__ */