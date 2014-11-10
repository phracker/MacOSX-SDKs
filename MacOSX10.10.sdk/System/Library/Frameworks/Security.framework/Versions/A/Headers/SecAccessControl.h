/*
 * Copyright (c) 2014 Apple Inc. All Rights Reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

/*!
 @header SecAccessControl
 SecAccessControl defines access rights for items.
 */

#ifndef _SECURITY_SECACCESSCONTROL_H_
#define _SECURITY_SECACCESSCONTROL_H_

#include <Security/SecBase.h>
#include <CoreFoundation/CFError.h>

__BEGIN_DECLS

/*!
 @function SecAccessControlGetTypeID
 @abstract Returns the type identifier of SecAccessControl instances.
 @result The CFTypeID of SecAccessControl instances.
 */
CFTypeID SecAccessControlGetTypeID(void)
__OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);

typedef CF_OPTIONS(CFIndex, SecAccessControlCreateFlags) {
    kSecAccessControlUserPresence     = 1 << 0,
} __OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);

/*!
 @function SecAccessControlCreateWithFlags
 @abstract Creates new access control object based on protection type and additional flags.
 @param allocator Allocator to be used by this instance.
 @param protection Protection class to be used for the item. One of kSecAttrAccessible constants.
 @param flags
 @param error Additional error information filled in case of failure.
 @result Newly created access control object.
 */
SecAccessControlRef SecAccessControlCreateWithFlags(CFAllocatorRef allocator, CFTypeRef protection,
                                                    SecAccessControlCreateFlags flags, CFErrorRef *error)
__OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);

__END_DECLS

#endif // _SECURITY_SECACCESSCONTROL_H_
